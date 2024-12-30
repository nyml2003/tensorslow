#ifndef TORCHLIGHT_OBJECT_PYFLOAT_H
#define TORCHLIGHT_OBJECT_PYFLOAT_H

#include "object/Klass.h"
#include "object/PyObject.h"

namespace torchlight::object {

class PyFloat : public PyObject {
 private:
  double value;

 public:
  explicit PyFloat(double value);

  [[nodiscard]] double Value() const;
};

using PyFloatPtr = std::shared_ptr<PyFloat>;

class FloatKlass : public Klass {
 public:
  explicit FloatKlass();

  static KlassPtr Self();

  PyObjPtr add(PyObjPtr lhs, PyObjPtr rhs) override;

  PyObjPtr sub(PyObjPtr lhs, PyObjPtr rhs) override;

  PyObjPtr mul(PyObjPtr lhs, PyObjPtr rhs) override;

  PyObjPtr div(PyObjPtr lhs, PyObjPtr rhs) override;

  PyObjPtr repr(PyObjPtr obj) override;

  PyObjPtr _serialize_(PyObjPtr obj) override;
};

}  // namespace torchlight::object

#endif  // TORCHLIGHT_OBJECT_PYFLOAT_H
