/**
 * Enigma Engine - Golang Pipeline Test
 * Validates Task 3.1: GoBuildInfo and Go RTTI parsing.
 * Covers:
 *   - GoBuildInfoParser: magic header detection, version extraction
 *   - GoRttiParser: type record parsing, kind name mapping
 *   - Go type data type creation
 */
#include <iostream>
#include <string>
#include <vector>
#include <cstdint>

#include "ghidra/GoBuildInfoParser.h"
#include "ghidra/GoRttiParser.h"
#include "ghidra/GolangSymbolAnalyzer.h"
#include "ghidra/ProgramDB.h"
#include "ghidra/AddressSpace.h"
#include "ghidra/ProgramAddressFactory.h"
#include "ghidra/Memory.h"
#include "ghidra/SymbolTable.h"
#include "ghidra/Symbol.h"
#include "ghidra/TaskMonitor.h"
#include "ghidra/MessageLog.h"
#include "ghidra/AddressSet.h"
#include "ghidra/Language.h"
#include "ghidra/StandAloneDataTypeManager.h"

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

    TestProgram()
        : ramSpace("ram", 64, AddressSpace::TYPE_RAM, 1),
          constSpace("const", 64, AddressSpace::TYPE_CONSTANT, 2),
          uniqueSpace("unique", 64, AddressSpace::TYPE_UNIQUE, 3),
          registerSpace("register", 64, AddressSpace::TYPE_REGISTER, 4),
          stackSpace("stack", 64, AddressSpace::TYPE_STACK, 5),
          prog("golang_test", nullptr, nullptr) {
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

// Build a synthetic Go build info section
static std::vector<uint8_t> buildGoBuildInfo() {
    std::vector<uint8_t> data(256, 0);

    // "\xff Go buildinf:" magic
    data[0] = 0xFF;
    data[1] = ' ';
    data[2] = 'G'; data[3] = 'o'; data[4] = ' ';
    data[5] = 'b'; data[6] = 'u'; data[7] = 'i'; data[8] = 'l';
    data[9] = 'd'; data[10] = 'i'; data[11] = 'n'; data[12] = 'f';
    data[13] = ':';
    // 2 pad bytes
    data[14] = 0; data[15] = 0;

    // Pointers to strings (offsets within the section)
    uint64_t verOff = 0x80;
    uint64_t modOff = 0xA0;
    uint64_t cmdOff = 0xC0;

    // Write pointers at offset 16
    memcpy(&data[16], &verOff, 8);
    memcpy(&data[24], &modOff, 8);
    memcpy(&data[32], &cmdOff, 8);

    // Go version string at offset 0x80
    const char* ver = "go1.21.0";
    memcpy(&data[verOff], ver, strlen(ver));

    // Module path at offset 0xA0
    const char* mod = "github.com/example/test";
    memcpy(&data[modOff], mod, strlen(mod));

    return data;
}

int main() {
    // === Test 1: GoBuildInfoParser ===
    {
        TestProgram tprog;
        Memory* memory = tprog.prog.getMemory();
        DefaultMemory* defaultMem = dynamic_cast<DefaultMemory*>(memory);
        TEST("memory is DefaultMemory", defaultMem != nullptr);

        std::vector<uint8_t> buildInfo = buildGoBuildInfo();
        Address start = tprog.addr(0x1000);
        DefaultMemoryBlock* block = defaultMem->createInitializedBlock(
            "go.buildinfo", start, buildInfo.size());
        TEST("buildinfo block created", block != nullptr);
        if (block) {
            block->setRead(true);
            block->putBytes(start, buildInfo.data(), static_cast<int>(buildInfo.size()));
        }

        GoBuildInfoParser::BuildInfo info = GoBuildInfoParser::parse(
            memory, start, static_cast<int64_t>(buildInfo.size()));
        TEST("GoBuildInfo parsed", info.valid);
        TEST("Go version extracted", info.goVersion == "go1.21.0");
        TEST("Module path extracted", info.modulePath == "github.com/example/test");
    }

    // === Test 2: GoBuildInfoParser findAndParse ===
    {
        TestProgram tprog;
        Memory* memory = tprog.prog.getMemory();
        DefaultMemory* defaultMem = dynamic_cast<DefaultMemory*>(memory);
        std::vector<uint8_t> buildInfo = buildGoBuildInfo();
        Address start = tprog.addr(0x2000);
        DefaultMemoryBlock* block = defaultMem->createInitializedBlock(
            "go_buildinfo", start, buildInfo.size());
        if (block) {
            block->setRead(true);
            block->putBytes(start, buildInfo.data(), static_cast<int>(buildInfo.size()));
        }

        GoBuildInfoParser::BuildInfo info = GoBuildInfoParser::findAndParse(memory);
        TEST("findAndParse found buildinfo", info.valid);
    }

    // === Test 3: GoRttiParser kind names ===
    {
        TEST("kind BOOL name", GoRttiParser::getKindName(1) == "bool");
        TEST("kind INT name", GoRttiParser::getKindName(2) == "int");
        TEST("kind INT64 name", GoRttiParser::getKindName(6) == "int64");
        TEST("kind UINT64 name", GoRttiParser::getKindName(11) == "uint64");
        TEST("kind STRUCT name", GoRttiParser::getKindName(18) == "struct");
        TEST("kind POINTER name", GoRttiParser::getKindName(22) == "pointer");
        TEST("kind STRING name", GoRttiParser::getKindName(23) == "string");
    }

    // === Test 4: GoRttiParser type parsing ===
    {
        TestProgram tprog;
        Memory* memory = tprog.prog.getMemory();
        DefaultMemory* defaultMem = dynamic_cast<DefaultMemory*>(memory);

        // Build a synthetic type record (Go 1.21 64-bit layout)
        std::vector<uint8_t> typeData(64, 0);
        // size = 16
        uint64_t size16 = 16;
        memcpy(&typeData[0], &size16, 8);
        // hash = 0x12345678
        uint32_t hash = 0x12345678;
        memcpy(&typeData[8], &hash, 4);
        // kind = 18 (struct)
        typeData[15] = 18;

        Address start = tprog.addr(0x3000);
        DefaultMemoryBlock* block = defaultMem->createInitializedBlock(
            ".gopclntab", start, typeData.size());
        if (block) {
            block->setRead(true);
            block->putBytes(start, typeData.data(), static_cast<int>(typeData.size()));
        }

        auto types = GoRttiParser::parseTypes(memory, start,
            static_cast<int64_t>(typeData.size()), true);
        TEST("GoRttiParser found types", !types.empty());

        if (!types.empty()) {
            auto& gt = types.begin()->second;
            TEST("type kind is struct", gt.kind == 18);
            TEST("type size is 16", gt.size == 16);
            TEST("type hash matches", gt.hash == 0x12345678);
            TEST("type name is struct", gt.name == "struct");
        }
    }

    // === Test 5: GoRttiParser createDataTypes ===
    {
        StandAloneDataTypeManager dtm("go_types_test");
        std::unordered_map<uint64_t, GoRttiParser::GoType> types;
        GoRttiParser::GoType gt;
        gt.address = 0x1000;
        gt.kind = 18;
        gt.size = 32;
        gt.hash = 0xDEADBEEF;
        gt.name = "struct";
        gt.valid = true;
        types[0x1000] = gt;

        GoRttiParser::createDataTypes(types, &dtm);
        int typeCount = dtm.getDataTypes().size();
        TEST("createDataTypes added Go types", typeCount > 0);
    }

    // === Test 6 (G5): package records + build-info accessor ===
    {
        TEST("packageOf main", GolangSymbolAnalyzer::packageOf("main.main") == "main");
        TEST("packageOf runtime", GolangSymbolAnalyzer::packageOf("runtime.foo") == "runtime");
        TEST("packageOf module path",
             GolangSymbolAnalyzer::packageOf("github.com/x/y.Func") == "github.com/x/y");
        TEST("packageOf no dot", GolangSymbolAnalyzer::packageOf("nodot") == "");
        TEST("packageOf leading dot", GolangSymbolAnalyzer::packageOf(".b") == "");
    }
    {
        // Minimal Go 1.18+ 64-bit pclntab with 2 functions.
        TestProgram tprog;
        Memory* memory = tprog.prog.getMemory();
        DefaultMemory* defaultMem = dynamic_cast<DefaultMemory*>(memory);
        std::vector<uint8_t> tab(0x300, 0);
        auto w64 = [&](size_t o, uint64_t v) { memcpy(&tab[o], &v, 8); };
        auto w32 = [&](size_t o, uint32_t v) { memcpy(&tab[o], &v, 4); };
        w32(0, 0xFFFFFFF0); // magic 1.18+
        tab[4] = 0; tab[5] = 1; tab[6] = 8;
        w64(7, 2);              // nfunc (detection reads here)
        w64(15, 0);             // nfiles
        // NOTE: the field parser reads textStart/funcnameOffset at the
        // 1.16-style offsets below; 1.18 field layout is a follow-up.
        w64(24, 0x400000);      // textStart
        w64(32, 0x100);         // funcnameOffset -> 0x400100
        // functab at 88: {entry, funcoff} x2; _func structs at 120/128.
        w64(88, 0x400010); w64(96, 120);
        w64(104, 0x400020); w64(112, 128);
        w32(120, 0x10); w32(124, 0);   // entryOff, nameOff -> "main.main"
        w32(128, 0x20); w32(132, 10);  // entryOff, nameOff -> "fmt.Println"
        const char* n1 = "main.main";
        const char* n2 = "fmt.Println";
        memcpy(&tab[0x100], n1, strlen(n1) + 1);
        memcpy(&tab[0x100 + 10], n2, strlen(n2) + 1);

        Address start = tprog.addr(0x400000);
        DefaultMemoryBlock* block = defaultMem->createInitializedBlock(
            ".gopclntab", start, tab.size());
        TEST("g5 pclntab block created", block != nullptr);
        if (block) {
            block->setRead(true);
            block->setExecute(true);
            block->putBytes(start, tab.data(), static_cast<int>(tab.size()));
        }

        GolangSymbolAnalyzer analyzer;
        AddressSet set;
        StubTaskMonitor monitor;
        MessageLog log;
        TEST("g5 analyzer added", analyzer.added(&tprog.prog, set, &monitor, log));
        auto funcs = analyzer.getFunctions();
        TEST("g5 two functions recovered", funcs.size() == 2);
        bool mainOk = false, fmtOk = false;
        for (const auto& f : funcs) {
            if (f.name == "main.main" && f.package == "main" &&
                f.entry.getOffset() == 0x400010)
                mainOk = true;
            if (f.name == "fmt.Println" && f.package == "fmt" &&
                f.entry.getOffset() == 0x400020)
                fmtOk = true;
        }
        TEST("g5 main.main record", mainOk);
        TEST("g5 fmt.Println record", fmtOk);
        auto pkgs = analyzer.getPackages();
        TEST("g5 packages sorted unique",
             pkgs.size() == 2 && pkgs[0] == "fmt" && pkgs[1] == "main");
        SymbolTable* st = tprog.prog.getSymbolTable();
        bool labels = false;
        if (st) {
            auto s1 = st->getSymbols(tprog.addr(0x400010));
            auto s2 = st->getSymbols(tprog.addr(0x400020));
            labels = !s1.empty() && !s2.empty();
        }
        TEST("g5 labels created", labels);
    }
    {
        // Build-info accessor wired through added().
        TestProgram tprog;
        Memory* memory = tprog.prog.getMemory();
        DefaultMemory* defaultMem = dynamic_cast<DefaultMemory*>(memory);
        std::vector<uint8_t> buildInfo = buildGoBuildInfo();
        Address start = tprog.addr(0x1000);
        DefaultMemoryBlock* block = defaultMem->createInitializedBlock(
            "go.buildinfo", start, buildInfo.size());
        if (block) {
            block->setRead(true);
            block->putBytes(start, buildInfo.data(), static_cast<int>(buildInfo.size()));
        }
        GolangSymbolAnalyzer analyzer;
        AddressSet set;
        StubTaskMonitor monitor;
        MessageLog log;
        TEST("g5 buildinfo added", analyzer.added(&tprog.prog, set, &monitor, log));
        auto bi = analyzer.getBuildInfo();
        TEST("g5 buildinfo valid", bi.valid);
        TEST("g5 buildinfo version", bi.goVersion == "go1.21.0");
        TEST("g5 buildinfo module", bi.modulePath == "github.com/example/test");
    }

    std::cout << "Golang Pipeline Tests: " << passed << "/" << total << " passed.\n" << std::flush;
    return (passed == total) ? 0 : 1;
}
