#ifndef TORCHLIGHT_COLLECTIONS_DECIMAL_H
#define TORCHLIGHT_COLLECTIONS_DECIMAL_H

#include "collections/Bytes.h"
#include "collections/List.h"
#include "collections/String.h"
#include "collections/common.h"

namespace torchlight::collections {
class Decimal {
  friend class List<Decimal>;
  friend class Integer;

 private:
  List<int32_t> parts;

  bool isNegative = false;

  static int UnicodeToInt(Unicode c) noexcept;

  static bool IsNegative(const String& str);

  static bool IsNegative(const Bytes& str);

  [[nodiscard]] Decimal Slice(Index start, Index end) const;

  explicit Decimal();

 public:
  explicit Decimal(const String& str);

  explicit Decimal(const Bytes& str);

  explicit Decimal(int32_t value);

  [[nodiscard]] String ToString() const;

  [[nodiscard]] Decimal Add(const Decimal& rhs) const;

  [[nodiscard]] Decimal Subtract(const Decimal& rhs) const;

  [[nodiscard]] Decimal Multiply(const Decimal& rhs) const;

  [[nodiscard]] Decimal Divide(const Decimal& rhs) const;

  [[nodiscard]] Decimal Modulo(const Decimal& rhs) const;

  [[nodiscard]] List<Decimal> DivMod(const Decimal& rhs) const;

  [[nodiscard]] bool GreaterThan(const Decimal& rhs) const;

  [[nodiscard]] bool Equal(const Decimal& rhs) const;

  [[nodiscard]] bool LessThan(const Decimal& rhs) const {
    return !GreaterThan(rhs) && !Equal(rhs);
  }

  [[nodiscard]] bool GreaterThanOrEqual(const Decimal& rhs) const {
    return GreaterThan(rhs) || Equal(rhs);
  }

  [[nodiscard]] bool LessThanOrEqual(const Decimal& rhs) const {
    return LessThan(rhs) || Equal(rhs);
  }

  [[nodiscard]] bool NotEqual(const Decimal& rhs) const { return !Equal(rhs); }

  /**
   * @brief 取反
   */
  Decimal Negate();

  /**
   * @brief 判断是否为0
   */
  [[nodiscard]] bool IsZero() const;

  /**
   * @brief 反转数字
   */
  [[nodiscard]] Decimal Reverse() const;

  [[nodiscard]] Decimal Copy() const;

  /*
   * @brief 去除前导0
   */
  void TrimLeadingZero();

  void TrimTrailingZero();
};

}  // namespace torchlight::collections

#endif  // TORCHLIGHT_UTIL_Decimal_H
