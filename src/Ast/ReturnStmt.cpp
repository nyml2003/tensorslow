#include "Ast/ReturnStmt.h"
#include "Ast/INode.h"
#include "Object/PyDictionary.h"
#include "Object/PyNone.h"
#include "Object/PyString.h"
#include "Object/PyType.h"

namespace torchlight::Ast {

ReturnStmt::ReturnStmt(Ast::INodePtr content, Ast::INodePtr parent)
  : INode(ReturnStmtKlass::Self(), std::move(parent)),
    content(std::move(content)) {}

Ast::INodePtr ReturnStmt::Content() const {
  return content;
}

Ast::INodePtr CreateReturnStmt(Ast::INodePtr content, Ast::INodePtr parent) {
  return std::make_shared<ReturnStmt>(std::move(content), parent);
}

void ReturnStmtKlass::Initialize() {
  SetName(Object::CreatePyString("ReturnStmt"));
  SetType(CreatePyType(Self()));
  SetAttributes(Object::CreatePyDict());
  Klass::Initialize();
}

ReturnStmtKlass::ReturnStmtKlass() = default;

Object::PyObjPtr
ReturnStmtKlass::visit(Object::PyObjPtr obj, Object::PyObjPtr codeList) {
  auto stmt = std::dynamic_pointer_cast<ReturnStmt>(obj);
  auto content = stmt->Content();
  content->visit(codeList);
  return Object::CreatePyNone();
}

Object::PyObjPtr
ReturnStmtKlass::emit(Object::PyObjPtr obj, Object::PyObjPtr codeList) {
  auto stmt = std::dynamic_pointer_cast<ReturnStmt>(obj);
  auto content = stmt->Content();
  content->emit(codeList);
  auto code = GetCodeFromList(codeList, stmt);
  code->ReturnValue();
  return Object::CreatePyNone();
}

Object::KlassPtr ReturnStmtKlass::Self() {
  static Object::KlassPtr instance = std::make_shared<ReturnStmtKlass>();
  return instance;
}

}  // namespace torchlight::Ast
