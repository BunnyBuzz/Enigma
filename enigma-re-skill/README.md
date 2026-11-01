# Enigma Reverse Engineering — Agent Skill

A portable, documentation-only agent skill for evidence-driven reverse
engineering with the Enigma Engine toolchain.

The skill teaches an AI agent how to:

- triage PE, ELF, Mach-O, and COFF binaries;
- inventory functions and disassemble targeted addresses;
- decompile functions to C-like pseudocode, including raw blobs with explicit
  language, base, and entry;
- inspect cross-references and control-flow graphs through the GUI or C++ API;
- import Ghidra projects, compare builds, and build optional FKS libraries;
- patch bytes in a copy and verify the exported result;
- report findings without overstating what the engine can prove.

It is intentionally explicit about what is verified, what is implemented but
unverified, what is planned, and what is unavailable.

## Contents

```text
enigma-reverse-engineering/
├── SKILL.md
├── README.md
├── references/
│   ├── analysis-workflows.md
│   ├── architecture-overview.md
│   ├── engine-architecture.md
│   ├── limitations.md
│   └── tool-reference.md
└── examples/
    └── analysis-example.md
```

- `SKILL.md` — the agent-facing instructions, with YAML frontmatter.
- `references/tool-reference.md` — exact CLI commands, flags, outputs, GUI
  actions, and C++ API surfaces.
- `references/analysis-workflows.md` — step-by-step recipes and evidence
  checkpoints.
- `references/limitations.md` — capability status and claims to avoid.
- `references/architecture-overview.md` — a condensed, task-oriented map of the
  engine's layers, data flow, and core components.
- `references/engine-architecture.md` — the repository's directory tree, copied
  verbatim for exact-path lookup.
- `examples/analysis-example.md` — a real PE analysis session with captured
  output.

## Requirements

- A built Enigma Engine toolchain. In a source checkout the tools are usually in
  `Enigma-Engine/build/`.
- Compiled SLEIGH specifications reachable through `ENIGMA_SLEIGH_DIR` if the
  default lookup fails.
- A shell for CLI workflows. PowerShell users should capture native stderr with
  `cmd /c "... 2> log.txt"`.
- Optional: a Qt build of `enigma_gui` for interactive xrefs, graphs, strings,
  data types, patches, and project history.
- Optional: a C++ compiler and the Enigma headers for automation that the CLI
  does not expose.

No MCP server, network service, credentials, or API keys are required. The
skill is text only and ships no engine binaries.

## Installation

Unzip the package into the skills directory used by your agent, or point the
agent at `SKILL.md`. The package is agent-agnostic: it uses plain Markdown and
shell commands, not a specific vendor's tool protocol.

Keep the directory structure intact so the relative links in `SKILL.md` resolve.

## Quick start

```bash
# 1. Triage
enigma_binary_audit target.bin > audit.txt 2> audit.log

# 2. Inventory functions
enigma_dump_functions target.bin > functions.csv 2> functions.log

# 3. Disassemble one address
enigma_dump_listing target.bin unused.csv 0x401000 > disasm.txt 2> disasm.log

# 4. Decompile one function
enigma_decompile_full -entry 0x401000 -max-func 1 -o function.c target.bin 2> decompile.log
```

Read `SKILL.md` for the full workflow and `references/limitations.md` before
making claims about source reconstruction, Ghidra parity, or unsupported
features.

## Evidence basis

The commands and outputs in this package were verified against the local build
in the Enigma Engine repository while the package was prepared. The worked
example records the target SHA-256, toolchain, commands, and captured output.
The repository's own progress notes were used for known gaps, but their parity
numbers are specific to the binaries and Ghidra versions they describe.

The package does not include:

- engine source code;
- engine binaries, DLLs, or libraries;
- sample binaries;
- FKS libraries or LMDB indexes;
- credentials, tokens, environment files, or caches;
- third-party source code.

## Compatibility

- **Agent implementations:** any agent that can read `SKILL.md` and run shell
  commands. The instructions avoid vendor-specific tool names.
- **Operating systems:** the CLI is built for the platform of the Enigma build.
  The examples use POSIX-style redirection; PowerShell notes are included.
- **Binary formats:** PE, ELF, Mach-O, COFF, and Ghidra
  `.gzf`/`.rep`/`.gbf` projects. Raw blobs are supported by
  `enigma_decompile_full` with explicit `-lang`, `-base`, and `-entry`, and by
  the experimental `enigma_decompile` with `-a`, `-b`, and `-base`. Coverage is
  subject to the limitations in `references/limitations.md`.
- **Architectures:** x86/x64, ARM32, AArch64, MIPS, and PowerPC are represented
  in the engine; parity varies by format and architecture.

## Limitations

This is a static-analysis skill. It does not reconstruct original source,
guarantee Ghidra-identical output, debug or emulate binaries, or provide an MCP
server, JSON API, or Python SDK. Cross-references and control-flow graphs are
GUI/C++ API capabilities, not CLI commands. See
`references/limitations.md` for the full matrix.

## License and attribution

The Enigma Engine source headers identify the project as Apache License 2.0.
No top-level `LICENSE` file was present in the verified tree, so confirm the
project's licensing before redistribution. This documentation package is
intended to accompany that project and includes a verbatim copy of the
repository's `engine-architecture.md`. The package contains no engine binaries
or third-party source.

License for marketplace distribution: **Apache-2.0 (proposed; confirm before
publishing)**. The publisher is responsible for verifying that the listing and
package comply with the repository's license and with Agensi's terms.

## Version

- Skill version: `1.0.0`
- Package date: 2026-11-01
- Verified against: local Enigma Engine tree at commit `d3c1554`.

## Changelog

### 1.0.0

- Initial documentation-only package.
- Verified CLI workflows for triage, function inventory, disassembly,
  decompilation, Ghidra project inspection, naming audit, patching, and FKS
  indexing.
- Documented GUI-only and C++ API capabilities with explicit caveats.
- Added worked PE example and limitations matrix.
