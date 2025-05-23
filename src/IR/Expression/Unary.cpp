#include "IR/Expression/Unary.h"
#include "Object/Core/PyNone.h"
#include "Object/Runtime/PyInst.h"

namespace tensorslow::IR {

Object::PyObjPtr UnaryKlass::visit(
  const Object::PyObjPtr& obj,
  const Object::PyObjPtr& codeList
) {
  auto unary = obj->as<Unary>();
  auto operand = unary->Operand();
  operand->visit(codeList);
  return Object::CreatePyNone();
}
Object::PyObjPtr UnaryKlass::emit(
  const Object::PyObjPtr& obj,
  const Object::PyObjPtr& codeList
) {
  auto unary = obj->as<Unary>();
  auto operand = unary->Operand();
  operand->emit(codeList);
  Object::PyObjPtr inst = nullptr;
  switch (unary->Oprt()) {
    case Unary::Operator::PLUS:
      inst = Object::CreateUnaryPositive();
      break;
    case Unary::Operator::MINUS:
      inst = Object::CreateUnaryNegative();
      break;
    case Unary::Operator::INVERT:
      inst = Object::CreateUnaryInvert();
      break;
    case Unary::Operator::NOT:
      inst = Object::CreateUnaryNot();
      break;
  }
  if (inst == nullptr) {
    throw std::runtime_error("UnaryKlass::emit(): unsupported operator");
  }
  auto code = GetCodeFromList(codeList, unary);
  code->Instructions()->Append(inst);
  return Object::CreatePyNone();
}

Object::PyObjPtr UnaryKlass::print(const Object::PyObjPtr& obj) {
  auto unary = obj->as<Unary>();
  auto operand = unary->Operand();
  auto text = Object::CreatePyString("Unary");
  auto oprt = Object::CreatePyString(
    unary->Oprt() == Unary::Operator::PLUS
      ? "+"
      : (unary->Oprt() == Unary::Operator::MINUS
           ? "-"
           : (unary->Oprt() == Unary::Operator::INVERT ? "~" : "!"))
  );
  operand->print();
  auto textList =
    StringConcat(Object::CreatePyList({text, oprt}))->as<Object::PyString>();
  PrintNode(unary, textList);
  PrintEdge(unary, operand, textList);
  return Object::CreatePyNone();
}
}  // namespace tensorslow::IR
