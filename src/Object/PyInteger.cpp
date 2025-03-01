#include "Object/PyInteger.h"
#include "ByteCode/ByteCode.h"
#include "Collections/BytesHelper.h"
#include "Collections/IntegerHelper.h"
#include "Object/PyBoolean.h"
#include "Object/PyBytes.h"
#include "Object/PyList.h"
#include "Object/PyString.h"
#include "Object/PyType.h"

namespace torchlight::Object {

PyObjPtr CreatePyInteger(Collections::Integer value) {
  return std::make_shared<PyInteger>(value);
}

PyObjPtr CreatePyInteger(uint64_t value) {
  return std::make_shared<PyInteger>(Collections::CreateIntegerWithU64(value));
}

PyObjPtr IntegerKlass::construct(const PyObjPtr& klass, const PyObjPtr& args) {
  if (klass->as<PyType>()->Owner() != Self()) {
    throw std::runtime_error("PyInteger::construct(): klass is not an integer");
  }
  auto argList = args->as<PyList>();
  if (argList->Length() == 0) {
    return CreatePyInteger(Collections::CreateIntegerZero());
  }
  if (argList->Length() != 1) {
    throw std::runtime_error(
      "PyInteger::construct(): args must be a list with one element"
    );
  }
  auto value = argList->GetItem(0);
  if (!value->is<PyInteger>()) {
    throw std::runtime_error("PyInteger::construct(): value is not an integer");
  }
  return value;
}

PyObjPtr IntegerKlass::add(const PyObjPtr& lhs, const PyObjPtr& rhs) {
  if (lhs->Klass() != Self() || rhs->Klass() != Self()) {
    throw std::runtime_error("PyInteger::add(): lhs or rhs is not an integer");
  }
  auto left = std::dynamic_pointer_cast<PyInteger>(lhs);
  auto right = std::dynamic_pointer_cast<PyInteger>(rhs);
  return CreatePyInteger(left->value.Add(right->value));
}

PyObjPtr IntegerKlass::sub(const PyObjPtr& lhs, const PyObjPtr& rhs) {
  if (lhs->Klass() != Self() || rhs->Klass() != Self()) {
    throw std::runtime_error("PyInteger::sub(): lhs or rhs is not an integer");
  }
  auto left = std::dynamic_pointer_cast<PyInteger>(lhs);
  auto right = std::dynamic_pointer_cast<PyInteger>(rhs);
  return CreatePyInteger(left->value.Subtract(right->value));
}

PyObjPtr IntegerKlass::mul(const PyObjPtr& lhs, const PyObjPtr& rhs) {
  if (lhs->Klass() != Self() || rhs->Klass() != Self()) {
    throw std::runtime_error("PyInteger::mul(): lhs or rhs is not an integer");
  }
  auto left = std::dynamic_pointer_cast<PyInteger>(lhs);
  auto right = std::dynamic_pointer_cast<PyInteger>(rhs);
  return CreatePyInteger(left->value.Multiply(right->value));
}

PyObjPtr IntegerKlass::div(const PyObjPtr& lhs, const PyObjPtr& rhs) {
  if (lhs->Klass() != Self() || rhs->Klass() != Self()) {
    throw std::runtime_error("PyInteger::div(): lhs or rhs is not an integer");
  }
  auto left = std::dynamic_pointer_cast<PyInteger>(lhs);
  auto right = std::dynamic_pointer_cast<PyInteger>(rhs);
  return CreatePyInteger(left->value.Divide(right->value));
}

PyObjPtr IntegerKlass::repr(const PyObjPtr& obj) {
  if (obj->Klass() != Self()) {
    throw std::runtime_error("PyInteger::repr(): obj is not an integer");
  }
  auto integer = std::dynamic_pointer_cast<PyInteger>(obj);
  return CreatePyString((integer->value).ToString());
}

PyObjPtr IntegerKlass::gt(const PyObjPtr& lhs, const PyObjPtr& rhs) {
  if (lhs->Klass() != Self() || rhs->Klass() != Self()) {
    throw std::runtime_error("PyInteger::gt(): lhs or rhs is not an integer");
  }
  auto left = std::dynamic_pointer_cast<PyInteger>(lhs);
  auto right = std::dynamic_pointer_cast<PyInteger>(rhs);
  return CreatePyBoolean(left->value.GreaterThan(right->value));
}

PyObjPtr IntegerKlass::eq(const PyObjPtr& lhs, const PyObjPtr& rhs) {
  if (lhs->Klass() != Self() || rhs->Klass() != Self()) {
    throw std::runtime_error("PyInteger::eq(): lhs or rhs is not an integer");
  }
  auto left = std::dynamic_pointer_cast<PyInteger>(lhs);
  auto right = std::dynamic_pointer_cast<PyInteger>(rhs);
  return CreatePyBoolean(left->value.Equal(right->value));
}

PyObjPtr IntegerKlass::_serialize_(const PyObjPtr& obj) {
  if (obj->Klass() != Self()) {
    throw std::runtime_error("PyInteger::_serialize_(): obj is not an integer");
  }
  auto integer = std::dynamic_pointer_cast<PyInteger>(obj);
  if (integer->value.IsZero()) {
    return CreatePyBytes(Collections::Serialize(Literal::ZERO));
  }
  return CreatePyBytes(Collections::Serialize(Literal::INTEGER)
                         .Add(Collections::Serialize(integer->value)));
}

}  // namespace torchlight::Object