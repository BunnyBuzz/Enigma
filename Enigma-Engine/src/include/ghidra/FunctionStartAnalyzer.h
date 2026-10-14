#pragma once

#include <ghidra/AbstractAnalyzer.h>

#include <string>

namespace ghidra {

class Disassembler;

class FunctionStartAnalyzer : public AbstractAnalyzer {
public:
    FunctionStartAnalyzer();
    virtual ~FunctionStartAnalyzer() = default;

    virtual bool canAnalyze(Program* program) const override;
    virtual bool added(Program* program, const AddressSetView& set, TaskMonitor* monitor, MessageLog& log) override;
};

// Shared candidate validation: a candidate is only a real function entry
// when no normal (non-padding, non-terminator) instruction ends exactly at
// it. Rejects fallthrough-interior and misaligned-pattern addresses, which
// is what prevents function creation from splitting real bodies.
// `disassembler` may be null, in which case the check is permissive.
bool isValidFunctionStartCandidate(Program* program, const Address& addr,
                                   const std::string& arch, int bitness,
                                   Disassembler* disassembler);

} // namespace ghidra
