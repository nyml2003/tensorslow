#ifndef TORCHLIGHT_OBJECT_PYMETHOD_H
#define TORCHLIGHT_OBJECT_PYMETHOD_H

#include "Function/BuiltinFunction.h"
#include "Object/Core/CoreHelper.h"
#include "Object/String/PyString.h"
namespace torchlight::Object {

class MethodKlass : public Klass {
 public:
  explicit MethodKlass() = default;

  static KlassPtr Self() {
    static KlassPtr instance = std::make_shared<MethodKlass>();
    return instance;
  }

  void Initialize() override {
    if (this->isInitialized) {
      return;
    }
    LoadClass(CreatePyString("method")->as<PyString>(), Self());
    ConfigureBasicAttributes(Self());
    this->isInitialized = true;
  }
  PyObjPtr repr(const PyObjPtr& obj) override;
};

class PyMethod : public PyObject {
 public:
  explicit PyMethod(PyObjPtr owner, PyObjPtr method)
    : PyObject(MethodKlass::Self()),
      owner(std::move(owner)),
      method(std::move(method)) {}

  [[nodiscard]] PyObjPtr Method() const { return method; }

  [[nodiscard]] PyObjPtr Owner() const { return owner; }

 private:
  PyObjPtr owner;
  PyObjPtr method;
};
using PyMethodPtr = std::shared_ptr<PyMethod>;
inline PyObjPtr CreatePyMethod(PyObjPtr owner, PyObjPtr method) {
  return std::make_shared<PyMethod>(std::move(owner), std::move(method));
}

}  // namespace torchlight::Object

#endif