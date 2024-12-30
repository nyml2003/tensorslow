#ifndef TORCHLIGHT_OBJECT_PYDICTIONARY_H
#define TORCHLIGHT_OBJECT_PYDICTIONARY_H

#include "collections/Map.h"
#include "collections/String.h"
#include "object/Klass.h"
#include "object/PyObject.h"

namespace torchlight::object {

class PyDictionary : public PyObject {
 private:
  collections::Map<collections::String, PyObjPtr> dict;

 public:
  explicit PyDictionary();
};

using PyDictPtr = std::shared_ptr<PyDictionary>;

class DictionaryKlass : public Klass {
 public:
  explicit DictionaryKlass();
  static object::KlassPtr Self();
};

}  // namespace torchlight::object

#endif