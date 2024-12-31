#ifndef TORCHLIGHT_COLLECTIONS_IMPL_INTEGER_H
#define TORCHLIGHT_COLLECTIONS_IMPL_INTEGER_H

#include <limits>
#include <stdexcept>
#include "collections/Integer.h"

namespace torchlight::collections {

int8_t UnicodeToHex(Unicode c) noexcept;

Unicode HexToUnicode(uint8_t c) noexcept;

Integer CreateIntegerWithDecimal(const Decimal& decimal);

void TrimLeadingZero(List<uint32_t>& parts);

void TrimTrailingZero(List<uint32_t>& parts);

Integer Slice(const Integer& integer, Index start, Index end);

Integer CreateIntegerWithString(const String& str);

Integer CreateIntegerWithBytes(const Bytes& bytes);

Integer CreateIntegerZero();

Integer CreateIntegerOne();

Integer CreateIntegerWithIndex(Index index);

Index ToIndex(const Integer& integer);

uint64_t safe_add(uint64_t a, int64_t b);

}  // namespace torchlight::collections

#endif