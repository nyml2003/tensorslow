#include "Function/PyNativeFunction.h"
#include "Object/PyInteger.h"
#include "Object/PyList.h"
#include "Object/ObjectHelper.h"

namespace torchlight::Object {

PyObjPtr PyNativeFunction::Call(const PyObjPtr& args) {
  return nativeFunction(args);
}

void CheckNativeFunctionArgumentsWithExpectedLength(
  const PyObjPtr& args,
  Index expected
) {
  CheckNativeFunctionArguments(args);
  auto list = args->as<PyList>();
  if (list->Length() != expected) {
    auto errorMessage = StringConcat(CreatePyList(
      {CreatePyString("Check Native Function Arguments With Expected Length: "),
       CreatePyInteger(expected)->str(), CreatePyString(" Expected, but got "),
       CreatePyInteger(list->Length())->str()}
    ));
    throw std::runtime_error(errorMessage->str()->as<PyString>()->ToCppString()
    );
  }
}

void CheckNativeFunctionArguments(const PyObjPtr& args) {
  if (args->is<PyList>()) {
    return;
  }
  auto errorMessage = StringConcat(CreatePyList(
    {CreatePyString("Check Native Function (Name: "), args->str(),
     CreatePyString(") Arguments: Expected a list, but got "),
     args->Klass()->Name()}
  ));
  throw std::runtime_error(errorMessage->str()->as<PyString>()->ToCppString());
}

void CheckNativeFunctionArgumentsAtIndexWithType(
  const PyStrPtr& funcName,
  const PyObjPtr& args,
  Index index,
  const KlassPtr& klass
) {
  CheckNativeFunctionArgumentWithType(
    funcName, args->as<PyList>()->GetItem(index), index, klass
  );
}

void CheckNativeFunctionArgumentWithType(
  const PyStrPtr& funcName,
  const PyObjPtr& arg,
  Index index,
  const KlassPtr& klass
) {
  if (arg->Klass() != klass) {
    auto errorMessage = StringConcat(CreatePyList(
      {CreatePyString("Check Native Function (Name: "), funcName,
       CreatePyString(") Arguments With Type At Index: "),
       CreatePyInteger(index)->str(), CreatePyString(" Expected Type: "),
       klass->Name(), CreatePyString(" Got Type: "), arg->Klass()->Name()}
    ));
    throw std::runtime_error(errorMessage->str()->as<PyString>()->ToCppString()
    );
  }
}

void NativeFunctionKlass::Initialize() {
  LoadClass(CreatePyString("native_function")->as<PyString>(), Self());
  ConfigureBasicAttributes(Self());
}

PyObjPtr NativeFunctionKlass::repr(const PyObjPtr& obj) {
  return StringConcat(CreatePyList(
    {CreatePyString("<built-in function at "), Identity(obj)->as<PyString>(),
     CreatePyString(">")}
  ));
}

}  // namespace torchlight::Object
