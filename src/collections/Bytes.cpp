#include "collections/Bytes.h"

#include "collections/Decimal.h"
#include "collections/Integer.h"
#include "collections/common.h"
#include "collections/impl/Bytes.h"
#include "collections/impl/Decimal.h"
#include "collections/impl/Integer.h"
#include "collections/impl/String.h"

#include <cstring>
#include <iostream>
#include <memory>

namespace torchlight::collections {

Bytes CreateBytesWithCString(const char* str) {
  const Byte* data = reinterpret_cast<const Byte*>(str);
  return Bytes(List<Byte>(static_cast<Index>(std::strlen(str)), data));
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
    Unicode codePoint = str[i];
    if (codePoint < 0x80) {
      bytes.Push(static_cast<Byte>(codePoint));
    } else if (codePoint < 0x800) {
      bytes.Push(static_cast<Byte>(0xC0 | (codePoint >> 6)));
      bytes.Push(static_cast<Byte>(0x80 | (codePoint & 0x3F)));
    } else if (codePoint < 0x10000) {
      bytes.Push(static_cast<Byte>(0xE0 | (codePoint >> 12)));
      bytes.Push(static_cast<Byte>(0x80 | ((codePoint >> 6) & 0x3F)));
      bytes.Push(static_cast<Byte>(0x80 | (codePoint & 0x3F)));
    } else if (codePoint <= 0x10FFFF) {
      bytes.Push(static_cast<Byte>(0xF0 | (codePoint >> 18)));
      bytes.Push(static_cast<Byte>(0x80 | ((codePoint >> 12) & 0x3F)));
      bytes.Push(static_cast<Byte>(0x80 | ((codePoint >> 6) & 0x3F)));
      bytes.Push(static_cast<Byte>(0x80 | (codePoint & 0x3F)));
    } else {
      throw std::runtime_error("Invalid Unicode code point");
    }
  }
  return Bytes(bytes);
}

Bytes::Bytes(const List<Byte>& value) : value(value) {}

Bytes::Bytes() : value() {}

[[nodiscard]] Bytes Bytes::Add(const Bytes& rhs) const {
  List<Byte> bytes(value.Copy());
  bytes.Concat(rhs.value);
  return Bytes(bytes);
}

[[nodiscard]] Byte Bytes::Get(Index index) const {
  return value.Get(index);
}

Byte& Bytes::operator[](Index index) {
  return value[index];
}

const Byte& Bytes::operator[](Index index) const {
  return value[index];
}

[[nodiscard]] Index Bytes::Size() const {
  return value.Size();
}

void Bytes::Concat(const Bytes& rhs) {
  value.Concat(rhs.value);
}

void Bytes::Push(Byte byte) {
  value.Push(byte);
}

Bytes Bytes::Slice(Index start, Index end) const {
  return Bytes(value.Slice(start, end));
}

std::unique_ptr<char[]> ToCString(const Bytes& bytes) {
  List<Byte> data = bytes.Value();
  const Byte* dataPtr = data.Data();
  const char* str = reinterpret_cast<const char*>(dataPtr);
  std::unique_ptr<char[]> cstr(new char[bytes.Size() + 1]);
  std::strncpy(cstr.get(), str, bytes.Size());
  cstr[bytes.Size()] = '\0';
  return cstr;
}

List<Byte> Bytes::Value() const {
  return value.Copy();
}

Bytes Serialize(double value) {
  return Bytes(List<Byte>(sizeof(double), reinterpret_cast<Byte*>(&value)));
}

Bytes Serialize(uint64_t value) {
  return Bytes(List<Byte>(sizeof(uint64_t), reinterpret_cast<Byte*>(&value)));
}

Bytes Serialize(int64_t value) {
  return Serialize(static_cast<uint64_t>(value));
}

Bytes Serialize(uint32_t value) {
  return Bytes(List<Byte>(sizeof(uint32_t), reinterpret_cast<Byte*>(&value)));
}

Bytes Serialize(uint16_t value) {
  return Bytes(List<Byte>(sizeof(uint16_t), reinterpret_cast<Byte*>(&value)));
}

Bytes Serialize(int32_t value) {
  return Bytes(List<Byte>(sizeof(int32_t), reinterpret_cast<Byte*>(&value)));
}

// Bytes Serialize(const Integer& value) {
//   Bytes bytes;
//   if (value.IsZero()) {
//     throw std::runtime_error("Cannot serialize zero Integer");
//   }
//   bytes.InplaceAdd(value.Sign() ? '-' : '+');
//   const auto data = value.Data();
//   bytes.InplaceConcat(Serialize(data.Size()));
//   for (Index i = 0; i < data.Size(); i++) {
//     bytes.InplaceConcat(Serialize(static_cast<uint16_t>(data.Get(i) &
//     0xFFFF)));
//   }
//   return bytes;
// }

