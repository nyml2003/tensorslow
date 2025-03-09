#include "Ast/Statement/ExprStmt.h"
#include "Object/PyNone.h"

namespace torchlight::Ast {

Object::PyObjPtr ExprStmtKlass::visit(
  const Object::PyObjPtr& obj,
  const Object::PyObjPtr& codeList
) {
  auto stmt = std::dynamic_pointer_cast<ExprStmt>(obj);
  auto content = stmt->Content();
  content->visit(codeList);
  return Object::CreatePyNone();
}

Object::PyObjPtr ExprStmtKlass::emit(
  const Object::PyObjPtr& obj,
  const Object::PyObjPtr& codeList
) {
  auto stmt = std::dynamic_pointer_cast<ExprStmt>(obj);
  auto content = stmt->Content();
  content->emit(codeList);
  auto code = GetCodeFromList(codeList, stmt);
  code->PopTop();
  return Object::CreatePyNone();
}

}  // namespace torchlight::Ast
