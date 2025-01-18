#include "Collections/IntegerHelper.h"
#include "Collections/StringHelper.h"
#include "Object/ByteCode.h"
#include "Object/MixinCollections.h"
#include "Object/PyBoolean.h"
#include "Object/PyBytes.h"
#include "Object/PyInteger.h"
#include "Object/PyString.h"


namespace torchlight::Object {

KlassPtr BooleanKlass::Self() {
  static KlassPtr instance = std::make_shared<BooleanKlass>();
  return instance;
}

BooleanKlass::BooleanKlass()
  : Klass(Collections::CreateStringWithCString("bool")) {}

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

PyBoolPtr CreatePyBoolean(bool value) {
  return value ? PyBoolean::True() : PyBoolean::False();
}

bool PyBoolean::Value() const {
  return PyInteger::Value().IsZero();
}

PyObjPtr BooleanKlass::_bool_(PyObjPtr obj) {
  return obj;
}

PyObjPtr BooleanKlass::_serialize_(PyObjPtr obj) {
  if (obj->Klass() != Self()) {
    throw std::runtime_error("PyBoolean::_serialize_(): obj is not a bool");
  }
  auto boolean = std::dynamic_pointer_cast<PyBoolean>(obj);
  if (boolean->Value()) {
    return CreatePyBytes(Collections::Serialize(Literal::TRUE));
  }
  return CreatePyBytes(Collections::Serialize(Literal::FALSE));
}

PyObjPtr BooleanKlass::repr(PyObjPtr obj) {
  if (obj->Klass() != Self()) {
    throw std::runtime_error("PyBoolean::repr(): obj is not a bool");
  }
  auto boolean = std::dynamic_pointer_cast<PyBoolean>(obj);
  return CreatePyString(
    Collections::CreateStringWithCString(boolean->Value() ? "True" : "False")
  );
}

PyObjPtr BooleanKlass::eq(PyObjPtr lhs, PyObjPtr rhs) {
  if (lhs->Klass() != Self() || rhs->Klass() != Self()) {
    return CreatePyBoolean(false);
  }
  auto left = std::dynamic_pointer_cast<PyBoolean>(lhs);
  auto right = std::dynamic_pointer_cast<PyBoolean>(rhs);
  return CreatePyBoolean(left->Value() == right->Value());
}

}  // namespace torchlight::Object