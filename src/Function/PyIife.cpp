#include "Function/PyIife.h"
#include "Object/ObjectHelper.h"
#include "Object/PyString.h"
namespace torchlight::Object {

void IifeKlass::Initialize() {
  auto klass = Self();
  LoadClass(CreatePyString("iife")->as<PyString>(), klass);
  ConfigureBasicAttributes(klass);
}

}  // namespace torchlight::Object