#ifndef TORCHLIGHT_OBJECT_PYNONE_H
#define TORCHLIGHT_OBJECT_PYNONE_H

#include "Object/Klass.h"

namespace torchlight::Object {

class NoneKlass : public Klass {
 public:
  explicit NoneKlass();
  static KlassPtr Self();

  PyObjPtr _serialize_(PyObjPtr obj) override;

  PyObjPtr repr(PyObjPtr obj) override;
};

class PyNone : public PyObject {
 public:
  explicit PyNone();
  static PyObjPtr Instance();
};

using PyNonePtr = std::shared_ptr<PyNone>;

PyNonePtr CreatePyNone();

}  // namespace torchlight::Object

#endif