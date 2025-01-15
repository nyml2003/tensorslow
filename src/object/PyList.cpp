
#include "collections/Iterator.h"
#include "collections/impl/Bytes.h"
#include "collections/impl/Integer.h"
#include "collections/impl/String.h"
#include "object/ByteCode.h"
#include "object/PyBytes.h"
#include "object/PyInteger.h"
#include "object/PyList.h"
#include "object/PyNone.h"
#include "object/PyString.h"

namespace torchlight::object {

using collections::CreateStringWithCString;
using collections::Index;
using collections::Iterator;
using collections::List;
using collections::Serialize;

PyList::PyList(List<PyObjPtr> value)
  : PyObject(ListKlass::Self()), value(std::move(value)) {}

PyListPtr CreatePyList(Index capacity) {
  List<PyObjPtr> list(capacity);
  list.Fill(PyNone::Instance());
  return std::make_shared<PyList>(list);
}

PyListPtr CreatePyList(List<PyObjPtr> list, Index capacity) {
  if (list.Size() >= capacity) {
    return std::make_shared<PyList>(list);
  }
  list.Concat(List<PyObjPtr>(capacity - list.Size(), PyNone::Instance()));
  return std::make_shared<PyList>(list);
}

List<PyObjPtr> PyList::Value() const {
  return value;
}

ListKlass::ListKlass() : Klass(CreateStringWithCString("list")) {}

KlassPtr ListKlass::Self() {
  static KlassPtr instance = std::make_shared<ListKlass>();
  return instance;
}

PyObjPtr ListKlass::add(PyObjPtr lhs, PyObjPtr rhs) {
  if (lhs->Klass() != Self() || rhs->Klass() != Self()) {
    return nullptr;
  }
  auto left = std::dynamic_pointer_cast<PyList>(lhs);
  auto right = std::dynamic_pointer_cast<PyList>(rhs);
  List<PyObjPtr> result = left->Value().Copy();
  result.Add(right->Value());
  return CreatePyList(result, result.Size());
}

PyObjPtr ListKlass::repr(PyObjPtr obj) {
  if (obj->Klass() != Self()) {
    return nullptr;
  }
  auto list = std::dynamic_pointer_cast<PyList>(obj);
  PyObjPtr result = CreatePyString(CreateStringWithCString("["));
  for (auto it = Iterator<PyObjPtr>::Begin(list->Value()); !it.End();
       it.Next()) {
    result = result->add(it.Get()->repr())
               ->add(CreatePyString(CreateStringWithCString(", ")));
  }
  return result->add(CreatePyString(CreateStringWithCString("]")));
}

PyObjPtr ListKlass::_serialize_(PyObjPtr obj) {
  if (obj->Klass() != Self()) {
    return nullptr;
  }
  auto list = std::dynamic_pointer_cast<PyList>(obj);
  PyObjPtr bytes =
    CreatePyBytes(Serialize(Literal::LIST).Add(Serialize(list->Value().Size()))
    );
  auto list_value = list->Value();
  for (Index i = 0; i < list_value.Size(); ++i) {
    auto element_s = list_value.Get(i)->_serialize_();
    if (element_s->Klass() != BytesKlass::Self()) {
      return nullptr;
    }
    bytes = bytes->add(element_s);
  }
  return bytes;
}

PyObjPtr ListKlass::getitem(PyObjPtr obj, PyObjPtr key) {
  if (obj->Klass() != Self() || key->Klass() != IntegerKlass::Self()) {
    return nullptr;
  }
  auto list = std::dynamic_pointer_cast<PyList>(obj);
  auto index = std::dynamic_pointer_cast<PyInteger>(key);
  return list->Value().Get(ToIndex(index->Value()));
}

PyObjPtr ListKlass::setitem(PyObjPtr obj, PyObjPtr key, PyObjPtr value) {
  if (obj->Klass() != Self() || key->Klass() != IntegerKlass::Self()) {
    return nullptr;
  }
  auto list = std::dynamic_pointer_cast<PyList>(obj);
  auto index = std::dynamic_pointer_cast<PyInteger>(key);
  list->Value().Set(ToIndex(index->Value()), value);
  return obj;
}

void PyList::Append(PyObjPtr obj) {
  value.Push(std::move(obj));
}

}  // namespace torchlight::object