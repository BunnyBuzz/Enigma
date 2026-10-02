#pragma once

#include <ghidra/AbstractAnalyzer.h>

#include <string>
#include <vector>

namespace ghidra {

class DataTypeManager;

class SwiftTypeMetadataAnalyzer : public AbstractAnalyzer {
public:
    struct SwiftFieldInfo {
        std::string name;
        std::string typeName;
    };
    // One nominal type from __swift5_types/__swift5_fieldmd: demangled
    // name, descriptor kind (4=class, 5=struct, 6=enum, 3=protocol,
    // -1 when seen only in field metadata). Backs the G7 Data Types dock.
    struct SwiftTypeInfo {
        std::string name;
        int kind = -1;
        std::vector<SwiftFieldInfo> fields;
    };

    SwiftTypeMetadataAnalyzer();
    virtual ~SwiftTypeMetadataAnalyzer() = default;

    virtual bool canAnalyze(Program* program) const override;
    virtual bool added(Program* program, const AddressSetView& set, TaskMonitor* monitor, MessageLog& log) override;

    std::vector<SwiftTypeInfo> getTypes() const { return types_; }
    // Register collected types as /swift structures in the DataTypeManager.
    void createDataTypes(DataTypeManager* dtm);

private:
    std::vector<SwiftTypeInfo> types_;
};

} // namespace ghidra
