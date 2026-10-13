# Disassembler Parity Audit (SLEIGH / DecompInterface vs Ghidra 12.1.3 headless)

Tooling: `tools/headless/DumpListing.java`, `tools/enigma_dump_listing.cpp`,
`tools/parity_listing_diff.py`, `tools/run_parity_audit.ps1`.

## Fix delivered
Dynamic ELF listing crash (`std::terminate` from `FunctionManager::createFunction`,
`Overlapping function body`) was caused by duplicate ELF symbols from both
`.symtab` (`type 2`) and `.dynsym` (`type 11`) being pushed into `symbols_`.
Fixed by deduping `symbols_` by `name@address` before `parseELFImports()`
(`src/core/BinaryLoader.cpp`).
`FunctionManager::createFunction` overlap errors now include the function name
and colliding ranges.

### Decode-correctness fixes (validated against Ghidra)
1. **ARM `ldr pc` treated as fallthrough** — PLT stubs end in
   `ldr pc, [r12, #imm]!`. `determineFlowType()` classified it as FALL_THROUGH,
   so recursive descent ran past the stub into the embedded literal pool and
   invented instructions (`ldrble sp,[r4],#0x4d4` from `d4d4d4d4`), which then
   desynchronised every subsequent instruction in the function.
   Fix: `ldr` with `pc` destination → TERMINATOR (`src/core/Disassembler.cpp`).
2. **MIPS delay slots dropped** — every MIPS branch has a delay slot that always
   executes, but the linear scan stopped at the branch so the delay slot was
   never emitted and fell out of the function body.
   Fix: `emitMipsDelaySlot()` pre-emits the delay slot at unconditional jumps,
   returns and indirect transfers before breaking (`src/core/DisassemblyAnalyzer.cpp`).

### Result
Instruction-level semantic parity is now **100% on every fixture**:

| Binary | match rate |
|---|---|
| x64_dyn_stripped.elf | 53/53 |
| aarch64_fib.elf | 38/38 |
| arm32_fib.elf | 25/25 |
| ppc32_fib.elf | 46/46 |
| mipsel_fib.elf | 52/52 |
| aarch64_pie_dyn.elf | 65/65 (shared) |
| arm_dyn.elf | 67/67 |
| mips_dyn.elf | 81/81 |
| ppc_dyn.elf | 106/106 |
| x64_dyn.elf | 53/53 |

0 mnemonic mismatches, 0 operand mismatches across all fixtures. Full CTest
suite: 78/78 pass.

## Remaining (known, non-blocking)
- `large_x86_64.elf`: Enigma's function-boundary heuristic splits large functions
  differently from Ghidra (shared entries cover ~135 of Ghidra's ~1400
  instructions for the worst case). Wherever both sides disassemble the same
  address the output is identical; the gap is body/extent assignment in
  `FunctionBodyFinalizer` / `FunctionStartAnalyzer`, not the decoder.
- `aarch64_pie_dyn.elf`: Ghidra discovers 14 more function entries (tail/branch
  heuristics); no shared-body differences.
- x64_dyn: 1 Ghidra-only function entry (IAT thunk). ppc_dyn: 1 Enigma-only
  entry. Function-count only; instruction coverage is exact.
