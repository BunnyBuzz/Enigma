# Analysis Workflows

These recipes assume the Enigma Engine tools are in `<tools>` and the target is
`<target>`. Use a scratch directory for outputs. Keep commands and logs with
your evidence.

## Workflow 0: Establish the evidence baseline

```bash
mkdir -p work
sha256sum <target> > work/target.sha256
<tools>/enigma_binary_audit <target> > work/audit.txt 2> work/audit.log
<tools>/enigma_dump_functions <target> > work/functions.csv 2> work/functions.log
```

Record:

- target path, SHA-256, size;
- tool path and repository commit;
- format, architecture, bitness, image base, entry point;
- the exact command line and output files.

If the target is untrusted, do not execute it. Static analysis is the default.

## Workflow A: Triage an unknown binary

### A1. Identify the container

Run `enigma_binary_audit` and read the first section. It reports PE, ELF,
Mach-O, or another loaded format, plus architecture and bitness. Confirm the
entry point and image base.

Check for:

- executable sections and their address ranges;
- import/export counts (use `enigma_pipeline_audit` for individual entries
  grouped by library);
- exports (DLLs) and symbol counts;
- unusual section names or writable/executable sections.

### A2. Inventory functions

```bash
<tools>/enigma_dump_functions <target> > work/functions.csv 2> work/functions.log
```

Sort by address for navigation:

```bash
sort -t, -k1,1 work/functions.csv > work/functions.sorted.csv
```

Do not overwrite the original CSV; it is evidence.

Look for:

- the `entry` row;
- `main`, `DllMain`, `WinMain`, or exported names;
- known library names;
- clusters of auto-named `func_0x...` addresses;
- functions whose addresses fall outside executable sections (a warning sign).

### A3. Choose a drill-down target

Good first targets:

1. The entry point.
2. A recognized `main` or application root.
3. An exported function.
4. A function called by an import-adjacent wrapper.
5. A function with many callers.

Record why you chose it.

### A4. Check naming coverage

```bash
<tools>/enigma_naming_audit <target> --csv work/naming.csv > work/naming.txt 2> work/naming.log
```

Use the report to see how much of the binary is auto-named and which repeated
unnamed signatures exist. This is a measure of the current analyzer set, not a
ground-truth label.

## Workflow B: Deep-dive one function

### B1. Disassemble

```bash
<tools>/enigma_dump_listing <target> work/unused.csv 0xADDR > work/func.disasm 2> work/func.disasm.log
```

The third positional argument prints eight instructions. For a longer view, use
the CSV listing:

```bash
<tools>/enigma_dump_listing <target> work/listing.csv 2> work/listing.log
```

Then filter by `funcEntry` or address. Remember that rows are grouped by
function and are not globally address-sorted.

### B2. Decompile the same address

```bash
<tools>/enigma_decompile_full -entry 0xADDR -max-func 1 -o work/func.c <target> 2> work/func.decompile.log
```

Use `-no-crt` if the function is a CRT/library body that is suppressed by
default. Use `-raw-types` if you need to see `undefinedN` types rather than
normalized `uintN_t`.

### B3. Compare listing and pseudocode

For each basic block, check:

- prologue and stack allocation;
- argument registers and stack arguments;
- direct calls and their targets;
- global/data references;
- branch conditions and loop structure;
- return value and epilogue;
- any inlined callee (the decompiler may not emit a call).

If the pseudocode shows a call that the listing does not, or vice versa, stop
and reconcile before drawing conclusions.

### B4. Identify the function's role

Collect evidence from:

- imported APIs it calls (file, network, registry, crypto, memory, process);
- strings it references;
- callers and callees;
- constants and error codes;
- structure of its loops and branches.

State a hypothesis and the evidence for it. Distinguish "this function calls
`CreateFileW`" (observed) from "this function writes a configuration file"
(inferred).

## Workflow C: Understand the program

### C1. Map the startup chain

Start at `entry` and follow calls. On Windows, expect CRT startup and then
`main`/`WinMain`. On Linux, expect `_start`, `__libc_start_main`, and `main`.
The decompiler may inline startup helpers; use the listing to confirm calls.

