#ifndef TORCHLIGHT_RUNTIME_PYFRAME_H
#define TORCHLIGHT_RUNTIME_PYFRAME_H

#include "ByteCode/PyCode.h"
#include "ByteCode/PyInst.h"
#include "Collections/Stack.h"
#include "Object/Klass.h"
#include "Object/PyDictionary.h"
#include "Object/PyList.h"
#include "Object/PyObject.h"

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
  bool isParsed = false;

 public:
  explicit PyFrame(
    const Object::PyCodePtr& _code,
    const Object::PyObjPtr& _locals,      // 传入的是 PyObjPtr
    const Object::PyObjPtr& _globals,     // 传入的是 PyObjPtr
    const Object::PyObjPtr& _fastLocals,  // 传入的是 PyObjPtr
    const Object::PyObjPtr& _caller
  );

  void SetProgramCounter(Index _pc);

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
  const Object::PyObjPtr& _function,
  const Object::PyObjPtr& _arguments,
  Object::PyObjPtr caller
);

class FrameKlass : public Object::Klass {
 public:
  explicit FrameKlass();
  static Object::KlassPtr Self();

  Object::PyObjPtr repr(const Object::PyObjPtr& obj) override;

  void Initialize() override;
};

void ParseByteCode(const Object::PyCodePtr& code);

}  // namespace torchlight::Runtime

#endif