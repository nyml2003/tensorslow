#ifndef TENSORSLOW_OBJECT_IIFE_H
#define TENSORSLOW_OBJECT_IIFE_H
#include "Object/Core/PyObject.h"

#include <functional>

namespace tensorslow::Object {

using TypeFunction = std::function<PyObjPtr(PyObjPtr)>;

class IifeKlass : public Klass {
 public:
  explicit IifeKlass() = default;

  static KlassPtr Self() {
    static KlassPtr instance = std::make_shared<IifeKlass>();
    return instance;
  }

  void Initialize() override;

  PyObjPtr str(const PyObjPtr& self) override;
};

class PyIife : public PyObject {
 private:
  TypeFunction nativeFunction;

 public:
  explicit PyIife(TypeFunction nativeFunction)
    : PyObject(IifeKlass::Self()), nativeFunction(std::move(nativeFunction)) {}

  PyObjPtr Call(const PyObjPtr& args) { return nativeFunction(args); }
};

inline PyObjPtr CreatePyIife(TypeFunction nativeFunction) {
  return std::make_shared<PyIife>(std::move(nativeFunction));
}

}  // namespace tensorslow::Object

#endif