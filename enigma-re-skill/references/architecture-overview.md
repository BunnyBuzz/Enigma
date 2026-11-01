# Architecture Overview

This is the working map of the Enigma Engine repository. It condenses the
8,356-line directory dump in `engine-architecture.md` into the parts that matter
for analysis work. The full tree is kept for exact-path lookup; you should not
need to read it end to end.

Counts and paths below were taken from the tree at packaging time. Re-check them
against your checkout before relying on a specific file.

## Why the tree is large

`engine-architecture.md` contains 8,351 tree entries. Most are generated build
output, vendored dependencies, packaged runtime files, or signature data:

| Area | Entries | What it is |
| --- | ---: | --- |
| `build/` | 3,525 | CMake/Ninja output, object files, `_deps` (nlohmann_json), compiler probes |
| `src/` | 2,726 | engine library, vendored decompiler, GUI, compatibility headers |
| `sleigh/` | 699 | processor specifications and compiled `.sla` files |
| `fid/` | 472 | FKS `.fkslib` signature libraries (data, not source) |
| `dist/` | 435 | packaged runtime: `enigma_gui.exe`, Qt/Capstone DLLs, SLEIGH data |
| `tests/` | 328 | unit/integration tests, corpus, Ghidra headless projects |
| `tools/` | 115 | CLI entry points and analysis scripts |
| other | 51 | schemas, test binaries, root artifacts, `build_asan/`, `Testing/` |

The engine's own source is concentrated in `src/`, `tools/`, `sleigh/`,
`schemas/`, and `tests/`. Ignore `build/`, `build_asan/`, `dist/`, and `fid/`
when you are trying to understand code.

## One-screen mental model

```text
          CLI tools              Qt GUI              C++ API
       (tools/*.cpp)          (src/gui/)       (src/include/ghidra/)
                \                 |                 /
                 +----------------+----------------+
                                  |
                    +-------------v-------------+
                    |  ProgramDB / program model |
                    |  memory, listing, symbols, |
                    |  functions, types, refs,   |
                    |  blocks, addresses         |
                    +------+--------------+------+
                           |              |
       loaders + analyzers |              | disassembly + decompilation
       (src/core,          |              | (sleigh/, src/pcode/,
        src/import)        |              |  src/decompiler/)
                           |              |
                    +------v--------------v------+
                    | input: PE, ELF, Mach-O,   |
                    | COFF, raw blob, Ghidra    |
                    | project, FKS library      |
                    +---------------------------+
```

The engine is a Ghidra-shaped C++17 program database. A loader turns a file into
memory blocks and metadata; analyzers, disassembly, and decompilation enrich
that database; the CLI, GUI, and C++ headers read it; FlatBuffers/LMDB storage
and Ghidra/FKS import provide persistence and signatures.

## Layers

| Layer | Main locations | Role |
| --- | --- | --- |
| Interfaces | `tools/`, `src/gui/`, `src/include/ghidra/` | CLI commands, Qt6 desktop views, Ghidra-compatible C++ API |
| Loaders | `src/core/BinaryLoader.cpp`, `src/core/*Analyzer.cpp` | detect PE/ELF/Mach-O/COFF/firmware containers; build memory blocks and metadata |
| Program model | `src/program/`, `src/address/`, `src/listing/`, `src/symbol/`, `src/function/`, `src/types/`, `src/memory/`, `src/block/` | addresses, instructions/data, symbols, functions, data types, references, basic blocks |
| Analysis | `src/core/AutoAnalysisManager.cpp`, `AnalysisScheduler.cpp`, `AnalysisTaskList.cpp`, `AnalysisBridge.cpp` | schedule analyzers that discover functions, names, references, types, and signatures |
| Disassembly | `sleigh/`, `src/core/Disassembler.cpp`, `src/pcode/PcodeCapstoneMapper.cpp`, `src/cfg/` | decode instructions, lift to p-code, build control-flow graphs |
| Decompilation | `src/decompiler/`, `src/core/DecompilerAdapter.cpp`, `src/core/DecompInterface.cpp`, `src/pcode/EnigmaPipeline.cpp` | produce C-like pseudocode from p-code |
| Persistence and import | `src/storage/`, `src/import/`, `schemas/` | snapshots, LMDB index, commits/branches, Ghidra `.rep`/`.gzf`/`.gbf` import |
| Patching | `src/core/patch/` | byte, instruction, metadata, NOP-fill, string, and code-cave patches |
| Tests | `tests/` | unit/integration tests, corpus, Ghidra headless projects |

