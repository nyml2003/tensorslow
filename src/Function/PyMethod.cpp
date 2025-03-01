#include "Function/PyMethod.h"
#include "Object/PyList.h"
#include "Object/PyString.h"

namespace torchlight::Object {

PyObjPtr MethodKlass::repr(const PyObjPtr& obj) {
  if (!obj->is<PyMethod>()) {
    auto errorMessage = StringConcat(CreatePyList(
      {CreatePyString("AttributeError: '"), obj->Klass()->Name(),
       CreatePyString("' object has no attribute '__repr__'")}
    ));
    throw std::runtime_error(errorMessage->as<PyString>()->ToCppString());
  }
  auto method = obj->as<PyMethod>();
  return StringConcat(CreatePyList(
    {CreatePyString("<method "), method->Owner()->repr(), CreatePyString("."),
     method->Method()->repr(), CreatePyString(">")}
  ));
}

}  // namespace torchlight::Object