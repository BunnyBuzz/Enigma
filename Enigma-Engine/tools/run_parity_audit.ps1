#!/usr/bin/env pwsh
# Full disassembler parity audit driver.
$ErrorActionPreference = "Continue"
$root = "C:\Users\pc\Desktop\Enigma IDE Local\Enigma-Engine"
$corpus = "$root\tests\corpus"
$outdir = "$corpus\ghidra_listing"
New-Item -ItemType Directory -Force -Path $outdir | Out-Null
. "$root\tools\ghidra_env.ps1"
$ghHome = Resolve-GhidraHome
if (-not $ghHome) {
    Write-Output "MISSING Ghidra install (set GHIDRA_HOME)"
    exit 1
}
$ghidra = Join-Path $ghHome "support\analyzeHeadless.bat"
$javaHome = Resolve-GhidraJavaHome
if ($javaHome) { $env:JAVA_HOME = $javaHome }
$proj = "$root\tests\headless_proj"
$projName = "parity$((Get-Date).ToString('yyyyMMddHHmmss'))"
$binaries = @(
    "aarch64_fib.elf", "arm32_fib.elf", "mipsel_fib.elf", "ppc32_fib.elf",
    "aarch64_pie_dyn.elf", "arm_dyn.elf", "mips_dyn.elf", "ppc_dyn.elf", "x64_dyn.elf",
    "large_x86_64.elf"
)
foreach ($b in $binaries) {
    $path = Join-Path $corpus $b
    if (-not (Test-Path $path)) { Write-Output "MISSING $path"; continue }
    $ghOut = Join-Path $outdir ($b + ".csv")
    $enOut = Join-Path $outdir ($b + "_enigma.csv")
    Write-Output "=== GHIDRA $b (Ghidra $(Get-GhidraVersion $ghHome)) ==="
    $env:GHIDRA_LISTING_OUT = $ghOut
    & $ghidra $proj $projName -import $path -postScript DumpListing.java -scriptPath "$root\tools\headless" 2>$null | Out-Null
    Write-Output "=== ENIGMA $b ==="
    & "$root\build\enigma_dump_listing.exe" $path $enOut 2>$null | Select-Object -Last 1
    & python3 "$root\tools\parity_listing_diff.py" $ghOut $enOut
}
