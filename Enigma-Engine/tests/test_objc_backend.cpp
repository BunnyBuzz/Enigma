/**
 * Enigma Engine - Objective-C metadata backend tests.
 * Covers GUI backlog G6 (GP-6327): class/protocol/category records with
 * methods and ivars, plus per-class namespaces for the Symbol Tree.
 * Builds synthetic __objc_classlist/protolist/catlist blocks and drives
 * ObjcTypeMetadataAnalyzer::added().
 */
#include <iostream>
#include <string>
#include <vector>
#include <cstring>
#include <cstdint>

#include "ghidra/ObjcTypeMetadataAnalyzer.h"
#include "ghidra/ProgramDB.h"
#include "ghidra/AddressSpace.h"
#include "ghidra/ProgramAddressFactory.h"
#include "ghidra/Memory.h"
#include "ghidra/SymbolTable.h"
#include "ghidra/Symbol.h"
#include "ghidra/Namespace.h"
#include "ghidra/TaskMonitor.h"
#include "ghidra/MessageLog.h"
#include "ghidra/AddressSet.h"
#include "ghidra/Language.h"

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
    void w64(uint64_t off, uint64_t v) { memcpy(&bytes[(size_t)off], &v, 8); }
    void w32(uint64_t off, uint32_t v) { memcpy(&bytes[(size_t)off], &v, 4); }
    void str(uint64_t off, const char* s) { memcpy(&bytes[(size_t)off], s, strlen(s) + 1); }
};

static bool hasNameAt(SymbolTable* st, const Address& a, const std::string& name) {
    auto syms = st->getSymbols(a);
    for (auto* s : syms) {
        if (s && s->getName() == name) return true;
    }
    return false;
}

static bool nsHasSymbol(SymbolTable* st, Namespace* ns, const std::string& name) {
    if (!ns) return false;
    auto syms = st->getSymbols(ns);
    for (auto* s : syms) {
        if (s && s->getName() == name) return true;
    }
    return false;
}

