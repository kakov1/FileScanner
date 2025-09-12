#include "thread_pool.hpp"
#include <atomic>
#include <filesystem>
#include <fstream>
#include <mutex>
#include <thread>

namespace util {
ScanResult ThreadPool::processFiles(FileQueue &queue, cFilePath &log,
                                    cHashVerdict &verdicts) const {
  std::atomic<size_t> total{0}, infected{0}, errors{0};
  std::mutex logMutex;
  std::ofstream logFile(log);

  std::vector<std::thread> workers;

  for (int i = 0; i < threadCount_; ++i) {
    workers.emplace_back([&]() {
      std::string filePath;

      while (queue.pop(filePath)) {
        try {
          std::string md5 = computeMD5(filePath);
          ++total;

          auto it = verdicts.find(md5);

          if (it != verdicts.end()) {
            ++infected;
            std::lock_guard<std::mutex> lock(logMutex);
            logFile << filePath << ";" << md5 << ";" << it->second << "\n";
          }
        } catch (const std::exception &e) {
          ++errors;
        }
      }
    });
  }

  for (auto &&th : workers) {
    if (th.joinable())
      th.join();
  }

  return {total.load(), infected.load(), errors.load()};
}
} // namespace util