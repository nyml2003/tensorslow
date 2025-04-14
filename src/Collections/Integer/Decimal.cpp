#include "Collections/Integer/DecimalHelper.h"
#include "Collections/Integer/IntegerHelper.h"
#include "Collections/Iterator.h"
#include "Collections/String/StringHelper.h"

#include <stdexcept>
namespace torchlight::Collections {
String Decimal::ToString() const {
  if (IsZero()) {
    return CreateStringWithCString("0");
  }
  const Unicode UnicodeDigitZero = 0x30;
  List<Unicode> str(parts.Size() + (sign ? 1 : 0));
  if (sign) {
    str.Push(UnicodeMinus);
  }
  for (Index i = 0; i < parts.Size(); i++) {
    str.Push(static_cast<uint32_t>(parts.Get(i)) + UnicodeDigitZero);
  }
  return String(std::move(str));
}
String Decimal::ToHexString() const {
  return CreateIntegerWithDecimal(*this).ToHexString();
}
Decimal Decimal::Add(const Decimal& rhs) const {
  if (IsZero()) {
    return rhs.Copy();
  }
  // 正负号相同
  if (sign == rhs.sign) {
    Index size = std::max(parts.Size(), rhs.parts.Size());
    List<int32_t> result(size + 1);
    int32_t carry = 0;
    for (auto it = Iterator<int32_t>::RBegin(parts),
              it2 = Iterator<int32_t>::RBegin(rhs.parts);
         !it.End() || !it2.End(); it.Next(), it2.Next()) {
      int32_t sum = carry;
      if (!it.End()) {
        sum += it.Get();
      }
      if (!it2.End()) {
        sum += it2.Get();
      }
      carry = sum / 10;
      sum %= 10;
      result.Push(sum);
    }
    if (carry != 0) {
      result.Push(carry);
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
  if (this->IsZero()) {
    return rhs.sign;
  }
  if (rhs.IsZero()) {
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
  for (auto lhsIndex = 0, rhsIndex = 0; lhsIndex < parts.Size();
       lhsIndex++, rhsIndex++) {
    if (parts.Get(lhsIndex) == rhs.parts.Get(rhsIndex)) {
      continue;
    }
    return sign ^ (parts.Get(lhsIndex) > rhs.parts.Get(rhsIndex));
  }
  return false;
}
Decimal Decimal::Subtract(const Decimal& rhs) const {
  // 正负号相同
  if (sign == rhs.sign) {
    // 假定左值大于右值
    bool newSign = false;
    Index size = 0;
    List<int32_t> _lhs = parts.Copy();
    List<int32_t> _rhs = rhs.parts.Copy();
    _lhs.Reverse();
    _rhs.Reverse();
    if (_lhs.Size() > _rhs.Size()) {
      _rhs.Concat(List<int32_t>(_lhs.Size() - _rhs.Size(), 0));
      size = _lhs.Size();
    } else if (_lhs.Size() < _rhs.Size()) {
      _lhs.Concat(List<int32_t>(_rhs.Size() - _lhs.Size(), 0));
      size = _rhs.Size();
      newSign = true;
      std::swap(_lhs, _rhs);
    } else {
      size = _lhs.Size();
      for (Index lhsIndex = _lhs.Size() - 1, rhsIndex = _rhs.Size() - 1;
           ~lhsIndex && ~rhsIndex; lhsIndex--, rhsIndex--) {
        if (_lhs.Get(lhsIndex) > _rhs.Get(rhsIndex)) {
          break;
        }
        if (_lhs.Get(lhsIndex) < _rhs.Get(rhsIndex)) {
          newSign = true;
          std::swap(_lhs, _rhs);
          break;
        }
      }
    }
    List<int32_t> result(size);
    int32_t borrow = 0;
    for (Index lhsIndex = 0, rhsIndex = 0; lhsIndex < size;
         lhsIndex++, rhsIndex++) {
      int32_t diff = borrow + _lhs.Get(lhsIndex);
      if (diff < _rhs.Get(rhsIndex)) {
        diff += 10;
        borrow = -1;
      } else {
        borrow = 0;
      }
      diff -= _rhs.Get(rhsIndex);
      result.Push(diff);
    }
    TrimTrailingZero(result);
    result.Reverse();
    Decimal ans(result, sign ^ newSign);
    return ans;
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
  for (auto it = Iterator<int32_t>::Begin(_lhs); !it.End(); it.Next()) {
    for (auto it2 = Iterator<int32_t>::Begin(_rhs); !it2.End(); it2.Next()) {
      int32_t product = it.Get() * it2.Get();
      Index index = it.GetCurrentIndex() + it2.GetCurrentIndex();
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
    return List<Decimal>({CreateDecimalZero(), Copy()});
  }
  if (Equal(rhs)) {
    return List<Decimal>({CreateDecimalOne(), CreateDecimalZero()});
  }
  Decimal result;
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
    result.parts.Push(quotient);
    if (i + rhs.parts.Size() < parts.Size()) {
      dividend.parts.Push(parts.Get(i + rhs.parts.Size()));
    }
    TrimLeadingZero(dividend.parts);
  }
  List<Decimal> divmods;
  TrimLeadingZero(result.parts);
  TrimLeadingZero(dividend.parts);
  divmods.Push(result);
  divmods.Push(dividend);
  return divmods;
}
bool Decimal::IsZero() const {
  if (parts.Size() == 0) {
    return true;
  }
  for (auto it = Iterator<int32_t>::Begin(parts); !it.End(); it.Next()) {
    if (it.Get() != 0) {
      return false;
    }
  }
  return true;
}
bool Decimal::Equal(const Decimal& rhs) const {
  if (this->IsZero() && rhs.IsZero()) {
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
Decimal::Decimal() = default;
bool Decimal::Sign() const {
  return sign;
}
}  // namespace torchlight::Collections
