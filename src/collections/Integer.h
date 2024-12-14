#ifndef TORCHLIGHT_COLLECTIONS_INTEGER_H
#define TORCHLIGHT_COLLECTIONS_INTEGER_H

#include "collections/Decimal.h"
#include "collections/List.h"
#include "collections/String.h"
#include "collections/common.h"

namespace torchlight::collections {

class Integer {
  friend class List<Integer>;

 private:
  List<uint32_t> parts;

  bool isNegative = false;

  /**
   * @brief 将Unicode字符转换为0-F的数字
   *
   * @param c
   * @return int32_t
   */
  static int UnicodeToHex(Unicode c) noexcept;

  static Unicode HexToUnicode(uint8_t c) noexcept;

  /**
   * @brief 判断字符串是否为负数
   *
   * @param str
   * @return bool
   */
  static bool IsNegative(const String& str);

  /**
   * @brief 构造一个空Integer
   */
  explicit Integer() = default;

  /**
   * @brief 转化为Decimal
   *
   * @param str
   */
  [[nodiscard]] Decimal ToDecimal() const;

  /**
   * @brief 从Decimal构造Integer
   *
   * @param decimal
   */
  void FromDecimal(const Decimal& decimal);

  [[nodiscard]] Integer Reverse() const;

  void TrimLeadingZero();

  void TrimTrailingZero();

  [[nodiscard]] Integer Slice(Index start, Index end) const;

 public:
  /**
   * @brief 使用Unicode字符串构造Integer
   *
   * @param str
   */
  explicit Integer(const String& str);

  /**
   * @brief 重新还原为字符串
   *
   * @return String
   */
  [[nodiscard]] String ToHexString() const;

  [[nodiscard]] String ToString() const;

  void Assign(const Integer& rhs);

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

  [[nodiscard]] Integer Copy() const;
};

}  // namespace torchlight::collections

#endif  // TORCHLIGHT_collections_INTEGER_H
