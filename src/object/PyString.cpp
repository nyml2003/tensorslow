#include "object/PyString.h"

#include "collections/String.h"
#include "collections/impl/Bytes.h"
#include "collections/impl/String.h"
#include "object/ByteCode.h"
#include "object/Klass.h"
#include "object/PyBytes.h"

namespace torchlight::object {

using collections::Bytes;
using collections::Serialize;

PyString::PyString(collections::String value)
  : PyObject(StringKlass::Self()), value(std::move(value)) {}

collections::String PyString::Value() const {
  return value;
}

StringKlass::StringKlass()
  : Klass(collections::CreateStringWithCString("str")) {}

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
  collections::String result =
    collections::CreateStringWithCString("<str '")
      .Concat(string->Value())
      .Concat(collections::CreateStringWithCString("'>"));
  return std::make_shared<PyString>(result);
}

PyObjPtr StringKlass::_serialize_(PyObjPtr obj) {
  if (obj->Klass() != Self()) {
    return nullptr;
  }
  auto string = std::dynamic_pointer_cast<PyString>(obj);
  Bytes bytes;
  bytes.InplaceConcat(Serialize(Literal::STRING));
  bytes.InplaceConcat(Serialize(string->Value()));
  return std::make_shared<PyBytes>(bytes);
}
}  // namespace torchlight::object