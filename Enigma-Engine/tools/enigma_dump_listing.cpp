/// enigma_dump_listing.cpp
/// Emit per-instruction listing CSV mirroring tools/headless/DumpListing.java
/// columns: funcEntry,addr,mnemonic,operands,bytes
/// Usage: enigma_dump_listing <binary> <out.csv>

#include <ghidra/BinaryLoader.h>
#include <ghidra/ProgramDB.h>
#include <ghidra/Memory.h>
#include <ghidra/MemoryBlock.h>
#include <ghidra/FunctionManager.h>
#include <ghidra/Function.h>
#include <ghidra/FunctionIterator.h>
#include <ghidra/SymbolTable.h>
#include <ghidra/ExternalManager.h>
#include <ghidra/Listing.h>
#include <ghidra/Instruction.h>
#include <ghidra/ProgramAddressFactory.h>
#include <ghidra/AddressSpace.h>
#include <ghidra/AddressRange.h>
#include <ghidra/AutoAnalysisManager.h>
#include <ghidra/TaskMonitor.h>
#include <ghidra/MessageLog.h>
#include <ghidra/EntryPointAnalyzer.h>
#include <ghidra/DisassemblyAnalyzer.h>
#include <ghidra/FunctionStartAnalyzer.h>
#include <ghidra/FunctionStartDataPostAnalyzer.h>
#include <ghidra/FunctionStartFuncAnalyzer.h>
#include <ghidra/DataSectionFunctionScannerAnalyzer.h>
#include <ghidra/ApplyDataArchiveAnalyzer.h>
#include <ghidra/MainRecognitionAnalyzer.h>
#include <ghidra/FragmentMergeAnalyzer.h>
#include <ghidra/FidAnalyzer.h>
#include <ghidra/FunctionBodyFinalizer.h>
#include <ghidra/ExternalEntryFunctionAnalyzer.h>
#include <ghidra/FunctionDiscoveryAnalyzer.h>
#include <ghidra/DataRefFunctionAnalyzer.h>
#include <ghidra/PEExceptionAnalyzer.h>
#include <ghidra/ImportThunkAnalyzer.h>
#include <ghidra/ScalarOperandAnalyzer.h>
#include <ghidra/OperandReferenceAnalyzer.h>
#include <ghidra/DataOperandReferenceAnalyzer.h>
#include <ghidra/ConstantPropagationAnalyzer.h>
#include <ghidra/StackReferenceAnalyzer.h>
#include <ghidra/StackVariableAnalyzer.h>
#include <ghidra/DecompInterface.h>

#include <iostream>
#include <fstream>
#include <string>
#include <memory>
#include <cstring>
#include <cstdio>

using namespace ghidra;

namespace {
std::string sanitize(const std::string& s) {
    std::string r = s;
    for (char& c : r) {
        if (c == ',' || c == '\n' || c == '\r') c = ';';
    }
    return r;
}

// disassembleAt(addr,1) emits "0xADDR:  MNEM  OP\n"; split into mnem/operands.
void splitAsmLine(const std::string& line, std::string& mnem, std::string& ops) {
    mnem.clear(); ops.clear();
    size_t colon = line.find(':');
    if (colon == std::string::npos) return;
    std::string rest = line.substr(colon + 1);
    while (!rest.empty() && (rest.front() == ' ' || rest.front() == '\t')) rest.erase(rest.begin());
    size_t sp = rest.find_first_of(" \t");
    if (sp == std::string::npos) { mnem = rest; return; }
    mnem = rest.substr(0, sp);
    std::string tail = rest.substr(sp + 1);
    while (!tail.empty() && (tail.front() == ' ' || tail.front() == '\t')) tail.erase(tail.begin());
    // trim trailing newline/whitespace
    while (!tail.empty() && (tail.back() == '\n' || tail.back() == '\r' || tail.back() == ' ' || tail.back() == '\t'))
        tail.pop_back();
    ops = tail;
}
} // namespace

