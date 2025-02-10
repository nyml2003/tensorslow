#ifndef TORCHLIGHT_AST_IF_STATEMENT_H
#define TORCHLIGHT_AST_IF_STATEMENT_H

#include "Ast/INode.h"

namespace torchlight::Ast {

class IfStmt : public INode {
 public:
  explicit IfStmt(
    Ast::INodePtr condition,
    Object::PyListPtr thenStmts,
    Ast::INodePtr parent
  );

  Ast::INodePtr Condition() const;

  Object::PyListPtr ThenStmts() const;

 private:
  Ast::INodePtr condition;
  Object::PyListPtr thenStmts;
};

Ast::INodePtr CreateIfStmt(
  Ast::INodePtr condition,
  Object::PyObjPtr thenStmts,
  Ast::INodePtr parent
);

class IfStmtKlass : public INodeKlass {
 public:
  explicit IfStmtKlass();

  static Object::KlassPtr Self();

  Object::PyObjPtr visit(Object::PyObjPtr obj, Object::PyObjPtr codeList)
    override;

  Object::PyObjPtr emit(Object::PyObjPtr obj, Object::PyObjPtr codeList)
    override;

  void Initialize() override;
};

}  // namespace torchlight::Ast

#endif