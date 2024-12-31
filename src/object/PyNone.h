#ifndef TORCHLIGHT_OBJECT_PYNONE_H
#define TORCHLIGHT_OBJECT_PYNONE_H

#include "object/Klass.h"

namespace torchlight::object {

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

}  // namespace torchlight::object

#endif