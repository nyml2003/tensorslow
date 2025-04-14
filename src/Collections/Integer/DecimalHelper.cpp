#include "Collections/Integer/DecimalHelper.h"
#include <stdexcept>
#include "Collections/String/StringHelper.h"
#include "Common.h"

namespace torchlight::Collections {
Decimal CreateDecimalZero() {
  return CreateDecimalWithU32(0);
}
Decimal CreateDecimalOne() {
  return CreateDecimalWithU32(1);
}
Decimal CreateDecimalWithU32(uint32_t value) {
  List<int32_t> parts;
  while (value > 0) {
    parts.Push(static_cast<int32_t>(value % 10));
    value /= 10;
  }
  parts.Reverse();
  return Decimal(parts, false);
}
int32_t UnicodeToDec(Unicode unicode) noexcept {
  if (unicode >= Unicode_0 && unicode <= Unicode_9) {
    return static_cast<int32_t>(unicode - Unicode_0);
  }
  return -1;
}
Byte DecToByte(int32_t dec) noexcept {
  return static_cast<Byte>(static_cast<Byte>(dec) + Unicode_0);
}
Decimal CreateDecimalWithString(const String& str) {
  Index index = 0;
  bool sign = false;
  if (str[0] == UnicodeMinus) {
    sign = true;
    index = 1;
  }
  List<int32_t> parts;
  for (; index < str.Size(); index++) {
    int32_t character = UnicodeToDec(str[index]);
    if (character == -1) {
      throw std::runtime_error("Invalid character in Decimal");
    }
    parts.Push(character);
  }
  return Decimal(parts, sign);
}
void TrimTrailingZero(List<int32_t>& parts) {
  for (Index i = parts.Size() - 1; ~i; --i) {
    if (parts[i] != 0 || i == 0) {
      parts = parts.Slice(0, i + 1);
      break;
    }
  }
}
void TrimLeadingZero(List<int32_t>& parts) {
  for (Index i = 0; i < parts.Size(); i++) {
    if (parts[i] != 0 || i == parts.Size() - 1) {
      parts = parts.Slice(i, parts.Size());
      break;
    }
  }
}
Decimal CreateDecimalWithCString(const char* str) {
  return CreateDecimalWithString(CreateStringWithCString(str));
}
}  // namespace torchlight::Collections