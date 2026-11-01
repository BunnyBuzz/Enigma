# Limitations and Capability Status

This document separates what was verified for this package from what is
implemented but not independently verified, what is planned, and what is not
available. When in doubt, report the narrower claim.

## Status legend

- **Verified** — exercised in this repository with the commands or APIs cited.
- **Implemented, not independently verified** — code and tests exist, but this
  package did not establish the behavior on representative inputs.
- **Planned / roadmap** — design material exists; do not present it as shipped.
- **Unsupported / unavailable** — no verified interface or capability.

## Verified for this package

The following were exercised against the local build while preparing the skill:

- `enigma_binary_audit` on a PE32+ sample: format, sections, import/export
  counts, symbols, and analysis counts.
- `enigma_dump_functions` on the same sample: `address,type,name` CSV with
  `entry` and `main` recognition.
- `enigma_dump_listing` on the same sample: full CSV listing and eight-instruction
  single-address mode.
- `enigma_decompile_full` on the same sample: `-entry` + `-max-func 1` produced
  a C-like `main` body; `-max-func 3 -time` produced multiple bodies and timing
  on stderr.
- `enigma_decompile` on a raw one-instruction blob with `-a x86 -b 64
  -base 0x1000`: produced a C-like body.
- `enigma_patch_cli`: patched `c3` to `90` at `0x140001000` in a copy, exported,
  and printed `VERIFY OK`.
- `enigma_gzf_inspect` and `enigma_gzf_probe` on a Ghidra `.rep` project:
  table inspection, imported program summary, function list, function fields,
  and decompilation of a named function.
- `enigma_naming_audit` and `enigma_pipeline_audit` on the PE sample.
- `enigma_fks_ingest` + `enigma_fks_build_index` on the PE sample: a `.fkslib`
  was created and an LMDB index was built.
- Source-level inspection of the CLI tools, `DecompInterface`,
  `ReferenceManager`, `Function`, `BinaryLoader`, `cfg::DisassemblyCFG`, and the
  storage headers.

The package does **not** claim that every loader, architecture, or GUI feature
was exercised. The repository's own progress notes contain broader parity
results; treat those as recorded evidence for their specific binaries, not as a
general guarantee.

## Implemented, not independently verified here

- **Mach-O, fat/universal binaries, Objective-C, and Swift analysis.** Loader
  and analyzer code exists, but parity is unverified without representative
  Apple binaries and toolchains.
- **COFF objects and archives.** Loader and test code exist, but this package
  did not exercise a COFF target; archive handling and parity are unverified
  here.
- **MIPS GOT parsing.** Requires section headers; stripped binaries without them
  may not resolve GOT-based references.
- **PE DWARF.** The progress notes record that the PE loader does not load
  `.debug_*` section bytes into memory, so PE DWARF type/signature recovery is
  limited. ELF DWARF is the verified path in those notes.
- **Ghidra project import fidelity.** The importer reads `.gzf`, `.rep`, and
  `.gbf` natively and reconstructs the program model. It is not a guarantee that
  every Ghidra comment, data type, bookmark, or analyzer result survives.
- **FKS function identification quality.** The pipeline exists and the index
  builds, but accuracy depends on the library's named functions and on the
  target's compiler/optimization. There is no public prebuilt database in this
  package.
- **GUI-only workflows.** Cross-reference browsing, function graphs, structure
  editing, string tables, commit history, and dyld cache browsing require a Qt
  build and were not exercised headlessly for this package.
- **Richer patch types.** The GUI exposes NOP fill, string, instruction, and
  metadata patches. The verified CLI path is a contiguous byte patch.
- **Project storage and history.** Repository, snapshot, commit, branch, and
  LMDB index code and tests exist. There is no verified CLI workflow.
- **Assembler patching.** Test coverage exists (`enigma_test_assembler_patching`),
  but the verified CLI exposes byte patching only.

## Planned / roadmap

- **Plugin system and stable ABI.** `PLAN/Enigma_Ecosystem.md` describes DLL
  plugins loaded from a `plugins/` directory, importer plugins, and a versioned
  plain-C contract. The phases are design/roadmap material. Do not claim that
  plugins can be installed or that a plugin ABI is shipped.
- **Broader importer ecosystem.** The design mentions additional importers.
  Only the Ghidra import path was verified here.
- **Parity work.** Function-start, jump-table, and decompiler-output parity are
  ongoing. The repository records specific audit numbers, but they are tied to
  specific binaries and Ghidra versions.

## Unsupported / unavailable

- **Original source reconstruction.** The decompiler emits C-like pseudocode
  with inferred names, types, and boundaries. It does not recover the original
  source, comments, macros, or build system.
- **MCP server.** No MCP server or MCP integration exists in the repository.
  This skill is plain documentation; it does not ship a server.
