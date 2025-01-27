#include "Collections/StringHelper.h"
#include "Function/PyNativeFunction.h"
#include "Object/PyDictionary.h"
#include "Object/PyString.h"
#include "Object/PyType.h"

namespace torchlight::Object {

NativeFunctionKlass::NativeFunctionKlass() = default;

void NativeFunctionKlass::Initialize() {
  SetType(CreatePyType(Self()));
  SetName(CreatePyString("native_function"));
  SetAttributes(CreatePyDict());
  Klass::Initialize();
}

KlassPtr NativeFunctionKlass::Self() {
  static KlassPtr instance = std::make_shared<NativeFunctionKlass>();
  return instance;
}

PyObjPtr NativeFunctionKlass::repr(PyObjPtr self) {
  if (self->Klass() != Self()) {
    throw std::runtime_error("NativeFunction does not support repr operation");
  }
  return CreatePyString(
    Collections::CreateStringWithCString("<native_function at ")
      .Add(Collections::ToString(reinterpret_cast<uint64_t>(self.get())))
      .Add(Collections::CreateStringWithCString(">"))
  );
}

PyNativeFunction::PyNativeFunction(TypeFunction nativeFunction)
  : PyObject(NativeFunctionKlass::Self()),
    nativeFunction(std::move(nativeFunction)) {}

PyObjPtr PyNativeFunction::Call(PyObjPtr args) {
  return nativeFunction(std::move(args));
}

PyObjPtr CreatePyNativeFunction(TypeFunction nativeFunction) {
  return std::make_shared<PyNativeFunction>(std::move(nativeFunction));
}

}  // namespace torchlight::Object
