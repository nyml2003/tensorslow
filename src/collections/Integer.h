#ifndef TORCHLIGHT_COLLECTIONS_INTEGER_H
#define TORCHLIGHT_COLLECTIONS_INTEGER_H

#include "collections/List.h"
#include "collections/String.h"
#include "collections/common.h"

namespace torchlight::collections {

class Integer {
 private:
  List<int> parts;

  bool isNegative = false;

  static int UnicodeToInt(Unicode c) noexcept;

  static bool IsNegative(const String& str);

  [[nodiscard]] Integer Slice(Index start, Index end) const;

 public:
  explicit Integer(const String& str);

  explicit Integer();

  explicit Integer(int value);

  explicit Integer(Index capacity);

  static Integer FromIndex(Index index);

  [[nodiscard]] String ToString() const;

  [[nodiscard]] Integer Add(const Integer& rhs) const;

  [[nodiscard]] Integer Subtract(const Integer& rhs) const;

  [[nodiscard]] Integer Multiply(const Integer& rhs) const;

  [[nodiscard]] Integer Divide(const Integer& rhs) const;

  [[nodiscard]] Integer Modulo(const Integer& rhs) const;

  [[nodiscard]] List<Integer> DivMod(const Integer& rhs) const;

  [[nodiscard]] bool GreaterThan(const Integer& rhs) const;

  [[nodiscard]] bool Equal(const Integer& rhs) const;

  [[nodiscard]] bool LessThan(const Integer& rhs) const {
    return !GreaterThan(rhs) && !Equal(rhs);
  }

  [[nodiscard]] bool GreaterThanOrEqual(const Integer& rhs) const {
    return GreaterThan(rhs) || Equal(rhs);
  }

  [[nodiscard]] bool LessThanOrEqual(const Integer& rhs) const {
    return LessThan(rhs) || Equal(rhs);
  }

  [[nodiscard]] bool NotEqual(const Integer& rhs) const { return !Equal(rhs); }

  /**
   * @brief 取反
   */
  Integer Negate();

  /**
   * @brief 判断是否为0
   */
  [[nodiscard]] bool IsZero() const;

  /**
   * @brief 反转数字
   */
  [[nodiscard]] Integer Reverse() const;

  [[nodiscard]] Integer Copy() const;

  /*
   * @brief 去除前导0
   */
  void TrimLeadingZero();

  void TrimTrailingZero();
};

}  // namespace torchlight::collections

#endif  // TORCHLIGHT_collections_INTEGER_H
