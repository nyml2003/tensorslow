#include "object/PyInst.h"

#include "collections/common.h"
#include "collections/impl/Bytes.h"
#include "collections/impl/String.h"
#include "object/PyBytes.h"
#include "object/PyString.h"

namespace torchlight::object {

using collections::Serialize;
using collections::ToString;
PyInst::PyInst(ByteCode code, OperandKind operand)
  : PyObject(InstKlass::Self()), code(code), operand(operand) {}

[[nodiscard]] ByteCode PyInst::Code() const {
  return code;
}

[[nodiscard]] OperandKind PyInst::Operand() const {
  return operand;
}

InstKlass::InstKlass() : Klass(collections::CreateStringWithCString("inst")) {}

KlassPtr InstKlass::Self() {
  static KlassPtr instance = std::make_shared<InstKlass>();
  return instance;
}

PyObjPtr InstKlass::_serialize_(PyObjPtr obj) {
  if (obj->Klass() != Self()) {
    return nullptr;
  }
  auto inst = std::dynamic_pointer_cast<PyInst>(obj);
  Bytes bytes;
  bytes.InplaceConcat(Serialize(inst->Code()));
  std::visit(
    overload{
      [&bytes](NoneType) {},
      [&bytes](Index index) { bytes.InplaceConcat(Serialize(index)); },
      [&bytes](CompareOp op) { bytes.InplaceConcat(Serialize(op)); }
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
  String result = collections::CreateStringWithCString("<inst ");
  result.InplaceConcat(ToString(inst->Code()));
  result.InplaceConcat(collections::CreateStringWithCString(" "));
  std::visit(
    overload{
      [&result](NoneType) {},
      [&result](Index index) { result.InplaceConcat(ToString(index)); },
      [&result](CompareOp op) { result.InplaceConcat(ToString(op)); }
    },
    inst->Operand()
  );
  result.InplaceConcat(collections::CreateStringWithCString(">\n"));
  return std::make_shared<PyString>(result);
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

}  // namespace torchlight::object