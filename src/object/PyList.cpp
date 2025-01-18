#include "Collections/BytesHelper.h"
#include "Collections/IntegerHelper.h"
#include "Collections/Iterator.h"
#include "Collections/StringHelper.h"
#include "Object/ByteCode.h"
#include "Object/PyBoolean.h"
#include "Object/PyBytes.h"
#include "Object/PyInteger.h"
#include "Object/PyList.h"
#include "Object/PyNone.h"
#include "Object/PyString.h"

namespace torchlight::Object {

PyList::PyList(Collections::List<PyObjPtr> value)
  : PyObject(ListKlass::Self()), value(std::move(value)) {}

PyListPtr CreatePyList(Index capacity) {
  if (capacity == 0) {
    return std::make_shared<PyList>(Collections::List<PyObjPtr>());
  }
  Collections::List<PyObjPtr> list(capacity);
  list.Fill(PyNone::Instance());
  return std::make_shared<PyList>(list);
}

PyListPtr CreatePyList(Collections::List<PyObjPtr> list, Index capacity) {
  if (list.Size() >= capacity) {
    return std::make_shared<PyList>(list);
  }
  list.Concat(
    Collections::List<PyObjPtr>(capacity - list.Size(), PyNone::Instance())
  );
  return std::make_shared<PyList>(list);
}

Collections::List<PyObjPtr>& PyList::Value() {
  return value;
}

ListKlass::ListKlass() : Klass(Collections::CreateStringWithCString("list")) {}

KlassPtr ListKlass::Self() {
  static KlassPtr instance = std::make_shared<ListKlass>();
  return instance;
}

PyObjPtr ListKlass::add(PyObjPtr lhs, PyObjPtr rhs) {
  if (lhs->Klass() != Self() || rhs->Klass() != Self()) {
    throw std::runtime_error("List does not support add operation");
  }
  auto left = std::dynamic_pointer_cast<PyList>(lhs);
  auto right = std::dynamic_pointer_cast<PyList>(rhs);
  Collections::List<PyObjPtr> result = left->Value().Copy();
  result.Add(right->Value());
  return CreatePyList(result, result.Size());
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
    throw std::runtime_error("List does not support getitem operation");
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

PyStrPtr PyList::Join(const PyStrPtr& separator) {
  Collections::List<Collections::String> reprs;
  for (auto it = Collections::Iterator<PyObjPtr>::Begin(value); !it.End();
       it.Next()) {
    auto repr = it.Get()->repr();
    if (repr->Klass() != StringKlass::Self()) {
      throw std::runtime_error("List element is not a string");
    }
    reprs.Push(std::dynamic_pointer_cast<PyString>(repr)->Value());
  }
  return CreatePyString(Collections::Join(reprs, separator->Value()));
}

}  // namespace torchlight::Object