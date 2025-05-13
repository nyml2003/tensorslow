#ifndef TENSORSLOW_COLLECTIONS_DECIMAL_HELPER_H
#define TENSORSLOW_COLLECTIONS_DECIMAL_HELPER_H
#include "Collections/Integer/Decimal.h"
#include "Collections/Integer/Integer.h"
#include "Collections/String/String.h"
namespace tensorslow::Collections {
// int32_t UnicodeToDec(Unicode unicode) noexcept;
Byte DecToByte(int32_t dec) noexcept;
int32_t ByteToDec(Byte byte) noexcept;
Decimal CreateDecimalWithString(const String& str);
Decimal CreateDecimalWithCString(const char* str);
Decimal CreateDecimalZero();
Decimal CreateDecimalOne();
Decimal CreateDecimalWithU32(uint32_t value);
Decimal CreateDecimalWithInteger(const Integer& integer);
void TrimLeadingZero(List<int32_t>& parts);
void TrimTrailingZero(List<int32_t>& parts);
}  // namespace tensorslow::Collections
#endif