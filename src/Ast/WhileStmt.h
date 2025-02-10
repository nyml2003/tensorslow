#ifndef TORCHLIGHT_AST_WHILE_STATEMENT_H
#define TORCHLIGHT_AST_WHILE_STATEMENT_H

#include "Ast/INode.h"

namespace torchlight::Ast {

class WhileStmt : public INode {
 public:
  explicit WhileStmt(
    Ast::INodePtr condition,
    Object::PyListPtr body,
    Ast::INodePtr parent
  );

  Ast::INodePtr Condition() const;

  Object::PyListPtr Body() const;

 private:
  Ast::INodePtr condition;
  Object::PyListPtr body;
};

Ast::INodePtr CreateWhileStmt(
  Ast::INodePtr condition,
  Object::PyObjPtr body,
  Ast::INodePtr parent
);

class WhileStmtKlass : public INodeKlass {
 public:
  explicit WhileStmtKlass();

  static Object::KlassPtr Self();

  Object::PyObjPtr visit(Object::PyObjPtr obj, Object::PyObjPtr codeList)
    override;

  Object::PyObjPtr emit(Object::PyObjPtr obj, Object::PyObjPtr codeList)
    override;

  void Initialize() override;
};

}  // namespace torchlight::Ast

#endif