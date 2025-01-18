#ifndef TORCHLIGHT_OBJECT_PYLIST_H
#define TORCHLIGHT_OBJECT_PYLIST_H

#include "Collections/List.h"
#include "Object/Klass.h"
#include "Object/PyObject.h"

namespace torchlight::Object {
class PyList : public PyObject {
 private:
  Collections::List<PyObjPtr> value;

 public:
  explicit PyList(Collections::List<PyObjPtr> value);

  [[nodiscard]] Collections::List<PyObjPtr>& Value();

  void Append(PyObjPtr obj);

  PyStrPtr Join(const PyStrPtr& separator);
};

using PyListPtr = std::shared_ptr<PyList>;

PyListPtr CreatePyList(Index capacity);

PyListPtr CreatePyList(Collections::List<PyObjPtr> list, Index capacity);

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
};

}  // namespace torchlight::Object

#endif