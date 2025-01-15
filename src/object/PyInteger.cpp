#include "collections/Integer.h"
#include "collections/impl/Bytes.h"
#include "collections/impl/Integer.h"
#include "collections/impl/String.h"
#include "object/ByteCode.h"
#include "object/PyBoolean.h"
#include "object/PyBytes.h"
#include "object/PyInteger.h"
#include "object/PyString.h"

namespace torchlight::object {

using collections::CreateIntegerWithIndex;
using collections::CreateStringWithCString;
using collections::Index;
using collections::Integer;
using collections::Serialize;

PyInteger::PyInteger(Integer value)
  : PyObject(IntegerKlass::Self()), value(std::move(value)) {}

[[nodiscard]]

Integer PyInteger::Value() const {
  return value;
}

PyIntPtr CreatePyInteger(Integer value) {
  return std::make_shared<PyInteger>(value);
}

PyIntPtr CreatePyInteger(Index value) {
  return std::make_shared<PyInteger>(CreateIntegerWithIndex(value));
}

IntegerKlass::IntegerKlass() : Klass(CreateStringWithCString("int")) {}

KlassPtr IntegerKlass::Self() {
  static KlassPtr instance = std::make_shared<IntegerKlass>();
  return instance;
}

PyObjPtr IntegerKlass::add(PyObjPtr lhs, PyObjPtr rhs) {
  if (lhs->Klass() != Self() || rhs->Klass() != Self()) {
    return nullptr;
  }
  auto left = std::dynamic_pointer_cast<PyInteger>(lhs);
  auto right = std::dynamic_pointer_cast<PyInteger>(rhs);
  return CreatePyInteger(left->Value().Add(right->Value()));
}

PyObjPtr IntegerKlass::sub(PyObjPtr lhs, PyObjPtr rhs) {
  if (lhs->Klass() != Self() || rhs->Klass() != Self()) {
    return nullptr;
  }
  auto left = std::dynamic_pointer_cast<PyInteger>(lhs);
  auto right = std::dynamic_pointer_cast<PyInteger>(rhs);
  return CreatePyInteger(left->Value().Subtract(right->Value()));
}

PyObjPtr IntegerKlass::mul(PyObjPtr lhs, PyObjPtr rhs) {
  if (lhs->Klass() != Self() || rhs->Klass() != Self()) {
    return nullptr;
  }
  auto left = std::dynamic_pointer_cast<PyInteger>(lhs);
  auto right = std::dynamic_pointer_cast<PyInteger>(rhs);
  return CreatePyInteger(left->Value().Multiply(right->Value()));
}

PyObjPtr IntegerKlass::div(PyObjPtr lhs, PyObjPtr rhs) {
  if (lhs->Klass() != Self() || rhs->Klass() != Self()) {
    return nullptr;
  }
  auto left = std::dynamic_pointer_cast<PyInteger>(lhs);
  auto right = std::dynamic_pointer_cast<PyInteger>(rhs);
  return CreatePyInteger(left->Value().Divide(right->Value()));
}

PyObjPtr IntegerKlass::repr(PyObjPtr obj) {
  if (obj->Klass() != Self()) {
    return nullptr;
  }
  auto integer = std::dynamic_pointer_cast<PyInteger>(obj);
  return CreatePyString(CreateStringWithCString("<int ")
                          .Add(integer->Value().ToString())
                          .Add(CreateStringWithCString(">")));
}

PyObjPtr IntegerKlass::gt(PyObjPtr lhs, PyObjPtr rhs) {
  if (lhs->Klass() != Self() || rhs->Klass() != Self()) {
    return nullptr;
  }
  auto left = std::dynamic_pointer_cast<PyInteger>(lhs);
  auto right = std::dynamic_pointer_cast<PyInteger>(rhs);
  return CreatePyBoolean(left->Value().GreaterThan(right->Value()));
}

PyObjPtr IntegerKlass::lt(PyObjPtr lhs, PyObjPtr rhs) {
  if (lhs->Klass() != Self() || rhs->Klass() != Self()) {
    return nullptr;
  }
  auto left = std::dynamic_pointer_cast<PyInteger>(lhs);
  auto right = std::dynamic_pointer_cast<PyInteger>(rhs);
  return CreatePyBoolean(left->Value().LessThan(right->Value()));
}

PyObjPtr IntegerKlass::eq(PyObjPtr lhs, PyObjPtr rhs) {
  if (lhs->Klass() != Self() || rhs->Klass() != Self()) {
    return nullptr;
  }
  auto left = std::dynamic_pointer_cast<PyInteger>(lhs);
  auto right = std::dynamic_pointer_cast<PyInteger>(rhs);
  return CreatePyBoolean(left->Value().Equal(right->Value()));
}

PyObjPtr IntegerKlass::ge(PyObjPtr lhs, PyObjPtr rhs) {
  if (lhs->Klass() != Self() || rhs->Klass() != Self()) {
    return nullptr;
  }
  auto left = std::dynamic_pointer_cast<PyInteger>(lhs);
  auto right = std::dynamic_pointer_cast<PyInteger>(rhs);
  return CreatePyBoolean(left->Value().GreaterThanOrEqual(right->Value()));
}

PyObjPtr IntegerKlass::le(PyObjPtr lhs, PyObjPtr rhs) {
  if (lhs->Klass() != Self() || rhs->Klass() != Self()) {
    return nullptr;
  }
  auto left = std::dynamic_pointer_cast<PyInteger>(lhs);
  auto right = std::dynamic_pointer_cast<PyInteger>(rhs);
  return CreatePyBoolean(left->Value().LessThanOrEqual(right->Value()));
}

PyObjPtr IntegerKlass::ne(PyObjPtr lhs, PyObjPtr rhs) {
  if (lhs->Klass() != Self() || rhs->Klass() != Self()) {
    return nullptr;
  }
  auto left = std::dynamic_pointer_cast<PyInteger>(lhs);
  auto right = std::dynamic_pointer_cast<PyInteger>(rhs);
  return CreatePyBoolean(left->Value().NotEqual(right->Value()));
}

PyObjPtr IntegerKlass::_serialize_(PyObjPtr obj) {
  if (obj->Klass() != Self()) {
    return nullptr;
  }
  auto integer = std::dynamic_pointer_cast<PyInteger>(obj);
  if (integer->Value().IsZero()) {
    return CreatePyBytes(Serialize(Literal::ZERO));
  }
  return CreatePyBytes(
    Serialize(Literal::INTEGER).Add(Serialize(integer->Value()))
  );
}

}  // namespace torchlight::object