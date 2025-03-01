#include "Ast/AssignStmt.h"
#include "Ast/Binary.h"
#include "Ast/INode.h"
#include "Ast/Identifier.h"
#include "Ast/MemberAccess.h"
#include "Object/PyBoolean.h"
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
    auto name = targetIdentifier->Name();
    auto code = GetCodeFromList(codeList, assignStmt);
    if (Object::IsTrue(code->VarNames()->contains(name))) {
      code->StoreFast(name);
    }
    if (Object::IsTrue(code->Names()->contains(name))) {
      code->StoreName(name);
    }
  } else if (target->Klass() == MemberAccessKlass::Self()) {
    auto memberAccess = std::dynamic_pointer_cast<MemberAccess>(target);
    auto object = memberAccess->Obj();
    object->emit(codeList);
    auto member = memberAccess->Member();
    auto code = GetCodeFromList(codeList, memberAccess);
    code->StoreAttr(member);
  } else if (target->Klass() == BinaryKlass::Self()) {
    auto binary = std::dynamic_pointer_cast<Binary>(target);
    auto oprt = binary->Oprt();
    if (oprt != Binary::Operator::SUBSCR) {
      throw std::runtime_error("Unknown target type");
    }
    auto left = binary->Left();
    left->emit(codeList);
    auto right = binary->Right();
    right->emit(codeList);
    auto code = GetCodeFromList(codeList, target);
    code->StoreSubscr();
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
    auto code = GetCodeFromList(codeList, targetIdentifier);
    if (code->Scope() == Object::Scope::GLOBAL) {
      code->RegisterName(targetIdentifier->Name());
    }
    if (code->Scope() == Object::Scope::LOCAL) {
      auto module = targetIdentifier->Parent()->Parent();
      auto moduleCode = GetCodeFromList(codeList, module);
      if (!Object::IsTrue(moduleCode->Names()->contains(targetIdentifier->Name()
          ))) {
        // Global没有这个变量，那一定是在local中定义的局部变量
        code->RegisterVarName(targetIdentifier->Name());
      }
    }
  } else if (target->Klass() == MemberAccessKlass::Self()) {
    auto memberAccess = std::dynamic_pointer_cast<MemberAccess>(target);
    memberAccess->visit(codeList);
  } else if (target->Klass() == BinaryKlass::Self()) {
    auto binary = std::dynamic_pointer_cast<Binary>(target);
    auto oprt = binary->Oprt();
    if (oprt != Binary::Operator::SUBSCR) {
      throw std::runtime_error("Unknown target type");
    }
    auto left = binary->Left();
    left->visit(codeList);
    auto right = binary->Right();
    right->visit(codeList);
    return Object::CreatePyNone();
  }
  return Object::CreatePyNone();
}

}  // namespace torchlight::Ast
