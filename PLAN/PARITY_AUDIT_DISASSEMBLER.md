# Disassembler Parity Audit (SLEIGH / DecompInterface vs Ghidra 12.2 headless)

Tooling: `tools/headless/DumpListing.java`, `tools/enigma_dump_listing.cpp`,
`tools/parity_listing_diff.py`, `tools/run_parity_audit.ps1`.

Ghidra ground truth is **Ghidra 12.2 + JDK 25**. The listing CSVs under
`tests/corpus/ghidra_listing/` were regenerated on 2026-10-23; the Ghidra-side
CSVs are authoritative. Enigma-side `*_enigma.csv` files are generated
snapshots and are not used as regression inputs.

## Ghidra 12.2 re-baseline (2026-10-23)

| Binary | Functions G/E/shared | Instructions G/E | Semantic | Mnem/Operand | Notes |
|---|---|---|---|---|---|
| `aarch64_fib.elf` | 2/2/2 | 38/38 | 37 | 0/1 | Ghidra `x11\|[x10; x9#0x0]` vs Enigma `x11; [x10; x9; LSL #0x0]` |
| `arm32_fib.elf` | 3/3/3 | 25/25 | 25 | 0/0 | exact |
| `mipsel_fib.elf` | 3/3/3 | 52/52 | 52 | 0/0 | exact |
| `ppc32_fib.elf` | 3/3/3 | 46/46 | 46 | 0/0 | exact |
| `aarch64_pie_dyn.elf` | 22/29/22 | 235/208 | 208 | 0/0 | 7 Enigma-only functions, 27 Ghidra-only instructions |
| `arm_dyn.elf` | 12/12/12 | 67/67 | 67 | 0/0 | exact |
| `mips_dyn.elf` | 2/2/2 | 81/81 | 81 | 0/0 | exact |
| `ppc_dyn.elf` | 12/12/12 | 106/106 | 106 | 0/0 | exact; 13 stale duplicate Enigma rows removed |
| `x64_dyn.elf` | 13/12/12 | 53/53 | 53 | 0/0 | 1 Ghidra-only entry (`0x101550` IAT thunk), 0 unique instructions |
| `large_x86_64.elf` | 3153/3241/3105 | 192928/181315 | 177844 | 0/0 | 48 Ghidra-only funcs, 136 Enigma-only; 15084/3471 unique instrs; 2951/3105 exact bodies |

No mnemonic or operand mismatches were found on any shared instruction other
than the single AArch64 operand-formatting quirk above. That is a Ghidra 12.2
printer quirk (`x9#0x0`), not a decode difference; Enigma deliberately keeps
the valid `LSL #0x0` spelling. Where both sides disassemble the same address,
the bytes and semantics are identical.

### Function-discovery differences (not decoder defects)

- **`aarch64_pie_dyn.elf`**: Ghidra 12.2 finds 22 image functions; Enigma finds
  29. The seven Enigma-only entries are `0x100c8c`, `0x100ce4`, `0x100e24`,
  `0x100fa4`, `0x101024`, `0x1010bc`, `0x101184`. Ghidra absorbs `0x100c8c`
  into the `entry` body, producing 27 Ghidra-only instructions. No shared-body
  instruction differs; this is a function-start/body-extent difference, not a
  decode failure.
- **`x64_dyn.elf`**: one Ghidra-only function (`0x101550`, IAT thunk).
  Enigma can decompile it by `-entry 0x101550` but its function manager does
  not list it as a separate function. It contributes zero unique instructions.
- **`large_x86_64.elf`**: 3105 shared functions and 177844 semantic matches
  (92.2% of shared-function instructions; 0 mnemonic / 0 operand mismatches).
  2951 of the 3105 shared bodies are byte-identical to Ghidra. The largest
  remaining causes are jump-table targets, merged/split boundaries, and
  unreachable compiler helpers. 48 Ghidra-only entries remain (21 push-frame
  prologues, 9 `sub rsp`, 2 `push rbp`, 1 `push rbx`, 2 `ret`, 13 other) and
  136 Enigma-only entries. `0x400160`/`0x400190` are now split exactly as Ghidra
  does; `0x400260` therefore calls `func_0x400190()` and `0x4009a0` calls
  `func_0x4d321f` without the former `unaff_RDI` copy code. Ghidra 12.2 moved
  the entry at `0x4a2375` to `0x4a2330` for 23 instructions, and the regenerated
  CSV reflects that.
