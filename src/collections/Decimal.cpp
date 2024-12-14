#include <stdexcept>
#include "collections/Decimal.h"
#include "collections/String.h"

namespace torchlight::collections {

int Decimal::UnicodeToInt(Unicode c) noexcept {
  if (c >= 0x0030 && c <= 0x0039) {
    return static_cast<int>(c - 0x0030);
  }
  return -1;
}

bool Decimal::IsNegative(const String& str) {
  const Unicode UnicodeMinus = 0x2D;
  return str.Get(0) == UnicodeMinus;
}

Decimal::Decimal(const String& str) {
  Index i = 0;
  if (IsNegative(str)) {
    isNegative = true;
    i = 1;
  }
  for (; i < str.Size(); i++) {
    int c = UnicodeToInt(str.Get(i));
    if (c == -1) {
      throw std::runtime_error("Invalid character in Decimal");
    }
    parts.Add(c);
  }
  TrimLeadingZero();
}

Decimal::Decimal() = default;

Decimal Decimal::Slice(Index start, Index end) const {
  Decimal newDecimal;
  newDecimal.parts = parts.Slice(start, end);
  newDecimal.isNegative = isNegative;
  return newDecimal;
}

Decimal::Decimal(int32_t value) {
  if (value < 0) {
    isNegative = true;
    value = -value;
  }
  while (value > 0) {
    parts.Add(value % 10);
    value /= 10;
  }
  this->parts.Reverse();
}

String Decimal::ToString() const {
  if (IsZero()) {
    return String("0");
  }
  const Unicode UnicodeDigitZero = 0x30;
  String str(parts.Size() + (isNegative ? 1 : 0));
  if (isNegative) {
    str.Add(0x2D);  // '-'
  }
  for (Index i = 0; i < parts.Size(); i++) {
    str.Add(parts.Get(i) + UnicodeDigitZero);
  }
  return str;
}

Decimal Decimal::Add(const Decimal& rhs) const {
  // 正负号相同
  if (isNegative == rhs.isNegative) {
    Index size = std::max(parts.Size(), rhs.parts.Size());
    Decimal result;
    result.parts.Expand(size + 1);
    int carry = 0;
    for (auto it = List<int>::Iterator::RBegin(parts),
              it2 = List<int>::Iterator::RBegin(rhs.parts);
         !(it.End() && it2.End()); it.Next(), it2.Next()) {
      int sum = carry;
      if (!it.End()) {
        sum += it.Get();
      }
      if (!it2.End()) {
        sum += it2.Get();
      }
      carry = sum / 10;
      sum %= 10;
      result.parts.Add(sum);
    }
    if (carry != 0) {
      result.parts.Add(carry);
    }
    result.isNegative = isNegative;
    return result.Reverse();
  }
  return Subtract(rhs.Copy().Negate());
}

Decimal Decimal::Negate() {
  Decimal newDecimal;
  newDecimal.parts = parts.Copy();
  newDecimal.isNegative = !isNegative;
  return newDecimal;
}

Decimal Decimal::Copy() const {
  Decimal newDecimal;
  newDecimal.parts = parts.Copy();
  newDecimal.isNegative = isNegative;
  return newDecimal;
}

bool Decimal::GreaterThan(const Decimal& rhs) const {
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
  for (auto it = List<int>::Iterator::Begin(parts),
            it2 = List<int>::Iterator::Begin(rhs.parts);
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
      Decimal temp = _lhs;
      _lhs = _rhs;
      _rhs = temp;
    } else {
      size = _lhs.parts.Size();
      for (auto it = List<int>::Iterator::RBegin(_lhs.parts),
                it2 = List<int>::Iterator::RBegin(_rhs.parts);
           !it.End() && !it2.End(); it.Next(), it2.Next()) {
        if (it.Get() > it2.Get()) {
          break;
        }
        if (it.Get() < it2.Get()) {
          sign = true;
          Decimal temp = _lhs;
          _lhs = _rhs;
          _rhs = temp;
          break;
        }
      }
    }
    Decimal result;
    result.parts.Expand(size);
    int borrow = 0;
    for (auto it = List<int>::Iterator::Begin(_lhs.parts),
              it2 = List<int>::Iterator::Begin(_rhs.parts);
         !it.End() && !it2.End(); it.Next(), it2.Next()) {
      int diff = borrow + it.Get();
      if (diff < it2.Get()) {
        diff += 10;
        borrow = -1;
      } else {
        borrow = 0;
      }
      diff -= it2.Get();
      result.parts.Add(diff);
    }
    result.TrimTrailingZero();
    result.isNegative = sign ^ isNegative;
    return result.Reverse();
  }
  return Add(rhs.Copy().Negate());
}