Bytes Serialize(const String& value) {
  return Serialize(value.Size()).Add(ToBytes(value));
}

Bytes Serialize(const Bytes& value) {
  return Serialize(value.Size()).Add(value);
}

double DeserializeDouble(const Bytes& bytes) {
  if (bytes.Size() != sizeof(double)) {
    throw std::runtime_error("Invalid byte size for double");
  }
  return *reinterpret_cast<const double*>(bytes.Value().Data());
}

uint64_t DeserializeUInt64(const Bytes& bytes) {
  if (bytes.Size() != sizeof(uint64_t)) {
    throw std::runtime_error("Invalid byte size for uint64_t");
  }
  return *reinterpret_cast<const uint64_t*>(bytes.Value().Data());
}

int64_t DeserializeInt64(const Bytes& bytes) {
  return static_cast<int64_t>(DeserializeUInt64(bytes));
}

uint32_t DeserializeUInt32(const Bytes& bytes) {
  if (bytes.Size() != sizeof(uint32_t)) {
    throw std::runtime_error("Invalid byte size for uint32_t");
  }
  return *reinterpret_cast<const uint32_t*>(bytes.Value().Data());
}

int32_t DeserializeInt32(const Bytes& bytes) {
  return static_cast<int32_t>(DeserializeUInt32(bytes));
}

uint16_t DeserializeUInt16(const Bytes& bytes) {
  if (bytes.Size() != sizeof(uint16_t)) {
    throw std::runtime_error("Invalid byte size for uint16_t");
  }
  return *reinterpret_cast<const uint16_t*>(bytes.Value().Data());
}

String DeserializeString(const Bytes& bytes) {
  Index size = DeserializeUInt64(bytes.Slice(0, sizeof(uint64_t)));
  return CreateStringWithBytes(bytes.Slice(sizeof(uint64_t), bytes.Size()));
}

Bytes DeserializeBytes(const Bytes& bytes) {
  Index size = DeserializeUInt64(bytes.Slice(0, sizeof(uint64_t)));
  return bytes.Slice(sizeof(uint64_t), bytes.Size());
}

Bytes Serialize(const Decimal& value) {
  if (value.IsZero()) {
    return Bytes();
  }
  Bytes bytes;
  bytes.Push(value.Sign() ? '-' : '+');
  const auto data = value.Data();
  bytes.Concat(Serialize(data.Size()));
  for (Index i = 0; i < data.Size(); i++) {
    bytes.Push(DecToByte(data.Get(i)));
  }
  return Bytes(bytes);
}

Decimal DeserializeDecimal(const Bytes& bytes) {
  if (bytes.Size() == 0) {
    return CreateDecimalZero();
  }
  Index i = 0;
  bool sign = false;
  switch (bytes.Get(i)) {
    case '+':
      sign = false;
      break;
    case '-':
      sign = true;
      break;
    default:
      throw std::runtime_error("Invalid sign for Decimal");
  }
  i++;
  Index size = DeserializeUInt64(bytes.Slice(i, i + sizeof(uint64_t)));
  i += sizeof(uint64_t);
  List<int32_t> data;
  for (Index j = 0; j < size; j++) {
    data.Push(UnicodeToDec(bytes.Get(i + j)));
  }
  return Decimal(data, sign);
}

Bytes Serialize(const Integer& value) {
  if (value.IsZero()) {
    return Bytes();
  }
  Bytes bytes;
  bytes.Push(value.Sign() ? '-' : '+');
  const auto data = value.Data();
  bytes.Concat(Serialize(data.Size()));
  for (Index i = 0; i < data.Size(); i++) {
    bytes.Concat(Serialize(static_cast<uint16_t>(data.Get(i) & 0xFFFF)));
  }
  return Bytes(bytes);
}

Integer DeserializeInteger(const Bytes& bytes) {
  if (bytes.Size() == 0) {
    return CreateIntegerZero();
  }
  Index i = 0;
  bool sign = false;
  switch (bytes.Get(i)) {
    case '+':
      sign = false;
      break;
    case '-':
      sign = true;
      break;
    default:
      throw std::runtime_error("Invalid sign for Integer");
  }
  i++;
  Index size = DeserializeUInt64(bytes.Slice(i, i + sizeof(uint64_t)));
  i += sizeof(uint64_t);
  List<uint32_t> data;
  for (Index j = 0; j < size; j++) {
    data.Push(DeserializeUInt16(
      bytes.Slice(i + j * sizeof(uint16_t), i + (j + 1) * sizeof(uint16_t))
    ));
  }
  return Integer(data, sign);
}

}  // namespace torchlight::collections
