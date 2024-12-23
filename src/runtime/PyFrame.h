#ifndef TORCHLIGHT_RUNTIME_PYFRAME_H
#define TORCHLIGHT_RUNTIME_PYFRAME_H

#include <memory>
#include "collections/Stack.h"
#include "collections/common.h"
#include "object/Klass.h"
#include "object/PyObject.h"
#include "runtime/PyCode.h"

namespace torchlight::runtime {
using collections::Index;
using collections::String;
class PyFrame : public object::PyObject {
 private:
  collections::Stack<object::PyObjPtr> stack;
  PyCodePtr code;
  Index programCounter = 0;

 public:
  explicit PyFrame(PyCodePtr code);
  void Run();
};

using PyFramePtr = std::shared_ptr<PyFrame>;

class FrameKlass : public object::Klass {
 public:
  explicit FrameKlass();
  static object::KlassPtr Self();
};

}  // namespace torchlight::runtime

#endif