int main(int argc, char* argv[]) {
    if (argc < 3) {
        std::cerr << "Usage: enigma_dump_listing <binary> <out.csv>\n";
        return 1;
    }
    std::string path = argv[1];
    std::string outPath = argv[2];

    auto loader = createLoader();
    if (!loader || !loader->load(path)) { std::cerr << "Failed to load\n"; return 1; }

    auto* ramSpace = new GenericAddressSpace("ram", 64, AddressSpace::TYPE_RAM, 1);
    auto* constSpace = new GenericAddressSpace("const", 64, AddressSpace::TYPE_CONSTANT, 2);
    auto* uniqueSpace = new GenericAddressSpace("unique", 64, AddressSpace::TYPE_UNIQUE, 3);
    auto* regSpace = new GenericAddressSpace("register", 64, AddressSpace::TYPE_REGISTER, 4);
    auto* stackSpace = new GenericAddressSpace("stack", 64, AddressSpace::TYPE_STACK, 5);

    auto prog = std::make_unique<ProgramDB>("listing", nullptr, nullptr);
    auto* addrFactory = dynamic_cast<ProgramAddressFactory*>(prog->getAddressFactory());
    if (addrFactory) {
        addrFactory->addAddressSpace(ramSpace); addrFactory->addAddressSpace(constSpace);
        addrFactory->addAddressSpace(uniqueSpace); addrFactory->addAddressSpace(regSpace);
        addrFactory->addAddressSpace(stackSpace); addrFactory->setDefaultSpace(ramSpace);
    }
    if (!loader->populateProgram(prog.get())) { std::cerr << "populateProgram failed\n"; return 1; }

    auto* fm = prog->getFunctionManager();
    auto* listing = prog->getListing();

    {
        FunctionDiscoveryOptions fdOpts;
        fdOpts.includeExternalInFunctionManager = true;
        FunctionDiscoveryAnalyzer fdAnalyzer(fdOpts);
        fdAnalyzer.analyzeLoader(*loader);
        if (fm && ramSpace) fdAnalyzer.applyTo(*fm, ramSpace);
    }

    auto analysisMgr = std::make_unique<AutoAnalysisManager>(prog.get());
    analysisMgr->registerAnalyzer(std::make_unique<EntryPointAnalyzer>());
    analysisMgr->registerAnalyzer(std::make_unique<DisassemblyAnalyzer>());
    analysisMgr->registerAnalyzer(std::make_unique<FunctionStartAnalyzer>());
    analysisMgr->registerAnalyzer(std::make_unique<DataSectionFunctionScannerAnalyzer>());
    analysisMgr->registerAnalyzer(std::make_unique<FunctionStartDataPostAnalyzer>());
    analysisMgr->registerAnalyzer(std::make_unique<FunctionStartFuncAnalyzer>());
    analysisMgr->registerAnalyzer(std::make_unique<ApplyDataArchiveAnalyzer>());
    analysisMgr->registerAnalyzer(std::make_unique<ExternalEntryFunctionAnalyzer>());
    analysisMgr->registerAnalyzer(std::make_unique<ghidra::PEExceptionAnalyzer>());
    analysisMgr->registerAnalyzer(std::make_unique<DataRefFunctionAnalyzer>());
    analysisMgr->registerAnalyzer(std::make_unique<ScalarOperandAnalyzer>());
    analysisMgr->registerAnalyzer(std::make_unique<OperandReferenceAnalyzer>());
    analysisMgr->registerAnalyzer(std::make_unique<DataOperandReferenceAnalyzer>());
    analysisMgr->registerAnalyzer(std::make_unique<ConstantPropagationAnalyzer>());
    analysisMgr->registerAnalyzer(std::make_unique<StackReferenceAnalyzer>());
    analysisMgr->registerAnalyzer(std::make_unique<StackVariableAnalyzer>());
    analysisMgr->registerAnalyzer(std::make_unique<FragmentMergeAnalyzer>());
    analysisMgr->registerAnalyzer(std::make_unique<ImportThunkAnalyzer>());
    analysisMgr->registerAnalyzer(std::make_unique<FidAnalyzer>());
    analysisMgr->registerAnalyzer(std::make_unique<MainRecognitionAnalyzer>());
    analysisMgr->registerAnalyzer(std::make_unique<FunctionBodyFinalizer>());
    analysisMgr->analyze(&ghidra::getDummyMonitor());

    DecompInterface decomp;
    if (!decomp.openProgram(prog.get())) {
        std::cerr << "openProgram failed\n";
        return 1;
    }

    auto* space = const_cast<AddressSpace*>(
        prog->getAddressFactory()->getDefaultAddressSpace());
    auto mem = prog->getMemory();

    if (argc >= 4) {
        uint64_t a = std::stoull(argv[3], nullptr, 0);
        Address at(space, static_cast<int64_t>(a));
        std::cout << decomp.disassembleAt(at, 8) << std::endl;
        return 0;
    }

    std::ofstream out(outPath, std::ios::binary);
    if (!out) { std::cerr << "cannot write " << outPath << "\n"; return 1; }
    out << "funcEntry,addr,mnemonic,operands,bytes\n";

    int count = 0;
    auto fit = fm->getFunctions(true);
    while (fit.hasNext()) {
        Function* fn = fit.next();
        if (!fn) continue;
        uint64_t entry = static_cast<uint64_t>(fn->getEntryPoint().getOffset());
        for (Instruction* inst : listing->getInstructions(fn->getBody())) {
            if (!inst) continue;
            uint64_t off = static_cast<uint64_t>(inst->getAddress().getOffset());
            Address a(space, static_cast<int64_t>(off));
            std::string asmLine = decomp.disassembleAt(a, 1);
            std::string mnem, ops;
            splitAsmLine(asmLine, mnem, ops);
            if (mnem.empty()) continue;
            // instruction bytes
            std::string bytes;
            auto instLen = inst->getLength();
            std::vector<uint8_t> raw(static_cast<size_t>(instLen));
            int got = mem->getBytes(a, raw.data(), instLen);
            for (int i = 0; i < got; i++) {
                char buf[3];
                std::snprintf(buf, sizeof(buf), "%02x", raw[i]);
                bytes += buf;
            }
            out << "0x" << std::hex << entry << ",0x" << off << std::dec << ","
                << sanitize(mnem) << "," << sanitize(ops) << "," << bytes << "\n";
            count++;
        }
    }
    std::cout << "enigma_dump_listing wrote " << count << " instructions to " << outPath << "\n";
    return 0;
}
