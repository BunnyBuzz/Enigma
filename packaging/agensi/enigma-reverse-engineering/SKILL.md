---
name: enigma-reverse-engineering
description: Use when the user asks to reverse engineer, triage, disassemble, decompile, map functions, inspect control flow or cross-references, compare binaries, import a Ghidra project, patch bytes, or document findings for a PE, ELF, Mach-O, COFF, or Ghidra project, or a raw binary with an explicit language and base, using the Enigma Engine toolchain.
summary: Evidence-driven reverse-engineering workflows for the Enigma Engine CLI, Qt GUI, and C++ APIs, with verified commands, output formats, and explicit limitations.
version: 1.0.0
tags:
  - reverse-engineering
  - decompilation
  - disassembly
  - binary-analysis
  - ghidra
keywords:
  - enigma engine
  - decompiler
  - disassembler
  - control-flow graph
  - cross-references
  - PE
  - ELF
  - Mach-O
  - Ghidra import
  - function fingerprinting
use_cases:
  - Triage an unknown PE, ELF, Mach-O, or COFF binary and identify its entry point, functions, sections, and import/export counts.
  - Disassemble a function and decompile it to C-like pseudocode for manual review, including a raw blob when its language, base, and entry are known.
  - Map callers, callees, and basic blocks to understand a function's role.
  - Compare two builds, measure naming coverage, or import a Ghidra project for continued analysis.
  - Patch bytes in a copy of a binary and verify the patched output.
  - Produce an evidence-backed reverse-engineering report without claiming source reconstruction.
---

# Enigma Reverse Engineering

Enigma Engine is a native C++17 reverse-engineering framework with a Ghidra-derived
analysis pipeline, a Qt desktop GUI, and command-line tools. This skill teaches an
incremental, evidence-first workflow for using the verified parts of that toolchain.

Use it for authorized analysis of binaries you own or are permitted to inspect.

## Scope and non-claims

- **Interfaces covered:** CLI tools (live-verified), the Qt GUI, and the C++
  headers under `Enigma-Engine/src/include/` (source-inspected; GUI workflows
  were not exercised headlessly).
- **Not available:** an MCP server, a JSON output mode, Python bindings, a stable
  plugin ABI, or a dedicated CLI for cross-references, control-flow graphs,
  structure recovery, or signature lookup. Do not invent such commands.
- **Decompiler output is C-like pseudocode.** It is not the original source.
  Variable names, types, signatures, and boundaries are inferred. Never present
  pseudocode as recovered source.
- **No AI/LLM features are part of the verified engine surface.** This skill is
  agent guidance, not an engine capability.

## Preflight

1. **Locate the toolchain.** In a source checkout the tools are usually in
   `Enigma-Engine/build/`. Installed builds may place them on `PATH`. Use one
   consistent tool directory and record it.
2. **Confirm the tools you intend to use.**
   - `enigma_decompile_full -h`
   - `enigma_dump_functions` (no arguments prints usage)
   - `enigma_dump_listing` (no arguments prints usage)
   - `enigma_binary_audit` (no arguments prints usage)
   - `enigma_gzf_inspect -h`
   - `enigma_gzf_probe` (no arguments prints usage)
3. **Check SLEIGH data.** If decompilation reports
   `No SLEIGH specs found`, set `ENIGMA_SLEIGH_DIR` to the directory containing
   the compiled `.sla` specifications, or run from the expected project root.
4. **Record evidence before analysis.** Capture the target path, SHA-256, file
   size, tool path, repository commit if available, and the exact command.
5. **Work on a copy for any write operation.** Never patch, export over, or
   execute an untrusted original.

## Evidence rules

- Separate machine-readable output from diagnostics. Most tools write `[INFO]`
  logs to **stderr** and data to **stdout** or a named file. Redirect them
  separately.
- Treat function names, decompiled types, and comments as **claims**. Verify
  addresses and control flow against the listing.
- Mark each statement as **observed** (directly in output), **inferred** (from
  evidence), or **unverified** (needs another check).
- Record negative evidence too: "no xrefs found", "function not present in the
  imported project", "decompilation failed".
- Function starts can differ between tools and from Ghidra. Do not silently
  reconcile counts; report the tool and analyzer set used.
- Do not run a suspect binary to "see what it does". Static analysis first.

## Quick start

```bash
# Triage: format, sections, import/export counts, symbols, analysis counts
enigma_binary_audit target.bin > audit.txt 2> audit.log

# Function inventory: address,type,name CSV on stdout
enigma_dump_functions target.bin > functions.csv 2> functions.log

# Disassemble eight instructions at one address (third positional argument)
enigma_dump_listing target.bin unused.csv 0x401000 > disasm.txt 2> disasm.log

# Decompile one function as the entry root
enigma_decompile_full -entry 0x401000 -max-func 1 -o function.c target.bin 2> decompile.log
```

