#include "Ast/Statement/YieldStmt.h"
#include "Object/PyNone.h"

namespace torchlight::Ast {

Object::PyObjPtr YieldStmtKlass::visit(
  const Object::PyObjPtr& obj,
  const Object::PyObjPtr& codeList
) {
  auto stmt = std::dynamic_pointer_cast<YieldStmt>(obj);
  auto content = stmt->Content();
  content->visit(codeList);
  return Object::CreatePyNone();
}

Object::PyObjPtr YieldStmtKlass::emit(
  const Object::PyObjPtr& obj,
  const Object::PyObjPtr& codeList
) {
  auto stmt = std::dynamic_pointer_cast<YieldStmt>(obj);
  auto content = stmt->Content();
  content->emit(codeList);
  auto code = GetCodeFromList(codeList, stmt);
  code->YieldValue();
  code->PopTop();
  return Object::CreatePyNone();
}

}  // namespace torchlight::Ast
