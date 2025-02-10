#include "Ast/WhileStmt.h"
#include "Ast/INode.h"
#include "ByteCode/PyInst.h"
#include "Collections/Iterator.h"
#include "Object/PyDictionary.h"
#include "Object/PyInteger.h"
#include "Object/PyNone.h"
#include "Object/PyString.h"
#include "Object/PyType.h"

namespace torchlight::Ast {

WhileStmt::WhileStmt(
  Ast::INodePtr condition,
  Object::PyListPtr body,
  Ast::INodePtr parent
)
  : INode(WhileStmtKlass::Self(), std::move(parent)),
    condition(std::move(condition)),
    body(std::move(body)) {}

Ast::INodePtr WhileStmt::Condition() const {
  return condition;
}

Object::PyListPtr WhileStmt::Body() const {
  return body;
}

Ast::INodePtr CreateWhileStmt(
  Ast::INodePtr condition,
  Object::PyObjPtr body,
  Ast::INodePtr parent
) {
  return std::make_shared<WhileStmt>(
    std::move(condition), std::dynamic_pointer_cast<Object::PyList>(body),
    parent
  );
}

void WhileStmtKlass::Initialize() {
  SetName(Object::CreatePyString("WhileStmt"));
  SetType(CreatePyType(Self()));
  SetAttributes(Object::CreatePyDict());
  Klass::Initialize();
}

WhileStmtKlass::WhileStmtKlass() = default;

Object::PyObjPtr
WhileStmtKlass::visit(Object::PyObjPtr obj, Object::PyObjPtr codeList) {
  auto stmt = std::dynamic_pointer_cast<WhileStmt>(obj);
  auto condition = stmt->Condition();
  auto body = stmt->Body();
  condition->visit(codeList);
  auto bodyList = std::dynamic_pointer_cast<Object::PyList>(body)->Value();
  for (auto stmt = Collections::Iterator<Object::PyObjPtr>::Begin(bodyList);
       !stmt.End(); stmt.Next()) {
    auto stmtObj = std::dynamic_pointer_cast<Ast::INode>(stmt.Get());
    stmtObj->visit(codeList);
  }
  return Object::CreatePyNone();
}

Object::PyObjPtr
WhileStmtKlass::emit(Object::PyObjPtr obj, Object::PyObjPtr codeList) {
  auto stmt = std::dynamic_pointer_cast<WhileStmt>(obj);
  auto condition = stmt->Condition();
  auto body = stmt->Body();

  auto bodyList = std::dynamic_pointer_cast<Object::PyList>(body)->Value();
  auto code = GetCodeFromList(codeList, stmt);
  auto condBegin = Object::ToU64(code->Instructions()->len());
  condition->emit(codeList);
  auto jumpStart = code->PopJumpIfFalse();
  for (auto stmt = Collections::Iterator<Object::PyObjPtr>::Begin(bodyList);
       !stmt.End(); stmt.Next()) {
    auto stmtObj = std::dynamic_pointer_cast<Ast::INode>(stmt.Get());
    stmtObj->emit(codeList);
  }
  code->JumpAbsolute(condBegin);
  auto jumpEnd = Object::ToU64(code->Instructions()->len());
  auto offset = static_cast<int64_t>(jumpEnd - jumpStart);
  code->Instructions()->Value().Set(
    jumpStart - 1, Object::CreatePopJumpIfFalse(offset)
  );
  return Object::CreatePyNone();
}

Object::KlassPtr WhileStmtKlass::Self() {
  static Object::KlassPtr instance = std::make_shared<WhileStmtKlass>();
  return instance;
}

}  // namespace torchlight::Ast
