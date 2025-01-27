#ifndef TORCHLIGHT_FUNCTION_PYNATIVEFUNCTION_H
#define TORCHLIGHT_FUNCTION_PYNATIVEFUNCTION_H

#include "Object/Common.h"
#include "Object/Klass.h"
#include "Object/PyObject.h"

#include <functional>

namespace torchlight::Object {

using TypeFunction = std::function<PyObjPtr(PyObjPtr)>;

class NativeFunctionKlass : public Klass {
 public:
  NativeFunctionKlass();

  static KlassPtr Self();

  PyObjPtr repr(PyObjPtr self) override;

  void Initialize() override;
};

class PyNativeFunction : public PyObject {
 private:
  TypeFunction nativeFunction;

 public:
  explicit PyNativeFunction(TypeFunction nativeFunction);

  PyObjPtr Call(PyObjPtr args);
};

using PyNativeFunctionPtr = std::shared_ptr<PyNativeFunction>;

PyObjPtr CreatePyNativeFunction(TypeFunction nativeFunction);

}  // namespace torchlight::Object

#endif