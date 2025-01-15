#include "object/PyString.h"

#include "collections/String.h"
#include "collections/impl/Bytes.h"
#include "collections/impl/String.h"
#include "object/ByteCode.h"
#include "object/Klass.h"
#include "object/PyBoolean.h"
#include "object/PyBytes.h"

namespace torchlight::object {

using collections::CreateStringWithCString;
using collections::Serialize;
using collections::String;

PyString::PyString(String value)
  : PyObject(StringKlass::Self()), value(std::move(value)) {}

String PyString::Value() const {
  return value;
}

StringKlass::StringKlass() : Klass(CreateStringWithCString("str")) {}

KlassPtr StringKlass::Self() {
  static KlassPtr instance = std::make_shared<StringKlass>();
  return instance;
}

PyStrPtr CreatePyString(String value) {
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
  auto string = std::dynamic_pointer_cast<PyString>(obj);
  return CreatePyString(CreateStringWithCString("<str '")
                          .Add(string->Value())
                          .Add(CreateStringWithCString("'>")));
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
    return nullptr;
  }
  auto string = std::dynamic_pointer_cast<PyString>(obj);
  return CreatePyBytes(Serialize(Literal::BYTES).Add(Serialize(string->Value()))
  );
}
}  // namespace torchlight::object