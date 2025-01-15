#include "collections/impl/Integer.h"
#include "collections/impl/String.h"
#include "object/ByteCode.h"
#include "object/PyBoolean.h"
#include "object/PyBytes.h"
#include "object/PyInteger.h"
#include "object/PyString.h"

namespace torchlight::object {

using collections::CreateIntegerOne;
using collections::CreateIntegerZero;
using collections::CreateStringWithCString;

KlassPtr BooleanKlass::Self() {
  static KlassPtr instance = std::make_shared<BooleanKlass>();
  return instance;
}

BooleanKlass::BooleanKlass() : Klass(CreateStringWithCString("bool")) {}

PyBoolean::PyBoolean(bool value)
  : PyInteger(value ? CreateIntegerZero() : CreateIntegerOne()) {
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
    return nullptr;
  }
  auto boolean = std::dynamic_pointer_cast<PyBoolean>(obj);
  if (boolean->Value()) {
    return CreatePyBytes(Serialize(Literal::TRUE));
  }
  return CreatePyBytes(Serialize(Literal::FALSE));
}

PyObjPtr BooleanKlass::repr(PyObjPtr obj) {
  if (obj->Klass() != Self()) {
    return nullptr;
  }
  auto boolean = std::dynamic_pointer_cast<PyBoolean>(obj);
  return CreatePyString(
    CreateStringWithCString("<bool ")
      .Add(CreateStringWithCString(boolean->Value() ? "True" : "False"))
      .Add(CreateStringWithCString(">"))
  );
}

}  // namespace torchlight::object