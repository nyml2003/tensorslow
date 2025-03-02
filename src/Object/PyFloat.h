#ifndef TORCHLIGHT_OBJECT_PYFLOAT_H
#define TORCHLIGHT_OBJECT_PYFLOAT_H

#include "Object/ObjectHelper.h"
#include "Object/PyString.h"

namespace torchlight::Object {

class FloatKlass : public Klass {
 public:
  explicit FloatKlass() = default;
  
  static KlassPtr Self() {
    static KlassPtr instance = std::make_shared<FloatKlass>();
    LoadClass(CreatePyString("float")->as<PyString>(), instance);
    ConfigureBasicAttributes(instance);
    return instance;
  }

  PyObjPtr construct(const PyObjPtr& klass, const PyObjPtr& args) override;

  PyObjPtr add(const PyObjPtr& lhs, const PyObjPtr& rhs) override;

  PyObjPtr sub(const PyObjPtr& lhs, const PyObjPtr& rhs) override;

  PyObjPtr mul(const PyObjPtr& lhs, const PyObjPtr& rhs) override;

  PyObjPtr div(const PyObjPtr& lhs, const PyObjPtr& rhs) override;

  PyObjPtr repr(const PyObjPtr& obj) override;

  PyObjPtr _serialize_(const PyObjPtr& obj) override;

  PyObjPtr eq(const PyObjPtr& lhs, const PyObjPtr& rhs) override;
};

class PyFloat : public PyObject {
 private:
  double value;

 public:
  explicit PyFloat(double value) : PyObject(FloatKlass::Self()), value(value) {}

  [[nodiscard]] double Value() const { return value; }
};

inline PyObjPtr CreatePyFloat(double value) {
  return std::make_shared<PyFloat>(value);
}
using PyFloatPtr = std::shared_ptr<PyFloat>;
}  // namespace torchlight::Object

#endif  // TORCHLIGHT_OBJECT_PYFLOAT_H
