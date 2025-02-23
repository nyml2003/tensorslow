#ifndef TORCHLIGHT_OBJECT_PYLIST_H
#define TORCHLIGHT_OBJECT_PYLIST_H

#include "Collections/List.h"
#include "Object/Klass.h"
#include "Object/PyObject.h"

namespace torchlight::Object {
class PyList : public PyObject {
  friend class ListKlass;

 private:
  Collections::List<PyObjPtr> value;

 public:
  explicit PyList(Collections::List<PyObjPtr> value);

  void Append(PyObjPtr obj);

  PyObjPtr Join(const PyObjPtr& separator);

  Index Length() const;

  bool Contains(const PyObjPtr& obj) const;

  Index IndexOf(const PyObjPtr& obj) const;

  PyObjPtr GetItem(Index index) const;

  void SetItem(Index index, const PyObjPtr& obj);
};

class ListKlass : public Klass {
 public:
  explicit ListKlass();
  static KlassPtr Self();

  PyObjPtr add(const PyObjPtr& lhs, const PyObjPtr& rhs) override;

  PyObjPtr repr(const PyObjPtr& obj) override;

  PyObjPtr _serialize_(const PyObjPtr& obj) override;

  PyObjPtr getitem(const PyObjPtr& obj, const PyObjPtr& key) override;

  PyObjPtr setitem(
    const PyObjPtr& obj,
    const PyObjPtr& key,
    const PyObjPtr& value
  ) override;

  PyObjPtr eq(const PyObjPtr& lhs, const PyObjPtr& rhs) override;

  PyObjPtr len(const PyObjPtr& obj) override;

  PyObjPtr contains(const PyObjPtr& obj, const PyObjPtr& key) override;

  PyObjPtr allocateInstance(const PyObjPtr& type, const PyObjPtr& args)
    override;

  PyObjPtr iter(const PyObjPtr& obj) override;

  void Initialize() override;
};

PyObjPtr CreatePyList(Index capacity);

PyObjPtr CreatePyList(Collections::List<PyObjPtr> list);

using PyListPtr = std::shared_ptr<PyList>;

PyObjPtr Join(const PyObjPtr& args);

PyObjPtr Append(const PyObjPtr& args);

PyObjPtr ListIndex(const PyObjPtr& args);
}  // namespace torchlight::Object

#endif