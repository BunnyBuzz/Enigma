#!/usr/bin/env python3
"""parity_decomp_diff.py - decompiler parity: Ghidra vs Enigma per-function.

Usage: parity_decomp_diff.py <gh_dir> <en_dir> --delta 0x10000
       [--ghidra-listing <gh_listing.csv>]

gh_dir: DumpDecompile output (index.csv + <entryhex>.c).
en_dir: per-function files named <rawhex>.c (enigma_decompile_full
        -entry 0x<raw> -max-func 1, no 0x prefix, lowercase hex).
--ghidra-listing: DumpListing CSV; its funcEntry set defines Ghidra image
        functions (excludes EXTERNAL-space thunks). Falls back to all
        index entries when omitted.

Join key: rebased entry address (enigma raw + delta = ghidra entry).

Metrics:
  M1 function-set parity (decompiled-output presence per image entry)
  M2 naming parity (raw + auto-name-normalized)
  M3 decompile success (Ghidra status vs Enigma halt_baddata presence)
  M4 signature parity (return type + param count)
  M5 callee-set parity (called function names per body)
  M6 normalized text similarity (whitespace-collapsed difflib ratio)
"""
import csv
import difflib
import os
import re
import sys

KEYWORDS = {"if", "for", "while", "switch", "return", "sizeof", "do", "else",
            "case", "goto", "typedef", "struct", "union", "enum"}
AUTO_RE = re.compile(r"^(FUN_|LAB_|DAT_|func_0x|sub_0x|function_0x|thunk_)",
                     re.IGNORECASE)


def auto_norm(name):
    return "AUTO" if AUTO_RE.match(name or "") else (name or "")


def read_text_smart(path):
    with open(path, "rb") as f:
        raw = f.read()
    for enc in ("utf-8-sig", "utf-16"):
        try:
            return raw.decode(enc)
        except (UnicodeDecodeError, UnicodeError):
            continue
    return raw.decode("utf-8", errors="replace")


def load_gh_index(d):
    rows = {}
    text = read_text_smart(os.path.join(d, "index.csv"))
    lines = [ln for ln in text.splitlines() if ln.strip()]
    for i, ln in enumerate(lines):
        if ln.strip().startswith("entry,"):
            lines = lines[i:]
            break
    for r in csv.DictReader(lines):
        try:
            rows[int(r["entry"], 16)] = r
        except (ValueError, KeyError):
            continue
    return rows


def load_gh_code(d, entry):
    p = os.path.join(d, "%x.c" % entry)
    try:
        return read_text_smart(p)
    except OSError:
        return ""


def load_en_code(d, raw_addr):
    for name in ("%x.c" % raw_addr, "0x%x.c" % raw_addr):
        p = os.path.join(d, name)
        if os.path.exists(p):
            try:
                return read_text_smart(p)
            except OSError:
                return ""
    return None


FUNC_NAME_RE = re.compile(r"([A-Za-z_]\w*)\s*\(")
CALL_RE = re.compile(r"\b([A-Za-z_]\w*)\s*\(")


def strip_comments(s):
    return re.sub(r"/\*.*?\*/", "", s, flags=re.S)


def first_sig(text):
    """First function signature: lines up to the opening brace."""
    text = strip_comments(text)
    lines = text.strip().split("\n")
    try:
        open_idx = next(i for i, l in enumerate(lines) if l.strip() == "{")
    except StopIteration:
        return ""
    return " ".join(l.strip() for l in lines[:open_idx]).strip()


def block_name(sig):
    ms = FUNC_NAME_RE.findall(sig)
    return ms[-1] if ms else ""


def body_after(text):
    text = strip_comments(text)
    lines = text.strip().split("\n")
    try:
        open_idx = next(i for i, l in enumerate(lines) if l.strip() == "{")
    except StopIteration:
        return text
    return "\n".join(lines[open_idx:])


PTR_RE = re.compile(r"^PTR_([A-Za-z_]\w*?)_[0-9a-fA-F]+$")
AUTO_ADDR_RE = re.compile(
    r"^(?:FUN_|func_0x|sub_0x|function_0x|LAB_|DAT_)0*([0-9a-fA-F]+)$")


def callee_key(tok, side_delta):
    """Canonical comparison key: auto-named symbols compare by rebased
    address (FUN_00100ea8 == func_0xea8 at delta 0x100000); everything
    else compares by normalized spelling."""
    m = AUTO_ADDR_RE.match(tok or "")
    if m:
        try:
            return ("addr", int(m.group(1), 16) + side_delta)
        except ValueError:
            pass
    return ("name", norm_callee(tok or ""))
