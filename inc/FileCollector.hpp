#pragma once

#include <iostream>
#include <memory>
#include <mutex>
#include <optional>
#include <unordered_map>
#include <vector>

namespace files {
class FileCollector final {
private:
  struct File;

private:
  using size_type = std::size_t;
  using id_type = uint32_t;
  using byte_type = uint8_t;
  using pFile = File *;
  using chunk_vector = std::vector<byte_type>;
  using file_optional = std::optional<chunk_vector>;
  using lock = std::lock_guard<std::mutex>;

private:
  struct File final {
    size_type size_ = 0;
    size_type curSize_ = 0;
    bool isDone_ = false;
    
    chunk_vector chunks_;
    chunk_vector flags_;

    std::mutex mutex_;

    File() = default;

    File(const File &file);
  };

private:
  std::unordered_map<id_type, File> files_;
  std::mutex mutex_;

private:
  pFile FindFile(id_type fileId);

  void putChunks(pFile file, size_type start_pos, chunk_vector &&chunk);

public:
  void CollectFile(id_type fileId, size_type fileSize);

  void OnNewChunk(id_type fileId, size_type start_pos, chunk_vector &&chunk);

  file_optional
  GetFile(id_type fileId); // я выбрал такой интерфейс. Возвращается копия, с
                           // точки зрения копирования больших файлов это плохо,
                           // т.к. тратится время, лучше было бы возвращать
                           // ссылку, но это не потокобезопасно.
};
} // namespace files