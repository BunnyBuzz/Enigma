#!/usr/bin/env pwsh
# Resolve the Ghidra install and JDK used by the parity audit drivers.
# Keeps the scripts version-agnostic: Ghidra upgrades change directory names,
# and a stale hardcoded JAVA_HOME silently breaks analyzeHeadless.

function Get-GhidraVersion {
    param([string]$GhidraHome)
    $props = Join-Path $GhidraHome "Ghidra\application.properties"
    if (Test-Path $props) {
        $line = Get-Content $props | Where-Object { $_ -match '^application\.version=' } | Select-Object -First 1
        if ($line) { return ($line -split '=', 2)[1].Trim() }
    }
    return "unknown"
}

function Resolve-GhidraHome {
    param([string]$SearchRoot = "C:\Users\pc\Desktop\Crack tools")

    # 1. Explicit override.
    if ($env:GHIDRA_HOME) {
        if (Test-Path (Join-Path $env:GHIDRA_HOME "support\analyzeHeadless.bat")) {
            return (Resolve-Path $env:GHIDRA_HOME).Path
        }
        Write-Output "WARN GHIDRA_HOME does not contain support\analyzeHeadless.bat: $env:GHIDRA_HOME"
    }

    # 2. Newest install (name sort handles ghidra_12.2 > ghidra_12.1.3 >
    #    ghidra) under the usual tools directory.
    if (Test-Path $SearchRoot) {
        $installs = Get-ChildItem $SearchRoot -Directory -ErrorAction SilentlyContinue |
            Where-Object { Test-Path (Join-Path $_.FullName "support\analyzeHeadless.bat") } |
            Sort-Object Name -Descending
        if ($installs) { return $installs[0].FullName }
    }
    return $null
}

function Resolve-GhidraJavaHome {
    # Ghidra's launcher uses JAVA_HOME when set, else java from PATH.
    if ($env:JAVA_HOME -and (Test-Path (Join-Path $env:JAVA_HOME "bin\java.exe"))) {
        return $env:JAVA_HOME
    }
    return $null
}
