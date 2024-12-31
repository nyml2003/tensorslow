#include "object/PyNone.h"
#include "collections/impl/String.h"
#include "object/ByteCode.h"
#include "object/PyBytes.h"
#include "object/PyString.h"

namespace torchlight::object {

using collections::CreateStringWithCString;

NoneKlass::NoneKlass()
  : Klass(collections::CreateStringWithCString("NoneType")) {}

KlassPtr NoneKlass::Self() {
  static KlassPtr instance = std::make_shared<NoneKlass>();
  return instance;
}

PyObjPtr NoneKlass::_serialize_(PyObjPtr obj) {
  if (obj->Klass() != Self()) {
    return nullptr;
  }
  return std::make_shared<PyBytes>(Serialize(Literal::NONE));
}

PyObjPtr NoneKlass::repr(PyObjPtr obj) {
  if (obj->Klass() != Self()) {
    return nullptr;
  }
  return std::make_shared<PyString>(CreateStringWithCString("None"));
}

PyNone::PyNone() : PyObject(NoneKlass::Self()) {}

PyObjPtr PyNone::Instance() {
  static PyObjPtr instance = std::make_shared<PyNone>();
  return instance;
}
}  // namespace torchlight::object