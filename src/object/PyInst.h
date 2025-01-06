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

PyInstPtr CreateLoadConst(collections::Index index);

PyInstPtr CreateBinaryAdd();

PyInstPtr CreateBinarySubtract();


PyInstPtr CreatePrint();

PyInstPtr CreateStoreName(collections::Index index);

PyInstPtr CreateLoadName(collections::Index index);

PyInstPtr CreateStoreFast(collections::Index index);

PyInstPtr CreateLoadFast(collections::Index index);

PyInstPtr CreateCompareOp(CompareOp op);

PyInstPtr CreatePopJumpIfFalse(int64_t index);

PyInstPtr CreatePopJumpIfTrue(int64_t index);

PyInstPtr CreateMakeFunction();

PyInstPtr CreateCallFunction(collections::Index argumentCount);

PyInstPtr CreateReturnValue();

PyInstPtr CreateLoadGlobal(collections::Index index);



}  // namespace torchlight::object

#endif