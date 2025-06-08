#include "IR/Statement/YieldStmt.h"
#include "Object/Core/PyNone.h"

namespace tensorslow::IR {

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

Object::PyObjPtr YieldStmtKlass::print(const Object::PyObjPtr& obj) {
  auto stmt = obj->as<YieldStmt>();
  auto content = stmt->Content();
  PrintNode(stmt, Object::CreatePyString("YieldStmt"));
  content->print();
  PrintEdge(stmt, content);
  return Object::CreatePyNone();
}

}  // namespace tensorslow::IR
