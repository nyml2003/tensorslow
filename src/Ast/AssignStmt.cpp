#include "Ast/AssignStmt.h"
#include "Ast/Expression/Binary.h"
#include "Ast/Identifier.h"
#include "Ast/MemberAccess.h"
#include "Object/PyNone.h"
#include "Object/PyObject.h"

namespace torchlight::Ast {

Object::PyObjPtr AssignStmtKlass::emit(
  const Object::PyObjPtr& obj,
  const Object::PyObjPtr& codeList
) {
  auto assignStmt = std::dynamic_pointer_cast<AssignStmt>(obj);
  auto source = assignStmt->Source();
  source->emit(codeList);
  auto target = assignStmt->Target();

  if (target->Klass() == IdentifierKlass::Self()) {
    auto targetIdentifier = std::dynamic_pointer_cast<Identifier>(target);
    targetIdentifier->emit(codeList);
  } else if (target->Klass() == MemberAccessKlass::Self()) {
    auto memberAccess = std::dynamic_pointer_cast<MemberAccess>(target);
    memberAccess->emit(codeList);
  } else if (target->Klass() == BinaryKlass::Self()) {
    auto binary = std::dynamic_pointer_cast<Binary>(target);
    binary->emit(codeList);
    return Object::CreatePyNone();
  }
  return Object::CreatePyNone();
}

Object::PyObjPtr AssignStmtKlass::visit(
  const Object::PyObjPtr& obj,
  const Object::PyObjPtr& codeList
) {
  auto assignStmt = std::dynamic_pointer_cast<AssignStmt>(obj);
  auto source = assignStmt->Source();
  source->visit(codeList);
  auto target = assignStmt->Target();
  if (target->Klass() == IdentifierKlass::Self()) {
    auto targetIdentifier = std::dynamic_pointer_cast<Identifier>(target);
    targetIdentifier->SetStoreMode();
    targetIdentifier->visit(codeList);
  } else if (target->Klass() == MemberAccessKlass::Self()) {
    auto memberAccess = std::dynamic_pointer_cast<MemberAccess>(target);
    memberAccess->SetStoreMode();
    memberAccess->visit(codeList);
  } else if (target->Klass() == BinaryKlass::Self()) {
    auto binary = std::dynamic_pointer_cast<Binary>(target);
    auto oprt = binary->Oprt();
    if (oprt != Binary::Operator::SUBSCR) {
      throw std::runtime_error("When assigning, only support subscript operation");
    }
    binary->SetOprt(Binary::Operator::STORE_SUBSCR);
    binary->visit(codeList);
    return Object::CreatePyNone();
  }
  return Object::CreatePyNone();
}

}  // namespace torchlight::Ast
