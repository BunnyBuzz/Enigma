#include <ghidra/ScalarOperandAnalyzer.h>
#include <ghidra/Program.h>
#include <ghidra/Listing.h>
#include <ghidra/Instruction.h>
#include <ghidra/Scalar.h>
#include <ghidra/AddressFactory.h>
#include <ghidra/AddressSpace.h>
#include <ghidra/Memory.h>
#include <ghidra/MemoryBlock.h>
#include <ghidra/SymbolTable.h>
#include <ghidra/FunctionManager.h>
#include <ghidra/RefTypeFactory.h>
#include <ghidra/ReferenceManager.h>
#include <ghidra/TaskMonitor.h>
#include <ghidra/MessageLog.h>
#include <ghidra/BookmarkManager.h>
#include <ghidra/RelocationTable.h>
#include <ghidra/Relocation.h>
#include <ghidra/Disassembler.h>
#include <ghidra/FunctionIterator.h>
#include <ghidra/Function.h>
#include <ghidra/AddressFactory.h>
#include <algorithm>
#include <cstdlib>
#include <unordered_set>
#include <vector>

namespace ghidra {

static constexpr uint64_t MASKS[9] = {
    0ULL, 0x0ffULL, 0x0ffffULL, 0x0ffffffULL, 0x0ffffffffULL,
    0x0ffffffffffULL, 0x0ffffffffffffULL, 0x0ffffffffffffffULL, 0xffffffffffffffffULL
};

static constexpr const char* OPT_NAME_RELOCATION_GUIDE = "Relocation Table Guide";

ScalarOperandAnalyzer::ScalarOperandAnalyzer()
    : AbstractAnalyzer("Scalar Operand References",
                       "Finds scalar operands that are valid memory addresses and creates references.",
                       AnalyzerType::INSTRUCTION_ANALYZER) {
    setPriority(AnalysisPriority::REFERENCE_ANALYSIS.before().before());
    setDefaultEnablement(true);
    setSupportsOneTimeAnalysis(true);
}

ScalarOperandAnalyzer::ScalarOperandAnalyzer(const std::string& name, const std::string& description)
    : AbstractAnalyzer(name, description, AnalyzerType::INSTRUCTION_ANALYZER) {
    setPriority(AnalysisPriority::REFERENCE_ANALYSIS.before().before());
    setDefaultEnablement(true);
    setSupportsOneTimeAnalysis(true);
}

bool ScalarOperandAnalyzer::canAnalyze(Program* program) const {
    // Skip ELF programs (handled by ElfScalarOperandAnalyzer)
    std::string format = program->getExecutableFormat();
    if (format.find("ELF") != std::string::npos ||
        format.find("elf") != std::string::npos) {
        // But still check: ELF may be handled by ElfScalarOperandAnalyzer
    }
    Address min = program->getMinAddress();
    return min.isValid();
}

bool ScalarOperandAnalyzer::getDefaultEnablement(Program* program) const {
    // Match Ghidra Java: skip languages where addresses don't appear directly in code
    std::string format = program->getExecutableFormat();
    if (format.find("ELF") != std::string::npos) return false;

    Address min = program->getMinAddress();
    if (!min.isValid() || min.getOffset() == 0) {
        return false;
    }
    if (program->getAddressFactory()->getDefaultAddressSpace()->getSize() < 32) {
        return false;
    }

    return true;
}

void ScalarOperandAnalyzer::registerOptions(Options& options, Program* program) {
    options.registerBool(OPT_NAME_RELOCATION_GUIDE, relocationGuideEnabled_,
                         "Use relocation table entries to guide pointer analysis.");
}

void ScalarOperandAnalyzer::optionsChanged(Options& options, Program* program) {
    relocationGuideEnabled_ = options.getBool(OPT_NAME_RELOCATION_GUIDE);
}

bool ScalarOperandAnalyzer::isValidRelocationAddress(Program* program, const Address& target) {
    RelocationTable* relocTable = program->getRelocationTable();
    if (!relocTable) return false;
    auto relocs = relocTable->getRelocations(target);
    return !relocs.empty();
}

bool ScalarOperandAnalyzer::added(Program* program, const AddressSetView& set,
                                   TaskMonitor* monitor, MessageLog& log) {
    std::cerr << "[INFO] ScalarOperandAnalyzer: starting added(" << getName() << "), set size=" << set.getNumAddresses() << std::endl;
    int count = 0;
    int nextLogCount = 100;
    int totalInstructions = 0;
    // PHASE 10: hard instruction limit to prevent infinite loops
    static const int SOA_MAX_INSTR_ITER = 5000000;
    currentMonitor_ = monitor;
    if (monitor) {
        monitor->initialize(set.getNumAddresses());
    }

    Listing* listing = program->getListing();
    std::cerr << "[INFO] ScalarOperandAnalyzer: got listing, getting instructions..." << std::endl;
    // `set` can be a stale/default range when ProgramDB has no valid min
    // address (common for loaders that map memory directly at high VAs).
    // Analyse every decoded instruction so high-based binaries are covered.
    auto instructions = listing->getAllInstructions();
    std::cerr << "[INFO] ScalarOperandAnalyzer: got " << instructions.size() << " instructions, starting loop" << std::endl;
    for (Instruction* instr : instructions) {
        if (monitor && monitor->isCancelled()) break;
        if (count >= SOA_MAX_INSTR_ITER) {
            std::cerr << "[WARN] ScalarOperandAnalyzer: instruction iter exceeded "
                      << SOA_MAX_INSTR_ITER << ", breaking" << std::endl;
            break;
        }
        if (monitor) {
            monitor->setProgress(++count);
        }
        if (count >= nextLogCount) {
            std::cerr << "[INFO] ScalarOperandAnalyzer: processed " << count << " instructions" << std::endl;
            nextLogCount += 100;
        }
        checkOperands(program, instr);
    }
    if (jumpTableAnomalies_ > 0) {
        std::cerr << "[WARN] ScalarOperandAnalyzer: " << jumpTableAnomalies_
                  << " jump table anomalies detected, " << jumpTableIterations_
                  << " total iterations, " << jumpTableVisited_.size() << " unique addresses" << std::endl;
    }
    std::cerr << "[INFO] ScalarOperandAnalyzer: completed " << count << " instructions total" << std::endl;
    currentMonitor_ = nullptr;
    return true;
}

void ScalarOperandAnalyzer::checkOperands(Program* program, Instruction* instr) {
    static int soaLogCounter_ = 0;
    // PHASE 10: hard iteration limit to prevent hangs on pathological binaries
    static const int SOA_MAX_SCALAR_ITER = 5000000;
    for (int i = 0; i < instr->getNumOperands(); ++i) {
        if (soaLogCounter_ >= SOA_MAX_SCALAR_ITER) return;
        auto scalars = instr->getOperandScalars(i);
        for (Scalar* scalar : scalars) {
            if (soaLogCounter_ >= SOA_MAX_SCALAR_ITER) return;
            uint64_t value = static_cast<uint64_t>(scalar->getUnsignedValue());
            // PHASE 10: aggressive filter for shell32-class binaries.
            // Skip values that are clearly not valid user-space pointers:
            // - Below 0x10000 (small constants, near-null, segment-like)
            // - Powers of two minus one (mask constants like 0x7fffffff)
            // - Common stack limit constants (0x7fff0000-0x7fffffff)
            // - Image-base-like values (0x180000000 etc., but those go through later)
            if (value < 0x10000) continue;
            if (value == 0xffff || value == 0xff00 || value == 0xffffff ||
                value == 0xff0000 || value == 0xff00ff || value == 0xffffffff ||
                value == 0xffffff00 || value == 0xffff0000 || value == 0xff000000) {
                continue;
            }
            // Skip 0x7fff_xxxx range (stack limit constants, mask values)
            if (value >= 0x7fff0000 && value <= 0x7fffffff) continue;
            // Skip sign-extended 32-bit negatives (0xffffffff_xxxxxxxx).
            // NOTE: must mask on the high 32 bits; a plain ">= 0xffff0000"
            // wrongly rejects real 64-bit image addresses above 4GB.
            if ((value & 0xFFFFFFFF00000000ULL) == 0xFFFFFFFF00000000ULL) continue;
            // Skip 0x10000-0x1000000 (likely not real code pointers)
            if (value < 0x100000) continue;

            if (++soaLogCounter_ % 1000 == 0) {
                std::cerr << "[INFO] ScalarOperandAnalyzer: scalar iter=" << soaLogCounter_
                          << " (instr 0x" << std::hex << instr->getAddress().getOffset() << std::dec
                          << " op " << i << " val 0x" << std::hex << value << std::dec << ")" << std::endl;
            }

            // Try default space first
            if (addReference(program, instr, i, instr->getAddress().getAddressSpace(), scalar)) {
                continue;
            }

            // PHASE 10: only iterate other address spaces if the scalar value
            // is large enough to be a real address. Most scalars that fail
            // the default-space check are small constants or stack offsets
            // that won't be valid in any space.
            if (value < 0x10000) continue;

            auto spaces = program->getAddressFactory()->getAddressSpaces();
            for (const AddressSpace* space : spaces) {
                if (addReference(program, instr, i, space, scalar)) {
                    break;
                }
            }
        }
    }
}

bool ScalarOperandAnalyzer::addReference(Program* program, Instruction* instr,
                                           int opIndex, const AddressSpace* space,
                                           Scalar* scalar) {
    // PHASE 10: hard cap on individual addReference calls to prevent hangs
    static int addRefCounter_ = 0;
    if (++addRefCounter_ % 100000 == 0) {
        std::cerr << "[INFO] ScalarOperandAnalyzer: addRef iter=" << addRefCounter_ << std::endl;
    }
    if (addRefCounter_ > 5000000) return false;

    if (space->isOverlaySpace()) return false;

    int sizeInBytes = space->getSize() / 8;
    if (sizeInBytes <= 0 || sizeInBytes > 8) return false;

    uint64_t value = static_cast<uint64_t>(scalar->getUnsignedValue() & MASKS[sizeInBytes]);
    Address addr(const_cast<AddressSpace*>(space), static_cast<int64_t>(value));

    // Check relocation table guide
    if (relocationGuideEnabled_ && !isValidRelocationAddress(program, addr)) {
        return false;
    }

    MemoryBlock* block = program->getMemory()->getBlock(addr);
    if (block == nullptr || !block->isInitialized()) {
        Symbol* sym = program->getSymbolTable()->getPrimarySymbol(addr);
        if (sym == nullptr || sym->getSource() == SourceType::DEFAULT) {
            return false;
        }
    }

    // Computed jumps through a memory table (e.g. JMP [table + idx*8]) carry
    // the table base as a scalar; the table itself lives in .rodata, so the
    // offcut-code test below can never see it. Detect the table from the
    // instruction's computed-jump flow instead.
    FlowType* flow = instr->getFlowType();
    if (flow && flow->isJump() && flow->isComputed()) {
        auto scalars = instr->getOperandScalars(opIndex);
        checkForJumpTable(program, instr, opIndex, scalars, addr);
        return false;
    }

    if (checkOffcutFuncRef(program, addr)) {
        // Could be a jump table - check for it
        auto scalars = instr->getOperandScalars(opIndex);
        checkForJumpTable(program, instr, opIndex, scalars, addr);
        return false;
    }

    if (!instr->getOperandReferences(opIndex).empty()) {
        return false;
    }

    const RefType* refType = RefTypeFactory::getDefaultMemoryRefType(
        instr, opIndex, addr, false);
    instr->addOperandReference(opIndex, addr, refType, SourceType::ANALYSIS);
    return true;
}

bool ScalarOperandAnalyzer::checkOffcutFuncRef(Program* program, const Address& addr) {
    Instruction* instr = program->getListing()->getInstructionContaining(addr);
    if (instr == nullptr) return false;
    if (!(instr->getAddress() == addr)) return true;
    Function* func = program->getFunctionManager()->getFunctionContaining(addr);
    if (func != nullptr && !(func->getEntryPoint() == addr)) return true;
    return false;
}

void ScalarOperandAnalyzer::checkForJumpTable(Program* program, Instruction* refInstr,
                                                int opIndex,
                                                const std::vector<Scalar*>& opObjects,
                                                const Address& addr) {
    // Skip if already visited (avoid re-scanning the same table)
    uint64_t addrKey = addr.getOffset();
    if (jumpTableVisited_.count(addrKey)) return;
    jumpTableVisited_.insert(addrKey);

    // The scalar is the table *base*, which lives in data — there is no
    // instruction at `addr`. Use the referencing instruction's flow type.
    FlowType* ftype = refInstr ? refInstr->getFlowType() : nullptr;
    if (!ftype || !(ftype->isJump() && ftype->isComputed())) return;

    // A data table behind an indirect jump is a switch only when the index is
    // range-checked first. Virtual-call / callback tables have no such branch;
    // decoding their targets as switch cases invents large amounts of code
    // that Ghidra never attributes to the enclosing function.
    {
        Listing* listing = program->getListing();
        Address cur = refInstr->getMinAddress();
        bool bounded = false;
        for (int i = 0; i < 8 && !bounded; ++i) {
            Instruction* prev = nullptr;
            for (int back = 1; back <= 24 && !prev; ++back) {
                Address before;
                try { before = cur.subtract(back); } catch (...) { break; }
                Instruction* cand = listing->getInstructionContaining(before);
                if (cand && cand->getMinAddress() < cur) prev = cand;
            }
            if (!prev) break;
            cur = prev->getMinAddress();
            const std::string& mn = prev->getMnemonicString();
            if (mn == "ja" || mn == "jae" || mn == "jb" || mn == "jbe" ||
                mn == "jg" || mn == "jge" || mn == "jl" || mn == "jle" ||
                mn == "jhi" || mn == "jhs" || mn == "jlo" || mn == "jls") {
                bounded = true;
            }
        }
        if (!bounded) return;
    }

    // Figure out the entry size from the scalar
    long entryLen = 0;
    for (Scalar* sc : opObjects) {
        if (!sc) continue;
        long value = static_cast<long>(sc->getUnsignedValue());
        if (value == 4 || value == 2 || value == 8) {
            entryLen = value;
            break;
        }
    }
    if (entryLen == 0) return;

    // Get function body ranges for fast is-in-function-body check
    FunctionManager* funcMgr = program->getFunctionManager();
    std::vector<std::pair<uint64_t, uint64_t>> funcRanges;
    if (funcMgr) {
        FunctionIterator fit = funcMgr->getFunctions(true);
        while (fit.hasNext()) {
            Function* func = fit.next();
            const AddressSet& body = func->getBody();
            if (!body.isEmpty()) {
                funcRanges.push_back({static_cast<uint64_t>(body.getMinAddress().getOffset()),
                                      static_cast<uint64_t>(body.getMaxAddress().getOffset())});
            }
        }
    }
    auto isInAnyFunc = [&funcRanges](uint64_t offset) -> bool {
        for (const auto& r : funcRanges) {
            if (offset >= r.first && offset <= r.second) return true;
        }
        return false;
    };

    Memory* memory = program->getMemory();

    auto readTableEntry = [&](const Address& entryAddr) -> Address {
        if (entryLen == 4) {
            uint8_t bytes[4] = {};
            MemoryBlock* blk = memory->getBlock(entryAddr);
            if (!blk) return Address();
            blk->getBytes(entryAddr, bytes, 4);
            uint64_t val = static_cast<uint64_t>(bytes[0]) |
                (static_cast<uint64_t>(bytes[1]) << 8) |
                (static_cast<uint64_t>(bytes[2]) << 16) |
                (static_cast<uint64_t>(bytes[3]) << 24);
            Address entryAddrSpace(entryAddr.getAddressSpace(), static_cast<int64_t>(val));
            if (memory->getBlock(entryAddrSpace)) return entryAddrSpace;
        } else if (entryLen == 8) {
            uint8_t bytes[8] = {};
            MemoryBlock* blk = memory->getBlock(entryAddr);
            if (!blk) return Address();
            blk->getBytes(entryAddr, bytes, 8);
            uint64_t val = static_cast<uint64_t>(bytes[0]) |
                (static_cast<uint64_t>(bytes[1]) << 8) |
                (static_cast<uint64_t>(bytes[2]) << 16) |
                (static_cast<uint64_t>(bytes[3]) << 24) |
                (static_cast<uint64_t>(bytes[4]) << 32) |
                (static_cast<uint64_t>(bytes[5]) << 40) |
                (static_cast<uint64_t>(bytes[6]) << 48) |
                (static_cast<uint64_t>(bytes[7]) << 56);
            Address entryAddrSpace(entryAddr.getAddressSpace(), static_cast<int64_t>(val));
            if (memory->getBlock(entryAddrSpace)) return entryAddrSpace;
        } else if (entryLen == 2) {
            uint8_t bytes[2] = {};
            MemoryBlock* blk = memory->getBlock(entryAddr);
            if (!blk) return Address();
            blk->getBytes(entryAddr, bytes, 2);
            uint64_t val = static_cast<uint64_t>(bytes[0]) |
                (static_cast<uint64_t>(bytes[1]) << 8);
            Address entryAddrSpace(entryAddr.getAddressSpace(), static_cast<int64_t>(val));
            if (memory->getBlock(entryAddrSpace)) return entryAddrSpace;
        }
        return Address();
    };

    auto checkCancelled = [this]() -> bool {
        return currentMonitor_ && currentMonitor_->isCancelled();
    };

    // Scan forward entries (PHASE 10: use function-range check instead of
    // getInstructionContaining to avoid O(N log N) rebuilds).
    Address scanAddr = addr;
    std::vector<Address> tableTargets;
    int tableCount = 0;
    while (tableCount < MAX_TABLE_ENTRIES) {
        if (checkCancelled()) {
            std::cerr << "[INFO] JumpTable:cancelled:forward=" << tableCount << std::endl;
            break;
        }
        if (isInAnyFunc(static_cast<uint64_t>(scanAddr.getOffset()))) break;
        if (tableCount > 0 && scanAddr <= addr) {
            ++jumpTableAnomalies_;
            std::cerr << "[WARN] JumpTable:wrapped:forward at " << scanAddr.toString() << std::endl;
            break;
        }
        Address target = readTableEntry(scanAddr);
        if (!target.isValid()) break;
        tableTargets.push_back(target);

        // Deliberately no label/reference here: a DATA reference from a
        // computed jump makes the decompiler infer code-pointer types for
        // unrelated parameters. Decoding the case targets below is enough for
        // listing/function-body parity.
        ++tableCount;
        ++jumpTableIterations_;
        try {
            scanAddr = scanAddr.add(entryLen);
        } catch (...) {
            break;
        }
    }

    if (tableCount > 0) {
        program->getBookmarkManager()->setBookmark(addr, "ANALYSIS",
            "Switch table with " + std::to_string(tableCount) + " entries");
    }

    // Scan backward entries
    scanAddr = addr;
    Address prevAddr;
    try {
        prevAddr = addr.subtract(entryLen);
    } catch (...) {
        return;
    }
    int negCount = 0;
    while (negCount < MAX_NEG_ENTRIES) {
        if (checkCancelled()) {
            std::cerr << "[INFO] JumpTable:cancelled:backward=" << negCount << std::endl;
            break;
        }
        if (isInAnyFunc(static_cast<uint64_t>(prevAddr.getOffset()))) break;
        if (negCount > 0 && prevAddr >= addr) {
            ++jumpTableAnomalies_;
            std::cerr << "[WARN] JumpTable:wrapped:backward at " << prevAddr.toString() << std::endl;
            break;
        }
        Address target = readTableEntry(prevAddr);
        if (!target.isValid()) break;
        tableTargets.push_back(target);

        ++negCount;
        ++jumpTableIterations_;
        try {
            prevAddr = prevAddr.subtract(entryLen);
        } catch (...) {
            break;
        }
    }

    // Labels/references alone do not put the case code in the listing; the
    // body finalizer can only extend a function over decoded instructions.
    if (!tableTargets.empty()) decodeJumpTableTargets(program, tableTargets);
}

void ScalarOperandAnalyzer::decodeJumpTableTargets(Program* program,
                                                    const std::vector<Address>& targets) {
    Listing* listing = program->getListing();
    Memory* memory = program->getMemory();
    FunctionManager* funcMgr = program->getFunctionManager();
    if (!listing || !memory) return;

    const std::string lid = program->getLanguageID().getIdAsString();
    std::string arch = "x86";
    if (lid.find("AARCH64") != std::string::npos || lid.find("ARM64") != std::string::npos)
        arch = "aarch64";
    else if (lid.find("ARM") != std::string::npos)
        arch = "ARM";
    else if (lid.find("MIPS") != std::string::npos)
        arch = "MIPS";
    else if (lid.find("PPC") != std::string::npos || lid.find("PowerPC") != std::string::npos)
        arch = "PPC";
    int bitness = (lid.find("64") != std::string::npos) ? 64 : 32;
    bool bigEndian = (lid.find("BE") != std::string::npos);
    auto disassembler = createDisassembler(arch, bitness, bigEndian);
    if (!disassembler) return;

    std::vector<uint64_t> entries;
    if (funcMgr) {
        FunctionIterator fit = funcMgr->getFunctions(true);
        while (fit.hasNext()) {
            Function* f = fit.next();
            if (f && f->getEntryPoint().isValid())
                entries.push_back(static_cast<uint64_t>(f->getEntryPoint().getOffset()));
        }
        std::sort(entries.begin(), entries.end());
    }

    const AddressSpace* space = program->getAddressFactory()
                                    ? program->getAddressFactory()->getDefaultAddressSpace()
                                    : nullptr;
    if (!space) return;

    static constexpr int kMaxCaseInstructions = 128;
    uint8_t buf[16];
    for (const Address& target : targets) {
        if (currentMonitor_ && currentMonitor_->isCancelled()) return;
        MemoryBlock* block = memory->getBlock(target);
        if (!block || !block->isExecute()) continue;
        uint64_t cur = static_cast<uint64_t>(target.getOffset());
        for (int i = 0; i < kMaxCaseInstructions; ++i) {
            Address curAddr(const_cast<AddressSpace*>(space), static_cast<int64_t>(cur));
            if (listing->getInstructionAt(curAddr)) break;
            // Never cross into a different function entry.
            auto next = std::upper_bound(entries.begin(), entries.end(), cur);
            if (next != entries.end() && cur + 4 > *next) break;
            int got = memory->getBytes(curAddr, buf, static_cast<int>(sizeof(buf)));
            if (got <= 0) break;
            std::vector<uint8_t> bytes(buf, buf + got);
            DisassembledInstruction di = disassembler->disassembleOne(bytes, cur);
            if (di.length <= 0) break;
            auto* inst = new Instruction(program, curAddr, di.mnemonic, di.length, di.flowType);
            for (size_t oi = 0; oi < di.operands.size(); ++oi)
                inst->setOperand(static_cast<int>(oi), di.operands[oi]);
            for (size_t oi = 0; oi < di.operandScalars.size(); ++oi)
                for (auto& sc : di.operandScalars[oi])
                    if (sc) inst->addOperandScalar(static_cast<int>(oi), sc.release());
            listing->addInstruction(inst);
            FlowType* ft = di.flowType;
            if (ft && (ft->isTerminal() || (ft->isJump() && !ft->isConditional()))) break;
            cur += static_cast<uint64_t>(di.length);
        }
    }
}

} // namespace ghidra
