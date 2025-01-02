#ifndef TORCHLIGHT_RUNTIME_SERIALIZE_H
#define TORCHLIGHT_RUNTIME_SERIALIZE_H

#include "object/PyCode.h"
#include "object/PyFloat.h"
#include "object/common.h"
namespace torchlight::runtime {

double ReadDouble(collections::List<collections::Byte>::Iterator& byteIter);
uint64_t ReadU64(collections::List<collections::Byte>::Iterator& byteIter);
int64_t ReadI64(collections::List<collections::Byte>::Iterator& byteIter);
uint32_t ReadU32(collections::List<collections::Byte>::Iterator& byteIter);
uint16_t ReadU16(collections::List<collections::Byte>::Iterator& byteIter);
uint8_t ReadU8(collections::List<collections::Byte>::Iterator& byteIter);

object::PyStrPtr ReadString(
  collections::List<collections::Byte>::Iterator& byteIter
);
object::PyIntPtr ReadInteger(
  collections::List<collections::Byte>::Iterator& byteIter
);
object::PyFloatPtr ReadFloat(
  collections::List<collections::Byte>::Iterator& byteIter
);
object::PyListPtr ReadList(
  collections::List<collections::Byte>::Iterator& byteIter
);
object::PyCodePtr ReadCode(
  collections::List<collections::Byte>::Iterator& byteIter
);
object::PyObjPtr ReadObject(
  collections::List<collections::Byte>::Iterator& byteIter
);
object::PyBytesPtr ReadBytes(
  collections::List<collections::Byte>::Iterator& byteIter
);

object::PyCodePtr MakeCode(const object::PyBytesPtr& bytes);

}  // namespace torchlight::runtime

#endif