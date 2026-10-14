#include <ghidra/FunctionBodyFinalizer.h>
#include <ghidra/Program.h>
#include <ghidra/ProgramDB.h>
#include <ghidra/Listing.h>
#include <ghidra/Instruction.h>
#include <ghidra/FunctionManager.h>
#include <ghidra/Function.h>
#include <ghidra/FunctionIterator.h>
#include <ghidra/AddressSet.h>
#include <ghidra/AddressSetView.h>
#include <ghidra/AddressFactory.h>
#include <ghidra/TaskMonitor.h>
#include <ghidra/MessageLog.h>
#include <ghidra/SourceType.h>
#include <ghidra/Msg.h>
#include <ghidra/Memory.h>
#include <ghidra/MemoryBlock.h>

#include <string>
#include <vector>
#include <algorithm>
#include <unordered_map>
#include <cstdint>

namespace ghidra {

// Maximum body extension past the entry when the next function entry is far
// away. 512 truncated large real functions (large_x86_64.elf: ~46 functions
// stalled at ~120 decoded instructions each although the sweep had decoded
// everything — the listing exporter only emits body-covered instructions).
// 8192 covers the largest observed bodies (~4.3KB); the next-entry clamp
// still prevents crossing known boundaries, and extension only follows
// actually-decoded instructions.
static constexpr uint64_t kBodyFinalizerMaxScan = 8192;

FunctionBodyFinalizer::FunctionBodyFinalizer()
    : AbstractAnalyzer(
          "Function Body Finalizer",
          "Extends function bodies to cover all decoded instructions between "
          "the function entry and the next function boundary.",
          AnalyzerType::FUNCTION_ANALYZER) {
    setDefaultEnablement(true);
    setSupportsOneTimeAnalysis(true);
    setPriority(AnalysisPriority::FUNCTION_ANALYSIS.after());
}

bool FunctionBodyFinalizer::canAnalyze(Program* program) const {
    return program != nullptr;
}

bool FunctionBodyFinalizer::added(Program* program, const AddressSetView& set,
                                  TaskMonitor* monitor, MessageLog& log)
{
    if (!program) return false;

    FunctionManager* funcMgr = program->getFunctionManager();
    Listing* listing = program->getListing();
    AddressFactory* af = program->getAddressFactory();
    if (!funcMgr || !listing || !af) return false;

    if (monitor) monitor->setMessage(getName() + ": Starting");

    // 1. Collect all functions and their entry points.
    std::vector<Function*> allFuncs;
    {
        FunctionIterator fit = funcMgr->getFunctions(true);
        while (fit.hasNext()) {
            Function* f = fit.next();
            if (f) allFuncs.push_back(f);
        }
    }

    if (allFuncs.empty()) {
        if (monitor) monitor->setMessage(getName() + ": No functions found");
        return true;
    }

    std::vector<uint64_t> funcEntries;
    std::unordered_map<uint64_t, Function*> entryToFunc;
    for (Function* f : allFuncs) {
        uint64_t ep = static_cast<uint64_t>(f->getEntryPoint().getOffset());
        funcEntries.push_back(ep);
        entryToFunc[ep] = f;
    }
    std::sort(funcEntries.begin(), funcEntries.end());

    // 2. Single pass over all decoded instructions: attribute each to the
    //     nearest preceding function entry, then record the extent.
    //     This is O(N log M) — N instructions, M function entries.
    std::unordered_map<uint64_t, uint64_t> funcMaxAddr;  // entry → last covered addr
    Memory* memory = program->getMemory();

    std::vector<Instruction*> allInsts = listing->getAllInstructions();
    for (Instruction* inst : allInsts) {
        if (!inst) continue;
        uint64_t addr = static_cast<uint64_t>(inst->getAddress().getOffset());
        uint64_t addrEnd = addr + inst->getLength() - 1;

        // Skip instructions in non-executable memory blocks
        // (e.g. import thunks decoded data in .idata as garbage instructions)
        Address instAddr = inst->getAddress();
        MemoryBlock* block = memory ? memory->getBlock(instAddr) : nullptr;
        if (block && !block->isExecute()) continue;

        // Nearest function entry ≤ addr
        auto it = std::upper_bound(funcEntries.begin(), funcEntries.end(), addr);
        if (it == funcEntries.begin()) continue;
        --it;
        uint64_t entry = *it;

        // Clamp to the next function boundary or max scan distance
        auto nextIt = std::upper_bound(funcEntries.begin(), funcEntries.end(), entry);
        uint64_t maxBound = entry + kBodyFinalizerMaxScan;
        if (nextIt != funcEntries.end()) {
            uint64_t nextEntry = *nextIt;
            if (nextEntry > entry && nextEntry - 1 < maxBound)
                maxBound = nextEntry - 1;
        }

        if (addrEnd > maxBound)
            addrEnd = maxBound;

        auto& stored = funcMaxAddr[entry];
        if (addrEnd > stored)
            stored = addrEnd;
    }

    // 3. For each function whose body is smaller than the instruction range,
    //     remove and re-create with the expanded body.
    int extended = 0;
    int skipped = 0;
    int removedFail = 0;
    int recreateFail = 0;
    int noInstr = 0;

    for (Function* func : allFuncs) {
        if (monitor && monitor->isCancelled()) break;

        uint64_t entry = static_cast<uint64_t>(func->getEntryPoint().getOffset());

        const AddressSet& body = func->getBody();
        uint64_t bodyStart = body.getMinAddress().isValid()
                                 ? static_cast<uint64_t>(body.getMinAddress().getOffset())
                                 : entry;
        uint64_t bodyEnd = body.getMaxAddress().isValid()
                               ? static_cast<uint64_t>(body.getMaxAddress().getOffset())
                               : entry;
        uint64_t bodySize = (bodyEnd >= bodyStart) ? (bodyEnd - bodyStart + 1) : 0;

        auto maxIt = funcMaxAddr.find(entry);
        if (maxIt == funcMaxAddr.end()) {
            if (bodySize <= 2)
                noInstr++;
            continue;
        }

        uint64_t realEnd = maxIt->second;
        if (realEnd <= entry) continue;

        uint64_t newSize = realEnd - entry + 1;
        if (newSize <= bodySize) {
            skipped++;
            continue;
        }

        // Expand the body
        Address entryAddr = af->oldGetAddressFromLong(entry);
        AddressSet newBody(entryAddr, af->oldGetAddressFromLong(realEnd));

        SourceType src = func->getSource();
        std::string name = func->getName();
        // Preserve attributes across remove/recreate (analysis passes such
        // as import-thunk detection key off them; losing isThunk here made
        // PLT stubs take import prototypes meant for externals).
        bool wasThunk = func->isThunk();
        bool wasExternal = func->isExternal();

        if (!funcMgr->removeFunction(func->getEntryPoint())) {
            removedFail++;
            continue;
        }

        try {
            Function* recreated = funcMgr->createFunction(name, entryAddr, newBody, src);
            if (recreated) {
                recreated->setThunk(wasThunk);
                recreated->setExternal(wasExternal);
            }
            extended++;
        } catch (const std::exception& e) {
            recreateFail++;
            log.append(getName(), "Failed to re-create 0x" + std::to_string(entry) +
                       ": " + e.what());
            try {
                funcMgr->createFunction(name, entryAddr,
                                        AddressSet(entryAddr, entryAddr),
                                        SourceType::ANALYSIS);
            } catch (const std::exception& e2) {
                log.append(getName(), "CRITICAL: lost function at 0x" +
                           std::to_string(entry) + ": " + e2.what());
            }
        }
    }

    Msg::info(getName(), "Complete: extended=" + std::to_string(extended) +
              " skipped=" + std::to_string(skipped) +
              " noInstr=" + std::to_string(noInstr) +
              " removeFail=" + std::to_string(removedFail) +
              " recreateFail=" + std::to_string(recreateFail));
    if (monitor) monitor->setMessage(getName() + ": Done (" + std::to_string(extended) + " extended)");
    return true;
}

} // namespace ghidra