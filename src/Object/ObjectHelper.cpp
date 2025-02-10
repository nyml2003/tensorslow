#include "Function/PyMethod.h"
#include "Function/PyNativeFunction.h"
#include "Object/ObjectHelper.h"
#include "Object/PyList.h"
#include "Object/PyString.h"

namespace torchlight::Object {

PyObjPtr Invoke(
  PyObjPtr obj,
  PyObjPtr methodName,
  std::initializer_list<PyObjPtr> arguments
) {
  auto method =
    std::dynamic_pointer_cast<Object::PyMethod>(obj->getattr(methodName));
  auto nativeFunction =
    std::dynamic_pointer_cast<Object::PyNativeFunction>(method->Method());
  Collections::List<PyObjPtr> args(arguments);
  args.Unshift(obj);
  return nativeFunction->Call(CreatePyList(args));
}

}  // namespace torchlight::Object