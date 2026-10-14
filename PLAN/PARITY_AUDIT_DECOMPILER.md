# Decompiler Parity Audit (Enigma vs Ghidra 12.1.3 headless DecompInterface)

Harness: `tools/headless/DumpDecompile.java` (per-function `<entryhex>.c` +
`index.csv`, optional `GHIDRA_DECOMP_ONLY` filter for large binaries),
`tools/run_decomp_audit.ps1` (drives Ghidra import+analysis+export, Enigma
per-function singles via `-entry -max-func 1`, then diff),
`tools/parity_decomp_diff.py` (join on rebased entry; --delta like the
listing audit; `--ghidra-listing` defines image functions to skip
EXTERNAL-space thunks).

Metrics: M1 function-set parity, M2 naming (exact + auto/normalized), M3
success (Ghidra status vs Enigma `halt_baddata`), M4 signatures (return type
+ param count), M5 callee sets (normalized: `PTR_name_addr`/`_name`/
`*.plt_pic32.*` spellings unified, auto names compared by rebased address,
Ghidra intrinsics and variable-calls excluded), M6 normalized text
similarity (informational).

Driven through `run_decomp_audit.ps1 -Binary <name> -Delta <d>`.

## Baselines (2026-10-13, full rebuild, 78/78 green)

| Binary | M1 shared | M2 exact/norm | M3 | M4 ret/params | M5 prec/rec |
|---|---|---|---|---|---|
| arm_dyn.elf (d=0x10000) | 12/12 (+PLT0 en-only) | 12/12 | 12/12 OK, 0 bad | 6/7 | 1.00/1.00 |
| x64_dyn.elf (d=0x100000) | 13/13 | 12/13 | 13/13 OK, 0 bad | 6/5 | 1.00/1.00 |
| aarch64_pie_dyn.elf (d=0x100000) | 29/30 | 16/28 | 29/29 OK, 0 bad | 23/24 | 0.92/0.92 |
| mips_dyn.elf (d=0x10000) | 2/2 | 2/2 | 2/2 OK, 0 bad | 1/2 | 0.00/0.00 |
| ppc_dyn.elf (d=0x10000) | 12/12 | 2 exact / 12 norm | 12/12 OK, 0 bad | 4/2 | 0.09/0.09 |
| aarch64_fib.elf (d=0x0) | 2/2 | 2/2 | 2/2 OK, 0 bad | 1/2 | 1.00/1.00 |
| arm32_fib.elf (d=0x0) | 3/3 | 3/3 | 3/3 OK, 0 bad | 1/3 | 1.00/1.00 |
| mipsel_fib.elf (d=0x0) | 3/3 | 3/3 | 3/3 OK, 0 bad | 1/3 | 1.00/1.00 |
| ppc32_fib.elf (d=0x0) | 3/3 | 3/3 | 3/3 OK, 0 bad | 2/3 | 1.00/1.00 |
| large_x86_64.elf (d=0x0, 28-func sample) | 28/28 | 0/28 auto both | 28/28 OK, 0 bad | 16/7 | 0.78/0.81 |

## Fixes delivered from audit findings
1. **noreturn library functions**: Enigma sailed past `__stack_chk_fail()`,
   merging four init fragments into one function (Ghidra stops: its DB marks
   it noreturn). Extended `isNoReturn` in Linux/Mac DBs and Windows
   `getNoReturnTable` (`_Exit`/`exit_group`/`siglongjmp`/`__stack_chk_fail`/
   `__assert_fail`/`pthread_exit`/`__cxa_throw`/…).
2. **Main-rename clobber guard** (`enigma_decompile_full.cpp`): winner keeps
   an existing meaningful name; only auto names become `main`.
3. **FunctionDiscovery pre-pass with loader** in the decompile tool (mirrors
   `enigma_dump_functions`): PLT stubs get import names before analysis.
