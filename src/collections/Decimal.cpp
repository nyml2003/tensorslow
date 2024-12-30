#include "collections/Decimal.h"
#include <stdexcept>
#include "collections/String.h"
#include "collections/impl/Decimal.h"
#include "collections/impl/String.h"

namespace torchlight::collections {

Decimal CreateDecimalZero() {
  return CreateDecimalWithU32(0);
}

Decimal CreateDecimalOne() {
  return CreateDecimalWithU32(1);
}

Decimal CreateDecimalWithU32(uint32_t value) {
  List<int32_t> parts;
  for (Index i = 0; value != 0; i++) {
    parts.Add(static_cast<int32_t>(value % 10));
    value /= 10;
  }
  parts.Reverse();
  return Decimal(parts, false);
}

int32_t UnicodeToInt(Unicode c) noexcept {
  if (c >= 0x0030 && c <= 0x0039) {
    return static_cast<int32_t>(c - 0x0030);
  }
  return -1;
}

bool IsNegative(const String& str) {
  const Unicode UnicodeMinus = 0x2D;
  return str.Get(0) == UnicodeMinus;
}

bool IsNegative(const Bytes& str) {
  const Byte ByteMinus = 0x2D;
  return str.Get(0) == ByteMinus;
}

Decimal Slice(const Decimal& decimal, Index start, Index end) {
  List<int32_t> parts = decimal.Data().Slice(start, end);
  return Decimal(parts, decimal.Sign());
}

Decimal CreateDecimalWithString(const String& str) {
  Index i = 0;
  bool sign = false;
  if (IsNegative(str)) {
    sign = true;
    i = 1;
  }
  List<int32_t> parts;
  for (; i < str.Size(); i++) {
    int32_t c = UnicodeToInt(str.Get(i));
    if (c == -1) {
      throw std::runtime_error("Invalid character in Decimal");
    }
    parts.Add(c);
  }

  return Decimal(parts, sign);
}

String Decimal::ToString() const {
  if (IsZero()) {
    return CreateStringWithCString("0");
  }
  const Unicode UnicodeDigitZero = 0x30;
  List<Unicode> str(parts.Size() + (sign ? 1 : 0));
  if (sign) {
    str.Add(0x2D);  // '-'
  }
  for (Index i = 0; i < parts.Size(); i++) {
    str.Add(parts.Get(i) + UnicodeDigitZero);
  }
  return String(str);
}

Decimal Decimal::Add(const Decimal& rhs) const {
  // 正负号相同
  if (sign == rhs.sign) {
    Index size = std::max(parts.Size(), rhs.parts.Size());
    List<int32_t> result(size + 1);
    int32_t carry = 0;
    for (auto it = List<int32_t>::Iterator::RBegin(parts),
              it2 = List<int32_t>::Iterator::RBegin(rhs.parts);
         !(it.End() && it2.End()); it.Next(), it2.Next()) {
      int32_t sum = carry;
      if (!it.End()) {
        sum += it.Get();
      }
      if (!it2.End()) {
        sum += it2.Get();
      }
      carry = sum / 10;
      sum %= 10;
      result.Add(sum);
    }
    if (carry != 0) {
      result.Add(carry);
    }
    result.Reverse();
    return Decimal(result, sign);
  }
  return Subtract(rhs.Copy().Negate());
}

Decimal Decimal::Negate() {
  Decimal newDecimal;
  newDecimal.parts = parts.Copy();
  newDecimal.sign = !sign;
  return newDecimal;
}

Decimal Decimal::Copy() const {
  Decimal newDecimal;
  newDecimal.parts = parts.Copy();
  newDecimal.sign = sign;
  return newDecimal;
}

bool Decimal::GreaterThan(const Decimal& rhs) const {
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
  for (auto it = List<int32_t>::Iterator::Begin(parts),
            it2 = List<int32_t>::Iterator::Begin(rhs.parts);
       !it.End() && !it2.End(); it.Next(), it2.Next()) {
    if (it.Get() == it2.Get()) {
      continue;
    }
    return sign ^ (it.Get() > it2.Get());
  }
  return false;
}

Decimal Decimal::Subtract(const Decimal& rhs) const {
  // 正负号相同
  if (sign == rhs.sign) {
    // 假定左值大于右值
    bool sign = false;
    Index size = 0;
    List<int32_t> _lhs = parts.Copy();
    _lhs.Reverse();
    List<int32_t> _rhs = rhs.parts.Copy();
    _rhs.Reverse();
    if (_lhs.Size() > _rhs.Size()) {
      _rhs.AppendElements(0, _lhs.Size() - _rhs.Size());
      size = _lhs.Size();
    } else if (_lhs.Size() < _rhs.Size()) {
      _lhs.AppendElements(0, _rhs.Size() - _lhs.Size());
      size = _rhs.Size();
      sign = true;
      std::swap(_lhs, _rhs);
    } else {
      size = _lhs.Size();
      for (auto it = List<int32_t>::Iterator::RBegin(_lhs),
                it2 = List<int32_t>::Iterator::RBegin(_rhs);
           !it.End() && !it2.End(); it.Next(), it2.Next()) {
        if (it.Get() > it2.Get()) {
          break;
        }
        if (it.Get() < it2.Get()) {
          sign = true;
          std::swap(_lhs, _rhs);
          break;
        }
      }
    }
    List<int32_t> result(size);
    int32_t borrow = 0;
    for (auto it = List<int32_t>::Iterator::Begin(_lhs),
              it2 = List<int32_t>::Iterator::Begin(_rhs);
         !it.End() && !it2.End(); it.Next(), it2.Next()) {
      int32_t diff = borrow + it.Get();
      if (diff < it2.Get()) {
        diff += 10;
        borrow = -1;
      } else {
        borrow = 0;
      }
      diff -= it2.Get();
      result.Add(diff);
    }
    TrimTrailingZero(result);
    result.Reverse();
    return Decimal(result, this->sign ^ sign);
  }
  return Add(rhs.Copy().Negate());
}

Decimal Decimal::Multiply(const Decimal& rhs) const {
  if (IsZero() || rhs.IsZero()) {
    return CreateDecimalZero();
  }
  List<int32_t> result(parts.Size() + rhs.parts.Size());
  result.Fill(0);
  List<int32_t> _lhs = parts.Copy();
  _lhs.Reverse();
  List<int32_t> _rhs = rhs.parts.Copy();
  _rhs.Reverse();
  for (auto it = List<int32_t>::Iterator::Begin(_lhs); !it.End(); it.Next()) {
    for (auto it2 = List<int32_t>::Iterator::Begin(_rhs); !it2.End();
         it2.Next()) {
      int32_t product = it.Get() * it2.Get();
      Index index = it.Index() + it2.Index();
      result.Set(index, result.Get(index) + product);
      result.Set(index + 1, result.Get(index + 1) + result.Get(index) / 10);
      result.Set(index, result.Get(index) % 10);
    }
  }
  TrimTrailingZero(result);
  result.Reverse();
  return Decimal(result, sign ^ rhs.sign);
}

Decimal Decimal::Divide(const Decimal& rhs) const {
  return DivMod(rhs).Get(0);
}

Decimal Decimal::Modulo(const Decimal& rhs) const {
  return DivMod(rhs).Get(1);
}

List<Decimal> Decimal::DivMod(const Decimal& rhs) const {
  if (rhs.IsZero()) {
    throw std::runtime_error("Division by zero");
  }
  if (IsZero() || LessThan(rhs)) {
    List<Decimal> divmods;
    divmods.Add(CreateDecimalZero());
    divmods.Add(Copy());
    return divmods;
  }
  if (Equal(rhs)) {
    List<Decimal> divmods;
    divmods.Add(CreateDecimalOne());
    divmods.Add(CreateDecimalZero());
    return divmods;
  }
  Decimal result;
  result.parts.Expand(parts.Size());
  result.sign = sign ^ rhs.sign;
  Decimal dividend(
    parts.Copy().Slice(0, std::min(parts.Size(), rhs.parts.Size())), false
  );
  Decimal divisor(rhs.parts.Copy(), false);
  for (Index i = 0; i < parts.Size() - rhs.parts.Size() + 1; i++) {
    int32_t quotient = 0;
    while (dividend.GreaterThanOrEqual(divisor)) {
      dividend = dividend.Subtract(divisor);
      quotient++;
    }
    result.parts.Add(quotient);
    if (i + rhs.parts.Size() < parts.Size()) {
      dividend.parts.Add(parts.Get(i + rhs.parts.Size()));
    }
    TrimLeadingZero(dividend.parts);
  }
  List<Decimal> divmods;
  TrimLeadingZero(result.parts);
  TrimLeadingZero(dividend.parts);
  divmods.Add(result);
  divmods.Add(dividend);
  return divmods;
}

bool Decimal::IsZero() const {
  if (parts.Size() == 0) {
    return true;
  }
  for (auto it = List<int32_t>::Iterator::Begin(parts); !it.End(); it.Next()) {
    if (it.Get() != 0) {
      return false;
    }
  }
  return true;
}

bool Decimal::Equal(const Decimal& rhs) const {
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

void TrimTrailingZero(List<int32_t>& parts) {
  for (auto it = List<int32_t>::Iterator::RBegin(parts); !it.End(); it.Next()) {
    if (it.Get() != 0 || it.Index() == 0) {
      parts = parts.Slice(0, it.Index() + 1);
      break;
    }
  }
}

void TrimLeadingZero(List<int32_t>& parts) {
  for (auto it = List<int32_t>::Iterator::Begin(parts); !it.End(); it.Next()) {
    if (it.Get() != 0 || it.Index() == parts.Size() - 1) {
      parts = parts.Slice(it.Index(), parts.Size());
      break;
    }
  }
}

bool Decimal::GreaterThanOrEqual(const Decimal& rhs) const {
  return GreaterThan(rhs) || Equal(rhs);
}

bool Decimal::LessThan(const Decimal& rhs) const {
  return !GreaterThan(rhs) && !Equal(rhs);
}

bool Decimal::LessThanOrEqual(const Decimal& rhs) const {
  return !GreaterThan(rhs);
}

bool Decimal::NotEqual(const Decimal& rhs) const {
  return !Equal(rhs);
}

List<int32_t> Decimal::Data() const {
  return parts;
}

Decimal::Decimal(const List<int32_t>& parts, bool sign)
  : parts(parts), sign(sign) {}

bool Decimal::Sign() const {
  return sign;
}

}  // namespace torchlight::collections