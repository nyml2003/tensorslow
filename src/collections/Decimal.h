#ifndef TORCHLIGHT_COLLECTIONS_DECIMAL_H
#define TORCHLIGHT_COLLECTIONS_DECIMAL_H

#include "collections/List.h"
#include "collections/String.h"

namespace torchlight::collections {

using collections::String;

class Decimal {
  friend class List<Decimal>;
  friend class Integer;

 private:
  List<int32_t> parts;

  bool sign = false;

 public:
  explicit Decimal() = default;
  explicit Decimal(const List<int32_t>& parts, bool sign);

  [[nodiscard]] String ToString() const;

  [[nodiscard]] List<int32_t> Data() const;

  [[nodiscard]] bool Sign() const;

  [[nodiscard]] Decimal Add(const Decimal& rhs) const;

  [[nodiscard]] Decimal Subtract(const Decimal& rhs) const;

  [[nodiscard]] Decimal Multiply(const Decimal& rhs) const;

  [[nodiscard]] Decimal Divide(const Decimal& rhs) const;

  [[nodiscard]] Decimal Modulo(const Decimal& rhs) const;

  [[nodiscard]] List<Decimal> DivMod(const Decimal& rhs) const;

  [[nodiscard]] bool GreaterThan(const Decimal& rhs) const;

  [[nodiscard]] bool Equal(const Decimal& rhs) const;

  [[nodiscard]] bool LessThan(const Decimal& rhs) const;

  [[nodiscard]] bool GreaterThanOrEqual(const Decimal& rhs) const;

  [[nodiscard]] bool LessThanOrEqual(const Decimal& rhs) const;

  [[nodiscard]] bool NotEqual(const Decimal& rhs) const;

  Decimal Negate();

  [[nodiscard]] bool IsZero() const;

  [[nodiscard]] Decimal Copy() const;
};

}  // namespace torchlight::collections

#endif  // TORCHLIGHT_UTIL_Decimal_H
