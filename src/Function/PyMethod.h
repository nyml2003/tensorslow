#ifndef TORCHLIGHT_FUNCTION_PYMETHOD_H
#define TORCHLIGHT_FUNCTION_PYMETHOD_H

#include "Object/Klass.h"
#include "Object/PyObject.h"

namespace torchlight::Object {

class MethodKlass : public Klass {
 public:
  MethodKlass();
  static KlassPtr Self();
  PyObjPtr repr(PyObjPtr obj) override;

  void Initialize() override;
};

class PyMethod : public PyObject {
 public:
  explicit PyMethod(PyObjPtr owner, PyObjPtr method);

  [[nodiscard]] PyObjPtr Method() const;

  [[nodiscard]] PyObjPtr Owner() const;

 private:
  PyObjPtr owner;
  PyObjPtr method;
};

PyObjPtr CreatePyMethod(PyObjPtr owner, PyObjPtr method);
}  // namespace torchlight::Object

#endif