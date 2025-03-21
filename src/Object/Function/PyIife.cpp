#include "Object/Function/PyIife.h"
#include "Function/ObjectHelper.h"
#include "Object/String/PyString.h"
#include "Object/Core/CoreHelper.h"
namespace torchlight::Object {

void IifeKlass::Initialize() {
  auto klass = Self();
  LoadClass(CreatePyString("iife")->as<PyString>(), klass);
  ConfigureBasicAttributes(klass);
}

PyObjPtr IifeKlass::str(const PyObjPtr& /*self*/) {
  return CreatePyString("<iife>");
}

}  // namespace torchlight::Object