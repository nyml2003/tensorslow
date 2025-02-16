#include "Object/ObjectHelper.h"

#include <utility>
#include "ByteCode/PyCode.h"
#include "ByteCode/PyInst.h"
#include "Function/PyFunction.h"
#include "Function/PyIife.h"
#include "Function/PyMethod.h"
#include "Function/PyNativeFunction.h"
#include "Object/PyBoolean.h"
#include "Object/PyDictionary.h"
#include "Object/PyList.h"
#include "Object/PyMatrix.h"
#include "Object/PyNone.h"
#include "Object/PyString.h"
#include "Object/PyType.h"

namespace torchlight::Object {

PyObjPtr Invoke(
  const PyObjPtr& obj,
  const PyObjPtr& methodName,
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

void BasicKlassLoad() {
  Object::StringKlass::Self()->Initialize();
  Object::BooleanKlass::Self()->Initialize();
  Object::NoneKlass::Self()->Initialize();
  Object::ListKlass::Self()->Initialize();
  Object::DictionaryKlass::Self()->Initialize();
  Object::TypeKlass::Self()->Initialize();
  Object::MethodKlass::Self()->Initialize();
  Object::NativeFunctionKlass::Self()->Initialize();
  Object::FunctionKlass::Self()->Initialize();
  Object::InstKlass::Self()->Initialize();
  Object::CodeKlass::Self()->Initialize();
  Object::IntegerKlass::Self()->Initialize();
  Object::BytesKlass::Self()->Initialize();
  Object::MatrixKlass::Self()->Initialize();
  Object::IifeKlass::Self()->Initialize();
}

}  // namespace torchlight::Object