#include "Object/PyBoolean.h"
#include "ByteCode/ByteCode.h"
#include "Collections/IntegerHelper.h"
#include "Collections/StringHelper.h"
#include "Object/PyBytes.h"
#include "Object/PyDictionary.h"
#include "Object/PyInteger.h"
#include "Object/PyString.h"
#include "Object/PyType.h"

namespace torchlight::Object {

KlassPtr BooleanKlass::Self() {
  static KlassPtr instance = std::make_shared<BooleanKlass>();
  return instance;
}

BooleanKlass::BooleanKlass() = default;

void BooleanKlass::Initialize() {
  SetType(CreatePyType(Self()));
  SetName(CreatePyString("bool"));
  SetAttributes(CreatePyDict());
  Klass::Initialize();
}

PyBoolean::PyBoolean(bool value)
  : PyInteger(
      value ? Collections::CreateIntegerZero() : Collections::CreateIntegerOne()
    ) {
  setKlass(BooleanKlass::Self());
}

PyBoolPtr PyBoolean::True() {
  static PyBoolPtr instance = std::make_shared<PyBoolean>(true);
  return instance;
}

PyBoolPtr PyBoolean::False() {
  static PyBoolPtr instance = std::make_shared<PyBoolean>(false);
  return instance;
}

PyObjPtr CreatePyBoolean(bool value) {
  return value ? PyBoolean::True() : PyBoolean::False();
}

bool PyBoolean::Value() const {
  return PyInteger::Value().IsZero();
}

PyObjPtr BooleanKlass::_bool_(const PyObjPtr& obj) {
  return obj;
}

PyObjPtr BooleanKlass::_serialize_(const PyObjPtr& obj) {
  if (obj->Klass() != Self()) {
    throw std::runtime_error("PyBoolean::_serialize_(): obj is not a bool");
  }
  auto boolean = std::dynamic_pointer_cast<PyBoolean>(obj);
  if (boolean->Value()) {
    return CreatePyBytes(Collections::Serialize(Literal::TRUE));
  }
  return CreatePyBytes(Collections::Serialize(Literal::FALSE));
}

PyObjPtr BooleanKlass::repr(const PyObjPtr& obj) {
  if (obj->Klass() != Self()) {
    throw std::runtime_error("PyBoolean::repr(): obj is not a bool");
  }
  auto boolean = std::dynamic_pointer_cast<PyBoolean>(obj);
  return CreatePyString(
    Collections::CreateStringWithCString(boolean->Value() ? "True" : "False")
  );
}

PyObjPtr BooleanKlass::eq(const PyObjPtr& lhs, const PyObjPtr& rhs) {
  if (lhs->Klass() != Self() || rhs->Klass() != Self()) {
    return CreatePyBoolean(false);
  }
  auto left = std::dynamic_pointer_cast<PyBoolean>(lhs);
  auto right = std::dynamic_pointer_cast<PyBoolean>(rhs);
  return CreatePyBoolean(left->Value() == right->Value());
}

bool IsTrue(const PyObjPtr& obj) {
  auto booleanObj = obj->_bool_();
  if (booleanObj->Klass() != BooleanKlass::Self()) {
    throw std::runtime_error("Cannot get value of non-boolean object");
  }
  auto boolean = std::dynamic_pointer_cast<PyBoolean>(booleanObj);
  return boolean->Value();
}

PyObjPtr Not(const PyObjPtr& obj) {
  return CreatePyBoolean(!IsTrue(obj));
}

PyObjPtr And(const PyObjPtr& lhs, const PyObjPtr& rhs) {
  return CreatePyBoolean(IsTrue(lhs) && IsTrue(rhs));
}

PyObjPtr Or(const PyObjPtr& lhs, const PyObjPtr& rhs) {
  return CreatePyBoolean(IsTrue(lhs) || IsTrue(rhs));
}

}  // namespace torchlight::Object