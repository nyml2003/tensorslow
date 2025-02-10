#ifndef TORCHLIGHT_RUNTIME_BUFFEREDINPUTSTREAM_H
#define TORCHLIGHT_RUNTIME_BUFFEREDINPUTSTREAM_H

#include <cstdint>
#include <cstdio>
#include <fstream>
#include <memory>
#include <optional>

namespace torchlight::Runtime {
constexpr int BUFFER_SIZE = 128;

class BufferedInputStream {
 private:
  std::ifstream file;

 public:
  explicit BufferedInputStream(const char* filename);

  ~BufferedInputStream();

  void Close();

  std::optional<uint8_t> ReadU8();

  std::optional<uint32_t> ReadU32();
};

using BufferedInputStreamPtr = std::unique_ptr<BufferedInputStream>;

}  // namespace torchlight::Runtime

#endif  // TORCHLIGHT_BUFFEREDINPUTSTREAM_H
