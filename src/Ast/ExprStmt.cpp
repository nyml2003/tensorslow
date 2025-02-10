#include "Ast/ExprStmt.h"
#include "Object/PyDictionary.h"
#include "Object/PyNone.h"
#include "Object/PyString.h"
#include "Object/PyType.h"

namespace torchlight::Ast {

ExprStmt::ExprStmt(Ast::INodePtr content, Ast::INodePtr parent)
  : INode(ExprStmtKlass::Self(), std::move(parent)),
    content(std::move(content)) {}

Ast::INodePtr ExprStmt::Content() const {
  return content;
}

Ast::INodePtr CreateExprStmt(Ast::INodePtr content, Ast::INodePtr parent) {
  return std::make_shared<ExprStmt>(std::move(content), parent);
}

void ExprStmtKlass::Initialize() {
  SetName(Object::CreatePyString("ExprStmt"));
  SetType(CreatePyType(Self()));
  SetAttributes(Object::CreatePyDict());
  Klass::Initialize();
}

ExprStmtKlass::ExprStmtKlass() = default;

Object::PyObjPtr
ExprStmtKlass::visit(Object::PyObjPtr obj, Object::PyObjPtr codeList) {
  auto stmt = std::dynamic_pointer_cast<ExprStmt>(obj);
  auto content = stmt->Content();
  content->visit(codeList);
  return Object::CreatePyNone();
}

Object::PyObjPtr
ExprStmtKlass::emit(Object::PyObjPtr obj, Object::PyObjPtr codeList) {
  auto stmt = std::dynamic_pointer_cast<ExprStmt>(obj);
  auto content = stmt->Content();
  content->emit(codeList);
  auto code = GetCodeFromList(codeList, stmt);
  code->PopTop();
  return Object::CreatePyNone();
}

Object::KlassPtr ExprStmtKlass::Self() {
  static Object::KlassPtr instance = std::make_shared<ExprStmtKlass>();
  return instance;
}

}  // namespace torchlight::Ast
