#include "Object/PyObject.h"
#include "Object/Object.h"
#include "Object/ObjectHelper.h"
#include "Object/PyBoolean.h"
#include "Object/PyDictionary.h"
#include "Object/PyList.h"
#include "Object/PyString.h"
#include "Object/PyType.h"

namespace torchlight::Object {

KlassPtr ObjectKlass::Self() {
  static KlassPtr instance = std::make_shared<ObjectKlass>();
  instance->SetName(CreatePyString("object")->as<PyString>());
  instance->SetAttributes(CreatePyDict());
  instance->SetType(CreatePyType(instance));
  instance->SetSuper(CreatePyList({}));
  instance->SetMro(CreatePyList({CreatePyType(instance)->as<PyType>()}));
  instance->SetNative();
  ConfigureBasicAttributes(instance);
  return instance;
}

PyObjPtr PyObject::Instance() {
  static PyObjPtr instance = std::make_shared<PyObject>(ObjectKlass::Self());
  return instance;
}

bool operator==(const PyObjPtr& lhs, const PyObjPtr& rhs) {
  if (lhs.get() == rhs.get()) {
    return true;
  }
  if (lhs->Klass() != rhs->Klass()) {
    return false;
  }
  auto equal = lhs->eq(rhs);
  return equal->as<PyBoolean>()->Value();
}

bool operator!=(const PyObjPtr& lhs, const PyObjPtr& rhs) {
  return !(lhs == rhs);
}

}  // namespace torchlight::Object