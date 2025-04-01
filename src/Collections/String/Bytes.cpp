#include "Collections/String/Bytes.h"
namespace torchlight::Collections {
Bytes::Bytes(const List<Byte>& _value) : value(_value) {}
Bytes::Bytes() = default;
[[nodiscard]] Bytes Bytes::Add(const Bytes& rhs) const {
  List<Byte> bytes(value.Copy());
  bytes.Concat(rhs.value);
  return Bytes(bytes);
}
[[nodiscard]] Byte Bytes::Get(Index index) const {
  return value.Get(index);
}
const Byte& Bytes::operator[](Index index) const {
  return value[index];
}
[[nodiscard]] Index Bytes::Size() const {
  return value.Size();
}
void Bytes::Concat(const Bytes& rhs) {
  value.Concat(rhs.value);
}
void Bytes::Push(Byte byte) {
  value.Push(byte);
}
Bytes Bytes::Slice(Index start, Index end) const {
  return Bytes(value.Slice(start, end));
}
List<Byte> Bytes::Value() const {
  return value;
}
bool Bytes::Equal(const Bytes& rhs) const {
  if (Size() != rhs.Size()) {
    return false;
  }
  for (Index i = 0; i < Size(); i++) {
    if (Get(i) != rhs.Get(i)) {
      return false;
    }
  }
  return true;
}
}  // namespace torchlight::Collections
