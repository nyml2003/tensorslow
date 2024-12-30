#include "object/PyDictionary.h"
#include "collections/impl/String.h"

namespace torchlight::object {

PyDictionary::PyDictionary() : PyObject(DictionaryKlass::Self()) {}

DictionaryKlass::DictionaryKlass()
  : Klass(collections::CreateStringWithCString("dict")) {}

KlassPtr DictionaryKlass::Self() {
  static KlassPtr self = std::make_shared<DictionaryKlass>();
  return self;
}

}  // namespace torchlight::object