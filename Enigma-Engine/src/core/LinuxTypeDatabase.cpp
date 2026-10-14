#include <ghidra/TypeDatabase.h>
#include <string>
#include <vector>
#include <memory>

namespace ghidra {

// glibc/LinuxC library prototypes for import thunk typing and call-site
// resolution. Type spellings use the Windows-DB-compatible names both
// resolvers map correctly (AnalysisBridge::resolveTypeName and the tool's
// local one): INT/UINT/INT64/UINT64/LPVOID/LPSTR/LPCSTR/void. LP64 widths:
// INT64/UINT64 are 8 bytes, matching long/size_t/ssize_t on LP64; the
// decompiler prints them with its core names (long/ulong).
// Sources: man pages + Ghidra generic_clib ground truth from the
// decompiler parity audit (prctl/scanf/setvbuf/ptrace/syscall/write/
// malloc/free/getenv signatures verified against Ghidra 12.1.3 output).
struct GlibcFunc {
    const char* name;
    const char* ret;
    std::vector<const char*> params;
    bool variadic;
};

static const GlibcFunc kGlibcFuncs[] = {
    // Observed audit imports (verified vs Ghidra output)
    {"prctl", "INT", {"INT"}, true},
    {"scanf", "INT", {"LPSTR"}, true},
    {"setvbuf", "INT", {"LPVOID", "LPSTR", "INT", "UINT64"}, false},
    {"ptrace", "INT64", {"INT"}, true},
    {"syscall", "INT64", {"INT64"}, true},
    {"write", "INT64", {"INT", "LPVOID", "UINT64"}, false},
    {"malloc", "LPVOID", {"UINT64"}, false},
    {"free", "void", {"LPVOID"}, false},
    {"getenv", "LPSTR", {"LPSTR"}, false},
    {"__stack_chk_fail", "void", {}, false},
    {"__read_chk", "INT64", {"INT", "LPVOID", "UINT64", "UINT64"}, false},
    {"__write_chk", "INT64", {"INT", "LPVOID", "UINT64", "UINT64"}, false},
    // Standard C library (same glibc semantics)
    {"printf", "INT", {"LPSTR"}, true},
    {"fprintf", "INT", {"LPVOID", "LPSTR"}, true},
    {"sprintf", "INT", {"LPSTR", "LPSTR"}, true},
    {"snprintf", "INT", {"LPSTR", "UINT64", "LPSTR"}, true},
    {"strlen", "UINT64", {"LPSTR"}, false},
    {"strcpy", "LPSTR", {"LPSTR", "LPSTR"}, false},
    {"strncpy", "LPSTR", {"LPSTR", "LPSTR", "UINT64"}, false},
    {"strcmp", "INT", {"LPSTR", "LPSTR"}, false},
    {"strncmp", "INT", {"LPSTR", "LPSTR", "UINT64"}, false},
    {"memcpy", "LPVOID", {"LPVOID", "LPVOID", "UINT64"}, false},
    {"memmove", "LPVOID", {"LPVOID", "LPVOID", "UINT64"}, false},
    {"memset", "LPVOID", {"LPVOID", "INT", "UINT64"}, false},
    {"memcmp", "INT", {"LPVOID", "LPVOID", "UINT64"}, false},
    {"calloc", "LPVOID", {"UINT64", "UINT64"}, false},
    {"realloc", "LPVOID", {"LPVOID", "UINT64"}, false},
    {"qsort", "void", {"LPVOID", "UINT64", "UINT64", "LPVOID"}, false},
    {"atexit", "INT", {"LPVOID"}, false},
    {"puts", "INT", {"LPSTR"}, false},
    {"getchar", "INT", {}, false},
    {"open", "INT", {"LPSTR", "INT"}, true},
    {"close", "INT", {"INT"}, false},
    {"read", "INT64", {"INT", "LPVOID", "UINT64"}, false},
    {"mmap", "LPVOID", {"LPVOID", "UINT64", "INT", "INT", "INT", "INT64"}, false},
    {"time", "INT64", {"LPVOID"}, false},
};

class LinuxTypeDatabase : public TypeDatabase {
public:
    bool getFunctionType(const std::string& funcName,
                         std::string& returnType,
                         std::vector<std::string>& paramTypes) const override {
        for (const auto& f : kGlibcFuncs) {
            if (funcName == f.name) {
                returnType = f.ret;
                paramTypes.clear();
                for (const char* p : f.params)
                    paramTypes.push_back(p);
                return true;
            }
        }
        return false;
    }

    bool isVariadic(const std::string& funcName) const override {
        for (const auto& f : kGlibcFuncs) {
            if (funcName == f.name)
                return f.variadic;
        }
        return false;
    }

    bool isNoReturn(const std::string& funcName) const override {
        // glibc termination paths: the decompiler must not flow past calls
        // to these (decompiler audit: missing __stack_chk_fail merged four
        // init fragments into one function). Mirrors Ghidra's NoReturn DB.
        return funcName == "abort" || funcName == "exit" || funcName == "_exit" ||
               funcName == "_Exit" || funcName == "exit_group" ||
               funcName == "quick_exit" || funcName == "longjmp" ||
               funcName == "siglongjmp" || funcName == "__stack_chk_fail" ||
               funcName == "__assert_fail" || funcName == "__chk_fail" ||
               funcName == "__fortify_fail" || funcName == "pthread_exit" ||
               funcName == "__cxa_throw" || funcName == "_Unwind_Resume";
    }

    std::string getPlatformName() const override {
        return "Linux";
    }
};

std::unique_ptr<TypeDatabase> createLinuxTypeDatabase() {
    return std::make_unique<LinuxTypeDatabase>();
}

} // namespace ghidra
