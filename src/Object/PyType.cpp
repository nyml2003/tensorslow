#include "Object/PyType.h"
#include "Object/PyDictionary.h"
#include "Object/PyString.h"

namespace torchlight::Object {

PyType::PyType(KlassPtr owner)
  : PyObject(TypeKlass::Self()), owner(std::move(owner)) {}

KlassPtr PyType::Owner() const {
  return owner;
}

TypeKlass::TypeKlass() = default;

KlassPtr TypeKlass::Self() {
  static KlassPtr instance = std::make_shared<TypeKlass>();
  return instance;
}

PyObjPtr CreatePyType(KlassPtr owner) {
  return std::make_shared<PyType>(owner);
}

void TypeKlass::Initialize() {
  SetType(CreatePyType(Self()));
  SetName(CreatePyString("type"));
  SetAttributes(CreatePyDict());
  Klass::Initialize();
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
