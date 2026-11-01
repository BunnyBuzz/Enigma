# Worked Example: PE32+ Triage and Function Review

This example records a real session on `samples/c_complex.exe` from the Enigma
Engine repository. The sample is a small PE32+ x86-64 executable built from C.
The package does not include the sample or its source.

Commands assume the Enigma CLI tools are on `PATH` and the working directory is
the repository root. If you run from `Enigma-Engine/`, drop the `Enigma-Engine/`
prefix from the Ghidra project paths.

## Evidence baseline

| Item | Value |
| --- | --- |
| Target | `samples/c_complex.exe` |
| SHA-256 | `EE923D4D8EAD769B0530E399932EB9394F98348CE335B739A65EB81032830AA5` |
| Size | 323,181 bytes |
| Format | PE32+ |
| Architecture | x86-64 |
| Image base | `0x140000000` |
| Entry point | `0x140001490` |
| Toolchain | local `Enigma-Engine/build/` |
| Repository commit | `d3c1554` |

Record your own commit and build. Treat the output as evidence for this build,
not as a stable golden file.

## Step 1: Triage

```bash
enigma_binary_audit samples/c_complex.exe > audit.txt 2> audit.log
```

Observed excerpt:

```text
=== BINARY STRUCTURE ===
Format: PE
Arch: x86
Bitness: 64
ImageBase: 0x140000000
EntryPoint: 0x140001490

Sections (18):
  .text: 0x140001000 - 0x14000b760 (size=a760, file=a800) type=0 r=1 w=0 x=1
  .data: 0x14000c000 - 0x14000c130 (size=130, file=200) type=0 r=1 w=1 x=0
  .rdata: 0x14000d000 - 0x14000e3c8 (size=13c8, file=1400) type=0 r=1 w=0 x=0
  .pdata: 0x14000f000 - 0x14000f528 (size=528, file=600) type=0 r=1 w=0 x=0
  ...

Exports: 0
Imports: 53
Symbols: 0 (functions: 0)
```

Interpretation:

- The executable is PE32+ x86-64 with a conventional image base.
- `.text` is the executable section; `.rdata` is a likely string/constant area.
- There are 53 imports and no exports, consistent with an executable rather than
  a DLL.
- The entry point is in `.text`.

The audit also reported, after analysis:

```text
Functions: 232
Instructions: 9131
Data: 110
```

These are analyzer counts, not ground truth.

## Step 2: Function inventory

```bash
enigma_dump_functions samples/c_complex.exe > functions.csv 2> functions.log
```

Observed rows around the entry:

```text
0x140001490,entry,entry
0x1400014fe,named,func_0x1400014fe
0x140001514,named,main
0x140001740,named,func_0x140001740
```

The `main` recognition is useful but heuristic. Note that
`enigma_binary_audit` showed the same address as `func_0x140001514` in its
function list because it uses a different analyzer set. This is exactly why the
skill asks you to record the tool and analyzer set instead of assuming all
tools agree.

## Step 3: Disassemble the candidate main

```bash
enigma_dump_listing samples/c_complex.exe unused.csv 0x140001514 > main.disasm 2> main.disasm.log
```

Observed:

```text
0x140001514:  PUSH  R13
0x140001516:  PUSH  R12
0x140001518:  PUSH  RBP
0x140001519:  PUSH  RDI
0x14000151a:  PUSH  RSI
0x14000151b:  PUSH  RBX
0x14000151c:  SUB  RSP,0x228
0x140001523:  MOV  dword ptr [RSP + 0x260],ECX
```

Interpretation:

- This is a standard x86-64 frame setup with six callee-saved register pushes
  and a large stack allocation.
- `ECX` is stored to a stack slot; in the Windows x64 calling convention `ECX`
  is the first integer argument. The decompiler later calls it `param_1`.
- The large `0x228` stack allocation suggests local buffers or structures.

Do not infer the full signature from the prologue alone.

## Step 4: Decompile the same address

```bash
enigma_decompile_full -entry 0x140001514 -max-func 1 -o main.c samples/c_complex.exe 2> main.decompile.log
```

Observed excerpt:

```c
bool __fastcall main(int32_t param_1)
{
    uint8_t *v_1;
    uint8_t *v_2;
    uint8_t *v_3;
    uint64_t v_4;
    int32_t v_5;
    uint32_t v_6;
    int64_t v_7;
    char v_8;
    uint64_t arg_0xfffffffffffffdc8;
    uint32_t v_9;
    uint8_t local_0x218 [128];
    char local_0x198 [112];
    uint8_t local_0x128 [16];
    uint64_t local_0x118 [4];
    uint8_t local_0xf8 [18];
    uint8_t local_0xe6 [126];
    uint64_t local_0x68;
    func_0x140001740();
    v_1 = (uint8_t *)0x14000d000;
    v_4 = 0x14650fb0739d0383;
    do {
        v_4 = (*v_1 ^ v_4) * 0x100000001b3;
        v_1 = v_1 + 1;
    } while (v_1 != (uint8_t *)0x14000d015);
    ...
    qsort(local_0xf8,4,0x30,func_0x1400014fe);
    __mingw_printf(local_0x198,0x80,0x14000d030,0xc0de,v_9 << 0x20 | 7,0x155,v_4);
    func_0x140002420(local_0x218,0x40,0x14000d058,0x402921fb54442d18,4);
    puts(local_0x198);
    func_0x1400023a0(0x14000d07e,local_0x218);
    ...
}
```

