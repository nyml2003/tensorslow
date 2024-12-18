#include "bytecode/utils.h"

#include <cstring>

namespace torchlight::bytecode {

uint8_t SerializeByteCode(ByteCode code) {
  return static_cast<uint8_t>(code);
}

void SerializeUInt32(uint32_t value, const char* value_str) {
  const char* value_uint32 = reinterpret_cast<const char*>(&value);
  std::memcpy(const_cast<char*>(value_str), value_uint32, sizeof(uint32_t));
}

}  // namespace torchlight::bytecode