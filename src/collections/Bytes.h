#ifndef TORCHLIGHT_COLLECTIONS_BYTES_H
#define TORCHLIGHT_COLLECTIONS_BYTES_H

#include "collections/List.h"

namespace torchlight::collections {
class Bytes {
 private:
  List<Byte> value;

 public:
  explicit Bytes(List<Byte> value);

  explicit Bytes() = default;

  explicit Bytes(const char* value);

  [[nodiscard]] List<Byte> Value() const;

  [[nodiscard]] Bytes Concat(const Bytes& rhs) const;

  [[nodiscard]] Byte Get(Index index) const;

  [[nodiscard]] Index Size() const;
};
}  // namespace torchlight::collections

#endif  // TORCHLIGHT_BYTES_H