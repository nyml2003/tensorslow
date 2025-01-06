#include "object/PyDictionary.h"

#include "collections/impl/Bytes.h"
#include "collections/impl/String.h"
#include "object/PyObject.h"
#include "object/PyString.h"

#include <iostream>
#include <stdexcept>

namespace torchlight::object {

PyDictionary::PyDictionary(collections::Map<collections::String, PyObjPtr> dict)
  : PyObject(DictionaryKlass::Self()), dict(std::move(dict)) {}

PyDictPtr CreateDict(collections::Map<collections::String, PyObjPtr> dict) {
  return std::make_shared<PyDictionary>(dict);
}

void PyDictionary::Put(const collections::String& key, const PyObjPtr& value) {
  dict.Put(key, value);
}

PyObjPtr PyDictionary::Get(const collections::String& key) {
  return dict.Get(key);
}

DictionaryKlass::DictionaryKlass()
  : Klass(collections::CreateStringWithCString("dict")) {}

KlassPtr DictionaryKlass::Self() {
  static KlassPtr self = std::make_shared<DictionaryKlass>();
  return self;
}

PyObjPtr DictionaryKlass::setitem(PyObjPtr obj, PyObjPtr key, PyObjPtr value) {
  if (obj->Klass() != Self()) {
    return nullptr;
  }
  auto dict = std::dynamic_pointer_cast<PyDictionary>(obj);
  dict->Put(std::dynamic_pointer_cast<PyString>(key)->Value(), value);
  return obj;
}

PyObjPtr DictionaryKlass::getitem(PyObjPtr obj, PyObjPtr key) {
  if (obj->Klass() != Self()) {
    return nullptr;
  }
  auto dict = std::dynamic_pointer_cast<PyDictionary>(obj);
  return dict->Value().Get(std::dynamic_pointer_cast<PyString>(key)->Value());
}

collections::Map<collections::String, PyObjPtr>& PyDictionary::Value() {
  return dict;
}

PyObjPtr DictionaryKlass::repr(PyObjPtr obj) {
  if (obj->Klass() != Self()) {
    return nullptr;
  }
  auto dict = std::dynamic_pointer_cast<PyDictionary>(obj);
  collections::String result = collections::CreateStringWithCString("{");
  auto keys = dict->Value().Keys();
  for (auto it = collections::List<collections::String>::Iterator::Begin(keys);
       !it.End(); it.Next()) {
    auto key = it.Get();
    auto value = dict->Value().Get(key);
    result.InplaceConcat(key);
    result.InplaceConcat(collections::CreateStringWithCString(": "));
    auto repr = value->repr();
    if (repr->Klass() != StringKlass::Self()) {
      throw std::runtime_error("Cannot represent object");
    }
    result.InplaceConcat(std::dynamic_pointer_cast<PyString>(repr)->Value());
    result.InplaceConcat(collections::CreateStringWithCString(", "));
  }
  result.InplaceConcat(collections::CreateStringWithCString("}"));
  return std::make_shared<PyString>(result);
}
}  // namespace torchlight::object