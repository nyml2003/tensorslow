#ifndef TORCHLIGHT_RUNTIME_PYINST_H
#define TORCHLIGHT_RUNTIME_PYINST_H

#include "ByteCode/ByteCode.h"
#include "Object/Klass.h"
#include "Object/PyObject.h"

namespace torchlight::Object {

class PyInst : public PyObject {
 private:
  ByteCode code;
  OperandKind operand = None();

 public:
  explicit PyInst(ByteCode code, OperandKind operand = None());

  [[nodiscard]] ByteCode Code() const;

  [[nodiscard]] OperandKind Operand() const;
};

using PyInstPtr = std::shared_ptr<PyInst>;

class InstKlass : public Klass {
 public:
  explicit InstKlass();
  static KlassPtr Self();

  PyObjPtr _serialize_(const PyObjPtr& obj) override;

  PyObjPtr repr(const PyObjPtr& obj) override;

  void Initialize() override;
};

PyInstPtr CreateLoadConst(Index index);

PyInstPtr CreateBinaryAdd();

PyInstPtr CreateBinarySubtract();

PyInstPtr CreateBinaryMultiply();

PyInstPtr CreateStoreName(Index index);

PyInstPtr CreateLoadName(Index index);

PyInstPtr CreateStoreFast(Index index);

PyInstPtr CreateLoadFast(Index index);

PyInstPtr CreateCompareOp(CompareOp op);

PyInstPtr CreatePopJumpIfFalse(int64_t index);

PyInstPtr CreatePopJumpIfTrue(int64_t index);

PyInstPtr CreateMakeFunction();

PyInstPtr CreateCallFunction(Index argumentCount);

PyInstPtr CreateReturnValue();

PyInstPtr CreateLoadGlobal(Index index);

PyInstPtr CreatePopTop();

PyInstPtr CreateLoadAttr(Index index);

PyInstPtr CreateBuildList(Index size);

PyInstPtr CreateBinaryMatrixMultiply();

PyInstPtr CreateJumpAbsolute(Index index);

PyInstPtr CreateBinarySubscr();

PyInstPtr CreateStoreSubscr();

PyInstPtr CreateGetIter();

PyInstPtr CreateForIter(Index index);

}  // namespace torchlight::Object

#endif