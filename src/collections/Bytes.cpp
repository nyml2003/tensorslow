#include "collections/Bytes.h"
#include <cstring>
#include "collections/common.h"
#include "collections/impl/Bytes.h"
#include "collections/impl/String.h"

#include <iostream>
#include <memory>

namespace torchlight::collections {

Bytes CreateBytesWithCString(const char* str) {
  List<Byte> bytes;
  std::copy(str, str + strlen(str), bytes.Data());
  return Bytes(bytes);
}

void Write(Bytes& bytes, const String& filename) {
  const Byte* data = bytes.Value().Data();
  std::unique_ptr<char[]> filenameCString = ToCString(filename);
  if (!filenameCString) {
    std::cerr << "文件名转换失败" << std::endl;
    return;
  }

  std::ofstream file(filenameCString.get(), std::ios::binary);
  if (!file.is_open()) {
    std::cerr << "无法打开文件：" << filenameCString.get() << std::endl;
    return;
  }

  file.write(
    reinterpret_cast<const char*>(data),
    static_cast<std::streamsize>(bytes.Size())
  );
  std::cout << "写入文件：" << filenameCString.get() << std::endl;
  std::cout << "文件大小：" << bytes.Size() << std::endl;
  if (!file) {
    std::cerr << "写入文件时出错：" << filenameCString.get() << std::endl;
  }

  file.close();
}

Bytes ToBytes(const String& str) {
  List<Byte> bytes;
  for (Index i = 0; i < str.Size(); i++) {
    Unicode codePoint = str.Get(i);
    if (codePoint < 0x80) {
      bytes.Add(static_cast<Byte>(codePoint));
    } else if (codePoint < 0x800) {
      bytes.Add(static_cast<Byte>(0xC0 | (codePoint >> 6)));
      bytes.Add(static_cast<Byte>(0x80 | (codePoint & 0x3F)));
    } else if (codePoint < 0x10000) {
      bytes.Add(static_cast<Byte>(0xE0 | (codePoint >> 12)));
      bytes.Add(static_cast<Byte>(0x80 | ((codePoint >> 6) & 0x3F)));
      bytes.Add(static_cast<Byte>(0x80 | (codePoint & 0x3F)));
    } else if (codePoint <= 0x10FFFF) {
      bytes.Add(static_cast<Byte>(0xF0 | (codePoint >> 18)));
      bytes.Add(static_cast<Byte>(0x80 | ((codePoint >> 12) & 0x3F)));
      bytes.Add(static_cast<Byte>(0x80 | ((codePoint >> 6) & 0x3F)));
      bytes.Add(static_cast<Byte>(0x80 | (codePoint & 0x3F)));
    } else {
      throw std::runtime_error("Invalid Unicode code point");
    }
  }
  return Bytes(bytes);
}

Bytes::Bytes(const List<Byte>& value) : value(value) {}

[[nodiscard]] Bytes Bytes::Concat(const Bytes& rhs) const {
  List<Byte> bytes(value.Copy());
  bytes.Add(rhs.value);
  return Bytes(bytes);
}

[[nodiscard]] Byte Bytes::Get(Index index) const {
  return value.Get(index);
}

[[nodiscard]] Index Bytes::Size() const {
  return value.Size();
}

void Bytes::InplaceConcat(const Bytes& rhs) {
  value.Add(rhs.value);
}

void Bytes::InplaceAdd(Byte byte) {
  value.Add(byte);
}
Bytes Bytes::Slice(Index start, Index end) const {
  return Bytes(value.Slice(start, end));
}

std::unique_ptr<char[]> ToCString(const Bytes& bytes) {
  auto str = std::make_unique<char[]>(bytes.Size() + 1);
  std::copy(
    bytes.Value().Data(), bytes.Value().Data() + bytes.Size(), str.get()
  );
  str[bytes.Size()] = '\0';
  return str;
}

List<Byte> Bytes::Value() const {
  return value;
}

Bytes Serialize(double value) {
  List<Byte> bytes(sizeof(double));
  Byte* ptr = reinterpret_cast<Byte*>(&value);
  bytes.Add(ptr, sizeof(double));
  return Bytes(bytes);
}

Bytes Serialize(uint64_t value) {
  List<Byte> bytes(sizeof(uint64_t));
  Byte* ptr = reinterpret_cast<Byte*>(&value);
  bytes.Add(ptr, sizeof(uint64_t));
  return Bytes(bytes);
}

Bytes Serialize(int64_t value) {
  List<Byte> bytes(sizeof(int64_t));
  Byte* ptr = reinterpret_cast<Byte*>(&value);
  bytes.Add(ptr, sizeof(int64_t));
  return Bytes(bytes);
}

Bytes Serialize(uint32_t value) {
  List<Byte> bytes(sizeof(uint32_t));
  Byte* ptr = reinterpret_cast<Byte*>(&value);
  bytes.Add(ptr, sizeof(uint32_t));
  return Bytes(bytes);
}

Bytes Serialize(uint16_t value) {
  List<Byte> bytes(sizeof(uint16_t));
  Byte* ptr = reinterpret_cast<Byte*>(&value);
  bytes.Add(ptr, sizeof(uint16_t));
  return Bytes(bytes);
}

Bytes Serialize(int32_t value) {
  List<Byte> bytes(sizeof(int32_t));
  Byte* ptr = reinterpret_cast<Byte*>(&value);
  bytes.Add(ptr, sizeof(int32_t));
  return Bytes(bytes);
}

Bytes Serialize(const Integer& value) {
  Bytes bytes;
  if (value.IsZero()) {
    throw std::runtime_error("Cannot serialize zero Integer");
  }
  bytes.InplaceAdd(value.Sign() ? '-' : '+');
  const auto data = value.Data();
  bytes.InplaceConcat(Serialize(data.Size()));
  for (Index i = 0; i < data.Size(); i++) {
    bytes.InplaceConcat(Serialize(static_cast<uint16_t>(data.Get(i) & 0xFFFF)));
  }
  return bytes;
}

Bytes Serialize(const String& value) {
  Bytes bytes;
  bytes.InplaceConcat(Serialize(value.Size()));
  return bytes.Concat(ToBytes(value));
}

}  // namespace torchlight::collections
