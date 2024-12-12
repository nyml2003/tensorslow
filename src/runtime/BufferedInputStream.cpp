#include <optional>
#include <stdexcept>
#include "runtime/BufferedInputStream.h"

namespace torchlight::runtime {

BufferedInputStream::BufferedInputStream(const char* filename) {
  file.open(filename, std::ios::binary);
  if (!file.is_open()) {
    throw std::runtime_error("Error opening file");
  }
}

BufferedInputStream::~BufferedInputStream() {
  Close();
}

void BufferedInputStream::Close() {
  if (file.is_open()) {
    file.close();
  }
}

std::optional<uint32_t> BufferedInputStream::ReadU32() {
  if (!file.is_open()) {
    return std::nullopt;
  }
  uint32_t buffer = 0;
  file.read(reinterpret_cast<char*>(&buffer), sizeof(uint32_t));
  if (file.eof()) {
    file.close();
  }
  return buffer;
}

std::optional<uint8_t> BufferedInputStream::ReadU8() {
  if (!file.is_open()) {
    return std::nullopt;
  }
  uint8_t buffer = 0;
  file.read(reinterpret_cast<char*>(&buffer), sizeof(uint8_t));
  if (file.eof()) {
    file.close();
  }
  return buffer;
}

}  // namespace torchlight::runtime