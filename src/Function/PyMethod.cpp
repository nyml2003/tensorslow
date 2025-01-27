#include "Collections/StringHelper.h"
#include "Function/PyMethod.h"
#include "Object/PyDictionary.h"
#include "Object/PyString.h"
#include "Object/PyType.h"

#include <utility>

namespace torchlight::Object {

MethodKlass::MethodKlass() = default;

void MethodKlass::Initialize() {
  SetType(CreatePyType(Self()));
  SetName(CreatePyString("method"));
  SetAttributes(CreatePyDict());

  Klass::Initialize();
}

KlassPtr MethodKlass::Self() {
  static KlassPtr instance = std::make_shared<MethodKlass>();
  return instance;
}

PyObjPtr MethodKlass::repr(PyObjPtr obj) {
  if (obj->Klass() != MethodKlass::Self()) {
    throw std::runtime_error("obj is not a method");
  }
  auto method = std::dynamic_pointer_cast<PyMethod>(obj);
  return CreatePyString(Collections::CreateStringWithCString("<method "))
    ->add(method->Owner()->repr())
    ->add(CreatePyString(Collections::CreateStringWithCString("."))
            ->add(method->Method()->repr())
            ->add(CreatePyString(Collections::CreateStringWithCString(">"))));
}

PyMethod::PyMethod(PyObjPtr owner, PyObjPtr method)
  : PyObject(MethodKlass::Self()),
    owner(std::move(owner)),
    method(std::move(method)) {}

PyObjPtr PyMethod::Method() const {
  return method;
}

PyObjPtr PyMethod::Owner() const {
  return owner;
}

PyObjPtr CreatePyMethod(PyObjPtr owner, PyObjPtr method) {
  return std::make_shared<PyMethod>(std::move(owner), std::move(method));
}

}  // namespace torchlight::Object