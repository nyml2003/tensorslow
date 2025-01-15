#include "collections/common.h"
#include "collections/impl/Bytes.h"
#include "collections/impl/String.h"
#include "object/PyBytes.h"
#include "object/PyInst.h"
#include "object/PyString.h"

namespace torchlight::object {

using collections::Bytes;
using collections::CreateStringWithCString;
using collections::Index;
using collections::Serialize;
using collections::String;
using collections::ToString;
PyInst::PyInst(ByteCode code, OperandKind operand)
  : PyObject(InstKlass::Self()), code(code), operand(operand) {}

[[nodiscard]] ByteCode PyInst::Code() const {
  return code;
}

[[nodiscard]] OperandKind PyInst::Operand() const {
  return operand;
}

InstKlass::InstKlass() : Klass(CreateStringWithCString("inst")) {}

KlassPtr InstKlass::Self() {
  static KlassPtr instance = std::make_shared<InstKlass>();
  return instance;
}

PyObjPtr InstKlass::_serialize_(PyObjPtr obj) {
  if (obj->Klass() != Self()) {
    return nullptr;
  }
  auto inst = std::dynamic_pointer_cast<PyInst>(obj);
  Bytes bytes = Serialize(inst->Code());
  std::visit(
    overload{
      [&bytes](NoneType) {},
      [&bytes](Index index) { bytes.Concat(Serialize(index)); },
      [&bytes](CompareOp op) { bytes.Concat(Serialize(op)); },
      [&bytes](int64_t index) { bytes.Concat(Serialize(index)); }
    },
    inst->Operand()
  );
  return std::make_shared<PyBytes>(bytes);
}

PyObjPtr InstKlass::repr(PyObjPtr obj) {
  if (obj->Klass() != Self()) {
    return nullptr;
  }
  auto inst = std::dynamic_pointer_cast<PyInst>(obj);
  String result = CreateStringWithCString("<inst ")
                    .Add(ToString(inst->Code()))
                    .Add(CreateStringWithCString(" "));
  std::visit(
    overload{
      [&result](NoneType) {},
      [&result](Index index) { result.Concat(ToString(index)); },
      [&result](CompareOp op) { result.Concat(ToString(op)); },
      [&result](int64_t index) { result.Concat(ToString(index)); }
    },
    inst->Operand()
  );
  result.Concat(CreateStringWithCString(">\n"));
  return CreatePyString(result);
}

PyInstPtr CreateLoadConst(Index index) {
  return std::make_shared<PyInst>(ByteCode::LOAD_CONST, index);
}

PyInstPtr CreateBinaryAdd() {
  return std::make_shared<PyInst>(ByteCode::BINARY_ADD);
}

PyInstPtr CreatePrint() {
  return std::make_shared<PyInst>(ByteCode::PRINT);
}

PyInstPtr CreateStoreName(Index index) {
  return std::make_shared<PyInst>(ByteCode::STORE_NAME, index);
}

PyInstPtr CreateLoadName(Index index) {
  return std::make_shared<PyInst>(ByteCode::LOAD_NAME, index);
}

PyInstPtr CreateStoreFast(Index index) {
  return std::make_shared<PyInst>(ByteCode::STORE_FAST, index);
}

PyInstPtr CreateLoadFast(Index index) {
  return std::make_shared<PyInst>(ByteCode::LOAD_FAST, index);
}

PyInstPtr CreateCompareOp(CompareOp op) {
  return std::make_shared<PyInst>(ByteCode::COMPARE_OP, op);
}

PyInstPtr CreatePopJumpIfFalse(int64_t index) {
  return std::make_shared<PyInst>(ByteCode::POP_JUMP_IF_FALSE, index);
}

PyInstPtr CreatePopJumpIfTrue(int64_t index) {
  return std::make_shared<PyInst>(ByteCode::POP_JUMP_IF_TRUE, index);
}

PyInstPtr CreateMakeFunction() {
  return std::make_shared<PyInst>(ByteCode::MAKE_FUNCTION);
}

PyInstPtr CreateCallFunction(Index argumentCount) {
  return std::make_shared<PyInst>(ByteCode::CALL_FUNCTION, argumentCount);
}

PyInstPtr CreateReturnValue() {
  return std::make_shared<PyInst>(ByteCode::RETURN_VALUE);
}

PyInstPtr CreateLoadGlobal(Index index) {
  return std::make_shared<PyInst>(ByteCode::LOAD_GLOBAL, index);
}

PyInstPtr CreateBinarySubtract() {
  return std::make_shared<PyInst>(ByteCode::BINARY_SUBTRACT);
}

}  // namespace torchlight::object