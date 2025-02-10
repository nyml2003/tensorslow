#ifndef TORCHLIGHT_OBJECT_PYNONE_H
#define TORCHLIGHT_OBJECT_PYNONE_H

#include "Object/Klass.h"
#include "Object/PyObject.h"

namespace torchlight::Object {

class NoneKlass : public Klass {
 public:
  explicit NoneKlass();
  static KlassPtr Self();

  PyObjPtr _serialize_(PyObjPtr obj) override;

  PyObjPtr repr(PyObjPtr obj) override;

  void Initialize() override;
};

class PyNone : public PyObject {
 public:
  explicit PyNone();
  static PyObjPtr Instance();
};

PyObjPtr CreatePyNone();

}  // namespace torchlight::Object

#endif