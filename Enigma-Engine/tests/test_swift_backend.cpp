/**
 * Enigma Engine - Swift metadata backend tests.
 * Covers GUI backlog G7 (GP-6281/GP-6137): Swift types registered in the
 * DataTypeManager (/swift structures with fields) and swiftcall convention
 * tags on demangled Swift functions.
 */
#include <iostream>
#include <string>
#include <vector>
#include <cstring>
#include <cstdint>

#include "ghidra/SwiftTypeMetadataAnalyzer.h"
#include "ghidra/SwiftDemanglerAnalyzer.h"
#include "ghidra/ProgramDB.h"
#include "ghidra/AddressSpace.h"
#include "ghidra/ProgramAddressFactory.h"
#include "ghidra/Memory.h"
#include "ghidra/SymbolTable.h"
#include "ghidra/Symbol.h"
#include "ghidra/FunctionManager.h"
#include "ghidra/Function.h"
#include "ghidra/FunctionTag.h"
#include "ghidra/PrototypeModel.h"
#include "ghidra/DataTypeManager.h"
#include "ghidra/CategoryPath.h"
#include "ghidra/StructureDataType.h"
#include "ghidra/TaskMonitor.h"
#include "ghidra/MessageLog.h"
#include "ghidra/AddressSet.h"
#include "ghidra/Language.h"
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

struct MemImage {
    std::vector<uint8_t> bytes;
    MemImage(size_t n) : bytes(n, 0) {}
    void w32(uint64_t off, uint32_t v) { memcpy(&bytes[(size_t)off], &v, 4); }
    void w64(uint64_t off, uint64_t v) { memcpy(&bytes[(size_t)off], &v, 8); }
    void str(uint64_t off, const char* s) { memcpy(&bytes[(size_t)off], s, strlen(s) + 1); }
};

static bool hasNameAt(SymbolTable* st, const Address& a, const std::string& name) {
    auto syms = st->getSymbols(a);
    for (auto* s : syms) {
        if (s && s->getName() == name) return true;
    }
    return false;
}