### C2. Group imports by capability

Use `enigma_binary_audit` for import/export counts, and `enigma_pipeline_audit`
for the individual entries. Group by library and by behavior:

- file and directory access;
- process/thread creation;
- memory allocation and protection;
- network and DNS;
- registry and services;
- cryptography and hashing;
- UI and graphics;
- error/logging.

This gives a capability map without executing the binary.

### C3. Find application-level roots

Use recognized names, exports, string references, and call-graph centrality.
`main` recognition is heuristic. Verify a candidate by checking its callers and
the APIs it uses.

### C4. Build a call graph

There is no CLI call-graph exporter. Use one of:

- the GUI Function Graph for a single function;
- decompiled call sites plus the listing;
- the C++ API (`Function::getCalledFunctions`, `getCallingFunctions`,
  `ReferenceManager`).

A decompiler call graph is not the same as a complete xref database. Say which
source you used.

### C5. Inspect strings and data

Use the GUI String Table (`View > Strings`) for interactive work. In headless
mode, use the listing and decompiled references to string addresses. Confirm the
bytes in the Hex view or with a small read of the binary; do not trust a string
label alone.

## Workflow D: Cross-references and control-flow graphs

### D1. GUI path

1. Open the binary.
2. Navigate to the address or function.
3. `Navigate > Show References (XRefs)...` to see references to/from the
   current location.
4. `View > Function Graph` for the current function's basic-block graph.
5. `View > Function Graph in New Window` for a separate graph window.
6. Double-click a node or reference to navigate; views synchronize selection.

### D2. C++ path

The headers are under `Enigma-Engine/src/include/`.

**Cross-references**

```cpp
#include <ghidra/ReferenceManager.h>
#include <ghidra/Reference.h>

ghidra::ReferenceManager* rm = program->getReferenceManager();
for (ghidra::Reference* r : rm->getReferencesTo(addr)) {
    std::cout << "from 0x" << std::hex << r->getFromAddress().getOffset()
              << " to 0x" << r->getToAddress().getOffset()
              << " op=" << std::dec << r->getOperandIndex()
              << " primary=" << r->isPrimary() << "\n";
}

for (ghidra::Reference* r : rm->getFlowReferencesFrom(addr)) {
    std::cout << "flow 0x" << std::hex << r->getToAddress().getOffset() << "\n";
}
```

**Control-flow graph**

```cpp
#include <cfg/DisassemblyCFG.h>

std::vector<cfg::CfgInsn> insns;
// Fill address, row, length, mnemonic, and operands from the listing/model.
cfg::DisassemblyCFG graph;
graph.build(insns, {functionEntry});

for (const cfg::CfgBlock& block : graph.blocks()) {
    std::cout << "block " << block.index
              << " 0x" << std::hex << block.startAddr
              << "-0x" << block.endAddr << "\n";
}

for (const cfg::CfaEdge& edge : graph.edges()) {
    std::cout << "edge 0x" << std::hex << edge.fromAddr
              << " -> 0x" << edge.toAddr
              << " " << cfg::edgeKindName(edge.kind) << "\n";
}
```

The CFG builder classifies flow from mnemonics and resolves direct targets from
operand text. Indirect targets become `Computed` or `ComputedCall` edges with
`toAddr == 0`. Do not treat an unresolved edge as a missing branch.

### D3. If neither path is available

Report that xrefs/CFG were not independently enumerated. Do not present a
decompiler call list as a complete xref result.

## Workflow E: Import a Ghidra project

### E1. Inspect the project

```bash
<tools>/enigma_gzf_inspect project.rep
<tools>/enigma_gzf_inspect project.rep --table Program --limit 5
```

For a multi-program project, use `--program NAME`. For a single database, pass
the `.gbf` or `.gzf` path.

### E2. Probe the imported program

```bash
<tools>/enigma_gzf_probe project.rep > work/probe.txt 2> work/probe.log
```

This lists the imported program, memory blocks, and functions. To decompile a
named function:

```bash
<tools>/enigma_gzf_probe project.rep fib > work/fib.txt 2> work/fib.log
```

