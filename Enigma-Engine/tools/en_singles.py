#!/usr/bin/env python3
"""en_singles.py - emit one decompiled file per function for parity audits.

Usage: en_singles.py <engine_root> <binary> <outdir> [addrs_file]

Runs enigma_decompile_full -entry <addr> -max-func 1 per address and writes
<outdir>/<hex>.c (UTF-8). Without addrs_file, addresses are enumerated via
enigma_dump_functions on the binary. ENIGMA_SLEIGH_DIR must be set.
"""
import csv
import glob
import os
import subprocess
import sys


def read_text_smart(path):
    with open(path, "rb") as f:
        raw = f.read()
    for enc in ("utf-8-sig", "utf-16"):
        try:
            return raw.decode(enc)
        except (UnicodeDecodeError, UnicodeError):
            continue
    return raw.decode("utf-8", errors="replace")


def enumerate_functions(engine_root, binary):
    exe = os.path.join(engine_root, "build", "enigma_dump_functions.exe")
    res = subprocess.run([exe, binary], capture_output=True, text=True,
                         timeout=900)
    lines = res.stdout.splitlines()
    for i, ln in enumerate(lines):
        if ln.strip().startswith("address,"):
            lines = lines[i:]
            break
    addrs = []
    for r in csv.DictReader(lines):
        try:
            addrs.append("0x%x" % int(r["address"], 16))
        except (ValueError, KeyError, TypeError):
            continue
    return addrs


def main():
    engine_root, binary, outdir = sys.argv[1], sys.argv[2], sys.argv[3]
    if len(sys.argv) > 4:
        with open(sys.argv[4], encoding="utf-8", errors="replace") as f:
            addrs = []
            for ln in f.read().replace(",", " ").split():
                ln = ln.strip()
                if ln:
                    addrs.append(ln)
    else:
        addrs = enumerate_functions(engine_root, binary)
    os.makedirs(outdir, exist_ok=True)
    for f in glob.glob(os.path.join(outdir, "*.c")):
        os.remove(f)
    exe = os.path.join(engine_root, "build", "enigma_decompile_full.exe")
    for a in addrs:
        hexname = a[2:] if a.lower().startswith("0x") else a
        res = subprocess.run(
            [exe, "-entry", a, "-max-func", "1", binary],
            capture_output=True, text=True, timeout=600, env=os.environ)
        with open(os.path.join(outdir, hexname + ".c"), "w",
                  encoding="utf-8", newline="") as f:
            f.write(res.stdout)
        if res.returncode != 0:
            print("FAIL %s: %s" % (a, (res.stderr or "")[:160]))
    print("en_singles: %d files -> %s" % (len(addrs), outdir))


if __name__ == "__main__":
    main()
