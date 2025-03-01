#include "Object/PyType.h"
#include "Object/PyString.h"

namespace torchlight::Object {

void TypeKlass::Initialize() {
  LoadClass(CreatePyString("type")->as<PyString>(), Self());
  ConfigureBasicAttributes(Self());
}

PyObjPtr TypeKlass::repr(const PyObjPtr& obj) {
  if (obj->Klass() != Self()) {
    throw std::runtime_error("PyType::repr(): obj is not a type object");
  }
  auto type = std::dynamic_pointer_cast<PyType>(obj);
  return CreatePyString("<class '")
    ->add(type->Owner()->Name())
    ->add(CreatePyString("'>"));
}

}  // namespace torchlight::Object
