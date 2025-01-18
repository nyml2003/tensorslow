#include "Collections/BytesHelper.h"
#include "Collections/IntegerHelper.h"
#include "Collections/StringHelper.h"
#include "Object/ByteCode.h"
#include "Object/PyBoolean.h"
#include "Object/PyBytes.h"
#include "Object/PyInteger.h"
#include "Object/PyString.h"

namespace torchlight::Object {

PyInteger::PyInteger(Collections::Integer value)
  : PyObject(IntegerKlass::Self()), value(std::move(value)) {}

[[nodiscard]]

Collections::Integer PyInteger::Value() const {
  return value;
}

PyIntPtr CreatePyInteger(Collections::Integer value) {
  return std::make_shared<PyInteger>(value);
}

PyIntPtr CreatePyInteger(uint64_t value) {
  return std::make_shared<PyInteger>(Collections::CreateIntegerWithU64(value));
}

IntegerKlass::IntegerKlass()
  : Klass(Collections::CreateStringWithCString("int")) {}

IntegerKlass::~IntegerKlass() = default;

KlassPtr IntegerKlass::Self() {
  static KlassPtr instance = std::make_shared<IntegerKlass>();
  return instance;
}

PyObjPtr IntegerKlass::add(PyObjPtr lhs, PyObjPtr rhs) {
  if (lhs->Klass() != Self() || rhs->Klass() != Self()) {
    throw std::runtime_error("PyInteger::add(): lhs or rhs is not an integer");
  }
  auto left = std::dynamic_pointer_cast<PyInteger>(lhs);
  auto right = std::dynamic_pointer_cast<PyInteger>(rhs);
  return CreatePyInteger(left->Value().Add(right->Value()));
}

PyObjPtr IntegerKlass::sub(PyObjPtr lhs, PyObjPtr rhs) {
  if (lhs->Klass() != Self() || rhs->Klass() != Self()) {
    throw std::runtime_error("PyInteger::sub(): lhs or rhs is not an integer");
  }
  auto left = std::dynamic_pointer_cast<PyInteger>(lhs);
  auto right = std::dynamic_pointer_cast<PyInteger>(rhs);
  return CreatePyInteger(left->Value().Subtract(right->Value()));
}

PyObjPtr IntegerKlass::mul(PyObjPtr lhs, PyObjPtr rhs) {
  if (lhs->Klass() != Self() || rhs->Klass() != Self()) {
    throw std::runtime_error("PyInteger::mul(): lhs or rhs is not an integer");
  }
  auto left = std::dynamic_pointer_cast<PyInteger>(lhs);
  auto right = std::dynamic_pointer_cast<PyInteger>(rhs);
  return CreatePyInteger(left->Value().Multiply(right->Value()));
}

PyObjPtr IntegerKlass::div(PyObjPtr lhs, PyObjPtr rhs) {
  if (lhs->Klass() != Self() || rhs->Klass() != Self()) {
    throw std::runtime_error("PyInteger::div(): lhs or rhs is not an integer");
  }
  auto left = std::dynamic_pointer_cast<PyInteger>(lhs);
  auto right = std::dynamic_pointer_cast<PyInteger>(rhs);
  return CreatePyInteger(left->Value().Divide(right->Value()));
}

PyObjPtr IntegerKlass::repr(PyObjPtr obj) {
  if (obj->Klass() != Self()) {
    throw std::runtime_error("PyInteger::repr(): obj is not an integer");
  }
  auto integer = std::dynamic_pointer_cast<PyInteger>(obj);
  return CreatePyString((integer->Value().ToString()));
}

PyObjPtr IntegerKlass::gt(PyObjPtr lhs, PyObjPtr rhs) {
  if (lhs->Klass() != Self() || rhs->Klass() != Self()) {
    throw std::runtime_error("PyInteger::gt(): lhs or rhs is not an integer");
  }
  auto left = std::dynamic_pointer_cast<PyInteger>(lhs);
  auto right = std::dynamic_pointer_cast<PyInteger>(rhs);
  return CreatePyBoolean(left->Value().GreaterThan(right->Value()));
}

PyObjPtr IntegerKlass::lt(PyObjPtr lhs, PyObjPtr rhs) {
  if (lhs->Klass() != Self() || rhs->Klass() != Self()) {
    throw std::runtime_error("PyInteger::lt(): lhs or rhs is not an integer");
  }
  auto left = std::dynamic_pointer_cast<PyInteger>(lhs);
  auto right = std::dynamic_pointer_cast<PyInteger>(rhs);
  return CreatePyBoolean(left->Value().LessThan(right->Value()));
}

PyObjPtr IntegerKlass::eq(PyObjPtr lhs, PyObjPtr rhs) {
  if (lhs->Klass() != Self() || rhs->Klass() != Self()) {
    throw std::runtime_error("PyInteger::eq(): lhs or rhs is not an integer");
  }
  auto left = std::dynamic_pointer_cast<PyInteger>(lhs);
  auto right = std::dynamic_pointer_cast<PyInteger>(rhs);
  return CreatePyBoolean(left->Value().Equal(right->Value()));
}

PyObjPtr IntegerKlass::ge(PyObjPtr lhs, PyObjPtr rhs) {
  if (lhs->Klass() != Self() || rhs->Klass() != Self()) {
    throw std::runtime_error("PyInteger::ge(): lhs or rhs is not an integer");
  }
  auto left = std::dynamic_pointer_cast<PyInteger>(lhs);
  auto right = std::dynamic_pointer_cast<PyInteger>(rhs);
  return CreatePyBoolean(left->Value().GreaterThanOrEqual(right->Value()));
}

PyObjPtr IntegerKlass::le(PyObjPtr lhs, PyObjPtr rhs) {
  if (lhs->Klass() != Self() || rhs->Klass() != Self()) {
    throw std::runtime_error("PyInteger::le(): lhs or rhs is not an integer");
  }
  auto left = std::dynamic_pointer_cast<PyInteger>(lhs);
  auto right = std::dynamic_pointer_cast<PyInteger>(rhs);
  return CreatePyBoolean(left->Value().LessThanOrEqual(right->Value()));
}

PyObjPtr IntegerKlass::ne(PyObjPtr lhs, PyObjPtr rhs) {
  if (lhs->Klass() != Self() || rhs->Klass() != Self()) {
    throw std::runtime_error("PyInteger::ne(): lhs or rhs is not an integer");
  }
  auto left = std::dynamic_pointer_cast<PyInteger>(lhs);
  auto right = std::dynamic_pointer_cast<PyInteger>(rhs);
  return CreatePyBoolean(left->Value().NotEqual(right->Value()));
}

PyObjPtr IntegerKlass::_serialize_(PyObjPtr obj) {
  if (obj->Klass() != Self()) {
    throw std::runtime_error("PyInteger::_serialize_(): obj is not an integer");
  }
  auto integer = std::dynamic_pointer_cast<PyInteger>(obj);
  if (integer->Value().IsZero()) {
    return CreatePyBytes(Collections::Serialize(Literal::ZERO));
  }
  return CreatePyBytes(Collections::Serialize(Literal::INTEGER)
                         .Add(Collections::Serialize(integer->Value())));
}

}  // namespace torchlight::Object