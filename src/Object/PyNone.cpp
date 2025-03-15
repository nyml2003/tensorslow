#include "Object/PyNone.h"
#include "ByteCode/ByteCode.h"
#include "Object/PyBoolean.h"
#include "Object/PyBytes.h"
#include "Object/PyString.h"

namespace torchlight::Object {

PyObjPtr NoneKlass::_serialize_(const PyObjPtr& obj) {
  if (obj->Klass() != Self()) {
    throw std::runtime_error("NoneType does not support serialization");
  }
  return CreatePyBytes(Collections::Serialize(Literal::NONE));
}

PyObjPtr NoneKlass::repr(const PyObjPtr& obj) {
  if (obj->Klass() != Self()) {
    throw std::runtime_error("NoneType does not support repr operation");
  }
  return CreatePyString("None");
}

PyObjPtr NoneKlass::eq(const PyObjPtr& lhs, const PyObjPtr& rhs) {
  if (lhs->is<PyNone>() && rhs->is<PyNone>()) {
    return CreatePyBoolean(true);
  }
  return CreatePyBoolean(false);
}

PyNone::PyNone() : PyObject(NoneKlass::Self()) {}

PyObjPtr PyNone::Instance() {
  static PyObjPtr instance = std::make_shared<PyNone>();
  return instance;
}

}  // namespace torchlight::Object