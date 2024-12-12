#ifndef TORCHLIGHT_RUNTIME_PYFRAME_H
#define TORCHLIGHT_RUNTIME_PYFRAME_H

#include <memory>
#include "collections/Stack.h"
#include "collections/common.h"
#include "object/Klass.h"
#include "object/PyObject.h"
#include "runtime/PyCode.h"

namespace torchlight::runtime {
class PyFrame : public object::PyObject {
 private:
  collections::Stack<object::PyObjPtr> stack;
  PyCodePtr code;

 public:
  explicit PyFrame(PyCodePtr code);
  void Run();
  size_t ReadSize(collections::List<collections::Byte>::Iterator& byteIter);
  collections::Integer ReadInt(
    collections::List<collections::Byte>::Iterator& byteIter
  );
  double ReadDouble(collections::List<collections::Byte>::Iterator& byteIter);
  collections::String ReadString(
    collections::List<collections::Byte>::Iterator& byteIter
  );
};

using PyFramePtr = std::shared_ptr<PyFrame>;

class FrameKlass : public object::Klass {
 public:
  explicit FrameKlass();
  static object::KlassPtr Self();
};

}  // namespace torchlight::runtime

#endif