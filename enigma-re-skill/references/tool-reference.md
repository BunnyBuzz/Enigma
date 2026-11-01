# Tool Reference

All commands below were verified against the local Enigma Engine build in this
repository. Tool behavior can change between revisions; record the tool path and
commit with your evidence.

## Conventions

- `<tools>` is the directory containing the executables, commonly
  `Enigma-Engine/build/` in a source checkout.
- `<target>` is the binary or project path.
- `enigma_dump_functions`, `enigma_dump_listing`, `enigma_binary_audit`,
  `enigma_pipeline_audit`, and `enigma_naming_audit` require a recognized
  container (PE, ELF, Mach-O, or COFF). Raw blobs are accepted by
  `enigma_decompile_full` with explicit `-lang`, `-base`, and `-entry`, and by
  the experimental `enigma_decompile` with `-a`, `-b`, and `-base`. Other tools
  require a container.
- Data goes to **stdout** or a named output file. Diagnostics normally go to
  **stderr**. Capture them separately.
- Addresses are hexadecimal. Use `0x` where the tool accepts it.
- Nonzero exit status means the command failed or printed usage. Observed
  statuses: `0` success, `1` usage/load/analysis failure, `2` patch CLI usage.
- On PowerShell, use `cmd /c "tool ... > out.txt 2> err.txt"` when native stderr
  would otherwise be surfaced as a PowerShell error.

## enigma_decompile_full

The official decompilation CLI. It auto-detects PE, ELF, Mach-O, and COFF, runs
the analysis pipeline, bridges the program model into the Ghidra-derived
decompiler, and emits C-like pseudocode. If the loader cannot identify the
file, it treats the input as a raw blob using the supplied language, base, and
entry.

```text
Usage: enigma_decompile_full [options] <binary>
```

| Option | Meaning |
| --- | --- |
| `-lang <id>` | Language ID. Default `x86:LE:64:default`. For detected PE/ELF/Mach-O/COFF the language is inferred unless supplied. |
| `-base <addr>` | VMA corresponding to file offset 0, in hex. Default `0x140001000` for raw input. Detected formats infer the image base. |
| `-entry <addr>` | Entry point address in hex. Defaults to the detected entry, or to `-base` when no entry is available. Also selects the decompilation root. |
| `-o <file>` | Write output to a file instead of stdout. |
| `-time` | Print a timing breakdown to stderr. |
| `-max-func <N>` | Limit total decompiled user functions. Default `200`. Minimum `1`. |
| `-all` | Decompile every function discovered by analysis, not only entry-reachable functions. |
| `-no-crt` | Do not suppress CRT/library function bodies. |
| `-no-bridge` | Skip all ProgramDB-to-decompiler bridging. |
| `-no-type-bridge` | Skip only the type bridge. |
| `-raw-types` | Preserve `undefined1/2/4/8` instead of normalizing to `uintN_t`. |
| `-h` | Print help. |

Behavior notes:

- Output is concatenated C-like function bodies with no banner. Functions are
  separated by blank lines.
- `-time` output is on stderr; do not mix it into a `.c` capture.
- By default, known CRT/library functions are decompiled for callee discovery
  but their bodies are not emitted and they do not count toward `-max-func`.
  Use `-no-crt` to see them.
- The tool strips decompiler warning comments, resolves some string references,
  removes single-call import thunks from output, and may rename a discovered
  application root to `main`.
- `-all` can be slow on large binaries. Prefer `-entry` plus a small
  `-max-func` for targeted work.
- The decompiler can inline a callee. In particular, `entry` may inline
  `__libc_start_main` rather than emitting a call. Do not treat the absence of a
  call as proof that the call does not exist.
- Pseudocode is not original source. Names and types are inferred.

Examples:

```bash
# One function
enigma_decompile_full -entry 0x140001514 -max-func 1 -o main.c target.exe 2> main.log

# First 20 user functions, with timing
enigma_decompile_full -max-func 20 -time target.elf > out.c 2> timing.log

# Raw blob at a known load address (full decompiler path)
enigma_decompile_full -lang x86:LE:32:default -base 0x8048000 -entry 0x8048000 raw.bin > out.c 2> out.log
```

## enigma_dump_functions

Runs the analysis pipeline and prints a function inventory as CSV.

```text
Usage: enigma_dump_functions <binary> [--ghidra-compat]
```

Default output:

```text
address,type,name
0x140001000,named,func_0x140001000
0x140001490,entry,entry
0x140001514,named,main
```

