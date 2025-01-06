#include "object/PyList.h"
#include "collections/Bytes.h"
#include "collections/impl/Bytes.h"
#include "collections/impl/Integer.h"
#include "collections/impl/String.h"
#include "object/ByteCode.h"
#include "object/PyBytes.h"
#include "object/PyInteger.h"
#include "object/PyNone.h"
#include "object/PyString.h"

namespace torchlight::object {

using collections::Bytes;
using collections::List;
using collections::Serialize;
using collections::String;

PyList::PyList(List<PyObjPtr> value)
  : PyObject(ListKlass::Self()), value(std::move(value)) {}

PyListPtr CreateList(collections::Index capacity) {
  List<PyObjPtr> list(capacity);
  list.Fill(PyNone::Instance());
  return std::make_shared<PyList>(list);
}

PyListPtr CreateList(List<PyObjPtr> list, collections::Index capacity) {
  if (list.Size() >= capacity) {
    return std::make_shared<PyList>(list);
  }
  list.AppendElements(PyNone::Instance(), capacity - list.Size());
  return std::make_shared<PyList>(list);
}

List<PyObjPtr> PyList::Value() const {
  return value;
}

ListKlass::ListKlass() : Klass(collections::CreateStringWithCString("list")) {}

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
  return std::make_shared<PyList>(result);
}

PyObjPtr ListKlass::repr(PyObjPtr obj) {
  if (obj->Klass() != Self()) {
    return nullptr;
  }
  auto list = std::dynamic_pointer_cast<PyList>(obj);
  String result = collections::CreateStringWithCString("[");
  for (auto it = List<PyObjPtr>::Iterator::Begin(list->Value()); !it.End();
       it.Next()) {
    auto s = it.Get()->repr();
    if (s->Klass() != StringKlass::Self()) {
      return nullptr;
    }
    auto str = std::dynamic_pointer_cast<PyString>(s);
    result.InplaceConcat(str->Value());
    if (!it.End()) {
      result.InplaceConcat(collections::CreateStringWithCString(", "));
    }
  }
  result.InplaceConcat(collections::CreateStringWithCString("]"));
  return std::make_shared<PyString>(result);
}

PyObjPtr ListKlass::_serialize_(PyObjPtr obj) {
  if (obj->Klass() != Self()) {
    return nullptr;
  }
  auto list = std::dynamic_pointer_cast<PyList>(obj);
  Bytes bytes;
  bytes.InplaceConcat(Serialize(Literal::LIST));
  bytes.InplaceConcat(Serialize(list->Value().Size()));
  for (auto it = List<PyObjPtr>::Iterator::Begin(list->Value()); !it.End();
       it.Next()) {
    auto s = it.Get()->_serialize_();
    if (s->Klass() != BytesKlass::Self()) {
      return nullptr;
    }
    auto str = std::dynamic_pointer_cast<PyBytes>(s);
    bytes.InplaceConcat(str->Value());
  }
  return std::make_shared<PyBytes>(bytes);
}

PyObjPtr ListKlass::getitem(PyObjPtr obj, PyObjPtr key) {
  if (obj->Klass() != Self() || key->Klass() != IntegerKlass::Self()) {
    return nullptr;
  }
  auto list = std::dynamic_pointer_cast<PyList>(obj);
  auto index = std::dynamic_pointer_cast<PyInteger>(key);
  return list->Value().Get(collections::ToIndex(index->Value()));
}

PyObjPtr ListKlass::setitem(PyObjPtr obj, PyObjPtr key, PyObjPtr value) {
  if (obj->Klass() != Self() || key->Klass() != IntegerKlass::Self()) {
    return nullptr;
  }
  auto list = std::dynamic_pointer_cast<PyList>(obj);
  auto index = std::dynamic_pointer_cast<PyInteger>(key);
  list->Value().Set(collections::ToIndex(index->Value()), value);
  return obj;
}

}  // namespace torchlight::object