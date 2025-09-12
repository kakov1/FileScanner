#pragma once

#include "queue.hpp"
#include "details.hpp"

namespace util {

class Scanner final {
private:
  HashVerdict readCsv(cFilePath &csv) const;

  void pushFiles(FileQueue &queue, cFilePath &path) const;

public:
  ScanResult run(cFilePath &directory, cFilePath &csv, cFilePath &log) const;
};
} // namespace util