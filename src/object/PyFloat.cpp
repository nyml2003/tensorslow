#include "Collections/BytesHelper.h"
#include "Collections/StringHelper.h"
#include "Object/ByteCode.h"
#include "Object/PyBoolean.h"
#include "Object/PyBytes.h"
#include "Object/PyFloat.h"
#include "Object/PyString.h"

namespace torchlight::Object {

PyFloat::PyFloat(double value) : PyObject(FloatKlass::Self()), value(value) {}

double PyFloat::Value() const {
  return value;
}

PyFloatPtr CreatePyFloat(double value) {
  return std::make_shared<PyFloat>(value);
}

FloatKlass::FloatKlass()
  : Klass(Collections::CreateStringWithCString("float")) {}

KlassPtr FloatKlass::Self() {
  static KlassPtr instance = std::make_shared<FloatKlass>();
  return instance;
}  // namespace torchlight::Object

PyObjPtr FloatKlass::add(PyObjPtr lhs, PyObjPtr rhs) {
  if (lhs->Klass() != Self() || rhs->Klass() != Self()) {
    throw std::runtime_error("PyFloat::add(): lhs or rhs is not a float");
  }
  auto left = std::dynamic_pointer_cast<PyFloat>(lhs);
  auto right = std::dynamic_pointer_cast<PyFloat>(rhs);
  return CreatePyFloat(left->Value() + right->Value());
}

PyObjPtr FloatKlass::sub(PyObjPtr lhs, PyObjPtr rhs) {
  if (lhs->Klass() != Self() || rhs->Klass() != Self()) {
    throw std::runtime_error("PyFloat::sub(): lhs or rhs is not a float");
  }
  auto left = std::dynamic_pointer_cast<PyFloat>(lhs);
  auto right = std::dynamic_pointer_cast<PyFloat>(rhs);
  return CreatePyFloat(left->Value() - right->Value());
}

PyObjPtr FloatKlass::mul(PyObjPtr lhs, PyObjPtr rhs) {
  if (lhs->Klass() != Self() || rhs->Klass() != Self()) {
    throw std::runtime_error("PyFloat::mul(): lhs or rhs is not a float");
  }
  auto left = std::dynamic_pointer_cast<PyFloat>(lhs);
  auto right = std::dynamic_pointer_cast<PyFloat>(rhs);
  return CreatePyFloat(left->Value() * right->Value());
}

PyObjPtr FloatKlass::div(PyObjPtr lhs, PyObjPtr rhs) {
  if (lhs->Klass() != Self() || rhs->Klass() != Self()) {
    throw std::runtime_error("PyFloat::div(): lhs or rhs is not a float");
  }
  auto left = std::dynamic_pointer_cast<PyFloat>(lhs);
  auto right = std::dynamic_pointer_cast<PyFloat>(rhs);
  return CreatePyFloat(left->Value() / right->Value());
}

PyObjPtr FloatKlass::repr(PyObjPtr obj) {
  if (obj->Klass() != Self()) {
    throw std::runtime_error("PyFloat::repr(): obj is not a float");
  }
  auto floatObj = std::dynamic_pointer_cast<PyFloat>(obj);
  return CreatePyString(Collections::ToString(floatObj->Value()));
}

PyObjPtr FloatKlass::_serialize_(PyObjPtr obj) {
  if (obj->Klass() != Self()) {
    throw std::runtime_error("PyFloat::_serialize_(): obj is not a float");
  }
  auto floatObj = std::dynamic_pointer_cast<PyFloat>(obj);
  return CreatePyBytes(Collections::Serialize(Literal::FLOAT)
                         .Add(Collections::Serialize(floatObj->Value())));
}

PyObjPtr FloatKlass::eq(PyObjPtr lhs, PyObjPtr rhs) {
  if (lhs->Klass() != Self() || rhs->Klass() != Self()) {
    return CreatePyBoolean(false);
  }
  auto left = std::dynamic_pointer_cast<PyFloat>(lhs);
  auto right = std::dynamic_pointer_cast<PyFloat>(rhs);
  return CreatePyBoolean(left->Value() == right->Value());
}

}  // namespace torchlight::Object
