#ifndef TORCHLIGHT_RUNTIME_PYFRAME_H
#define TORCHLIGHT_RUNTIME_PYFRAME_H

#include "ByteCode/PyCode.h"
#include "ByteCode/PyInst.h"
#include "Collections/Stack.h"
#include "Function/PyFunction.h"
#include "Object/Klass.h"
#include "Object/Object.h"
#include "Object/PyDictionary.h"
#include "Object/PyList.h"
#include "Object/PyObject.h"

namespace torchlight::Runtime {
class PyFrame;
using PyFramePtr = std::shared_ptr<PyFrame>;

class PyFrame : public Object::PyObject {
 private:
  Collections::Stack<Object::PyObjPtr> stack;
  Index programCounter;

  Object::PyCodePtr code;
  Object::PyDictPtr locals;
  Object::PyDictPtr globals;
  Object::PyListPtr fastLocals;
  PyFramePtr caller;
  bool isParsed = false;

 public:
  explicit PyFrame(
    Object::PyCodePtr code,
    Object::PyDictPtr locals,      // 传入的是 PyObjPtr
    Object::PyDictPtr globals,     // 传入的是 PyObjPtr
    Object::PyListPtr fastLocals,  // 传入的是 PyObjPtr
    PyFramePtr caller
  );

  void SetProgramCounter(Index _pc);

  [[nodiscard]] Object::PyCodePtr Code() const;

  [[nodiscard]] Index ProgramCounter() const;

  [[nodiscard]] PyFramePtr Caller() const;

  [[nodiscard]] Object::PyInstPtr Instruction() const;

  Object::PyListPtr CurrentStack() const;

  Object::PyObjPtr StackTop() const { return stack.Top(); }

  Object::PyDictPtr CurrentLocals() const;

  Object::PyDictPtr CurrentGlobals() const;

  Object::PyListPtr CurrentFastLocals() const;

  bool Finished() const;

  void NextProgramCounter();

  bool HasCaller() const;

  [[nodiscard]] Object::PyObjPtr Eval();

  [[nodiscard]] Object::PyObjPtr EvalWithDestory();
};

using PyFramePtr = std::shared_ptr<PyFrame>;

PyFramePtr CreateModuleEntryFrame(const Object::PyCodePtr& code);

PyFramePtr CreateFrameWithPyFunction(
  const Object::PyFunctionPtr& function,
  const Object::PyListPtr& arguments
);

class FrameKlass : public Object::Klass {
 public:
  explicit FrameKlass() = default;
  static Object::KlassPtr Self() {
    static Object::KlassPtr instance = std::make_shared<FrameKlass>();
    LoadClass(
      Object::CreatePyString("frame")->as<Object::PyString>(), instance
    );
    ConfigureBasicAttributes(instance);
    return instance;
  }

  Object::PyObjPtr repr(const Object::PyObjPtr& obj) override;
};

void ParseByteCode(const Object::PyCodePtr& code);
void PrintFrame(const PyFramePtr& frame);
inline PyFramePtr CreatePyFrame(
  const Object::PyCodePtr& code,
  const Object::PyDictPtr& locals,
  const Object::PyDictPtr& globals,
  const Object::PyListPtr& fastLocals,
  const PyFramePtr& caller
) {
  return std::make_shared<PyFrame>(code, locals, globals, fastLocals, caller);
}
}  // namespace torchlight::Runtime

#endif