4. **`_` CRT filter is PE-only** (`isPeFormat`): ELF glibc imports
   (`___cxa_atexit`, …) are real functions, not CRT to hide.
5. **glibc prototype table + platform DB selection** (`LinuxTypeDatabase`,
   `detectPlatform` switch): 40 verified glibc signatures; bridge param
   names use Ghidra-style `param_1`.
6. **Thunk/user signature discipline** (`bridgeImportSignatures`): import
   thunks keep Ghidra-style `void(void)` (flags now preserved across
   `FunctionBodyFinalizer` remove/recreate); library prototypes NEVER apply
   to user-defined image functions (inference rules there — forcing `INT`
   onto user `fib` demonstrably perturbs inference with casts while two
   independent inferences agreed). Applies to externals + call sites.
7. **`resolveTypeName` signedness fix** (`AnalysisBridge`): `INT`/`LONG`/
   `HRESULT` mapped to unsigned — now correctly split signed/unsigned
   (also `INT64`/`LONG_PTR`/`time_t` placement).

### Prototype note (honest assessment)
The Linux table + platform switch is currently near-output-neutral: the
fixtures' visible signatures were already carried by inference and the
firing Windows-DB entries. Its value is architectural (correct layer for
glibc types, noreturn correctness, POSIX-only call-site typing). M4
therefore still measures mostly inference-vs-inference (arm 6/12, x64 6/13,
pie 23/29, mips 1/2, ppc 4/12). Closing it needs prototype/inference
interplay, not more table rows. `printc` house style (`int32_t` for core
`int`) is intentional and normalized away in M4.

## Ranked findings (open)
1. **Prototype/inference interplay**: table-forcing on user code backfires
   (casts); inference alone misses params Ghidra finds (x64 `fib()` vs
   `fib(int)`). Needs FID-gated application, not blanket rules.
2. **MIPS/PPC GOT-indirect call resolution**: Ghidra binds GOT slots to
   imports (`(*(code *)PTR_fib_…)(10)`); Enigma leaves computed
   (`(**(code **)(arg_t9+…))(10)`, `(…(unaff_r30+…))()`). M5 0.00 on both.
   Loader has the relocations; decompiler call-target propagation doesn't
   apply them. (PPC bodies are otherwise structurally identical incl.
   strength reduction.)
3. **Jump-table recovery**: entry calls `FUN_00100c8c` in Ghidra vs
   `UNRECOVERED_JUMPTABLE` in Enigma; `0x101184` calls table target vs
   `ptr_0x5790`. Decompiler/graph scope.
4. **Stub-pattern tails**: `{31 C0 C3}`-style patterns fire on dead code
   after unconditional jumps (e.g. `func_0x406e91` swallowing Ghidra
   `0x406E94`'s rows). Follow-up: require a flow reference for stub
   patterns (stubs exist to be called), mirroring the landing-pad rule.
5. **`.init` naming**: `_INIT_0` vs `func_0xd78` (section-based naming).
6. x64 `0x101550` IAT thunk: Ghidra decompiles it (2 instrs); Enigma too
   (`func_0x1550`) — matched.

## Method notes (traps for future runs)
- `enigma_decompile_full -entry <addr> -max-func 1` output is identical in
  quality to `-all` mode for the same function — use it for address-exact
  pairs (whole-output splitting breaks on duplicate names like the two
  `fib`s).
- Ghidra decompiles THUNKS by following to the target (stub entry yields the
  real body) and decompiles EXTERNAL-space functions as `halt_baddata`
  stubs — both handled (self-call exclusion, non-image skip).
- `run_decomp_audit.ps1` cleans `*_gh/*_en` dirs at start: stale per-function
  files corrupt M1 (found the hard way).
- PowerShell `>` writes UTF-16; the comparator auto-detects UTF-8/UTF-16.
- Corpus `-max-func 50` windows shift with discovery changes; regen only
  after verifying hunks against Ghidra truth.
