#include "Object/Function/PyIife.h"
#include "Function/BuiltinFunction.h"
#include "Object/Core/CoreHelper.h"
#include "Object/String/PyString.h"
namespace torchlight::Object {

void IifeKlass::Initialize() {
  if (this->isInitialized) {
    return;
  }
  InitKlass(CreatePyString("iife")->as<PyString>(), IifeKlass::Self());
  ConfigureBasicAttributes(IifeKlass::Self());
  this->isInitialized = true;
}

PyObjPtr IifeKlass::str(const PyObjPtr& /*self*/) {
  return CreatePyString("<iife>");
}

}  // namespace torchlight::Object