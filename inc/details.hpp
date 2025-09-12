#pragma once

#include <filesystem>
#include <unordered_map>

namespace util {
namespace fs = std::filesystem;

using FileNumber = size_t;
using HashVerdict = std::unordered_map<std::string, std::string>;
using cHashVerdict = const std::unordered_map<std::string, std::string>;
using FilePath = std::string;
using cFilePath = const std::string;

void failOpenFile(cFilePath &file);

std::string computeMD5(cFilePath &file);

struct ScanResult {
  FileNumber total;
  FileNumber infected;
  FileNumber errors;
};
} // namespace util