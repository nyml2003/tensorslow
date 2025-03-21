#include "Ast/Expression/Binary.h"
#include "Object/Core/PyNone.h"
#include "Object/Runtime/PyInst.h"

namespace torchlight::Ast {

Object::PyObjPtr BinaryKlass::visit(
  const Object::PyObjPtr& obj,
  const Object::PyObjPtr& codeList
) {
  auto binary = obj->as<Binary>();
  auto left = binary->Left();
  auto right = binary->Right();
  left->visit(codeList);
  right->visit(codeList);
  return Object::CreatePyNone();
}
Object::PyObjPtr BinaryKlass::emit(
  const Object::PyObjPtr& obj,
  const Object::PyObjPtr& codeList
) {
  auto binary = obj->as<Binary>();
  auto left = binary->Left();
  auto right = binary->Right();
  left->emit(codeList);
  right->emit(codeList);
  Object::PyObjPtr inst = nullptr;
  switch (binary->Oprt()) {
    case Binary::Operator::ADD:
      inst = Object::CreateBinaryAdd();
      break;
    case Binary::Operator::SUB:
      inst = Object::CreateBinarySubtract();
      break;
    case Binary::Operator::MUL:
      inst = Object::CreateBinaryMultiply();
      break;
    case Binary::Operator::MATMUL:
      inst = Object::CreateBinaryMatrixMultiply();
      break;
    case Binary::Operator::EQ:
      inst = Object::CreateCompareOp(Object::CompareOp::EQUAL);
      break;
    case Binary::Operator::GE:
      inst = Object::CreateCompareOp(Object::CompareOp::GREATER_THAN_EQUAL);
      break;
    case Binary::Operator::LE:
      inst = Object::CreateCompareOp(Object::CompareOp::LESS_THAN_EQUAL);
      break;
    case Binary::Operator::NE:
      inst = Object::CreateCompareOp(Object::CompareOp::NOT_EQUAL);
      break;
    case Binary::Operator::LT:
      inst = Object::CreateCompareOp(Object::CompareOp::LESS_THAN);
      break;
    case Binary::Operator::GT:
      inst = Object::CreateCompareOp(Object::CompareOp::GREATER_THAN);
      break;
    case Binary::Operator::IS:
      inst = Object::CreateCompareOp(Object::CompareOp::IS);
      break;
    case Binary::Operator::IS_NOT:
      inst = Object::CreateCompareOp(Object::CompareOp::IS_NOT);
      break;
    case Binary::Operator::IN:
      inst = Object::CreateCompareOp(Object::CompareOp::IN);
      break;
    case Binary::Operator::NOT_IN:
      inst = Object::CreateCompareOp(Object::CompareOp::NOT_IN);
      break;
    case Binary::Operator::SUBSCR:
      inst = Object::CreateBinarySubscr();
      break;
    case Binary::Operator::STORE_SUBSCR:
      inst = Object::CreateStoreSubscr();
      break;
    case Binary::Operator::FLOOR_DIV:
      inst = Object::CreateBinaryFloorDivide();
      break;
    case Binary::Operator::DIV:
      inst = Object::CreateBinaryTrueDivide();
      break;
    case Binary::Operator::MOD:
      inst = Object::CreateBinaryModulo();
      break;
    case Binary::Operator::AND:
      inst = Object::CreateBinaryAnd();
      break;
    case Binary::Operator::OR:
      inst = Object::CreateBinaryOr();
      break;
    case Binary::Operator::XOR:
      inst = Object::CreateBinaryXor();
      break;
    case Binary::Operator::LSHIFT:
      inst = Object::CreateBinaryLShift();
      break;
    case Binary::Operator::RSHIFT:
      inst = Object::CreateBinaryRShift();
      break;
    case Binary::Operator::POWER:
      inst = Object::CreateBinaryPower();
      break;
  }
  if (inst == nullptr) {
    throw std::runtime_error("BinaryKlass::emit(): unsupported operator");
  }
  auto code = GetCodeFromList(codeList, binary);
  code->Instructions()->Append(inst);
  return Object::CreatePyNone();
}

}  // namespace torchlight::Ast
