#ifndef TORCHLIGHT_OBJECT_PYDICTIONARY_H
#define TORCHLIGHT_OBJECT_PYDICTIONARY_H

#include "Common.h"
#include "Object/Core/Klass.h"
#include "Object/Core/PyObject.h"

#include <map>

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
  PyObjPtr len(const PyObjPtr& obj) override;
  static void Initialize();
};

bool KeyCompare(const PyObjPtr& lhs, const PyObjPtr& rhs);

class PyDictionary : public PyObject {
 private:
  std::map<PyObjPtr, PyObjPtr, decltype(KeyCompare)*> dict{KeyCompare};

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