#include <ghidra/storage/BranchManager.h>
#include <ghidra/storage/Repository.h>
#include <ghidra/storage/CommitManager.h>
#include <flatbuffers/flatbuffers.h>
#include <fstream>
#include <filesystem>
#include <vector>
#include <algorithm>

namespace ghidra {
namespace storage {

namespace fb = fbschema;
namespace fs = std::filesystem;

static bool readMetaFile(const std::string& path, std::vector<uint8_t>& buf) {
    if (!fs::exists(path)) return false;
    std::ifstream in(path, std::ios::binary | std::ios::ate);
    if (!in) return false;
    size_t size = static_cast<size_t>(in.tellg());
    in.seekg(0);
    buf.resize(size);
    if (!in.read(reinterpret_cast<char*>(buf.data()), static_cast<std::streamsize>(size)))
        return false;
    flatbuffers::Verifier verifier(buf.data(), buf.size());
    return fb::VerifyProjectMetadataBuffer(verifier);
}

// Null-safe flatbuffer string extraction: corrupt metadata must not crash.
static std::string fbStr(const flatbuffers::String* s) {
    return s ? s->str() : std::string();
}

bool BranchManager::createBranch(const std::string& repoPath,
                                  const std::string& branchName,
                                  const std::string& commitId) {
    if (branchName.empty()) return false;
    if (!Repository::open(repoPath)) return false;
    if (!CommitManager::commitExists(repoPath, commitId)) return false;

    std::string metaPath = Repository::getProjectMetaPath(repoPath);
    std::vector<uint8_t> buf;
    if (!readMetaFile(metaPath, buf)) return false;

    auto* meta = fb::GetProjectMetadata(buf.data());

    // Check if branch already exists
    if (meta->branches()) {
        for (auto* bp : *meta->branches()) {
            if (fbStr(bp->name()) == branchName) return false;
        }
    }

    // Rebuild with new branch added
    flatbuffers::FlatBufferBuilder builder(1024);
    auto nameStr = builder.CreateString(fbStr(meta->project_name()));
    auto binStr = builder.CreateString(fbStr(meta->binary_name()));
    auto shaStr = meta->binary_sha256() ? builder.CreateString(meta->binary_sha256()->str()) : 0;
    auto langStr = meta->language_id() ? builder.CreateString(meta->language_id()->str()) : 0;
    auto compStr = meta->compiler_spec_id() ? builder.CreateString(meta->compiler_spec_id()->str()) : 0;
    auto curBranchStr = builder.CreateString(fbStr(meta->current_branch()));
    uint64_t created = meta->created_timestamp();
    uint64_t now = static_cast<uint64_t>(std::time(nullptr));

    // Build branch list
    std::vector<flatbuffers::Offset<fb::BranchPointer>> branchOffsets;
    if (meta->branches()) {
        for (auto* bp : *meta->branches()) {
            auto n = builder.CreateString(fbStr(bp->name()));
            auto h = builder.CreateString(fbStr(bp->head_commit_id()));
            branchOffsets.push_back(fb::CreateBranchPointer(builder, n, h));
        }
    }
    {
        auto n = builder.CreateString(branchName);
        auto h = builder.CreateString(commitId);
        branchOffsets.push_back(fb::CreateBranchPointer(builder, n, h));
    }
    auto branchesVec = builder.CreateVector(branchOffsets);

    auto newMeta = fb::CreateProjectMetadata(builder, 1, 1, nameStr, binStr, shaStr,
        created, now, curBranchStr, branchesVec, langStr, compStr,
        meta->image_base());
    builder.Finish(newMeta);

    std::ofstream out(metaPath, std::ios::binary);
    if (!out) return false;
    out.write(reinterpret_cast<const char*>(builder.GetBufferPointer()),
              static_cast<std::streamsize>(builder.GetSize()));
    return out.good();
}

std::vector<BranchInfo> BranchManager::listBranches(const std::string& repoPath) {
    std::vector<BranchInfo> result;
    std::string metaPath = Repository::getProjectMetaPath(repoPath);
    std::vector<uint8_t> buf;
    if (!readMetaFile(metaPath, buf)) return result;

    auto* meta = fb::GetProjectMetadata(buf.data());
    if (meta->branches()) {
        for (auto* bp : *meta->branches()) {
            BranchInfo info;
            info.name = fbStr(bp->name());
            info.headCommitId = fbStr(bp->head_commit_id());
            result.push_back(info);
        }
    }
    return result;
}

bool BranchManager::deleteBranch(const std::string& repoPath,
                                  const std::string& branchName) {
    if (branchName.empty()) return false;
    std::string metaPath = Repository::getProjectMetaPath(repoPath);
    std::vector<uint8_t> buf;
    if (!readMetaFile(metaPath, buf)) return false;

    auto* meta = fb::GetProjectMetadata(buf.data());

    // Cannot delete current branch
    if (fbStr(meta->current_branch()) == branchName) return false;

    // Find and remove the branch
    bool found = false;
    if (meta->branches()) {
        for (auto* bp : *meta->branches()) {
            if (fbStr(bp->name()) == branchName) {
                found = true;
                break;
            }
        }
    }
    if (!found) return false;

    flatbuffers::FlatBufferBuilder builder(1024);
    auto nameStr = builder.CreateString(fbStr(meta->project_name()));
    auto binStr = builder.CreateString(fbStr(meta->binary_name()));
    auto shaStr = meta->binary_sha256() ? builder.CreateString(meta->binary_sha256()->str()) : 0;
    auto langStr = meta->language_id() ? builder.CreateString(meta->language_id()->str()) : 0;
    auto compStr = meta->compiler_spec_id() ? builder.CreateString(meta->compiler_spec_id()->str()) : 0;
    auto curBranchStr = builder.CreateString(fbStr(meta->current_branch()));
    uint64_t created = meta->created_timestamp();
    uint64_t now = static_cast<uint64_t>(std::time(nullptr));

    std::vector<flatbuffers::Offset<fb::BranchPointer>> branchOffsets;
    if (meta->branches()) {
        for (auto* bp : *meta->branches()) {
            if (fbStr(bp->name()) == branchName) continue;
            auto n = builder.CreateString(fbStr(bp->name()));
            auto h = builder.CreateString(fbStr(bp->head_commit_id()));
            branchOffsets.push_back(fb::CreateBranchPointer(builder, n, h));
        }
    }
    auto branchesVec = builder.CreateVector(branchOffsets);

    auto newMeta = fb::CreateProjectMetadata(builder, 1, 1, nameStr, binStr, shaStr,
        created, now, curBranchStr, branchesVec, langStr, compStr,
        meta->image_base());
    builder.Finish(newMeta);

    std::ofstream out(metaPath, std::ios::binary);
    if (!out) return false;
    out.write(reinterpret_cast<const char*>(builder.GetBufferPointer()),
              static_cast<std::streamsize>(builder.GetSize()));
    return out.good();
}

bool BranchManager::switchBranch(const std::string& repoPath,
                                  const std::string& branchName) {
    std::string metaPath = Repository::getProjectMetaPath(repoPath);
    std::vector<uint8_t> buf;
    if (!readMetaFile(metaPath, buf)) return false;

    auto* meta = fb::GetProjectMetadata(buf.data());

    // Verify branch exists
    bool found = false;
    if (meta->branches()) {
        for (auto* bp : *meta->branches()) {
            if (fbStr(bp->name()) == branchName) {
                found = true;
                break;
            }
        }
    }
    if (!found) return false;

    // Already on this branch
    if (fbStr(meta->current_branch()) == branchName) return true;

    flatbuffers::FlatBufferBuilder builder(1024);
    auto nameStr = builder.CreateString(fbStr(meta->project_name()));
    auto binStr = builder.CreateString(fbStr(meta->binary_name()));
    auto shaStr = meta->binary_sha256() ? builder.CreateString(meta->binary_sha256()->str()) : 0;
    auto langStr = meta->language_id() ? builder.CreateString(meta->language_id()->str()) : 0;
    auto compStr = meta->compiler_spec_id() ? builder.CreateString(meta->compiler_spec_id()->str()) : 0;
    auto curBranchStr = builder.CreateString(branchName);
    uint64_t created = meta->created_timestamp();
    uint64_t now = static_cast<uint64_t>(std::time(nullptr));

    std::vector<flatbuffers::Offset<fb::BranchPointer>> branchOffsets;
    if (meta->branches()) {
        for (auto* bp : *meta->branches()) {
            auto n = builder.CreateString(fbStr(bp->name()));
            auto h = builder.CreateString(fbStr(bp->head_commit_id()));
            branchOffsets.push_back(fb::CreateBranchPointer(builder, n, h));
        }
    }
    auto branchesVec = builder.CreateVector(branchOffsets);

    auto newMeta = fb::CreateProjectMetadata(builder, 1, 1, nameStr, binStr, shaStr,
        created, now, curBranchStr, branchesVec, langStr, compStr,
        meta->image_base());
    builder.Finish(newMeta);

    std::ofstream out(metaPath, std::ios::binary);
    if (!out) return false;
    out.write(reinterpret_cast<const char*>(builder.GetBufferPointer()),
              static_cast<std::streamsize>(builder.GetSize()));
    return out.good();
}

std::string BranchManager::getCurrentBranch(const std::string& repoPath) {
    std::string metaPath = Repository::getProjectMetaPath(repoPath);
    std::vector<uint8_t> buf;
    if (!readMetaFile(metaPath, buf)) return "";
    auto* meta = fb::GetProjectMetadata(buf.data());
    return fbStr(meta->current_branch());
}

std::string BranchManager::getBranchCommit(const std::string& repoPath,
                                            const std::string& branchName) {
    std::string metaPath = Repository::getProjectMetaPath(repoPath);
    std::vector<uint8_t> buf;
    if (!readMetaFile(metaPath, buf)) return "";
    auto* meta = fb::GetProjectMetadata(buf.data());
    if (meta->branches()) {
        for (auto* bp : *meta->branches()) {
            if (fbStr(bp->name()) == branchName) {
                return fbStr(bp->head_commit_id());
            }
        }
    }
    return "";
}

bool BranchManager::branchExists(const std::string& repoPath,
                                  const std::string& branchName) {
    std::string metaPath = Repository::getProjectMetaPath(repoPath);
    std::vector<uint8_t> buf;
    if (!readMetaFile(metaPath, buf)) return false;
    auto* meta = fb::GetProjectMetadata(buf.data());
    if (meta->branches()) {
        for (auto* bp : *meta->branches()) {
            if (fbStr(bp->name()) == branchName) return true;
        }
    }
    return false;
}

bool BranchManager::advanceBranch(const std::string& repoPath,
                                   const std::string& branchName,
                                   const std::string& commitId) {
    if (branchName.empty() || commitId.empty()) return false;
    if (!CommitManager::commitExists(repoPath, commitId)) return false;

    std::string metaPath = Repository::getProjectMetaPath(repoPath);
    std::vector<uint8_t> buf;
    if (!readMetaFile(metaPath, buf)) return false;

    auto* meta = fb::GetProjectMetadata(buf.data());

    bool found = false;
    if (meta->branches()) {
        for (auto* bp : *meta->branches()) {
            if (fbStr(bp->name()) == branchName) {
                found = true;
                break;
            }
        }
    }
    if (!found) return false;

    flatbuffers::FlatBufferBuilder builder(1024);
    auto nameStr = builder.CreateString(fbStr(meta->project_name()));
    auto binStr = builder.CreateString(fbStr(meta->binary_name()));
    auto shaStr = meta->binary_sha256() ? builder.CreateString(meta->binary_sha256()->str()) : 0;
    auto langStr = meta->language_id() ? builder.CreateString(meta->language_id()->str()) : 0;
    auto compStr = meta->compiler_spec_id() ? builder.CreateString(meta->compiler_spec_id()->str()) : 0;
    auto curBranchStr = builder.CreateString(fbStr(meta->current_branch()));
    uint64_t created = meta->created_timestamp();
    uint64_t now = static_cast<uint64_t>(std::time(nullptr));

    std::vector<flatbuffers::Offset<fb::BranchPointer>> branchOffsets;
    if (meta->branches()) {
        for (auto* bp : *meta->branches()) {
            auto n = builder.CreateString(fbStr(bp->name()));
            std::string headId = (fbStr(bp->name()) == branchName) ? commitId : fbStr(bp->head_commit_id());
            auto h = builder.CreateString(headId);
            branchOffsets.push_back(fb::CreateBranchPointer(builder, n, h));
        }
    }
    auto branchesVec = builder.CreateVector(branchOffsets);

    auto newMeta = fb::CreateProjectMetadata(builder, 1, 1, nameStr, binStr, shaStr,
        created, now, curBranchStr, branchesVec, langStr, compStr,
        meta->image_base());
    builder.Finish(newMeta);

    std::ofstream out(metaPath, std::ios::binary);
    if (!out) return false;
    out.write(reinterpret_cast<const char*>(builder.GetBufferPointer()),
              static_cast<std::streamsize>(builder.GetSize()));
    return out.good();
}

} // namespace storage
} // namespace ghidra
