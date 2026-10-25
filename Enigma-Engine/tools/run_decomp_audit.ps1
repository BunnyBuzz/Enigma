#!/usr/bin/env pwsh
# Decompiler parity audit driver: Ghidra headless decompile vs Enigma.
# Usage: run_decomp_audit.ps1 -Binary <name> -Delta <hex>
#   Binary: corpus file name (e.g. arm_dyn.elf)
#   Delta:  ghidra_entry - enigma_raw (e.g. 0x10000)
param(
    [string]$Binary = "arm_dyn.elf",
    [string]$Delta = "0x10000",
    [string]$Addrs = "",
    [string]$AddrsFile = ""
)
$ErrorActionPreference = "Continue"
$root = "C:\Users\pc\Desktop\Enigma IDE Local\Enigma-Engine"
$corpus = "$root\tests\corpus"
$tmp = "C:\Users\pc\AppData\Local\Temp\opencode\decomp_audit"
. "$root\tools\ghidra_env.ps1"
$ghHome = Resolve-GhidraHome
if (-not $ghHome) {
    Write-Output "MISSING Ghidra install (set GHIDRA_HOME)"
    exit 1
}
$ghidra = Join-Path $ghHome "support\analyzeHeadless.bat"
$ghVersion = Get-GhidraVersion $ghHome
$proj = "$root\tests\headless_proj"
$javaHome = Resolve-GhidraJavaHome
if ($javaHome) { $env:JAVA_HOME = $javaHome }
$env:ENIGMA_SLEIGH_DIR = "$root\sleigh"

$binPath = Join-Path $corpus $Binary
if (-not (Test-Path $binPath)) { Write-Output "MISSING $binPath"; exit 1 }

$ghDir = Join-Path $tmp ($Binary + "_gh")
$enDir = Join-Path $tmp ($Binary + "_en")
New-Item -ItemType Directory -Force -Path $ghDir | Out-Null
New-Item -ItemType Directory -Force -Path $enDir | Out-Null
# Fresh state: stale per-function files from older runs corrupt M1
Get-ChildItem $ghDir -Filter *.c -ErrorAction SilentlyContinue | Remove-Item -Force
Get-ChildItem $enDir -Filter *.c -ErrorAction SilentlyContinue | Remove-Item -Force

Write-Output "=== GHIDRA $Binary (Ghidra $ghVersion) ==="
$env:GHIDRA_DECOMP_OUT = $ghDir
$projName = "decomp$((Get-Date).ToString('yyyyMMddHHmmss'))"
if ($env:GHIDRA_DECOMP_ONLY) { Write-Output "Ghidra entry filter: $env:GHIDRA_DECOMP_ONLY" }
& $ghidra $proj $projName -import $binPath -postScript DumpDecompile.java -scriptPath "$root\tools\headless" 2>&1 | Select-String -Pattern "DumpDecompile|error|Error" | Select-Object -First 4

Write-Output "=== ENIGMA $Binary ==="
$enArgs = @("$root", $binPath, $enDir)
if ($AddrsFile -ne "" -and (Test-Path $AddrsFile)) { $enArgs += $AddrsFile }
elseif ($Addrs -ne "") {
    $addrTmp = Join-Path $tmp ($Binary + "_addrs.txt")
    $addrLines = $Addrs -split "," | ForEach-Object { $_.Trim() } |
        Where-Object { $_ -ne "" }
    # UTF8 without BOM: enigma_decompile_full parses these with stoull.
    [System.IO.File]::WriteAllText($addrTmp, ($addrLines -join "`n"),
        (New-Object System.Text.UTF8Encoding($false)))
    $enArgs += $addrTmp
}
& python3 "$root\tools\en_singles.py" @enArgs

Write-Output "=== DIFF $Binary (delta $Delta) ==="
if ($env:GHIDRA_DECOMP_ONLY) {
    # The decompile dump is a requested subset; comparing it with the full
    # listing would report every omitted function as ghidra-only.
    $ghListing = $null
} else {
    $ghListing = Join-Path $corpus "ghidra_listing\$Binary.csv"
    if (-not (Test-Path $ghListing)) { $ghListing = $null }
}
if ($ghListing) {
    & python3 "$root\tools\parity_decomp_diff.py" $ghDir $enDir --delta $Delta --ghidra-listing $ghListing
} else {
    & python3 "$root\tools\parity_decomp_diff.py" $ghDir $enDir --delta $Delta
}
