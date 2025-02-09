#ifndef TORCHLIGHT_AST_ATOM_H
#define TORCHLIGHT_AST_ATOM_H

#include "Ast/INode.h"

namespace torchlight::Ast {
// True False None Integer Float String字面量，不包含dict, list, tuple
class Atom : public INode {
 public:
  explicit Atom(Object::PyObjPtr obj, Ast::INodePtr parent);

  [[nodiscard]] Object::PyObjPtr Obj() const;

 private:
  Object::PyObjPtr obj;
};

class AtomKlass : public INodeKlass {
 public:
  AtomKlass();

  static Object::KlassPtr Self();

  Object::PyObjPtr visit(Object::PyObjPtr obj, Object::PyObjPtr codeList)
    override;

  Object::PyObjPtr emit(Object::PyObjPtr obj, Object::PyObjPtr codeList)
    override;

  void Initialize() override;
};

using AtomPtr = std::shared_ptr<Atom>;

Ast::INodePtr CreateAtom(Object::PyObjPtr obj, Ast::INodePtr parent);

}  // namespace torchlight::Ast

#endif