#include "collections/String.h"
#include "object/Klass.h"
#include "object/PyString.h"

namespace torchlight::object {
PyString::PyString(collections::String value)
  : PyObject(StringKlass::Self()), value(std::move(value)) {}

collections::String PyString::Value() const {
  return value;
}

StringKlass::StringKlass()
  : Klass(collections::String("str")) {}

KlassPtr StringKlass::Self() {
  static KlassPtr instance = std::make_shared<StringKlass>();
  return instance;
}

PyObjPtr StringKlass::add(PyObjPtr lhs, PyObjPtr rhs) {
  if (lhs->Klass() != StringKlass::Self() ||
      rhs->Klass() != StringKlass::Self()) {
    return nullptr;
  }
  auto left = std::dynamic_pointer_cast<PyString>(lhs);
  auto right = std::dynamic_pointer_cast<PyString>(rhs);
  return std::make_shared<PyString>(left->Value().Concat(right->Value()));
}

PyObjPtr StringKlass::repr(PyObjPtr obj) {
  if (obj->Klass() != StringKlass::Self()) {
    return nullptr;
  }
  auto string = std::dynamic_pointer_cast<PyString>(obj);
  collections::String result = collections::String("<str '")
                                 .Concat(string->Value())
                                 .Concat(collections::String("'>"));
  return std::make_shared<PyString>(result);
}
}  // namespace torchlight::object