To inspect an address after naming a function:

```bash
<tools>/enigma_gzf_probe project.rep fib --instr 0x1014c0
```

The `--instr` option only works after a non-option function name because the
second argument is always treated as the function name.

### E3. Continue analysis

The import reconstructs the program model and can decompile functions. It is not
a promise that every Ghidra feature, comment, or data type survived. Record
which program and tables you inspected.

## Workflow F: Compare builds and function identity

### F1. Fingerprint comparison

```bash
<tools>/enigma_fingerprint_audit old.bin new.bin --csv work/fingerprints.csv > work/fingerprints.txt 2> work/fingerprints.log
```

Use it to compare fingerprint quality and candidate matches. It is not a
semantic diff and does not prove that two functions are identical.

### F2. Build an FKS library

```bash
<tools>/enigma_fks_ingest library.bin work/fid/library.fkslib --family mylib --compiler gcc --version 1.0
<tools>/enigma_fks_build_index work/fid
ENIGMA_FKS_DIR=work/fid <tools>/enigma_dump_functions target.bin > work/functions.csv 2> work/functions.log
```

Check that `work/fid/index/lmdb` exists. `FidAnalyzer` only renames
auto-generated functions; a match is a candidate. Verify the body and call
sites before accepting a name.

## Workflow G: Patch and verify

### G1. Copy and hash

```bash
cp <target> work/target.work.bin
sha256sum <target> work/target.work.bin
```

### G2. Confirm the original bytes

Use the listing or Hex view to confirm the bytes at the virtual address. Then:

```bash
<tools>/enigma_patch_cli work/target.work.bin 0xADDR c3 90 work/target.patched.bin
```

The tool records `orig_hex` but does **not** check it against the input. Confirm
the bytes yourself, then apply `new_hex`. The tool exports and verifies the new
bytes at the mapped file offset. Require `VERIFY OK`.

### G3. Record the result

- original and patched SHA-256;
- virtual address and file offset;
- original and new bytes, and where the original bytes were confirmed;
- tool output;
- what was **not** verified (runtime behavior, checksums, relocations).

Never overwrite the original. A byte-level `VERIFY OK` is not a runtime test.

## Workflow H: Interactive GUI session

Use the GUI when the task needs visual navigation or editing:

1. `File > Open Binary...` or `Open Project...`.
2. `Analysis > Auto Analyze` if the project is not already analyzed.
3. Use the Function Explorer to select a function.
4. Use `Navigate > Show References (XRefs)...` for callers/callees.
5. Use `View > Function Graph` for basic blocks.
6. Use `View > Strings` for string browsing.
7. Use `Edit > Rename Function`, `Set Function Type / Signature...`,
   `Add Label...`, `Set Comment...`, and `Add Bookmark...` to annotate.
8. Use `Import > Data Types...` for the structure/union editor.
9. Use `Repository > Commit...` and branch actions for project history.
10. Use `Patch > Export Patched Binary...` only after reviewing the patch list.

The GUI is the only verified path for interactive xrefs, graphs, structure
editing, string browsing, and commit history. Do not claim those operations were
performed if you only ran CLI tools.

## Workflow I: Automate with the C++ API

Use the C++ API when you need a repeatable batch operation that the CLI does not
expose.

1. Start from `Enigma-Engine/tools/enigma_dump_functions.cpp` for loader,
   address-space, analyzer, and `DecompInterface` setup.
2. Add your operation using the headers in `Enigma-Engine/src/include/`.
3. Compile against the same tree and link the `enigma_engine` target.
4. Keep the helper in a scratch directory; do not modify the engine or its
   build configuration for a one-off analysis.

Verified API surfaces are listed in `references/tool-reference.md`. Do not
assume ABI stability or invent methods.

## Workflow J: Write the report

Use the template in `SKILL.md`. At minimum:

- target identity and hashes;
- toolchain and commands;
- observed facts with addresses;
- inferred behavior with confidence and alternatives;
- negative results;
- limitations and unverified claims;
- reproduction steps.

A good report lets another analyst rerun the commands and reach the same
observations, even if they disagree with the interpretation.
