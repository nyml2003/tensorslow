#include "Collections/Integer.h"
#include <stdexcept>
#include "Collections/Decimal.h"
#include "Collections/DecimalHelper.h"
#include "Collections/IntegerHelper.h"
#include "Collections/Iterator.h"
#include "Collections/StringHelper.h"

namespace torchlight::Collections {
Integer::Integer(const List<uint32_t>& _parts, bool _sign)
  : parts(_parts), sign(_sign) {}
Integer::Integer() = default;
bool Integer::Sign() const {
  return sign;
}
Integer::IntSign Integer::GetSign() const {
  return sign ? IntSign::Negative : IntSign::Positive;
}
String Integer::ToString() const {
  return CreateDecimalWithInteger(*this).ToString();
}
String Integer::ToHexString() const {
  if (IsZero()) {
    return CreateStringWithCString("0");
  }
  const Unicode UnicodeDigitZero = 0x30;
  const Unicode UnicodeDigit_x = 0x78;
  List<Unicode> str;
  for (Index i = 0; i < parts.Size(); i++) {
    uint32_t item = parts.Get(i);
    std::array<uint8_t, 4> buffer = {0};
    buffer[0] = (item & 0x0000F000) >> 12;
    buffer[1] = (item & 0x00000F00) >> 8;
    buffer[2] = (item & 0x000000F0) >> 4;
    buffer[3] = (item & 0x0000000F);
    for (Index j = 0; j < 4; j++) {
      str.Push(HexToUnicode(buffer[j]));
    }
  }
  Index it = 0;
  for (; it < str.Size(); it++) {
    if (str.Get(it) != UnicodeDigitZero) {
      break;
    }
  }
  str = str.Slice(it, str.Size());
  str.Unshift(UnicodeDigit_x);
  str.Unshift(UnicodeDigitZero);
  return String(str);
}
Integer Integer::Add(const Integer& rhs) const {
  if (sign == rhs.sign) {
    uint32_t carry = 0;
    List<uint32_t> result;
    for (auto itl = Iterator<uint32_t>::RBegin(parts),
              itr = Iterator<uint32_t>::RBegin(rhs.parts);
         !itl.End() || !itr.End(); itl.Next(), itr.Next()) {
      uint32_t sum = carry;
      if (!itl.End()) {
        sum += itl.Get();
      }
      if (!itr.End()) {
        sum += itr.Get();
      }
      // 进位是高16位
      carry = (sum >> 16) & 0x0000FFFF;
      sum &= 0x0000FFFF;
      result.Push(sum);
    }
    if (carry != 0) {
      result.Push(carry);
    }
    result.Reverse();
    return Integer(result, sign);
  }
  return Subtract(Integer(rhs.parts, !rhs.sign));
}

Integer Integer::Copy() const {
  Integer newInteger;
  newInteger.parts = parts.Copy();
  newInteger.sign = sign;
  return newInteger;
}
bool Integer::GreaterThan(const Integer& rhs) const {
  bool lzero = IsZero();
  bool rzero = rhs.IsZero();
  if (lzero && rzero) {
    return false;
  }
  if (lzero) {
    return rhs.sign;
  }
  if (rzero) {
    return !sign;
  }
  // 如果左值是负数，右值是正数，那么左值一定比右值小
  if (sign && !rhs.sign) {
    return false;
  }
  // 如果左值是正数，右值是负数，那么左值一定比右值大
  if (!sign && rhs.sign) {
    return true;
  }
  // 此时左值和右值正负号相同
  if (parts.Size() != rhs.parts.Size()) {
    // 正号，位数多的数大；负号，位数少的数大
    return sign ^ (parts.Size() > rhs.parts.Size());
  }
  // 此时左值和右值的位数相等，正负号相同
  for (auto it = Iterator<uint32_t>::Begin(parts),
            it2 = Iterator<uint32_t>::Begin(rhs.parts);
       !it.End() && !it2.End(); it.Next(), it2.Next()) {
    if (it.Get() == it2.Get()) {
      continue;
    }
    return sign ^ (it.Get() > it2.Get());
  }
  return false;
}
Integer Integer::Subtract(const Integer& rhs) const {
  // 正负号相同
  if (sign == rhs.sign) {
    // 假定左值大于右值
    bool _sign = false;
    Index size = 0;
    List<uint32_t> _lhs = parts.Copy();
    _lhs.Reverse();
    List<uint32_t> _rhs = rhs.parts.Copy();
    _rhs.Reverse();
    if (_lhs.Size() > _rhs.Size()) {
      _rhs.Concat(List<uint32_t>(_lhs.Size() - _rhs.Size(), (uint32_t)0));
      size = _lhs.Size();
    } else if (_lhs.Size() < _rhs.Size()) {
      _lhs.Concat(List<uint32_t>(_rhs.Size() - _lhs.Size(), (uint32_t)0));
      size = _rhs.Size();
      _sign = true;
      std::swap(_lhs, _rhs);
    } else {
      size = _lhs.Size();
      for (auto it = Iterator<uint32_t>::RBegin(_lhs),
                it2 = Iterator<uint32_t>::RBegin(_rhs);
           !it.End() && !it2.End(); it.Next(), it2.Next()) {
        if (it.Get() > it2.Get()) {
          break;
        }
        if (it.Get() < it2.Get()) {
          _sign = true;
          std::swap(_lhs, _rhs);
          break;
        }
      }
    }
    List<uint32_t> result(size);
    bool borrow = false;
    for (auto it = Iterator<uint32_t>::Begin(_lhs),
              it2 = Iterator<uint32_t>::Begin(_rhs);
         !it.End() && !it2.End(); it.Next(), it2.Next()) {
      uint32_t diff = 0;
      uint32_t sub = it2.Get() + (borrow ? 1 : 0);
      if (it.Get() < sub) {
        diff = 0x10000 + it.Get() - sub;
        borrow = true;
      } else {
        diff = it.Get() - sub;
        borrow = false;
      }
      result.Push(diff);
    }
    TrimTrailingZero(result);
    result.Reverse();
    return Integer(result, _sign ^ sign);
  }
  return Add(Integer(rhs.parts, !rhs.sign));
}
Integer Integer::Multiply(const Integer& rhs) const {
  if (IsZero() || rhs.IsZero()) {
    return CreateIntegerZero();
  }
  List<uint32_t> result(parts.Size() + rhs.parts.Size() + 1);
  result.Fill(0);
  auto _lhs = parts;
  _lhs.Reverse();
  auto _rhs = rhs.parts;
  _rhs.Reverse();
  for (auto it = Iterator<uint32_t>::Begin(_lhs); !it.End(); it.Next()) {
    for (auto it2 = Iterator<uint32_t>::Begin(_rhs); !it2.End(); it2.Next()) {
      uint32_t product = it.Get() * it2.Get();
      Index index = it.GetCurrentIndex() + it2.GetCurrentIndex();
      result.Set(index, result.Get(index) + product);
      result.Set(index + 1, result.Get(index + 1) + (result.Get(index) >> 16));
      result.Set(index, (result.Get(index) & 0x0000FFFF));
    }
  }
  TrimTrailingZero(result);
  result.Reverse();
  return Integer(result, sign ^ rhs.sign);
}
Integer Integer::Divide(const Integer& rhs) const {
  return DivMod(rhs).Get(0);
}
Integer Integer::Modulo(const Integer& rhs) const {
  return DivMod(rhs).Get(1);
}
List<Integer> Integer::DivMod(const Integer& rhs) const {
  if (rhs.IsZero()) {
    throw std::runtime_error("Division by zero");
  }
  if (IsZero() || LessThan(rhs)) {
    List<Integer> divmods = {CreateIntegerZero(), Copy()};
    return divmods;
  }
  if (Equal(rhs)) {
    List<Integer> divmods = {CreateIntegerOne(), CreateIntegerZero()};
    return divmods;
  }
  Integer result;
  result.sign = sign ^ rhs.sign;
  Integer dividend =
    Slice(*this, 0, std::min(parts.Size(), rhs.parts.Size())).Copy();
  dividend.sign = false;
  Integer divisor = rhs.Copy();
  divisor.sign = false;
  for (Index i = 0; i < parts.Size() - rhs.parts.Size() + 1; i++) {
    uint32_t quotient = 0;
    while (dividend.GreaterThanOrEqual(divisor)) {
      dividend = dividend.Subtract(divisor);
      quotient++;
    }
    result.parts.Push(quotient);
    if (i + rhs.parts.Size() < parts.Size()) {
      dividend.parts.Push(parts.Get(i + rhs.parts.Size()));
    }
    TrimLeadingZero(dividend.parts);
  }
  List<Integer> divmods;
  TrimTrailingZero(result.parts);
  TrimTrailingZero(dividend.parts);
  divmods.Push(result);
  divmods.Push(dividend);
  return divmods;
}
bool Integer::IsZero() const {
  if (parts.Size() == 0) {
    return true;
  }
  for (auto it = Iterator<uint32_t>::Begin(parts); !it.End(); it.Next()) {
    if (it.Get() != 0) {
      return false;
    }
  }
  return true;
}
bool Integer::Equal(const Integer& rhs) const {
  if (IsZero() && rhs.IsZero()) {
    return true;
  }
  if (sign != rhs.sign) {
    return false;
  }
  if (parts.Size() != rhs.parts.Size()) {
    return false;
  }
  for (Index i = 0; i < parts.Size(); i++) {
    if (parts.Get(i) != rhs.parts.Get(i)) {
      return false;
    }
  }
  return true;
}
Integer Integer::BitWiseAnd(const Integer& rhs) const {
  List<uint32_t> result(std::max(parts.Size(), rhs.parts.Size()));
  for (auto it = Iterator<uint32_t>::RBegin(parts),
            it2 = Iterator<uint32_t>::RBegin(rhs.parts);
       !it.End() || !it2.End(); it.Next(), it2.Next()) {
    if (it.End() || it2.End()) {
      result.Push(0);
    } else {
      result.Push(it.Get() & it2.Get());
    }
  }
  result.Reverse();
  return Integer(result, sign ^ rhs.sign);
}
Integer Integer::BitWiseOr(const Integer& rhs) const {
  List<uint32_t> result(std::max(parts.Size(), rhs.parts.Size()));
  for (auto it = Iterator<uint32_t>::RBegin(parts),
            it2 = Iterator<uint32_t>::RBegin(rhs.parts);
       !it.End() || !it2.End(); it.Next(), it2.Next()) {
    if (it.End()) {
      result.Push(it2.Get());
    } else if (it2.End()) {
      result.Push(it.Get());
    } else {
      result.Push(it.Get() | it2.Get());
    }
  }
  result.Reverse();
  return Integer(result, sign ^ rhs.sign);
}
Integer Integer::BitWiseXor(const Integer& rhs) const {
  List<uint32_t> result(std::max(parts.Size(), rhs.parts.Size()));
  for (auto it = Iterator<uint32_t>::RBegin(parts),
            it2 = Iterator<uint32_t>::RBegin(rhs.parts);
       !it.End() || !it2.End(); it.Next(), it2.Next()) {
    if (it.End()) {
      result.Push(it2.Get());
    } else if (it2.End()) {
      result.Push(it.Get());
    } else {
      result.Push(it.Get() ^ it2.Get());
    }
  }
  result.Reverse();
  return Integer(result, sign ^ rhs.sign);
}
Integer Integer::BitWiseNot() const {
  List<uint32_t> result(parts.Size());
  for (auto it = Iterator<uint32_t>::Begin(parts); !it.End(); it.Next()) {
    result.Push(~it.Get());
  }
  return Integer(result, !sign);
}
bool Integer::LessThan(const Integer& rhs) const {
  return !GreaterThan(rhs) && !Equal(rhs);
}
bool Integer::GreaterThanOrEqual(const Integer& rhs) const {
  return GreaterThan(rhs) || Equal(rhs);
}
bool Integer::LessThanOrEqual(const Integer& rhs) const {
  return !GreaterThan(rhs);
}
bool Integer::NotEqual(const Integer& rhs) const {
  return !Equal(rhs);
}
List<uint32_t> Integer::Data() const {
  return parts;
}

Integer Integer::Negate() const {
  return Integer(parts, !sign);
}

Integer Integer::Power(const Integer& rhs) const {
  if (rhs.sign) {
    throw std::runtime_error("Exponent must be non-negative");
  }
  if (rhs.IsZero()) {
    return CreateIntegerOne();
  }
  if (rhs.Equal(CreateIntegerOne())) {
    return Copy();
  }
  if (rhs.Equal(CreateIntegerTwo())) {
    return Multiply(*this);
  }
  Integer result = CreateIntegerOne();
  Integer base = Copy();
  Integer exponent = rhs.Copy();
  while (!exponent.IsZero()) {
    if ((exponent.parts.Get(0) & 1) != 0U) {
      result = result.Multiply(base);
    }
    base = base.Multiply(base);
    exponent = exponent.RightShift(CreateIntegerOne());
  }
  return result;
}

Integer Integer::LeftShift(const Integer& rhs) const {
  if (rhs.sign) {
    throw std::runtime_error("Shift count must be non-negative");
  }
  if (rhs.IsZero()) {
    return Copy();
  }

  Integer result = Copy();
  uint32_t totalShift = 0;

  // 计算总位移量
  for (Index i = 0; i < rhs.parts.Size(); i++) {
    totalShift += rhs.parts.Get(i);
  }

  // 如果总位移量超过最大范围，直接返回0
  if (totalShift >= 16 * result.parts.Size()) {
    return CreateIntegerZero();
  }

  // 扩展数组大小以容纳新的位移结果
  Index newPartsSize = result.parts.Size() + (totalShift + 15) / 16;
  result.parts.ExpandWithElement(newPartsSize, 0);

  // 逐位进行位移
  for (Index i = 0; i < result.parts.Size(); i++) {
    uint32_t lowShift = totalShift % 16;
    uint32_t highShift = 16 - lowShift;

    if (i + 1 < result.parts.Size()) {
      uint32_t overflow = result.parts.Get(i) >> highShift;
      result.parts.Set(i + 1, result.parts.Get(i + 1) | overflow);
    }

    result.parts.Set(i, result.parts.Get(i) << lowShift);
  }

  return result;
}

Integer Integer::RightShift(const Integer& rhs) const {
  if (rhs.sign) {
    throw std::runtime_error("Shift count must be non-negative");
  }
  if (rhs.IsZero()) {
    return Copy();
  }
  Integer result = Copy();
  for (Index i = 0; i < rhs.parts.Size(); i++) {
    uint32_t shift = rhs.parts.Get(i);
    if (shift == 0) {
      continue;
    }
    for (Index j = 0; j < result.parts.Size(); j++) {
      result.parts.Set(j, result.parts.Get(j) >> shift);
      if (j + 1 < result.parts.Size()) {
        result.parts.Set(
          j, result.parts.Get(j) | (result.parts.Get(j + 1) << (16 - shift))
        );
      }
    }
  }
  TrimLeadingZero(result.parts);
  return result;
}
}  // namespace torchlight::Collections