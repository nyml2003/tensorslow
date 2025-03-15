#include "Object/PyFloat.h"
#include "ByteCode/ByteCode.h"
#include "Collections/BytesHelper.h"
#include "Collections/StringHelper.h"
#include "Object/PyBoolean.h"
#include "Object/PyBytes.h"
#include "Object/PyList.h"
#include "Object/PyString.h"
#include "Object/PyType.h"

namespace torchlight::Object {

PyObjPtr FloatKlass::init(const PyObjPtr& klass, const PyObjPtr& args) {
  if (klass->as<PyType>()->Owner() != Self()) {
    throw std::runtime_error("PyFloat::init(): klass is not a float");
  }
  auto argList = args->as<PyList>();
  if (argList->Length() == 0) {
    return CreatePyFloat(0.0);
  }
  if (argList->Length() != 1) {
    throw std::runtime_error(
      "PyFloat::init(): args must be a list with one element"
    );
  }
  auto value = argList->GetItem(0);
  if (!value->is<PyFloat>()) {
    throw std::runtime_error("PyFloat::init(): value is not a float");
  }
  return value;
}

PyObjPtr FloatKlass::add(const PyObjPtr& lhs, const PyObjPtr& rhs) {
  if (!lhs->is<PyFloat>() || !rhs->is<PyFloat>()) {
    throw std::runtime_error("PyFloat::add(): lhs or rhs is not a float");
  }
  return CreatePyFloat(
    lhs->as<PyFloat>()->Value() + rhs->as<PyFloat>()->Value()
  );
}

PyObjPtr FloatKlass::sub(const PyObjPtr& lhs, const PyObjPtr& rhs) {
  if (!lhs->is<PyFloat>() || !rhs->is<PyFloat>()) {
    throw std::runtime_error("PyFloat::sub(): lhs or rhs is not a float");
  }
  return CreatePyFloat(
    lhs->as<PyFloat>()->Value() - rhs->as<PyFloat>()->Value()
  );
}

PyObjPtr FloatKlass::mul(const PyObjPtr& lhs, const PyObjPtr& rhs) {
  if (!lhs->is<PyFloat>() || !rhs->is<PyFloat>()) {
    throw std::runtime_error("PyFloat::mul(): lhs or rhs is not a float");
  }
  return CreatePyFloat(
    lhs->as<PyFloat>()->Value() * rhs->as<PyFloat>()->Value()
  );
}

PyObjPtr FloatKlass::truediv(const PyObjPtr& lhs, const PyObjPtr& rhs) {
  if (!lhs->is<PyFloat>() || !rhs->is<PyFloat>()) {
    throw std::runtime_error("PyFloat::div(): lhs or rhs is not a float");
  }
  return CreatePyFloat(
    lhs->as<PyFloat>()->Value() / rhs->as<PyFloat>()->Value()
  );
}

PyObjPtr FloatKlass::neg(const PyObjPtr& obj) {
  if (!obj->is<PyFloat>()) {
    throw std::runtime_error("PyFloat::neg(): obj is not a float");
  }
  return CreatePyFloat(-obj->as<PyFloat>()->Value());
}

PyObjPtr FloatKlass::repr(const PyObjPtr& obj) {
  if (!obj->is<PyFloat>()) {
    throw std::runtime_error("PyFloat::repr(): obj is not a float");
  }
  auto floatObj = obj->as<PyFloat>();
  return CreatePyString(Collections::ToString(floatObj->Value()));
}

PyObjPtr FloatKlass::_serialize_(const PyObjPtr& obj) {
  if (obj->Klass() != Self()) {
    throw std::runtime_error("PyFloat::_serialize_(): obj is not a float");
  }
  auto floatObj = std::dynamic_pointer_cast<PyFloat>(obj);
  return CreatePyBytes(Collections::Serialize(Literal::FLOAT)
                         .Add(Collections::Serialize(floatObj->Value())));
}

PyObjPtr FloatKlass::eq(const PyObjPtr& lhs, const PyObjPtr& rhs) {
  if (lhs->Klass() != Self() || rhs->Klass() != Self()) {
    return CreatePyBoolean(false);
  }
  auto left = std::dynamic_pointer_cast<PyFloat>(lhs);
  auto right = std::dynamic_pointer_cast<PyFloat>(rhs);
  return CreatePyBoolean(left->Value() == right->Value());
}

}  // namespace torchlight::Object
