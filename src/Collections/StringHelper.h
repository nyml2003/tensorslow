#ifndef TORCHLIGHT_COLLECTIONS_STRING_HELPER_H
#define TORCHLIGHT_COLLECTIONS_STRING_HELPER_H
#include <functional>
#include "Collections/Bytes.h"
#include "Collections/String.h"

namespace torchlight::Collections {
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
std::string ToCppString(const String& str);
String Join(const List<String>& list, const String& separator);
}  // namespace torchlight::Collections
#endif