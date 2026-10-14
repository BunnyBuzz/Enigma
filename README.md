<img width="1920" height="1015" alt="image" src="https://github.com/user-attachments/assets/0423f341-b101-4f81-aef0-7def8af5df61" />
<img width="1920" height="1020" alt="image" src="https://github.com/user-attachments/assets/fda40f45-f793-4cc4-83fb-b3359d0af933" />
<img width="1920" height="1014" alt="image" src="https://github.com/user-attachments/assets/5be083d7-5167-44a0-8c39-98075d4f4ab6" />



# Enigma Engine

A native C++ reverse-engineering engine inspired by Ghidra's analysis pipeline.

Enigma removes the JVM dependency and provides a standalone analysis core that can be embedded, extended, and integrated directly with native tools and AI systems.

---

## Current State

Enigma is under active development and already has a functional end-to-end analysis pipeline.

### Analysis Engine

* PE, ELF (32/64-bit, LE/BE, stripped binaries via program headers), Mach-O (incl. fat/universal), COFF objects/archives, and Ghidra `.gzf`/`.rep` import path
* Multi-arch disassembly (x86/x64, ARM32, AArch64, MIPS incl. 16e variants, PowerPC) via Capstone + compiled SLEIGH specs
* Pcode generation using Ghidra's native decompiler library
* Function detection audited against Ghidra 12.1.3 headless: 100% instruction-level semantic parity (0 mnemonic / 0 operand mismatches) on all small fixtures across x86-64, ARM, AArch64, MIPS, and PPC; 2856 shared functions / 116k+ semantic matches on a large x86-64 binary
* C decompilation with per-function parity harness (function-set, naming, success, signature, callee-set, and text-similarity metrics vs Ghidra 12.1.3; zero `halt_baddata` on all fixtures)
* Type recovery with Windows API signatures (1400+ prototypes), glibc/Linux prototypes, and noreturn tables (Linux/Mac/Windows)
* Symbols, references, functions, types, and memory model
* Analysis pipeline with 142 registered analyzers
* Project persistence using FlatBuffers + LMDB with git-like commits and branches

### GUI

* Interactive disassembly (incl. data-section banners + hex/ASCII dumps)
* Hex viewer and patching
* Decompiler (incl. string-literal resolution, equate names, advanced comments)
* Inline control-flow visualization
* Function Graph window (zoomable basic-block flowchart) + Call Graph
* Cross-reference exploration
* Symbol and function navigation
* Cross-view synchronization between Disassembly, Decompiler, and Hex
* Function and symbol renaming

The core pipeline is stable (78/78 CTest suites green), and the current work focuses on expanding feature coverage, improving engine/GUI integration, and closing remaining capability gaps identified during Ghidra 12.1.3 parity testing.

---

## Architecture

```text
Binary (PE / ELF / Mach-O / COFF)
        │
        ▼
Binary Loader
        │
        ▼
Capstone + SLEIGH Disassembly
        │
        ▼
Pcode / Decompiler Engine
        │
        ▼
Analysis Pipeline
        │
        ├── Function Detection
        ├── Type Recovery
        ├── Symbols
        ├── References
        └── Other Analyses
        │
        ▼
Program Model
        │
        ├── Functions
        ├── Symbols
        ├── Types
        ├── Memory
        └── References
        │
        ▼
Storage
        │
        ├── FlatBuffers snapshots
        ├── LMDB index
        └── Git-like commits / branches
        │
        ▼
Qt GUI
        │
        ├── Disassembly
        ├── Decompiler
        ├── Hex View
        ├── CFG / Call Graph
        └── Explorers
```

---

## Original Work vs. Ghidra Components

| Component                       | Source                               |
| ------------------------------- | ------------------------------------ |
| Decompiler engine               | Ghidra native C++ decompiler library |
| Sleigh processor specifications | Ghidra                               |
| Program model                   | Native Enigma C++ implementation     |
| Type and memory systems         | Native Enigma C++ implementation     |
| Analysis pipeline               | Native Enigma C++ implementation     |
| Function detection              | Native Enigma implementation         |
| Binary loaders                  | Native Enigma implementation (PE/ELF/Mach-O/COFF) |
| Storage                         | Native Enigma implementation         |
| GUI                             | Native Qt6 implementation            |

Enigma uses Ghidra components where they provide the required low-level analysis technology, while the surrounding engine architecture is implemented natively in C++.

---

## Building

### Requirements

* C++17 or newer
* CMake 3.16+
* Ninja (backend) or MSYS Makefiles (GUI), MinGW64 g++ via MSYS2
* Capstone
* LMDB
* SQLite3
* FlatBuffers + `flatc`
* zlib
* Python3 (CLI regression tests)
* Qt 6 (Widgets, Core, Gui — GUI only; Qt-Advanced-Docking-System is fetched automatically via CMake FetchContent)

### Build

```bash
git clone https://github.com/adam-040/Enigma.git
cd Enigma/Enigma-Engine

cmake -B build -G Ninja -DCMAKE_BUILD_TYPE=Release
cmake --build build
ctest --test-dir build --output-on-failure
```

---

## Project Status

Enigma is no longer only a prototype analysis core. The native pipeline, storage layer, analysis systems, and GUI are operational (78/78 CTest suites green).

Current development is focused on **expanding the engine's capabilities and connecting functionality that already exists in the backend to the GUI**, while closing the remaining gaps identified during Ghidra 12.1.3 disassembler/decompiler parity audits (see `PLAN/`).

---

## License

This project is licensed under the **Apache License 2.0**.

Third-party components used by Enigma remain subject to their respective licenses.
