#include "Collections/StringHelper.h"
#include "Function/PyIife.h"
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

PyObjPtr IifeKlass::repr(PyObjPtr self) {
  if (self->Klass() != Self()) {
    throw std::runtime_error("Iife does not support repr operation");
  }
  return CreatePyString(
    Collections::CreateStringWithCString("<iife at ")
      .Add(Collections::ToString(reinterpret_cast<uint64_t>(self.get())))
      .Add(Collections::CreateStringWithCString(">"))
  );
}

PyIife::PyIife(TypeFunction nativeFunction)
  : PyObject(IifeKlass::Self()), nativeFunction(std::move(nativeFunction)) {}

PyObjPtr PyIife::Call(PyObjPtr args) {
  return nativeFunction(std::move(args));
}

PyObjPtr CreatePyIife(TypeFunction nativeFunction) {
  return std::make_shared<PyIife>(std::move(nativeFunction));
}

}  // namespace torchlight::Object