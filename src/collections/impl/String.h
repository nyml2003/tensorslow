#ifndef TORCHLIGHT_COLLECTIONS_STRING_IMPL_H
#define TORCHLIGHT_COLLECTIONS_STRING_IMPL_H

#include "collections/Bytes.h"
#include "collections/String.h"

#include <functional>

namespace torchlight::collections {

Unicode GetUnicode(
  Index& index,
  const std::function<Byte(Index)>& GetByte,
  const std::function<bool(Index)>& IsValid
);

String CreateStringWithCString(const char* str);

String CreateStringWithBytes(const Bytes& bytes);

String ToString(double value);

String ToString(uint64_t value);

String ToString(uint32_t value);

String ToString(int32_t value);

String ToString(int64_t value);

std::unique_ptr<char[]> ToCString(const String& str);

}  // namespace torchlight::collections

#endif