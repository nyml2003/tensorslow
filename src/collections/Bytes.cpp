#include "collections/Bytes.h"

namespace torchlight::collections {

Bytes::Bytes(List<Byte> value) : value(std::move(value)) {}

Bytes::Bytes(const char* value) {
  for (Index i = 0; value[i] != '\0'; ++i) {
    this->value.Add(static_cast<Byte>(value[i]));
  }
}

[[nodiscard]] List<Byte> Bytes::Value() const {
  return value;
}

[[nodiscard]] Bytes Bytes::Concat(const Bytes& rhs) const {
  Bytes bytes(value.Copy());
  bytes.value.Add(rhs.value);
  return bytes;
}

[[nodiscard]] Byte Bytes::Get(Index index) const {
  return value.Get(index);
}

[[nodiscard]] Index Bytes::Size() const {
  return value.Size();
}
}  // namespace torchlight::collections
