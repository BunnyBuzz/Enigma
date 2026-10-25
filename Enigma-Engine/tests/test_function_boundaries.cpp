/**
 * Enigma Engine - Function Entry Boundary Trimming Test
 * Validates Task 1.4: FunctionStartAnalyzer must not leave function entries
 * anchored on NOP/INT3 alignment padding. Covers:
 *   - MOVE: entry on padding with real code after -> trimmed forward, name kept
 *   - DROP (owned): entry on padding whose real start is another function
 *   - DROP (block end): entry on padding run extending to the block boundary
 *   - UNTOUCHED: real entry preceded by padding is never moved
 */
#include <iostream>
#include <string>
#include <vector>
#include <cstdint>
#include <memory>

#include "ghidra/FunctionStartAnalyzer.h"
#include "ghidra/ProgramDB.h"
#include "ghidra/AddressSpace.h"
#include "ghidra/ProgramAddressFactory.h"
#include "ghidra/Memory.h"
#include "ghidra/TaskMonitor.h"
#include "ghidra/MessageLog.h"
#include "ghidra/Language.h"
#include "ghidra/FunctionManager.h"
#include "ghidra/Function.h"
#include "ghidra/FunctionBodyFinalizer.h"
#include "ghidra/FragmentMergeAnalyzer.h"
#include "ghidra/ReferenceManager.h"
#include "ghidra/RefType.h"
#include "ghidra/AddressSet.h"
#include "ghidra/AutoNaming.h"
#include "ghidra/Listing.h"
#include "ghidra/Instruction.h"

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
          prog("function_boundaries_test", nullptr, nullptr) {
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

static std::vector<uint8_t> buildBlock() {
    std::vector<uint8_t> b(0xC0, 0xCC);
    // 0x1000: call rel32 -> 0x1058 (Case A: padding + real non-pattern code)
    b[0x000] = 0xE8; b[0x001] = 0x53; b[0x002] = 0x00; b[0x003] = 0x00; b[0x004] = 0x00;
    // 0x1005: call rel32 -> 0x10A0 (Case B: padding run to block end)
    b[0x005] = 0xE8; b[0x006] = 0x96; b[0x007] = 0x00; b[0x008] = 0x00; b[0x009] = 0x00;
    // 0x100A: call rel32 -> 0x1030 (Case C: padding + pattern prologue)
    b[0x00A] = 0xE8; b[0x00B] = 0x21; b[0x00C] = 0x00; b[0x00D] = 0x00; b[0x00E] = 0x00;
    // 0x1030: 90 90 90 55 48 89 E5 C3   (padding then push rbp; mov rbp,rsp; ret)
    b[0x030] = 0x90; b[0x031] = 0x90; b[0x032] = 0x90;
    b[0x033] = 0x55; b[0x034] = 0x48; b[0x035] = 0x89; b[0x036] = 0xE5; b[0x037] = 0xC3;
    // 0x1058: 90 90 4C 89 44 24 08 C3   (padding then mov [rsp+8],r8; ret)
    b[0x058] = 0x90; b[0x059] = 0x90;
    b[0x05A] = 0x4C; b[0x05B] = 0x89; b[0x05C] = 0x44; b[0x05D] = 0x24; b[0x05E] = 0x08; b[0x05F] = 0xC3;
    // 0x1090: 90 31 C0 C3               (padding then xor eax,eax; ret - real entry)
    b[0x090] = 0x90;
    b[0x091] = 0x31; b[0x092] = 0xC0; b[0x093] = 0xC3;
    // 0x10A0..0x10BF: NOP padding run to block end (Case B region)
    for (int i = 0xA0; i < 0xC0; ++i) b[i] = 0x90;
    return b;
}

static Function* findFunc(FunctionManager* fm, uint64_t off) {
    AddressSet all;
    FunctionIterator it = fm->getFunctions(true);
    while (it.hasNext()) {
        Function* f = it.next();
        if (f && f->getEntryPoint().getOffset() == static_cast<int64_t>(off)) return f;
    }
    return nullptr;
}

int main() {
    TestProgram tprog;
    Address startAddr = tprog.addr(0x1000);
    Memory* memory = tprog.prog.getMemory();
    std::vector<uint8_t> data = buildBlock();
    DefaultMemory* defaultMem = dynamic_cast<DefaultMemory*>(memory);
    TEST("memory is DefaultMemory", defaultMem != nullptr);
    DefaultMemoryBlock* block = defaultMem ? defaultMem->createInitializedBlock(".text", startAddr, data.size()) : nullptr;
    TEST("block created", block != nullptr);
    if (!block) {
        std::cout << "Function Boundary Tests: " << passed << "/" << total << " passed.\n";
        return 1;
    }
    block->setExecute(true);
    int written = block->putBytes(startAddr, data.data(), static_cast<int>(data.size()));
    TEST("block bytes written", written == static_cast<int>(data.size()));

    FunctionStartAnalyzer analyzer;
    TEST("canAnalyze", analyzer.canAnalyze(&tprog.prog));

    AddressSet set;
    StubTaskMonitor monitor;
    MessageLog log;
    bool ok = false;
    try {
        ok = analyzer.added(&tprog.prog, set, &monitor, log);
    } catch (const std::exception& e) {
        std::cerr << "added() threw: " << e.what() << "\n";
    }
    TEST("FunctionStartAnalyzer::added completes", ok);

    FunctionManager* fm = tprog.prog.getFunctionManager();

    // Case C: phantom at 0x1030 dropped (real entry 0x1033 already owned by func_0x1033)
    TEST("C: no function at 0x1030", fm->getFunctionAt(tprog.addr(0x1030)) == nullptr);
    Function* f1033 = findFunc(fm, 0x1033);
    TEST("C: function at 0x1033 kept", f1033 != nullptr);
    if (f1033) TEST("C: func_0x1033 name", f1033->getName() == "func_0x1033");

    // Case A: phantom at 0x1058 moved to 0x105A with name preserved
    TEST("A: no function at 0x1058", fm->getFunctionAt(tprog.addr(0x1058)) == nullptr);
    Function* f105a = findFunc(fm, 0x105A);
    TEST("A: function moved to 0x105A", f105a != nullptr);
    if (f105a) TEST("A: name preserved func_0x1058", f105a->getName() == "func_0x1058");

    // Case B: phantom at 0x10A0 dropped (padding to block end)
    TEST("B: no function at 0x10A0", fm->getFunctionAt(tprog.addr(0x10A0)) == nullptr);

    // Untouched: real entry at 0x1091 (xor eax,eax; ret) preceded by padding
    Function* f1091 = findFunc(fm, 0x1091);
    TEST("untouched: function at 0x1091 kept", f1091 != nullptr);
    if (f1091) TEST("untouched: func_0x1091 name", f1091->getName() == "func_0x1091");

    // Exactly three functions remain
    int count = 0;
    FunctionIterator it = fm->getFunctions(true);
    while (it.hasNext()) { it.next(); ++count; }
    TEST("total function count is 3", count == 3);

    // --- FunctionBodyFinalizer: conditional-branch target cleanup ---
    // A synthetic entry targeted only by an intra-function conditional branch
    // is an interior block (Ghidra keeps it inside the source body). Call
    // targets and cross-function jump (tail-call) targets must survive.
    TestProgram t2;
    FunctionManager* fm2 = t2.prog.getFunctionManager();
    ReferenceManager* rm2 = t2.prog.getReferenceManager();
    TEST("finalizer: reference manager", rm2 != nullptr);
    if (fm2 && rm2) {
        auto makeFunc = [&](uint64_t off) {
            AddressSet b(t2.addr(off), t2.addr(off));
            fm2->createFunction("func_0x" + std::to_string(off), t2.addr(off),
                                b, SourceType::ANALYSIS);
        };
        makeFunc(0x2000); // source function
        makeFunc(0x200a); // only a conditional-branch target -> removed
        makeFunc(0x2200); // conditional target plus a direct call -> kept
        makeFunc(0x2400); // conditional target plus a cross-function jump -> kept

        rm2->addMemoryReference(t2.addr(0x2006), t2.addr(0x200a),
                                &RefTypes::CONDITIONAL_JUMP,
                                SourceType::ANALYSIS, 0);
        rm2->addMemoryReference(t2.addr(0x2100), t2.addr(0x2200),
                                &RefTypes::UNCONDITIONAL_CALL,
                                SourceType::ANALYSIS, 0);
        rm2->addMemoryReference(t2.addr(0x2106), t2.addr(0x2200),
                                &RefTypes::CONDITIONAL_JUMP,
                                SourceType::ANALYSIS, 0);
        rm2->addMemoryReference(t2.addr(0x2300), t2.addr(0x2400),
                                &RefTypes::UNCONDITIONAL_JUMP,
                                SourceType::ANALYSIS, 0);
        rm2->addMemoryReference(t2.addr(0x2306), t2.addr(0x2400),
                                &RefTypes::CONDITIONAL_JUMP,
                                SourceType::ANALYSIS, 0);

        FunctionBodyFinalizer finalizer;
        AddressSet emptySet;
        MessageLog finalLog;
        bool finalOk = false;
        try {
            finalOk = finalizer.added(&t2.prog, emptySet, &monitor, finalLog);
        } catch (const std::exception& e) {
            std::cerr << "FunctionBodyFinalizer::added threw: " << e.what() << "\n";
        }
        TEST("finalizer: added completes", finalOk);
        TEST("finalizer: conditional-only target removed",
             fm2->getFunctionAt(t2.addr(0x200a)) == nullptr);
        TEST("finalizer: source function kept",
             fm2->getFunctionAt(t2.addr(0x2000)) != nullptr);
        TEST("finalizer: direct call target kept",
             fm2->getFunctionAt(t2.addr(0x2200)) != nullptr);
        TEST("finalizer: cross-function jump target kept",
             fm2->getFunctionAt(t2.addr(0x2400)) != nullptr);
    }

    // --- FragmentMergeAnalyzer: adjacent entry arbitration ---
    // Ghidra treats a tiny epilogue fragment immediately followed by a real
    // entry as the tail of the preceding function, but keeps adjacent call
    // targets and jump thunks as distinct functions.
    TestProgram t3;
    FunctionManager* fm3 = t3.prog.getFunctionManager();
    ReferenceManager* rm3 = t3.prog.getReferenceManager();
    DefaultMemory* mem3 = dynamic_cast<DefaultMemory*>(t3.prog.getMemory());
    TEST("fragment merge: function manager", fm3 != nullptr);
    if (fm3 && rm3 && mem3) {
        std::vector<uint8_t> mb(0x100, 0xCC);
        // 0x3000: xor eax,eax; ret (stray epilogue, jump target only)
        mb[0x00] = 0x31; mb[0x01] = 0xC0; mb[0x02] = 0xC3;
        // 0x3003: push r15; push r14; push r13; mov r13,rdi; ...
        mb[0x03] = 0x41; mb[0x04] = 0x57; mb[0x05] = 0x41; mb[0x06] = 0x56;
        mb[0x07] = 0x41; mb[0x08] = 0x55; mb[0x09] = 0x49; mb[0x0A] = 0x89;
        mb[0x0B] = 0xFD; mb[0x0C] = 0x41; mb[0x0D] = 0x54; mb[0x0E] = 0x55;
        mb[0x0F] = 0x53; mb[0x10] = 0xC3;
        // 0x3020: ret (direct-call target); 0x3021: real prologue
        mb[0x20] = 0xC3;
        mb[0x21] = 0x41; mb[0x22] = 0x56; mb[0x23] = 0x41; mb[0x24] = 0x55;
        mb[0x25] = 0x41; mb[0x26] = 0x54; mb[0x27] = 0x55; mb[0x28] = 0x53;
        mb[0x29] = 0xC3;
        // 0x3040: mov rax,rdi; ret (tiny real function)
        mb[0x40] = 0x48; mb[0x41] = 0x89; mb[0x42] = 0xF8; mb[0x43] = 0xC3;
        // 0x3044: jmp 0x3040 (tail-call thunk)
        mb[0x44] = 0xE9; mb[0x45] = 0xF7; mb[0x46] = 0xFF; mb[0x47] = 0xFF;
        mb[0x48] = 0xFF;
        // 0x3060: push rbp; mov rbp,rsp; sub rsp,0x20; ret (real frame)
        mb[0x60] = 0x55; mb[0x61] = 0x48; mb[0x62] = 0x89; mb[0x63] = 0xE5;
        mb[0x64] = 0x48; mb[0x65] = 0x83; mb[0x66] = 0xEC; mb[0x67] = 0x20;
        mb[0x68] = 0xC3;
        // 0x3080: ret (end of previous function)
        // 0x3081: xor eax,eax; ret (no incoming flow refs, abuts RET)
        mb[0x80] = 0xC3;
        mb[0x81] = 0x31; mb[0x82] = 0xC0; mb[0x83] = 0xC3;
        // 0x3084: push r14; push r13; push r12; push rbp; push rbx; ret
        mb[0x84] = 0x41; mb[0x85] = 0x56; mb[0x86] = 0x41; mb[0x87] = 0x55;
        mb[0x88] = 0x41; mb[0x89] = 0x54; mb[0x8A] = 0x55; mb[0x8B] = 0x53;
        mb[0x8C] = 0xC3;
        // 0x30A0: xor eax,eax; ret (branch target inside preceding function)
        mb[0xA0] = 0x31; mb[0xA1] = 0xC0; mb[0xA2] = 0xC3;
        // 0x30A3: push r14; push r13; push r12; push rbp; push rbx; ret
        mb[0xA3] = 0x41; mb[0xA4] = 0x56; mb[0xA5] = 0x41; mb[0xA6] = 0x55;
        mb[0xA7] = 0x41; mb[0xA8] = 0x54; mb[0xA9] = 0x55; mb[0xAA] = 0x53;
        mb[0xAB] = 0xC3;
        // 0x30C0: xor eax,eax; ret (padding-separated fragment)
        mb[0xC0] = 0x31; mb[0xC1] = 0xC0; mb[0xC2] = 0xC3;
        // 0x30C3: push r14; push r13; push r12; push rbp; push rbx; ret
        mb[0xC3] = 0x41; mb[0xC4] = 0x56; mb[0xC5] = 0x41; mb[0xC6] = 0x55;
        mb[0xC7] = 0x41; mb[0xC8] = 0x54; mb[0xC9] = 0x55; mb[0xCA] = 0x53;
        mb[0xCB] = 0xC3;

        Address mstart = t3.addr(0x3000);
        DefaultMemoryBlock* mblock =
            mem3->createInitializedBlock(".text", mstart, mb.size());
        TEST("fragment merge: block created", mblock != nullptr);
        if (mblock) {
            mblock->setExecute(true);
            mblock->putBytes(mstart, mb.data(), static_cast<int>(mb.size()));

            auto makeFunc = [&](uint64_t off) {
                AddressSet b(t3.addr(off), t3.addr(off));
                fm3->createFunction("func_0x" + std::to_string(off), t3.addr(off),
                                    b, SourceType::ANALYSIS);
            };
            for (uint64_t off : {0x3000ULL, 0x3003ULL, 0x3020ULL, 0x3021ULL,
                                 0x3040ULL, 0x3044ULL, 0x3060ULL, 0x3063ULL,
                                 0x3070ULL, 0x3081ULL, 0x3084ULL, 0x30A0ULL,
                                 0x30A3ULL, 0x30C0ULL, 0x30C3ULL}) {
                makeFunc(off);
            }

            // Terminator instruction at 0x3080 so the epilogue stub at 0x3081
            // is seen as directly abutting the previous function's RET.
            Listing* listing3 = t3.prog.getListing();
            std::vector<std::unique_ptr<Instruction>> ownedInsts;
            auto addInst = [&](uint64_t off, const char* mnemonic, int len) {
                auto inst = std::make_unique<Instruction>(&t3.prog, t3.addr(off),
                                                          mnemonic, len);
                listing3->addInstruction(inst.get());
                ownedInsts.push_back(std::move(inst));
            };
            addInst(0x3080, "ret", 1);
            addInst(0x3081, "xor", 2);
            addInst(0x3083, "ret", 1);
            addInst(0x30A0, "xor", 2);
            addInst(0x30A2, "ret", 1);
            addInst(0x30C0, "xor", 2);
            addInst(0x30C2, "ret", 1);

            rm3->addMemoryReference(t3.addr(0x3100), t3.addr(0x3000),
                                    &RefTypes::UNCONDITIONAL_JUMP,
                                    SourceType::ANALYSIS, 0);
            rm3->addMemoryReference(t3.addr(0x3110), t3.addr(0x3020),
                                    &RefTypes::UNCONDITIONAL_CALL,
                                    SourceType::ANALYSIS, 0);
            rm3->addMemoryReference(t3.addr(0x3115), t3.addr(0x3021),
                                    &RefTypes::UNCONDITIONAL_CALL,
                                    SourceType::ANALYSIS, 0);
            rm3->addMemoryReference(t3.addr(0x3120), t3.addr(0x3040),
                                    &RefTypes::UNCONDITIONAL_JUMP,
                                    SourceType::ANALYSIS, 0);
            // 0x3081 has no incoming flow ref; 0x3084 is a call target.
            rm3->addMemoryReference(t3.addr(0x3130), t3.addr(0x3084),
                                    &RefTypes::UNCONDITIONAL_CALL,
                                    SourceType::ANALYSIS, 0);
            // 0x30A0 is a branch target inside the preceding function.
            rm3->addMemoryReference(t3.addr(0x3090), t3.addr(0x30A0),
                                    &RefTypes::UNCONDITIONAL_JUMP,
                                    SourceType::ANALYSIS, 0);
            rm3->addMemoryReference(t3.addr(0x3150), t3.addr(0x30C3),
                                    &RefTypes::UNCONDITIONAL_CALL,
                                    SourceType::ANALYSIS, 0);

            FragmentMergeAnalyzer merger;
            AddressSet emptySet3;
            MessageLog mergeLog;
            bool mergeOk = false;
            try {
                mergeOk = merger.added(&t3.prog, emptySet3, &monitor, mergeLog);
            } catch (const std::exception& e) {
                std::cerr << "FragmentMergeAnalyzer::added threw: " << e.what() << "\n";
            }
            TEST("fragment merge: added completes", mergeOk);
            TEST("fragment merge: epilogue stub before prologue removed",
                 fm3->getFunctionAt(t3.addr(0x3000)) == nullptr);
            TEST("fragment merge: real prologue after stub kept",
                 fm3->getFunctionAt(t3.addr(0x3003)) != nullptr);
            TEST("fragment merge: call-target stub kept",
                 fm3->getFunctionAt(t3.addr(0x3020)) != nullptr);
            TEST("fragment merge: adjacent call-target prologue kept",
                 fm3->getFunctionAt(t3.addr(0x3021)) != nullptr);
            TEST("fragment merge: tiny real function kept",
                 fm3->getFunctionAt(t3.addr(0x3040)) != nullptr);
            TEST("fragment merge: jump thunk kept",
                 fm3->getFunctionAt(t3.addr(0x3044)) != nullptr);
            TEST("fragment merge: real frame function kept",
                 fm3->getFunctionAt(t3.addr(0x3060)) != nullptr);
            TEST("fragment merge: interior fragment removed",
                 fm3->getFunctionAt(t3.addr(0x3063)) == nullptr);
            TEST("fragment merge: unreferenced stub abutting RET removed",
                 fm3->getFunctionAt(t3.addr(0x3081)) == nullptr);
            TEST("fragment merge: entry after abutting stub kept",
                 fm3->getFunctionAt(t3.addr(0x3084)) != nullptr);
            TEST("fragment merge: branch-target stub removed",
                 fm3->getFunctionAt(t3.addr(0x30A0)) == nullptr);
            TEST("fragment merge: entry after branch-target stub kept",
                 fm3->getFunctionAt(t3.addr(0x30A3)) != nullptr);
            TEST("fragment merge: padding-separated stub removed",
                 fm3->getFunctionAt(t3.addr(0x30C0)) == nullptr);
            TEST("fragment merge: entry after padding-separated stub kept",
                 fm3->getFunctionAt(t3.addr(0x30C3)) != nullptr);
        }
    }

    std::cout << "Function Boundary Tests: " << passed << "/" << total << " passed.\n" << std::flush;
    return (passed == total) ? 0 : 1;
}