int main() {
    TestProgram tprog("objc_backend_test");
    Memory* memory = tprog.prog.getMemory();
    DefaultMemory* defaultMem = dynamic_cast<DefaultMemory*>(memory);
    TEST("objc memory is DefaultMemory", defaultMem != nullptr);
    if (!defaultMem) {
        std::cout << "ObjC Backend Tests: " << passed << "/" << total << " passed.\n";
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

    // Executable block hosting the method IMP.
    {
        MemImage text(0x100);
        DefaultMemoryBlock* tb = makeBlock(".text", 0x400000, text);
        TEST("objc text block", tb != nullptr);
        if (tb) tb->setExecute(true);
    }

    // __objc_classlist block holds only the class pointer (like real
    // binaries); metadata lives in a separate __objc_data block so stray
    // nonzero words cannot be mistaken for classes.
    {
        MemImage img(0x1000);
        img.w64(0x0000, 0x501000);          // classlist[0]
        TEST("objc classlist block", makeBlock("__objc_classlist", 0x500000, img) != nullptr);
    }
    {
        MemImage img(0x7000);
        img.w64(0x0000 + 32, 0x502000);     // class_t.data (ro)
        img.w32(0x1000 + 4, 8);             // ro.instanceStart
        img.w32(0x1000 + 8, 16);            // ro.instanceSize
        img.w64(0x1000 + 24, 0x503000);     // ro.name
        img.w64(0x1000 + 32, 0x504000);     // ro.baseMethods
        img.w64(0x1000 + 48, 0x505000);     // ro.ivars
        img.str(0x2000, "MyClass");
        img.w32(0x3000, 24); img.w32(0x3000 + 4, 1);       // method list header
        img.w64(0x3000 + 8, 0x506000);                     // method.name (SEL)
        img.w64(0x3000 + 16, 0x506010);                    // method.types
        img.w64(0x3000 + 24, 0x400010);                    // method.imp
        img.str(0x5000, "doThing:");
        img.str(0x5010, "v@:");
        img.w32(0x4000, 32); img.w32(0x4000 + 4, 1);       // ivar list header
        img.w64(0x4000 + 8, 0x507000);                     // ivar.offset ptr
        img.w64(0x4000 + 16, 0x507010);                    // ivar.name
        img.w64(0x4000 + 24, 0x507018);                    // ivar.type
        img.w32(0x4000 + 32, 2);                           // ivar.alignment
        img.w32(0x4000 + 36, 4);                           // ivar.size
        img.w32(0x6000, 8);                                // ivar offset value
        img.str(0x6010, "myIvar");
        img.str(0x6018, "i");
        TEST("objc data block", makeBlock("__objc_data", 0x501000, img) != nullptr);
    }

    // __objc_protolist block (@0x510000, size 0x3000 covers data to 0x512000).
    {
        MemImage img(0x3000);
        img.w64(0x0000, 0x511000);          // protolist[0]
        img.w64(0x1000 + 16, 0x512000);     // protocol_t.mangledName
        img.str(0x2000, "MyProtocol");
        TEST("objc protolist block", makeBlock("__objc_protolist", 0x510000, img) != nullptr);
    }

    // __objc_catlist block referencing the class above.
    {
        MemImage img(0x3000);
        img.w64(0x0000, 0x521000);          // catlist[0]
        img.w64(0x1000, 0x522000);          // category_t.name
        img.w64(0x1008, 0x501000);          // category_t.cls (classref)
        img.str(0x2000, "MyCategory");
        TEST("objc catlist block", makeBlock("__objc_catlist", 0x520000, img) != nullptr);
    }

    ObjcTypeMetadataAnalyzer analyzer;
    AddressSet set;
    StubTaskMonitor monitor;
    MessageLog log;
    TEST("objc added", analyzer.added(&tprog.prog, set, &monitor, log));

    auto classes = analyzer.getClasses();
    TEST("objc one class", classes.size() == 1);
    if (!classes.empty()) {
        const auto& c = classes[0];
        TEST("objc class name", c.name == "MyClass");
        TEST("objc class addrs",
             c.clsAddr.getOffset() == 0x501000 && c.roAddr.getOffset() == 0x502000);
        TEST("objc one method", c.methods.size() == 1);
        if (!c.methods.empty()) {
            TEST("objc method sel", c.methods[0].sel == "doThing:");
            TEST("objc method types", c.methods[0].types == "v@:");
            TEST("objc method impl", c.methods[0].impl.getOffset() == 0x400010);
        }
        TEST("objc one ivar", c.ivars.size() == 1);
        if (!c.ivars.empty()) {
            TEST("objc ivar name", c.ivars[0].name == "myIvar");
            TEST("objc ivar offset", c.ivars[0].offset == 8);
            TEST("objc ivar type", c.ivars[0].type == "i");
            TEST("objc ivar size", c.ivars[0].size == 4);
        }
    }

    auto protos = analyzer.getProtocols();
    TEST("objc one protocol",
         protos.size() == 1 && protos[0].name == "MyProtocol" &&
         protos[0].addr.getOffset() == 0x511000);

    auto cats = analyzer.getCategories();
    TEST("objc one category",
         cats.size() == 1 && cats[0].name == "MyCategory" &&
         cats[0].className == "MyClass" && cats[0].addr.getOffset() == 0x521000);

    SymbolTable* st = tprog.prog.getSymbolTable();
    TEST("objc class label",
         hasNameAt(st, tprog.addr(0x501000), "OBJC_CLASS_$_MyClass"));
    TEST("objc protocol label",
         hasNameAt(st, tprog.addr(0x511000), "OBJC_PROTOCOL_$_MyProtocol"));
    TEST("objc category label",
         hasNameAt(st, tprog.addr(0x521000), "OBJC_CATEGORY_$_MyClass(MyCategory)"));
    Namespace* global = st->getGlobalNamespace();
    Namespace* classNs = st->getNamespace("MyClass", global);
    TEST("objc class namespace", classNs != nullptr);
    TEST("objc method in namespace",
         nsHasSymbol(st, classNs, "doThing:"));
    TEST("objc protocol namespace", st->getNamespace("MyProtocol", global) != nullptr);
    TEST("objc category namespace",
         st->getNamespace("MyClass_MyCategory", global) != nullptr);

    std::cout << "\n=== Summary ===" << std::endl;
    std::cout << "ObjC Backend Tests: " << passed << "/" << total << " passed." << std::endl;
    return (passed == total) ? 0 : 1;
}
