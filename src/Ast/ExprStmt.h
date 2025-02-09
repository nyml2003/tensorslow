#ifndef TORCHLIGHT_AST_EXPRESSION_STATEMENT_H
#define TORCHLIGHT_AST_EXPRESSION_STATEMENT_H

#include "Ast/INode.h"

namespace torchlight::Ast {

class ExprStmt : public INode {
 public:
  explicit ExprStmt(Ast::INodePtr content, Ast::INodePtr parent);

  Ast::INodePtr Content() const;

 private:
  Ast::INodePtr content;
};

Ast::INodePtr CreateExprStmt(Ast::INodePtr content, Ast::INodePtr parent);

class ExprStmtKlass : public INodeKlass {
 public:
  explicit ExprStmtKlass();

  static Object::KlassPtr Self();

  Object::PyObjPtr visit(Object::PyObjPtr obj, Object::PyObjPtr codeList)
    override;

  Object::PyObjPtr emit(Object::PyObjPtr obj, Object::PyObjPtr codeList)
    override;

  void Initialize() override;
};

}  // namespace torchlight::Ast

#endif