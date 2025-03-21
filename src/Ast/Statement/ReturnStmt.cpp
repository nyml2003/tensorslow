#include "Ast/Statement/ReturnStmt.h"
#include "Object/PyNone.h"

namespace torchlight::Ast {

Object::PyObjPtr ReturnStmtKlass::visit(
  const Object::PyObjPtr& obj,
  const Object::PyObjPtr& codeList
) {
  auto stmt = obj->as<ReturnStmt>();
  auto content = stmt->Content();
  content->visit(codeList);
  return Object::CreatePyNone();
}

Object::PyObjPtr ReturnStmtKlass::emit(
  const Object::PyObjPtr& obj,
  const Object::PyObjPtr& codeList
) {
  auto stmt = obj->as<ReturnStmt>();
  auto content = stmt->Content();
  content->emit(codeList);
  auto code = GetCodeFromList(codeList, stmt);
  code->ReturnValue();
  return Object::CreatePyNone();
}

}  // namespace torchlight::Ast
