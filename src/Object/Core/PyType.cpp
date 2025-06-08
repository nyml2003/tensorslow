#include "Object/Core/PyType.h"
#include "Function/BuiltinFunction.h"
#include "Object/Core/PyBoolean.h"
#include "Object/String/PyString.h"
namespace tensorslow::Object {

void TypeKlass::Initialize() {
  if (this->isInitialized) {
    return;
  }
  InitKlass(CreatePyString("type")->as<PyString>(), Self());
  this->isInitialized = true;
}

PyType::PyType(KlassPtr _owner)
  : PyObject(TypeKlass::Self()), owner(std::move(_owner)) {
  this->SetAttributes(owner->Attributes());
}

PyObjPtr TypeKlass::repr(const PyObjPtr& obj) {
  if (!obj->is(TypeKlass::Self())) {
    throw std::runtime_error("PyType::repr(): obj is not a type object");
  }
  auto type = obj->as<PyType>();
  return CreatePyString("<class '")
    ->add(type->Owner()->Name())
    ->add(CreatePyString("'>"));
}

PyObjPtr TypeKlass::eq(const PyObjPtr& lhs, const PyObjPtr& rhs) {
  if (!lhs->is(TypeKlass::Self()) || !rhs->is(TypeKlass::Self())) {
    throw std::runtime_error("PyType::eq(): lhs or rhs is not a type object");
  }
  auto lhsType = lhs->as<PyType>();
  auto rhsType = rhs->as<PyType>();
  return CreatePyBoolean(lhsType->Owner() == rhsType->Owner());
}

}  // namespace tensorslow::Object
