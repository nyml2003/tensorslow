#include "ByteCode/ByteCode.h"
#include "Collections/Bytes.h"
#include "Collections/BytesHelper.h"
#include "Collections/List.h"
#include "Collections/StringHelper.h"
#include "Object/PyBoolean.h"
#include "Object/PyBytes.h"
#include "Object/PyInteger.h"
#include "Object/PyList.h"
#include "Object/PyNone.h"
#include "Object/PyString.h"
#include "Runtime/Serialize.h"

#include <cstring>
namespace torchlight::Runtime {

Collections::Bytes
ReadBytes(Collections::Iterator<Byte>& byteIter, uint64_t size) {
  return Collections::Bytes(byteIter.Advance(size));
}

double ReadDouble(Collections::Iterator<Byte>& byteIter) {
  return Collections::DeserializeDouble(
    Collections::Bytes(byteIter.Advance(sizeof(double)))
  );
}
uint64_t ReadU64(Collections::Iterator<Byte>& byteIter) {
  return Collections::DeserializeU64(
    Collections::Bytes(byteIter.Advance(sizeof(uint64_t)))
  );
}

uint64_t ReadSize(Collections::Iterator<Byte>& byteIter) {
  return Collections::DeserializeU64(
    Collections::Bytes(byteIter.Preview(sizeof(uint64_t)))
  );
}

int64_t ReadI64(Collections::Iterator<Byte>& byteIter) {
  return Collections::DeserializeI64(
    Collections::Bytes(byteIter.Advance(sizeof(int64_t)))
  );
}
uint32_t ReadU32(Collections::Iterator<Byte>& byteIter) {
  return Collections::DeserializeU32(
    Collections::Bytes(byteIter.Advance(sizeof(uint32_t)))
  );
}
uint16_t ReadU16(Collections::Iterator<Byte>& byteIter) {
  return Collections::DeserializeU16(
    Collections::Bytes(byteIter.Advance(sizeof(uint16_t)))
  );
}
uint8_t ReadU8(Collections::Iterator<Byte>& byteIter) {
  auto result = byteIter.Get();
  byteIter.Next();
  return result;
}

Object::PyObjPtr ReadString(Collections::Iterator<Byte>& byteIter) {
  auto size = ReadU64(byteIter);
  return Object::CreatePyString(
    Collections::CreateStringWithBytes(ReadBytes(byteIter, size))
  );
}

Object::PyObjPtr ReadBytes(Collections::Iterator<Byte>& byteIter) {
  uint64_t size = ReadU64(byteIter);
  return Object::CreatePyBytes(Collections::Bytes(ReadBytes(byteIter, size)));
}

Object::PyObjPtr ReadInteger(Collections::Iterator<Byte>& byteIter) {
  uint64_t size = ReadSize(byteIter);
  auto bytes = ReadBytes(byteIter, size * 2 + sizeof(uint64_t) + 1);
  return Object::CreatePyInteger(Collections::DeserializeInteger(bytes));
}
Object::PyObjPtr ReadFloat(Collections::Iterator<Byte>& byteIter) {
  return Object::CreatePyFloat(ReadDouble(byteIter));
}
Object::PyObjPtr ReadList(Collections::Iterator<Byte>& byteIter) {
  uint64_t size = ReadU64(byteIter);
  if (size == 0) {
    return Object::CreatePyList(0);
  }
  Collections::List<Object::PyObjPtr> result(size);
  for (uint64_t i = 0; i < size; i++) {
    auto obj = ReadObject(byteIter);
    result.Push(obj);
  }
  return Object::CreatePyList(result);
}

Object::PyObjPtr ReadObject(Collections::Iterator<Byte>& byteIter) {
  Byte type = byteIter.Get();
  byteIter.Next();
  auto e = static_cast<Object::Literal>(type);
  switch (e) {
    case Object::Literal::STRING:
      return ReadString(byteIter);
    case Object::Literal::INTEGER:
      return ReadInteger(byteIter);
    case Object::Literal::FLOAT:
      return ReadFloat(byteIter);
    case Object::Literal::LIST:
      return ReadList(byteIter);
    case Object::Literal::TRUE:
      return Object::CreatePyBoolean(true);
    case Object::Literal::FALSE:
      return Object::CreatePyBoolean(false);
    case Object::Literal::NONE:
      return Object::CreatePyNone();
    case Object::Literal::ZERO:
      return Object::CreatePyInteger(0);
    case Object::Literal::CODE:
      return ReadCode(byteIter);
    case Object::Literal::BYTES:
      return ReadBytes(byteIter);
  }
  throw std::runtime_error("Unknown type");
}

Object::PyObjPtr ReadCode(Collections::Iterator<Byte>& byteIter) {
  auto consts = ReadObject(byteIter);
  auto names = ReadObject(byteIter);
  auto varNames = ReadObject(byteIter);
  auto name = ReadObject(byteIter);
  auto nLocals = ReadU64(byteIter);
  auto byteCode = ReadObject(byteIter);
  return std::make_shared<Object::PyCode>(
    byteCode, consts, names, varNames, name, nLocals
  );
}

Object::PyCodePtr MakeCode(const Object::PyObjPtr& byteCode) {
  if (byteCode->Klass() != Object::BytesKlass::Self()) {
    throw std::runtime_error("Invalid byte code");
  }
  auto bytes = std::dynamic_pointer_cast<Object::PyBytes>(byteCode)->Value().Value();
  Collections::Iterator<Byte> byteIter =
    Collections::Iterator<Byte>::Begin(bytes);
  auto obj = ReadObject(byteIter);
  return std::dynamic_pointer_cast<Object::PyCode>(obj);
}
}  // namespace torchlight::Runtime