## Data flow

1. **Load.** `BinaryLoader` reads the container. A format analyzer
   (`PortableExecutableAnalyzer`, `ElfAnalyzer`, `MachoAnalyzer`,
   `CoffAnalyzer`, and firmware/embedded analyzers) creates memory blocks,
   sections, imports, exports, and entry metadata.
2. **Model.** `ProgramDB` owns the program. Address spaces and sets live in
   `src/address/`; instructions and data in `src/listing/`; symbols, references,
   and functions in `src/symbol/` and `src/function/`; data types in
   `src/types/`; basic-block models in `src/block/`.
3. **Analyze.** `AutoAnalysisManager` registers analyzers and
   `AnalysisScheduler` runs them. Analyzer families cover entry points,
   function starts and bodies, thunks, stack variables, constant propagation,
   data references, RTTI, DWARF/PDB, demangling, and architecture-specific
   recovery.
4. **Disassemble.** SLEIGH specifications in `sleigh/` decode instructions.
   `Disassembler` and `SleighLanguage` produce p-code; `PcodeCapstoneMapper`
   provides a Capstone-backed path. `DisassemblyCFG` and `FunctionGraphLayout`
   build blocks and edges.
5. **Decompile.** The full CLI (`enigma_decompile_full`) drives the vendored
   Ghidra C++ decompiler through `libdecomp` and `PrintC`, with `ProgramDB`
   bridging. The smaller `enigma_decompile` tool uses the native
   `EnigmaPipeline` path. Both emit C-like pseudocode, not original source.
6. **Persist or import.** FlatBuffers schemas in `schemas/` define program,
   project, changeset, commit, and FKS records. `src/storage/` provides
   snapshots, an LMDB index, commits, branches, and FKS lookup. `src/import/`
   reads Ghidra projects and GZF/GBF data.
7. **Expose.** CLI tools print text or CSV; the Qt GUI renders synchronized
   disassembly, decompiler, hex, function, xref, graph, string, type, and patch
   views; C++ callers use the headers under `src/include/ghidra/`.

## Core components

### Interfaces

- **CLI:** `tools/enigma_*.cpp`. The verified analysis commands are
  `enigma_decompile_full`, `enigma_decompile`, `enigma_dump_functions`,
  `enigma_dump_listing`, `enigma_binary_audit`, `enigma_pipeline_audit`,
  `enigma_naming_audit`, `enigma_patch_cli`, `enigma_fingerprint_audit`,
  `enigma_gzf_inspect`, `enigma_gzf_probe`, and the `enigma_fks_*` tools.
- **GUI:** `src/gui/`. `MainWindow` wires the docks; the main views are
  `DisassemblyFieldView`/`DisassemblyModel`, `DecompilerView`, `HexView`,
  `FunctionExplorer`, `CrossReferenceExplorer`, `FunctionGraphView`/
  `FunctionGraphWindow`, `StructureEditorWidget`, `StringTableWidget`,
  `PatchListWidget`, and `AddressMinimap`.
- **C++ API:** `src/include/ghidra/` is the Ghidra-compatible surface
  (roughly 1,200 header entries, including subdirectories for `block`,
  `correlate`, `import`, `patch`, `pcode`, `program`, `storage`, and `util`).
  `src/include/cfg/` holds the CFG headers. This is a source-level surface, not
  a stable binary ABI.

### Loaders and format support

- `src/core/BinaryLoader.cpp` is the entry point for container detection.
- Format analyzers live beside it: `PortableExecutableAnalyzer.cpp`,
  `ElfAnalyzer.cpp`, `MachoAnalyzer.cpp`, `CoffAnalyzer.cpp`, and
  `CoffArchiveAnalyzer.cpp`.
- Firmware and embedded formats have dedicated analyzers, including Android
  boot images, Apple images, DMG, Ext4, FDT/DTB, PEF, and various boot formats.
