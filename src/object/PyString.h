#ifndef TORCHLIGHT_OBJECT_PYSTRING_H
#define TORCHLIGHT_OBJECT_PYSTRING_H

#include "Object/Common.h"
#include "Object/Klass.h"
#include "Object/PyObject.h"

namespace torchlight::Object {

class PyString : public PyObject {
 private:
  Collections::String value;

 public:
  explicit PyString(Collections::String value);

  [[nodiscard]] Collections::String Value() const;
};

using PyStrPtr = std::shared_ptr<PyString>;

PyStrPtr CreatePyString(Collections::String value);

class StringKlass : public Klass {
 public:
  explicit StringKlass();
  static KlassPtr Self();

  PyObjPtr add(PyObjPtr lhs, PyObjPtr rhs) override;

  PyObjPtr repr(PyObjPtr obj) override;

  PyObjPtr eq(PyObjPtr lhs, PyObjPtr rhs) override;

  PyObjPtr _serialize_(PyObjPtr obj) override;
};

}  // namespace torchlight::Object

#endif  // TORCHLIGHT_OBJECT_PYSTRING_H
