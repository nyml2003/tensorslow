#ifndef TORCHLIGHT_AST_LIST_H
#define TORCHLIGHT_AST_LIST_H

#include <utility>

#include "Ast/INode.h"
#include "Object/ObjectHelper.h"

namespace torchlight::Ast {

class ListKlass : public INodeKlass {
 public:
  ListKlass() = default;

  static Object::KlassPtr Self() {
    static auto instance = std::make_shared<ListKlass>();
    Object::LoadClass(
      Object::CreatePyString("List")->as<Object::PyString>(), instance
    );
    Object::ConfigureBasicAttributes(instance);
    return instance;
  }

  Object::PyObjPtr
  visit(const Object::PyObjPtr& obj, const Object::PyObjPtr& codeList) override;

  Object::PyObjPtr
  emit(const Object::PyObjPtr& obj, const Object::PyObjPtr& codeList) override;
};

// 作为右值的list
class List : public INode {
 public:
  explicit List(Object::PyListPtr elements, INodePtr parent)
    : INode(ListKlass::Self(), std::move(parent)),
      elements(std::move(elements)) {}

  [[nodiscard]] Object::PyListPtr Elements() const { return elements; }

 private:
  Object::PyListPtr elements;
};

using ListPtr = std::shared_ptr<List>;

inline INodePtr
CreateList(const Object::PyListPtr& elements, const INodePtr& parent) {
  return std::make_shared<List>(elements, parent);
}

}  // namespace torchlight::Ast

#endif