What is **observed**:

- The decompiler emitted a function named `main` with one parameter.
- It shows a loop over bytes at `0x14000d000` with constants
  `0x14650fb0739d0383` and `0x100000001b3`. The second constant is the FNV-1a
  64-bit prime; the first is a custom seed, not the standard FNV offset basis
  (`0xcbf29ce484222325`). The loop is consistent with an FNV-1a-style hash, but
  the seed choice is the binary's own.
- It calls `qsort` with element size `0x30` and a comparator at
  `0x1400014fe`.
- It calls `__mingw_printf`, `puts`, and unnamed helpers such as
  `func_0x140002420` and `func_0x1400023a0`.
- It references strings at `0x14000d030`, `0x14000d058`, and `0x14000d07e`.

What is **inferred**:

- The function is the application's `main`; the name came from analysis.
- `param_1` is likely `argc`, but the decompiler did not emit `argv`. The real
  signature may have more parameters.
- `local_0x118` is likely a table of string pointers; `local_0xf8` is likely an
  array of `0x30`-byte records sorted by `qsort`.
- `func_0x1400014fe` is the comparator because it is passed to `qsort`, not
  because its body was verified here.
- The `0x402921fb54442d18` constant is a double bit pattern (approximately
  `12.566370614359172`, or 4π), consistent with a 4π-related calculation. This
  is an inference from the constant, not a source-level proof.

What is **not** established:

- The original variable names, struct layouts, and comments.
- That the decompiled `bool` return type is correct. `main` normally returns
  `int`; the decompiler inferred `bool` from the observed return values.
- That every callee was decompiled or that every call was emitted rather than
  inlined.
- That the binary is safe to execute.

## Step 5: Check naming coverage

```bash
enigma_naming_audit samples/c_complex.exe > naming.txt 2> naming.log
```

Observed:

```text
Total functions:    232
Named functions:    39  (16.8%)
Auto-generated:     193  (83.2%)
```

This is a useful warning: most functions are auto-named. Do not treat a
`func_0x...` name as meaningless, but do not treat a `named` row as proven
either.

## Step 6: Cross-reference and CFG check

There is no CLI for xrefs or CFG. In the GUI:

1. Open the binary.
2. Go to `0x140001514`.
3. `Navigate > Show References (XRefs)...` to see callers.
4. `View > Function Graph` to inspect basic blocks.

For a headless workflow, use the C++ `ReferenceManager` and
`cfg::DisassemblyCFG` APIs described in `references/analysis-workflows.md`.
Record that the xref/CFG check was not performed if you only ran the CLI.

## Step 7: Patch verification (separate task)

This is a byte-level example, not part of the main analysis:

```bash
cp samples/c_complex.exe work/c_complex.work.exe
enigma_patch_cli work/c_complex.work.exe 0x140001000 c3 90 work/c_complex.patched.exe
```

Observed:

```text
Loaded ... format=PE arch=x86 bits=64
ProgramDB + spaces OK
populateProgram OK
PatchManager OK
Patch applied
Patch at 0x140001000: c3 -> 90
Active patches: 1
Export OK
File offset: 0x600
VERIFY OK: patched bytes present in output
```

The tool verified the bytes at the mapped file offset. It did not verify that
the patched program runs, that checksums are valid, or that the patch is
semantically correct. It also did not verify the supplied original byte `c3`
against the input; that byte was confirmed separately in the listing.

## Step 8: Ghidra project import appendix

A separate verified run on `tests/headless_proj/smokeproj.rep`:

```bash
enigma_gzf_inspect Enigma-Engine/tests/headless_proj/smokeproj.rep --table Program --limit 2
enigma_gzf_probe Enigma-Engine/tests/headless_proj/smokeproj.rep
```

Observed excerpt:

```text
== imported program: x64_dyn_stripped.elf ==
language=x86:LE:64:default
compilerSpec=gcc
effectiveImageBase=0x100000

== memory blocks ==
  segment_4 start=0x1036d8 length=104 W R
  segment_3 start=0x102600 length=2560 R
  segment_2 start=0x1014c0 length=320 X R
  segment_1 start=0x100000 length=1208 R
  EXTERNAL start=0x104000 length=80 W R

== functions (31) ==
  0x1014c0  fib
  0x1014f0  _start
  ...
```

This shows that the native Ghidra import path reconstructs a program model and
function inventory. It does not prove that every Ghidra feature survived.

## Reproduction checklist

- Use the same target hash and tool build.
- Capture stdout and stderr separately.
- Record the exact commands.
- Re-run the listing before trusting a decompiled address.
- Mark observed versus inferred claims.
- State which GUI/API checks were not performed.

## What this example does not prove

- That Enigma reconstructs the original C source.
- That `main` recognition is correct for every binary.
- That the inferred types and local names match the source.
- That the patched binary is valid or safe.
- That the Ghidra import is lossless.
