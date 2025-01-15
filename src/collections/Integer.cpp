
#include "collections/Integer.h"
#include "collections/Iterator.h"
#include "collections/impl/Decimal.h"
#include "collections/impl/Integer.h"
#include "collections/impl/String.h"

#include <stdexcept>

namespace torchlight::collections {

int8_t UnicodeToHex(Unicode c) noexcept {
  const Unicode UnicodeDigit_0 = 0x0030;
  const Unicode UnicodeDigit_9 = 0x0039;
  const Unicode UnicodeDigit_A = 0x0041;
  const Unicode UnicodeDigit_F = 0x0046;
  const Unicode UnicodeDigit_a = 0x0061;
  const Unicode UnicodeDigit_f = 0x0066;
  if (c >= UnicodeDigit_0 && c <= UnicodeDigit_9) {
    return static_cast<int8_t>(c - 0x0030);
  }
  if (c >= UnicodeDigit_A && c <= UnicodeDigit_F) {
    return static_cast<int8_t>(c - 0x0041 + 10);
  }
  if (c >= UnicodeDigit_a && c <= UnicodeDigit_f) {
    return static_cast<int8_t>(c - 0x0061 + 10);
  }
  return -1;
}

Unicode HexToUnicode(uint8_t c) noexcept {
  const Unicode UnicodeDigit_0 = 0x0030;
  const Unicode UnicodeDigit_9 = 0x0039;
  const Unicode UnicodeDigit_A = 0x0041;
  const Unicode UnicodeDigit_F = 0x0046;
  const Unicode UnicodeDigit_a = 0x0061;
  const Unicode UnicodeDigit_f = 0x0066;
  if (c >= 0 && c <= 9) {
    return static_cast<Unicode>(c + UnicodeDigit_0);
  }
  if (c >= 10 && c <= 15) {
    return static_cast<Unicode>(c - 10 + UnicodeDigit_A);
  }
  return 0;
}

Integer::Integer(const List<uint32_t>& _parts, bool _sign)
  : parts(_parts), sign(_sign) {}

Integer::Integer() = default;

Integer CreateIntegerWithString(const String& str) {
  Unicode unicode_0 = 0x0030;
  Unicode unicode_X = 0x0058;
  Unicode unicode_x = 0x0078;
  if (str.Size() > 2 && str.Get(0) == unicode_0 &&
      (str.Get(1) == unicode_X || str.Get(1) == unicode_x)) {
    List<uint32_t> parts;
    uint32_t buffer = 0;
    uint32_t count = 0;
    for (Index i = str.Size() - 1; i >= 2; i--) {
      int8_t value = UnicodeToHex(str.Get(i));
      if (value == -1) {
        throw std::runtime_error("Invalid character in Hexadecimal");
      }
      buffer = (value << (count * 4)) | buffer;
      count++;
      if (count == 4) {
        parts.Push(buffer);
        buffer = 0;
        count = 0;
      }
    }
    if (count != 0) {
      parts.Push(buffer);
    }
    parts.Reverse();
    return Integer(parts, false);
  }
  return CreateIntegerWithDecimal(CreateDecimalWithString(str));
}

Integer CreateIntegerWithCString(const char* str) {
  return CreateIntegerWithString(CreateStringWithCString(str));
}

String Integer::ToString() const {
  return CreateDecimalWithInteger(*this).ToString();
}

bool Integer::Sign() const {
  return sign;
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

Decimal CreateDecimalWithInteger(const Integer& integer) {
  Decimal decimal = CreateDecimalZero();
  const auto& parts = integer.Data();
  for (Index i = 0; i < parts.Size(); i++) {
    Decimal temp = CreateDecimalWithU32(parts.Get(i));
    decimal = decimal.Multiply(CreateDecimalWithU32(65536)).Add(temp);
  }
  return Decimal(decimal.Data(), integer.Sign());
}

Integer CreateIntegerWithDecimal(const Decimal& decimal) {
  List<uint32_t> parts;
  Decimal temp = decimal.Copy();
  Decimal num65536(CreateDecimalWithString(CreateStringWithCString("65536")));
  while (!temp.IsZero()) {
    List<Decimal> divmod = temp.DivMod(num65536);
    temp = divmod.Get(0);
    Decimal remainder = divmod.Get(1);
    int32_t value = 0;
    for (Index i = 0; i < remainder.Data().Size(); i++) {
      value = value * 10 + remainder.Data().Get(i);
    }
    parts.Push(value);
  }
  parts.Reverse();
  Integer result(parts, decimal.Sign());
  return result;
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

void Integer::Negate() {
  sign = !sign;
}

Integer Integer::Copy() const {
  Integer newInteger;
  newInteger.parts = parts.Copy();
  newInteger.sign = sign;
  return newInteger;
}

bool Integer::GreaterThan(const Integer& rhs) const {
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

void TrimTrailingZero(List<uint32_t>& parts) {
  for (auto it = Iterator<uint32_t>::RBegin(parts); !it.End(); it.Next()) {
    if (it.Get() != 0 || it.GetCurrentIndex() == 0) {
      parts = parts.Slice(0, it.GetCurrentIndex() + 1);
      break;
    }
  }
}

void TrimLeadingZero(List<uint32_t>& parts) {
  for (auto it = Iterator<uint32_t>::Begin(parts); !it.End(); it.Next()) {
    if (it.Get() != 0 || it.GetCurrentIndex() == parts.Size() - 1) {
      parts = parts.Slice(it.GetCurrentIndex(), parts.Size());
      break;
    }
  }
}

Integer Slice(const Integer& integer, Index start, Index end) {
  List<uint32_t> parts = integer.Data().Slice(start, end);
  return Integer(parts, integer.Sign());
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

Integer CreateIntegerZero() {
  List<uint32_t> parts = {0};
  return Integer(parts, false);
}

Integer CreateIntegerOne() {
  List<uint32_t> parts = {1};
  return Integer(parts, false);
}

List<uint32_t> Integer::Data() const {
  return parts;
}

Index ToIndex(const Integer& integer) {
  if (integer.IsZero()) {
    return 0;
  }
  if (integer.Sign()) {
    throw std::runtime_error("Negative integer cannot be converted to index");
  }
  auto data = integer.Data();
  if (data.Size() > 4) {
    throw std::runtime_error("Integer is too large to be converted to index");
  }

  Index result = 0;
  for (Index i = 0; i < data.Size(); i++) {
    result = (result << 16) | data.Get(i);
  }
  return result;
}

Integer CreateIntegerWithIndex(Index index) {
  List<uint32_t> parts;
  while (index != 0) {
    parts.Push(index & 0x0000FFFF);
    index >>= 16;
  }
  parts.Reverse();
  return Integer(parts, false);
}
uint64_t safe_add(uint64_t a, int64_t b) {
  if (b >= 0) {
    // b 是正数或零，直接相加
    if (a > std::numeric_limits<uint64_t>::max() - b) {
      throw std::overflow_error("Addition overflow");
    }
    return a + static_cast<uint64_t>(b);
  } else {
    // b 是负数，转换为补码并相减
    if (a < static_cast<uint64_t>(-b)) {
      throw std::underflow_error("Subtraction underflow");
    }
    return a - static_cast<uint64_t>(-b);
  }
}
}  // namespace torchlight::collections