- `--ghidra-compat` emits `address,name` instead, for comparison scripts.
- `type` can be `entry`, `named`, `thunk`, `prologue`, or `discovery`, depending
  on the function name and body. In the verified PE sample most non-entry
  functions were `named`.
- The analyzer set includes function discovery, function-start analysis,
  import thunk detection, FID, main recognition, and function-body finalization.
- `enigma_binary_audit` uses a different analyzer set and can show different
  names for the same address. Do not compare outputs from different tools
  without saying so.

## enigma_dump_listing

Emits a per-instruction listing, or disassembles a single address.

```text
Usage: enigma_dump_listing <binary> <out.csv>
       enigma_dump_listing <binary> <out.csv> <addr>
```

CSV columns:

```text
funcEntry,addr,mnemonic,operands,bytes
0x140001010,0x14000102c,MOV,EAX;EDX,89d0
0x140001010,0x140001026,AND,EDX;0x1,83e201
```

- Commas inside operands are replaced with `;`.
- `bytes` is lowercase hex.
- Rows are emitted per function body. They are **not globally sorted by
  address**; do not assume row order is execution order. Deduplicate by
  `(funcEntry,addr)` when counting.
- In full-listing mode the CSV is written to `<out.csv>`; stdout receives a
  one-line `wrote N instructions` status message, not the CSV.
- In single-address mode the third positional argument is the address; the tool
  prints eight instructions to stdout and does **not** write `<out.csv>`. The
  `<out.csv>` argument is still required.
- Single-address output looks like:

```text
0x140001514:  PUSH  R13
0x140001516:  PUSH  R12
0x140001518:  PUSH  RBP
```

## enigma_binary_audit

A human-readable triage diagnostic.

```text
Usage: enigma_binary_audit <binary>
```

It prints:

- format, architecture, bitness, image base, entry point;
- sections with virtual/file sizes and read/write/execute flags;
- export and import counts (not individual entries; use
  `enigma_pipeline_audit` for those);
- symbol counts;
- analysis stages and before/after function, instruction, and data counts;
- the first 30 functions.

Use it to choose a language/base/entry and to confirm that imports and sections
were parsed. It is not a stable machine format and its analyzer set differs from
`enigma_dump_functions`.

## enigma_pipeline_audit

Analyzer timing and pipeline diagnostic.

```text
Usage: enigma_pipeline_audit <binary> [options]
Options:
  --timeout N   Max seconds per analyzer (default: 60)
```

It prints binary information, sections, symbol counts, individual imports and
exports, analyzer timings, and final counts. Use it when a run is slow, hangs, or discovers far more/fewer
functions than expected. It is not an export format.

## enigma_naming_audit

Measures naming coverage and repeated unnamed function signatures.

```text
Usage: enigma_naming_audit <binary> [--csv <output.csv>]
```

The text report includes total/named/auto-generated counts, category and failure
breakdowns, named-function sources, a signature summary, and top repeated
unnamed signatures. The CSV header observed was:

```text
binary,addr,name,category,auto,body_size,instrs,callers,callees,calls_named,called_by_named,hash,hash_bytes,failure
```

Use this to prioritize functions for manual review, not as proof that a name is
correct. It measures the current analyzer set, not ground truth.

## enigma_patch_cli

Applies one contiguous byte patch, exports a new binary, and verifies the
patched bytes at the mapped file offset.

```text
Usage: enigma_patch_cli <input> <addr:hex> <orig_hex> <new_hex> <output>
```

- `addr` is a virtual address, with or without `0x`.
- `orig_hex` and `new_hex` are hex byte strings without `0x`. Use the same
  length for a conventional replacement; the CLI does not normalize lengths.
- The CLI records `orig_hex` but does **not** verify it against the input before
  applying. Confirm the original bytes yourself from the listing or hex view.
- On success it prints `Export OK`, `File offset: 0x...`, and
  `VERIFY OK: patched bytes present in output`.
- If export succeeds but the new bytes are not present, it prints
  `VERIFY FAIL: patched bytes NOT in output` and exits nonzero. Export failures
  print `export FAILED` and exit `1`. Do not use the output file in either case.
- This is a byte-level patch. It does not assemble instructions, fix up
  relocations, update checksums, or guarantee that the patched program runs.
- Always patch a copy. Keep the original and record both hashes.

Example:

