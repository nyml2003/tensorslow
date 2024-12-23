#include "collections/Integer.h"

#include <stdexcept>
#include "collections/Bytes.h"

namespace torchlight::collections {

int Integer::UnicodeToHex(Unicode c) noexcept {
  const Unicode UnicodeDigit_0 = 0x0030;
  const Unicode UnicodeDigit_9 = 0x0039;
  const Unicode UnicodeDigit_A = 0x0041;
  const Unicode UnicodeDigit_F = 0x0046;
  const Unicode UnicodeDigit_a = 0x0061;
  const Unicode UnicodeDigit_f = 0x0066;
  if (c >= UnicodeDigit_0 && c <= UnicodeDigit_9) {
    return static_cast<int>(c - 0x0030);
  }
  if (c >= UnicodeDigit_A && c <= UnicodeDigit_F) {
    return static_cast<int>(c - 0x0041 + 10);
  }
  if (c >= UnicodeDigit_a && c <= UnicodeDigit_f) {
    return static_cast<int>(c - 0x0061 + 10);
  }
  return -1;
}

Unicode Integer::HexToUnicode(uint8_t c) noexcept {
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

bool Integer::IsNegative(const String& str) {
  const Unicode UnicodeMinus = 0x2D;
  return str.Get(0) == UnicodeMinus;
}

Integer::Integer(const String& str) {
  Unicode unicode_0 = 0x0030;
  Unicode unicode_X = 0x0058;
  Unicode unicode_x = 0x0078;
  if (str.Size() > 2 && str.Get(0) == unicode_0 &&
      (str.Get(1) == unicode_X || str.Get(1) == unicode_x)) {
    int32_t buffer = 0;
    int counter = 0;
    for (Index i = 2; i < str.Size(); i++) {
      Unicode c = str.Get(i);
      int32_t hex = UnicodeToHex(c);
      if (hex == -1) {
        throw std::runtime_error("Invalid character in Integer");
      }
      buffer = (buffer << 4) | hex;
      counter++;
      if (counter == 8) {
        parts.Add(buffer);
        buffer = 0;
        counter = 0;
      }
    }
    if (counter != 0) {
      parts.Add(buffer);
    }
  } else {
    FromDecimal(Decimal(str));
  }
}

Integer::Integer(const Bytes& str) {
  Byte byte_0 = 0x30;
  Byte byte_X = 0x58;
  Byte byte_x = 0x78;
  if (str.Size() > 2 && str.Get(0) == byte_0 &&
      (str.Get(1) == byte_X || str.Get(1) == byte_x)) {
    int32_t buffer = 0;
    int counter = 0;
    for (Index i = 0; i < str.Size(); i++) {
      uint8_t c = str.Get(i);
      buffer = (buffer << 8) | c;
      counter++;
      if (counter == 4) {
        parts.Add(buffer);
        buffer = 0;
        counter = 0;
      }
    }
    if (counter != 0) {
      parts.Add(buffer);
    }
  }
  FromDecimal(Decimal(str));
}

String Integer::ToString() const {
  return ToDecimal().ToString();
}

String Integer::ToHexString() const {
  if (IsZero()) {
    return String("0");
  }
  const Unicode UnicodeDigitZero = 0x30;
  String str;
  for (Index i = 0; i < parts.Size(); i++) {
    uint32_t item = parts.Get(i);
    std::array<uint8_t, 4> buffer = {0};
    buffer[0] = (item & 0x0000F000) >> 12;
    buffer[1] = (item & 0x00000F00) >> 8;
    buffer[2] = (item & 0x000000F0) >> 4;
    buffer[3] = (item & 0x0000000F);
    for (Index j = 0; j < 4; j++) {
      str.Add(HexToUnicode(buffer[j]));
    }
  }
  Index it = 0;
  for (; it < str.Size(); it++) {
    if (str.Get(it) != UnicodeDigitZero) {
      break;
    }
  }
  str = str.Slice(it, str.Size());
  str.Reverse();
  str = str.Concat(String("x0"));
  str.Reverse();
  return str;
}

void Integer::Assign(const Integer& rhs) {
  parts = rhs.parts.Copy();
}

Decimal Integer::ToDecimal() const {
  Decimal decimal(0);
  for (Index i = 0; i < parts.Size(); i++) {
    Decimal temp(static_cast<int32_t>(parts.Get(i)));
    decimal = decimal.Multiply(Decimal(0x10000)).Add(temp);
  }
  decimal.isNegative = isNegative;
  return decimal;
}

void Integer::FromDecimal(const Decimal& decimal) {
  parts.Clear();
  isNegative = decimal.isNegative;
  Decimal temp = decimal.Copy();
  Decimal num65536(0x10000);
  while (!temp.IsZero()) {
    List<Decimal> divmod = temp.DivMod(num65536);
    temp = divmod.Get(0);
    Decimal remainder = divmod.Get(1);
    int32_t value = 0;
    for (Index i = 0; i < remainder.parts.Size(); i++) {
      value = value * 10 + remainder.parts.Get(i);
    }
    parts.Add(value);
  }
  parts.Reverse();
}

Integer Integer::Add(const Integer& rhs) const {
  if (isNegative == rhs.isNegative) {
    uint32_t carry = 0;
    Integer result;
    result.isNegative = isNegative;
    for (auto itl = List<uint32_t>::Iterator::RBegin(parts),
              itr = List<uint32_t>::Iterator::RBegin(rhs.parts);
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
      result.parts.Add(sum);
    }
    if (carry != 0) {
      result.parts.Add(carry);
    }
    return result.Reverse();
  }
  return Subtract(rhs.Copy().Negate());
}

Integer Integer::Negate() {
  Integer newInteger;
  newInteger.parts = parts.Copy();
  newInteger.isNegative = !isNegative;
  return newInteger;
}

Integer Integer::Copy() const {
  Integer newInteger;
  newInteger.parts = parts.Copy();
  newInteger.isNegative = isNegative;
  return newInteger;
}

bool Integer::GreaterThan(const Integer& rhs) const {
  // 如果左值是负数，右值是正数，那么左值一定比右值小
  if (isNegative && !rhs.isNegative) {
    return false;
  }
  // 如果左值是正数，右值是负数，那么左值一定比右值大
  if (!isNegative && rhs.isNegative) {
    return true;
  }
  bool sign = isNegative;
  // 此时左值和右值正负号相同
  if (parts.Size() != rhs.parts.Size()) {
    // 正号，位数多的数大；负号，位数少的数大
    return sign ^ (parts.Size() > rhs.parts.Size());
  }
  // 此时左值和右值的位数相等，正负号相同
  for (auto it = List<uint32_t>::Iterator::Begin(parts),
            it2 = List<uint32_t>::Iterator::Begin(rhs.parts);
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
  if (isNegative == rhs.isNegative) {
    // 假定左值大于右值
    bool sign = false;
    Index size = 0;
    auto _lhs = Copy().Reverse();
    auto _rhs = rhs.Copy().Reverse();
    if (_lhs.parts.Size() > _rhs.parts.Size()) {
      const Index diff = _lhs.parts.Size() - _rhs.parts.Size();
      for (Index i = 0; i < diff; i++) {
        _rhs.parts.Add(0);
      }
      size = _lhs.parts.Size();
    } else if (_lhs.parts.Size() < _rhs.parts.Size()) {
      const Index diff = _rhs.parts.Size() - _lhs.parts.Size();
      for (Index i = 0; i < diff; i++) {
        _lhs.parts.Add(0);
      }
      size = _rhs.parts.Size();
      sign = true;
      Integer temp = _lhs;
      _lhs = _rhs;
      _rhs = temp;
    } else {
      size = _lhs.parts.Size();
      for (auto it = List<uint32_t>::Iterator::RBegin(_lhs.parts),
                it2 = List<uint32_t>::Iterator::RBegin(_rhs.parts);
           !it.End() && !it2.End(); it.Next(), it2.Next()) {
        if (it.Get() > it2.Get()) {
          break;
        }
        if (it.Get() < it2.Get()) {
          sign = true;
          Integer temp = _lhs;
          _lhs = _rhs;
          _rhs = temp;
          break;
        }
      }
    }
    Integer result;
    result.parts.Expand(size);
    bool borrow = false;
    for (auto it = List<uint32_t>::Iterator::Begin(_lhs.parts),
              it2 = List<uint32_t>::Iterator::Begin(_rhs.parts);
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
      result.parts.Add(diff);
    }
    result.TrimTrailingZero();
    result.isNegative = sign ^ isNegative;
    return result.Reverse();
  }
  return Add(rhs.Copy().Negate());
}

Integer Integer::Multiply(const Integer& rhs) const {
  if (IsZero() || rhs.IsZero()) {
    return Integer();
  }
  Integer result;
  result.parts.Expand(parts.Size() + rhs.parts.Size());
  result.parts.Fill(0);
  auto _lhs = Copy().Reverse();
  auto _rhs = rhs.Copy().Reverse();
  for (auto it = List<uint32_t>::Iterator::Begin(_lhs.parts); !it.End();
       it.Next()) {
    for (auto it2 = List<uint32_t>::Iterator::Begin(_rhs.parts); !it2.End();
         it2.Next()) {
      uint32_t product = it.Get() * it2.Get();
      Index index = it.Index() + it2.Index();
      result.parts.Set(index, result.parts.Get(index) + product);
      result.parts.Set(
        index + 1, result.parts.Get(index + 1) + (result.parts.Get(index) >> 16)
      );
      result.parts.Set(index, (result.parts.Get(index) & 0x0000FFFF));
    }
  }
  result.TrimTrailingZero();
  result.isNegative = isNegative ^ rhs.isNegative;  // 处理符号
  return result.Reverse();
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
    List<Integer> divmods;
    divmods.Add(Integer(String("0")));
    divmods.Add(Copy());
    return divmods;
  }
  if (Equal(rhs)) {
    List<Integer> divmods;
    divmods.Add(Integer(String("1")));
    divmods.Add(Integer(String("0")));
    return divmods;
  }
  Integer result;
  result.parts.Expand(parts.Size());
  result.isNegative = isNegative ^ rhs.isNegative;
  Integer dividend = Copy().Slice(0, std::min(parts.Size(), rhs.parts.Size()));
  dividend.isNegative = false;
  Integer divisor = rhs.Copy();
  divisor.isNegative = false;
  for (Index i = 0; i < parts.Size() - rhs.parts.Size() + 1; i++) {
    uint32_t quotient = 0;
    while (dividend.GreaterThanOrEqual(divisor)) {
      dividend = dividend.Subtract(divisor);
      quotient++;
    }
    result.parts.Add(quotient);
    if (i + rhs.parts.Size() < parts.Size()) {
      dividend.parts.Add(parts.Get(i + rhs.parts.Size()));
    }
    dividend.TrimLeadingZero();
  }
  List<Integer> divmods;
  result.TrimLeadingZero();
  dividend.TrimLeadingZero();
  divmods.Add(result);
  divmods.Add(dividend);
  return divmods;
}

bool Integer::IsZero() const {
  if (parts.Size() == 0) {
    return true;
  }
  for (auto it = List<uint32_t>::Iterator::Begin(parts); !it.End(); it.Next()) {
    if (it.Get() != 0) {
      return false;
    }
  }
  return true;
}

Integer Integer::Reverse() const {
  Integer newInteger;
  newInteger.parts = parts.Copy();
  newInteger.parts.Reverse();
  newInteger.isNegative = isNegative;
  return newInteger;
}

bool Integer::Equal(const Integer& rhs) const {
  if (isNegative != rhs.isNegative) {
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

void Integer::TrimTrailingZero() {
  for (auto it = List<uint32_t>::Iterator::RBegin(parts); !it.End();
       it.Next()) {
    if (it.Get() != 0 || it.Index() == 0) {
      parts = parts.Slice(0, it.Index() + 1);
      break;
    }
  }
}

void Integer::TrimLeadingZero() {
  for (auto it = List<uint32_t>::Iterator::Begin(parts); !it.End(); it.Next()) {
    if (it.Get() != 0 || it.Index() == parts.Size() - 1) {
      parts = parts.Slice(it.Index(), parts.Size());
      break;
    }
  }
}

Integer Integer::Slice(Index start, Index end) const {
  Integer newInteger;
  newInteger.parts = parts.Slice(start, end);
  newInteger.isNegative = isNegative;
  return newInteger;
}

Integer Integer::BitWiseAnd(const Integer& rhs) const {
  Integer result;
  result.parts.Expand(std::min(parts.Size(), rhs.parts.Size()));
  for (auto it = List<uint32_t>::Iterator::RBegin(parts),
            it2 = List<uint32_t>::Iterator::RBegin(rhs.parts);
       !it.End() || !it2.End(); it.Next(), it2.Next()) {
    if (it.End() || it2.End()) {
      result.parts.Add(0);
    } else {
      result.parts.Add(it.Get() & it2.Get());
    }
  }
  return result.Reverse();
}

Integer Integer::BitWiseOr(const Integer& rhs) const {
  Integer result;
  result.parts.Expand(std::max(parts.Size(), rhs.parts.Size()));
  Index diff = 0;
  if (parts.Size() > rhs.parts.Size()) {
    diff = parts.Size() - rhs.parts.Size();
  } else if (parts.Size() < rhs.parts.Size()) {
    diff = rhs.parts.Size() - parts.Size();
  }
  auto _lhs = Copy().Reverse();
  auto _rhs = rhs.Copy().Reverse();
  for (Index i = 0; i < diff; i++) {
    if (parts.Size() > rhs.parts.Size()) {
      _rhs.parts.Add(0);
    } else {
      _lhs.parts.Add(0);
    }
  }
  for (auto it = List<uint32_t>::Iterator::Begin(_lhs.parts),
            it2 = List<uint32_t>::Iterator::Begin(_rhs.parts);
       !it.End() || !it2.End(); it.Next(), it2.Next()) {
    result.parts.Add(it.Get() | it2.Get());
  }
  return result.Reverse();
}

Integer Integer::BitWiseXor(const Integer& rhs) const {
  Integer result;
  result.parts.Expand(std::max(parts.Size(), rhs.parts.Size()));
  for (auto it = List<uint32_t>::Iterator::RBegin(parts),
            it2 = List<uint32_t>::Iterator::RBegin(rhs.parts);
       !it.End() || !it2.End(); it.Next(), it2.Next()) {
    if (it.End()) {
      result.parts.Add(it2.Get());
    } else if (it2.End()) {
      result.parts.Add(it.Get());
    } else {
      result.parts.Add(it.Get() ^ it2.Get());
    }
  }
  return result.Reverse();
}

Integer Integer::BitWiseNot() const {
  Integer result;
  result.parts.Expand(parts.Size());
  for (auto it = List<uint32_t>::Iterator::Begin(parts); !it.End(); it.Next()) {
    result.parts.Add(~it.Get());
  }
  return result.Reverse();
}

}  // namespace torchlight::collections