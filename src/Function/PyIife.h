#ifndef TORCHLIGHT_FUNCTION_IIFE_H
#define TORCHLIGHT_FUNCTION_IIFE_H
#include "Object/PyObject.h"

#include <functional>

namespace torchlight::Object {

using TypeFunction = std::function<PyObjPtr(PyObjPtr)>;

class IifeKlass : public Klass {
 public:
  explicit IifeKlass() = default;

  static KlassPtr Self() {
    static KlassPtr instance = std::make_shared<IifeKlass>();
    return instance;
  }

  static void Initialize();
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

}  // namespace torchlight::Object

#endif