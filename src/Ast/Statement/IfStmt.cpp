#include "Ast/Statement/IfStmt.h"
#include "Ast/INode.h"
#include "ByteCode/PyInst.h"
#include "Object/ObjectHelper.h"
#include "Object/PyNone.h"

namespace torchlight::Ast {

Object::PyObjPtr IfStmtKlass::visit(
  const Object::PyObjPtr& obj,
  const Object::PyObjPtr& codeList
) {
  auto stmt = std::dynamic_pointer_cast<IfStmt>(obj);
  auto condition = stmt->Condition();
  auto thenStmts = stmt->ThenStmts();
  condition->visit(codeList);
  Object::ForEach(
    thenStmts,
    [&codeList](const Object::PyObjPtr& stmt, Index, const Object::PyObjPtr&) {
      auto stmtObj = std::dynamic_pointer_cast<Ast::INode>(stmt);
      stmtObj->visit(codeList);
    }
  );

  return Object::CreatePyNone();
}

Object::PyObjPtr IfStmtKlass::emit(
  const Object::PyObjPtr& obj,
  const Object::PyObjPtr& codeList
) {
  auto stmt = std::dynamic_pointer_cast<IfStmt>(obj);
  auto condition = stmt->Condition();
  auto thenStmts = stmt->ThenStmts();
  condition->emit(codeList);
  auto code = GetCodeFromList(codeList, stmt);
  auto jumpStart = code->PopJumpIfFalse();
  Object::ForEach(
    thenStmts,
    [&codeList](const Object::PyObjPtr& stmt, Index, const Object::PyObjPtr&) {
      auto stmtObj = std::dynamic_pointer_cast<Ast::INode>(stmt);
      stmtObj->emit(codeList);
    }
  );
  auto jumpEnd = code->Instructions()->Length();
  auto offset = static_cast<int64_t>(jumpEnd - jumpStart);
  code->Instructions()->SetItem(
    jumpStart - 1, Object::CreatePopJumpIfFalse(offset)
  );
  return Object::CreatePyNone();
}

}  // namespace torchlight::Ast
