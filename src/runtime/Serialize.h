#ifndef TORCHLIGHT_RUNTIME_SERIALIZE_H
#define TORCHLIGHT_RUNTIME_SERIALIZE_H

#include "collections/Integer.h"
#include "object/PyCode.h"
#include "object/PyFloat.h"
namespace torchlight::runtime {

using collections::Byte;
using collections::Integer;
using collections::List;
using collections::String;
using object::PyBytesPtr;
using object::PyCodePtr;
using object::PyFloatPtr;
using object::PyIntPtr;
using object::PyListPtr;
using object::PyObjPtr;
using object::PyStrPtr;

double ReadDouble(List<Byte>::Iterator& byteIter);
uint64_t ReadU64(List<Byte>::Iterator& byteIter);
int64_t ReadI64(List<Byte>::Iterator& byteIter);
uint32_t ReadU32(List<Byte>::Iterator& byteIter);
uint16_t ReadU16(List<Byte>::Iterator& byteIter);
uint8_t ReadU8(List<Byte>::Iterator& byteIter);

PyStrPtr ReadString(List<Byte>::Iterator& byteIter);
PyIntPtr ReadInteger(List<Byte>::Iterator& byteIter);
PyFloatPtr ReadFloat(List<Byte>::Iterator& byteIter);
PyListPtr ReadList(List<Byte>::Iterator& byteIter);
PyObjPtr ReadObject(List<Byte>::Iterator& byteIter);

PyCodePtr MakeCode(const PyBytesPtr& bytes);

}  // namespace torchlight::runtime

#endif