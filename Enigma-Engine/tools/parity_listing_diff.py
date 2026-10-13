#!/usr/bin/env python3
"""parity_listing_diff.py - compare Ghidra vs Enigma listing CSVs."""
import csv, re, sys, os, collections

DECORATIONS = re.compile(
    r'\b(BYTE|WORD|DWORD|QWORD|TBYTE|OWORD|XMMWORD|YMMWORD|ZMMWORD|'
    r'PTR|SHORT|NEAR|FAR|OFFSET|CS|SS|DS|ES|FS|GS)\b|'
    r'\b[Dd][Ww][Oo][Rr][Dd]\s+PTR\b|ds:|es:|fs:|gs:|cs:|ss:', re.I)

ADDRESS_TARGET_MNEMS = {
    "b","bl","br","blr","ret","cbz","cbnz","tbz","tbnz",
    "beq","bne","bcs","bhs","bcc","blo","bmi","bpl","bvs","bvc","bhi","bls","bge","blt","bgt","ble",
    "j","jal","jalr","jr","jrc","jr.hb","jalx","bal","beqz","bnez","bgtz","bltz",
    "adrp","adr","call","jmp","loop","loopz","loopnz"
}

def norm_op(op_str, gh_addrs, base_delta, mnem):
    if not op_str: return ""
    targetish = norm_mnemonic(mnem) in ADDRESS_TARGET_MNEMS
    parts = re.split(r"[|;]", op_str)
    out = []
    for raw_part in parts:
        p = raw_part.strip().lstrip('#').strip()
        p = DECORATIONS.sub("", p)
        p = re.sub(r"[\s,\(\)\{\}]+", " ", p).strip().lower()
        is_imm = raw_part.strip().startswith('#')
        if p:
            def hexn(m):
                literal = m.group(0)
                v = int(literal, 16)
                in_bracket = m.start() > 0 and p[m.start()-1] == '['
                if base_delta != 0:
                    if in_bracket:
                        return f"0x{v + base_delta:x}"
                    if targetish and not is_imm:
                        return f"0x{v + base_delta:x}"
                    if (v + base_delta) in gh_addrs:
                        return f"0x{v + base_delta:x}"
                return f"0x{v:x}"
            p = re.sub(r"0x[0-9a-fA-F]+", hexn, p)
            out.append(p)
    return " ".join(out)

def norm_mnemonic(s):
    return (s or "").strip().lower().rstrip(";").lstrip("_")

def load(path):
    rows = collections.defaultdict(dict)  # funcEntry -> addr -> row
    with open(path, newline="", encoding="utf-8-sig") as f:
        r = csv.DictReader(f)
        for row in r:
            try:
                fe = int(row["funcEntry"], 16)
                addr = int(row["addr"], 16)
            except (ValueError, KeyError):
                continue
            rows[fe][addr] = row
    return rows

def main():
    if len(sys.argv) < 3:
        print("usage: parity_listing_diff.py <ghidra_csv> <enigma_csv>")
        sys.exit(2)
    gh = load(sys.argv[1])
    en = load(sys.argv[2])
    # Rebase: Ghidra may include base delta vs Enigma ELF RVA-zero base.
    gh_base = min((a for d in gh.values() for a in d), default=0)
    en_base = min((a for d in en.values() for a in d), default=0)
    delta = gh_base - en_base
    if delta != 0:
        en = {fe + delta: {a + delta: row for a, row in m.items()} for fe, m in en.items()}
    all_funcs = sorted(set(gh) | set(en))
    stats = dict(total_gh=0, total_en=0, matched=0, mnem_mismatch=0, op_mismatch=0,
                 gh_only_func=0, en_only_func=0, gh_only_addr=0, en_only_addr=0)
    diffs = []
    gh_addrs = {a for m in gh.values() for a in m}
    for fe in all_funcs:
        g = gh.get(fe, {})
        e = en.get(fe, {})
        if fe not in gh:
            stats["en_only_func"] += 1
            continue
        if fe not in en:
            stats["gh_only_func"] += 1
            continue
        stats["total_gh"] += len(g)
        stats["total_en"] += len(e)
        for addr in sorted(set(g) | set(e)):
            if addr in g and addr in e:
                gr, er = g[addr], e[addr]
                gm, em = norm_mnemonic(gr.get("mnemonic")), norm_mnemonic(er.get("mnemonic"))
                go = norm_op(gr.get("operands"), gh_addrs, 0, gr.get("mnemonic"))
                eo = norm_op(er.get("operands"), gh_addrs, delta, er.get("mnemonic"))
                if gm == em and go == eo:
                    stats["matched"] += 1
                elif gm != em:
                    stats["mnem_mismatch"] += 1
                    diffs.append(("MNEM", fe, addr, gr.get("mnemonic"), er.get("mnemonic")))
                else:
                    stats["op_mismatch"] += 1
                    diffs.append(("OP", fe, addr, gr.get("operands"), er.get("operands")))
            elif addr in g:
                stats["gh_only_addr"] += 1
            else:
                stats["en_only_addr"] += 1

    print(f"functions: ghidra={len(gh)} enigma={len(en)} shared={len(set(gh)&set(en))}")
    print(f"instructions: ghidra={stats['total_gh']} enigma={stats['total_en']}")
    print(f"semantic matches: {stats['matched']}")
    print(f"mnemonic mismatches: {stats['mnem_mismatch']}, operand mismatches: {stats['op_mismatch']}")
    print(f"gh-only functions: {stats['gh_only_func']}, en-only functions: {stats['en_only_func']}")
    print(f"gh-only instrs: {stats['gh_only_addr']}, en-only instrs: {stats['en_only_addr']}")
    if diffs:
        print("\nworst diffs:")
        for d in diffs[:15]:
            print(f"  {d[0]} func=0x{d[1]:x} addr=0x{d[2]:x}: ghidra='{d[3]}' enigma='{d[4]}'")

if __name__ == "__main__":
    main()
