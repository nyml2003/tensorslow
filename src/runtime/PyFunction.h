#ifndef TORCHLIGHT_RUNTIME_PYFUNCTION_H
#define TORCHLIGHT_RUNTIME_PYFUNCTION_H

#include "Object/PyCode.h"
#include "Object/PyObject.h"

namespace torchlight::Runtime {
class PyFunction : public Object::PyObject {
 private:
  Object::PyCodePtr code;
  Object::PyDictPtr globals;

 public:
  PyFunction(Object::PyCodePtr code, Object::PyDictPtr globals);

  [[nodiscard]] Object::PyCodePtr Code() const;

  [[nodiscard]] Object::PyDictPtr& Globals();

  [[nodiscard]] Object::PyStrPtr Name() const;
};

using PyFunctionPtr = std::shared_ptr<PyFunction>;

class FunctionKlass : public Object::Klass {
 public:
  FunctionKlass();

  static Object::KlassPtr Self();

  Object::PyObjPtr repr(Object::PyObjPtr self) override;
};

}  // namespace torchlight::Runtime

#endif