`enigma_dump_listing` still requires the output-CSV argument in single-address
mode. That file is not written in this mode; the instructions go to stdout.

On PowerShell, native stderr can be surfaced as errors. For clean captures use:

```powershell
cmd /c "enigma_dump_functions target.bin > functions.csv 2> functions.log"
```

## Core workflow

### 1. Scope the target

Identify format, architecture, bitness, image base, entry point, sections, and
symbol presence. `enigma_binary_audit` prints these plus
import/export/symbol counts. Use it for triage, not as a stable machine format.
When you need individual import/export entries, use `enigma_pipeline_audit` or
the C++ `BinaryLoader` API.

Decide whether the task is interactive (GUI) or batch (CLI/C++). Do not promise
GUI-only results from a headless run.

### 2. Build a function map

Run `enigma_dump_functions`. The default CSV is:

```text
address,type,name
0x140001000,named,func_0x140001000
0x140001490,entry,entry
0x140001514,named,main
```

`--ghidra-compat` emits `address,name` instead. Sort by address for navigation,
but keep the original output as evidence. Distinguish:

- `entry` — the program entry point;
- `named` — a symbol-derived or analysis-derived name;
- `thunk` / `prologue` / `discovery` — possible classifications for auto-named
  functions, depending on the analyzer set and name pattern.

Do not assume every `named` function is correctly named. Check imports, call
sites, and strings.

### 3. Drill into one function

Disassemble before decompiling:

```bash
enigma_dump_listing target.bin unused.csv 0x140001514 > main.disasm 2> main.disasm.log
```

Then decompile the same address as a single root:

```bash
enigma_decompile_full -entry 0x140001514 -max-func 1 -o main.c target.bin 2> main.decompile.log
```

Read the listing and pseudocode together. Confirm:

- the function prologue and end;
- direct call targets;
- stack and global accesses;
- branch conditions;
- whether the decompiler emitted a call or inlined a callee;
- whether names came from imports, symbols, or heuristics.

### 4. Cross-references and control flow

There is **no dedicated xref or CFG CLI**. Use one of these documented paths:

- **GUI:** `Navigate > Show References (XRefs)...` opens the cross-reference
  explorer. `View > Function Graph` shows the basic-block graph for the current
  function; `View > Function Graph in New Window` opens a separate window.
- **C++ API:** use `ReferenceManager::getReferencesTo`, `getReferencesFrom`,
  `getFlowReferencesFrom`, and `hasFlowReferencesFrom`; use
  `cfg::DisassemblyCFG::build` with `cfg::CfgInsn` records and function entries
  to obtain blocks and typed edges. See
  `references/analysis-workflows.md` for header paths and method names.

If neither path is available, say so. Do not fabricate an xref listing from a
decompiler call graph and call it complete.

### 5. Understand the program

Build a small, checkable model:

1. Entry point and startup chain.
2. `main` or the application-level root, if recognized.
3. Imported APIs grouped by library.
4. Callers and callees of the functions that matter.
5. Strings and data references (GUI String Table or listing references).
6. Error paths, logging, file/network/registry access, and cryptographic constants.

`enigma_naming_audit` measures naming coverage and repeated unnamed signatures.
`enigma_fingerprint_audit` compares two binaries' function fingerprints.
Neither proves semantic equivalence.

### 6. Verify before reporting

- Re-read the exact bytes in the full listing CSV (`bytes` column) or the Hex
  view.
- Check that the address is mapped and executable.
- Check the image base and any `-base` override.
- Re-run with a smaller scope if output is noisy or times out.
- For patches, require `VERIFY OK` and compare file hashes.
- State what was not checked.

### 7. Report

Use the template at the end of this file. Keep observed facts separate from
inferences, and include reproduction commands.

## Tool selection

