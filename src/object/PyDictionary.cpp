#include "collections/Iterator.h"
#include "collections/Map.h"
#include "collections/impl/String.h"
#include "object/PyDictionary.h"
#include "object/PyObject.h"
#include "object/PyString.h"

namespace torchlight::object {

using collections::CreateStringWithCString;
using collections::Iterator;
using collections::Map;
using collections::MapEntry;

PyDictionary::PyDictionary(Map<PyObjPtr, PyObjPtr> dict)
  : PyObject(DictionaryKlass::Self()), dict(std::move(dict)) {}

PyDictPtr CreatePyDict() {
  return std::make_shared<PyDictionary>(Map<PyObjPtr, PyObjPtr>());
}

DictionaryKlass::DictionaryKlass() : Klass(CreateStringWithCString("dict")) {}

KlassPtr DictionaryKlass::Self() {
  static KlassPtr self = std::make_shared<DictionaryKlass>();
  return self;
}

PyObjPtr DictionaryKlass::setitem(PyObjPtr obj, PyObjPtr key, PyObjPtr value) {
  if (obj->Klass() != Self()) {
    return nullptr;
  }
  auto dict = std::dynamic_pointer_cast<PyDictionary>(obj);
  dict->Value().Put(std::move(key), std::move(value));
  return obj;
}

PyObjPtr DictionaryKlass::getitem(PyObjPtr obj, PyObjPtr key) {
  if (obj->Klass() != Self()) {
    return nullptr;
  }
  auto dict = std::dynamic_pointer_cast<PyDictionary>(obj);
  return dict->Value().Get(key);
}

PyObjPtr DictionaryKlass::delitem(PyObjPtr obj, PyObjPtr key) {
  if (obj->Klass() != Self()) {
    return nullptr;
  }
  auto dict = std::dynamic_pointer_cast<PyDictionary>(obj);
  dict->Value().Remove(key);
  return obj;
}

Map<PyObjPtr, PyObjPtr>& PyDictionary::Value() {
  return dict;
}

PyObjPtr DictionaryKlass::repr(PyObjPtr obj) {
  if (obj->Klass() != Self()) {
    return nullptr;
  }
  auto dict = std::dynamic_pointer_cast<PyDictionary>(obj);
  PyObjPtr result = CreatePyString(CreateStringWithCString("{"));
  auto entries = dict->Value().Entries();
  for (auto it = Iterator<MapEntry<PyObjPtr, PyObjPtr>>::Begin(entries);
       !it.End(); it.Next()) {
    auto entry = it.Get();
    result = result->add(entry.Key()->repr())
               ->add(CreatePyString(CreateStringWithCString(": ")))
               ->add(entry.Value()->repr())
               ->add(CreatePyString(CreateStringWithCString(", ")));
  }
  result = result->add(CreatePyString(CreateStringWithCString("}")));
  return result;
}
}  // namespace torchlight::object