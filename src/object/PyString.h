#ifndef TORCHLIGHT_OBJECT_PYSTRING_H
#define TORCHLIGHT_OBJECT_PYSTRING_H

#include "collections/String.h"
#include "object/Klass.h"
#include "object/PyObject.h"
#include "object/common.h"

namespace torchlight::object {

class PyString : public PyObject {
 private:
  collections::String value;

 public:
  explicit PyString(collections::String value);

  [[nodiscard]] collections::String Value() const;
};

using PyStrPtr = std::shared_ptr<PyString>;

class StringKlass : public Klass {
 public:
  explicit StringKlass();
  static KlassPtr Self();

  PyObjPtr add(PyObjPtr lhs, PyObjPtr rhs) override;

  PyObjPtr repr(PyObjPtr obj) override;

  PyObjPtr _serialize_(PyObjPtr obj) override;
};

}  // namespace torchlight::object

#endif  // TORCHLIGHT_OBJECT_PYSTRING_H
