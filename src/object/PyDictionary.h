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
  explicit PyDictionary(collections::Map<collections::String, PyObjPtr> dict);

  collections::Map<collections::String, PyObjPtr>& Value();

  void Put(const collections::String& key, const PyObjPtr& value);

  PyObjPtr Get(const collections::String& key);
};

using PyDictPtr = std::shared_ptr<PyDictionary>;

PyDictPtr CreateDict(collections::Map<collections::String, PyObjPtr> dict);

class DictionaryKlass : public Klass {
 public:
  explicit DictionaryKlass();
  static object::KlassPtr Self();

  PyObjPtr setitem(PyObjPtr obj, PyObjPtr key, PyObjPtr value) override;

  PyObjPtr getitem(PyObjPtr obj, PyObjPtr key) override;

  PyObjPtr repr(PyObjPtr obj) override;
};

}  // namespace torchlight::object

#endif