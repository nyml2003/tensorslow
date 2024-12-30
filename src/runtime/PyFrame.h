#ifndef TORCHLIGHT_RUNTIME_PYFRAME_H
#define TORCHLIGHT_RUNTIME_PYFRAME_H

#include "collections/Map.h"
#include "collections/Stack.h"
#include "collections/common.h"
#include "object/Klass.h"
#include "object/PyCode.h"
#include "object/PyInst.h"
#include "object/PyObject.h"
#include "object/common.h"

namespace torchlight::runtime {
using collections::Index;
using collections::Map;
using collections::Stack;
using collections::String;
using object::Klass;
using object::PyCodePtr;
using object::PyDictPtr;
using object::PyInstPtr;
using object::PyObject;
using object::PyObjPtr;
class PyFrame : public PyObject {
 private:
  Stack<PyObjPtr> stack;
  PyCodePtr code;
  Index programCounter = 0;
  PyDictPtr locals;
  PyDictPtr globals;
  PyDictPtr fastLocals;

 public:
  explicit PyFrame(PyCodePtr code);

  void SetProgramCounter(Index pc);

  [[nodiscard]] PyCodePtr Code() const;

  [[nodiscard]] Index ProgramCounter() const;

  [[nodiscard]] PyDictPtr Locals() const;

  [[nodiscard]] PyDictPtr Globals() const;

  [[nodiscard]] PyDictPtr FastLocals() const;

  [[nodiscard]] Stack<PyObjPtr>& Stack();

  PyInstPtr Instruction() const;

  bool Finished() const;

  void NextProgramCounter();
};

using PyFramePtr = std::shared_ptr<PyFrame>;

class FrameKlass : public object::Klass {
 public:
  explicit FrameKlass();
  static object::KlassPtr Self();
};

void ParseByteCode(const PyCodePtr& code);

}  // namespace torchlight::runtime

#endif