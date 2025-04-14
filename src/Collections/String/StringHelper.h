#ifndef TORCHLIGHT_COLLECTIONS_STRING_HELPER_H
#define TORCHLIGHT_COLLECTIONS_STRING_HELPER_H

#include "Collections/String/Bytes.h"
#include "Collections/String/String.h"

#include <functional>

namespace torchlight::Collections {
Unicode GetUnicode(
  Index& index,
  const std::function<Byte(Index)>& GetByte,
  const std::function<bool(Index)>& IsValid
) noexcept;
String CreateStringWithCString(const char* str) noexcept;
String CreateStringWithBytes(const List<Byte>& bytes) noexcept;
String ToString(double value);
String ToString(uint64_t value);
String ToString(uint32_t value);
String ToString(int32_t value);
String ToString(int64_t value);
std::string ToCppString(const String& str);
String Join(const List<String>& list, const String& separator);
std::size_t UnicodeListHash(const List<Unicode>& str) noexcept;
std::size_t Hash(const char* str) noexcept;
}  // namespace torchlight::Collections

namespace std {
template <>
struct hash<torchlight::Collections::String> {
  size_t operator()(const torchlight::Collections::String& str) const {
    return str.Hash();
  }
};
}  // namespace std
#endif