#ifndef TORCHLIGHT_OBJECT_PYBOOLEAN_H
#define TORCHLIGHT_OBJECT_PYBOOLEAN_H

#include "Object/Klass.h"
#include "Object/PyInteger.h"

namespace torchlight::Object {

class BooleanKlass : public Klass {
 public:
  explicit BooleanKlass();
  static KlassPtr Self();

  PyObjPtr _bool_(PyObjPtr obj) override;

  PyObjPtr _serialize_(PyObjPtr obj) override;

  PyObjPtr repr(PyObjPtr obj) override;

  PyObjPtr eq(PyObjPtr lhs, PyObjPtr rhs) override;
};

PyBoolPtr CreatePyBoolean(bool value);

class PyBoolean : public PyInteger {
 public:
  explicit PyBoolean(bool value);
  static PyBoolPtr False();

  static PyBoolPtr True();

  bool Value() const;
};

using PyBoolPtr = std::shared_ptr<PyBoolean>;
}  // namespace torchlight::Object

#endif  // TORCHLIGHT_OBJECT_PYBOOLEAN_H