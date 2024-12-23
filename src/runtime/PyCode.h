#ifndef TORCHLIGHT_RUNTIME_PYCODE_H
#define TORCHLIGHT_RUNTIME_PYCODE_H

#include "bytecode/ByteCode.h"
#include "object/Klass.h"
#include "object/PyBytes.h"
#include "object/common.h"

namespace torchlight::runtime {

using collections::Bytes;

class PyCode : public object::PyObject {
 private:
  bytecode::InstStream instructions;

  static size_t ReadSize(
    collections::List<collections::Byte>::Iterator& byteIter
  );
  static double ReadDouble(
    collections::List<collections::Byte>::Iterator& byteIter
  );
  static Bytes ReadString(
    collections::List<collections::Byte>::Iterator& byteIter
  );

  static uint32_t ReadU32(
    collections::List<collections::Byte>::Iterator& byteIter
  );

  static uint8_t ReadU8(collections::List<collections::Byte>::Iterator& byteIter
  );

  void ReadCode(object::PyBytesPtr byteCodes);

 public:
  explicit PyCode(object::PyBytesPtr byteCodes);

  [[nodiscard]] bytecode::InstStream& Instructions();
};

using PyCodePtr = std::shared_ptr<PyCode>;

class CodeKlass : public object::Klass {
 public:
  explicit CodeKlass();
  static object::KlassPtr Self();
};

}  // namespace torchlight::runtime

#endif  // TORCHLIGHT_RUNTIME_PYCODE_H