| Need | Tool | Notes |
| --- | --- | --- |
| Format, sections, import/export counts, symbols | `enigma_binary_audit` | Human-readable diagnostic output; analyzer set differs from `enigma_dump_functions`. Use `enigma_pipeline_audit` for individual import/export entries. |
| Function inventory | `enigma_dump_functions` | CSV on stdout; `--ghidra-compat` for `address,name`. |
| Instruction listing / single-address disassembly | `enigma_dump_listing` | CSV columns `funcEntry,addr,mnemonic,operands,bytes`; third positional argument prints 8 instructions. |
| C-like decompilation | `enigma_decompile_full` | Pseudocode; logs and `-time` go to stderr. |
| Analyzer timing / pipeline diagnostics | `enigma_pipeline_audit` | `--timeout N` per analyzer. |
| Naming coverage | `enigma_naming_audit` | Optional `--csv`. |
| Byte patch + export + verify | `enigma_patch_cli` | Writes a new file; prints `VERIFY OK` or `VERIFY FAIL`. |
| Ghidra project/table inspection | `enigma_gzf_inspect` | `.gbf`, `.rep` directory, or `.gzf`. |
| Ghidra project import + function decompile | `enigma_gzf_probe` | Diagnostic probe; noisy decompiler markup. |
| Function ID / fingerprints | `enigma_fks_*`, `enigma_fingerprint_audit` | FKS name lookup needs a local library and index; `enigma_fingerprint_audit` compares two binaries. |
| Cross-references, CFG, strings, data types, commits | Qt GUI or C++ API | No CLI equivalent. |

## Output handling

- `enigma_dump_functions`: CSV header `address,type,name`. Addresses are
  lowercase hex with `0x`.
- `enigma_dump_listing`: CSV header `funcEntry,addr,mnemonic,operands,bytes`.
  Commas inside operands are replaced with `;`. Rows are grouped by function,
  not globally sorted by address. Do not assume row order is execution order.
  Full mode writes the CSV to the named file; stdout is a one-line status
  message.
- `enigma_decompile_full`: concatenated C-like function bodies on stdout, no
  banner. `-o` writes the same text to a file. Diagnostics and `-time` go to
  stderr. Default `-max-func` is 200; default language is
  `x86:LE:64:default`; default base is `0x140001000` for a raw blob. PE, ELF,
  Mach-O, and COFF are auto-detected and the image base is inferred unless
  `-base` is supplied. Raw blobs use explicit `-lang`, `-base`, and `-entry`.
  The experimental `enigma_decompile` also accepts raw input with `-a`, `-b`,
  and `-base`; the inventory, listing, and audit tools require a recognized
  container.
- `enigma_binary_audit`: human-readable sections, import/export counts,
  symbols, and before/after analysis counts. It is a diagnostic, not a stable
  API. `enigma_pipeline_audit` lists individual imports and exports.
- `enigma_gzf_inspect`: table and metadata dump. Use `--table`, `--limit`,
  `--all`, `--chain`, `--program`, and `--filebytes` as documented by its help.
- `enigma_gzf_probe`: imported program summary, memory blocks, function list,
  optional function fields and decompilation. `--instr` only works after a
  non-option function name because the second argument is always treated as
  the function name.

## Advanced capabilities

### GUI

Menu paths present in the Qt GUI source include:

- `File > Open Binary...`, `Open Project...`, `Save Project`,
  `Browse Dyld Cache Images...`
- `Edit > Rename Function`, `Set Function Type / Signature...`, `Add Label...`,
  `Set Comment...`, `Add Bookmark...`, `Command Palette...`
- `View > Function Graph`, `Function Graph in New Window`, `Strings`,
  `Show Bytes`
- `Navigate > Show References (XRefs)...`, `Go to Address / Symbol...`,
  `Back`, `Forward`
- `Analysis > Auto Analyze`
- `Import > Import from Ghidra...`, `Data Types...`
- `Repository > Commit...`, `Commit History...`, `Create Branch...`,
  `Switch Branch...`
- `Patch > Export Patched Binary...`, `Show Patch List`, `Save Patches...`,
  `Load Patches...`, `Revert All Patches`

Use the GUI when the task needs interactive xrefs, graph navigation, structure
editing, string browsing, or project history. Do not claim these are available
headlessly.

### C++ API

The public headers are under `Enigma-Engine/src/include/`. The canonical minimal
loader/analysis harness is `Enigma-Engine/tools/enigma_dump_functions.cpp`.
Entry points present in the public headers include:

- `ghidra::createLoader()`, `BinaryLoader::load`, `populateProgram`
- `ghidra::AutoAnalysisManager`
- `ghidra::DecompInterface::openProgram`, `getFunctions`,
  `decompileFunction`, `disassembleAt`, `instructionLengthAt`
- `ghidra::FunctionManager::getFunctions`, `getFunctionAt`,
  `getFunctionContaining`
- `ghidra::Function::getEntryPoint`, `getBody`, `getParameters`,
  `getReturnType`, `getCalledFunctions`, `getCallingFunctions`
- `ghidra::ReferenceManager::getReferencesTo`, `getReferencesFrom`,
  `getFlowReferencesFrom`
- `cfg::DisassemblyCFG::build`, `blocks`, `edges`
- `ghidra::BinaryLoader::getImports`, `getExports`, `getSections`,
  `getSymbols`, `getRelocations`

Do not assume these APIs are ABI-stable or that a header exists in an installed
build. Compile against the same tree as the tools.

