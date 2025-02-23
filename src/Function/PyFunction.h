#ifndef TORCHLIGHT_FUNCTION_PYFUNCTION_H
#define TORCHLIGHT_FUNCTION_PYFUNCTION_H

#include "ByteCode/PyCode.h"
#include "Object/PyObject.h"

namespace torchlight::Object {
class PyFunction : public PyObject {
 private:
  PyCodePtr code;
  PyDictPtr globals;

 public:
  PyFunction(const PyObjPtr& code, const PyObjPtr& globals);

  [[nodiscard]] PyCodePtr Code() const;

  [[nodiscard]] PyDictPtr& Globals();

  [[nodiscard]] PyStrPtr Name() const;
};

using PyFunctionPtr = std::shared_ptr<PyFunction>;

class FunctionKlass : public Klass {
 public:
  FunctionKlass();

  static KlassPtr Self();

  PyObjPtr repr(const PyObjPtr& self) override;

  void Initialize() override;
};

PyObjPtr CreatePyFunction(const PyObjPtr& code, const PyObjPtr& globals);

}  // namespace torchlight::Object

#endif