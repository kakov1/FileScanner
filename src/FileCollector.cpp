#include "FileCollector.hpp"

namespace files {
FileCollector::File::File(const File &file) {
  size_ = file.size_;
  chunks_ = file.chunks_;
  flags_ = file.flags_;
}

auto FileCollector::FindFile(id_type fileId) -> pFile {
  lock fileLock{mutex_};

  auto file_it = files_.find(fileId);

  if (file_it == files_.end())
    return nullptr;

  return std::addressof(file_it->second);
}

void FileCollector::putChunks(pFile file, size_type start_pos,
                              chunk_vector &&chunk) {
  if (file->size_ <= start_pos)
    return;

  if (file->isDone_)
    return;

  auto chunk_size = chunk.size();

  for (auto pos = start_pos; pos < file->size_ && pos < start_pos + chunk_size;
       ++pos) {
    if (file->flags_[pos] == 0) {
      file->chunks_[pos] = std::move(chunk[pos - start_pos]);
      file->flags_[pos] = 1;
      ++file->curSize_;
    }
  }

  if (file->curSize_ == file->size_)
    file->isDone_ = true;
}

void FileCollector::CollectFile(id_type fileId, size_type fileSize) {
  lock FileLock{mutex_};

  if (files_.find(fileId) == files_.end()) {
    auto &file = files_[fileId];
    file.size_ = fileSize;
    file.chunks_.resize(fileSize);
    file.flags_.resize(fileSize);
  }
}

void FileCollector::OnNewChunk(id_type fileId, size_type start_pos,
                               chunk_vector &&chunk) {
  pFile file;

  {
    file = FindFile(fileId);

    if (!file)
      return;
  }

  lock fileLock{file->mutex_};

  putChunks(file, start_pos, std::move(chunk));
}

auto FileCollector::GetFile(id_type fileId) -> file_optional {
  pFile file;

  {
    file = FindFile(fileId);

    if (!file)
      return std::nullopt;
  }

  lock fileLock(file->mutex_);

  return file->chunks_;
}
} // namespace files
