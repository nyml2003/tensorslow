#ifndef TORCHLIGHT_OBJECT_PYDICTIONARY_H
#define TORCHLIGHT_OBJECT_PYDICTIONARY_H

#include "Collections/Map.h"
#include "Object/Klass.h"
#include "Object/PyObject.h"

namespace torchlight::Object {

class PyDictionary : public PyObject {
 private:
  Collections::Map<PyObjPtr, PyObjPtr> dict;

 public:
  explicit PyDictionary(Collections::Map<PyObjPtr, PyObjPtr> dict);

  Collections::Map<PyObjPtr, PyObjPtr>& Value();
};

using PyDictPtr = std::shared_ptr<PyDictionary>;

PyDictPtr CreatePyDict();

class DictionaryKlass : public Klass {
 public:
  explicit DictionaryKlass();
  static Object::KlassPtr Self();

  PyObjPtr setitem(PyObjPtr obj, PyObjPtr key, PyObjPtr value) override;

  PyObjPtr getitem(PyObjPtr obj, PyObjPtr key) override;

  PyObjPtr delitem(PyObjPtr obj, PyObjPtr key) override;

  PyObjPtr repr(PyObjPtr obj) override;
};

}  // namespace torchlight::Object

#endif