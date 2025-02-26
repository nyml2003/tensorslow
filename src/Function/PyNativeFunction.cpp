#include "Function/PyNativeFunction.h"
#include "Collections/StringHelper.h"
#include "Object/ObjectHelper.h"
#include "Object/PyDictionary.h"
#include "Object/PyList.h"
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

PyNativeFunction::PyNativeFunction(TypeFunction nativeFunction)
  : PyObject(NativeFunctionKlass::Self()),
    nativeFunction(std::move(nativeFunction)) {}

PyObjPtr PyNativeFunction::Call(const PyObjPtr& args) {
  return nativeFunction(args);
}

PyObjPtr CreatePyNativeFunction(TypeFunction nativeFunction) {
  return std::make_shared<PyNativeFunction>(std::move(nativeFunction));
}

void CheckNativeFunctionArgumentsWithExpectedLength(
  const PyObjPtr& args,
  Index expected
) {
  CheckNativeFunctionArguments(args);
  auto list = std::dynamic_pointer_cast<PyList>(args);
  if (list->Length() != expected) {
    throw std::runtime_error(
      "NativeFunction expected " +
      Collections::ToCppString(Collections::ToString(expected)) +
      " arguments, but got " +
      Collections::ToCppString(Collections::ToString(list->Length()))
    );
  }
}

void CheckNativeFunctionArguments(const PyObjPtr& args) {
  IsType(args, ListKlass::Self());
}

void CheckNativeFunctionArgumentsWithTypes(
  const PyObjPtr& args,
  const Collections::List<KlassPtr>& types
) {
  CheckNativeFunctionArguments(args);
  auto list = std::dynamic_pointer_cast<PyList>(args);
  for (Index i = 0; i < list->Length(); ++i) {
    auto arg = list->GetItem(i);
    if (arg->Klass() != types.Get(i)) {
      throw std::runtime_error(
        "NativeFunction expected argument " +
        Collections::ToCppString(Collections::ToString(i)) + " to be of type " +
        Collections::ToCppString(types.Get(i)->Name()->Value()) + ", but got " +
        Collections::ToCppString(arg->Klass()->Name()->Value())
      );
    }
  }
}

}  // namespace torchlight::Object
