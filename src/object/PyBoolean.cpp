#include "object/PyBoolean.h"
#include "collections/impl/Integer.h"
#include "collections/impl/String.h"
#include "object/ByteCode.h"
#include "object/PyBytes.h"
#include "object/PyInteger.h"

namespace torchlight::object {

using collections::Bytes;

KlassPtr BooleanKlass::Self() {
  static KlassPtr instance = std::make_shared<BooleanKlass>();
  return instance;
}

BooleanKlass::BooleanKlass()
  : Klass(collections::CreateStringWithCString("bool")) {}

PyObjPtr BooleanKlass::_bool_(PyObjPtr obj) {
  return obj;
}

PyBoolean::PyBoolean(bool value)
  : PyInteger(
      value ? collections::CreateIntegerZero() : collections::CreateIntegerOne()
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

PyBoolPtr PyBoolean::Constant(bool value) {
  return value ? True() : False();
}

bool PyBoolean::Value() const {
  return PyInteger::Value().IsZero();
}

PyObjPtr BooleanKlass::_serialize_(PyObjPtr obj) {
  if (obj->Klass() != Self()) {
    return nullptr;
  }
  auto b = std::dynamic_pointer_cast<PyBoolean>(obj);
  if (b->Value()) {
    return std::make_shared<PyBytes>(Serialize(Literal::TRUE));
  }
  return std::make_shared<PyBytes>(Serialize(Literal::FALSE));
}

}  // namespace torchlight::object