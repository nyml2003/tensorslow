#ifndef TORCHLIGHT_AST_IF_STATEMENT_H
#define TORCHLIGHT_AST_IF_STATEMENT_H

#include "Ast/INode.h"

namespace torchlight::Ast {

class IfStmtKlass : public INodeKlass {
 public:
  explicit IfStmtKlass() = default;

  static Object::KlassPtr Self() {
    static auto instance = std::make_shared<IfStmtKlass>();
    LoadClass(
      Object::CreatePyString("IfStmt")->as<Object::PyString>(), instance
    );
    ConfigureBasicAttributes(instance);
    return instance;
  }

  Object::PyObjPtr
  visit(const Object::PyObjPtr& obj, const Object::PyObjPtr& codeList) override;

  Object::PyObjPtr
  emit(const Object::PyObjPtr& obj, const Object::PyObjPtr& codeList) override;
};

class IfStmt : public INode {
 public:
  explicit IfStmt(
    INodePtr condition,
    Object::PyListPtr thenStmts,
    INodePtr parent
  )
    : INode(IfStmtKlass::Self(), std::move(parent)),
      condition(std::move(condition)),
      thenStmts(std::move(thenStmts)) {}

  [[nodiscard]] INodePtr Condition() const { return condition; }

  [[nodiscard]] Object::PyListPtr ThenStmts() const { return thenStmts; }

 private:
  INodePtr condition;
  Object::PyListPtr thenStmts;
};

inline INodePtr CreateIfStmt(
  const INodePtr& condition,
  const Object::PyObjPtr& thenStmts,
  INodePtr parent
) {
  return std::make_shared<IfStmt>(
    condition, thenStmts->as<Object::PyList>(), std::move(parent)
  );
}

}  // namespace torchlight::Ast

#endif