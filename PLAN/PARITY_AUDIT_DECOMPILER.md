# Decompiler Parity Audit (Enigma vs Ghidra 12.2 headless DecompInterface)

Harness: `tools/headless/DumpDecompile.java` (per-function `<entryhex>.c` +
`index.csv`, optional `GHIDRA_DECOMP_ONLY` filter for large binaries),
`tools/run_decomp_audit.ps1` (Ghidra import+analysis+export, Enigma per-function
singles via `-entry -max-func 1`, then diff), `tools/parity_decomp_diff.py`
(join on rebased entry; `--delta` like the listing audit; `--ghidra-listing`
defines image functions to skip EXTERNAL-space thunks), and `tools/en_singles.py`
(per-function Enigma export).

Ghidra ground truth is **Ghidra 12.2 + JDK 25**. Compare byte-sensitive
semantics, not exact text.

Metrics: M1 function-set parity, M2 naming (exact + auto/normalized), M3
success (Ghidra status vs Enigma `halt_baddata`), M4 signatures (return type
+ param count), M5 callee sets (normalized: `PTR_name_addr`/`_name`/
`*.plt_pic32.*` spellings unified, auto names compared by rebased address,
Ghidra intrinsics and variable-calls excluded), M6 normalized text
similarity (informational).

## Baselines (2026-10-23, Ghidra 12.2, full rebuild, 78/78 CTest green)

| Binary | M1 shared | M2 exact/norm | M3 | M4 ret/params | M5 prec/rec |
|---|---|---|---|---|---|
| `arm_dyn.elf` | 12 (+`0x203a0` Enigma-only) | 12/12 | 12/12 OK, 0 bad | 6/7 | 1.00/1.00 |
| `x64_dyn.elf` | 13/13 | 12/13, 13/13 | 13/13 OK, 0 bad | 7/6 | 1.00/1.00 |
| `aarch64_pie_dyn.elf` | 22 (+7 Enigma-only) | 17/22, 22/22 | 22/22 OK, 0 bad | 17/17 | 1.00/1.00 |
| `mips_dyn.elf` | 2/2 | 2/2 | 2/2 OK, 0 bad | 1/2 | 1.00/1.00 |
| `ppc_dyn.elf` | 12/12 | 2/12, 12/12 | 12/12 OK, 0 bad | 4/2 | 1.00/1.00 |
| `aarch64_fib.elf` | 2/2 | 2/2 | 2/2 OK, 0 bad | 2/2 | 1.00/1.00 |
| `arm32_fib.elf` | 3/3 | 3/3 | 3/3 OK, 0 bad | 1/3 | 1.00/1.00 |
| `mipsel_fib.elf` | 3/3 | 3/3 | 3/3 OK, 0 bad | 1/3 | 1.00/1.00 |
| `ppc32_fib.elf` | 3/3 | 3/3 | 3/3 OK, 0 bad | 2/3 | 1.00/1.00 |
| `large_x86_64.elf` (28-function sample) | 28/28 | 0/28, 27/28 | 28/28 OK, 0 bad | 18/28, 6/28 | 0.95/0.93 |

The 28-function sample is `0x400120` through `0x400bf0` (first 28 Ghidra 12.2
entries). Its M6 is 0.418; M6 is informational and not a parity gate.

### Baseline notes

- **M5 is 1.00 on every small/medium fixture.** MIPS GOT calls now print as
  `(*_fib)(10)` / `(*_prctl)(...)`; PPC `.plt_pic32` stubs resolve through the
  GOT base; x64 `0x101550` normalizes Ghidra `PTR_001036e8` to Enigma
  `ptr_0x36e8`.
- **aarch64_pie M1/M2.** Ghidra 12.2's function manager finds 22 image
  functions, not the 29 found by earlier Ghidra/Enigma. The seven Enigma-only
  entries are `0x100c8c`, `0x100ce4`, `0x100e24`, `0x100fa4`, `0x101024`,
  `0x1010bc`, `0x101184`. This is a function-discovery difference, not a
  decompile failure. M2 is 17/22 exact and 22/22 normalized; the remaining
  exact-only differences are generic auto names.
- **large sample M2 artifact.** `0x400190` is a Ghidra-only function in this
  sample; forcing `-entry 0x400190` creates a placeholder named `entry`, so the
  normalized M2 denominator is 27/28. This is a harness artifact, not a naming
  mismatch.
- **large sample M4.** Return/parameter counts are weak because Enigma's
  per-function `-entry` path does not reproduce Ghidra's call-site signature
  inference. This is separate from callee resolution.
- **large sample M5 gaps (resolved 2026-10-25).** `0x400260`: Ghidra emits a
  call to `FUN_00400190`; Enigma formerly emitted none because `0x400190` was
  merged into the `0x400160` function body. `0x4009a0`: Enigma formerly lost
  `FUN_004d321f` while emitting `unaff_RDI` copy code. Both are fixed; see the
  large-sample update below.

## Large-sample update (2026-10-25)

The 50-function corpus run (`-all -max-func 50`) emits 47 functions after CRT
filtering and remains byte-identical to
`tests/corpus/expected/large_x86_64.elf.c` (29652 bytes); no baseline
regeneration was needed for this pass.

Against the 48-entry Ghidra decompile audit set:

