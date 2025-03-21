#ifndef TORCHLIGHT_OBJECT_PYINST_H
#define TORCHLIGHT_OBJECT_PYINST_H

#include "ByteCode/ByteCode.h"
#include "Function/ObjectHelper.h"
#include "Object/Core/CoreHelper.h"
#include "Object/Object.h"
#include "Object/String/PyString.h"

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
  explicit InstKlass() = default;

  static KlassPtr Self() {
    static KlassPtr instance = std::make_shared<InstKlass>();
    LoadClass(CreatePyString("Instruction")->as<PyString>(), instance);
    ConfigureBasicAttributes(instance);
    return instance;
  }

  PyObjPtr _serialize_(const PyObjPtr& obj) override;

  PyObjPtr repr(const PyObjPtr& obj) override;

  PyObjPtr str(const PyObjPtr& obj) override { return repr(obj); }
};

PyInstPtr CreateLoadConst(Index index);

PyInstPtr CreateBinaryAdd();

PyInstPtr CreateBinarySubtract();

PyInstPtr CreateBinaryMultiply();

PyInstPtr CreateStoreName(Index index);

PyInstPtr CreateLoadName(Index index);

PyInstPtr CreateStoreFast(Index index);

PyInstPtr CreateLoadFast(Index index);

PyInstPtr CreateCompareOp(CompareOp compOp);

PyInstPtr CreatePopJumpIfFalse(int64_t index);

PyInstPtr CreatePopJumpIfTrue(int64_t index);

PyInstPtr CreateMakeFunction();

PyInstPtr CreateCallFunction(Index argumentCount);

PyInstPtr CreateReturnValue();

PyInstPtr CreateLoadGlobal(Index index);

PyInstPtr CreatePopTop();

PyInstPtr CreateLoadAttr(Index index);

inline PyInstPtr CreateBuildList(Index size) {
  return std::make_shared<PyInst>(ByteCode::BUILD_LIST, size);
}

inline PyInstPtr CreateBuildSlice() {
  return std::make_shared<PyInst>(ByteCode::BUILD_SLICE);
}

inline PyInstPtr CreateBuildMap(Index size) {
  return std::make_shared<PyInst>(ByteCode::BUILD_MAP, size);
}

PyInstPtr CreateBinaryMatrixMultiply();

PyInstPtr CreateJumpAbsolute(Index index);

PyInstPtr CreateBinarySubscr();

PyInstPtr CreateStoreSubscr();

PyInstPtr CreateGetIter();

PyInstPtr CreateForIter(Index index);

PyInstPtr CreateLoadBuildClass();

PyInstPtr CreateStoreAttr(Index index);

PyInstPtr CreateNop();

inline PyInstPtr CreateUnaryPositive() {
  return std::make_shared<PyInst>(ByteCode::UNARY_POSITIVE);
}

inline PyInstPtr CreateUnaryNegative() {
  return std::make_shared<PyInst>(ByteCode::UNARY_NEGATIVE);
}

inline PyInstPtr CreateUnaryNot() {
  return std::make_shared<PyInst>(ByteCode::UNARY_NOT);
}

inline PyInstPtr CreateUnaryInvert() {
  return std::make_shared<PyInst>(ByteCode::UNARY_INVERT);
}

inline PyInstPtr CreateBinaryPower() {
  return std::make_shared<PyInst>(ByteCode::BINARY_POWER);
}

inline PyInstPtr CreateBinaryModulo() {
  return std::make_shared<PyInst>(ByteCode::BINARY_MODULO);
}

inline PyInstPtr CreateBinaryFloorDivide() {
  return std::make_shared<PyInst>(ByteCode::BINARY_FLOOR_DIVIDE);
}

inline PyInstPtr CreateBinaryTrueDivide() {
  return std::make_shared<PyInst>(ByteCode::BINARY_TRUE_DIVIDE);
}

inline PyInstPtr CreateBinaryXor() {
  return std::make_shared<PyInst>(ByteCode::BINARY_XOR);
}

inline PyInstPtr CreateBinaryAnd() {
  return std::make_shared<PyInst>(ByteCode::BINARY_AND);
}

inline PyInstPtr CreateBinaryOr() {
  return std::make_shared<PyInst>(ByteCode::BINARY_OR);
}

inline PyInstPtr CreateBinaryLShift() {
  return std::make_shared<PyInst>(ByteCode::BINARY_LSHIFT);
}

inline PyInstPtr CreateBinaryRShift() {
  return std::make_shared<PyInst>(ByteCode::BINARY_RSHIFT);
}

inline PyInstPtr CreateYieldValue() {
  return std::make_shared<PyInst>(ByteCode::YIELD_VALUE);
}

inline PyInstPtr CreateJumpForward(Index index) {
  return std::make_shared<PyInst>(ByteCode::JUMP_FORWARD, index);
}

}  // namespace torchlight::Object

#endif