- **Function starts recovered in the 2026-10-25 pass**: 42 additional Ghidra
  entries in three stages — 12 from canonical forward decoding of REX-push
  prologues after `CALL`/`JMP`, 14 more after accepting `RET` as the preceding
  transfer, and 16 from the broader push-frame patterns. The 16 push-frame
  starts are `0x409f12`, `0x41f57f`, `0x426ceb`, `0x44aa7b`, `0x44ab9d`,
  `0x44ac0b`, `0x47b55d`, `0x486ceb`, `0x48ec7f`, `0x48ecb2`, `0x48ece5`,
  `0x4972d9`, `0x499633`, `0x49a1f8`, `0x49e455`, `0x4be3fa`; all match Ghidra
  bodies exactly. Two previously over-extended bodies (`0x4be3e6`,
  `0x41f51b`) now match exactly as a side effect of the new splits. The
  remaining body-extent diffs in the other recovered functions are pre-existing
  Enigma-only splits (`0x49bf7d`, `0x49e066`), not missing calls.
- **Jump-table recovery** is still the dominant missing class for large x86:
  indirect branches such as `JMP [base+RAX*8]` in the `0x474040` region. This
  is decompiler/graph scope rather than an instruction-decoding defect.

## Function-start rules (2026-10-25)

`isValidFunctionStartCandidate` remains authoritative for every entry. The
following rules supplement it; the first two are gated to 64-bit x86 and only
run for push-frame prologue patterns.

1. **`followsCanonicalTransfer()`** (`src/core/FunctionStartAnalyzer.cpp`).
   When the validator rejects a push-frame candidate because a shorter byte
   window decodes as an ordinary instruction, Enigma decodes forward from the
   nearest known entry (initially every existing function, then each start
   accepted in the same pass). The candidate is accepted only when the decode
   lands exactly on it and the preceding instruction is `CALL`, `JMP`, `RET`,
   or `RETN`.
   - This replaces the earlier backward-window `hasCallOrJumpEndingAt()` scan,
     which accepted a fake `JMP` decoded from `e9 52 4c 89 e2` inside
     `mov rdx,r12` at `0x48ede7`.
   - It still recovers `0x4948e8` (after `JMP`), `0x494af5` (after `CALL`),
     `0x48ed20`, and the 14 cold-code starts after `RET`
     (`0x40a567`, `0x411c02`, `0x422b8d`, ...).
   - Conditional branches and fallthrough never qualify. `0x4586ca` (target of
     `JS`) and `0x497bb8` (target of `JNZ`) are still rejected; those targets
     are folded into their parents exactly as Ghidra does.
   - Decoding through an early `RET` inside the source function is permitted,
     because functions with multiple return blocks legitimately place the next
     function after any of them. A "stop at the first `RET`" variant was tried
     and reverted: it lost 35 correct functions while removing only 6
     unreferenced data-region false positives.

2. **Cross-function JMP stub skip** (`findCrossFunctionJumpTargets`). A
   cross-function `JMP` target is not turned into a new entry when the target
   begins a trivial epilogue (`RET`, `xor eax,eax; ret`, ...). This removed
   `0x4004c3`, `0x400b16`, `0x41f577`, and `0x43b960` without losing any
   shared function. The `afterTinyRetStub` exception keeps `0x400dc0`, whose
   target resolves to the same entry interval because `0x401130` has not yet
   been discovered.

