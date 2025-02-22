#ifndef TORCHLIGHT_AST_FOR_STATEMENT_H
#define TORCHLIGHT_AST_FOR_STATEMENT_H

#include "Ast/INode.h"
#include "Object/Object.h"

namespace torchlight::Ast {

class ForStmt : public INode {
 public:
  explicit ForStmt(
    Ast::INodePtr target,
    Ast::INodePtr iter,
    Object::PyObjPtr body,
    Ast::INodePtr parent
  );

  Ast::INodePtr Target() const;

  Ast::INodePtr Iter() const;

  Object::PyListPtr Body() const;

 private:
  Ast::INodePtr target;
  Ast::INodePtr iter;
  Object::PyListPtr body;
};

Ast::INodePtr CreateForStmt(
  Ast::INodePtr target,
  Ast::INodePtr iter,
  Object::PyObjPtr body,
  Ast::INodePtr parent
);

class ForStmtKlass : public INodeKlass {
 public:
  explicit ForStmtKlass();

  static Object::KlassPtr Self();

  Object::PyObjPtr visit(Object::PyObjPtr obj, Object::PyObjPtr codeList)
    override;

  Object::PyObjPtr emit(Object::PyObjPtr obj, Object::PyObjPtr codeList)
    override;

  void Initialize() override;
};

}  // namespace torchlight::Ast

#endif