#ifndef TORCHLIGHT_FUNCTION_PYNATIVEFUNCTION_H
#define TORCHLIGHT_FUNCTION_PYNATIVEFUNCTION_H

#include <functional>
#include "Object/PyString.h"

namespace torchlight::Object {

using TypeFunction = std::function<PyObjPtr(PyObjPtr)>;

class NativeFunctionKlass : public Klass {
 public:
  explicit NativeFunctionKlass() = default;

  static KlassPtr Self() {
    static KlassPtr instance = std::make_shared<NativeFunctionKlass>();
    return instance;
  }

  PyObjPtr repr(const PyObjPtr& obj) override;
  static void Initialize();
};

class PyNativeFunction : public PyObject {
 private:
  TypeFunction nativeFunction;

 public:
  explicit PyNativeFunction(TypeFunction nativeFunction)
    : PyObject(NativeFunctionKlass::Self()),
      nativeFunction(std::move(nativeFunction)) {}

  PyObjPtr Call(const PyObjPtr& args) { return nativeFunction(args); }
};

using PyNativeFunctionPtr = std::shared_ptr<PyNativeFunction>;

inline PyObjPtr CreatePyNativeFunction(TypeFunction nativeFunction) {
  return std::make_shared<PyNativeFunction>(std::move(nativeFunction));
}

void CheckNativeFunctionArguments(const PyObjPtr& args);
void CheckNativeFunctionArgumentsWithExpectedLength(
  const PyObjPtr& args,
  Index expected
);

void CheckNativeFunctionArgumentsAtIndexWithType(
  const PyStrPtr& funcName,
  const PyObjPtr& args,
  Index index,
  const KlassPtr& klass
);

void CheckNativeFunctionArgumentWithType(
  const PyStrPtr& funcName,
  const PyObjPtr& arg,
  Index index,
  const KlassPtr& klass
);

}  // namespace torchlight::Object

#endif