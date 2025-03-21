#ifndef TORCHLIGHT_COLLECTIONS_INTEGER_H
#define TORCHLIGHT_COLLECTIONS_INTEGER_H
#include "Collections/Integer/Decimal.h"
#include "Collections/List.h"
#include "Collections/String/Bytes.h"
#include "Collections/String/String.h"


namespace torchlight::Collections {
class Integer {
  friend class List<Integer>;

 private:
  List<uint32_t> parts;
  bool sign = false;

 public:
  enum class IntSign { Positive = 0, Negative = 1 };
  explicit Integer();
  explicit Integer(const List<uint32_t>& _parts, bool _sign);
  [[nodiscard]] List<uint32_t> Data() const;
  [[nodiscard]] bool Sign() const;
  [[nodiscard]] IntSign GetSign() const;
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
  [[nodiscard]] Integer Negate() const;
  [[nodiscard]] Integer Power(const Integer& rhs) const;
  [[nodiscard]] Integer LeftShift(const Integer& rhs) const;
  [[nodiscard]] Integer RightShift(const Integer& rhs) const;
};
}  // namespace torchlight::Collections
#endif  // TORCHLIGHT_COLLECTIONS_INTEGER_H
