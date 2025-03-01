#include "Object/ObjectHelper.h"
#include "Function/PyFunction.h"
#include "Function/PyMethod.h"
#include "Function/PyNativeFunction.h"
#include "Object/Iterator.h"
#include "Object/Object.h"
#include "Object/PyBoolean.h"
#include "Object/PyDictionary.h"
#include "Object/PyList.h"
#include "Object/PyNone.h"
#include "Object/PyObject.h"
#include "Object/PyString.h"
#include "Object/PyType.h"
#include "Runtime/PyFrame.h"
#include "Collections/IntegerHelper.h"
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
  Object::StringKlass::Initialize();
  Object::ListKlass::Initialize();
  Object::DictionaryKlass::Initialize();
  Object::TypeKlass::Initialize();
  Object::BooleanKlass::Initialize();
  Object::NativeFunctionKlass::Initialize();
}

void ForEach(
  const PyObjPtr& obj,
  const std::function<
    void(const PyObjPtr& value, Index index, const PyObjPtr& obj)>& func
) {
  auto iter = obj->iter();
  auto iterable = std::dynamic_pointer_cast<IIterator>(iter);
  if (!iterable) {
    throw std::runtime_error("object is not iterable");
  }
  auto value = iter->next();
  while (!value->is<IterDone>()) {
    func(value, iterable->CurrentIndex(), obj);
    value = iter->next();
  }
}

PyObjPtr Identity(const PyObjPtr& obj) {
  return CreatePyString(
    Collections::CreateIntegerWithU64(reinterpret_cast<uint64_t>(obj.get()))
      .ToHexString()
  );
}

}  // namespace torchlight::Object