#ifndef TENSORSLOW_OBJECT_PYMETHOD_H
#define TENSORSLOW_OBJECT_PYMETHOD_H

#include "Object/Core/CoreHelper.h"
#include "Object/String/PyString.h"
namespace tensorslow::Object {

class MethodKlass : public KlassBase<MethodKlass> {
 public:
  explicit MethodKlass() = default;

  void Initialize() override {
    if (this->IsInitialized()) {
      return;
    }
    LoadClass(CreatePyString("method")->as<PyString>(), Self());
    ConfigureBasicAttributes(Self());
    this->SetInitialized();
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

}  // namespace tensorslow::Object

#endif