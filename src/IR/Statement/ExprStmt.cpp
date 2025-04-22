#include "IR/Statement/ExprStmt.h"
#include "Object/Core/PyNone.h"

namespace torchlight::IR {

Object::PyObjPtr ExprStmtKlass::visit(
  const Object::PyObjPtr& obj,
  const Object::PyObjPtr& codeList
) {
  auto stmt = obj->as<ExprStmt>();
  auto content = stmt->Content();
  content->visit(codeList);
  return Object::CreatePyNone();
}

Object::PyObjPtr ExprStmtKlass::emit(
  const Object::PyObjPtr& obj,
  const Object::PyObjPtr& codeList
) {
  auto stmt = obj->as<ExprStmt>();
  auto content = stmt->Content();
  content->emit(codeList);
  auto code = GetCodeFromList(codeList, stmt);
  code->PopTop();
  return Object::CreatePyNone();
}

}  // namespace torchlight::IR