- **M1**: all 48 Ghidra entries are present in Enigma's function map.
- **Bodies**: 47/48 have byte-identical instruction extents to Ghidra. The one
  remaining diff is `0x4038b1`: Enigma splits `0x4038c7` into its own function
  while Ghidra keeps it in the parent body. The `syscall`/`svc` fall-through
  fix raised this from 40/48 to 47/48.
- **Callees**: listing-level `CALL` target sets are identical for all 48
  functions. The earlier per-function decompiler audit showed identical callee
  sets for 44/45 common functions.
- **`0x400260`**: now emits `func_0x400190(); return;`, matching Ghidra's
  `FUN_00400190()` call. The former merge of `0x400190` into `0x400160` is
  fixed.
- **`0x4009a0`**: now emits `func_0x4d321f(param_1, v_1 + 1)` with no
  `unaff_RDI` copy code, closing the former M5 gap.
- **`0x400490` / `0x400a70`**: per-function output matches Ghidra structure with
  no false interior calls.
- **Known divergence**: Enigma's `entry` inlines `__libc_start_main`
  (`0x4bede0`) instead of emitting a call. This is pre-existing and unrelated
  to the function-start changes.
- M2/M3/M4 were not re-measured across all 48 entries: per-function `-entry`
  export takes roughly two minutes each. The 28-function M2-M5 numbers above
  remain the last full audit snapshot and are not directly comparable because
  the function set changed.

## Fixes delivered from audit findings

1. **MIPS/PPC GOT and PLT resolution.** MIPS `.dynamic`/`.dynsym`/`.dynstr`
   parsing synthesizes GOT imports with plain names (`_fib`, `_prctl`);
   `$t9` is seeded per function entry. PPC `.plt_pic32` stubs emit
   `(*ptr_0x...)` through the r30/r2 GOT base. Both audits now have M5 1.00.
2. **Shared tracked-register seeding.** `src/core/TrackedRegisterSeeder.cpp`
   and `src/include/ghidra/TrackedRegisterSeeder.h` centralize MIPS `$t9` =
   function entry and PPC32 `r30` / PPC64 `r2` = `.got2` or
   `_SDA_BASE_`/`_SDA2_BASE_` + `0x8000`. `AnalysisBridge` and
   `DecompInterface` both use it, so direct bridge users and the per-function
   audit path share one implementation.
3. **ELF init/fini array naming.** Relative relocations whose target lies in
   `.init_array`/`.fini_array` now synthesize `_INIT_n`/`_FINI_n` function
   symbols before function discovery, matching Ghidra's external-entry naming.
   This fixed the aarch64_pie `_INIT_0` vs `func_0xd78` M2 difference.
4. **x64 PTR normalization.** `parity_decomp_diff.py` keeps Ghidra
   `PTR_<hex>` in Ghidra address space and applies the side delta once in
   `callee_key`, fixing the `0x101550` false mismatch.
5. **Audit harness determinism.** `en_singles.py` strips UTF-8 BOMs;
   `run_decomp_audit.ps1` writes BOM-free address files and skips the full
   listing when `GHIDRA_DECOMP_ONLY` is set, so a filtered decompile sample
   cannot report thousands of false Ghidra-only functions.
6. **Earlier retained fixes.** Ghidra 12.2 listing CSVs are the authoritative
   disassembly baseline; MIPS16 `jr $t9` is treated as a return; MIPS/PPC
   delay-slot and `blr` flow is modeled; known-noreturn thunks no longer
   create phantom fallthrough; `main` renaming and CRT boundary output remain
   deterministic.

## Open findings (not yet parity blockers for the current baselines)

1. Jump-table recovery and switch normalization remain behind Ghidra; not
   covered by the current small fixtures.
2. `entry` inlines `__libc_start_main` (`0x4bede0`) instead of emitting a call.
   Pre-existing and unrelated to function discovery.
3. Large-sample M4 parameter/return recovery needs a call-aware signature
   pass; per-function `-entry` output alone is insufficient.
4. Mach-O/ObjC/Swift parity is unverified: no real Apple binaries are
   available in the corpus.
5. MIPS GOT parsing currently requires section headers (`.dynamic`/`.dynsym`);
   stripped ELFs without those headers are not covered.
6. Production `ProgramDB` does not populate `Instruction::pcode`, so analyzer
   symbolic propagation cannot influence ProgramDB state; GOT call resolution
   is done at the decompiler-bridge level.

## Method notes

- M1 uses the Ghidra function manager as the authority. `isPE` stays true for
  any load; `isPeFormat` is used for PE-only rules. Library prototypes apply
  only to externals/import thunks, never user-defined image functions.
- `DumpDecompile.java` writes `index.csv`; M2 exact comparison requires both
  sides to name the same function. Generic auto names are normalized by entry
  address, so `FUN_00400260` and `func_0x400260` compare equal.
- For large binaries, `GHIDRA_DECOMP_ONLY` may select a sample. The audit then
  deliberately skips the full Ghidra listing for M1; otherwise every function
  outside the sample would be reported as Ghidra-only.
- The corpus baselines under `tests/corpus/expected/` are regenerated only
  after each hunk is checked against Ghidra truth. All changes remain
  uncommitted; the user performs commits.
