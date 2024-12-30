#include "object/PyFloat.h"

#include "collections/Bytes.h"
#include "collections/impl/Bytes.h"
#include "collections/impl/String.h"
#include "object/ByteCode.h"
#include "object/PyBytes.h"
#include "object/PyString.h"

namespace torchlight::object {

using collections::Bytes;
using collections::Serialize;
using collections::String;

PyFloat::PyFloat(double value) : PyObject(FloatKlass::Self()), value(value) {}

double PyFloat::Value() const {
  return value;
}

FloatKlass::FloatKlass()
  : Klass(collections::CreateStringWithCString("float")) {}

KlassPtr FloatKlass::Self() {
  static KlassPtr instance = std::make_shared<FloatKlass>();
  return instance;
}  // namespace torchlight::object

PyObjPtr FloatKlass::add(PyObjPtr lhs, PyObjPtr rhs) {
  if (lhs->Klass() != Self() || rhs->Klass() != Self()) {
    return nullptr;
  }
  auto left = std::dynamic_pointer_cast<PyFloat>(lhs);
  auto right = std::dynamic_pointer_cast<PyFloat>(rhs);
  return std::make_shared<PyFloat>(left->Value() + right->Value());
}

PyObjPtr FloatKlass::sub(PyObjPtr lhs, PyObjPtr rhs) {
  if (lhs->Klass() != Self() || rhs->Klass() != Self()) {
    return nullptr;
  }
  auto left = std::dynamic_pointer_cast<PyFloat>(lhs);
  auto right = std::dynamic_pointer_cast<PyFloat>(rhs);
  return std::make_shared<PyFloat>(left->Value() - right->Value());
}

PyObjPtr FloatKlass::mul(PyObjPtr lhs, PyObjPtr rhs) {
  if (lhs->Klass() != Self() || rhs->Klass() != Self()) {
    return nullptr;
  }
  auto left = std::dynamic_pointer_cast<PyFloat>(lhs);
  auto right = std::dynamic_pointer_cast<PyFloat>(rhs);
  return std::make_shared<PyFloat>(left->Value() * right->Value());
}

PyObjPtr FloatKlass::div(PyObjPtr lhs, PyObjPtr rhs) {
  if (lhs->Klass() != Self() || rhs->Klass() != Self()) {
    return nullptr;
  }
  auto left = std::dynamic_pointer_cast<PyFloat>(lhs);
  auto right = std::dynamic_pointer_cast<PyFloat>(rhs);
  return std::make_shared<PyFloat>(left->Value() / right->Value());
}

PyObjPtr FloatKlass::repr(PyObjPtr obj) {
  if (obj->Klass() != Self()) {
    return nullptr;
  }
  auto floatObj = std::dynamic_pointer_cast<PyFloat>(obj);
  String result = collections::CreateStringWithCString("<float ")
                    .Concat(collections::ToString(floatObj->Value()))
                    .Concat(collections::CreateStringWithCString(" >"));
  return std::make_shared<PyString>(result);
}

PyObjPtr FloatKlass::_serialize_(PyObjPtr obj) {
  if (obj->Klass() != Self()) {
    return nullptr;
  }
  auto floatObj = std::dynamic_pointer_cast<PyFloat>(obj);
  Bytes bytes;
  bytes.InplaceConcat(Serialize(Literal::FLOAT));
  bytes.InplaceConcat(Serialize(floatObj->Value()));
  return std::make_shared<PyBytes>(bytes);
}

}  // namespace torchlight::object
