#ifndef TORCHLIGHT_AST_IDENTIFIER_H
#define TORCHLIGHT_AST_IDENTIFIER_H

#include "Ast/INode.h"

namespace torchlight::Ast {

class Identifier : public INode {
 public:
  explicit Identifier(Object::PyObjPtr _name, Ast::INodePtr parent);

  [[nodiscard]] Object::PyStrPtr Name() const;

 private:
  Object::PyStrPtr name;
};

class IdentifierKlass : public INodeKlass {
 public:
  IdentifierKlass();

  static Object::KlassPtr Self();

  Object::PyObjPtr visit(Object::PyObjPtr obj, Object::PyObjPtr codeList)
    override;
  Object::PyObjPtr emit(Object::PyObjPtr obj, Object::PyObjPtr codeList)
    override;

  void Initialize() override;
};

using IdentifierPtr = std::shared_ptr<Identifier>;

Ast::INodePtr CreateIdentifier(Object::PyObjPtr name, Ast::INodePtr parent);

}  // namespace torchlight::Ast

#endif