#include "queue.hpp"

namespace util {
void FileQueue::push(cFilePath &path) {
  {
    std::lock_guard<std::mutex> lock(mtx_);
    files_.push(path);
  }

  cv_.notify_one();
}

bool FileQueue::pop(FilePath &path) {
  std::unique_lock<std::mutex> lock(mtx_);
  cv_.wait(lock, [&]() { return finished_ || !files_.empty(); });

  if (files_.empty())
    return false;

  path = files_.front();
  files_.pop();

  return true;
}

void FileQueue::setFinished() {
  {
    std::lock_guard<std::mutex> lock(mtx_);
    finished_ = true;
  }

  cv_.notify_all();
}
} // namespace util
