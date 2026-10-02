#pragma once

#include <ghidra/AbstractAnalyzer.h>
#include <ghidra/Address.h>
#include <ghidra/GoBuildInfoParser.h>

#include <string>
#include <vector>

namespace ghidra {

class GolangSymbolAnalyzer : public AbstractAnalyzer {
public:
    // One recovered Go function: full symbol name, package path (part
    // before the last dot, e.g. "main", "runtime", "github.com/x/y"),
    // and entry address. Backs the G5 package-grouping explorer.
    struct GoFunctionInfo {
        std::string name;
        std::string package;
        Address entry;
    };

    GolangSymbolAnalyzer();
    virtual ~GolangSymbolAnalyzer() = default;

    virtual bool canAnalyze(Program* program) const override;
    virtual void registerOptions(Options& options, Program* program) override;
    virtual void optionsChanged(Options& options, Program* program) override;
    virtual bool added(Program* program, const AddressSetView& set, TaskMonitor* monitor, MessageLog& log) override;

    // Package path of a Go symbol name ("main.main" -> "main").
    static std::string packageOf(const std::string& funcName);
    // Functions recovered by the last added() run.
    std::vector<GoFunctionInfo> getFunctions() const { return functions_; }
    // Sorted unique package paths from the last added() run.
    std::vector<std::string> getPackages() const;
    // Build metadata parsed by the last added() run (version/module wired;
    // dependencies need the modinfo pointer chain - tracked as follow-up).
    GoBuildInfoParser::BuildInfo getBuildInfo() const { return buildInfo_; }

private:
    void recordFunction(const std::string& name, const Address& entry);

    std::vector<GoFunctionInfo> functions_;
    GoBuildInfoParser::BuildInfo buildInfo_;
};

} // namespace ghidra
