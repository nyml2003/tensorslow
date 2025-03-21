#ifndef TORCHLIGHT_RUNTIME_SERIALIZE_H
#define TORCHLIGHT_RUNTIME_SERIALIZE_H

#include "Collections/Iterator.h"
#include "Object/Runtime/PyCode.h"

namespace torchlight::Runtime {
Collections::Bytes ReadBytes(
  Collections::Iterator<Byte>& byteIter,
  uint64_t size
);  // 读取指定大小的字节
double ReadDouble(Collections::Iterator<Byte>& byteIter);
uint64_t ReadU64(Collections::Iterator<Byte>& byteIter
);  // 读取一个64位无符号整数, 会移动迭代器
uint64_t ReadSize(Collections::Iterator<Byte>& byteIter
);  // 读取一个64位无符号整数, 不会移动迭代器
int64_t ReadI64(Collections::Iterator<Byte>& byteIter);
uint32_t ReadU32(Collections::Iterator<Byte>& byteIter);
uint16_t ReadU16(Collections::Iterator<Byte>& byteIter);
uint8_t ReadU8(Collections::Iterator<Byte>& byteIter);
Object::PyObjPtr ReadString(Collections::Iterator<Byte>& byteIter);
Object::PyObjPtr ReadInteger(Collections::Iterator<Byte>& byteIter);
Object::PyObjPtr ReadFloat(Collections::Iterator<Byte>& byteIter);
Object::PyObjPtr ReadList(Collections::Iterator<Byte>& byteIter);
Object::PyObjPtr ReadCode(Collections::Iterator<Byte>& byteIter);
Object::PyObjPtr ReadObject(Collections::Iterator<Byte>& byteIter);
Object::PyObjPtr ReadBytes(Collections::Iterator<Byte>& byteIter);
Object::PyCodePtr MakeCode(const Object::PyObjPtr& byteCode);
}  // namespace torchlight::Runtime

#endif