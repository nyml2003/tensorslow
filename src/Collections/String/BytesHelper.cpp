#include "Collections/String/BytesHelper.h"
#include "Collections/Integer/DecimalHelper.h"
#include "Collections/Integer/IntegerHelper.h"
#include "Collections/String/StringHelper.h"

#include <cstring>
#include <fstream>
#include <iostream>
#include <stdexcept>
namespace torchlight::Collections {
String ReprByte(Byte byte) {
  // 使用 \x 格式表示一个字节
  char buffer[5];  // 需要 5 个字符：\x + 2 个十六进制字符 + 终止符
  std::snprintf(buffer, sizeof(buffer), "\\x%02X", byte);
  return CreateStringWithCString(buffer);
}
Bytes CreateBytesWithCString(const char* str) {
  const Byte* data = reinterpret_cast<const Byte*>(str);
  return Bytes(List<Byte>(static_cast<Index>(std::strlen(str)), data));
}
void Write(const Bytes& bytes, const String& filename) {
  List<Byte> data = bytes.Value();
  std::string filenameCppString = ToCppString(filename);
  if (filenameCppString.empty()) {
    throw std::runtime_error("Filename is empty");
  }
  std::ofstream file(filenameCppString, std::ios::binary);
  if (!file.is_open()) {
    std::cerr << "无法打开文件：" << filenameCppString << std::endl;
    return;
  }
  file.write(
    reinterpret_cast<const char*>(data.Data()),
    static_cast<std::streamsize>(bytes.Size())
  );
  std::cout << "写入文件：" << filenameCppString << std::endl;
  std::cout << "文件大小：" << bytes.Size() << std::endl;
  if (!file) {
    std::cerr << "写入文件时出错：" << filenameCppString << std::endl;
  }
  file.close();
}
Bytes ToBytes(const String& str) noexcept {
  List<Byte> bytes(str.Size());
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
    }
  }
  return Bytes(bytes);
}
std::string ToCppString(const Bytes& bytes) {
  std::string str;
  for (Index i = 0; i < bytes.Size(); i++) {
    str.push_back(static_cast<char>(bytes.Get(i)));
  }
  return str;
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
Bytes Serialize(const String& value) {
  Bytes bytes = ToBytes(value);
  return Serialize(bytes.Size()).Add(bytes);
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
uint64_t DeserializeU64(const Bytes& bytes) {
  if (bytes.Size() != sizeof(uint64_t)) {
    throw std::runtime_error("Invalid byte size for uint64_t");
  }
  return *reinterpret_cast<const uint64_t*>(bytes.Value().Data());
}
int64_t DeserializeI64(const Bytes& bytes) {
  return static_cast<int64_t>(DeserializeU64(bytes));
}
uint32_t DeserializeU32(const Bytes& bytes) {
  if (bytes.Size() != sizeof(uint32_t)) {
    throw std::runtime_error("Invalid byte size for uint32_t");
  }
  return *reinterpret_cast<const uint32_t*>(bytes.Value().Data());
}
int32_t DeserializeI32(const Bytes& bytes) {
  return static_cast<int32_t>(DeserializeU32(bytes));
}
uint16_t DeserializeU16(const Bytes& bytes) {
  if (bytes.Size() != sizeof(uint16_t)) {
    throw std::runtime_error("Invalid byte size for uint16_t");
  }
  return *reinterpret_cast<const uint16_t*>(bytes.Value().Data());
}
String DeserializeString(const Bytes& bytes) {
  return CreateStringWithBytes(bytes.Slice(sizeof(uint64_t), bytes.Size()));
}
Bytes DeserializeBytes(const Bytes& bytes) {
  return bytes.Slice(sizeof(uint64_t), bytes.Size());
}
Bytes Serialize(const Decimal& value) {
  if (value.IsZero()) {
    return Bytes();
  }
  Index size = value.Data().Size();
  List<Byte> bytes(size + sizeof(uint64_t) + 1);
  Bytes result(bytes);
  result.Concat(Serialize(size));
  result.Push(value.Sign() ? '-' : '+');
  auto data = value.Data();
  for (Index i = 0; i < data.Size(); i++) {
    result.Push(DecToByte(data.Get(i)));
  }
  return result;
}
Decimal DeserializeDecimal(const Bytes& bytes) {
  if (bytes.Size() == 0) {
    return CreateDecimalZero();
  }
  Index i = 0;
  Index size = DeserializeU64(bytes.Slice(i, i + sizeof(uint64_t)));
  i += sizeof(uint64_t);
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
  Index size = value.Data().Size();
  List<Byte> bytes(size * 2 + sizeof(uint64_t) + 1);
  Bytes result(bytes);
  result.Concat(Serialize(size));
  result.Push(value.Sign() ? '-' : '+');
  auto data = value.Data();
  for (Index i = 0; i < size; i++) {
    result.Concat(Serialize(static_cast<uint16_t>(data.Get(i) & 0x0000FFFF)));
  }
  return result;
}
Integer DeserializeInteger(const Bytes& bytes) {
  if (bytes.Size() == 0) {
    return CreateIntegerZero();
  }
  Index i = 0;
  Index size = DeserializeU64(bytes.Slice(i, i + sizeof(uint64_t)));
  i += sizeof(uint64_t);
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
  List<uint32_t> data;
  for (Index j = 0; j < size; j++) {
    data.Push(DeserializeU16(
      bytes.Slice(i + j * sizeof(uint16_t), i + (j + 1) * sizeof(uint16_t))
    ));
  }
  return Integer(data, sign);
}
}  // namespace torchlight::Collections