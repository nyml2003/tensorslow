#ifndef TORCHLIGHT_RUNTIME_PYFRAME_H
#define TORCHLIGHT_RUNTIME_PYFRAME_H

#include "Collections/Stack.h"
#include "Object/Klass.h"
#include "Object/PyCode.h"
#include "Object/PyDictionary.h"
#include "Object/PyInst.h"
#include "Object/PyObject.h"
#include "Runtime/PyFunction.h"

namespace torchlight::Runtime {
class PyFrame : public Object::PyObject {
 private:
  Collections::Stack<Object::PyObjPtr> stack;
  Index programCounter;

  Object::PyCodePtr code;
  Object::PyDictPtr locals;
  Object::PyDictPtr globals;
  Object::PyListPtr fastLocals;
  Object::PyObjPtr caller;

 public:
  explicit PyFrame(
    Object::PyCodePtr code,
    Object::PyDictPtr locals,
    Object::PyDictPtr globals,
    Object::PyListPtr fastLocals,
    Object::PyObjPtr caller
  );

  void SetProgramCounter(Index pc);

  [[nodiscard]] Object::PyCodePtr Code() const;

  [[nodiscard]] Index ProgramCounter() const;

  [[nodiscard]] Object::PyDictPtr& Locals();

  [[nodiscard]] Object::PyDictPtr& Globals();

  [[nodiscard]] Object::PyListPtr& FastLocals();

  [[nodiscard]] Collections::Stack<Object::PyObjPtr>& Stack();

  [[nodiscard]] Object::PyObjPtr Caller() const;

  [[nodiscard]] Object::PyInstPtr Instruction() const;

  bool Finished() const;

  void NextProgramCounter();

  bool HasCaller() const;
};

using PyFramePtr = std::shared_ptr<PyFrame>;

PyFramePtr CreateFrameWithCode(const Object::PyCodePtr& code);

PyFramePtr CreateFrameWithFunction(
  const PyFunctionPtr& function,
  const Collections::List<Object::PyObjPtr>& arguments,
  Object::PyObjPtr caller
);

class FrameKlass : public Object::Klass {
 public:
  explicit FrameKlass();
  static Object::KlassPtr Self();

  Object::PyObjPtr repr(Object::PyObjPtr obj) override;
};

void ParseByteCode(const Object::PyCodePtr& code);

}  // namespace torchlight::Runtime

#endif