PTR_HEX_RE = re.compile(r"^PTR_([0-9a-fA-F]+)$")
GHIDRA_INTRINSIC_RE = re.compile(r"^(CONCAT|SUB|ZEXT|SEXT|POPCOUNT|BSWAP|ROTATE)[0-9]*$")
# Linker-namespaced PLT symbols: Ghidra keeps 00000000.plt_pic32.fib
# (sanitized to _0000000_plt_pic32_fib in bodies); Enigma uses fib.
PLT_NS_RE = re.compile(r"^[._]?[0-9a-fA-F_.]*plt_pic32[_.](.+)$")


def base_import_name(name):
    m = PLT_NS_RE.match(name or "")
    if m:
        return m.group(1)
    return name or ""


def norm_callee(tok, delta=0):
    """Map spelling variants to import names: Ghidra PTR_name_addr and
    Enigma _name (ELF symbol) both become name. Anonymous GOT slots
    (PTR_<hex> / ptr_0x<hex>) are rebased by delta for comparison."""
    m = PTR_RE.match(tok)
    if m:
        stripped = m.group(1).lstrip("_")
        return stripped or m.group(1)
    m = PTR_HEX_RE.match(tok)
    if m:
        try:
            return "ptr_0x%x" % (int(m.group(1), 16) - delta)
        except ValueError:
            pass
    if GHIDRA_INTRINSIC_RE.match(tok):
        return ""
    stripped = tok.lstrip("_")
    tok = stripped or tok
    return base_import_name(tok)


def callees(body, self_name, delta=0):
    self_norm = norm_callee(self_name, delta)
    found = set(c for c in
                (norm_callee(x, delta) for x in CALL_RE.findall(body))
                if c and c not in KEYWORDS and c != self_norm)
    # indirect pass-through calls: (*NAME)(...), (**...)(...), (*(type *)NAME)(...)
    found.update(c for c in
                 (norm_callee(x, delta) for x in
                  re.findall(r"\(\*+\s*(?:\([^)]*\)\s*)?([A-Za-z_]\w*)\s*\)\s*\(", body))
                 if c and c != self_norm)
    return found


def split_params_inside(sig):
    i = sig.find("(")
    j = sig.rfind(")")
    if i < 0 or j < 0 or j < i:
        return None
    inner = sig[i + 1:j].strip()
    if inner in ("", "void"):
        return []
    depth = 0
    parts, cur = [], ""
    for ch in inner:
        if ch == "(":
            depth += 1
        elif ch == ")":
            depth -= 1
        if ch == "," and depth == 0:
            parts.append(cur.strip())
            cur = ""
        else:
            cur += ch
    if cur.strip():
        parts.append(cur.strip())
    return parts


def parse_sig(sig):
    i = sig.find("(")
    if i < 0:
        return None, None
    head = sig[:i].strip()
    ret = head.rsplit(None, 1)[0] if head else ""
    ret = re.sub(r"\b(__cdecl|__stdcall|__fastcall)\b", "", ret).strip()
    ret = re.sub(r"\s+", " ", ret)
    return ret, split_params_inside(sig)


TYPE_NORM = {
    "int32_t": "int", "uint32_t": "uint", "int16_t": "short",
    "uint16_t": "ushort", "int64_t": "long", "uint64_t": "ulong",
    "int8_t": "char", "uint8_t": "byte",
}


def norm_type(t):
    t = (t or "").strip()
    t = re.sub(r"\s*\*\s*", "*", t)
    t = re.sub(r"\s+", " ", t)
    return TYPE_NORM.get(t, t)


def norm_text(s):
    s = re.sub(r"/\*.*?\*/", "", s, flags=re.S)
    s = re.sub(r"\s+", " ", s).strip()
    return s


