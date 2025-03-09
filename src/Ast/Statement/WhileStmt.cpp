#include "Ast/Statement/WhileStmt.h"
#include "Object/PyNone.h"

namespace torchlight::Ast {

Object::PyObjPtr WhileStmtKlass::visit(
  const Object::PyObjPtr& obj,
  const Object::PyObjPtr& codeList
) {
  auto stmt = std::dynamic_pointer_cast<WhileStmt>(obj);
  auto condition = stmt->Condition();
  auto body = stmt->Body();
  condition->visit(codeList);
  Object::ForEach(
    body,
    [&codeList](const Object::PyObjPtr& stmt, Index, const Object::PyObjPtr&) {
      auto stmtObj = std::dynamic_pointer_cast<Ast::INode>(stmt);
      stmtObj->visit(codeList);
    }
  );
  return Object::CreatePyNone();
}

Object::PyObjPtr WhileStmtKlass::emit(
  const Object::PyObjPtr& obj,
  const Object::PyObjPtr& codeList
) {
  auto stmt = std::dynamic_pointer_cast<WhileStmt>(obj);
  auto condition = stmt->Condition();
  auto body = stmt->Body();
  auto code = GetCodeFromList(codeList, stmt);
  auto condBegin = code->Instructions()->Length();
  condition->emit(codeList);
  auto jumpStart = code->PopJumpIfFalse();
  Object::ForEach(
    body,
    [&codeList](const Object::PyObjPtr& stmt, Index, const Object::PyObjPtr&) {
      auto stmtObj = std::dynamic_pointer_cast<Ast::INode>(stmt);
      stmtObj->emit(codeList);
    }
  );
  code->JumpAbsolute(condBegin);
  auto jumpEnd = code->Instructions()->Length();
  auto offset = static_cast<int64_t>(jumpEnd - jumpStart);
  code->Instructions()->SetItem(
    jumpStart - 1, Object::CreatePopJumpIfFalse(offset)
  );
  return Object::CreatePyNone();
}

}  // namespace torchlight::Ast