Decimal Decimal::Multiply(const Decimal& rhs) const {
  if (IsZero() || rhs.IsZero()) {
    return Decimal(String("0"));
  }
  Decimal result;
  result.parts.Expand(parts.Size() + rhs.parts.Size());
  result.parts.Fill(0);
  auto _lhs = Copy().Reverse();
  auto _rhs = rhs.Copy().Reverse();
  for (auto it = List<int>::Iterator::Begin(_lhs.parts); !it.End(); it.Next()) {
    for (auto it2 = List<int>::Iterator::Begin(_rhs.parts); !it2.End();
         it2.Next()) {
      int product = it.Get() * it2.Get();
      Index index = it.Index() + it2.Index();
      result.parts.Set(index, result.parts.Get(index) + product);
      result.parts.Set(
        index + 1, result.parts.Get(index + 1) + result.parts.Get(index) / 10
      );
      result.parts.Set(index, result.parts.Get(index) % 10);
    }
  }
  result.TrimTrailingZero();
  result.isNegative = isNegative ^ rhs.isNegative;  // 处理符号
  return result.Reverse();
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
    divmods.Add(Decimal(String("0")));
    divmods.Add(Copy());
    return divmods;
  }
  if (Equal(rhs)) {
    List<Decimal> divmods;
    divmods.Add(Decimal(String("1")));
    divmods.Add(Decimal(String("0")));
    return divmods;
  }
  Decimal result;
  result.parts.Expand(parts.Size());
  result.isNegative = isNegative ^ rhs.isNegative;
  Decimal dividend = Copy().Slice(0, std::min(parts.Size(), rhs.parts.Size()));
  dividend.isNegative = false;
  Decimal divisor = rhs.Copy();
  divisor.isNegative = false;
  for (Index i = 0; i < parts.Size() - rhs.parts.Size() + 1; i++) {
    int quotient = 0;
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
  List<Decimal> divmods;
  result.TrimLeadingZero();
  dividend.TrimLeadingZero();
  divmods.Add(result);
  divmods.Add(dividend);
  return divmods;
}

bool Decimal::IsZero() const {
  if (parts.Size() == 0) {
    return true;
  }
  for (auto it = List<int>::Iterator::Begin(parts); !it.End(); it.Next()) {
    if (it.Get() != 0) {
      return false;
    }
  }
  return true;
}

Decimal Decimal::Reverse() const {
  Decimal newDecimal;
  newDecimal.parts = parts.Copy();
  newDecimal.parts.Reverse();
  newDecimal.isNegative = isNegative;
  return newDecimal;
}

bool Decimal::Equal(const Decimal& rhs) const {
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

void Decimal::TrimTrailingZero() {
  for (auto it = List<int>::Iterator::RBegin(parts); !it.End(); it.Next()) {
    if (it.Get() != 0 || it.Index() == 0) {
      parts = parts.Slice(0, it.Index() + 1);
      break;
    }
  }
}

void Decimal::TrimLeadingZero() {
  for (auto it = List<int>::Iterator::Begin(parts); !it.End(); it.Next()) {
    if (it.Get() != 0 || it.Index() == parts.Size() - 1) {
      parts = parts.Slice(it.Index(), parts.Size());
      break;
    }
  }
}

}  // namespace torchlight::collections