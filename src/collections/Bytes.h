#ifndef TORCHLIGHT_COLLECTIONS_BYTES_H
#define TORCHLIGHT_COLLECTIONS_BYTES_H

#include "collections/List.h"

namespace torchlight::collections {
class Bytes {
 private:
  List<Byte> value;

 public:
  explicit Bytes(List<Byte> value);

  [[nodiscard]] List<Byte> Value() const;
};
}  // namespace torchlight::collections

#endif  // TORCHLIGHT_BYTES_H