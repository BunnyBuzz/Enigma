/**
 * Enigma Engine - Rust demangler + offcut string label backend tests.
 * Covers GUI backlog G8 (GP-6108, Rust v0 clean prototypes) and G9
 * (GP-6345, offcut-string labels): both backends were implemented but had
 * no dedicated tests. Drives RustDemanglerAnalyzer::added() and
 * StringsAnalyzer::added() on synthetic ProgramDBs.
 */
#include <iostream>
#include <string>
#include <vector>
#include <cstdint>

#include "ghidra/RustDemanglerAnalyzer.h"
#include "ghidra/StringsAnalyzer.h"
#include "ghidra/ProgramDB.h"
#include "ghidra/AddressSpace.h"
#include "ghidra/ProgramAddressFactory.h"
#include "ghidra/Memory.h"
#include "ghidra/Listing.h"
#include "ghidra/SymbolTable.h"
#include "ghidra/Symbol.h"
#include "ghidra/ReferenceManager.h"
#include "ghidra/RefType.h"
#include "ghidra/TaskMonitor.h"
#include "ghidra/MessageLog.h"
#include "ghidra/Language.h"
#include "ghidra/AddressSet.h"
#include "ghidra/SourceType.h"

int passed = 0, total = 0;
#define TEST(n, x) do { total++; if(x){std::cout<<"[PASS] "<<n<<"\n"<<std::flush;passed++;}else{std::cout<<"[FAIL] "<<n<<"\n"<<std::flush;} } while(0)

using namespace ghidra;

struct TestProgram {
    GenericAddressSpace ramSpace;
    GenericAddressSpace constSpace;
    GenericAddressSpace uniqueSpace;
    GenericAddressSpace registerSpace;
    GenericAddressSpace stackSpace;
    ProgramDB prog;

    TestProgram(const std::string& name)
        : ramSpace("ram", 64, AddressSpace::TYPE_RAM, 1),
          constSpace("const", 64, AddressSpace::TYPE_CONSTANT, 2),
          uniqueSpace("unique", 64, AddressSpace::TYPE_UNIQUE, 3),
          registerSpace("register", 64, AddressSpace::TYPE_REGISTER, 4),
          stackSpace("stack", 64, AddressSpace::TYPE_STACK, 5),
          prog(name, nullptr, nullptr) {
        auto* addrFactory = dynamic_cast<ProgramAddressFactory*>(prog.getAddressFactory());
        if (addrFactory) {
            addrFactory->addAddressSpace(&ramSpace);
            addrFactory->setDefaultSpace(&ramSpace);
            addrFactory->setConstantSpace(&constSpace);
            addrFactory->setUniqueSpace(&uniqueSpace);
            addrFactory->setRegisterSpace(&registerSpace);
            addrFactory->setStackSpace(&stackSpace);
        }
        prog.setLanguageID(LanguageID("x86:LE:64:default"));
    }

    Address addr(uint64_t off) {
        return Address(&ramSpace, static_cast<int64_t>(off));
    }
};

static bool hasNameAt(SymbolTable* st, const Address& a, const std::string& name) {
    auto syms = st->getSymbols(a);
    for (auto* s : syms) {
        if (s && s->getName() == name) return true;
    }
    return false;
}

int main() {
    std::cout << "\n--- G8: Rust demangler ---" << std::endl;
    {
        TestProgram tprog("rust_demangle_test");
        SymbolTable* st = tprog.prog.getSymbolTable();
        st->createLabel(tprog.addr(0x1000), "_RC5hello", SourceType::IMPORTED);
        st->createLabel(tprog.addr(0x1010), "_RN4test3fooE", SourceType::IMPORTED);
        st->createLabel(tprog.addr(0x1020), "_RNC4test3fooE", SourceType::IMPORTED);
        st->createLabel(tprog.addr(0x1028), "_RNvC4testE", SourceType::IMPORTED);
        st->createLabel(tprog.addr(0x1030), "_Z3foov", SourceType::IMPORTED);

        RustDemanglerAnalyzer analyzer;
        TEST("rust canAnalyze", analyzer.canAnalyze(&tprog.prog));
        AddressSet set;
        StubTaskMonitor monitor;
        MessageLog log;
        TEST("rust added", analyzer.added(&tprog.prog, set, &monitor, log));
        TEST("rust v0 C-path", hasNameAt(st, tprog.addr(0x1000), "hello"));
        TEST("rust v0 N-path", hasNameAt(st, tprog.addr(0x1010), "test::foo"));
        TEST("rust v0 N-path no leading separator",
             hasNameAt(st, tprog.addr(0x1020), "test::foo"));
        TEST("rust legacy", hasNameAt(st, tprog.addr(0x1028), "test"));
        TEST("rust non-rust untouched",
             hasNameAt(st, tprog.addr(0x1030), "_Z3foov") &&
             !hasNameAt(st, tprog.addr(0x1030), "foo"));
    }

    std::cout << "\n--- G9: offcut string labels ---" << std::endl;
    {
        TestProgram tprog("offcut_strings_test");
        Memory* memory = tprog.prog.getMemory();
        DefaultMemory* defaultMem = dynamic_cast<DefaultMemory*>(memory);
        TEST("offcut memory is DefaultMemory", defaultMem != nullptr);
        if (!defaultMem) {
            std::cout << "Rust/Strings Backend Tests: " << passed << "/" << total << " passed.\n";
            return 1;
        }
        // "Message\0" at 0x2000 (8 bytes incl NUL > min length 5), plus a
        // few code-ish bytes at 0x2010 to source the interior reference.
        std::vector<uint8_t> data(0x20, 0xCC);
        const char* msg = "Message";
        for (int i = 0; i < 7; i++) data[i] = static_cast<uint8_t>(msg[i]);
        data[7] = 0x00;
        DefaultMemoryBlock* block =
            defaultMem->createInitializedBlock(".rodata", tprog.addr(0x2000), data.size());
        TEST("offcut block created", block != nullptr);
        block->putBytes(tprog.addr(0x2000), data.data(), static_cast<int>(data.size()));

        StringsAnalyzer analyzer;
        TEST("strings canAnalyze", analyzer.canAnalyze(&tprog.prog));
        AddressSet set;
        StubTaskMonitor monitor;
        MessageLog log;
        TEST("strings added", analyzer.added(&tprog.prog, set, &monitor, log));
        TEST("strings phase1 defines data",
             tprog.prog.getListing()->getDataAt(tprog.addr(0x2000)) != nullptr);

        SymbolTable* st = tprog.prog.getSymbolTable();
        st->createLabel(tprog.addr(0x2000), "s_Message", SourceType::ANALYSIS);
        ReferenceManager* refMgr = tprog.prog.getReferenceManager();
        TEST("offcut ref added",
             refMgr->addMemoryReference(tprog.addr(0x2010), tprog.addr(0x2002),
                                        &RefTypes::DATA, SourceType::ANALYSIS, 0) != nullptr);
        TEST("strings added again", analyzer.added(&tprog.prog, set, &monitor, log));
        TEST("offcut label created",
             hasNameAt(st, tprog.addr(0x2002), "s_Message_+2"));
        TEST("offcut no label without ref",
             !st->hasSymbol(tprog.addr(0x2003)));
    }

    std::cout << "\n=== Summary ===" << std::endl;
    std::cout << "Rust/Strings Backend Tests: " << passed << "/" << total << " passed." << std::endl;
    return (passed == total) ? 0 : 1;
}
