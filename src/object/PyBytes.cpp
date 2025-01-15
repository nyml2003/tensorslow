#include "collections/Bytes.h"
#include "collections/impl/Bytes.h"
#include "collections/impl/String.h"
#include "object/ByteCode.h"
#include "object/PyBytes.h"
#include "object/PyObject.h"
#include "object/PyString.h"

namespace torchlight::object {

using collections::Bytes;
using collections::CreateStringWithCString;
PyBytes::PyBytes(Bytes value)
  : PyObject(BytesKlass::Self()), value(std::move(value)) {}

PyBytesPtr CreatePyBytes(Bytes value) {
  return std::make_shared<PyBytes>(value);
}

[[nodiscard]] Bytes PyBytes::Value() const {
  return value;
}

BytesKlass::BytesKlass() : Klass(CreateStringWithCString("bytes")) {}

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
  return CreatePyBytes(left->Value().Add(right->Value()));
}

PyObjPtr BytesKlass::_serialize_(PyObjPtr obj) {
  if (obj->Klass() != Self()) {
    return nullptr;
  }
  return CreatePyBytes(
    Serialize(Literal::BYTES)
      .Add(Serialize(std::dynamic_pointer_cast<PyBytes>(obj)->Value()))
  );
}

PyObjPtr BytesKlass::repr(PyObjPtr obj) {
  if (obj->Klass() != Self()) {
    return nullptr;
  }
  auto bytes = std::dynamic_pointer_cast<PyBytes>(obj);
  return CreatePyString(CreateStringWithCString("<bytes ")
                          .Add(CreateStringWithBytes(bytes->Value()))
                          .Add(CreateStringWithCString(">")));
}

}  // namespace torchlight::object