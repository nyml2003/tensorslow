#include "Ast/AssignStmt.h"
#include "Ast/Expression/Binary.h"
#include "Ast/Identifier.h"
#include "Ast/MemberAccess.h"
#include "Object/Core/PyNone.h"
#include "Object/Core/PyObject.h"

namespace torchlight::Ast {

Object::PyObjPtr AssignStmtKlass::emit(
  const Object::PyObjPtr& obj,
  const Object::PyObjPtr& codeList
) {
  auto assignStmt = obj->as<AssignStmt>();
  auto source = assignStmt->Source();
  source->emit(codeList);
  auto target = assignStmt->Target();
  if (target->is(IdentifierKlass::Self())) {
    auto targetIdentifier = target->as<Identifier>();
    targetIdentifier->emit(codeList);
  } else if (target->is(MemberAccessKlass::Self())) {
    auto memberAccess = target->as<MemberAccess>();
    memberAccess->emit(codeList);
  } else if (target->is(BinaryKlass::Self())) {
    auto binary = target->as<Binary>();
    binary->emit(codeList);
    return Object::CreatePyNone();
  }
  return Object::CreatePyNone();
}

Object::PyObjPtr AssignStmtKlass::visit(
  const Object::PyObjPtr& obj,
  const Object::PyObjPtr& codeList
) {
  auto assignStmt = obj->as<AssignStmt>();
  auto source = assignStmt->Source();
  source->visit(codeList);
  auto target = assignStmt->Target();
  if (target->is(IdentifierKlass::Self())) {
    auto targetIdentifier = target->as<Identifier>();
    targetIdentifier->SetStoreMode();
    targetIdentifier->visit(codeList);
  } else if (target->is(MemberAccessKlass::Self())) {
    auto memberAccess = target->as<MemberAccess>();
    memberAccess->SetStoreMode();
    memberAccess->visit(codeList);
  } else if (target->is(BinaryKlass::Self())) {
    auto binary = target->as<Binary>();
    auto oprt = binary->Oprt();
    if (oprt != Binary::Operator::SUBSCR) {
      throw std::runtime_error(
        "When assigning, only support subscript operation"
      );
    }
    binary->SetOprt(Binary::Operator::STORE_SUBSCR);
    binary->visit(codeList);
    return Object::CreatePyNone();
  }
  return Object::CreatePyNone();
}

}  // namespace torchlight::Ast