def main():
    if len(sys.argv) < 3:
        print(__doc__)
        sys.exit(2)
    gh_dir, en_dir = sys.argv[1], sys.argv[2]
    delta = 0
    gh_listing = None
    args = sys.argv[3:]
    for i, a in enumerate(args):
        if a == "--delta" and i + 1 < len(args):
            delta = int(args[i + 1], 16)
        if a == "--ghidra-listing" and i + 1 < len(args):
            gh_listing = args[i + 1]

    gh = load_gh_index(gh_dir)
    if gh_listing:
        gh_image = set()
        text = read_text_smart(gh_listing)
        for r in csv.DictReader(text.splitlines()):
            try:
                gh_image.add(int(r["funcEntry"], 16))
            except (ValueError, KeyError):
                continue
    else:
        gh_image = set(gh)

    en_raw = set()
    for fn in os.listdir(en_dir):
        m = re.match(r"^(?:0x)?([0-9a-fA-F]+)\.c$", fn)
        if m:
            try:
                en_raw.add(int(m.group(1), 16))
            except ValueError:
                pass
    en_rebased = {a + delta for a in en_raw}

    matched = gh_image & en_rebased
    print("M1 functions: ghidra_image=%d enigma=%d shared=%d" %
          (len(gh_image), len(en_rebased), len(matched)))
    print("M1 ghidra-only entries: %s" %
          (sorted("0x%x" % e for e in gh_image - en_rebased)[:8] or "none"))
    print("M1 enigma-only entries: %s" %
          (sorted("0x%x" % e for e in en_rebased - gh_image)[:8] or "none"))
    print("M1 ghidra non-image functions skipped: %d" % (len(gh) - len(gh_image)))

    gh_name = {e: gh[e].get("name", "") for e in matched if e in gh}
    # Enigma names come from each file's own signature (address-exact)
    en_name, en_code = {}, {}
    for e in matched:
        code = load_en_code(en_dir, e - delta)
        if code is None:
            continue
        en_code[e] = code
        en_name[e] = block_name(first_sig(code))

    exact = sum(1 for e in en_code if gh_name.get(e, "") == en_name.get(e, ""))
    norm = sum(1 for e in en_code
               if auto_norm(gh_name.get(e, "")) == auto_norm(en_name.get(e, "")) or
               base_import_name(gh_name.get(e, "")) == base_import_name(en_name.get(e, "")))
    print("M2 naming: exact=%d/%d normalized=%d/%d" %
          (exact, len(en_code), norm, len(en_code)))
    for e in sorted(en_code):
        if auto_norm(gh_name.get(e, "")) != auto_norm(en_name.get(e, "")) and \
                base_import_name(gh_name.get(e, "")) != base_import_name(en_name.get(e, "")):
            print("  M2 DIFF 0x%x: ghidra='%s' enigma='%s'" %
                  (e, gh_name.get(e, ""), en_name.get(e, "")))

    gh_ok = sum(1 for e in en_code
                if e in gh and gh[e].get("status", "").strip() == "OK")
    en_bad = sum(1 for e, code in en_code.items() if "halt_baddata" in code)
    print("M3 success: ghidra_OK=%d/%d enigma_with_halt_baddata=%d" %
          (gh_ok, len(en_code), en_bad))
    for e in sorted(en_code):
        st = gh[e].get("status", "").strip() if e in gh else "?"
        if st != "OK":
            print("  M3 GHIDRA-FAIL 0x%x %s: %s" % (e, gh_name.get(e, ""), st))
        if "halt_baddata" in en_code[e]:
            print("  M3 ENIGMA-BADDATA 0x%x %s" % (e, en_name.get(e, "")))

    sig_n = sig_ret = sig_params = 0
    call_prec = call_rec = 0.0
    call_n = 0
    sim_sum = 0.0
    for e in sorted(en_code):
        gcode = load_gh_code(gh_dir, e)
        gsig = first_sig(gcode)
        gret, gparams = parse_sig(gsig)
        eret, eparams = parse_sig(first_sig(en_code[e]))
        if gret is not None and eret is not None:
            sig_n += 1
            if norm_type(gret) == norm_type(eret):
                sig_ret += 1
            if gparams is not None and eparams is not None and len(gparams) == len(eparams):
                sig_params += 1
        elif gsig or first_sig(en_code[e]):
            print("  M4 UNPARSED 0x%x: gh='%s' en='%s'" %
                  (e, gsig[:80], first_sig(en_code[e])[:80]))
        gcal_raw = callees(body_after(gcode), gh_name.get(e, ""), delta)
        ecal_raw = callees(body_after(en_code[e]), en_name.get(e, ""), delta)
        gcal = set(callee_key(c, 0) for c in gcal_raw)
        ecal = set(callee_key(c, delta) for c in ecal_raw)
        if gcal or ecal:
            call_n += 1
            inter = gcal & ecal
            call_prec += len(inter) / max(1, len(ecal))
            call_rec += len(inter) / max(1, len(gcal))
            if gcal != ecal and len(gcal | ecal) <= 14:
                def show(s):
                    return sorted(("0x%x" % v if k == "addr" else v) for k, v in s)
                print("  M5 CALLS 0x%x %s: gh=%s en=%s" %
                      (e, gh_name.get(e, ""), show(gcal), show(ecal)))
        sim_sum += difflib.SequenceMatcher(
            None, norm_text(gcode), norm_text(en_code[e])).ratio()
    print("M4 signatures: parsed=%d ret_match=%d paramcount_match=%d" %
          (sig_n, sig_ret, sig_params))
    if call_n:
        print("M5 callees: pairs=%d mean_precision=%.2f mean_recall=%.2f" %
              (call_n, call_prec / call_n, call_rec / call_n))
    if en_code:
        print("M6 mean normalized text similarity: %.3f over %d pairs" %
              (sim_sum / len(en_code), len(en_code)))


if __name__ == "__main__":
    main()
