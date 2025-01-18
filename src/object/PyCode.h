#ifndef TORCHLIGHT_RUNTIME_PYCODE_H
#define TORCHLIGHT_RUNTIME_PYCODE_H

#include "Object/Klass.h"
#include "Object/PyBytes.h"
#include "Object/PyObject.h"

namespace torchlight::Object {

class PyCode : public PyObject {
  friend class CodeKlass;

 private:
  PyBytesPtr byteCode;
  PyListPtr instructions;
  PyListPtr consts;
  PyListPtr names;
  PyListPtr varNames;
  PyStrPtr name;
  Index nLocals;

 public:
  explicit PyCode(
    const PyObjPtr& byteCodes,
    const PyObjPtr& consts,
    const PyObjPtr& names,
    const PyObjPtr& varNames,
    const PyObjPtr& name,
    Index nLocals
  );

  [[nodiscard]] PyListPtr Instructions();

  void SetInstructions(const PyListPtr& insts);

  PyBytesPtr ByteCode() const;

  [[nodiscard]] PyListPtr Consts() const;

  [[nodiscard]] PyListPtr Names() const;

  [[nodiscard]] PyStrPtr Name() const;

  [[nodiscard]] PyListPtr VarNames() const;

  [[nodiscard]] Index NLocals() const;
};

using PyCodePtr = std::shared_ptr<PyCode>;

class CodeKlass : public Object::Klass {
 public:
  explicit CodeKlass();
  static Object::KlassPtr Self();

  PyObjPtr repr(PyObjPtr self) override;

  PyObjPtr _serialize_(PyObjPtr self) override;
};

}  // namespace torchlight::Object

#endif  // TORCHLIGHT_RUNTIME_PYCODE_H
