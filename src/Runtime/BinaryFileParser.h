#ifndef TORCHLIGHT_RUNTIME_BINARY_FILEPARSER_H
#define TORCHLIGHT_RUNTIME_BINARY_FILEPARSER_H

#include <filesystem>
#include <fstream>
#include "Collections/String/BytesHelper.h"
#include "Collections/String/StringHelper.h"
#include "Object/Core/PyBoolean.h"
#include "Object/Core/PyNone.h"
#include "Object/Number/PyFloat.h"
#include "Object/Number/PyInteger.h"
#include "Object/Runtime/PyCode.h"
#include "Object/String/PyBytes.h"

namespace torchlight::Runtime {
namespace fs = std::filesystem;

class BinaryFileParser {
 public:
  explicit BinaryFileParser(const fs::path& filename) {
    fileStream.open(filename, std::ios::binary);
    if (!fileStream.is_open()) {
      throw std::runtime_error("Failed to open file: " + filename.string());
    }
  }

  Object::PyCodePtr Parse() {
    return ReadObject()->as<Object::PyCode>();
    fileStream.close();
  }

 private:
  std::ifstream fileStream;
  uint64_t ReadSize() {
    std::streampos originalPosition = fileStream.tellg();
    uint64_t size;
    fileStream.read(reinterpret_cast<char*>(&size), sizeof(size));
    fileStream.seekg(originalPosition);
    return size;
  }
  double ReadDouble() {
    double value;
    fileStream.read(reinterpret_cast<char*>(&value), sizeof(value));
    return value;
  }
  int64_t ReadI64() {
    int64_t value;
    fileStream.read(reinterpret_cast<char*>(&value), sizeof(value));
    return value;
  }
  uint64_t ReadU64() {
    uint64_t value;
    fileStream.read(reinterpret_cast<char*>(&value), sizeof(value));
    return value;
  }
  Object::PyStrPtr ReadString() {
    uint64_t size = ReadU64();
    auto buffer = std::make_unique<char[]>(size + 1);
    fileStream.read(reinterpret_cast<char*>(buffer.get()), size);
    return Object::CreatePyString(
      Collections::CreateStringWithCString(buffer.get())
    );
  }
  Collections::List<Byte> ReadBytes(uint64_t size) {
    auto buffer = std::make_unique<unsigned char[]>(size);
    fileStream.read(reinterpret_cast<char*>(buffer.get()), size);
    return Collections::List<Byte>(size, std::move(buffer));
  }
  Object::PyBytesPtr ReadBytes() {
    return Object::CreatePyBytes(Collections::String(ReadBytes(ReadU64())));
  }
  Object::PyIntPtr ReadInteger() {
    uint64_t size = ReadSize();
    return Object::CreatePyInteger(Collections::DeserializeInteger(
      ReadBytes(size * 2 + sizeof(uint64_t) + 1)
    ));
  }
  Object::PyFloatPtr ReadFloat() { return Object::CreatePyFloat(ReadDouble()); }
  Object::PyListPtr ReadList() {
    uint64_t size = ReadU64();
    if (size == 0) {
      return Object::CreatePyList(0);
    }
    Collections::List<Object::PyObjPtr> list(size);
    for (uint64_t i = 0; i < size; ++i) {
      auto obj = ReadObject();
      list.Push(obj);
    }
    return Object::CreatePyList(std::move(list));
  }
  uint8_t ReadU8() {
    uint8_t value;
    fileStream.read(reinterpret_cast<char*>(&value), sizeof(value));
    return value;
  }
  Object::PyObjPtr ReadObject() {
    Byte type = ReadU8();
    auto e = static_cast<Object::Literal>(type);
    switch (e) {
      case Object::Literal::STRING:
        return ReadString();
      case Object::Literal::INTEGER:
        return ReadInteger();
      case Object::Literal::FLOAT:
        return ReadFloat();
      case Object::Literal::LIST:
        return ReadList();
      case Object::Literal::TRUE:
        return Object::CreatePyBoolean(true);
      case Object::Literal::FALSE:
        return Object::CreatePyBoolean(false);
      case Object::Literal::NONE:
        return Object::CreatePyNone();
      case Object::Literal::ZERO:
        return Object::CreatePyInteger(0);
      case Object::Literal::CODE:
        return ReadCode();
      case Object::Literal::BYTES:
        return ReadBytes();
    }
    throw std::runtime_error("Unknown object type");
  }
  Object::PyCodePtr ReadCode() {
    auto consts = ReadObject()->as<Object::PyList>();
    auto names = ReadObject()->as<Object::PyList>();
    auto varNames = ReadObject()->as<Object::PyList>();
    auto name = ReadObject()->as<Object::PyString>();
    auto nLocals = ReadU64();
    auto byteCode = ReadObject()->as<Object::PyBytes>();
    return std::make_shared<Object::PyCode>(
      byteCode, consts, names, varNames, name, nLocals
    );
  }
};
}  // namespace torchlight::Runtime

#endif  // TORCHLIGHT_RUNTIME_BINARY_FILEPARSER_H
