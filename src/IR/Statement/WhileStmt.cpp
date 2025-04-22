#include "IR/Statement/WhileStmt.h"
#include "Object/Core/PyNone.h"
#include "Object/Iterator/IteratorHelper.h"
namespace torchlight::IR {

Object::PyObjPtr WhileStmtKlass::visit(
  const Object::PyObjPtr& obj,
  const Object::PyObjPtr& codeList
) {
  auto stmt = obj->as<WhileStmt>();
  auto condition = stmt->Condition();
  auto body = stmt->Body();
  condition->visit(codeList);
  Object::ForEach(body, [&codeList](const Object::PyObjPtr& stmt) {
    stmt->as<INode>()->visit(codeList);
  });
  return Object::CreatePyNone();
}

Object::PyObjPtr WhileStmtKlass::emit(
  const Object::PyObjPtr& obj,
  const Object::PyObjPtr& codeList
) {
  auto stmt = obj->as<WhileStmt>();
  auto condition = stmt->Condition();
  auto body = stmt->Body();
  auto code = GetCodeFromList(codeList, stmt);
  auto condBegin = code->Instructions()->Length();
  condition->emit(codeList);
  auto jumpStart = code->PopJumpIfFalse();
  Object::ForEach(body, [&codeList](const Object::PyObjPtr& stmt) {
    stmt->as<INode>()->emit(codeList);
  });
  code->JumpAbsolute(condBegin);
  auto jumpEnd = code->Instructions()->Length();
  auto offset = static_cast<int64_t>(jumpEnd - jumpStart + 1);
  code->Instructions()->SetItem(
    jumpStart - 1, Object::CreatePopJumpIfFalse(offset)
  );
  return Object::CreatePyNone();
}

}  // namespace torchlight::IR
