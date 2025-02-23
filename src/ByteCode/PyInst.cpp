#include "ByteCode/PyInst.h"
#include "ByteCode/PyCode.h"
#include "Collections/BytesHelper.h"
#include "Collections/StringHelper.h"
#include "Object/PyBytes.h"
#include "Object/PyDictionary.h"
#include "Object/PyString.h"
#include "Object/PyType.h"

namespace torchlight::Object {

PyInst::PyInst(ByteCode code, OperandKind operand)
  : PyObject(InstKlass::Self()), code(code), operand(operand) {}

[[nodiscard]] ByteCode PyInst::Code() const {
  return code;
}

[[nodiscard]] OperandKind PyInst::Operand() const {
  return operand;
}

InstKlass::InstKlass() = default;

void InstKlass::Initialize() {
  SetType(CreatePyType(Self()));
  SetName(CreatePyString("inst"));
  SetAttributes(CreatePyDict());
  Klass::Initialize();
}

KlassPtr InstKlass::Self() {
  static KlassPtr instance = std::make_shared<InstKlass>();
  return instance;
}

PyObjPtr InstKlass::_serialize_(const PyObjPtr& obj) {
  if (obj->Klass() != Self()) {
    throw std::runtime_error("PyInst::_serialize_(): obj is not an inst object"
    );
  }
  auto inst = std::dynamic_pointer_cast<PyInst>(obj);
  Collections::Bytes bytes = Collections::Serialize(inst->Code());
  std::visit(
    overload{
      [&bytes](None) {},
      [&bytes](Index index) { bytes.Concat(Collections::Serialize(index)); },
      [&bytes](CompareOp op) { bytes.Concat(Collections::Serialize(op)); },
      [&bytes](int64_t index) { bytes.Concat(Collections::Serialize(index)); }
    },
    inst->Operand()
  );
  return std::make_shared<PyBytes>(bytes);
}

PyObjPtr InstKlass::repr(const PyObjPtr& obj) {
  if (obj->Klass() != Self()) {
    throw std::runtime_error("PyInst::repr(): obj is not an inst object");
  }
  auto inst = std::dynamic_pointer_cast<PyInst>(obj);
  Collections::String result =
    Collections::ToString(inst->Code())
      .Add(Collections::CreateStringWithCString(" "));
  std::visit(
    overload{
      [&result](None) {},
      [&result](Index index) { result.Concat(Collections::ToString(index)); },
      [&result](CompareOp op) { result.Concat(Collections::ToString(op)); },
      [&result](int64_t index) { result.Concat(Collections::ToString(index)); }
    },
    inst->Operand()
  );
  return CreatePyString(result);
}

PyInstPtr CreateLoadConst(Index index) {
  return std::make_shared<PyInst>(ByteCode::LOAD_CONST, index);
}

PyInstPtr CreateBinaryAdd() {
  return std::make_shared<PyInst>(ByteCode::BINARY_ADD);
}

PyInstPtr CreateBinaryMultiply() {
  return std::make_shared<PyInst>(ByteCode::BINARY_MULTIPLY);
}

PyInstPtr CreateBinaryMatrixMultiply() {
  return std::make_shared<PyInst>(ByteCode::BINARY_MATRIX_MULTIPLY);
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

PyInstPtr CreatePopTop() {
  return std::make_shared<PyInst>(ByteCode::POP_TOP);
}

PyInstPtr CreateLoadAttr(Index index) {
  return std::make_shared<PyInst>(ByteCode::LOAD_ATTR, index);
}

PyInstPtr CreateBuildList(Index size) {
  return std::make_shared<PyInst>(ByteCode::BUILD_LIST, size);
}

PyInstPtr CreateJumpAbsolute(Index index) {
  return std::make_shared<PyInst>(ByteCode::JUMP_ABSOLUTE, index);
}

PyInstPtr CreateBinarySubscr() {
  return std::make_shared<PyInst>(ByteCode::BINARY_SUBSCR);
}

PyInstPtr CreateStoreSubscr() {
  return std::make_shared<PyInst>(ByteCode::STORE_SUBSCR);
}

PyInstPtr CreateGetIter() {
  return std::make_shared<PyInst>(ByteCode::GET_ITER);
}

PyInstPtr CreateForIter(Index index) {
  return std::make_shared<PyInst>(
    ByteCode::FOR_ITER, static_cast<int64_t>(index)
  );
}

}  // namespace torchlight::Object