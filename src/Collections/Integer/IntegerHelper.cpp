#include "Collections/Integer/IntegerHelper.h"
#include "Collections/Integer/DecimalHelper.h"
#include "Collections/Iterator.h"
#include "Collections/String/StringHelper.h"
#include "Common.h"

#include <cstdint>
#include <limits>
#include <stdexcept>
namespace torchlight::Collections {
int8_t UnicodeToHex(Unicode unicode) noexcept {
  if (unicode >= Unicode_0 && unicode <= Unicode_9) {
    return static_cast<int8_t>(unicode - Unicode_0);
  }
  if (unicode >= Unicode_A && unicode <= Unicode_F) {
    return static_cast<int8_t>(unicode - Unicode_A + 10);
  }
  if (unicode >= Unicode_a && unicode <= Unicode_f) {
    return static_cast<int8_t>(unicode - Unicode_a + 10);
  }
  return -1;
}
Unicode HexToUnicode(uint8_t hex) noexcept {
  if (hex <= 9) {
    return static_cast<Unicode>(hex + Unicode_0);
  }
  if (hex >= 10 && hex <= 15) {
    return static_cast<Unicode>(hex - 10 + Unicode_A);
  }
  return 0;
}
Integer CreateIntegerWithString(const String& str) {
  if (str.Size() > 2 && str.Get(0) == Unicode_0 && (str.Get(1) == Unicode_X || str.Get(1) == Unicode_x)) {
    List<uint32_t> parts;
    uint32_t buffer = 0;
    uint32_t count = 0;
    for (Index i = str.Size() - 1; i >= 2; i--) {
      int8_t value = UnicodeToHex(str.Get(i));
      if (value == -1) {
        throw std::runtime_error("Invalid character in Hexadecimal");
      }
      buffer = (static_cast<uint32_t>(value) << (count * 4)) | buffer;
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
Decimal CreateDecimalWithInteger(const Integer& integer) {
  Decimal decimal = CreateDecimalZero();
  const auto& parts = integer.Data();
  for (Index i = 0; i < parts.Size(); i++) {
    Decimal temp = CreateDecimalWithU32(parts.Get(i));
    decimal = decimal.Multiply(CreateDecimalWithU32(0x10000)).Add(temp);
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
    parts.Push(static_cast<uint32_t>(value));
  }
  parts.Reverse();
  Integer result(parts, decimal.Sign());
  return result;
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
Integer CreateIntegerZero() {
  return Integer(List<uint32_t>({0}), false);
}
Integer CreateIntegerOne() {
  return Integer(List<uint32_t>({1}), false);
}
Integer CreateIntegerTwo() {
  return Integer(List<uint32_t>({2}), false);
}
uint64_t ToU64(const Integer& integer) {
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
Integer CreateIntegerWithU64(uint64_t value, bool sign) {
  List<uint32_t> parts;
  while (value != 0) {
    parts.Push(value & 0x0000FFFF);
    value >>= 16;
  }
  parts.Reverse();
  return Integer(parts, sign);
}

bool IsBigNumber(const Integer& integer) {
  return integer.Data().Size() > 4;
}

Integer CreateIntegerWithI64(int64_t value) {
  if (value == 0) {
    return CreateIntegerZero();
  }
  if (value < 0) {
    return CreateIntegerWithU64(static_cast<uint64_t>(-value), true);
  }
  return CreateIntegerWithU64(static_cast<uint64_t>(value), false);
}
int64_t ToI64(const Integer& integer) {
  if (integer.IsZero()) {
    return 0;
  }
  if (integer.Data().Size() > 4) {
    throw std::runtime_error("Integer is too large to be converted to index");
  }
  int64_t result = 0;
  for (Index i = 0; i < integer.Data().Size(); i++) {
    result = (result << 16) | integer.Data().Get(i);
  }
  return integer.Sign() ? -static_cast<int64_t>(result) : result;
}

}  // namespace torchlight::Collections
