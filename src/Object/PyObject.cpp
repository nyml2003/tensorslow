#include "Object/PyObject.h"
#include "Function/PyNativeFunction.h"
#include "Object/PyBoolean.h"
#include "Object/PyList.h"
#include "Object/PyNone.h"
#include "Object/PyString.h"

namespace torchlight::Object {

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

void DebugPrint(const PyObjPtr& obj) {
  obj->str()->as<PyString>()->PrintLine();
}

PyObjPtr Print(const PyObjPtr& args) {
  CheckNativeFunctionArguments(args);
  auto argList = args->as<PyList>();
  CreatePyString(" ")->as<PyString>()->Join(argList)->PrintLine();
  return CreatePyNone();
}

PyObjPtr Len(const PyObjPtr& args) {
  CheckNativeFunctionArgumentsWithExpectedLength(args, 1);
  auto value = args->as<PyList>()->GetItem(0);
  return value->len();
}

KlassPtr ObjectKlass::Self() {
  static KlassPtr instance = std::make_shared<ObjectKlass>();
  LoadClass(CreatePyString("object")->as<PyString>(), instance);
  ConfigureBasicAttributes(instance);
  return instance;
}

}  // namespace torchlight::Object