#ifndef TORCHLIGHT_OBJECT_PYDICTIONARY_H
#define TORCHLIGHT_OBJECT_PYDICTIONARY_H

#include <map>
#include "Collections/Map.h"
#include "Common.h"
#include "Object/Klass.h"
#include "Object/PyObject.h"

namespace torchlight::Object {

class DictionaryKlass : public Klass {
 public:
  explicit DictionaryKlass() = default;
  static KlassPtr Self() {
    static KlassPtr instance = std::make_shared<DictionaryKlass>();
    return instance;
  }

  PyObjPtr init(const PyObjPtr& klass, const PyObjPtr& args) override;

  PyObjPtr setitem(
    const PyObjPtr& obj,
    const PyObjPtr& key,
    const PyObjPtr& value
  ) override;

  PyObjPtr getitem(const PyObjPtr& obj, const PyObjPtr& key) override;
  PyObjPtr delitem(const PyObjPtr& obj, const PyObjPtr& key) override;
  PyObjPtr contains(const PyObjPtr& obj, const PyObjPtr& key) override;
  PyObjPtr repr(const PyObjPtr& obj) override;
  PyObjPtr str(const PyObjPtr& obj) override;
  PyObjPtr iter(const PyObjPtr& obj) override;
  static void Initialize();
};

class PyDictionary : public PyObject {
 private:
  Collections::Map<PyObjPtr, PyObjPtr> dict;

 public:
  explicit PyDictionary() : PyObject(DictionaryKlass::Self()) {}

  void Put(const PyObjPtr& key, const PyObjPtr& value);

  PyObjPtr Get(const PyObjPtr& key);

  void Remove(const PyObjPtr& key);

  bool Contains(const PyObjPtr& key);

  Index Size() const;

  PyObjPtr GetItem(Index index) const;
};

PyObjPtr CreatePyDict();
using PyDictPtr = std::shared_ptr<PyDictionary>;
}  // namespace torchlight::Object

#endif