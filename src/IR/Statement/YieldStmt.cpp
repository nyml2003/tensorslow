#include "IR/Statement/YieldStmt.h"
#include "Object/Core/PyNone.h"

namespace torchlight::IR {

Object::PyObjPtr YieldStmtKlass::visit(
  const Object::PyObjPtr& obj,
  const Object::PyObjPtr& codeList
) {
  auto stmt = obj->as<YieldStmt>();
  auto content = stmt->Content();
  content->visit(codeList);
  return Object::CreatePyNone();
}

Object::PyObjPtr YieldStmtKlass::emit(
  const Object::PyObjPtr& obj,
  const Object::PyObjPtr& codeList
) {
  auto stmt = obj->as<YieldStmt>();
  auto content = stmt->Content();
  content->emit(codeList);
  auto code = GetCodeFromList(codeList, stmt);
  code->YieldValue();
  code->PopTop();
  return Object::CreatePyNone();
}

}  // namespace torchlight::IR
