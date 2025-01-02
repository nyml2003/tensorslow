#ifndef TORCHLIGHT_OBJECT_PYLIST_H
#define TORCHLIGHT_OBJECT_PYLIST_H

#include "collections/List.h"
#include "object/Klass.h"
#include "object/PyObject.h"

namespace torchlight::object {
class PyList : public PyObject {
 private:
  collections::List<PyObjPtr> value;

 public:
  explicit PyList(collections::List<PyObjPtr> value);

  [[nodiscard]] collections::List<PyObjPtr> Value() const;
};

using PyListPtr = std::shared_ptr<PyList>;

class ListKlass : public Klass {
 public:
  explicit ListKlass();
  static KlassPtr Self();

  PyObjPtr add(PyObjPtr lhs, PyObjPtr rhs) override;

  PyObjPtr repr(PyObjPtr obj) override;

  PyObjPtr _serialize_(PyObjPtr obj) override;

  PyObjPtr getitem(PyObjPtr obj, PyObjPtr key) override;

  PyObjPtr setitem(PyObjPtr obj, PyObjPtr key, PyObjPtr value) override;
};

}  // namespace torchlight::object

#endif