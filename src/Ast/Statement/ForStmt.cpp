#include "Ast/Statement/ForStmt.h"
#include "Ast/INode.h"
#include "Ast/Identifier.h"
#include "ByteCode/PyInst.h"
#include "Object/ObjectHelper.h"
#include "Object/PyNone.h"

namespace torchlight::Ast {

Object::PyObjPtr ForStmtKlass::emit(
  const Object::PyObjPtr& obj,
  const Object::PyObjPtr& codeList
) {
  auto stmt = obj->as<ForStmt>();
  auto iter = stmt->Iter();
  iter->emit(codeList);
  auto code = GetCodeFromList(codeList, stmt);
  code->GetIter();
  Index start = code->ForIter(0);
  auto target = stmt->Target();
  if (target->is<Identifier>()) {
    auto identifier = target->as<Identifier>();
    auto name = identifier->Name();
    if (code->Scope() == Object::Scope::GLOBAL) {
      code->StoreName(name);
    }
    if (code->Scope() == Object::Scope::LOCAL) {
      code->StoreFast(name);
    }
  } else {
    throw std::runtime_error("ForStmt::emit(): unsupported target type");
  }
  auto body = stmt->Body();
  Object::ForEach(
    body,
    [codeList](const Object::PyObjPtr& stmt, Index, const Object::PyObjPtr&) {
      stmt->as<INode>()->emit(codeList);
    }
  );
  code->JumpAbsolute(start - 1);
  Index end = code->Instructions()->Length();
  code->Instructions()->SetItem(
    start - 1, Object::CreateForIter(end - start + 1)
  );
  return Object::CreatePyNone();
}

Object::PyObjPtr ForStmtKlass::visit(
  const Object::PyObjPtr& obj,
  const Object::PyObjPtr& codeList
) {
  auto stmt = obj->as<ForStmt>();
  auto target = stmt->Target();
  auto iter = stmt->Iter();
  auto body = stmt->Body();
  iter->visit(codeList);
  if (target->is<Identifier>()) {
    auto identifier = target->as<Identifier>();
    auto code = GetCodeFromList(codeList, stmt);
    auto name = identifier->Name();
    if (code->Scope() == Object::Scope::GLOBAL) {
      code->RegisterName(name);
    }
    if (code->Scope() == Object::Scope::LOCAL) {
      code->RegisterVarName(name);
    }
  } else {
    DebugPrint(target);
    throw std::runtime_error("ForStmt::visit(): unsupported target type");
  }
  Object::ForEach(
    body,
    [codeList](const Object::PyObjPtr& stmt, Index, const Object::PyObjPtr&) {
      stmt->as<INode>()->visit(codeList);
    }
  );
  return Object::CreatePyNone();
}

}  // namespace torchlight::Ast
