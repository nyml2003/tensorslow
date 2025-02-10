#include "Ast/IfStmt.h"
#include "Ast/INode.h"
#include "ByteCode/PyInst.h"
#include "Collections/Iterator.h"
#include "Object/PyDictionary.h"
#include "Object/PyInteger.h"
#include "Object/PyNone.h"
#include "Object/PyString.h"
#include "Object/PyType.h"

namespace torchlight::Ast {

IfStmt::IfStmt(
  Ast::INodePtr condition,
  Object::PyListPtr thenStmts,
  Ast::INodePtr parent
)
  : INode(IfStmtKlass::Self(), std::move(parent)),
    condition(std::move(condition)),
    thenStmts(std::move(thenStmts)) {}

Ast::INodePtr IfStmt::Condition() const {
  return condition;
}

Object::PyListPtr IfStmt::ThenStmts() const {
  return thenStmts;
}

Ast::INodePtr CreateIfStmt(
  Ast::INodePtr condition,
  Object::PyObjPtr thenStmts,
  Ast::INodePtr parent
) {
  return std::make_shared<IfStmt>(
    std::move(condition), std::dynamic_pointer_cast<Object::PyList>(thenStmts),
    parent
  );
}

void IfStmtKlass::Initialize() {
  SetName(Object::CreatePyString("IfStmt"));
  SetType(CreatePyType(Self()));
  SetAttributes(Object::CreatePyDict());
  Klass::Initialize();
}

IfStmtKlass::IfStmtKlass() = default;

Object::PyObjPtr
IfStmtKlass::visit(Object::PyObjPtr obj, Object::PyObjPtr codeList) {
  auto stmt = std::dynamic_pointer_cast<IfStmt>(obj);
  auto condition = stmt->Condition();
  auto thenStmts = stmt->ThenStmts();
  condition->visit(codeList);
  auto thenStmtsList =
    std::dynamic_pointer_cast<Object::PyList>(thenStmts)->Value();
  for (auto stmt =
         Collections::Iterator<Object::PyObjPtr>::Begin(thenStmtsList);
       !stmt.End(); stmt.Next()) {
    auto stmtObj = std::dynamic_pointer_cast<Ast::INode>(stmt.Get());
    stmtObj->visit(codeList);
  }
  return Object::CreatePyNone();
}

Object::PyObjPtr
IfStmtKlass::emit(Object::PyObjPtr obj, Object::PyObjPtr codeList) {
  auto stmt = std::dynamic_pointer_cast<IfStmt>(obj);
  auto condition = stmt->Condition();
  auto thenStmts = stmt->ThenStmts();
  condition->emit(codeList);
  auto thenStmtsList =
    std::dynamic_pointer_cast<Object::PyList>(thenStmts)->Value();
  auto code = GetCodeFromList(codeList, stmt);
  auto jumpStart = code->PopJumpIfFalse();
  for (auto stmt =
         Collections::Iterator<Object::PyObjPtr>::Begin(thenStmtsList);
       !stmt.End(); stmt.Next()) {
    auto stmtObj = std::dynamic_pointer_cast<Ast::INode>(stmt.Get());
    stmtObj->emit(codeList);
  }
  auto jumpEnd = Object::ToU64(code->Instructions()->len());
  auto offset = static_cast<int64_t>(jumpEnd - jumpStart);
  code->Instructions()->Value().Set(
    jumpStart - 1, Object::CreatePopJumpIfFalse(offset)
  );
  return Object::CreatePyNone();
}

Object::KlassPtr IfStmtKlass::Self() {
  static Object::KlassPtr instance = std::make_shared<IfStmtKlass>();
  return instance;
}

}  // namespace torchlight::Ast
