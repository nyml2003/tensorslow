
#include "object/PyBytes.h"
#include "collections/Bytes.h"
#include "collections/impl/Bytes.h"
#include "collections/impl/String.h"
#include "object/ByteCode.h"
#include "object/PyObject.h"
#include "object/PyString.h"

namespace torchlight::object {

PyBytes::PyBytes(collections::Bytes value)
  : PyObject(BytesKlass::Self()), value(std::move(value)) {}

[[nodiscard]] collections::Bytes PyBytes::Value() const {
  return value;
}

BytesKlass::BytesKlass()
  : Klass(collections::CreateStringWithCString("bytes")) {}

KlassPtr BytesKlass::Self() {
  static KlassPtr instance = std::make_shared<BytesKlass>();
  return instance;
}

PyObjPtr BytesKlass::add(PyObjPtr lhs, PyObjPtr rhs) {
  if (lhs->Klass() != Self() || rhs->Klass() != Self()) {
    return nullptr;
  }
  auto left = std::dynamic_pointer_cast<PyBytes>(lhs);
  auto right = std::dynamic_pointer_cast<PyBytes>(rhs);
  return std::make_shared<PyBytes>(left->Value().Concat(right->Value()));
}

PyObjPtr BytesKlass::_serialize_(PyObjPtr obj) {
  if (obj->Klass() != Self()) {
    return nullptr;
  }
  return std::make_shared<PyBytes>(
    Serialize(Literal::BYTES)
      .Concat(Serialize(std::dynamic_pointer_cast<PyBytes>(obj)->Value()))
  );
}

PyObjPtr BytesKlass::repr(PyObjPtr obj) {
  if (obj->Klass() != Self()) {
    return nullptr;
  }
  auto bytes = std::dynamic_pointer_cast<PyBytes>(obj);
  collections::String result =
    collections::CreateStringWithCString("<bytes ")
      .Concat(collections::CreateStringWithBytes(bytes->Value()))
      .Concat(collections::CreateStringWithCString(">\n"));
  return std::make_shared<PyString>(result);
}

}  // namespace torchlight::object