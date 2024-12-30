#ifndef TORCHLIGHT_RUNTIME_PYINST_H
#define TORCHLIGHT_RUNTIME_PYINST_H

#include "object/ByteCode.h"
#include "object/Klass.h"
#include "object/PyObject.h"
#include "object/common.h"

namespace torchlight::object {

class PyInst : public PyObject {
 private:
  ByteCode code;
  OperandKind operand = NoneType();

 public:
  explicit PyInst(ByteCode code, OperandKind operand = NoneType());

  [[nodiscard]] ByteCode Code() const;

  [[nodiscard]] OperandKind Operand() const;
};

using PyInstPtr = std::shared_ptr<PyInst>;

class InstKlass : public Klass {
 public:
  explicit InstKlass();
  static KlassPtr Self();

  PyObjPtr _serialize_(PyObjPtr obj) override;

  PyObjPtr repr(PyObjPtr obj) override;
};

PyInstPtr CreateLoadConst(Index index);

PyInstPtr CreateBinaryAdd();

PyInstPtr CreatePrint();

}  // namespace torchlight::object

#endif