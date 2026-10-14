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

## Follow-up: mid-function split root cause + silent analysis-skip (2026-10-13)
- Worst-case split (`func_0x4153e5` keeping 8 of Ghidra's 1072 instructions)
  traced to `findPatternStarts()` in `src/core/FunctionStartAnalyzer.cpp`: the
  `isAtFunctionBoundary()` byte heuristic treated the trailing `0x00` of
  `mov edi,0xa` (`BF 0A 00 00 00`) as padding and short-circuited the precise
  `isValidFunctionStartCandidate()` fallthrough check. Fix: validator alone is
  authoritative (it already accepts real padding/terminators); the byte
  heuristic was deleted. large_x86_64 now: 2856 shared functions, 116049
  semantic matches, 0 mnemonic / 0 operand mismatches (was 112847).
- The `.symtab`/`.dynsym` dedup crash fix exposed a silent analysis-skip in
  `enigma_decompile_full`: without dedup, `populateProgram` threw
  `Overlapping function body`, the tool caught it and reset the analysis
  program, so baselines for the dyn ELFs were produced with NO analysis
  (loader names only). With analysis actually running, two tool gaps showed:
  (1) PLT stubs stayed `func_0x...` because the default analyzer set's
  `FunctionDiscoveryAdapter` carries no loader — fixed with a
  `FunctionDiscovery` pre-pass mirroring `enigma_dump_functions`;
  (2) the main heuristic unconditionally overwrote the winner (fib's stub
  became `main`) — fixed with an auto-name guard mirroring
  `MainRecognitionAnalyzer`; (3) the `_`-prefix CRT filter hid ELF glibc
  imports (`___cxa_atexit`, …) because `isPE` is true for any loaded binary —
  fixed with a true `isPeFormat` flag (other `isPE` heuristics untouched).
- Baselines regenerated with justification (all entries verified against
  Ghidra/relocation truth): `arm_dyn.elf.c` +8 (PLT0 resolver block),
  `x64_dyn.elf.c` +8 (IAT thunk at raw `0x1550` = Ghidra's rebased `0x101550`),
  `aarch64_pie_dyn.elf.c` (13 PLT thunks `func_0x…` → import names + import
  signatures; no functions added/removed). Full suite: 78/78 pass.

## Follow-up: unreachable-function discovery + body clamp (2026-10-13)
- Quantified the large_x86_64 gap: 296 Ghidra-only functions, of which 73 are
  1–2 instruction fragments (lone RET/JMP Ghidra artifacts, deliberately not
  chased) but the largest (822/633/614/597/487 instrs) are real unreachable
  functions starting with `PUSH R15`/`PUSH R12` — 130/296 share REX push-pair
  prologues with zero direct references, so no discovery pass proposed them.
  Added 11 patterns (`41 57 41 56`, `41 55 41 54`, `41 56 41 55`,
  `41 54 55`, R12/R14+mov pairs, RBX/RBP shuffle frames) to
  `getProloguePatterns()`; candidates still pass the authoritative
  `isValidFunctionStartCandidate`. Shared functions 2856 → 2987.
- The new functions then stalled at ~120 instructions each — traced NOT to the
  sweep (probe showed decoding continues past the apparent stall) but to the
  listing exporter, which only emits body-covered instructions, combined with
  `FunctionBodyFinalizer` clamping bodies to entry+512. Raised
  `kBodyFinalizerMaxScan` 512 → 8192 (largest observed body ~4.3KB;
  next-entry clamp still prevents crossing known boundaries).
- Result: semantic matches 116049 → 167393 (**90.4%** of shared-function
  instructions, 0 mismatches), Ghidra-only-in-shared 50820 → 17801.
  New Enigma-only entries are near-all in Ghidra-undecoded regions (real finds,
  e.g. post-RET boundaries) — one verified defensible split at 0x469168.
  `large_x86_64.elf.c` baseline: 1-line change (newly discovered Ghidra-confirmed
  function `0x4bedb2` now referenced). Full suite: 78/78 pass; small-fixture
  parity unchanged (all perfect).
- Remaining gap characterized as diffuse (no dominant pattern): biggest
  contributor is indirect-branch targets (e.g. `JMP [base+RAX*8]` jump tables
  in 0x474040) — jump-table recovery, i.e. decompiler/graph-audit scope, not
  a disassembler defect. Stopping here.