- Raw blobs are accepted by `enigma_decompile_full` with explicit `-lang`,
  `-base`, and `-entry`, and by the experimental `enigma_decompile` with
  `-a`, `-b`, and `-base`; the inventory and audit tools require a recognized
  container.

### Program model

- `src/program/ProgramDB.cpp` is the central database. It ties together
  memory, listing, symbols, functions, data types, references, equates,
  properties, and change sets.
- `src/address/` provides address spaces, ranges, sets, and iterators.
- `src/listing/` provides instructions, data, comments, and code units.
- `src/symbol/` provides symbols, functions, namespaces, references, thunks,
  and function signatures.
- `src/function/` provides the function and variable implementations.
- `src/types/` is the data-type system: integers, floats, pointers, arrays,
  structures, unions, enums, typedefs, strings, and many format-specific types.
- `src/memory/` and `src/core/Memory.cpp` provide byte buffers and memory
  blocks. `src/block/` provides basic-block and subroutine models.

### Analysis

- `AutoAnalysisManager` is the registry and lifecycle owner;
  `AnalysisScheduler` executes queued work; `AnalysisTaskList` groups tasks by
  phase; `AnalysisBridge` connects analysis to the decompiler.
- Function recovery is spread across `EntryPointAnalyzer`,
  `FunctionStart*Analyzer`, `FunctionDiscoveryAnalyzer`,
  `FunctionBodyFinalizer`, `AggressiveRecoveryAnalyzer`, and
  `SharedReturn*Analyzer`.
- Naming and signature work is in `NamingService`, `FidAnalyzer`,
  `ApplyKnownSignatureAnalyzer`, `KnownFunctionHashes`, and the GNU, Microsoft,
  Rust, and Swift demanglers.
- Type and reference recovery is in `ConstantPropagationAnalyzer`,
  `StackVariableAnalyzer`, `DataOperandReferenceAnalyzer`,
  `OperandReferenceAnalyzer`, `RttiAnalyzer`, `DWARFAnalyzer`, and
  `PdbAnalyzer`.
- Decompiler-driven analyzers include `DecompilerFunctionAnalyzer`,
  `DecompilerSwitchAnalyzer`, and `DecompilerCallConventionAnalyzer`.

### Disassembly and CFG

- `sleigh/` contains the processor specifications: x86, ARM, AArch64, MIPS,
  PowerPC, RISC-V, 6502, 68000, 8051, Dalvik, JVM, and others (about 38
  specification directories).
- `Sleigh`, `SleighLanguage`, `SleighLanguageProvider`, and `Disassembler`
  decode instructions and lift them to p-code.
- `PcodeCapstoneMapper` and `EnigmaPipeline` provide a Capstone-backed native
  path; this is supporting code, not the primary verified decompiler path.
- `src/cfg/DisassemblyCFG.cpp` builds basic blocks and edges;
  `src/cfg/FunctionGraphLayout.cpp` computes graph layout for the GUI.
- There is no dedicated xref or CFG CLI. Use the GUI or the C++ API.

### Decompilation

- `src/decompiler/` is the vendored Ghidra C++ decompiler: actions, heritage,
  rules, type recovery, jump-table recovery, and the `PrintC`/`PrintJava`
  printers. It is built as the separate `decompiler` library.
- `src/core/DecompilerAdapter.cpp` and `DecompInterface.cpp` bridge the engine's
  `ProgramDB` to that decompiler for the GUI and C++ callers.
- `enigma_decompile_full` drives the decompiler directly (`libdecomp`,
  `printc`) and applies `ProgramDB` bridging, CRT filtering, string resolution,
  and call-site type application. It is the verified full-decompiler CLI.
- `src/pcode/EnigmaPipeline.cpp` is the smaller native pipeline used by
  `enigma_decompile`; it loads a raw file, runs SLEIGH, builds a `Funcdata`, and
  prints with `PrintC`.
- Output is C-like pseudocode. Names, types, signatures, and boundaries are
  inferred; do not present them as recovered source.

### Persistence, import, and signatures