3. **FragmentMerge arbitration** (`src/core/FragmentMergeAnalyzer.cpp`).
   - Keep the earlier entry when it is a direct-call target.
   - Drop a trivial epilogue stub with an incoming flow reference.
   - For a stub directly abutting a preceding `RET`/`JMP`, keep it only with an
     incoming reference or a raw-byte `CALL` target; otherwise drop it.
   - Remove orphan `func_0x*` trivial-epilogue stubs with no call/data refs,
     no raw `CALL` target, and no cross-function flow refs.
   - Otherwise drop the earlier stub in favor of the later entry.

4. **Finalizer cleanup** (`src/core/FunctionBodyFinalizer.cpp`). Synthetic
   entries whose only incoming references are conditional branches from another
   function are removed. Direct-call targets and cross-function jump/tail-call
   targets are kept.

The six new Enigma-only entries introduced by the broader push-frame fallback
(`0x426a68`, `0x44a608`, `0x44a66c`, `0x496ff6`, `0x49d613`, `0x4b4f06`) are
unreferenced starts inside Ghidra-undecoded data regions. No clean runtime
discriminator was found, so they are recorded rather than filtered. Removing
them would require a stop-at-`RET` rule that costs 35 real functions.

### SYSCALL/SVC fall-through (2026-10-25)

`Disassembler::determineFlowType()` classified `syscall` and `svc` as
`TERMINATOR`. Ghidra models both as userops with normal fall-through: the x86
`SYSCALL` semantic sets `RCX = inst_next` and the AArch64 `SVC` semantic calls
`CallSupervisor` without a `goto`. Treating them as terminal truncated every
glibc syscall wrapper at the syscall, dropping the return-value test and error
path from the function body.

Removing them from the terminator list raised semantic matches 176609 → 177844
and exact bodies 2809 → 2951 of 3105, with zero previously-exact bodies
regressing and no new over-extensions. Ghidra-only instructions in shared
functions fell 16319 → 15084. The 50-function corpus output remained
byte-identical (29652 bytes) and all 78 CTest suites passed.

## Historical follow-ups (Ghidra 12.1.3 era; retained for context)

### Decode-correctness fixes (validated against Ghidra)
1. **ARM `ldr pc` treated as fallthrough** — PLT stubs end in
   `ldr pc, [r12, #imm]!`. `determineFlowType()` classified it as FALL_THROUGH,
   so recursive descent ran past the stub into the embedded literal pool and
   invented instructions (`ldrble sp,[r4],#0x4d4` from `d4d4d4d4`), which then
   desynchronised every subsequent instruction in
   the ARM binary. Fixed by treating `ldr pc` as a terminal branch.
2. **MIPS `jr $t9` treated as fallthrough** — GNU MIPS PIC PLT stubs end in
   `jr $t9`, which is a return from the stub, not a fallthrough. Fixed by
   classifying `jr` as terminal and modeling the delay slot.
3. **PPC `blr` treated as fallthrough** — `blr` is the PPC return; recursive
   descent ran into the next function. Fixed by treating `blr` as a terminal
   branch and suppressing its delay slot (PPC has none).
4. **MIPS delay slots** — branch delay-slot instructions are now decoded as
   part of the branch, matching Ghidra's listing extent.
5. **Duplicate ELF symbols** — `.symtab` and `.dynsym` entries with the same
   `name@address` were both pushed into `symbols_`, causing
   `FunctionManager::createFunction` overlap exceptions. `src/core/BinaryLoader.cpp`
   now dedupes before `parseELFImports()`.
6. **Silent analysis-skip** — without the dedup, `populateProgram` threw
   `Overlapping function body`, the tool caught it and reset the analysis
   program, so some baselines were produced with no analysis at all. Fixed by
   the dedup plus a `FunctionDiscovery` pre-pass in `enigma_decompile_full`.
7. **`isPE` vs `isPeFormat`** — `isPE` is true for any load, so the `_`-prefix
   CRT filter hid ELF glibc imports (`___cxa_atexit`, …). A true `isPeFormat`
   flag now gates PE-only rules; other `isPE` heuristics are untouched.

### Follow-up: mid-function split root cause + silent analysis-skip (2026-10-13)
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

### Follow-up: unreachable-function discovery + body clamp (2026-10-13)
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