int main() {
    std::cout << "\n--- G7: Swift types in DataTypeManager ---" << std::endl;
    {
        TestProgram tprog("swift_types_test");
        Memory* memory = tprog.prog.getMemory();
        DefaultMemory* defaultMem = dynamic_cast<DefaultMemory*>(memory);
        TEST("swift memory is DefaultMemory", defaultMem != nullptr);
        if (!defaultMem) {
            std::cout << "Swift Backend Tests: " << passed << "/" << total << " passed.\n";
            return 1;
        }
        auto makeBlock = [&](const std::string& name, uint64_t base, MemImage& img) {
            DefaultMemoryBlock* b = defaultMem->createInitializedBlock(
                name, tprog.addr(base), img.bytes.size());
            if (b) {
                b->setRead(true);
                b->putBytes(tprog.addr(base), img.bytes.data(), (int)img.bytes.size());
            }
            return b;
        };

        // __swift5_types: one relative ref to a struct descriptor.
        {
            MemImage img(0x3000);
            img.w32(0x0000, 0x1000);                 // rel -> desc @0x601000
            img.w32(0x1000, 5);                     // flags: struct
            img.w32(0x1000 + 8, 0x602000 - 0x601008); // name rel -> "$s4test8MyStructV"
            img.str(0x2000, "$s4test8MyStructV");
            TEST("swift types block", makeBlock("__swift5_types", 0x600000, img) != nullptr);
        }
        // __swift5_fieldmd: one field descriptor with two fields.
        {
            MemImage img(0x3000);
            img.w32(0x0000, 0x1000);                    // rel -> fielddesc @0x611000
            img.w32(0x1000, 0);                         // record kind: struct
            img.w32(0x1000 + 4, 0x612000 - 0x611004);    // type name rel
            img.w32(0x1000 + 12, 2);                     // numFields
            img.w32(0x1010, 0x612020 - 0x611010);        // field0 name rel -> "x"
            img.w32(0x1010 + 4, 0x612030 - 0x611014);    // field0 type rel -> "$sSi"
            img.w32(0x1020, 0x612022 - 0x611020);        // field1 name rel -> "y"
            img.w32(0x1020 + 4, 0x612038 - 0x611024);    // field1 type rel -> "$sSb"
            img.str(0x2000, "$s4test8MyStructV");
            img.str(0x2020, "x");
            img.str(0x2022, "y");
            img.str(0x2030, "$sSi");
            img.str(0x2038, "$sSb");
            TEST("swift fieldmd block", makeBlock("__swift5_fieldmd", 0x610000, img) != nullptr);
        }

        SwiftTypeMetadataAnalyzer analyzer;
        TEST("swift canAnalyze", analyzer.canAnalyze(&tprog.prog));
        AddressSet set;
        StubTaskMonitor monitor;
        MessageLog log;
        TEST("swift added", analyzer.added(&tprog.prog, set, &monitor, log));

        auto types = analyzer.getTypes();
        TEST("swift one type", types.size() == 1);
        if (!types.empty()) {
            TEST("swift type name", types[0].name == "test.MyStruct");
            TEST("swift type kind struct", types[0].kind == 5);
            TEST("swift two fields", types[0].fields.size() == 2);
            bool fx = false, fy = false;
            for (const auto& f : types[0].fields) {
                if (f.name == "x" && f.typeName == "$sSi") fx = true;
                if (f.name == "y" && f.typeName == "$sSb") fy = true;
            }
            TEST("swift field x", fx);
            TEST("swift field y", fy);
        }

        DataTypeManager* dtm = tprog.prog.getDataTypeManager();
        TEST("swift dtm present", dtm != nullptr);
        DataType* dt = dtm ? dtm->getDataType(CategoryPath("/swift"), "test.MyStruct") : nullptr;
        TEST("swift struct registered", dt != nullptr);
        StructureDataType* st = dynamic_cast<StructureDataType*>(dt);
        TEST("swift struct is structure", st != nullptr);
        if (st) {
            TEST("swift struct two components", st->getNumComponents() == 2);
            bool cx = false, cy = false;
            for (int i = 0; i < st->getNumComponents(); ++i) {
                DataTypeComponent* c = st->getComponent(i);
                if (!c) continue;
                if (c->getFieldName() == "x" && c->getDataType() &&
                    c->getDataType()->getName() == "qword")
                    cx = true;
                if (c->getFieldName() == "y" && c->getDataType() &&
                    c->getDataType()->getName() == "bool")
                    cy = true;
            }
            TEST("swift component x:qword", cx);
            TEST("swift component y:bool", cy);
        }
        SymbolTable* syms = tprog.prog.getSymbolTable();
        TEST("swift type label",
             hasNameAt(syms, tprog.addr(0x601000), "swift_test_MyStruct"));
    }

    std::cout << "\n--- G7: swiftcall convention tags ---" << std::endl;
    {
        TestProgram tprog("swiftcall_test");
        SymbolTable* syms = tprog.prog.getSymbolTable();
        syms->createLabel(tprog.addr(0x400010), "_$s4test6myFunc", SourceType::IMPORTED);
        FunctionManager* fm = tprog.prog.getFunctionManager();
        AddressSet body;
        body.add(tprog.addr(0x400010), tprog.addr(0x400020));
        Function* func = fm ? fm->createFunction("myFunc", tprog.addr(0x400010), body,
                                                 SourceType::ANALYSIS) : nullptr;
        TEST("swiftcall function created", func != nullptr);

        SwiftDemanglerAnalyzer analyzer;
        AddressSet set;
        StubTaskMonitor monitor;
        MessageLog log;
        TEST("swift demangle added", analyzer.added(&tprog.prog, set, &monitor, log));
        TEST("swift demangled alias",
             hasNameAt(syms, tprog.addr(0x400010), "test.myFunc"));
        PrototypeModel* cc = fm ? fm->getCallingConvention("swiftcall") : nullptr;
        TEST("swiftcall convention registered", cc != nullptr);
        bool ccSet = func && func->getCallingConvention() &&
                     func->getCallingConvention()->getName() == "swiftcall";
        TEST("swiftcall set on function", ccSet);
        bool tagged = false;
        if (func) {
            for (auto* t : func->getTags()) {
                if (t && t->getName() == "swiftcall") { tagged = true; break; }
            }
        }
        TEST("swiftcall tag present", tagged);
    }

    std::cout << "\n=== Summary ===" << std::endl;
    std::cout << "Swift Backend Tests: " << passed << "/" << total << " passed." << std::endl;
    return (passed == total) ? 0 : 1;
}