- **JSON output mode.** The verified CLI outputs CSV, plain text, or C-like
  pseudocode. Do not parse it as JSON.
- **Python bindings.** No Python API was found. Automation is via CLI or C++.
- **Dedicated CLI for xrefs, CFG, structure recovery, or signature lookup.**
  Xrefs and CFG are GUI/C++ API capabilities. Import/export counts are printed
  by `enigma_binary_audit`; entries are printed by `enigma_pipeline_audit` and
  exposed through `BinaryLoader`. Structures are edited in the GUI or via C++
  data-type APIs. Signature recognition is analyzer/FKS work, not a standalone
  CLI.
- **Automatic structure recovery as a documented feature.** Structure and union
  types can be created/edited, and analyzers may create format-specific
  structures, but there is no verified general "recover all structs" CLI.
- **Dynamic analysis, debugging, emulation, or sandboxing.** Enigma is a static
  analysis toolchain in the verified surface. Do not claim it runs or debugs the
  target.
- **Guaranteed Ghidra-identical output.** Enigma is Ghidra-inspired and uses a
  Ghidra-derived decompiler, but function starts, jump-table recovery, and
  output formatting can differ. "Ghidra-compatible" is a design goal, not a
  byte-for-byte guarantee.
- **A prebuilt signature database.** FKS libraries must be built locally.

## Known gaps and quirks

### Function discovery and parity

The repository's recorded audit on `large_x86_64.elf` (Ghidra 12.2) reports:

- 3105 shared functions;
- 177,844 semantic matches;
- 2951/3105 byte-identical bodies;
- 0 mnemonic and 0 operand mismatches in shared functions;
- 48 Ghidra-only and 136 Enigma-only function starts.

These numbers are specific to that binary and comparison. Do not generalize them
to other targets or present them as a universal parity score.

### Decompiler behavior

- `entry` may inline `__libc_start_main` instead of emitting a call.
- Jump-table recovery lags Ghidra on some binaries.
- Names and types are inferred; a `main` label is heuristic.
- CRT/library bodies are suppressed by default; use `-no-crt` to see them.
- Output can be noisy for startup code and heavily optimized functions.
- The decompiler may inline callees, so the absence of a call in pseudocode is
  not proof that the call is absent in the binary.

### Tool-output quirks

- `enigma_dump_listing` CSV rows are grouped by function, not globally sorted by
  address. Full-listing mode writes the CSV to the named file and prints only a
  status line to stdout.
- Commas inside operands are replaced with `;`.
- Single-address mode still requires the `<out.csv>` argument and does not write
  that file.
- `enigma_gzf_probe` treats `argv[2]` as the function name; `--instr` only works
  after a non-option function name.
- `enigma_binary_audit` uses a different analyzer set from
  `enigma_dump_functions` and can show different names for the same address.
- `enigma_patch_cli` records `orig_hex` but does not verify it against the
  input; `VERIFY OK` only confirms the new bytes in the exported file.
- `enigma_decompile` is the experimental native pipeline, not the official
  decompiler path. Prefer `enigma_decompile_full`.
- Most tools write diagnostics to stderr. Mixing stderr into a CSV or `.c` file
  corrupts the capture.

### Environment and build

- `ENIGMA_SLEIGH_DIR` must point at compiled SLEIGH `.sla` specifications when
  the default is not found.
- `ENIGMA_FKS_DIR` must point at the FKS directory containing `.fkslib` files
  and `index/lmdb`.
- The FKS LMDB data file can be large/sparse; do not package it.
- GUI features require a Qt build and a display. They are not available in a
  headless CLI run.
- Installed builds may not contain every tool target present in a source
  checkout.

### Version claims

The repository README and progress notes cite different Ghidra versions and
audit numbers. Check the current source and tool output before repeating a
version-specific claim. This package deliberately avoids pinning a parity score
to the skill.

## Claims to avoid

Do not say:

- "Enigma reconstructs the original source."
- "Enigma is byte-for-byte identical to Ghidra."
- "Enigma has an MCP server / JSON API / Python SDK."
- "Enigma can recover all structures automatically."
- "The plugin ecosystem is available."
- "The decompiler output is verified safe to run."
- "A fingerprint match proves the function is the same."
- "The GUI workflow was performed" when only CLI tools were run.

## Evidence used for this package

- Live CLI runs on `samples/c_complex.exe` (PE32+ x86-64).
- Live Ghidra project inspection on
  `Enigma-Engine/tests/headless_proj/smokeproj.rep`.
- Live FKS ingest/index on the PE sample.
- Source inspection of the CLI tools and public headers.
- Repository status and progress notes for known gaps.

The package was prepared from a local build at commit `d3c1554`. The skill
describes the local verified behavior, not a released version.
