#include "Collections/StringHelper.h"
#include "Object/ByteCode.h"
#include "Object/PyBytes.h"
#include "Object/PyNone.h"
#include "Object/PyString.h"

namespace torchlight::Object {

NoneKlass::NoneKlass()
  : Klass(Collections::CreateStringWithCString("NoneType")) {}

KlassPtr NoneKlass::Self() {
  static KlassPtr instance = std::make_shared<NoneKlass>();
  return instance;
}

PyObjPtr NoneKlass::_serialize_(PyObjPtr obj) {
  if (obj->Klass() != Self()) {
    throw std::runtime_error("NoneType does not support serialization");
  }
  return CreatePyBytes(Collections::Serialize(Literal::NONE));
}

PyObjPtr NoneKlass::repr(PyObjPtr obj) {
  if (obj->Klass() != Self()) {
    throw std::runtime_error("NoneType does not support repr operation");
  }
  return CreatePyString(Collections::CreateStringWithCString("None"));
}

PyNone::PyNone() : PyObject(NoneKlass::Self()) {}

PyObjPtr PyNone::Instance() {
  static PyObjPtr instance = std::make_shared<PyNone>();
  return instance;
}

PyNonePtr CreatePyNone() {
  return std::make_shared<PyNone>();
}
}  // namespace torchlight::Object