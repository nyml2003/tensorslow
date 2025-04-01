#include "Object/Core/PyObject.h"

#include <utility>
#include "Function/ObjectHelper.h"
#include "Object/Container/PyDictionary.h"
#include "Object/Container/PyList.h"
#include "Object/Core/PyBoolean.h"
#include "Object/Core/PyType.h"
#include "Object/Function/PyNativeFunction.h"
#include "Object/Object.h"
#include "Object/String/PyString.h"
#include "Runtime/Interpreter.h"

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
  return instance;
}

void ObjectKlass::Initialize() {
  if (this->isInitialized) {
    return;
  }
  auto instance = Self();
  instance->SetName(CreatePyString("object")->as<PyString>());
  instance->SetAttributes(CreatePyDict()->as<PyDictionary>());
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
  instance->SetSuper(CreatePyList({})->as<PyList>());
  instance->SetMro(
    CreatePyList({CreatePyType(instance)->as<PyType>()})->as<PyList>()
  );
  instance->SetNative();
  ConfigureBasicAttributes(instance);
  this->isInitialized = true;
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

bool operator<(const PyObjPtr& lhs, const PyObjPtr& rhs) {
  auto ltFunc = lhs->getattr(CreatePyString("__lt__")->as<PyString>());
  if (ltFunc != nullptr) {
    return Runtime::Interpreter::Eval(ltFunc, CreatePyList({rhs})->as<PyList>())
      ->as<PyBoolean>()
      ->Value();
  }
  throw std::runtime_error("TypeError: '<' not supported between instances");
}

}  // namespace torchlight::Object