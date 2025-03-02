#include "Object/PyList.h"
#include "ByteCode/ByteCode.h"
#include "Collections/BytesHelper.h"
#include "Function/PyNativeFunction.h"
#include "Object/Iterator.h"
#include "Object/Object.h"
#include "Object/ObjectHelper.h"
#include "Object/PyBoolean.h"
#include "Object/PyBytes.h"
#include "Object/PyInteger.h"
#include "Object/PyNone.h"
#include "Object/PyObject.h"
#include "Object/PyString.h"
#include "Object/PyType.h"

namespace torchlight::Object {

PyObjPtr CreatePyList(Index capacity) {
  if (capacity == 0) {
    return std::make_shared<PyList>(Collections::List<PyObjPtr>());
  }
  Collections::List<PyObjPtr> list(capacity);
  list.Fill(PyNone::Instance());
  return std::make_shared<PyList>(list);
}

PyObjPtr CreatePyList(Collections::List<PyObjPtr> list) {
  return std::make_shared<PyList>(list);
}

void ListKlass::Initialize() {
  LoadClass(CreatePyString("list")->as<PyString>(), Self());
  ConfigureBasicAttributes(Self());
  Self()->AddAttribute(
    CreatePyString("append")->as<PyString>(), CreatePyNativeFunction(ListAppend)
  );
  Self()->AddAttribute(
    CreatePyString("index")->as<PyString>(), CreatePyNativeFunction(ListIndex)
  );
}

PyObjPtr ListKlass::construct(const PyObjPtr& type, const PyObjPtr& args) {
  if (type->as<PyType>()->Owner() != Self()) {
    throw std::runtime_error("List does not support construct operation");
  }
  if (!args->is<PyList>()) {
    throw std::runtime_error("List allocation argument must be a list");
  }
  auto argList = args->as<PyList>();
  if (argList->Length() == 0) {
    return CreatePyList({});
  }
  CheckNativeFunctionArgumentsWithExpectedLength(args, 1);
  auto value = argList->GetItem(0);
  if (!value->is<PyList>()) {
    throw std::runtime_error("List allocation argument must be a list");
  }
  return value;
}

PyObjPtr ListKlass::add(const PyObjPtr& lhs, const PyObjPtr& rhs) {
  if (!lhs->is<PyList>() || !rhs->is<PyList>()) {
    throw std::runtime_error("List does not support add operation");
  }
  return lhs->as<PyList>()->Add(rhs->as<PyList>());
}

PyObjPtr ListKlass::repr(const PyObjPtr& obj) {
  auto list = obj->as<PyList>();
  return StringConcat(CreatePyList(
    {CreatePyString("["), CreatePyString(", ")->as<PyString>()->Join(list),
     CreatePyString("]")}
  ));
}

PyObjPtr ListKlass::eq(const PyObjPtr& lhs, const PyObjPtr& rhs) {
  if (lhs->Klass() != Self() || rhs->Klass() != Self()) {
    throw std::runtime_error("List does not support eq operation");
  }
  auto left = std::dynamic_pointer_cast<PyList>(lhs);
  auto right = std::dynamic_pointer_cast<PyList>(rhs);
  if (left->Length() != right->Length()) {
    return CreatePyBoolean(false);
  }
  for (Index i = 0; i < left->Length(); i++) {
    if (left->GetItem(i) != right->GetItem(i)) {
      return CreatePyBoolean(false);
    }
  }
  return CreatePyBoolean(true);
}

PyObjPtr ListKlass::getitem(const PyObjPtr& obj, const PyObjPtr& key) {
  if (!obj->is<PyList>() || !key->is<PyInteger>()) {
    auto errorMessage = StringConcat(CreatePyList(
      {CreatePyString("AttributeError: '"), obj->Klass()->Name(),
       CreatePyString("' object has no attribute '__getitem__'")}
    ));
    throw std::runtime_error(errorMessage->as<PyString>()->ToCppString());
  }
  auto list = obj->as<PyList>();
  auto index = key->as<PyInteger>();
  return list->GetItem(index->ToU64());
}

PyObjPtr ListKlass::setitem(
  const PyObjPtr& obj,
  const PyObjPtr& key,
  const PyObjPtr& value
) {
  if (!obj->is<PyList>() || !key->is<PyInteger>()) {
    auto errorMessage = StringConcat(CreatePyList(
      {CreatePyString("AttributeError: '"), obj->Klass()->Name(),
       CreatePyString("' object has no attribute '__setitem__'")}
    ));
    throw std::runtime_error(errorMessage->as<PyString>()->ToCppString());
  }
  auto list = obj->as<PyList>();
  auto index = key->as<PyInteger>()->ToU64();
  list->SetItem(index, value);
  return CreatePyNone();
}

PyObjPtr ListKlass::len(const PyObjPtr& obj) {
  if (!obj->is<PyList>()) {
    auto errorMessage = StringConcat(CreatePyList(
      {CreatePyString("TypeError: unsupported operand type(s) for"),
       CreatePyString(" len(): '"), obj->Klass()->Name(), CreatePyString("'")}
    ));
    throw std::runtime_error(errorMessage->as<PyString>()->ToCppString());
  }
  return CreatePyInteger(obj->as<PyList>()->Length());
}

PyObjPtr ListKlass::contains(const PyObjPtr& obj, const PyObjPtr& key) {
  if (!obj->is<PyList>()) {
    throw std::runtime_error("List does not support contains operation");
  }
  return CreatePyBoolean(obj->as<PyList>()->Contains(key));
}

PyObjPtr ListKlass::_serialize_(const PyObjPtr& obj) {
  if (obj->Klass() != Self()) {
    throw std::runtime_error("List does not support serialization");
  }
  auto list = std::dynamic_pointer_cast<PyList>(obj);
  PyObjPtr bytes =
    CreatePyBytes(Collections::Serialize(Literal::LIST)
                    .Add(Collections::Serialize(list->Length())));
  auto iter = CreateListIterator(obj);
  auto value = iter->next();
  while (value->Klass() != IterDoneKlass::Self()) {
    bytes = bytes->add(value->_serialize_());
    value = iter->next();
  }
  return bytes;
}

PyObjPtr ListAppend(const PyObjPtr& args) {
  CheckNativeFunctionArgumentsWithExpectedLength(args, 2);
  auto argList = args->as<PyList>();
  auto obj = argList->GetItem(1);
  auto list = argList->GetItem(0)->as<PyList>();
  list->Append(obj);
  return CreatePyNone();
}

PyObjPtr ListIndex(const PyObjPtr& args) {
  CheckNativeFunctionArgumentsWithExpectedLength(args, 2);
  auto funcName = CreatePyString("list_index")->as<PyString>();
  CheckNativeFunctionArgumentsAtIndexWithType(
    funcName, args, 0, ListKlass::Self()
  );
  auto argList = args->as<PyList>();
  auto obj = argList->GetItem(1);
  auto list = argList->GetItem(0)->as<PyList>();
  return CreatePyInteger(list->IndexOf(obj));
}

PyObjPtr ListKlass::iter(const PyObjPtr& obj) {
  if (!obj->is<PyList>()) {
    throw std::runtime_error("List does not support iter operation");
  }
  return CreateListIterator(obj);
}

}  // namespace torchlight::Object