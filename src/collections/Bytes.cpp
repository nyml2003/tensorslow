#include "collections/Bytes.h"

namespace torchlight::collections {

Bytes::Bytes(List<Byte> value) : value(std::move(value)) {}

[[nodiscard]] List<Byte> Bytes::Value() const {
  return value;
}
}  // namespace torchlight::collections
