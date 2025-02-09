#ifndef TORCHLIGHT_AST_MEMBERACCESS_H
#define TORCHLIGHT_AST_MEMBERACCESS_H

#include "Ast/INode.h"

namespace torchlight::Ast {

class MemberAccess : public INode {
 public:
  MemberAccess(
    Ast::INodePtr obj,
    Object::PyObjPtr member,
    Ast::INodePtr parent
  );

  [[nodiscard]] Ast::INodePtr Obj() const;

  [[nodiscard]] Object::PyStrPtr Member() const;

 private:
  Ast::INodePtr obj;
  Object::PyStrPtr member;
};

class MemberAccessKlass : public INodeKlass {
 public:
  MemberAccessKlass();

  static Object::KlassPtr Self();

  Object::PyObjPtr visit(Object::PyObjPtr obj, Object::PyObjPtr codeList)
    override;

  Object::PyObjPtr emit(Object::PyObjPtr obj, Object::PyObjPtr codeList)
    override;

  void Initialize() override;
};

using MemberAccessPtr = std::shared_ptr<MemberAccess>;

Ast::INodePtr CreateMemberAccess(
  Ast::INodePtr obj,
  Object::PyObjPtr member,
  Ast::INodePtr parent
);

}  // namespace torchlight::Ast

#endif