```bash
cp target.exe target.work.exe
enigma_patch_cli target.work.exe 0x140001000 c3 90 target.patched.exe
```

The GUI exposes richer patch types (NOP fill, string, instruction, metadata)
through its Patch menu. There is no verified CLI for those types.

## enigma_gzf_inspect

Inspects a Ghidra project database or a single Ghidra program file without a
Ghidra install or JVM.

```text
usage: enigma_gzf_inspect <db.gbf | dir.rep | file.gzf> [--table NAME]
                          [--limit N] [--all] [--chain ID] [--program NAME]
                          [--filebytes OUT]
```

- Accepts a `.gbf` database, a `.rep` project directory, or a `.gzf` file.
- Prints project/program identity, database parameters, table list, and table
  contents.
- `--table NAME` restricts output to one table; `--limit N` limits records;
  `--all` requests all records; `--chain ID` selects a table chain; `--program
  NAME` selects a program in a multi-program project; `--filebytes OUT` writes
  file bytes.
- This is an inspection tool. Use `enigma_gzf_probe` to import a program and
  decompile functions.

## enigma_gzf_probe

Imports a Ghidra project/program and dumps the resulting Enigma program state.
This is a diagnostic probe, not a polished reporting tool.

```text
usage: enigma_gzf_probe <db.gbf | dir.rep | file.gzf> [funcName]
                        [--instr HEXADDR]
```

It prints:

- imported program name, language, compiler spec, effective image base;
- memory blocks with permissions;
- function count and function list;
- for a named function: signature, parameters, locals, storage, and decompiled
  output;
- for `--instr`: listing lookup at the address and the first eight instructions.

Quirks:

- `argv[2]` is always treated as the function name. `--instr` only works after a
  non-option function name, for example
  `enigma_gzf_probe project.rep fib --instr 0x1014c0`.
- Running `enigma_gzf_probe project.rep --instr 0x1014c0` reports
  `function not found: --instr`.
- Decompiled output can be markup-laden and noisy. Use `enigma_decompile_full`
  for readable pseudocode after import where possible.

## Function ID / FKS tools

FKS (Function Knowledge System) stores function fingerprints and names in
`.fkslib` files with an LMDB index. It is optional; basic analysis works without
it.

```text
enigma_fks_ingest <binary> <output.fkslib> [--family <name>] [--compiler <name>] [--version <ver>]
enigma_fks_build_index [<fid_dir>]
enigma_fks_export_hashes [<fid_dir>]
enigma_survey_fkslibs <directory>
enigma_rebuild_fks_index <fid_dir>
enigma_fingerprint_audit <binary_a> <binary_b> [--csv output.csv]
```

Workflow:

1. Ingest a binary with useful names into a `.fkslib`.
2. Put one or more `.fkslib` files in a directory.
3. Build the index with `enigma_fks_build_index <dir>`. It creates
   `<dir>/index/lmdb`.
4. Set `ENIGMA_FKS_DIR=<dir>` when running analysis tools. `FidAnalyzer` checks
   for the index and only renames auto-generated functions.
5. Use `enigma_fingerprint_audit` to compare fingerprint quality between two
   binaries; use `enigma_survey_fkslibs` to inspect a library directory.

Notes:

- The compiled-in default FKS directory is an install-prefix path; set
  `ENIGMA_FKS_DIR` explicitly in a source checkout.
- The LMDB data file can be large/sparse. Do not package it.
- There is no public prebuilt signature database in this package.
- A fingerprint match is a candidate, not proof of identity.

## Experimental native pipeline

`enigma_decompile` is a separate, experimental native-pipeline tool:

```text
Usage: enigma_decompile [options] <binary>
Options:
  -a <arch>    Architecture (x86, arm, mips, ppc) [default: x86]
  -b <bits>    Bitness (32 or 64) [default: 64]
  -base <addr> Base address (hex) [default: 0x1000]
  -h           Print this help
```

It accepts a raw file with `-a`, `-b`, and `-base`; this path was verified on a
one-instruction blob. It is not the official decompilation path and can produce
different results from `enigma_decompile_full`. Prefer `enigma_decompile_full`
for analysis unless the task specifically targets the native pipeline.

## GUI features

The Qt GUI (`enigma_gui`) is the supported path for interactive capabilities
that have no CLI:

