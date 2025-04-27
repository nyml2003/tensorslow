#ifndef TORCHLIGHT_COLLECTIONS_STRING_HELPER_H
#define TORCHLIGHT_COLLECTIONS_STRING_HELPER_H

#include "Collections/String/String.h"

#include <functional>

namespace torchlight::Collections {
String CreateStringWithCString(const char* str) noexcept;
template <typename T>
String ToString(T value) {
  return CreateStringWithCString(std::to_string(value).c_str());
}
std::size_t Hash(const List<Byte>& str) noexcept;
}  // namespace torchlight::Collections
#endif