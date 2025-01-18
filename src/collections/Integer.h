#ifndef TORCHLIGHT_COLLECTIONS_INTEGER_H
#define TORCHLIGHT_COLLECTIONS_INTEGER_H
#include "Collections/Bytes.h"
#include "Collections/Decimal.h"
#include "Collections/List.h"
#include "Collections/String.h"
namespace torchlight::Collections {
class Integer {
  friend class List<Integer>;

 private:
  List<uint32_t> parts;
  bool sign = false;

 public:
  explicit Integer();
  explicit Integer(const List<uint32_t>& _parts, bool _sign);
  [[nodiscard]] List<uint32_t> Data() const;
  [[nodiscard]] bool Sign() const;
  [[nodiscard]] String ToHexString() const;
  [[nodiscard]] String ToString() const;
  [[nodiscard]] Bytes Serialize() const;
  [[nodiscard]] Integer Add(const Integer& rhs) const;
  [[nodiscard]] Integer Subtract(const Integer& rhs) const;
  [[nodiscard]] Integer Multiply(const Integer& rhs) const;
  [[nodiscard]] Integer Divide(const Integer& rhs) const;
  [[nodiscard]] Integer Modulo(const Integer& rhs) const;
  [[nodiscard]] List<Integer> DivMod(const Integer& rhs) const;
  [[nodiscard]] Integer BitWiseAnd(const Integer& rhs) const;
  [[nodiscard]] Integer BitWiseOr(const Integer& rhs) const;
  [[nodiscard]] Integer BitWiseXor(const Integer& rhs) const;
  [[nodiscard]] Integer BitWiseNot() const;
  [[nodiscard]] bool GreaterThan(const Integer& rhs) const;
  [[nodiscard]] bool Equal(const Integer& rhs) const;
  [[nodiscard]] bool LessThan(const Integer& rhs) const;
  [[nodiscard]] bool GreaterThanOrEqual(const Integer& rhs) const;
  [[nodiscard]] bool LessThanOrEqual(const Integer& rhs) const;
  [[nodiscard]] bool NotEqual(const Integer& rhs) const;
  [[nodiscard]] bool IsZero() const;
  [[nodiscard]] Integer Copy() const;
};
}  // namespace torchlight::Collections
#endif  // TORCHLIGHT_COLLECTIONS_INTEGER_H
