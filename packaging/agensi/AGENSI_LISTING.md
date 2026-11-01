# Agensi Listing — Draft

> **Status: DRAFT — not submitted, not published.**  
> **Price: intentionally unset — publisher decision.**  
> Confirm Agensi's current category names, tag vocabulary, and submission fields
> in Creator Studio before publishing. Agensi changes its listing schema.

## Listing name

Enigma Reverse Engineering

## Slug

`enigma-reverse-engineering`

## Category

Developer Tools → Reverse Engineering / Binary Analysis (proposed; select the
closest live Agensi category at submission time)

## Summary

Evidence-driven reverse-engineering workflows for the Enigma Engine CLI, Qt GUI,
and C++ APIs — triage, disassembly, decompilation, xrefs, CFGs, Ghidra import,
function fingerprinting, and verified byte patching, with explicit limits.

## Description

Enigma Reverse Engineering is a documentation-only agent skill for analysts who
use the Enigma Engine toolchain. It teaches an AI agent how to move from an
unknown binary to a defensible report: identify the format and architecture,
inventory functions, disassemble a target address, decompile it to C-like
pseudocode, inspect cross-references and control flow, and separate observed
facts from inferences.

The skill is built around the documented interfaces: the `enigma_decompile_full`,
`enigma_dump_functions`, `enigma_dump_listing`, `enigma_binary_audit`,
`enigma_patch_cli`, and Ghidra-project tools; the Qt GUI for interactive xrefs,
function graphs, strings, data types, and project history; and the C++ headers
for automation. It also documents optional FKS function fingerprinting and the
exact commands to build a local library and index.

It is deliberately honest about limits. Decompiler output is pseudocode, not
recovered source. Cross-references and CFGs are GUI/C++ API capabilities, not
CLI commands. Ghidra parity is not guaranteed. There is no MCP server, JSON API,
or Python SDK. The package contains documentation only; it does not include the
Enigma Engine binaries, sample binaries, FKS databases, credentials, or
third-party source.

## What buyers get

- `SKILL.md` with portable agent instructions and valid YAML frontmatter.
- A tool reference with exact commands, flags, output formats, exit behavior,
  GUI actions, and C++ API surfaces.
- Step-by-step workflows for triage, function review, program understanding,
  xrefs/CFGs, Ghidra import, FKS, patching, GUI sessions, and reporting.
- A limitations matrix that separates verified, implemented-but-unverified,
  planned, and unsupported capabilities.
- A worked PE32+ example with captured output and an observed-vs-inferred
  analysis.
- A condensed architecture overview plus a verbatim copy of the repository's
  `engine-architecture.md` directory tree for exact-path lookup.

## Demo / example session

A verified session on a small PE32+ sample:

```text
$ enigma_binary_audit samples/c_complex.exe
Format: PE
Arch: x86
Bitness: 64
ImageBase: 0x140000000
EntryPoint: 0x140001490
...
Imports: 53
Exports: 0
```

```text
$ enigma_dump_functions samples/c_complex.exe
address,type,name
0x140001490,entry,entry
0x140001514,named,main
...
```

```text
$ enigma_dump_listing samples/c_complex.exe unused.csv 0x140001514
0x140001514:  PUSH  R13
0x140001516:  PUSH  R12
0x140001518:  PUSH  RBP
0x140001519:  PUSH  RDI
0x14000151a:  PUSH  RSI
0x14000151b:  PUSH  RBX
0x14000151c:  SUB  RSP,0x228
0x140001523:  MOV  dword ptr [RSP + 0x260],ECX
```

```text
$ enigma_decompile_full -entry 0x140001514 -max-func 1 -o main.c samples/c_complex.exe
```

The decompiled body shows a `main`-like function with a byte loop using the
FNV-1a prime and a custom seed, a `qsort` call, and `__mingw_printf`/`puts`
calls. The example marks which facts were observed and which roles were
inferred. It also records
what was not proven: original names, types, struct layouts, and runtime safety.

See `examples/analysis-example.md` for the full session.

## Compatibility

- **Agents:** any agent that can read `SKILL.md` and run shell commands. The
  instructions are vendor-neutral.
- **Platforms:** the platform of the installed Enigma Engine build. Examples use
  POSIX-style redirection; PowerShell capture notes are included.
- **Formats:** PE, ELF, Mach-O, COFF, and Ghidra `.gzf`/`.rep`/`.gbf`
  projects. Raw blobs are decompiled through `enigma_decompile_full` with
  explicit `-lang`, `-base`, and `-entry`, or through the experimental
  `enigma_decompile` with `-a`, `-b`, and `-base`, subject to the limitations.
- **Architectures:** x86/x64, ARM32, AArch64, MIPS, and PowerPC are represented
  in the engine; parity varies by format and architecture.
- **Interfaces:** CLI, Qt GUI, and C++ headers. No MCP server, JSON mode, or
  Python bindings.

## Requirements / Needs access to

- A local Enigma Engine build with the CLI tools (commonly
  `Enigma-Engine/build/`).
- Compiled SLEIGH specifications reachable through `ENIGMA_SLEIGH_DIR` if the
  default lookup fails.
- Target binaries or Ghidra projects that the buyer is authorized to analyze.
- Optional: a Qt build of `enigma_gui` for interactive xrefs, graphs, strings,
  data types, and project history.
