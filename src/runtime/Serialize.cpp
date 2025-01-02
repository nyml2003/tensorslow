

#include "runtime/Serialize.h"
#include "collections/Bytes.h"
#include "collections/Integer.h"
#include "collections/impl/Integer.h"
#include "collections/impl/String.h"
#include "object/ByteCode.h"
#include "object/PyBoolean.h"
#include "object/PyBytes.h"
#include "object/PyCode.h"
#include "object/PyFloat.h"
#include "object/PyInteger.h"
#include "object/PyList.h"
#include "object/PyNone.h"
#include "object/PyString.h"

#include <cstring>
#include <memory>
#include <stdexcept>
namespace torchlight::runtime {
using collections::Byte;
using collections::Bytes;
using collections::Integer;
using collections::List;
using object::Literal;
using object::PyBoolean;
using object::PyBytes;
using object::PyBytesPtr;
using object::PyCode;
using object::PyCodePtr;
using object::PyFloat;
using object::PyFloatPtr;
using object::PyInteger;
using object::PyIntPtr;
using object::PyList;
using object::PyListPtr;
using object::PyNone;
using object::PyObjPtr;
using object::PyString;
using object::PyStrPtr;

double ReadDouble(List<Byte>::Iterator& byteIter) {
  std::array<Byte, sizeof(double)> sizeBuffer{};
  for (std::size_t i = 0; i < sizeof(double); ++i) {
    sizeBuffer[i] = byteIter.Get();
    byteIter.Next();
  }
  double result = 0;
  std::memcpy(&result, sizeBuffer.data(), sizeof(double));
  return result;
}
uint64_t ReadU64(List<Byte>::Iterator& byteIter) {
  uint64_t result = 0;
  for (size_t i = 0; i < sizeof(uint64_t); ++i) {
    result |= byteIter.Get() << (i * 8);
    byteIter.Next();
  }
  return result;
}

int64_t ReadI64(List<Byte>::Iterator& byteIter) {
  int64_t result = 0;
  for (size_t i = 0; i < sizeof(int64_t); ++i) {
    result |= static_cast<int64_t>(byteIter.Get()) << (i * 8);
    byteIter.Next();
  }
  return result;
}
uint32_t ReadU32(List<Byte>::Iterator& byteIter) {
  uint32_t result = 0;
  for (size_t i = 0; i < sizeof(uint32_t); ++i) {
    result |= byteIter.Get() << (i * 8);
    byteIter.Next();
  }
  return result;
}
uint16_t ReadU16(List<Byte>::Iterator& byteIter) {
  uint16_t result = 0;
  for (size_t i = 0; i < sizeof(uint16_t); ++i) {
    result |= byteIter.Get() << (i * 8);
    byteIter.Next();
  }
  return result;
}
uint8_t ReadU8(List<Byte>::Iterator& byteIter) {
  uint8_t result = byteIter.Get();
  byteIter.Next();
  return result;
}

PyStrPtr ReadString(List<Byte>::Iterator& byteIter) {
  uint64_t size = ReadU64(byteIter);
  List<Byte> result(size);
  while (size--) {
    result.Add(byteIter.Get());
    byteIter.Next();
  }
  return std::make_shared<PyString>(
    collections::CreateStringWithBytes(Bytes(result))
  );
}

PyBytesPtr ReadBytes(List<Byte>::Iterator& byteIter) {
  uint64_t size = ReadU64(byteIter);
  List<Byte> result(size);
  while (size--) {
    result.Add(byteIter.Get());
    byteIter.Next();
  }
  return std::make_shared<PyBytes>(Bytes(result));
}

PyIntPtr ReadInteger(List<Byte>::Iterator& byteIter) {
  const char positiveSign = '+';
  const char negativeSign = '-';
  char sign = static_cast<char>(byteIter.Get());
  if (sign != positiveSign && sign != negativeSign) {
    throw std::runtime_error("Invalid integer sign");
  }
  bool isNegative = sign == negativeSign;
  byteIter.Next();
  uint64_t size = ReadU64(byteIter);
  List<uint32_t> result(size);
  while (size--) {
    result.Add(ReadU16(byteIter));
  }
  return std::make_shared<PyInteger>(Integer(result, isNegative));
}
PyFloatPtr ReadFloat(List<Byte>::Iterator& byteIter) {
  double value = ReadDouble(byteIter);
  return std::make_shared<PyFloat>(value);
}
PyListPtr ReadList(List<Byte>::Iterator& byteIter) {
  uint64_t size = ReadU64(byteIter);
  if (size == 0) {
    return std::make_shared<PyList>(List<PyObjPtr>());
  }
  List<PyObjPtr> result(size);
  while (size--) {
    result.Add(ReadObject(byteIter));
  }
  return std::make_shared<PyList>(result);
}

PyObjPtr ReadObject(List<Byte>::Iterator& byteIter) {
  Byte type = byteIter.Get();
  byteIter.Next();
  auto e = static_cast<Literal>(type);
  switch (e) {
    case Literal::STRING:
      return ReadString(byteIter);
    case Literal::INTEGER:
      return ReadInteger(byteIter);
    case Literal::FLOAT:
      return ReadFloat(byteIter);
    case Literal::LIST:
      return ReadList(byteIter);
    case Literal::TRUE:
      return PyBoolean::True();
    case Literal::FALSE:
      return PyBoolean::False();
    case Literal::NONE:
      return PyNone::Instance();
    case Literal::ZERO:
      return std::make_shared<PyInteger>(collections::CreateIntegerZero());
    case Literal::CODE:
      return ReadCode(byteIter);
    case Literal::BYTES:
      return ReadBytes(byteIter);
  }
}

PyCodePtr ReadCode(List<Byte>::Iterator& byteIter) {
  auto consts = ReadObject(byteIter);
  auto names = ReadObject(byteIter);
  auto varNames = ReadObject(byteIter);
  auto name = ReadObject(byteIter);
  auto nLocals = ReadU64(byteIter);
  auto byteCode = ReadObject(byteIter);
  return std::make_shared<PyCode>(
    byteCode, consts, names, varNames, name, nLocals
  );
}

PyCodePtr MakeCode(const PyBytesPtr& bytes) {
  auto it = List<Byte>::Iterator::Begin(bytes->Value().Value());
  auto code = ReadObject(it);
  return std::dynamic_pointer_cast<PyCode>(code);
}

}  // namespace torchlight::runtime
