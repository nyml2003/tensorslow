#ifndef TORCHLIGHT_COLLECTIONS_BYTES_H
#define TORCHLIGHT_COLLECTIONS_BYTES_H

#include "collections/List.h"

namespace torchlight::collections {
class Bytes {
 private:
  List<Byte> value;

 public:
  explicit Bytes(const List<Byte>& value);
  explicit Bytes();

  [[nodiscard]] Bytes Add(const Bytes& rhs) const;

  [[nodiscard]] List<Byte> Value() const;

  void Concat(const Bytes& rhs);

  void Push(Byte byte);

  [[nodiscard]] Byte Get(Index index) const;

  [[nodiscard]] Index Size() const;

  [[nodiscard]] Bytes Slice(Index start, Index end) const;

  Byte& operator[](Index index);

  const Byte& operator[](Index index) const;
};
}  // namespace torchlight::collections

#endif  // TORCHLIGHT_BYTES_H