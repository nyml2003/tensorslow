#ifndef TORCHLIGHT_OBJECT_PYBOOLEAN_H
#define TORCHLIGHT_OBJECT_PYBOOLEAN_H

#include "object/Klass.h"
#include "object/PyInteger.h"

namespace torchlight::object {

class BooleanKlass : public Klass {
 public:
  explicit BooleanKlass();
  static KlassPtr Self();

  PyObjPtr _bool_(PyObjPtr obj) override;

  PyObjPtr _serialize_(PyObjPtr obj) override;

  
};

class PyBoolean : public PyInteger {
 public:
  explicit PyBoolean(bool value);
  static PyBoolPtr False();

  static PyBoolPtr True();

  static PyBoolPtr Constant(bool value);

  bool Value() const;
};

using PyBoolPtr = std::shared_ptr<PyBoolean>;
}  // namespace torchlight::object

#endif  // TORCHLIGHT_OBJECT_PYBOOLEAN_H