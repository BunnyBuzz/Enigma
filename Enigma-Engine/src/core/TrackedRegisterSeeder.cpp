#include <ghidra/TrackedRegisterSeeder.h>

#include <ghidra/AddressSet.h>
#include <ghidra/Function.h>
#include <ghidra/FunctionIterator.h>
#include <ghidra/FunctionManager.h>
#include <ghidra/LanguageID.h>
#include <ghidra/Memory.h>
#include <ghidra/MemoryBlock.h>
#include <ghidra/Program.h>
#include <ghidra/Symbol.h>
#include <ghidra/SymbolTable.h>

#include <architecture.hh>
#include <globalcontext.hh>
#include <translate.hh>

namespace ghidra {
namespace {

using Mapper = std::function<uint64_t(uint64_t)>;

void seedRange(ghidra_decompiler::Architecture* arch,
               ghidra_decompiler::AddrSpace* codeSpace, FunctionManager* fm,
               const ghidra_decompiler::VarnodeData& reg,
               const Mapper& mapAddress,
               const std::function<uint64_t(uint64_t)>& valueForEntry) {
    ghidra_decompiler::TrackedSet& defaults =
        arch->context->getTrackedDefault();
    FunctionIterator fit = fm->getFunctions(true);
    while (fit.hasNext()) {
        Function* func = fit.next();
        if (!func || func->isExternal() || func->isThunk()) continue;
        const AddressSet& body = func->getBody();
        if (body.isEmpty()) continue;
        uint64_t start = mapAddress(
            static_cast<uint64_t>(func->getEntryPoint().getOffset()));
        uint64_t end = mapAddress(
            static_cast<uint64_t>(body.getMaxAddress().getOffset())) + 1;
        if (end <= start) continue;
        try {
            ghidra_decompiler::Address a1(codeSpace,
                static_cast<ghidra_decompiler::int8>(start));
            ghidra_decompiler::Address a2(codeSpace,
                static_cast<ghidra_decompiler::int8>(end));
            ghidra_decompiler::TrackedSet& track =
                arch->context->createSet(a1, a2);
            track = defaults;
            ghidra_decompiler::TrackedContext tc;
            tc.loc = reg;
            tc.val = valueForEntry(start);
            track.push_back(tc);
        } catch (...) {
            // A bad range must never abort decompiler setup.
        }
    }
}

ghidra_decompiler::VarnodeData lookupRegister(
    ghidra_decompiler::Architecture* arch, const std::string& name,
    bool& found) {
    found = true;
    try {
        return arch->translate->getRegister(name);
    } catch (...) {
        found = false;
        return ghidra_decompiler::VarnodeData();
    }
}

} // namespace

void TrackedRegisterSeeder::seed(
    Program* program, ghidra_decompiler::Architecture* arch,
    const std::function<uint64_t(uint64_t)>& mapAddress) {
    if (!program || !arch || !arch->context || !arch->translate) return;
    FunctionManager* fm = program->getFunctionManager();
    ghidra_decompiler::AddrSpace* codeSpace = arch->getDefaultCodeSpace();
    if (!fm || !codeSpace) return;

    const std::string langId = program->getLanguageID().getIdAsString();

    if (langId.find("MIPS") != std::string::npos) {
        // MIPS PIC code addresses its GOT through $t9; the ABI guarantees it
        // holds the current function's entry address on entry.
        bool found = false;
        ghidra_decompiler::VarnodeData t9 =
            lookupRegister(arch, "t9", found);
        if (!found) return;
        seedRange(arch, codeSpace, fm, t9, mapAddress,
                  [](uint64_t entry) { return entry; });
        return;
    }

    if (langId.find("PowerPC") != std::string::npos) {
        // PPC32 PIC keeps the GOT base in r30 (.got2 + 0x8000); PPC64 uses r2
        // for the same role (_SDA_BASE_/_SDA2_BASE_). Linker-generated
        // .plt_pic32 stubs load call targets relative to that base.
        uint64_t gotBase = 0;
        if (SymbolTable* symbols = program->getSymbolTable()) {
            auto sda = symbols->getGlobalSymbols("_SDA_BASE_");
            if (sda.empty())
                sda = symbols->getGlobalSymbols("_SDA2_BASE_");
            if (!sda.empty()) {
                gotBase = mapAddress(static_cast<uint64_t>(
                    sda[0]->getAddress().getOffset())) + 0x8000;
            }
        }
        if (gotBase == 0) {
            if (Memory* memory = program->getMemory()) {
                if (MemoryBlock* got2 = memory->getBlock(".got2")) {
                    gotBase = mapAddress(static_cast<uint64_t>(
                        got2->getStart().getOffset())) + 0x8000;
                }
            }
        }
        if (gotBase == 0) return;

        const std::string regName =
            langId.find(":64:") != std::string::npos ? "r2" : "r30";
        bool found = false;
        ghidra_decompiler::VarnodeData toc =
            lookupRegister(arch, regName, found);
        if (!found) return;
        seedRange(arch, codeSpace, fm, toc, mapAddress,
                  [gotBase](uint64_t) { return gotBase; });
    }
}

} // namespace ghidra
