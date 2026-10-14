// DumpDecompile.java - per-function decompiler parity export.
// Run via analyzeHeadless -postScript with env:
//   GHIDRA_DECOMP_OUT  output directory (per-function <entryhex>.c + index.csv)
// Uses the headless program's analysis results; decompiles every function.
import ghidra.app.script.GhidraScript;
import ghidra.app.decompiler.DecompInterface;
import ghidra.app.decompiler.DecompileResults;
import ghidra.program.model.address.Address;
import ghidra.program.model.listing.*;
import java.io.*;

public class DumpDecompile extends GhidraScript {
    static java.util.Set<Long> parseOnly(String s) {
        java.util.Set<Long> out = new java.util.HashSet<Long>();
        if (s == null || s.isEmpty()) return out;
        for (String part : s.split("[,;\\s]+")) {
            part = part.trim().toLowerCase();
            if (part.startsWith("0x")) part = part.substring(2);
            if (part.isEmpty()) continue;
            try { out.add(Long.parseLong(part, 16)); } catch (NumberFormatException e) {}
        }
        return out;
    }

    static String sanitize(String s) {
        StringBuilder r = new StringBuilder();
        for (int i = 0; i < s.length(); i++) {
            char c = s.charAt(i);
            if (c == ',' || c == '\n' || c == '\r' || c == '"') r.append(' ');
            else r.append(c);
        }
        return r.toString();
    }

    @Override
    public void run() throws Exception {
        String outDir = System.getenv("GHIDRA_DECOMP_OUT");
        if (outDir == null || outDir.isEmpty()) outDir = "decomp";
        new File(outDir).mkdirs();

        DecompInterface decomp = new DecompInterface();
        decomp.openProgram(currentProgram);

        FunctionManager fm = currentProgram.getFunctionManager();
        int ok = 0, fail = 0, skipped = 0;
        // Optional: GHIDRA_DECOMP_ONLY=0x401680,0x4153e5,... restricts export
        // to listed entries (large binaries).
        java.util.Set<Long> only = parseOnly(System.getenv("GHIDRA_DECOMP_ONLY"));
        PrintWriter idx = new PrintWriter(new BufferedWriter(
            new FileWriter(new File(outDir, "index.csv"))));
        idx.println("entry,name,status,lines");
        FunctionIterator fit = fm.getFunctions(true);
        while (fit.hasNext()) {
            if (monitor.isCancelled()) break;
            Function f = fit.next();
            long entry = f.getEntryPoint().getOffset();
            if (!only.isEmpty() && !only.contains(entry)) { skipped++; continue; }
            String hex = Long.toHexString(entry);
            String status;
            String code = "";
            try {
                DecompileResults res = decomp.decompileFunction(f, 60, monitor);
                if (res != null && res.decompileCompleted()) {
                    code = res.getDecompiledFunction().getC();
                    status = "OK";
                    ok++;
                } else {
                    status = "FAIL:" + (res != null ? res.getErrorMessage() : "null");
                    fail++;
                }
            } catch (Exception e) {
                status = "EXCEPT:" + e.getClass().getSimpleName();
                fail++;
            }
            PrintWriter w = new PrintWriter(new BufferedWriter(
                new FileWriter(new File(outDir, hex + ".c"))));
            w.print(code);
            w.close();
            int lines = code.isEmpty() ? 0 : code.split("\n").length;
            idx.println(String.format("0x%x,\"%s\",%s,%d",
                entry, sanitize(f.getName()), sanitize(status), lines));
        }
        idx.close();
        decomp.dispose();
        println("DumpDecompile OK=" + ok + " FAIL=" + fail + " skipped=" + skipped +
                " -> " + outDir);
    }
}
