#include "Function/PyFunction.h"

namespace torchlight::Object {

PyObjPtr FunctionKlass::repr(const PyObjPtr& obj) {
  return StringConcat(CreatePyList(
    {CreatePyString("<function "), obj->as<PyFunction>()->Name(),
     CreatePyString(" at "),
     Identity(obj)->as<PyString>(),
     CreatePyString(">")}
  ));
}

}  // namespace torchlight::Object