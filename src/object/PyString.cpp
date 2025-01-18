#include "Collections/BytesHelper.h"
#include "Collections/StringHelper.h"
#include "Object/ByteCode.h"
#include "Object/Klass.h"
#include "Object/PyBoolean.h"
#include "Object/PyBytes.h"
#include "Object/PyString.h"

namespace torchlight::Object {

PyString::PyString(Collections::String value)
  : PyObject(StringKlass::Self()), value(std::move(value)) {}

Collections::String PyString::Value() const {
  return value;
}

StringKlass::StringKlass()
  : Klass(Collections::CreateStringWithCString("str")) {}

KlassPtr StringKlass::Self() {
  static KlassPtr instance = std::make_shared<StringKlass>();
  return instance;
}

PyStrPtr CreatePyString(Collections::String value) {
  return std::make_shared<PyString>(value);
}

PyObjPtr StringKlass::add(PyObjPtr lhs, PyObjPtr rhs) {
  if (lhs->Klass() != StringKlass::Self()) {
    throw std::runtime_error("lhs is not a string");
  }
  if (rhs->Klass() != StringKlass::Self()) {
    throw std::runtime_error("rhs is not a string");
  }
  auto left = std::dynamic_pointer_cast<PyString>(lhs);
  auto right = std::dynamic_pointer_cast<PyString>(rhs);
  return CreatePyString(left->Value().Add(right->Value()));
}

PyObjPtr StringKlass::repr(PyObjPtr obj) {
  if (obj->Klass() != StringKlass::Self()) {
    throw std::runtime_error("obj is not a string");
  }
  return CreatePyString(Collections::CreateStringWithCString("\"")
                         .Add(std::dynamic_pointer_cast<PyString>(obj)->Value())
                         .Add(Collections::CreateStringWithCString("\"")));
}

PyObjPtr StringKlass::eq(PyObjPtr lhs, PyObjPtr rhs) {
  if (lhs->Klass() != Self()) {
    throw std::runtime_error("lhs is not a string");
  }
  if (rhs->Klass() != Self()) {
    throw std::runtime_error("rhs is not a string");
  }
  auto left = std::dynamic_pointer_cast<PyString>(lhs);
  auto right = std::dynamic_pointer_cast<PyString>(rhs);
  return CreatePyBoolean(left->Value() == right->Value());
}

PyObjPtr StringKlass::_serialize_(PyObjPtr obj) {
  if (obj->Klass() != Self()) {
    throw std::runtime_error("str does not support serialization");
  }
  auto string = std::dynamic_pointer_cast<PyString>(obj);
  return CreatePyBytes(Collections::Serialize(Literal::STRING)
                         .Add(Collections::Serialize(string->Value())));
}
}  // namespace torchlight::Object