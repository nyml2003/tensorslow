#ifndef TORCHLIGHT_COLLECTIONS_IMPL_DECIMAL_H
#define TORCHLIGHT_COLLECTIONS_IMPL_DECIMAL_H

#include "collections/Decimal.h"
#include "collections/Integer.h"
#include "collections/String.h"

namespace torchlight::collections {

int32_t UnicodeToDec(Unicode c) noexcept;

Byte DecToByte(int32_t c) noexcept;

bool IsNegative(const String& str);

Decimal Slice(const Decimal& decimal, Index start, Index end);

Decimal CreateDecimalWithString(const String& str);

Decimal CreateDecimalWithCString(const char* str);

Decimal CreateDecimalZero();

Decimal CreateDecimalOne();

Decimal CreateDecimalWithU32(uint32_t value);

Decimal CreateDecimalWithInteger(const Integer& integer);

void TrimLeadingZero(List<int32_t>& parts);

void TrimTrailingZero(List<int32_t>& parts);

}  // namespace torchlight::collections

#endif