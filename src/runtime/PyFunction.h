#ifndef TORCHLIGHT_RUNTIME_PYFUNCTION_H
#define TORCHLIGHT_RUNTIME_PYFUNCTION_H

#include "object/PyCode.h"
#include "object/PyObject.h"
#include "object/common.h"

namespace torchlight::runtime {
class PyFunction : public object::PyObject {
 private:
  object::PyCodePtr code;
  object::PyDictPtr globals;

 public:
  PyFunction(object::PyCodePtr code, object::PyDictPtr globals);

  [[nodiscard]] object::PyCodePtr Code() const;

  [[nodiscard]] object::PyDictPtr& Globals();

  [[nodiscard]] object::PyStrPtr Name() const;
};

using PyFunctionPtr = std::shared_ptr<PyFunction>;

class FunctionKlass : public object::Klass {
 public:
  FunctionKlass();

  static object::KlassPtr Self();

  object::PyObjPtr repr(object::PyObjPtr self) override;
};

}  // namespace torchlight::runtime

#endif