#pragma once
#include <ghidra/storage/EventLog.h>
#include <ghidra/ProgramDB.h>
#include <string>
#include <vector>

namespace ghidra {
namespace storage {

struct ChangeEntry {
    fbschema::ChangeType type = static_cast<fbschema::ChangeType>(0);
    uint64_t             address = 0;
    std::string          name;
    std::string          oldValue;
    std::string          newValue;
};

struct CommitInfo {
    std::string commitId;
    std::string parentCommitId;
    std::string snapshotSha256;
    uint64_t    snapshotSize = 0;
    uint64_t    timestamp = 0;
    std::string message;
    std::string branchName;
    std::string author;
    int         changeCount = 0;
};

class CommitManager {
public:
    static std::string createCommit(const std::string& repoPath,
                                     const std::string& parentCommitId,
                                     const std::string& message,
                                     const std::string& author,
                                     const std::string& branchName,
                                     ProgramDB& program,
                                     EventLog& eventLog);

    static bool loadCommitMeta(const std::string& repoPath,
                                const std::string& commitId,
                                CommitInfo& info);

    static std::vector<std::string> listCommits(const std::string& repoPath);

    static bool loadChangeSet(const std::string& repoPath,
                               const std::string& commitId,
                               std::vector<ChangeEntry>& changes);

    static bool commitExists(const std::string& repoPath, const std::string& commitId);

private:
    static std::string generateCommitId();
    static std::vector<uint8_t> generateChangeSet(const std::string& commitId,
                                                    const std::string& parentCommitId,
                                                    EventLog& eventLog);
};

} // namespace storage
} // namespace ghidra
