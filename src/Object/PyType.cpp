#include "Object/PyType.h"
#include "Object/ObjectHelper.h"
#include "Object/PyBoolean.h"
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

PyObjPtr TypeKlass::eq(const PyObjPtr& lhs, const PyObjPtr& rhs) {
  if (!lhs->is<PyType>() || !rhs->is<PyType>()) {
    throw std::runtime_error("PyType::eq(): lhs or rhs is not a type object");
  }
  auto lhsType = lhs->as<PyType>();
  auto rhsType = rhs->as<PyType>();
  return CreatePyBoolean(lhsType->Owner() == rhsType->Owner());
}

}  // namespace torchlight::Object
