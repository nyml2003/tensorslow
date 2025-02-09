#ifndef TORCHLIGHT_AST_ASSIGN_STATEMENT_H
#define TORCHLIGHT_AST_ASSIGN_STATEMENT_H

#include "Ast/INode.h"

namespace torchlight::Ast {

class AssignStmt : public INode {
 public:
  explicit AssignStmt(
    Ast::INodePtr target,
    Ast::INodePtr source,
    Ast::INodePtr parent
  );

  Ast::INodePtr Target() const;

  Ast::INodePtr Source() const;

 private:
  Ast::INodePtr target;
  Ast::INodePtr source;
};

Ast::INodePtr CreateAssignStmt(
  Ast::INodePtr target,
  Ast::INodePtr source,
  Ast::INodePtr parent
);

class AssignStmtKlass : public INodeKlass {
 public:
  explicit AssignStmtKlass();

  static Object::KlassPtr Self();

  Object::PyObjPtr visit(Object::PyObjPtr obj, Object::PyObjPtr codeList)
    override;

  Object::PyObjPtr emit(Object::PyObjPtr obj, Object::PyObjPtr codeList)
    override;

  void Initialize() override;
};

}  // namespace torchlight::Ast

#endif