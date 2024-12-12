#include <string>
#include "object/PyFloat.h"
#include "object/PyString.h"

namespace torchlight::object {

PyFloat::PyFloat(double value) : PyObject(FloatKlass::Self()), value(value) {}

double PyFloat::Value() const {
  return value;
}

FloatKlass::FloatKlass() : Klass(collections::String("float")) {}

KlassPtr FloatKlass::Self() {
  static KlassPtr instance = std::make_shared<FloatKlass>();
  return instance;
}  // namespace torchlight::object

PyObjPtr FloatKlass::add(PyObjPtr lhs, PyObjPtr rhs) {
  if (lhs->Klass() != FloatKlass::Self() ||
      rhs->Klass() != FloatKlass::Self()) {
    return nullptr;
  }
  auto left = std::dynamic_pointer_cast<PyFloat>(lhs);
  auto right = std::dynamic_pointer_cast<PyFloat>(rhs);
  return std::make_shared<PyFloat>(left->Value() + right->Value());
}

PyObjPtr FloatKlass::sub(PyObjPtr lhs, PyObjPtr rhs) {
  if (lhs->Klass() != FloatKlass::Self() ||
      rhs->Klass() != FloatKlass::Self()) {
    return nullptr;
  }
  auto left = std::dynamic_pointer_cast<PyFloat>(lhs);
  auto right = std::dynamic_pointer_cast<PyFloat>(rhs);
  return std::make_shared<PyFloat>(left->Value() - right->Value());
}

PyObjPtr FloatKlass::mul(PyObjPtr lhs, PyObjPtr rhs) {
  if (lhs->Klass() != FloatKlass::Self() ||
      rhs->Klass() != FloatKlass::Self()) {
    return nullptr;
  }
  auto left = std::dynamic_pointer_cast<PyFloat>(lhs);
  auto right = std::dynamic_pointer_cast<PyFloat>(rhs);
  return std::make_shared<PyFloat>(left->Value() * right->Value());
}

PyObjPtr FloatKlass::div(PyObjPtr lhs, PyObjPtr rhs) {
  if (lhs->Klass() != FloatKlass::Self() ||
      rhs->Klass() != FloatKlass::Self()) {
    return nullptr;
  }
  auto left = std::dynamic_pointer_cast<PyFloat>(lhs);
  auto right = std::dynamic_pointer_cast<PyFloat>(rhs);
  return std::make_shared<PyFloat>(left->Value() / right->Value());
}

PyObjPtr FloatKlass::repr(PyObjPtr obj) {
  if (obj->Klass() != FloatKlass::Self()) {
    return nullptr;
  }
  auto floatObj = std::dynamic_pointer_cast<PyFloat>(obj);
  collections::String result =
    collections::String("<float ")
      .Concat(collections::String(std::to_string(floatObj->Value()).c_str()))
      .Concat(collections::String(">"));
  return std::make_shared<PyString>(result);
}

}  // namespace torchlight::object
