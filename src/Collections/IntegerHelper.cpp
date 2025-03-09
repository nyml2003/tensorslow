#include "Collections/IntegerHelper.h"
#include "Collections/DecimalHelper.h"
#include "Collections/Iterator.h"
#include "Collections/StringHelper.h"
#include "Common.h"

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
  if (hex >= 0 && hex <= 9) {
    return static_cast<Unicode>(hex + Unicode_0);
  }
  if (hex >= 10 && hex <= 15) {
    return static_cast<Unicode>(hex - 10 + Unicode_A);
  }
  return 0;
}
Integer CreateIntegerWithString(const String& str) {
  if (str.Size() > 2 && str.Get(0) == Unicode_0 &&
      (str.Get(1) == Unicode_X || str.Get(1) == Unicode_x)) {
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
    parts.Push(value);
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
  List<uint32_t> parts = {0};
  return Integer(parts, false);
}
Integer CreateIntegerOne() {
  List<uint32_t> parts = {1};
  return Integer(parts, false);
}
Integer CreateIntegerTwo() {
  List<uint32_t> parts = {2};
  return Integer(parts, false);
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
Integer CreateIntegerWithU64(uint64_t value) {
  List<uint32_t> parts;
  while (value != 0) {
    parts.Push(value & 0x0000FFFF);
    value >>= 16;
  }
  parts.Reverse();
  return Integer(parts, false);
}
uint64_t safe_add(uint64_t lhs, int64_t rhs) {
  if (rhs >= 0) {
    // b 是正数或零，直接相加
    if (lhs > std::numeric_limits<uint64_t>::max() - rhs) {
      throw std::overflow_error("Addition overflow");
    }
    return lhs + static_cast<uint64_t>(rhs);
  }
  // b 是负数，转换为补码并相减
  if (lhs < static_cast<uint64_t>(-rhs)) {
    throw std::underflow_error("Subtraction underflow");
  }
  return lhs - static_cast<uint64_t>(-rhs);
}
}  // namespace torchlight::Collections