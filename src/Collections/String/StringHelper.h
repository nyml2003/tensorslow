#ifndef TORCHLIGHT_COLLECTIONS_STRING_HELPER_H
#define TORCHLIGHT_COLLECTIONS_STRING_HELPER_H

#include "Collections/String/Bytes.h"
#include "Collections/String/String.h"

#include <functional>

namespace torchlight::Collections {
String CreateStringWithCString(const char* str) noexcept;
String CreateStringWithBytes(const List<Byte>& bytes) noexcept;
String ToString(double value);
String ToString(uint64_t value);
String ToString(uint32_t value);
String ToString(int32_t value);
String ToString(int64_t value);
std::string ToCppString(const String& str);
Unicode GetUnicode(size_t& index, const Byte* data, size_t dataLength) noexcept;
std::size_t Hash(const char* str) noexcept;
std::size_t Hash(const List<Byte>& bytes) noexcept;
}  // namespace torchlight::Collections
#endif