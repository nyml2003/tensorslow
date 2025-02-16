#ifndef TORCHLIGHT_OBJECT_PYDICTIONARY_H
#define TORCHLIGHT_OBJECT_PYDICTIONARY_H

#include "Collections/Map.h"
#include "Object/Common.h"
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

class DictionaryKlass : public Klass {
 public:
  explicit DictionaryKlass();
  static KlassPtr Self();

  PyObjPtr allocateInstance(PyObjPtr klass, PyObjPtr args) override;

  PyObjPtr setitem(PyObjPtr obj, PyObjPtr key, PyObjPtr value) override;

  PyObjPtr getitem(PyObjPtr obj, PyObjPtr key) override;

  PyObjPtr delitem(PyObjPtr obj, PyObjPtr key) override;

  PyObjPtr contains(PyObjPtr obj, PyObjPtr key) override;

  PyObjPtr repr(PyObjPtr obj) override;

  void Initialize() override;
};

PyObjPtr CreatePyDict();
PyObjPtr CreatePyDict(Collections::Map<PyObjPtr, PyObjPtr> dict);
using PyDictPtr = std::shared_ptr<PyDictionary>;
}  // namespace torchlight::Object

#endif