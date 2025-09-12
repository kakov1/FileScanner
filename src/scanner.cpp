#include "scanner.hpp"
#include "thread_pool.hpp"
#include <fstream>

namespace util {
HashVerdict Scanner::readCsv(cFilePath &csv) const {
  HashVerdict infectedFiles;
  std::ifstream verdicts(csv);

  if (!verdicts.is_open()) {
    failOpenFile(csv);
  }

  std::string line;

  while (std::getline(verdicts, line)) {
    std::istringstream stream(line);
    std::string hash, verdict;

    if (std::getline(stream, hash, ';') && std::getline(stream, verdict)) {
      infectedFiles[hash] = verdict;
    }
  }

  return infectedFiles;
}

void Scanner::pushFiles(FileQueue &queue, cFilePath &path) const {

  for (auto &&item : fs::recursive_directory_iterator(path)) {
    if (item.is_regular_file()) {
      queue.push(item.path().string());
    }
  }
}

ScanResult Scanner::run(cFilePath &directory, cFilePath &csv,
                        cFilePath &log) const {
  HashVerdict verdicts = readCsv(csv);
  FileQueue queue;

  ThreadPool pool{std::thread::hardware_concurrency()};

  if (fs::exists(directory))
    pushFiles(queue, directory);
    
  queue.setFinished();

  ScanResult result = pool.processFiles(queue, log, verdicts);

  return result;
}
} // namespace util
