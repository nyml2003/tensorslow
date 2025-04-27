#include "IR/Statement/ForStmt.h"
#include "Function/BuiltinFunction.h"
#include "IR/INode.h"
#include "IR/Identifier.h"
#include "Object/Core/PyNone.h"
#include "Object/Iterator/IteratorHelper.h"
#include "Object/Runtime/PyInst.h"
namespace torchlight::IR {

Object::PyObjPtr ForStmtKlass::emit(
  const Object::PyObjPtr& obj,
  const Object::PyObjPtr& codeList
) {
  auto stmt = obj->as<ForStmt>();
  auto iter = stmt->Iter();
  iter->emit(codeList);
  auto code = GetCodeFromList(codeList, stmt);
  code->GetIter();
  Index start = code->ForIter(0);
  auto target = stmt->Target();
  if (target->is(IdentifierKlass::Self())) {
    auto identifier = target->as<Identifier>();
    auto name = identifier->Name();
    if (code->GetScope() == Object::Scope::GLOBAL) {
      code->StoreName(name);
    }
    if (code->GetScope() == Object::Scope::LOCAL) {
      code->StoreFast(name);
    }
  } else {
    throw std::runtime_error("ForStmt::emit(): unsupported target type");
  }
  auto body = stmt->Body();
  Object::ForEach(body, [codeList](const Object::PyObjPtr& stmt) {
    stmt->as<INode>()->emit(codeList);
  });
  code->JumpAbsolute(start - 1);
  Index end = code->Instructions()->Length();
  code->Instructions()->SetItem(
    start - 1, Object::CreateForIter(end - start + 1)
  );
  return Object::CreatePyNone();
}

Object::PyObjPtr ForStmtKlass::visit(
  const Object::PyObjPtr& obj,
  const Object::PyObjPtr& codeList
) {
  auto stmt = obj->as<ForStmt>();
  auto target = stmt->Target();
  auto iter = stmt->Iter();
  auto body = stmt->Body();
  iter->visit(codeList);
  if (target->is(IdentifierKlass::Self())) {
    auto identifier = target->as<Identifier>();
    auto code = GetCodeFromList(codeList, stmt);
    auto name = identifier->Name();
    if (code->GetScope() == Object::Scope::GLOBAL) {
      code->RegisterName(name);
    }
    if (code->GetScope() == Object::Scope::LOCAL) {
      code->RegisterVarName(name);
    }
  } else {
    Function::DebugPrint(target);
    throw std::runtime_error("ForStmt::visit(): unsupported target type");
  }
  Object::ForEach(body, [codeList](const Object::PyObjPtr& stmt) {
    stmt->as<INode>()->visit(codeList);
  });
  return Object::CreatePyNone();
}

Object::PyObjPtr ForStmtKlass::print(const Object::PyObjPtr& obj) {
  auto stmt = obj->as<ForStmt>();
  auto iter = stmt->Iter();
  auto target = stmt->Target();
  auto body = stmt->Body();
  PrintNode(stmt, Object::CreatePyString("ForStmt"));
  iter->print();
  PrintEdge(stmt, iter, Object::CreatePyString("iter"));
  target->print();
  PrintEdge(stmt, target, Object::CreatePyString("target"));
  Object::ForEach(body, [&](const Object::PyObjPtr& stmt) {
    stmt->as<INode>()->print();
    PrintEdge(stmt, stmt, Object::CreatePyString("stmt"));
  });
  return Object::CreatePyNone();
}

}  // namespace torchlight::IR
