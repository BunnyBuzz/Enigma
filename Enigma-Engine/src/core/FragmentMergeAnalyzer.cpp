#include <ghidra/FragmentMergeAnalyzer.h>
#include <ghidra/Program.h>
#include <ghidra/FunctionManager.h>
#include <ghidra/Function.h>
#include <ghidra/FunctionIterator.h>
#include <ghidra/AddressSet.h>
#include <ghidra/AddressFactory.h>
#include <ghidra/AddressSpace.h>
#include <ghidra/TaskMonitor.h>
#include <ghidra/MessageLog.h>
#include <ghidra/Disassembler.h>
#include <ghidra/AutoNaming.h>
#include <ghidra/Memory.h>
#include <ghidra/Listing.h>
#include <ghidra/Instruction.h>
#include <ghidra/ReferenceManager.h>
#include <ghidra/Reference.h>
#include <ghidra/RefType.h>
#include <algorithm>
#include <cstdint>
#include <cstring>
#include <vector>
#include <utility>
#include <unordered_set>
#include <sstream>
#include <chrono>
#include <iostream>

namespace ghidra {

namespace {

// Read up to 4 bytes at `addr`; returns the number of bytes read.
size_t readBytes(Memory* memory, const Address& addr, uint8_t* out, size_t count) {
    if (!memory || count == 0) return 0;
    try {
        return static_cast<size_t>(memory->getBytes(addr, out, static_cast<int>(count)));
    } catch (...) {
        return 0;
    }
}

// A function entry whose entire body is an x86 epilogue fragment.  These are
// exactly the tails Ghidra's x86-64 compiler patterns list as valid prepatterns
// for a following function start (RET, XOR EAX,EAX; RET, POP reg; RET, ...).
// When such a fragment is immediately followed by a real entry, Ghidra treats
// the bytes as the tail of the preceding function rather than as their own
// function.  Trailing NOP/INT3 padding is allowed.
bool isTrivialEpilogueFragment(Memory* memory, const Address& entry, uint64_t length) {
    if (length == 0 || length > 4) return false;
    uint8_t b[4] = {0, 0, 0, 0};
    if (readBytes(memory, entry, b, static_cast<size_t>(length)) != length) return false;

    size_t n = static_cast<size_t>(length);
    while (n > 1 && (b[n - 1] == 0x90 || b[n - 1] == 0xCC)) --n;
    while (n > 1 && b[0] == 0x90) {
        for (size_t i = 1; i < n; i++) b[i - 1] = b[i];
        --n;
    }

    if (b[0] == 0xC3) return n == 1;                      // RET
    if (b[0] == 0xC2) return n == 3;                      // RET imm16
    if (b[n - 1] != 0xC3) return false;
    if (n == 2) {
        if (b[0] == 0xC9) return true;                    // LEAVE; RET
        if (b[0] >= 0x58 && b[0] <= 0x5F) return true;    // POP r64; RET
        return false;
    }
    if (n == 3) {
        if (b[0] == 0x31 && b[1] == 0xC0) return true;    // XOR EAX,EAX; RET
        if (b[0] == 0x33 && b[1] == 0xC0) return true;    // XOR EAX,EAX; RET
        if (b[0] == 0x41 && b[1] >= 0x58 && b[1] <= 0x5F) return true; // POP R8-R15; RET
        if (b[0] == 0x66 && b[1] == 0x90) return true;    // NOP(2); RET
        return false;
    }
    if (n == 4) {
        if (b[0] == 0x48 && b[1] == 0x31 && b[2] == 0xC0) return true; // XOR RAX,RAX; RET
        if (b[0] == 0x83 && b[1] == 0xC8 && b[2] == 0xFF) return true; // OR EAX,-1; RET
        if (b[0] == 0x0F && b[1] == 0x1F && b[2] == 0x00) return true; // NOP(3); RET
        return false;
    }
    return false;
}

// True when `entry` begins with an epilogue/padding sequence rather than a
// real function prologue.  Used to avoid dropping a real entry in favour of a
// stray fragment.
bool beginsEpilogueOrPadding(Memory* memory, const Address& entry) {
    uint8_t b[4] = {0, 0, 0, 0};
    if (readBytes(memory, entry, b, 4) < 2) return false;
    if (b[0] == 0xC3 || b[0] == 0xC2 || b[0] == 0xC9) return true;
    if (b[0] == 0x90 || b[0] == 0xCC) return true;
    if (b[0] == 0x0F && b[1] == 0x1F) return true;        // multi-byte NOP
    if (b[0] == 0x31 && b[1] == 0xC0) return true;        // XOR EAX,EAX
    if (b[0] == 0x33 && b[1] == 0xC0) return true;
    if (b[0] >= 0x58 && b[0] <= 0x5F) return true;        // POP r64
    if (b[0] == 0x41 && b[1] >= 0x58 && b[1] <= 0x5F) return true; // POP R8-R15
    return false;
}

// A thunk entry (JMP rel32/rel8 or JMP [rip+disp]) is a genuine function in
// Ghidra even when it sits a few bytes after another entry.
bool beginsUnconditionalJumpThunk(Memory* memory, const Address& entry) {
    uint8_t b[2] = {0, 0};
    if (readBytes(memory, entry, b, 2) < 2) return false;
    if (b[0] == 0xE9 || b[0] == 0xEB) return true;
    if (b[0] == 0xFF && (b[1] == 0x25 || b[1] == 0x27)) return true;
    return false;
}

bool hasCallReference(ReferenceManager* refMgr, const Address& addr) {
    if (!refMgr) return false;
    for (Reference* ref : refMgr->getReferencesTo(addr)) {
        if (!ref) continue;
        const RefType* rt = ref->getReferenceType();
        if (rt && rt->isCall()) return true;
    }
    return false;
}

bool hasFlowReference(ReferenceManager* refMgr, const Address& addr) {
    if (!refMgr) return false;
    for (Reference* ref : refMgr->getReferencesTo(addr)) {
        if (!ref) continue;
        const RefType* rt = ref->getReferenceType();
        if (rt && rt->isFlow()) return true;
    }
    return false;
}

// True when the code unit ending at `addr - 1` ends exactly at `addr` and is
// a control-flow terminator.  Ghidra's x86-64 GCC pattern list treats such a
// position as a valid function start (prepatterns include RET/JMP), so an
// epilogue stub there is a real function when nothing branches into it.
// Capstone mnemonics are lowercase, so compare case-insensitively.
bool mnemonicIs(const std::string& mnemonic, const char* expectedLower) {
    size_t n = std::strlen(expectedLower);
    if (mnemonic.size() != n) return false;
    for (size_t i = 0; i < n; i++) {
        char c = mnemonic[i];
        if (c >= 'A' && c <= 'Z') c = static_cast<char>(c - 'A' + 'a');
        if (c != expectedLower[i]) return false;
    }
    return true;
}

bool abutsTerminator(Listing* listing, const AddressSpace* space, uint64_t addr) {
    if (!listing || !space || addr == 0) return false;
    Address prev(const_cast<AddressSpace*>(space), static_cast<int64_t>(addr - 1));
    Instruction* inst = listing->getInstructionContaining(prev);
    if (!inst) return false;
    // Instruction does not override CodeUnit::getMaxAddress(), so compute the
    // end from address + length explicitly.
    if (static_cast<uint64_t>(inst->getAddress().getOffset()) +
            static_cast<uint64_t>(inst->getLength()) != addr) {
        return false;
    }
    const std::string& mn = inst->getMnemonicString();
    return mnemonicIs(mn, "ret") || mnemonicIs(mn, "retf") ||
           mnemonicIs(mn, "iret") || mnemonicIs(mn, "iretd") ||
           mnemonicIs(mn, "iretq") || mnemonicIs(mn, "jmp");
}

// Build a set of all CALL rel32 (0xE8) target addresses in executable memory.
// Used to identify compiler-generated stubs that are genuine call targets
// even when ReferenceManager lacks the reference (disassembly hasn't reached
// the caller yet).
static std::unordered_set<uint64_t> buildCallTargetSet(Memory* memory) {
    std::unordered_set<uint64_t> callTargets;
    if (!memory) return callTargets;

    auto blocks = memory->getBlocks();
    for (auto* block : blocks) {
        if (!block || !block->isExecute() || !block->isInitialized()) continue;
        uint64_t blockStart = block->getStart().getOffset();
        uint64_t blockEnd = block->getEnd().getOffset();
        uint64_t size = blockEnd - blockStart + 1;
        if (size < 5) continue;
        if (size > 8 * 1024 * 1024) size = 8 * 1024 * 1024;
        std::vector<uint8_t> buf(static_cast<size_t>(size));
        Address addr(block->getStart());
        int read = block->getBytes(addr, buf.data(), static_cast<int>(buf.size()));
        if (read < 5) continue;
        size = static_cast<uint64_t>(read);

        for (uint64_t off = 0; off + 5 <= size; ++off) {
            if (buf[off] != 0xE8) continue; // CALL rel32
            int32_t rel = 0;
            std::memcpy(&rel, buf.data() + off + 1, sizeof(rel));
            uint64_t callAddr = blockStart + off;
            uint64_t targetAddr = callAddr + 5 + static_cast<uint64_t>(static_cast<int64_t>(rel));
            callTargets.insert(targetAddr);
        }
    }
    return callTargets;
}

} // namespace

FragmentMergeAnalyzer::FragmentMergeAnalyzer()
    : AbstractAnalyzer("Fragment Merge",
                       "Merges func_start_ entries within 16 bytes of another func_start_ entry "
                       "into the parent function, reducing false function count without affecting recall.",
                       AnalyzerType::BYTE_ANALYZER) {
    setPriority(AnalysisPriority::CODE_ANALYSIS.after());
    setDefaultEnablement(true);
    setSupportsOneTimeAnalysis(true);
}

bool FragmentMergeAnalyzer::canAnalyze(Program* program) const {
    return program != nullptr;
}

bool FragmentMergeAnalyzer::added(Program* program, const AddressSetView& set,
                                   TaskMonitor* monitor, MessageLog& log) {
    if (!program || !monitor) return true;
    monitor->setMessage("Merging func_start_ fragments into parent functions...");

    auto t0 = std::chrono::high_resolution_clock::now();

    FunctionManager* funcMgr = program->getFunctionManager();
    if (!funcMgr) return true;

    LanguageID lid = program->getLanguageID();
    std::string lidStr = lid.getIdAsString();
    std::string arch;
    if (lidStr.find("x86") != std::string::npos || lidStr.find("X86") != std::string::npos) arch = "x86";
    else if (lidStr.find("ARM") != std::string::npos || lidStr.find("AARCH64") != std::string::npos) arch = "ARM";
    const bool isX86 = (arch == "x86");
    int bitness = (lidStr.find("64") != std::string::npos) ? 64 : 32;
    bool bigEndian = lidStr.find(":BE:") != std::string::npos;

    Memory* memory = program->getMemory();
    ReferenceManager* refMgr = program->getReferenceManager();
    Listing* listing = program->getListing();
    AddressFactory* addrFactory = program->getAddressFactory();
    const AddressSpace* defaultSpace =
        addrFactory ? addrFactory->getDefaultAddressSpace() : nullptr;

    // Collect all function addresses and names, sorted by address
    std::vector<std::pair<uint64_t, std::string>> funcs;
    FunctionIterator fit = funcMgr->getFunctions(true);
    while (fit.hasNext()) {
        Function* f = fit.next();
        if (f) {
            funcs.emplace_back(f->getEntryPoint().getOffset(), f->getName());
        }
    }

    if (funcs.empty()) return true;

    // Precompute call targets from raw bytes for x86. This catches call
    // targets whose callers haven't been disassembled yet (so ReferenceManager
    // lacks the reference). Only needed for the stub-abuts-terminator case.
    std::unordered_set<uint64_t> callTargets;
    if (isX86 && memory) {
        callTargets = buildCallTargetSet(memory);
    }

    // Merge fragments created inside an existing function.  On x86 the
    // earlier entry of a close pair can instead be a stray epilogue fragment
    // (RET, XOR EAX,EAX; RET, ...) that Ghidra folds into the preceding
    // function; adjacent call targets and jump thunks are distinct functions
    // and are never merged.
    std::unordered_set<uint64_t> toRemove;
    uint64_t prevAddr = funcs[0].first;
    std::string prevName = funcs[0].second;
    for (size_t i = 1; i < funcs.size(); i++) {
        uint64_t addr = funcs[i].first;
        const std::string& name = funcs[i].second;
        uint64_t gap = addr - prevAddr;

        const bool adjacent = name.rfind("func_0x", 0) == 0 &&
                              prevName.rfind("func_0x", 0) == 0 &&
                              gap > 0 && gap <= 4;
        if (!adjacent) {
            prevAddr = addr;
            prevName = name;
            continue;
        }

        bool keepBoth = false;
        bool removeEarlier = false;
        if (isX86 && memory && defaultSpace) {
            Address prevEntry(const_cast<AddressSpace*>(defaultSpace),
                              static_cast<int64_t>(prevAddr));
            Address curEntry(const_cast<AddressSpace*>(defaultSpace),
                             static_cast<int64_t>(addr));
            const bool prevCall = hasCallReference(refMgr, prevEntry);
            const bool prevFlow = hasFlowReference(refMgr, prevEntry);
            const bool curCall = hasCallReference(refMgr, curEntry);
            const bool curFlow = hasFlowReference(refMgr, curEntry);
            const bool prevStub = isTrivialEpilogueFragment(memory, prevEntry, gap);
            const bool curStub = beginsEpilogueOrPadding(memory, curEntry);
            const bool curThunk = beginsUnconditionalJumpThunk(memory, curEntry);
            const bool prevAbutsTerminator =
                abutsTerminator(listing, defaultSpace, prevAddr);
            const bool prevHasAnyRef = prevCall || prevFlow;
            const bool prevIsCallTarget = callTargets.count(prevAddr) > 0;

            if (prevCall) {
                // Ghidra keeps direct-call targets even when an adjacent entry
                // follows within a few bytes.
                keepBoth = true;
            } else if (prevStub && prevFlow) {
                // The stub is a branch target inside the preceding function
                // (e.g. a shared epilogue reached by JMP/JZ): the bytes stay
                // in that body, and the later real entry is the function.
                removeEarlier = true;
            } else if (prevStub && prevAbutsTerminator) {
                // Stub directly follows the previous function's RET/JMP.
                // Ghidra only creates a separate function here if the stub
                // has an incoming reference (CALL or unconditional JMP from
                // another function). Compiler-generated zero-return stubs
                // with no refs are folded into the preceding function.
                // Check both ReferenceManager (for already-disassembled callers)
                // and raw-byte call target scan (for callers not yet disassembled).
                if (prevHasAnyRef || prevIsCallTarget) {
                    keepBoth = true;
                } else {
                    removeEarlier = true;
                }
            } else if (curCall || curThunk) {
                // The later entry is a real target: drop the earlier fragment
                // if that is all it is, otherwise keep both.
                if (prevStub) removeEarlier = true;
                else keepBoth = true;
            } else if (prevStub && !curStub) {
                // Tiny epilogue immediately before a real entry: the bytes
                // belong to the preceding function in Ghidra.
                removeEarlier = true;
            }
        }

        if (removeEarlier) {
            toRemove.insert(prevAddr);
            prevAddr = addr;
            prevName = name;
            continue;
        }
        if (keepBoth) {
            prevAddr = addr;
            prevName = name;
            continue;
        }
        toRemove.insert(addr); // default: later entry is an interior fragment
    }

    // --- Step 1b: orphan trivial-epilogue stubs ---
    // The x86 pattern list contains `xor eax,eax; ret` / `or eax,-1; ret`
    // stubs. Ghidra does not create functions for these unless control
    // actually reaches them from outside the containing function. Without
    // this pass a stub in the middle of a function (e.g. a shared `return 0`
    // block reached only by an intra-function JZ) stays a separate function
    // and truncates its container. A stub is kept when it is a direct call
    // target (ReferenceManager or raw-byte scan), has a data reference
    // (address-taken), or is reached by a flow reference from a different
    // function interval.
    if (isX86 && memory && defaultSpace) {
        std::vector<uint64_t> allEntries;
        allEntries.reserve(funcs.size());
        for (const auto& f : funcs) allEntries.push_back(f.first);

        for (const auto& f : funcs) {
            uint64_t addr = f.first;
            if (toRemove.count(addr)) continue;
            if (f.second.rfind("func_0x", 0) != 0) continue;

            Address entry(const_cast<AddressSpace*>(defaultSpace),
                          static_cast<int64_t>(addr));
            bool isStub = false;
            for (uint64_t len = 1; len <= 4; ++len) {
                if (isTrivialEpilogueFragment(memory, entry, len)) {
                    isStub = true;
                    break;
                }
            }
            if (!isStub) continue;
            if (callTargets.count(addr)) continue;

            bool keep = false;
            for (Reference* ref : refMgr->getReferencesTo(entry)) {
                if (!ref) continue;
                const RefType* rt = ref->getReferenceType();
                if (!rt) continue;
                if (rt->isCall() || !rt->isFlow()) {
                    // Direct call or address-taken (data/indirect) reference.
                    keep = true;
                    break;
                }
                uint64_t from = static_cast<uint64_t>(
                    ref->getFromAddress().getOffset());
                auto it = std::upper_bound(allEntries.begin(), allEntries.end(),
                                           from);
                if (it == allEntries.begin()) {
                    keep = true;
                    break;
                }
                --it;
                if (*it != addr) {
                    // Reached from a different function interval: real target.
                    keep = true;
                    break;
                }
            }
            if (!keep) toRemove.insert(addr);
        }
    }

    auto t1 = std::chrono::high_resolution_clock::now();

    if (!toRemove.empty()) {
        if (!defaultSpace) return true;

        for (uint64_t addr : toRemove) {
            Address funcAddr(const_cast<AddressSpace*>(defaultSpace), static_cast<int64_t>(addr));
            funcMgr->removeFunction(funcAddr);
        }
    }

    auto t2 = std::chrono::high_resolution_clock::now();

    // --- Step 2: Gap bridging (reference-required) ---
    if (arch == "x86") {
        auto disassembler = createDisassembler(arch, bitness, bigEndian);
        if (disassembler) {
            monitor->setMessage("Scanning gaps for CALL-target functions...");

            std::vector<std::pair<uint64_t, uint64_t>> funcRanges;
            FunctionIterator fit2 = funcMgr->getFunctions(true);
            while (fit2.hasNext()) {
                Function* f = fit2.next();
                if (f) {
                    const AddressSet& body = f->getBody();
                    if (body.isEmpty()) {
                        uint64_t entry = f->getEntryPoint().getOffset();
                        funcRanges.emplace_back(entry, entry);
                    } else {
                        uint64_t start = body.getMinAddress().getOffset();
                        uint64_t end = body.getMaxAddress().getOffset();
                        funcRanges.emplace_back(start, end);
                    }
                }
            }

            auto t3 = std::chrono::high_resolution_clock::now();

            int gapFunctions = 0;
            AddressSpace* defSpace = const_cast<AddressSpace*>(program->getAddressFactory()->getDefaultAddressSpace());
            auto blocks2 = memory->getBlocks();

            uint64_t totalBytesScanned = 0;
            uint64_t totalCallsFound = 0;

            for (auto* block : blocks2) {
                if (!block || !block->isExecute() || !block->isInitialized()) continue;
                uint64_t blockStart = block->getStart().getOffset();
                uint64_t blockEnd = block->getEnd().getOffset();

                uint64_t bufSize = (blockEnd - blockStart + 1);
                if (bufSize > 8 * 1024 * 1024) bufSize = 8 * 1024 * 1024;
                if (bufSize < 5) continue;
                std::vector<uint8_t> blockBuf(static_cast<size_t>(bufSize));
                Address blockStartAddr(defSpace, static_cast<int64_t>(blockStart));
                int got = block->getBytes(blockStartAddr, blockBuf.data(), static_cast<int>(blockBuf.size()));
                if (got < 5) continue;
                bufSize = static_cast<uint64_t>(got);
                totalBytesScanned += bufSize;

                std::vector<uint64_t> funcStarts;
                funcStarts.reserve(funcRanges.size());
                for (const auto& fr : funcRanges) {
                    funcStarts.push_back(fr.first);
                }

                for (uint64_t callOff = 0; callOff + 5 <= bufSize; callOff++) {
                    if (blockBuf[callOff] != 0xE8) continue;
                    totalCallsFound++;

                    int32_t rel = *reinterpret_cast<const int32_t*>(blockBuf.data() + callOff + 1);
                    uint64_t callSrc = blockStart + callOff;
                    uint64_t callTgt = callSrc + 5 + static_cast<uint64_t>(static_cast<int64_t>(rel));

                    if (callTgt < blockStart || callTgt > blockEnd) continue;

                    auto it = std::upper_bound(funcStarts.begin(), funcStarts.end(), callTgt);
                    if (it == funcStarts.begin() || it == funcStarts.end()) continue;
                    size_t idx = static_cast<size_t>(std::distance(funcStarts.begin(), it));

                    uint64_t prevEnd = funcRanges[idx - 1].second;
                    uint64_t currStart = funcRanges[idx].first;

                    if (prevEnd < blockStart || currStart > blockEnd) continue;
                    if (callTgt <= prevEnd) continue;

                    uint64_t gapStart = std::max(prevEnd + 1, blockStart);
                    uint64_t gapEnd = std::min(currStart > 0 ? currStart - 1 : 0, blockEnd);
                    if (callTgt < gapStart || callTgt > gapEnd) continue;

                    uint64_t gapSize = gapEnd - gapStart + 1;
                    if (gapSize > 128) continue;

                    Address tgtAddr(defSpace, static_cast<int64_t>(callTgt));
                    if (funcMgr->getFunctionAt(tgtAddr)) continue;
                    if (funcMgr->getFunctionContaining(tgtAddr)) continue;
                    if (!listing->isUndefined(tgtAddr)) continue;

                    try {
                        uint8_t fb = 0;
                        memory->getBytes(tgtAddr, &fb, 1);
                        if (fb == 0xCC || fb == 0x00) continue;
                    } catch (...) { continue; }

                    try {
                        AddressSet body(tgtAddr, tgtAddr);
                        std::ostringstream funcName;
                        funcName << AutoNaming::nameVal("func", callTgt);
                        funcMgr->createFunction(funcName.str(), tgtAddr, body, SourceType::ANALYSIS);
                        gapFunctions++;
                    } catch (const std::exception&) {}
                }
            }

            auto t4 = std::chrono::high_resolution_clock::now();

            auto ms0 = std::chrono::duration_cast<std::chrono::milliseconds>(t1 - t0).count();
            auto ms1 = std::chrono::duration_cast<std::chrono::milliseconds>(t2 - t1).count();
            auto ms2 = std::chrono::duration_cast<std::chrono::milliseconds>(t3 - t2).count();
            auto ms3 = std::chrono::duration_cast<std::chrono::milliseconds>(t4 - t3).count();

            std::cerr << "[FRAGMENT-MERGE-PROFILE] t_identify=" << ms0 << "ms"
                      << " t_remove=" << ms1 << "ms"
                      << " t_funcRanges=" << ms2 << "ms"
                      << " t_scanBlocks=" << ms3 << "ms"
                      << " removed=" << toRemove.size()
                      << " gapFuncs=" << gapFunctions
                      << " bytesScanned=" << totalBytesScanned
                      << " callsFound=" << totalCallsFound
                      << std::endl;
        }
    }
    return true;
}

} // namespace ghidra
