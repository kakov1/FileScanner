#include "details.hpp"
#include <openssl/md5.h>
#include <fstream>

namespace util {
void failOpenFile(cFilePath &file) {
  throw std::runtime_error("Не удалось открыть файл: " + file);
}

std::string computeMD5(cFilePath &file) {
  const std::size_t bufferSize = 16 * 1024;
  unsigned char buffer[bufferSize];
  unsigned char md5Result[MD5_DIGEST_LENGTH];

  std::ifstream fileStream(file, std::ios::binary);

  if (!fileStream.is_open()) {
    failOpenFile(file);
  }

  MD5_CTX md5Context;
  MD5_Init(&md5Context);

  while (fileStream.good()) {
    fileStream.read(reinterpret_cast<char *>(buffer), bufferSize);
    std::streamsize bytes = fileStream.gcount();

    if (bytes > 0) {
      MD5_Update(&md5Context, buffer,
                 bytes); // добавляет данные к текущему хэшу, без
                         // необходимости хранить сразу всё
    }
  }

  MD5_Final(md5Result, &md5Context);

  std::ostringstream oss;
  oss << std::hex << std::setfill('0');

  for (int i = 0; i < MD5_DIGEST_LENGTH; ++i) {
    oss << std::setw(2) << static_cast<int>(md5Result[i]);
  }

  return oss.str();
}
} // namespace util