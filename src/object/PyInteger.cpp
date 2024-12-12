#include "collections/Integer.h"
#include "object/PyInteger.h"

#include <utility>
#include "object/PyString.h"

namespace torchlight::object {

PyInteger::PyInteger(int value)
  : PyObject(IntegerKlass::Self()), value(collections::Integer(value)) {}

PyInteger::PyInteger(collections::Integer value)
  : PyObject(IntegerKlass::Self()), value(std::move(value)) {}

[[nodiscard]]

collections::Integer PyInteger::Value() const {
  return value;
}

IntegerKlass::IntegerKlass()
  : Klass(collections::String("int")) {}

KlassPtr IntegerKlass::Self() {
  static KlassPtr instance = std::make_shared<IntegerKlass>();
  return instance;
}

PyObjPtr IntegerKlass::add(PyObjPtr lhs, PyObjPtr rhs) {
  if (lhs->Klass() != IntegerKlass::Self() ||
      rhs->Klass() != IntegerKlass::Self()) {
    return nullptr;
  }
  auto left = std::dynamic_pointer_cast<PyInteger>(lhs);
  auto right = std::dynamic_pointer_cast<PyInteger>(rhs);
  return std::make_shared<PyInteger>(left->Value().Add(right->Value()));
}

PyObjPtr IntegerKlass::sub(PyObjPtr lhs, PyObjPtr rhs) {
  if (lhs->Klass() != IntegerKlass::Self() ||
      rhs->Klass() != IntegerKlass::Self()) {
    return nullptr;
  }
  auto left = std::dynamic_pointer_cast<PyInteger>(lhs);
  auto right = std::dynamic_pointer_cast<PyInteger>(rhs);
  return std::make_shared<PyInteger>(left->Value().Subtract(right->Value()));
}

PyObjPtr IntegerKlass::mul(PyObjPtr lhs, PyObjPtr rhs) {
  if (lhs->Klass() != IntegerKlass::Self() ||
      rhs->Klass() != IntegerKlass::Self()) {
    return nullptr;
  }
  auto left = std::dynamic_pointer_cast<PyInteger>(lhs);
  auto right = std::dynamic_pointer_cast<PyInteger>(rhs);
  return std::make_shared<PyInteger>(left->Value().Multiply(right->Value()));
}

PyObjPtr IntegerKlass::div(PyObjPtr lhs, PyObjPtr rhs) {
  if (lhs->Klass() != IntegerKlass::Self() ||
      rhs->Klass() != IntegerKlass::Self()) {
    return nullptr;
  }
  auto left = std::dynamic_pointer_cast<PyInteger>(lhs);
  auto right = std::dynamic_pointer_cast<PyInteger>(rhs);
  return std::make_shared<PyInteger>(left->Value().Divide(right->Value()));
}

PyObjPtr IntegerKlass::repr(PyObjPtr obj) {
  if (obj->Klass() != IntegerKlass::Self()) {
    return nullptr;
  }
  auto integer = std::dynamic_pointer_cast<PyInteger>(obj);
  collections::String result = collections::String("<int ")
                                 .Concat(integer->Value().ToString())
                                 .Concat(collections::String(">"));
  return std::make_shared<PyString>(result);
}

}  // namespace torchlight::object