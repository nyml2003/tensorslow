#include "object/PyDictionary.h"

#include "collections/impl/String.h"
#include "object/PyObject.h"
#include "object/PyString.h"

#include <stdexcept>
#include <utility>

namespace torchlight::object {

PyDictionary::PyDictionary() : PyObject(DictionaryKlass::Self()) {}

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
  dict->Value().Put(std::dynamic_pointer_cast<PyString>(key)->Value(), value);
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
}  // namespace torchlight::object