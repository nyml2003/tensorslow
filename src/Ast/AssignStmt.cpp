#include "Ast/AssignStmt.h"
#include <memory>
#include <utility>
#include "Ast/Binary.h"
#include "Ast/INode.h"
#include "Ast/Identifier.h"
#include "Ast/MemberAccess.h"
#include "Object/PyBoolean.h"
#include "Object/PyDictionary.h"
#include "Object/PyNone.h"
#include "Object/PyString.h"
#include "Object/PyType.h"

namespace torchlight::Ast {

AssignStmt::AssignStmt(
  Ast::INodePtr target,
  Ast::INodePtr source,
  Ast::INodePtr parent
)
  : INode(AssignStmtKlass::Self(), std::move(parent)),
    target(std::move(target)),
    source(std::move(source)) {}

Ast::INodePtr AssignStmt::Target() const {
  return target;
}

Ast::INodePtr AssignStmt::Source() const {
  return source;
}

Ast::INodePtr CreateAssignStmt(
  Ast::INodePtr target,
  Ast::INodePtr source,
  Ast::INodePtr parent
) {
  return std::make_shared<AssignStmt>(target, source, parent);
}

void AssignStmtKlass::Initialize() {
  SetName(Object::CreatePyString("AssignStmt"));
  SetType(CreatePyType(Self()));
  SetAttributes(Object::CreatePyDict());
  Klass::Initialize();
}

AssignStmtKlass::AssignStmtKlass() = default;

Object::PyObjPtr
AssignStmtKlass::emit(Object::PyObjPtr obj, Object::PyObjPtr codeList) {
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
    // 有误
    // target->emit(codeList);
    // auto code = GetCodeFromList(codeList, target);
    // code->StoreSubscr();
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

Object::PyObjPtr
AssignStmtKlass::visit(Object::PyObjPtr obj, Object::PyObjPtr codeList) {
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

Object::KlassPtr AssignStmtKlass::Self() {
  static Object::KlassPtr instance = std::make_shared<AssignStmtKlass>();
  return instance;
}

}  // namespace torchlight::Ast
