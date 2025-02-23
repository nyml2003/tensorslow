#include "Object/PyFloat.h"
#include "ByteCode/ByteCode.h"
#include "Collections/BytesHelper.h"
#include "Collections/StringHelper.h"
#include "Object/PyBoolean.h"
#include "Object/PyBytes.h"
#include "Object/PyDictionary.h"
#include "Object/PyString.h"
#include "Object/PyType.h"

namespace torchlight::Object {

PyFloat::PyFloat(double value) : PyObject(FloatKlass::Self()), value(value) {}

double PyFloat::Value() const {
  return value;
}

PyObjPtr CreatePyFloat(double value) {
  return std::make_shared<PyFloat>(value);
}

FloatKlass::FloatKlass() = default;

void FloatKlass::Initialize() {
  SetType(CreatePyType(Self()));
  SetName(CreatePyString("float"));
  SetAttributes(CreatePyDict());
  Klass::Initialize();
}

KlassPtr FloatKlass::Self() {
  static KlassPtr instance = std::make_shared<FloatKlass>();
  return instance;
}

PyObjPtr
FloatKlass::allocateInstance(const PyObjPtr& klass, const PyObjPtr& args) {
  if (Self()->Type() != klass) {
    throw std::runtime_error("PyFloat::allocateInstance(): klass is not a float"
    );
  }
  if (ToU64(args->len()) == 0) {
    return CreatePyFloat(0.0);
  }
  if (args->len() != CreatePyInteger(1)) {
    throw std::runtime_error(
      "PyFloat::allocateInstance(): args must be a list with one element"
    );
  }
  auto value = args->getitem(CreatePyInteger(0));
  if (value->Klass() != FloatKlass::Self()) {
    throw std::runtime_error("PyFloat::allocateInstance(): value is not a float"
    );
  }
  return value;
}

PyObjPtr FloatKlass::add(const PyObjPtr& lhs, const PyObjPtr& rhs) {
  if (lhs->Klass() != Self() || rhs->Klass() != Self()) {
    throw std::runtime_error("PyFloat::add(): lhs or rhs is not a float");
  }
  auto left = std::dynamic_pointer_cast<PyFloat>(lhs);
  auto right = std::dynamic_pointer_cast<PyFloat>(rhs);
  return CreatePyFloat(left->Value() + right->Value());
}

PyObjPtr FloatKlass::sub(const PyObjPtr& lhs, const PyObjPtr& rhs) {
  if (lhs->Klass() != Self() || rhs->Klass() != Self()) {
    throw std::runtime_error("PyFloat::sub(): lhs or rhs is not a float");
  }
  auto left = std::dynamic_pointer_cast<PyFloat>(lhs);
  auto right = std::dynamic_pointer_cast<PyFloat>(rhs);
  return CreatePyFloat(left->Value() - right->Value());
}

PyObjPtr FloatKlass::mul(const PyObjPtr& lhs, const PyObjPtr& rhs) {
  if (lhs->Klass() != Self() || rhs->Klass() != Self()) {
    throw std::runtime_error("PyFloat::mul(): lhs or rhs is not a float");
  }
  auto left = std::dynamic_pointer_cast<PyFloat>(lhs);
  auto right = std::dynamic_pointer_cast<PyFloat>(rhs);
  return CreatePyFloat(left->Value() * right->Value());
}

PyObjPtr FloatKlass::div(const PyObjPtr& lhs, const PyObjPtr& rhs) {
  if (lhs->Klass() != Self() || rhs->Klass() != Self()) {
    throw std::runtime_error("PyFloat::div(): lhs or rhs is not a float");
  }
  auto left = std::dynamic_pointer_cast<PyFloat>(lhs);
  auto right = std::dynamic_pointer_cast<PyFloat>(rhs);
  return CreatePyFloat(left->Value() / right->Value());
}

PyObjPtr FloatKlass::repr(const PyObjPtr& obj) {
  if (obj->Klass() != Self()) {
    throw std::runtime_error("PyFloat::repr(): obj is not a float");
  }
  auto floatObj = std::dynamic_pointer_cast<PyFloat>(obj);
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
