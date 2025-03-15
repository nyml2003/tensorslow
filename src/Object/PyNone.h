#ifndef TORCHLIGHT_OBJECT_PYNONE_H
#define TORCHLIGHT_OBJECT_PYNONE_H

#include "Object/Object.h"
#include "Object/ObjectHelper.h"
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
  PyObjPtr str(const PyObjPtr& obj) override { return repr(obj); }

  PyObjPtr eq(const PyObjPtr& lhs, const PyObjPtr& rhs) override;

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