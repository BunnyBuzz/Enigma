#include <ghidra/TypeDatabase.h>
#include <string>
#include <vector>
#include <memory>

namespace ghidra {

class MacOSTypeDatabase : public TypeDatabase {
public:
    bool getFunctionType(const std::string& funcName,
                         std::string& returnType,
                         std::vector<std::string>& paramTypes) const override {
        return false;
    }

    bool isNoReturn(const std::string& funcName) const override {
        // Libc termination paths; mirrors Ghidra's NoReturn DB (see Linux DB).
        return funcName == "abort" || funcName == "exit" || funcName == "_exit" ||
               funcName == "_Exit" || funcName == "exit_group" ||
               funcName == "quick_exit" || funcName == "longjmp" ||
               funcName == "siglongjmp" || funcName == "__stack_chk_fail" ||
               funcName == "__assert_fail" || funcName == "__assert_rtn" ||
               funcName == "pthread_exit";
    }

    std::string getPlatformName() const override {
        return "MacOS";
    }
};

std::unique_ptr<TypeDatabase> createMacOSTypeDatabase() {
    return std::make_unique<MacOSTypeDatabase>();
}

} // namespace ghidra
