#include "Object/PyList.h"

#include "ByteCode/ByteCode.h"
#include "Collections/BytesHelper.h"
#include "Collections/IntegerHelper.h"
#include "Collections/StringHelper.h"
#include "Function/PyNativeFunction.h"
#include "Object/Iterator.h"
#include "Object/Klass.h"
#include "Object/Object.h"
#include "Object/ObjectHelper.h"
#include "Object/PyBoolean.h"
#include "Object/PyBytes.h"
#include "Object/PyDictionary.h"
#include "Object/PyInteger.h"
#include "Object/PyNone.h"
#include "Object/PyObject.h"
#include "Object/PyString.h"
#include "Object/PyType.h"

#include <memory>

namespace torchlight::Object {

PyList::PyList(Collections::List<PyObjPtr> value)
  : PyObject(ListKlass::Self()), value(std::move(value)) {}

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

Index PyList::Length() const {
  return value.Size();
}

ListKlass::ListKlass() = default;

void ListKlass::Initialize() {
  SetType(CreatePyType(Self()));
  SetName(CreatePyString("list"));
  Collections::Map<PyObjPtr, PyObjPtr> methods;
  methods.Put(CreatePyString("join"), CreatePyNativeFunction(Join));
  methods.Put(CreatePyString("append"), CreatePyNativeFunction(Append));
  methods.Put(CreatePyString("index"), CreatePyNativeFunction(ListIndex));
  SetAttributes(CreatePyDict(std::move(methods)));
  Klass::Initialize();
}

KlassPtr ListKlass::Self() {
  static KlassPtr instance = std::make_shared<ListKlass>();
  return instance;
}

PyObjPtr
ListKlass::allocateInstance(const PyObjPtr& type, const PyObjPtr& args) {
  if (Self()->Type() != type) {
    Klass::allocateInstance(type, args);
  }
  if (ToU64(args->len()) == 0) {
    return CreatePyList({});
  }
  if (ToU64(args->len()) != 1) {
    throw std::runtime_error("List allocation takes exactly 1 argument");
  }
  auto value = args->getitem(CreatePyInteger(0));
  if (value->Klass() != ListKlass::Self()) {
    throw std::runtime_error("List allocation argument must be a list");
  }
  return value;
}

PyObjPtr ListKlass::add(const PyObjPtr& lhs, const PyObjPtr& rhs) {
  if (lhs->Klass() != Self() || rhs->Klass() != Self()) {
    throw std::runtime_error("List does not support add operation");
  }
  auto left = std::dynamic_pointer_cast<PyList>(lhs);
  auto right = std::dynamic_pointer_cast<PyList>(rhs);
  return CreatePyList(left->value.Add(right->value));
}

PyObjPtr ListKlass::repr(const PyObjPtr& obj) {
  if (obj->Klass() != Self()) {
    throw std::runtime_error("List does not support repr operation");
  }
  auto list = std::dynamic_pointer_cast<PyList>(obj);
  auto list_repr =
    list->Join(CreatePyString(Collections::CreateStringWithCString(", ")));
  return CreatePyString(Collections::CreateStringWithCString("["))
    ->add(list_repr)
    ->add(CreatePyString(Collections::CreateStringWithCString("]")));
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
  if (obj->Klass() != Self() || key->Klass() != IntegerKlass::Self()) {
    ThrowUnsupportedOperandError(obj, key, CreatePyString("__getitem__"));
  }
  auto list = std::dynamic_pointer_cast<PyList>(obj);
  auto index = std::dynamic_pointer_cast<PyInteger>(key);
  return list->GetItem(Collections::ToU64(index->Value()));
}

PyObjPtr ListKlass::setitem(
  const PyObjPtr& obj,
  const PyObjPtr& key,
  const PyObjPtr& value
) {
  if (obj->Klass() != Self() || key->Klass() != IntegerKlass::Self()) {
    throw std::runtime_error("PyList::setitem(): obj is not a list");
  }
  auto list = std::dynamic_pointer_cast<PyList>(obj);
  auto index = std::dynamic_pointer_cast<PyInteger>(key);
  list->SetItem(Collections::ToU64(index->Value()), value);
  return CreatePyNone();
}

void PyList::Append(PyObjPtr obj) {
  value.Push(std::move(obj));
}

PyObjPtr PyList::Join(const PyObjPtr& separator) {
  if (separator->Klass() != StringKlass::Self()) {
    throw std::runtime_error("List::Join(): separator is not a string");
  }
  Collections::List<Collections::String> reprs;
  ForEach(
    shared_from_this(),
    [&reprs](const PyObjPtr& value, Index, const PyObjPtr&) {
      auto repr = value->str();
      if (repr->Klass() != StringKlass::Self()) {
        throw std::runtime_error("List element is not a string");
      }
      reprs.Push(std::dynamic_pointer_cast<PyString>(repr)->Value());
    }
  );
  auto separator_str = std::dynamic_pointer_cast<PyString>(separator)->Value();
  return CreatePyString(Collections::Join(reprs, separator_str));
}

PyObjPtr ListKlass::len(const PyObjPtr& obj) {
  if (obj->Klass() != Self()) {
    throw std::runtime_error("List does not support len operation");
  }
  auto list = std::dynamic_pointer_cast<PyList>(obj);
  return CreatePyInteger(list->Length());
}

PyObjPtr ListKlass::contains(const PyObjPtr& obj, const PyObjPtr& key) {
  if (!IsType(obj, Self())) {
    throw std::runtime_error("List does not support contains operation");
  }
  return CreatePyBoolean(std::dynamic_pointer_cast<PyList>(obj)->Contains(key));
}

bool PyList::Contains(const PyObjPtr& obj) const {
  return value.Contains(obj);
}

Index PyList::IndexOf(const PyObjPtr& obj) const {
  return value.IndexOf(obj);
}

PyObjPtr PyList::GetItem(Index index) const {
  return value.Get(index);
}

void PyList::SetItem(Index index, const PyObjPtr& obj) {
  value.Set(index, obj);
}

PyObjPtr Join(const PyObjPtr& args) {
  CheckNativeFunctionArgumentsWithExpectedLength(args, 2);
  auto arguments = std::dynamic_pointer_cast<PyList>(args);
  auto separator = arguments->GetItem(1);
  auto list = std::dynamic_pointer_cast<PyList>(arguments->GetItem(0));
  return list->Join(separator);
}

PyObjPtr Append(const PyObjPtr& args) {
  CheckNativeFunctionArgumentsWithExpectedLength(args, 2);
  auto arguments = std::dynamic_pointer_cast<PyList>(args);
  auto obj = arguments->GetItem(1);
  auto list = std::dynamic_pointer_cast<PyList>(arguments->GetItem(0));
  list->Append(obj);
  return CreatePyNone();
}

PyObjPtr ListIndex(const PyObjPtr& args) {
  CheckNativeFunctionArgumentsWithExpectedLength(args, 2);
  auto arguments = std::dynamic_pointer_cast<PyList>(args);
  auto obj = arguments->GetItem(1);
  auto list = std::dynamic_pointer_cast<PyList>(arguments->GetItem(0));
  return CreatePyInteger(list->IndexOf(obj));
}

PyObjPtr ListKlass::iter(const PyObjPtr& obj) {
  if (obj->Klass() != Self()) {
    throw std::runtime_error("List does not support iter operation");
  }
  return CreateListIterator(obj);
}

}  // namespace torchlight::Object