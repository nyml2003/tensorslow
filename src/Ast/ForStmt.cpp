#include "Ast/ForStmt.h"
#include <memory>
#include <utility>
#include "Ast/Binary.h"
#include "Ast/INode.h"
#include "Ast/Identifier.h"
#include "Ast/MemberAccess.h"
#include "ByteCode/PyInst.h"
#include "Object/ObjectHelper.h"
#include "Object/PyBoolean.h"
#include "Object/PyDictionary.h"
#include "Object/PyNone.h"
#include "Object/PyString.h"
#include "Object/PyType.h"

namespace torchlight::Ast {

ForStmt::ForStmt(
  Ast::INodePtr target,
  Ast::INodePtr iter,
  Object::PyObjPtr body,
  Ast::INodePtr parent
)
  : INode(ForStmtKlass::Self(), std::move(parent)),
    target(std::move(target)),
    iter(std::move(iter)),
    body(std::dynamic_pointer_cast<Object::PyList>(body)) {}

Ast::INodePtr ForStmt::Target() const {
  return target;
}

Ast::INodePtr ForStmt::Iter() const {
  return iter;
}

Object::PyListPtr ForStmt::Body() const {
  return body;
}

Ast::INodePtr CreateForStmt(
  Ast::INodePtr target,
  Ast::INodePtr iter,
  Object::PyObjPtr body,
  Ast::INodePtr parent
) {
  return std::make_shared<ForStmt>(
    std::move(target), std::move(iter), std::move(body), std::move(parent)
  );
}

void ForStmtKlass::Initialize() {
  SetName(Object::CreatePyString("ForStmt"));
  SetType(CreatePyType(Self()));
  SetAttributes(Object::CreatePyDict());
  Klass::Initialize();
}

ForStmtKlass::ForStmtKlass() = default;

Object::PyObjPtr
ForStmtKlass::emit(Object::PyObjPtr obj, Object::PyObjPtr codeList) {
  auto stmt = std::dynamic_pointer_cast<ForStmt>(obj);
  auto iter = stmt->Iter();
  iter->emit(codeList);
  auto code = GetCodeFromList(codeList, stmt);
  code->GetIter();
  Index start = code->ForIter(0);
  auto target = stmt->Target();
  if (Object::IsType(target, IdentifierKlass::Self())) {
    auto identifier = std::dynamic_pointer_cast<Identifier>(target);
    code->StoreName(identifier->Name());
  } else {
    throw std::runtime_error("ForStmt::emit(): unsupported target type");
  }
  auto body = stmt->Body();
  Object::ForEach(
    body,
    [codeList](const Object::PyObjPtr& stmt, Index, const Object::PyObjPtr&) {
      auto stmtNode = std::dynamic_pointer_cast<Ast::INode>(stmt);
      stmtNode->emit(codeList);
    }
  );
  code->JumpAbsolute(start - 1);
  Index end = code->Instructions()->Length();
  code->Instructions()->SetItem(
    start - 1, Object::CreateForIter(end - start + 1)
  );
  return Object::CreatePyNone();
}

Object::PyObjPtr
ForStmtKlass::visit(Object::PyObjPtr obj, Object::PyObjPtr codeList) {
  auto stmt = std::dynamic_pointer_cast<ForStmt>(obj);
  auto target = stmt->Target();
  auto iter = stmt->Iter();
  auto body = stmt->Body();
  iter->visit(codeList);
  if (Object::IsType(target, IdentifierKlass::Self())) {
    auto identifier = std::dynamic_pointer_cast<Identifier>(target);
    auto code = GetCodeFromList(codeList, stmt);
    code->RegisterName(identifier->Name());
  } else {
    DebugPrint(target);
    throw std::runtime_error("ForStmt::visit(): unsupported target type");
  }
  Object::ForEach(
    body,
    [codeList](const Object::PyObjPtr& stmt, Index, const Object::PyObjPtr&) {
      auto stmtNode = std::dynamic_pointer_cast<Ast::INode>(stmt);
      stmtNode->visit(codeList);
    }
  );
  return Object::CreatePyNone();
}

Object::KlassPtr ForStmtKlass::Self() {
  static Object::KlassPtr instance = std::make_shared<ForStmtKlass>();
  return instance;
}

}  // namespace torchlight::Ast
