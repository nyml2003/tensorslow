#ifndef TORCHLIGHT_AST_LIST_H
#define TORCHLIGHT_AST_LIST_H

#include "Ast/INode.h"

namespace torchlight::Ast {
// 作为右值的list
class List : public INode {
 public:
  explicit List(Object::PyObjPtr elements, Ast::INodePtr parent);

  [[nodiscard]] Object::PyListPtr Elements() const;

 private:
  Object::PyListPtr elements;
};

class ListKlass : public INodeKlass {
 public:
  ListKlass();

  static Object::KlassPtr Self();

  Object::PyObjPtr visit(Object::PyObjPtr obj, Object::PyObjPtr codeList)
    override;

  Object::PyObjPtr emit(Object::PyObjPtr obj, Object::PyObjPtr codeList)
    override;

  void Initialize() override;
};

using ListPtr = std::shared_ptr<List>;

Ast::INodePtr CreateList(Object::PyObjPtr elements, Ast::INodePtr parent);

}  // namespace torchlight::Ast

#endif