<img width="1920" height="1016" alt="image" src="https://github.com/user-attachments/assets/37b4675f-adbf-4fb0-aeaf-f57baecb910f" />
<img width="1920" height="1015" alt="image" src="https://github.com/user-attachments/assets/bd59ddd8-6ff2-4241-b960-f97984a1d529" />


# Enigma Engine

A native C++ reverse-engineering engine inspired by Ghidra's analysis pipeline.

Enigma removes the JVM dependency and provides a standalone analysis core that can be embedded, extended, and integrated directly with native tools and AI systems.

---

## Current State

Enigma is under active development and already has a functional end-to-end analysis pipeline.

### Analysis Engine

* PE and ELF binary loading
* x86/x64 disassembly with Capstone
* Pcode generation using Ghidra's native decompiler library
* Function detection with ~97% recall on tested Windows binaries
* C decompilation
* Type recovery with Windows API signatures (1400+ prototypes)
* Symbols, references, functions, types, and memory model
* Analysis pipeline with 139 registered analyzers
* Ghidra `.gzf` import path
* Project persistence using FlatBuffers + LMDB with git-like commits and branches

### GUI

* Interactive disassembly
* Hex viewer and patching
* Decompiler
* Inline control-flow visualization
* Call Graph
* Cross-reference exploration
* Symbol and function navigation
* Cross-view synchronization between Disassembly, Decompiler, and Hex
* Function and symbol renaming

The core pipeline is stable, and the current work focuses on expanding feature coverage, improving engine/GUI integration, and closing remaining capability gaps identified during Ghidra 12.1.3 parity testing.

---

## Architecture

```text
Binary (PE / ELF)
        │
        ▼
Binary Loader
        │
        ▼
Capstone Disassembler
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
| Binary loaders                  | Native Enigma implementation         |
| Storage                         | Native Enigma implementation         |
| GUI                             | Native Qt6 implementation            |

Enigma uses Ghidra components where they provide the required low-level analysis technology, while the surrounding engine architecture is implemented natively in C++.

---

## Building

### Requirements

* C++17 or newer
* CMake 3.20+
* Ninja
* Qt 6
* Capstone
* LMDB

### Build

```bash
git clone https://github.com/adam-040/Enigma.git
cd Enigma/enigma-engine

cmake -B build -G Ninja -DCMAKE_BUILD_TYPE=Release
cmake --build build
```

---

## Project Status

Enigma is no longer only a prototype analysis core. The native pipeline, storage layer, analysis systems, and GUI are operational.

Current development is focused on **expanding the engine's capabilities and connecting functionality that already exists in the backend to the GUI**, while implementing the remaining gaps identified during parity analysis.

---

## License

This project is licensed under the **Apache License 2.0**.

Third-party components used by Enigma remain subject to their respective licenses.
