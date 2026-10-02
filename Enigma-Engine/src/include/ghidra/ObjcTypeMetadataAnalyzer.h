#pragma once

#include <ghidra/AbstractAnalyzer.h>
#include <ghidra/Address.h>

#include <string>
#include <vector>

namespace ghidra {

class ObjcTypeMetadataAnalyzer : public AbstractAnalyzer {
public:
    struct ObjcIvarInfo {
        std::string name;
        uint32_t offset = 0;
        std::string type;
        uint32_t size = 0;
    };
    struct ObjcMethodInfo {
        std::string sel;
        std::string types;
        Address impl;
    };
    // One class from __objc_classlist: name, class/method-list addresses,
    // parsed methods and ivars. Backs the G6 Classes tree.
    struct ObjcClassInfo {
        std::string name;
        Address clsAddr;
        Address roAddr;
        std::vector<ObjcMethodInfo> methods;
        std::vector<ObjcIvarInfo> ivars;
    };
    struct ObjcProtocolInfo {
        std::string name;
        Address addr;
    };
    struct ObjcCategoryInfo {
        std::string name;
        std::string className;
        Address addr;
    };

    ObjcTypeMetadataAnalyzer();
    virtual ~ObjcTypeMetadataAnalyzer() = default;

    virtual bool canAnalyze(Program* program) const override;
    virtual bool added(Program* program, const AddressSetView& set, TaskMonitor* monitor, MessageLog& log) override;

    std::vector<ObjcClassInfo> getClasses() const { return classes_; }
    std::vector<ObjcProtocolInfo> getProtocols() const { return protocols_; }
    std::vector<ObjcCategoryInfo> getCategories() const { return categories_; }

private:
    std::vector<ObjcClassInfo> classes_;
    std::vector<ObjcProtocolInfo> protocols_;
    std::vector<ObjcCategoryInfo> categories_;
};

} // namespace ghidra
