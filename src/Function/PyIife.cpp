#include "Function/PyIife.h"
#include "Collections/StringHelper.h"
#include "Object/PyDictionary.h"
#include "Object/PyString.h"
#include "Object/PyType.h"

namespace torchlight::Object {

IifeKlass::IifeKlass() = default;

void IifeKlass::Initialize() {
  SetType(CreatePyType(Self()));
  SetName(CreatePyString("iife"));
  SetAttributes(CreatePyDict());
  Klass::Initialize();
}

KlassPtr IifeKlass::Self() {
  static KlassPtr instance = std::make_shared<IifeKlass>();
  return instance;
}


PyIife::PyIife(TypeFunction nativeFunction)
  : PyObject(IifeKlass::Self()), nativeFunction(std::move(nativeFunction)) {}

PyObjPtr PyIife::Call(const PyObjPtr& args) {
  return nativeFunction(args);
}

PyObjPtr CreatePyIife(TypeFunction nativeFunction) {
  return std::make_shared<PyIife>(std::move(nativeFunction));
}

}  // namespace torchlight::Object