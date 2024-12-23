#include "object/PyBoolean.h"
#include "object/PyInteger.h"

namespace torchlight::object {

KlassPtr BooleanKlass::Self() {
  static KlassPtr instance = std::make_shared<BooleanKlass>();
  return instance;
}

BooleanKlass::BooleanKlass() : Klass(String("bool")) {}

PyObjPtr BooleanKlass::_bool_(PyObjPtr obj) {
  return obj;
}

PyBoolean::PyBoolean(bool value)
  : PyInteger(value ? Integer(String("1")) : Integer(String("0"))) {
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

}  // namespace torchlight::object