- `schemas/program.fbs`, `project.fbs`, `changeset.fbs`, `commit.fbs`, and
  `fks.fbs` define the on-disk records.
- `src/storage/Repository.cpp`, `WorkingSnapshot.cpp`, `CommitManager.cpp`,
  `BranchManager.cpp`, and `IndexManager.cpp` implement snapshots, commits,
  branches, and the LMDB-backed index.
- `src/import/GzfProgramImporter.cpp`, `RepProject.cpp`, `GbfReader.cpp`, and
  `ZipArchive.cpp` read Ghidra projects and GZF/GBF data.
- `src/core/FidAnalyzer.cpp`, `FksLibrary.cpp`, `FunctionFingerprint.cpp`, and
  `FidHasher.cpp` implement FKS signature matching. `src/storage/FksRepository.cpp`
  and `FksIndexManager.cpp` manage the libraries and index.
- `fid/` contains the shipped `.fkslib` data. It is input data, not engine
  source.

### Patching

- `src/core/patch/PatchManager.cpp` coordinates active patches and export.
- Patch types include `BytePatch`, `InstructionPatch`, `MetadataPatch`,
  `NopFillPatch`, and `StringPatch`; `CodeCaveAllocator` finds space,
  `PatchConflictDetector` checks overlaps, and `PatchMemory` applies changes.
- `enigma_patch_cli` is the verified byte-patch path. The GUI exposes patches
  through `PatchListWidget`.

### Build and tests

- CMake builds `decompiler` (static library), `enigma_engine` (library),
  optional `enigma_gui` (`ENABLE_GUI`), the CLI tools, and the test binaries.
- Dependencies include Capstone, SQLite3, LMDB, FlatBuffers, nlohmann_json,
  zlib, Qt6 (Widgets, Concurrent, Svg), bcrypt, and `dbghelp`.
- `tests/` covers loaders, ELF PLT/GOT, Mach-O, COFF, GZF import, FKS,
  disassembly CFG, function graphs, patching, storage, and a GUI smoke test.
  `tests/corpus/` and `tests/headless_proj/` hold regression inputs and Ghidra
  projects.
- `dist/` is a packaged runtime, not source. `build/` and `build_asan/` are
  generated.

## Where to look

| Task | Start here |
| --- | --- |
| Add or change a container format | `src/core/BinaryLoader.cpp`, the matching `src/core/*Analyzer.cpp`, `src/include/ghidra/BinaryLoader.h` |
| Change function discovery or boundaries | `src/core/EntryPointAnalyzer.cpp`, `FunctionStart*Analyzer.cpp`, `FunctionDiscoveryAnalyzer.cpp`, `FunctionBodyFinalizer.cpp` |
| Change decompiler output | `src/decompiler/printc.cc`, `src/decompiler/CFormatter.cpp`, `tools/enigma_decompile_full.cpp` |
| Add a CLI command | `tools/`, `Enigma-Engine/CMakeLists.txt` |
| Add or change a GUI view | `src/gui/`, especially `MainWindow.cpp` |
| Change persistence | `schemas/*.fbs`, `src/storage/` |
| Change Ghidra import | `src/import/` |
| Change signature matching | `src/core/FidAnalyzer.cpp`, `src/storage/Fks*` |
| Change patching | `src/core/patch/` |
| Verify behavior | `tests/`, especially the matching `test_*.cpp` |

## Boundaries and caveats

- `src/decompiler/` is vendored/derived Ghidra code, not Enigma-original code.
  Treat its behavior as inherited and verify it in this build.
- `src/pcode/` is the supporting native pipeline. The verified full-decompiler
  CLI is `enigma_decompile_full`, not `enigma_decompile`.
- `src/include/ghidra/` is a source-level compatibility surface. It is not a
  promise of ABI stability or of Ghidra parity.
- `dist/`, `fid/`, and `build*/` are artifacts. Do not edit them to change
  engine behavior; change `src/`, `tools/`, or `sleigh/` instead.
- GUI menu paths and C++ APIs in this package were source-inspected, not
  exercised headlessly. CLI behavior was live-verified for the commands in
  `tool-reference.md`.
- There is no MCP server, JSON output mode, Python binding, or stable plugin
  ABI in the verified tree.
