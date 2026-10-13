// DumpListing.java - output per-instruction listing CSV for parity diff.
// Run via analyzeHeadless -postScript with env GHIDRA_LISTING_OUT set.
import ghidra.app.script.GhidraScript;
import ghidra.program.model.address.Address;
import ghidra.program.model.listing.*;
import ghidra.program.model.symbol.*;
import java.io.*;

public class DumpListing extends GhidraScript {
    @Override
    public void run() throws Exception {
        String out = System.getenv("GHIDRA_LISTING_OUT");
        if (out == null || out.isEmpty()) out = "listing.csv";
        FunctionManager fm = currentProgram.getFunctionManager();
        Listing listing = currentProgram.getListing();
        int count = 0;
        try (PrintWriter w = new PrintWriter(new BufferedWriter(new FileWriter(out)))) {
            w.println("funcEntry,addr,mnemonic,operands,bytes");
            FunctionIterator fit = fm.getFunctions(true);
            while (fit.hasNext()) {
                if (monitor.isCancelled()) break;
                Function f = fit.next();
                Address start = f.getEntryPoint();
                InstructionIterator it = listing.getInstructions(f.getBody(), true);
                while (it.hasNext()) {
                    Instruction in = it.next();
                    String op = in.getDefaultOperandRepresentation(0);
                    StringBuilder ops = new StringBuilder();
                    for (int i = 0; i < in.getNumOperands(); i++) {
                        if (i > 0) ops.append('|');
                        ops.append(in.getDefaultOperandRepresentation(i).replace(',', ';'));
                    }
                    byte[] b = new byte[in.getLength()];
                    currentProgram.getMemory().getBytes(in.getAddress(), b);
                    StringBuilder hex = new StringBuilder();
                    for (byte x : b) hex.append(String.format("%02x", x));
                    w.println(String.format("0x%x,0x%x,%s,%s,%s",
                        start.getOffset(), in.getAddress().getOffset(),
                        in.getMnemonicString(), ops.toString(), hex));
                    count++;
                }
            }
        }
        println("DumpListing wrote " + count + " instructions to " + out);
    }
}
