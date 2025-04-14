
#include "Collections/String/StringHelper.h"
#include "Collections/String/BytesHelper.h"
#include "Collections/String/String.h"

#include <cstring>
#include <stdexcept>
namespace torchlight::Collections {
static const unsigned char utf8_sequence_length[256] = {
  1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
  1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
  1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
  1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
  1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,

  // 0x80-0x9F 是后续字节，无效leadByte → 0
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
  0, 0, 0, 0, 0, 0,

  // 0xA0-0xBF → 后续字节 → 0
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
  0, 0, 0, 0, 0, 0,

  // 0xC0-0xDF → 2字节
  2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2,
  2, 2, 2, 2, 2, 2,

  // 0xE0-0xEF →3字节
  3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3,

  // 0xF0-0xF7 →4字节
  4, 4, 4, 4, 4, 4, 4, 4,

  // 0xF8-0xFF →无效 →0
  0, 0, 0, 0, 0, 0, 0, 0};
Unicode
GetUnicode(size_t& index, const Byte* data, size_t dataLength) noexcept {
  Byte leadByte = data[index];
  int sequenceLength = utf8_sequence_length[leadByte];
  Unicode codePoint = 0;

  switch (sequenceLength) {
    case 1:
      codePoint = leadByte;
      break;
    case 2: {
      Byte byte1 = data[index + 1];
      codePoint = (leadByte & 0x1F) << 6 | (byte1 & 0x3F);
      break;
    }
    case 3: {
      Byte byte1 = data[index + 1];
      Byte byte2 = data[index + 2];
      codePoint =
        (leadByte & 0x0F) << 12 | (byte1 & 0x3F) << 6 | (byte2 & 0x3F);
      break;
    }
    case 4: {
      Byte byte1 = data[index + 1];
      Byte byte2 = data[index + 2];
      Byte byte3 = data[index + 3];
      codePoint = (leadByte & 0x07) << 18 | (byte1 & 0x3F) << 12 |
                  (byte2 & 0x3F) << 6 | (byte3 & 0x3F);
      break;
    }
    default:
      // 处理无效的序列（如返回0或错误值）
      break;
  }

  index += sequenceLength;
  return codePoint;
}
String CreateStringWithCString(const char* str) noexcept {
  List<Unicode> codePoints;
  size_t length = strlen(str);
  size_t index = 0;
  const Byte* data = reinterpret_cast<const Byte*>(str);
  while (index < length) {
    codePoints.Push(GetUnicode(index, data, length));
  }
  return String(codePoints);
}

String CreateStringWithBytes(const List<Byte>& bytes) noexcept {
  List<Unicode> codePoints;
  const Byte* data = bytes.Data();  // 假设List提供Data()返回指针
  size_t length = bytes.Size();
  size_t index = 0;

  while (index < length) {
    codePoints.Push(GetUnicode(index, data, length));
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
  snprintf(buffer, sizeof(buffer), "%lld", value);
  return CreateStringWithCString(buffer);
}
String ToString(uint32_t value) {
  char buffer[32];
  snprintf(buffer, sizeof(buffer), "%u", value);
  return CreateStringWithCString(buffer);
}

String Join(const List<String>& list, const String& separator) {
  StringBuilder sb;
  for (Index i = 0; i < list.Size(); i++) {
    sb.Append(list.Get(i));
    if (i < list.Size() - 1) {
      sb.Append(separator);
    }
  }
  return sb.ToString();
}

std::size_t UnicodeListHash(const List<Unicode>& str) noexcept {
  // FNV-1a 常量（64 位版本）
  constexpr std::size_t FNV_OFFSET_BASIS = 14695981039346656037ULL;
  constexpr std::size_t FNV_PRIME = 1099511628211ULL;

  std::size_t hash = FNV_OFFSET_BASIS;

  for (Index i = 0; i < str.Size(); ++i) {
    hash ^= str[i];
    hash *= FNV_PRIME;
  }
  return hash;
}

}  // namespace torchlight::Collections