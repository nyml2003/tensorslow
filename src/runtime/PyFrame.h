#ifndef TORCHLIGHT_RUNTIME_PYFRAME_H
#define TORCHLIGHT_RUNTIME_PYFRAME_H

#include "collections/Stack.h"
#include "collections/common.h"
#include "object/Klass.h"
#include "object/PyCode.h"
#include "object/PyDictionary.h"
#include "object/PyInst.h"
#include "object/PyObject.h"
#include "object/common.h"
#include "runtime/PyFunction.h"

namespace torchlight::runtime {
class PyFrame : public object::PyObject {
 private:
  collections::Stack<object::PyObjPtr> stack;
  object::PyCodePtr code;
  collections::Index programCounter = 0;
  object::PyDictPtr locals;
  object::PyDictPtr globals;
  object::PyListPtr fastLocals;
  object::PyObjPtr caller;

 public:
  explicit PyFrame(object::PyCodePtr code);

  explicit PyFrame(
    const PyFunctionPtr& function,
    const collections::List<object::PyObjPtr>& arguments,
    object::PyObjPtr caller
  );

  void SetProgramCounter(collections::Index pc);

  [[nodiscard]] object::PyCodePtr Code() const;

  [[nodiscard]] collections::Index ProgramCounter() const;

  [[nodiscard]] object::PyDictPtr& Locals();

  [[nodiscard]] object::PyDictPtr& Globals();

  [[nodiscard]] object::PyListPtr& FastLocals();

  [[nodiscard]] collections::Stack<object::PyObjPtr>& Stack();

  [[nodiscard]] object::PyObjPtr Caller() const;

  [[nodiscard]] object::PyInstPtr Instruction() const;

  bool Finished() const;

  void NextProgramCounter();

  bool HasCaller() const;
};

using PyFramePtr = std::shared_ptr<PyFrame>;

class FrameKlass : public object::Klass {
 public:
  explicit FrameKlass();
  static object::KlassPtr Self();
};

void ParseByteCode(const object::PyCodePtr& code);

}  // namespace torchlight::runtime

#endif