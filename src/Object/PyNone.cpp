#include "Object/PyNone.h"
#include "ByteCode/ByteCode.h"
#include "Collections/StringHelper.h"
#include "Object/PyBytes.h"
#include "Object/PyDictionary.h"
#include "Object/PyString.h"
#include "Object/PyType.h"

namespace torchlight::Object {

NoneKlass::NoneKlass() = default;

KlassPtr NoneKlass::Self() {
  static KlassPtr instance = std::make_shared<NoneKlass>();
  return instance;
}

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
  return CreatePyString(Collections::CreateStringWithCString("None"));
}

PyNone::PyNone() : PyObject(NoneKlass::Self()) {}

PyObjPtr PyNone::Instance() {
  static PyObjPtr instance = std::make_shared<PyNone>();
  return instance;
}

PyObjPtr CreatePyNone() {
  return PyNone::Instance();
}

void NoneKlass::Initialize() {
  SetType(CreatePyType(Self()));
  SetAttributes(CreatePyDict());
  SetName(CreatePyString("None"));
  Klass::Initialize();
}

}  // namespace torchlight::Object