#ifndef TORCHLIGHT_COLLECTIONS_BYTES_H
#define TORCHLIGHT_COLLECTIONS_BYTES_H
#include "Collections/List.h"
namespace torchlight::Collections {
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
  [[nodiscard]] bool Equal(const Bytes& rhs) const;
  const Byte& operator[](Index index) const;
};
}  // namespace torchlight::Collections
#endif  // TORCHLIGHT_BYTES_H