- Optional: a C++ compiler and the Enigma headers for custom automation.
- Optional: a local FKS library and LMDB index for function-name lookup.

**No MCP server, network service, API key, or credential is required or
included.** The skill does not execute target binaries.

## Tags (proposed; confirm against Agensi's live list)

- reverse-engineering
- decompilation
- disassembly
- binary-analysis
- ghidra
- security-analysis
- static-analysis

## Keywords

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
- byte patching

## Use cases

1. Triage an unknown PE, ELF, or Mach-O binary and identify its entry point,
   sections, import/export inventory, and function inventory.
2. Disassemble a function and decompile it to C-like pseudocode for manual
   review.
3. Map callers, callees, and basic blocks through the GUI or C++ API.
4. Import a Ghidra project and continue analysis without a Ghidra install or JVM.
5. Compare builds, measure naming coverage, or build a local FKS fingerprint
   library.
6. Patch bytes in a copy of a binary and verify the exported result.
7. Produce an evidence-backed report that separates observations from
   inferences.

## Permissions

- **Local file read:** reads target binaries, Ghidra projects, and FKS libraries
  supplied by the user.
- **Local file write:** writes analysis outputs, logs, patched copies, and FKS
  indexes to user-selected paths.
- **Process execution:** runs Enigma CLI tools and, optionally, the Qt GUI. It
  does not execute the target binary.
- **Network:** none.
- **Credentials/secrets:** none.
- **System modification:** none beyond files the user explicitly creates or
  exports.

## Limitations

- Decompiler output is C-like pseudocode, not original source. Names, types,
  signatures, and boundaries are inferred.
- No MCP server, JSON output mode, Python bindings, or stable plugin ABI.
- Cross-references, CFGs, strings, structure editing, and project history are
  GUI/C++ API capabilities, not CLI commands.
- No verified general-purpose automatic structure recovery.
- Ghidra parity is not guaranteed; function starts and jump-table recovery can
  differ.
- Mach-O/Objective-C/Swift parity is unverified without representative Apple
  binaries.
- FKS requires a locally built library and index; there is no public prebuilt
  signature database in the package.
- The CLI byte patch is not an assembler and does not verify runtime behavior,
  checksums, or relocations.
- The package requires a local Enigma Engine build; it does not ship engine
  binaries.

## FAQs

**Does the package include Enigma Engine?**  
No. It is documentation only. The buyer must have an Enigma Engine build.

**Does it work without the GUI?**  
Yes for triage, function inventory, disassembly, decompilation, Ghidra project
inspection, naming audits, byte patching, and FKS indexing. Xrefs, CFGs, string
browsing, structure editing, and commit history require the GUI or C++ API.

**Does it reconstruct the original source?**  
No. It produces C-like pseudocode with inferred names and types.

**Does it require Ghidra or a JVM?**  
No for the native `.gzf`/`.rep`/`.gbf` import path. Ghidra itself is not
required.

**Can it patch binaries?**  
Yes, one contiguous byte range at a time through `enigma_patch_cli`, with
`VERIFY OK` checking the exported bytes. It does not guarantee the patched
program runs.

**Is there an MCP server?**  
No. The repository contains no MCP server or MCP integration. This skill is
plain documentation.

**What formats and architectures are supported?**  
PE, ELF, Mach-O, COFF, and Ghidra projects; raw blobs through
`enigma_decompile_full` (explicit language/base/entry) or the experimental
`enigma_decompile` (architecture/bitness/base); x86/x64, ARM32, AArch64, MIPS,
and PowerPC are represented. Coverage and parity vary. Check the limitations
file before promising a specific target.

**Is it safe to use on malware?**  
The skill is static-analysis guidance and does not execute targets. Buyers are
responsible for authorization, isolation, and safe handling of untrusted files.

## Price

**Not set — publisher decision.** Do not publish until the publisher chooses
free, one-time, or subscription pricing in Agensi Creator Studio. No price is
encoded in the package.

## Version

`1.0.0`

## License

Apache-2.0 (proposed, matching the Apache-2.0 headers in the Enigma Engine
sources; no top-level `LICENSE` file was present in the verified tree, so
confirm before publishing). The package includes a verbatim copy of the
repository's `engine-architecture.md` and no engine binaries or third-party
source.

## Support

Publisher-provided support only. Include a contact or repository URL before
publishing if Agensi requires one. No support URL is encoded in this draft
because no public documentation URL was verified.

## Package contents

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

## Status

**Draft.** Not submitted to Agensi. Not published. No price selected.

## Pre-publication checklist

- [ ] Confirm Agensi's current category and tag vocabulary in Creator Studio.
- [ ] Confirm that a text-only skill requiring a local Enigma Engine build is
      accepted under Agensi's current delivery rules. Agensi states that it
      delivers through MCP and that locally installed plugins are not currently
      sellable; this skill ships no plugin or server, but it does assume a local
      toolchain. Resolve this with Agensi review before submitting.
- [ ] Choose the price (or free) in Creator Studio; do not encode it here.
- [ ] Confirm the license and attribution wording.
- [ ] Add a logo/screenshots if the listing form requires media. None are
      included in this package.
- [ ] Add a public support or repository URL if required.
- [ ] Run Agensi's security scan on the final ZIP.
- [ ] Verify the ZIP contains exactly one `SKILL.md` at the package root and no
      binaries, credentials, caches, or Git metadata.
- [ ] Submit only after publisher approval; do not publish from this draft.
