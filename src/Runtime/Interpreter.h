#ifndef TORCHLIGHT_RUNTIME_INTERPRETER_H
#define TORCHLIGHT_RUNTIME_INTERPRETER_H

#include "ByteCode/PyCode.h"
#include "Function/PyMethod.h"
#include "Function/PyNativeFunction.h"
#include "Object/Object.h"
#include "Runtime/PyFrame.h"

namespace torchlight::Runtime {

class Interpreter {
 private:
  PyFramePtr frame;
  Object::PyDictPtr builtins;
  explicit Interpreter();

 public:
  static Interpreter& Instance();

  void Run(const Object::PyCodePtr& code);

  [[nodiscard]] Object::PyDictPtr Builtins() const;

  [[nodiscard]] Object::PyObjPtr EvalNativeFunction(
    const Object::PyNativeFunctionPtr& func,
    const Object::PyListPtr& arguments
  );

  [[nodiscard]] Object::PyObjPtr EvalMethod(
    const Object::PyMethodPtr& func,
    const Object::PyListPtr& arguments
  );

  [[nodiscard]] Object::PyObjPtr EvalConstructor(
    const Object::PyTypePtr& type,
    const Object::PyListPtr& arguments
  );

  [[nodiscard]] Object::PyObjPtr EvalPyFunction(
    const Object::PyFunctionPtr& func,
    const Object::PyListPtr& arguments
  );

  [[nodiscard]] Object::PyObjPtr
  Eval(const Object::PyObjPtr& func, const Object::PyListPtr& arguments);

  void BackToParentFrame();
  void SetFrame(const PyFramePtr& child);
  [[nodiscard]] PyFramePtr CurrentFrame() const;
};

}  // namespace torchlight::Runtime

#endif