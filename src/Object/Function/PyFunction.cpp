#include "Object/Function/PyFunction.h"
#include "Object/String/PyString.h"

namespace tensorslow::Object {

PyObjPtr FunctionKlass::repr(const PyObjPtr& obj) {
  return StringConcat(CreatePyList(
    {CreatePyString("<function ")->as<PyString>(),
     obj->as<PyFunction>()->Name(), CreatePyString(" at ")->as<PyString>(),
     Function::Identity(CreatePyList({obj}))->as<PyString>(),
     CreatePyString(">")->as<PyString>()}
  ));
}

}  // namespace tensorslow::Object