#include "Object/Core/PyNone.h"
#include "ByteCode/ByteCode.h"
#include "Object/Core/PyBoolean.h"
#include "Object/String/PyBytes.h"
#include "Object/String/PyString.h"

namespace torchlight::Object {

PyObjPtr NoneKlass::_serialize_(const PyObjPtr& obj) {
  if (!obj->is<PyNone>()) {
    throw std::runtime_error("NoneType does not support serialization");
  }
  return CreatePyBytes(Collections::Serialize(Literal::NONE));
}

PyObjPtr NoneKlass::repr(const PyObjPtr& obj) {
  if (!obj->is<PyNone>()) {
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

PyObjPtr NoneKlass::boolean(const PyObjPtr& obj) {
  if (!obj->is<PyNone>()) {
    throw std::runtime_error("NoneType does not support boolean operation");
  }
  return CreatePyBoolean(false);
}

PyNone::PyNone() : PyObject(NoneKlass::Self()) {}

PyObjPtr PyNone::Instance() {
  static PyObjPtr instance = std::make_shared<PyNone>();
  return instance;
}

}  // namespace torchlight::Object