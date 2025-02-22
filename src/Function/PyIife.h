#ifndef TORCHLIGHT_FUNCTION_IIFE_H
#define TORCHLIGHT_FUNCTION_IIFE_H

#include "Object/Klass.h"
#include "Object/PyObject.h"

#include <functional>

namespace torchlight::Object {

using TypeFunction = std::function<PyObjPtr(PyObjPtr)>;

class IifeKlass : public Klass {
 public:
  explicit IifeKlass();

  static KlassPtr Self();

  PyObjPtr repr(PyObjPtr self) override;

  void Initialize() override;
};

class PyIife : public PyObject {
 private:
  TypeFunction nativeFunction;

 public:
  explicit PyIife(TypeFunction nativeFunction);

  PyObjPtr Call(PyObjPtr args);
};

using PyIifePtr = std::shared_ptr<PyIife>;

PyObjPtr CreatePyIife(TypeFunction nativeFunction);

}  // namespace torchlight::Object

#endif