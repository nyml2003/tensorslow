
#include "Collections/String/StringHelper.h"
#include "Collections/String/BytesHelper.h"
#include "Collections/String/String.h"

#include <cstring>
#include <stdexcept>
namespace torchlight::Collections {
Unicode GetUnicode(
  Index& index,
  const std::function<Byte(Index)>& GetByte,
  const std::function<bool(Index)>& IsValid
) {
  Byte leadByte = GetByte(index);
  int sequenceLength = 0;
  if ((leadByte & 0x80) == 0) {
    sequenceLength = 1;
  } else if ((leadByte & 0xE0) == 0xC0) {
    sequenceLength = 2;
  } else if ((leadByte & 0xF0) == 0xE0) {
    sequenceLength = 3;
  } else if ((leadByte & 0xF8) == 0xF0) {
    sequenceLength = 4;
  } else {
    throw std::runtime_error("Invalid UTF-8 sequence");
  }
  if (!IsValid(index + sequenceLength - 1)) {
    throw std::runtime_error("Invalid UTF-8 sequence");
  }
  Unicode codePoint = 0;
  switch (sequenceLength) {
    case 1:
      codePoint = leadByte;
      break;
    case 2:
      codePoint = (leadByte & 0x1F) << 6;
      codePoint |= GetByte(index + 1) & 0x3F;
      break;
    case 3:
      codePoint = (leadByte & 0x0F) << 12;
      codePoint |= (GetByte(index + 1) & 0x3F) << 6;
      codePoint |= GetByte(index + 2) & 0x3F;
      break;
    case 4:
      codePoint = (leadByte & 0x07) << 18;
      codePoint |= (GetByte(index + 1) & 0x3F) << 12;
      codePoint |= (GetByte(index + 2) & 0x3F) << 6;
      codePoint |= GetByte(index + 3) & 0x3F;
      break;
    default:
      throw std::runtime_error("Invalid UTF-8 sequence");
  }
  index += sequenceLength;
  return codePoint;
}
String CreateStringWithCString(const char* str) {
  List<Unicode> codePoints;
  size_t length = strlen(str);
  size_t index = 0;
  while (index < length) {
    Unicode codePoint = GetUnicode(
      index,
      [str](Index index) -> Byte { return static_cast<Byte>(str[index]); },
      [length](Index index) -> bool { return index < length; }
    );
    codePoints.Push(codePoint);
  }
  return String(codePoints);
}
String CreateStringWithBytes(const Bytes& bytes) {
  List<Unicode> codePoints;
  size_t length = bytes.Size();
  size_t index = 0;
  while (index < length) {
    Unicode codePoint = GetUnicode(
      index, [bytes](Index index) -> Byte { return bytes[index]; },
      [length](Index index) -> bool { return index < length; }
    );
    codePoints.Push(codePoint);
  }
  return String(codePoints);
}
std::string ToCppString(const String& str) {
  return ToCppString(ToBytes(str));
}
String ToString(double value) {
  char buffer[32];
  snprintf(buffer, sizeof(buffer), "%.6f", value);
  return CreateStringWithCString(buffer);
}
String ToString(int32_t value) {
  char buffer[32];
  snprintf(buffer, sizeof(buffer), "%d", value);
  return CreateStringWithCString(buffer);
}
String ToString(uint64_t value) {
  char buffer[32];  // 足够大的缓冲区
  // 使用 %llu 格式化 uint64_t
  snprintf(
    buffer, sizeof(buffer), "%llu", static_cast<unsigned long long>(value)
  );
  return CreateStringWithCString(buffer);
}
String ToString(int64_t value) {
  char buffer[32];
  snprintf(buffer, sizeof(buffer), "%ld", value);
  return CreateStringWithCString(buffer);
}
String ToString(uint32_t value) {
  char buffer[32];
  snprintf(buffer, sizeof(buffer), "%u", value);
  return CreateStringWithCString(buffer);
}

String Join(const List<String>& list, const String& separator) {
  String str;
  for (Index i = 0; i < list.Size(); i++) {
    str.Concat(list.Get(i));
    if (i < list.Size() - 1) {
      str.Concat(separator);
    }
  }
  return str;
}

}  // namespace torchlight::Collections