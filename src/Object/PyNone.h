#ifndef TORCHLIGHT_OBJECT_PYNONE_H
#define TORCHLIGHT_OBJECT_PYNONE_H

#include "Object/PyString.h"

namespace torchlight::Object {

class NoneKlass : public Klass {
 public:
  explicit NoneKlass() = default;

  static KlassPtr Self() {
    static KlassPtr instance = std::make_shared<NoneKlass>();
    LoadClass(CreatePyString("None")->as<PyString>(), instance);
    ConfigureBasicAttributes(instance);
    return instance;
  }

  PyObjPtr repr(const PyObjPtr& obj) override;

  PyObjPtr _serialize_(const PyObjPtr& obj) override;
};

class PyNone : public PyObject {
 public:
  explicit PyNone();
  static PyObjPtr Instance();
};

inline PyObjPtr CreatePyNone() {
  return PyNone::Instance();
}

}  // namespace torchlight::Object

#endif