#include "Object/PyList.h"

#include "ByteCode/ByteCode.h"
#include "ByteCode/PyCode.h"
#include "Collections/BytesHelper.h"
#include "Collections/IntegerHelper.h"
#include "Collections/Iterator.h"
#include "Collections/StringHelper.h"
#include "Function/PyNativeFunction.h"
#include "Object/Klass.h"
#include "Object/PyBoolean.h"
#include "Object/PyBytes.h"
#include "Object/PyDictionary.h"
#include "Object/PyInteger.h"
#include "Object/PyNone.h"
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

PyObjPtr CreatePyList(Collections::List<PyObjPtr> list, Index capacity) {
  if (list.Size() >= capacity) {
    return std::make_shared<PyList>(list);
  }
  list.Concat(
    Collections::List<PyObjPtr>(capacity - list.Size(), PyNone::Instance())
  );
  return std::make_shared<PyList>(list);
}

PyObjPtr CreatePyList(Collections::List<PyObjPtr> list) {
  return std::make_shared<PyList>(list);
}

Collections::List<PyObjPtr>& PyList::Value() {
  return value;
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

PyObjPtr ListKlass::add(PyObjPtr lhs, PyObjPtr rhs) {
  if (lhs->Klass() != Self() || rhs->Klass() != Self()) {
    Klass::add(lhs, rhs);
  }
  auto left = std::dynamic_pointer_cast<PyList>(lhs);
  auto right = std::dynamic_pointer_cast<PyList>(rhs);
  return CreatePyList(left->Value().Add(right->Value()));
}

PyObjPtr ListKlass::repr(PyObjPtr obj) {
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

PyObjPtr ListKlass::_serialize_(PyObjPtr obj) {
  if (obj->Klass() != Self()) {
    throw std::runtime_error("List does not support serialization");
  }
  auto list = std::dynamic_pointer_cast<PyList>(obj);
  PyObjPtr bytes =
    CreatePyBytes(Collections::Serialize(Literal::LIST)
                    .Add(Collections::Serialize(list->Value().Size())));
  auto list_value = list->Value();
  for (Index i = 0; i < list_value.Size(); ++i) {
    bytes = bytes->add(list_value.Get(i)->_serialize_());
  }
  return bytes;
}

PyObjPtr ListKlass::eq(PyObjPtr lhs, PyObjPtr rhs) {
  if (lhs->Klass() != Self() || rhs->Klass() != Self()) {
    throw std::runtime_error("List does not support eq operation");
  }
  auto left = std::dynamic_pointer_cast<PyList>(lhs);
  auto right = std::dynamic_pointer_cast<PyList>(rhs);
  if (left->Value().Size() != right->Value().Size()) {
    return CreatePyBoolean(false);
  }
  for (Index i = 0; i < left->Value().Size(); ++i) {
    if (left->Value().Get(i)->eq(right->Value().Get(i)) == PyNone::Instance()) {
      return CreatePyBoolean(false);
    }
  }
  return CreatePyBoolean(true);
}

PyObjPtr ListKlass::getitem(PyObjPtr obj, PyObjPtr key) {
  if (obj->Klass() != Self() || key->Klass() != IntegerKlass::Self()) {
    ThrowUnsupportedOperandError(obj, key, CreatePyString("__getitem__"));
  }
  auto list = std::dynamic_pointer_cast<PyList>(obj);
  auto index = std::dynamic_pointer_cast<PyInteger>(key);
  return list->Value().Get(Collections::ToU64(index->Value()));
}

PyObjPtr ListKlass::setitem(PyObjPtr obj, PyObjPtr key, PyObjPtr value) {
  if (obj->Klass() != Self() || key->Klass() != IntegerKlass::Self()) {
    throw std::runtime_error("PyList::setitem(): obj is not a list");
  }
  auto list = std::dynamic_pointer_cast<PyList>(obj);
  auto index = std::dynamic_pointer_cast<PyInteger>(key);
  list->Value().Set(Collections::ToU64(index->Value()), value);
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
  for (auto it = Collections::Iterator<PyObjPtr>::Begin(value); !it.End();
       it.Next()) {
    auto repr = it.Get()->str();
    if (repr->Klass() != StringKlass::Self()) {
      throw std::runtime_error("List element is not a string");
    }
    reprs.Push(std::dynamic_pointer_cast<PyString>(repr)->Value());
  }
  auto separator_str = std::dynamic_pointer_cast<PyString>(separator)->Value();
  return CreatePyString(Collections::Join(reprs, separator_str));
}

PyObjPtr ListKlass::len(PyObjPtr obj) {
  if (obj->Klass() != Self()) {
    throw std::runtime_error("List does not support len operation");
  }
  auto list = std::dynamic_pointer_cast<PyList>(obj);
  return CreatePyInteger(list->Value().Size());
}

PyObjPtr ListKlass::contains(PyObjPtr obj, PyObjPtr key) {
  if (obj->Klass() != Self()) {
    throw std::runtime_error("List does not support contains operation");
  }
  auto list = std::dynamic_pointer_cast<PyList>(obj);
  return CreatePyBoolean(list->Value().Contains(key));
}

PyObjPtr Join(PyObjPtr args) {
  if (args->Klass() != ListKlass::Self()) {
    throw std::runtime_error("Join(): args is not a list");
  }
  auto list = std::dynamic_pointer_cast<PyList>(args);
  if (list->Value().Size() != 2) {
    throw std::runtime_error("Join(): args does not have 2 elements");
  }
  auto separator = list->Value().Get(1);
  auto list_obj = list->Value().Get(0);
  if (separator->Klass() != StringKlass::Self() ||
      list_obj->Klass() != ListKlass::Self()) {
    throw std::runtime_error(
      "Join(): separator is not a string or list is not a list"
    );
  }
  return std::dynamic_pointer_cast<PyList>(list_obj)->Join(separator);
}

PyObjPtr Append(PyObjPtr args) {
  if (args->Klass() != ListKlass::Self()) {
    throw std::runtime_error("Append(): args is not a list");
  }
  auto list = std::dynamic_pointer_cast<PyList>(args);
  if (list->Value().Size() != 2) {
    throw std::runtime_error("Append(): args does not have 2 elements");
  }
  auto obj = list->Value().Get(1);
  auto list_obj = list->Value().Get(0);
  if (list_obj->Klass() != ListKlass::Self()) {
    throw std::runtime_error("Append(): list is not a list");
  }
  std::dynamic_pointer_cast<PyList>(list_obj)->Append(obj);
  return CreatePyNone();
}

PyObjPtr ListIndex(PyObjPtr args) {
  if (args->Klass() != ListKlass::Self()) {
    throw std::runtime_error("ListIndex(): args is not a list");
  }
  auto list = std::dynamic_pointer_cast<PyList>(args);
  if (list->Value().Size() != 2) {
    throw std::runtime_error("ListIndex(): args does not have 2 elements");
  }
  auto obj = list->Value().Get(1);
  auto list_obj = list->Value().Get(0);
  if (list_obj->Klass() != ListKlass::Self()) {
    throw std::runtime_error("ListIndex(): list is not a list");
  }
  auto list_value = std::dynamic_pointer_cast<PyList>(list_obj)->Value();
  return CreatePyInteger(list_value.IndexOf(obj));
}

}  // namespace torchlight::Object