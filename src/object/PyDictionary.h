#ifndef TORCHLIGHT_OBJECT_PYDICTIONARY_H
#define TORCHLIGHT_OBJECT_PYDICTIONARY_H

#include "collections/Map.h"
#include "object/Klass.h"
#include "object/PyObject.h"

namespace torchlight::object {

class PyDictionary : public PyObject {
 private:
  collections::Map<PyObjPtr, PyObjPtr> dict;

 public:
  explicit PyDictionary(collections::Map<PyObjPtr, PyObjPtr> dict);

  collections::Map<PyObjPtr, PyObjPtr>& Value();
};

using PyDictPtr = std::shared_ptr<PyDictionary>;

PyDictPtr CreatePyDict();

class DictionaryKlass : public Klass {
 public:
  explicit DictionaryKlass();
  static object::KlassPtr Self();

  PyObjPtr setitem(PyObjPtr obj, PyObjPtr key, PyObjPtr value) override;

  PyObjPtr getitem(PyObjPtr obj, PyObjPtr key) override;

  PyObjPtr delitem(PyObjPtr obj, PyObjPtr key) override;

  PyObjPtr repr(PyObjPtr obj) override;
};

}  // namespace torchlight::object

#endif