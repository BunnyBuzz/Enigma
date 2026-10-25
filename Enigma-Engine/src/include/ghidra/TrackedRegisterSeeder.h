#pragma once

#include <cstdint>
#include <functional>

namespace ghidra {
class Program;
}

namespace ghidra_decompiler {
class Architecture;
}

namespace ghidra {

/// Seeds ABI-mandated register values that Ghidra's address analyzers write
/// into ProgramContext, so the decompiler can resolve PIC call targets.
/// MIPS: $t9 = current function entry. PowerPC: r30 (32-bit) or r2 (64-bit)
/// = GOT/SDA base (small data area + 0x8000).
class TrackedRegisterSeeder {
public:
    /// mapAddress converts Program addresses into the decompiler's address
    /// space. Use identity for the standard ProgramDB/decompiler mapping.
    static void seed(Program* program, ghidra_decompiler::Architecture* arch,
                     const std::function<uint64_t(uint64_t)>& mapAddress);
};

} // namespace ghidra
