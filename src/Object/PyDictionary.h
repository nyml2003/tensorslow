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

  void Put(const PyObjPtr& key, const PyObjPtr& value);

  PyObjPtr Get(const PyObjPtr& key);

  void Remove(const PyObjPtr& key);

  bool Contains(const PyObjPtr& key);
};

class DictionaryKlass : public Klass {
 public:
  explicit DictionaryKlass();
  static KlassPtr Self();

  PyObjPtr allocateInstance(const PyObjPtr& klass, const PyObjPtr& args)
    override;

  PyObjPtr setitem(
    const PyObjPtr& obj,
    const PyObjPtr& key,
    const PyObjPtr& value
  ) override;

  PyObjPtr getitem(const PyObjPtr& obj, const PyObjPtr& key) override;

  PyObjPtr delitem(const PyObjPtr& obj, const PyObjPtr& key) override;

  PyObjPtr contains(const PyObjPtr& obj, const PyObjPtr& key) override;

  PyObjPtr repr(const PyObjPtr& obj) override;

  void Initialize() override;
};

PyObjPtr CreatePyDict();
PyObjPtr CreatePyDict(Collections::Map<PyObjPtr, PyObjPtr> dict);
using PyDictPtr = std::shared_ptr<PyDictionary>;
}  // namespace torchlight::Object

#endif