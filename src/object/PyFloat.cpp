#include "collections/Bytes.h"
#include "collections/impl/Bytes.h"
#include "collections/impl/String.h"
#include "object/ByteCode.h"
#include "object/PyBytes.h"
#include "object/PyFloat.h"
#include "object/PyString.h"

namespace torchlight::object {

using collections::CreateStringWithCString;
using collections::Serialize;
using collections::ToString;

PyFloat::PyFloat(double value) : PyObject(FloatKlass::Self()), value(value) {}

double PyFloat::Value() const {
  return value;
}

PyFloatPtr CreateFloat(double value) {
  return std::make_shared<PyFloat>(value);
}

FloatKlass::FloatKlass() : Klass(CreateStringWithCString("float")) {}

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
  return CreateFloat(left->Value() + right->Value());
}

PyObjPtr FloatKlass::sub(PyObjPtr lhs, PyObjPtr rhs) {
  if (lhs->Klass() != Self() || rhs->Klass() != Self()) {
    return nullptr;
  }
  auto left = std::dynamic_pointer_cast<PyFloat>(lhs);
  auto right = std::dynamic_pointer_cast<PyFloat>(rhs);
  return CreateFloat(left->Value() - right->Value());
}

PyObjPtr FloatKlass::mul(PyObjPtr lhs, PyObjPtr rhs) {
  if (lhs->Klass() != Self() || rhs->Klass() != Self()) {
    return nullptr;
  }
  auto left = std::dynamic_pointer_cast<PyFloat>(lhs);
  auto right = std::dynamic_pointer_cast<PyFloat>(rhs);
  return CreateFloat(left->Value() * right->Value());
}

PyObjPtr FloatKlass::div(PyObjPtr lhs, PyObjPtr rhs) {
  if (lhs->Klass() != Self() || rhs->Klass() != Self()) {
    return nullptr;
  }
  auto left = std::dynamic_pointer_cast<PyFloat>(lhs);
  auto right = std::dynamic_pointer_cast<PyFloat>(rhs);
  return CreateFloat(left->Value() / right->Value());
}

PyObjPtr FloatKlass::repr(PyObjPtr obj) {
  if (obj->Klass() != Self()) {
    return nullptr;
  }
  auto floatObj = std::dynamic_pointer_cast<PyFloat>(obj);
  return CreatePyString(CreateStringWithCString("<float ")
                          .Add(ToString(floatObj->Value()))
                          .Add(CreateStringWithCString(">")));
}

PyObjPtr FloatKlass::_serialize_(PyObjPtr obj) {
  if (obj->Klass() != Self()) {
    return nullptr;
  }
  auto floatObj = std::dynamic_pointer_cast<PyFloat>(obj);
  return CreatePyBytes(
    Serialize(Literal::FLOAT).Add(Serialize(floatObj->Value()))
  );
}

}  // namespace torchlight::object
