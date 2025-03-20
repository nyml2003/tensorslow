#include "Function/PyFunction.h"
#include "Object/PyString.h"

namespace torchlight::Object {

PyObjPtr FunctionKlass::repr(const PyObjPtr& obj) {
  return StringConcat(CreatePyList(
    {CreatePyString("<function ")->as<PyString>(),
     obj->as<PyFunction>()->Name(), CreatePyString(" at ")->as<PyString>(),
     Identity(CreatePyList({obj}))->as<PyString>(), CreatePyString(">")->as<PyString>()}
  ));
}

}  // namespace torchlight::Object