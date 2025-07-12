#include "Object/Runtime/PyInst.h"
#include "Collections/String/BytesHelper.h"
#include "Collections/String/StringHelper.h"
#include "Object/String/PyBytes.h"
#include "Object/String/PyString.h"

namespace tensorslow::Object {

PyInst::PyInst(ByteCode code, OperandKind operand)
  : PyObject(InstKlass::Self()), code(code), operand(operand) {}

[[nodiscard]] ByteCode PyInst::Code() const {
  return code;
}

[[nodiscard]] OperandKind PyInst::Operand() const {
  return operand;
}

PyObjPtr InstKlass::_serialize_(const PyObjPtr& obj) {
  if (!obj->is(Self())) {
    throw std::runtime_error(
      "PyInst::_serialize_(): obj is not an inst object"
    );
  }
  auto inst = obj->as<PyInst>();
  Collections::StringBuilder sb(Collections::Serialize(inst->Code()));
  std::visit(
    overload{
      [](None) {},
      [&sb](Index index) { sb.Append(Collections::Serialize(index)); },
      [&sb](CompareOp compOp) { sb.Append(Collections::Serialize(compOp)); },
      [&sb](int64_t index) { sb.Append(Collections::Serialize(index)); }
    },
    inst->Operand()
  );
  return CreatePyBytes(sb.ToString());
}

PyObjPtr InstKlass::repr(const PyObjPtr& obj) {
  if (!obj->is(Self())) {
    throw std::runtime_error("PyInst::repr(): obj is not an inst object");
  }
  auto inst = obj->as<PyInst>();
  Collections::StringBuilder sb(Collections::ToString(inst->Code()));
  sb.Append(Collections::CreateStringWithCString(" "));
  std::visit(
    overload{
      [](None) {},
      [&sb](Index index) { sb.Append(Collections::ToString(index)); },
      [&sb](CompareOp compOp) { sb.Append(Collections::ToString(compOp)); },
      [&sb](int64_t index) { sb.Append(Collections::ToString(index)); }
    },
    inst->Operand()
  );
  return CreatePyString(sb.ToString(), false);
}

}  // namespace tensorslow::Object