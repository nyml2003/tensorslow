#ifndef TORCHLIGHT_COLLECTIONS_INTEGER_HELPER_H
#define TORCHLIGHT_COLLECTIONS_INTEGER_HELPER_H
#include "Collections/Integer.h"
namespace torchlight::Collections {
int8_t UnicodeToHex(Unicode unicode) noexcept;
Unicode HexToUnicode(uint8_t hex) noexcept;
Integer CreateIntegerWithDecimal(const Decimal& decimal);
void TrimLeadingZero(List<uint32_t>& parts);
void TrimTrailingZero(List<uint32_t>& parts);
Integer Slice(const Integer& integer, Index start, Index end);
Integer CreateIntegerWithString(const String& str);
Integer CreateIntegerWithCString(const char* str);
Integer CreateIntegerZero();
Integer CreateIntegerOne();
Integer CreateIntegerTwo();
Integer CreateIntegerWithU64(uint64_t value);
uint64_t ToU64(const Integer& integer);
uint64_t safe_add(uint64_t lhs, int64_t rhs);
}  // namespace torchlight::Collections
#endif