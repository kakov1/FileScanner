#pragma once

#include "queue.hpp"
#include "details.hpp"

namespace util {
std::string computeMD5(cFilePath &file);

class ThreadPool final {
private:
  size_t threadCount_;

public:
  explicit ThreadPool(size_t threadCount) : threadCount_(threadCount) {}

  ScanResult processFiles(FileQueue &queue, cFilePath &log,
                          cHashVerdict &verdicts) const;
};
} // namespace util