#include "Object/ObjectHelper.h"
#include "ByteCode/PyCode.h"
#include "ByteCode/PyInst.h"
#include "Function/PyFunction.h"
#include "Function/PyIife.h"
#include "Function/PyMethod.h"
#include "Function/PyNativeFunction.h"
#include "Object/Iterator.h"
#include "Object/Object.h"
#include "Object/PyBoolean.h"
#include "Object/PyDictionary.h"
#include "Object/PyList.h"
#include "Object/PyMatrix.h"
#include "Object/PyNone.h"
#include "Object/PyObject.h"
#include "Object/PyString.h"
#include "Object/PyType.h"
#include "Runtime/Interpreter.h"
#include "Runtime/PyFrame.h"

#include <memory>

namespace torchlight::Object {

PyObjPtr Invoke(
  const PyObjPtr& obj,
  const PyObjPtr& methodName,
  std::initializer_list<PyObjPtr> arguments
) {
  if (!obj->Klass()->Attributes()->Contains(methodName)) {
    return CreatePyNone();
  }

  Collections::List<PyObjPtr> argumentsList(arguments);
  argumentsList.Unshift(obj);
  PyListPtr args =
    std::dynamic_pointer_cast<PyList>(CreatePyList(argumentsList));
  auto method =
    std::dynamic_pointer_cast<Object::PyMethod>(obj->getattr(methodName))
      ->Method();
  auto isNative = std::dynamic_pointer_cast<PyNativeFunction>(method);
  if (isNative) {
    return isNative->Call(args);
  }
  return Runtime::CreateFrameWithPyFunction(
           std::dynamic_pointer_cast<PyFunction>(method), args
  )
    ->EvalWithDestory();
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
  Object::IterDoneKlass::Self()->Initialize();
  Object::ListIteratorKlass::Self()->Initialize();
  Object::ObjectKlass::Self()->Initialize();
}

bool IsType(const PyObjPtr& obj, const KlassPtr& type) {
  return obj->Klass() == type;
}

void ForEach(
  const PyObjPtr& obj,
  const std::function<
    void(const PyObjPtr& value, Index index, const PyObjPtr& list)>& func
) {
  auto iter = std::dynamic_pointer_cast<ListIterator>(obj->iter());
  auto value = iter->next();
  while (!IsType(value, IterDoneKlass::Self())) {
    func(value, iter->Index(), obj);
    value = iter->next();
  }
}

PyObjPtr SetItem(const PyObjPtr& args) {
  auto self = args->getitem(CreatePyInteger(0));
  auto key = args->getitem(CreatePyInteger(1));
  auto value = args->getitem(CreatePyInteger(2));
  return self->setitem(key, value);
}

}  // namespace torchlight::Object