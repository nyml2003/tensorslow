#include "Object/PyObject.h"

#include <utility>
#include "Function/PyNativeFunction.h"
#include "Object/Object.h"
#include "Object/ObjectHelper.h"
#include "Object/PyBoolean.h"
#include "Object/PyDictionary.h"
#include "Object/PyList.h"
#include "Object/PyString.h"
#include "Object/PyType.h"

namespace torchlight::Object {

PyObject::PyObject(KlassPtr klass) : klass(std::move(klass)) {}

PyDictPtr PyObject::Attributes() {
  if (attributes == nullptr) {
    attributes = CreatePyDict()->as<PyDictionary>();
  }
  return attributes;
}

PyObjPtr ObjectInit(const PyObjPtr& args) {
  CheckNativeFunctionArgumentsWithExpectedLength(args, 1);
  auto self = args->as<PyList>()->GetItem(0);
  auto klass = self->Klass();
  auto instance = std::make_shared<PyObject>(klass);
  return instance;
}

KlassPtr ObjectKlass::Self() {
  static KlassPtr instance = std::make_shared<ObjectKlass>();
  instance->SetName(CreatePyString("object")->as<PyString>());
  instance->SetAttributes(CreatePyDict());
  instance->AddAttribute(
    CreatePyString("__init__")->as<PyString>(),
    CreatePyNativeFunction(ObjectInit)
  );
  instance->AddAttribute(
    CreatePyString("__str__")->as<PyString>(), CreatePyNativeFunction(KlassStr)
  );
  instance->AddAttribute(
    CreatePyString("__repr__")->as<PyString>(),
    CreatePyNativeFunction(KlassRepr)
  );
  instance->AddAttribute(
    CreatePyString("__bool__")->as<PyString>(),
    CreatePyNativeFunction(KlassBool)
  );
  instance->SetType(CreatePyType(instance)->as<PyType>());
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