#include "Function/PyIife.h"
#include "Object/ObjectHelper.h"
#include "Object/PyString.h"
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