#include "Collections/String/BytesHelper.h"
#include "Collections/Integer/DecimalHelper.h"
#include "Collections/Integer/IntegerHelper.h"
#include "Collections/String/StringHelper.h"

#include <cstring>
#include <fstream>
#include <iostream>
#include <stdexcept>
namespace tensorslow::Collections {
String ReprByte(Byte byte) {
  // 使用 \x 格式表示一个字节
  char buffer[5];  // 需要 5 个字符：\x + 2 个十六进制字符 + 终止符
  std::snprintf(buffer, sizeof(buffer), "\\x%02X", byte);
  return CreateStringWithCString(buffer);
}
String CreateBytesWithCString(const char* str) {
  Byte* data = reinterpret_cast<Byte*>(const_cast<char*>(str));
  return String(List<Byte>(static_cast<Index>(std::strlen(str)), data));
}
void Write(const String& bytes, const String& filename) {
  std::string data = bytes.ToCppString();
  std::string filenameCppString = filename.ToCppString();
  if (filenameCppString.empty()) {
    throw std::runtime_error("Filename is empty");
  }
  std::ofstream file(filenameCppString, std::ios::binary);
  if (!file.is_open()) {
    std::cerr << "无法打开文件：" << filenameCppString << std::endl;
    return;
  }
  file.write(data.data(), data.size());
  std::cout << "写入文件：" << filenameCppString << std::endl;
  std::cout << "文件大小：" << data.size() << " 字节" << std::endl;
  if (!file) {
    std::cerr << "写入文件时出错：" << filenameCppString << std::endl;
  }
  file.close();
}

String Serialize(double value) {
  return String(List<Byte>(sizeof(double), reinterpret_cast<Byte*>(&value)));
}
String Serialize(uint64_t value) {
  return String(List<Byte>(sizeof(uint64_t), reinterpret_cast<Byte*>(&value)));
}
String Serialize(int64_t value) {
  return Serialize(static_cast<uint64_t>(value));
}
String Serialize(uint32_t value) {
  return String(List<Byte>(sizeof(uint32_t), reinterpret_cast<Byte*>(&value)));
}
String Serialize(uint16_t value) {
  return String(List<Byte>(sizeof(uint16_t), reinterpret_cast<Byte*>(&value)));
}
String Serialize(int32_t value) {
  return String(List<Byte>(sizeof(int32_t), reinterpret_cast<Byte*>(&value)));
}
String Serialize(const String& value) {
  StringBuilder bytesWithSize(Serialize(value.GetCodeUnitCount()));
  bytesWithSize.Append(value);
  return bytesWithSize.ToString();
}
double DeserializeDouble(const List<Byte>& bytes) {
  if (bytes.Size() != sizeof(double)) {
    throw std::runtime_error("Invalid byte size for double");
  }
  return *reinterpret_cast<const double*>(bytes.Data());
}
uint64_t DeserializeU64(const List<Byte>& bytes) {
  if (bytes.Size() != sizeof(uint64_t)) {
    throw std::runtime_error("Invalid byte size for uint64_t");
  }
  return *reinterpret_cast<const uint64_t*>(bytes.Data());
}
uint64_t DeserializeU64(const List<Byte>& bytes, Index& offset) {
  uint64_t value = *reinterpret_cast<const uint64_t*>(bytes.Data() + offset);
  offset += sizeof(uint64_t);
  return value;
}
int64_t DeserializeI64(const List<Byte>& bytes) {
  return static_cast<int64_t>(DeserializeU64(bytes));
}
int64_t DeserializeI64(const List<Byte>& bytes, Index& offset) {
  return static_cast<int64_t>(DeserializeU64(bytes, offset));
}
uint32_t DeserializeU32(const List<Byte>& bytes) {
  if (bytes.Size() != sizeof(uint32_t)) {
    throw std::runtime_error("Invalid byte size for uint32_t");
  }
  return *reinterpret_cast<const uint32_t*>(bytes.Data());
}
int32_t DeserializeI32(const List<Byte>& bytes) {
  return static_cast<int32_t>(DeserializeU32(bytes));
}
uint16_t DeserializeU16(const List<Byte>& bytes) {
  if (bytes.Size() != sizeof(uint16_t)) {
    throw std::runtime_error("Invalid byte size for uint16_t");
  }
  return *reinterpret_cast<const uint16_t*>(bytes.Data());
}
String DeserializeString(const List<Byte>& bytes) {
  return String(bytes.Slice(sizeof(uint64_t), bytes.Size()));
}
String Serialize(const Decimal& value) {
  if (value.IsZero()) {
    return CreateStringWithCString("");
  }
  Index size = value.Data().Size();
  List<Byte> bytes(size + sizeof(uint64_t) + 1);
  StringBuilder result(String(std::move(bytes)));
  result.Append(Serialize(size));
  result.Append(value.Sign() ? '-' : '+');
  auto data = value.Data();
  for (Index i = 0; i < data.Size(); i++) {
    result.Append(DecToByte(data.Get(i)));
  }
  return result.ToString();
}
Decimal DeserializeDecimal(const List<Byte>& bytes) {
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
    data.Push(ByteToDec(bytes.Get(i + j)));
  }
  return Decimal(data, sign);
}
String Serialize(const Integer& value) {
  if (value.IsZero()) {
    return CreateStringWithCString("");
  }
  Index size = value.Data().Size();
  List<Byte> bytes(size * 2 + sizeof(uint64_t) + 1);
  StringBuilder result(String(std::move(bytes)));
  result.Append(Serialize(size));
  result.Append(value.Sign() ? '-' : '+');
  auto data = value.Data();
  for (Index i = 0; i < size; i++) {
    result.Append(Serialize(static_cast<uint16_t>(data.Get(i) & 0x0000FFFF)));
  }
  return result.ToString();
}
Integer DeserializeInteger(const List<Byte>& bytes) {
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
}  // namespace tensorslow::Collections