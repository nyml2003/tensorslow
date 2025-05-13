#include "Collections/String/BytesHelper.h"
#include "Collections/Integer/DecimalHelper.h"
#include "Collections/Integer/IntegerHelper.h"
#include "Collections/String/StringHelper.h"
#include "Tools/Logger/ConsoleLogger.h"
#include "Tools/Logger/ErrorLogger.h"

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

void Write(const String& bytes, const std::string& filename) {
  std::string data = bytes.ToCppString();
  if (filename.empty()) {
    throw std::runtime_error("Filename is empty");
  }
  std::ofstream file(filename, std::ios::binary);
  if (!file.is_open()) {
    tensorslow::ErrorLogger::getInstance().log("无法打开文件：" + filename);
    return;
  }
  file.write(data.data(), std::streamsize(data.size()));
  tensorslow::ConsoleLogger::getInstance().log("写入文件：");
  tensorslow::ConsoleLogger::getInstance().log(filename);
  tensorslow::ConsoleLogger::getInstance().log("\n");
  tensorslow::ConsoleLogger::getInstance().log("文件大小：");
  tensorslow::ConsoleLogger::getInstance().log(std::to_string(data.size()));
  tensorslow::ConsoleLogger::getInstance().log("字节");
  tensorslow::ConsoleLogger::getInstance().log("\n");
  if (!file) {
    tensorslow::ErrorLogger::getInstance().log("写入文件时出错：" + filename);
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
int64_t DeserializeI64(const List<Byte>& bytes, Index& offset) {
  return static_cast<int64_t>(DeserializeU64(bytes, offset));
}
uint16_t DeserializeU16(const List<Byte>& bytes) {
  if (bytes.Size() != sizeof(uint16_t)) {
    throw std::runtime_error("Invalid byte size for uint16_t");
  }
  return *reinterpret_cast<const uint16_t*>(bytes.Data());
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
  bool sign;
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