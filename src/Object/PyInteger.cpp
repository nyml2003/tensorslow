#include "Object/PyInteger.h"
#include "ByteCode/ByteCode.h"
#include "Collections/BytesHelper.h"
#include "Collections/IntegerHelper.h"
#include "Collections/StringHelper.h"
#include "Object/Common.h"
#include "Object/PyBoolean.h"
#include "Object/PyBytes.h"
#include "Object/PyDictionary.h"
#include "Object/PyString.h"
#include "Object/PyType.h"

namespace torchlight::Object {

PyInteger::PyInteger(Collections::Integer value)
  : PyObject(IntegerKlass::Self()), value(std::move(value)) {}

[[nodiscard]]

Collections::Integer PyInteger::Value() const {
  return value;
}

PyObjPtr CreatePyInteger(Collections::Integer value) {
  return std::make_shared<PyInteger>(value);
}

PyObjPtr CreatePyInteger(uint64_t value) {
  return std::make_shared<PyInteger>(Collections::CreateIntegerWithU64(value));
}

uint64_t ToU64(const PyObjPtr& obj) {
  if (obj->Klass() != IntegerKlass::Self()) {
    throw std::runtime_error("PyInteger::ToU64(): obj is not an integer");
  }
  auto integer = std::dynamic_pointer_cast<PyInteger>(obj);
  return ToU64(integer->Value());
}

IntegerKlass::IntegerKlass() = default;

void IntegerKlass::Initialize() {
  SetType(CreatePyType(Self()));
  SetName(CreatePyString("int"));
  SetAttributes(CreatePyDict());
  Klass::Initialize();
}

IntegerKlass::~IntegerKlass() = default;

KlassPtr IntegerKlass::Self() {
  static KlassPtr instance = std::make_shared<IntegerKlass>();
  return instance;
}

PyObjPtr IntegerKlass::allocateInstance(PyObjPtr klass, PyObjPtr args) {
  if (Self()->Type() != klass) {
    throw std::runtime_error(
      "PyInteger::allocateInstance(): klass is not an integer"
    );
  }
  if (ToU64(args->len()) == 0) {
    return CreatePyInteger(Collections::CreateIntegerZero());
  }
  if (args->len() != CreatePyInteger(1)) {
    throw std::runtime_error(
      "PyInteger::allocateInstance(): args must be a list with one element"
    );
  }
  auto value = args->getitem(CreatePyInteger(0));
  if (value->Klass() != IntegerKlass::Self()) {
    throw std::runtime_error(
      "PyInteger::allocateInstance(): value is not an integer"
    );
  }
  return value;
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

PyObjPtr IntegerKlass::eq(PyObjPtr lhs, PyObjPtr rhs) {
  if (lhs->Klass() != Self() || rhs->Klass() != Self()) {
    throw std::runtime_error("PyInteger::eq(): lhs or rhs is not an integer");
  }
  auto left = std::dynamic_pointer_cast<PyInteger>(lhs);
  auto right = std::dynamic_pointer_cast<PyInteger>(rhs);
  return CreatePyBoolean(left->Value().Equal(right->Value()));
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