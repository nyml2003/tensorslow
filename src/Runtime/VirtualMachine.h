#ifndef TENSORSLOW_RUNTIME_VIRTUAL_MACHINE_H
#define TENSORSLOW_RUNTIME_VIRTUAL_MACHINE_H

#include "Object/Function/PyMethod.h"
#include "Object/Function/PyNativeFunction.h"
#include "Object/Object.h"
#include "Object/Runtime/PyCode.h"
#include "Object/Runtime/PyFrame.h"

namespace tensorslow::Runtime {

class VirtualMachine {
 private:
  Object::PyFramePtr frame;
  Object::PyDictPtr builtins;
  explicit VirtualMachine();

 public:
  static VirtualMachine& Instance();

  static void Run(const Object::PyCodePtr& code);

  [[nodiscard]] Object::PyDictPtr Builtins() const;

  [[nodiscard]] static Object::PyObjPtr EvalNativeFunction(
    const Object::PyNativeFunctionPtr& func,
    const Object::PyListPtr& arguments
  );

  [[nodiscard]] static Object::PyObjPtr EvalMethod(
    const Object::PyMethodPtr& func,
    const Object::PyListPtr& arguments
  );

  [[nodiscard]] static Object::PyObjPtr EvalConstructor(
    const Object::PyTypePtr& type,
    const Object::PyListPtr& arguments
  );

  [[nodiscard]] static Object::PyObjPtr EvalPyFunction(
    const Object::PyFunctionPtr& func,
    const Object::PyListPtr& arguments
  );

  [[nodiscard]] static Object::PyObjPtr
  Eval(const Object::PyObjPtr& func, const Object::PyListPtr& arguments);

  void BackToParentFrame();
  void SetFrame(const Object::PyFramePtr& child);
  [[nodiscard]] Object::PyFramePtr CurrentFrame() const;
};

}  // namespace tensorslow::Runtime

#endif