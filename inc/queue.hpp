#pragma once

#include "details.hpp"
#include <condition_variable>
#include <iostream>
#include <mutex>
#include <queue>

namespace util {
class FileQueue final {
private:
  std::queue<std::string> files_;
  std::mutex mtx_;
  std::condition_variable cv_;
  bool finished_ = false;

public:
  void push(cFilePath &path);

  bool pop(FilePath &path);

  void setFinished();
};
} // namespace util