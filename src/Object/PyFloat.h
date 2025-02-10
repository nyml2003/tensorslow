#ifndef TORCHLIGHT_OBJECT_PYFLOAT_H
#define TORCHLIGHT_OBJECT_PYFLOAT_H

#include "Object/Klass.h"
#include "Object/PyObject.h"

namespace torchlight::Object {

class PyFloat : public PyObject {
 private:
  double value;

 public:
  explicit PyFloat(double value);

  [[nodiscard]] double Value() const;
};

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

  PyObjPtr eq(PyObjPtr lhs, PyObjPtr rhs) override;

  void Initialize() override;
};

PyObjPtr CreatePyFloat(double value);
using PyFloatPtr = std::shared_ptr<PyFloat>;
}  // namespace torchlight::Object

#endif  // TORCHLIGHT_OBJECT_PYFLOAT_H