### Ghidra project import

```bash
enigma_gzf_inspect project.rep
enigma_gzf_inspect project.rep --table Program --limit 5
enigma_gzf_probe project.rep
enigma_gzf_probe project.rep fib
```

The importer reads Ghidra `.gzf`, `.rep` directories, and `.gbf` databases
natively; it does not require a Ghidra install or JVM. It reconstructs the
program model and can decompile imported functions. It is not a full fidelity
guarantee for every Ghidra feature.

### Function ID / FKS

FKS function-name lookup requires a local knowledge library:

```bash
# Build a library from a binary with useful names
enigma_fks_ingest library.bin library.fkslib --family mylib --compiler gcc --version 1.0

# Put .fkslib files in a directory, then build the LMDB index
enigma_fks_build_index /path/to/fid

# Point analysis at the index
ENIGMA_FKS_DIR=/path/to/fid enigma_dump_functions target.bin > functions.csv 2> functions.log
```

`FidAnalyzer` consults the FKS index when it exists and only renames
auto-generated names, with special handling for `entry`/`main`. There is no
public prebuilt signature database in this package. Treat matches as candidates
and verify them.

### Patching

```bash
copy target.bin target.work.bin
enigma_patch_cli target.work.bin 0x140001000 c3 90 target.patched.bin
```

The tool verifies the patched bytes at the mapped file offset and prints
`VERIFY OK` or `VERIFY FAIL`. It does **not** verify the supplied original bytes
against the input; confirm them from the listing or hex view first. A successful
byte write does not prove semantic correctness or that the file still runs.
Keep the original untouched.

### Project storage and history

Project save/load, commits, branches, and the LMDB index are exposed through the
C++ API (`Repository`, `WorkingSnapshot`, `CommitManager`, `BranchManager`,
`IndexManager`) and the GUI Repository menu. There is no CLI for these
operations in the verified tool set.

### Dyld shared cache

The GUI can browse dyld cache images (`File > Browse Dyld Cache Images...`).
The `BinaryLoader` API exposes `isDyldCache`, `getDyldCacheImages`,
`loadDyldCacheImage`, and `getDyldCacheImageBytes`. This is not a CLI workflow.

## Failure handling

| Symptom | Likely cause | Next check |
| --- | --- | --- |
| `Failed to load` | Unsupported/corrupt file or wrong path | Confirm format with `enigma_binary_audit`; check file size and magic. |
| `No SLEIGH specs found` | `ENIGMA_SLEIGH_DIR` not set | Point it at the compiled `.sla` tree; rerun from the expected root. |
| Empty or malformed CSV | Logs mixed into stdout | Re-run with `2>` to a separate log; do not use `2>&1` for data captures. |
| Address not found | Wrong image base, PIE, or raw default | Check `enigma_binary_audit` image base; use `-base` with `enigma_decompile_full` for a raw blob. |
| Noisy or truncated decompilation | Scope too large or analyzer timeout | Use `-entry` + `-max-func 1`; inspect `enigma_pipeline_audit` timings. |
| `VERIFY FAIL` | New bytes are not present in the exported file | Stop. Do not use the output. Recheck the address and file offset. |
| `export FAILED` | Address is outside the exported image or the write failed | Check the mapping; retry at a mapped address. Do not use a partial output. |
| FKS has no effect | Index missing or `ENIGMA_FKS_DIR` unset | Build the index with `enigma_fks_build_index`; confirm `index/lmdb` exists. |
| Ghidra probe cannot find function | Name mismatch or wrong program | List functions first; try `--program` on `enigma_gzf_inspect`. |

## Reporting template

```markdown
## Target
- Path / SHA-256 / size:
- Format / architecture / bitness / image base:
- Toolchain path / commit / date:

## Commands run
- ...

## Observed
- Entry point:
- Functions of interest:
- Imports / strings / data references:
- Disassembly evidence:
- Decompilation evidence:

## Inferred
- Hypothesis:
- Supporting evidence:
- Confidence: high / medium / low
- Alternative explanations:

## Not verified
- ...

## Reproduction
- ...
```

## References

- [Tool reference](references/tool-reference.md) — exact commands, flags, outputs, and quirks.
- [Analysis workflows](references/analysis-workflows.md) — step-by-step recipes for common tasks.
- [Limitations](references/limitations.md) — verified, unverified, planned, and unsupported capabilities.
- [Architecture overview](references/architecture-overview.md) — the condensed map of the engine; start here.
- [Full directory tree](references/engine-architecture.md) — the repository tree copied verbatim, for exact-path lookup only.
- [Worked example](examples/analysis-example.md) — a real PE analysis session with captured output.