| Area | Actions present in the GUI source |
| --- | --- |
| File | Open Binary, Open Project, Save Project, Browse Dyld Cache Images |
| Edit | Rename Function, Set Function Type/Signature, Add/Remove Label, Set/Remove Comment, Add/Delete Bookmark, Command Palette |
| View | Disassembly, Decompiler, Hex, Console, Strings, Function Graph, Function Graph in New Window, Show Bytes |
| Navigate | Go to Address/Symbol, Back, Forward, Show References (XRefs), Toggle Decompiler/Disassembly Focus |
| Analysis | Auto Analyze |
| Import | Import from Ghidra, Data Types |
| Repository | Commit, Commit History, Create Branch, Switch Branch |
| Patch | Export Patched Binary, Show Patch List, Save/Load Patches, Revert All Patches, Print Patch List to Console |

The GUI includes a cross-reference explorer, function graph, structure/union
editor, string table, patch list, address minimap, command palette, and dyld
cache browser. These are not exposed as CLI commands.

## C++ API map

Headers are under `Enigma-Engine/src/include/` in this tree. Some repository
documentation refers to `include/ghidra/`; verify the actual path before
compiling.

| Header | Surface present in the headers |
| --- | --- |
| `ghidra/BinaryLoader.h` | `createLoader`, `load`, `populateProgram`, `getFormatName`, `getArchitecture`, `getBitness`, `getEntryPoint`, `getImageBase`, `getSections`, `getSymbols`, `getImports`, `getExports`, `getDelayLoads`, `getRelocations`, `getBytes`, `virtualAddressToFileOffset`; dyld cache methods. |
| `ghidra/ProgramDB.h` | `getListing`, `getMemory`, `getSymbolTable`, `getFunctionManager`, `getDataTypeManager`, `getReferenceManager`, `getExternalManager`. |
| `ghidra/DecompInterface.h` | `openProgram`, `closeProgram`, `isOpen`, `getFunctions`, `decompileFunction`, `disassembleAt`, `instructionLengthAt`, `refreshFunctionSymbols`. |
| `ghidra/ReferenceManager.h` | `getReferencesTo`, `getReferencesFrom`, `getFlowReferencesFrom`, `hasFlowReferencesFrom`, `getReferenceCountTo/From`, `getAllReferences`. |
| `ghidra/Function.h` | `getEntryPoint`, `getBody`, `getName`, `getParameters`, `getReturnType`, `getCalledFunctions`, `getCallingFunctions`, `isThunk`, `isExternal`, `getSignatureSource`, `getCallingConvention`. |
| `ghidra/FunctionManager.h` | `getFunctions`, `getFunctionAt`, `getFunctionContaining`, `createFunction`. |
| `cfg/DisassemblyCFG.h` | `cfg::CfgInsn`, `cfg::DisassemblyCFG::build`, `blocks`, `edges`, `EdgeKind`, `parseDirectTarget`. |
| `ghidra/storage/Repository.h` | project repository operations. |
| `ghidra/storage/WorkingSnapshot.h` | snapshot load/save. |
| `ghidra/storage/CommitManager.h` | `createCommit`, `loadCommitMeta`, `listCommits`, `loadChangeSet`, `commitExists`. |
| `ghidra/storage/BranchManager.h` | create/list/delete/switch/get current branch. |
| `ghidra/storage/IndexManager.h` | LMDB symbol/function index rebuild and lookup. |

For a working minimal harness, read
`Enigma-Engine/tools/enigma_dump_functions.cpp`. It shows the required address
spaces, loader setup, analyzer registration, and `DecompInterface` use. Do not
copy only part of that setup and expect analysis to work.

## Environment variables

| Variable | Effect |
| --- | --- |
| `ENIGMA_SLEIGH_DIR` | Directory containing compiled SLEIGH `.sla` specifications. Required when the tools cannot find their default. |
| `ENIGMA_FKS_DIR` | FKS directory containing `.fkslib` files and `index/lmdb`. Used by `FidAnalyzer` and FKS tools. |
| `ENIGMA_DEBUG` | Prints extra diagnostic detail to stderr in `enigma_decompile_full` (imports, exports, SLEIGH dir, base, entry, format). |

## Exit status and failure handling

- `enigma_decompile_full -h` exits `0`.
- Most tools print usage and exit `1` when required arguments are missing.
- `enigma_patch_cli` prints usage and exits `2` when arguments are missing.
- A nonzero exit is a failure; do not parse partial output as success.
- If a tool writes logs to stderr, a clean data file is not proof that analysis
  succeeded. Check the exit status and the log for errors.
