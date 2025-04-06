#ifndef TORCHLIGHT_OBJECT_PYNONE_H
#define TORCHLIGHT_OBJECT_PYNONE_H

#include "Function/ObjectHelper.h"
#include "Object/Core/CoreHelper.h"
#include "Object/Object.h"
#include "Object/String/PyString.h"

namespace torchlight::Object {

class NoneKlass : public Klass {
 public:
  explicit NoneKlass() = default;

  static KlassPtr Self() {
    static KlassPtr instance = std::make_shared<NoneKlass>();
    return instance;
  }

  void Initialize() override {
    if (this->isInitialized) {
      return;
    }
    LoadClass(CreatePyString("NoneType")->as<PyString>(), Self());
    ConfigureBasicAttributes(Self());
    this->isInitialized = true;
  }

  PyObjPtr repr(const PyObjPtr& obj) override;
  PyObjPtr str(const PyObjPtr& obj) override { return repr(obj); }
  PyObjPtr eq(const PyObjPtr& lhs, const PyObjPtr& rhs) override;
  PyObjPtr boolean(const PyObjPtr& obj) override;

  PyObjPtr _serialize_(const PyObjPtr& obj) override;
};
class PyNone;
using PyNonePtr = std::shared_ptr<PyNone>;
class PyNone : public PyObject {
 public:
  explicit PyNone();
  static PyNonePtr Instance();
};

inline PyNonePtr CreatePyNone() {
  return PyNone::Instance();
}

}  // namespace torchlight::Object

#endif