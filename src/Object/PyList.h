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

  PyObjPtr add(PyObjPtr lhs, PyObjPtr rhs) override;

  PyObjPtr repr(PyObjPtr obj) override;

  PyObjPtr _serialize_(PyObjPtr obj) override;

  PyObjPtr getitem(PyObjPtr obj, PyObjPtr key) override;

  PyObjPtr setitem(PyObjPtr obj, PyObjPtr key, PyObjPtr value) override;

  PyObjPtr eq(PyObjPtr lhs, PyObjPtr rhs) override;

  PyObjPtr len(PyObjPtr obj) override;

  PyObjPtr contains(PyObjPtr obj, PyObjPtr key) override;

  PyObjPtr allocateInstance(PyObjPtr type, PyObjPtr args) override;

  PyObjPtr iter(PyObjPtr obj) override;

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