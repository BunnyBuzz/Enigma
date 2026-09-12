#pragma once

#include <ghidra/AbstractAnalyzer.h>
#include <ghidra/Address.h>
#include <vector>
#include <cstdint>
#include <unordered_set>
#include <unordered_map>
#include <queue>

namespace ghidra {

class ProgramDB;
struct DisassembledInstruction;
class Disassembler;

class DisassemblyAnalyzer : public AbstractAnalyzer {
public:
    DisassemblyAnalyzer();
    bool added(Program* program, const AddressSetView& set,
               TaskMonitor* monitor, MessageLog& log) override;
    bool canAnalyze(Program* program) const override;

private:
    // Compressed-ISA context tracking (GP-6766). NOTE: this Capstone has no
    // MIPS16e mode: mode 1 selects microMIPS tables, so native 2-byte rows
    // have plausible lengths but microMIPS-flavored mnemonics. The
    // semantically correct MIPS16e decode lives in the SLEIGH path
    // (DecompInterface ISA_MODE context); see ProgramDB::getMips16Ranges.
    // contextTable_ maps address -> ISA mode (0=MIPS32, 1=microMIPS)
    std::unordered_map<uint64_t, int> contextTable_;
    int currentIsaMode_ = 0;
    bool isMips_ = false;

    bool isIsaSwitchInstruction(const std::string& mnemonic) const;
    void handleIsaContextSwitch(const DisassembledInstruction& di,
                                Disassembler* disassembler, uint64_t addr);
};

} // namespace ghidra
