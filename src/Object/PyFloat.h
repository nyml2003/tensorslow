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

  PyObjPtr allocateInstance(const PyObjPtr& klass, const PyObjPtr& args)
    override;

  PyObjPtr add(const PyObjPtr& lhs, const PyObjPtr& rhs) override;

  PyObjPtr sub(const PyObjPtr& lhs, const PyObjPtr& rhs) override;

  PyObjPtr mul(const PyObjPtr& lhs, const PyObjPtr& rhs) override;

  PyObjPtr div(const PyObjPtr& lhs, const PyObjPtr& rhs) override;

  PyObjPtr repr(const PyObjPtr& obj) override;

  PyObjPtr _serialize_(const PyObjPtr& obj) override;

  PyObjPtr eq(const PyObjPtr& lhs, const PyObjPtr& rhs) override;

  void Initialize() override;
};

PyObjPtr CreatePyFloat(double value);
using PyFloatPtr = std::shared_ptr<PyFloat>;
}  // namespace torchlight::Object

#endif  // TORCHLIGHT_OBJECT_PYFLOAT_H
