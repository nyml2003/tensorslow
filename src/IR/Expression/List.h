#ifndef TENSORSLOW_AST_LIST_H
#define TENSORSLOW_AST_LIST_H

#include <utility>

#include "Function/BuiltinFunction.h"
#include "IR/INode.h"

namespace tensorslow::IR {

class ListKlass : public INodeKlass {
 public:
  ListKlass() = default;

  void Initialize() override {
    if (this->isInitialized) {
      return;
    }
    InitKlass(Object::CreatePyString("ast_list"), Self());
    this->isInitialized = true;
  }

  static Object::KlassPtr Self() {
    static auto instance = std::make_shared<ListKlass>();
    return instance;
  }

  Object::PyObjPtr
  visit(const Object::PyObjPtr& obj, const Object::PyObjPtr& codeList) override;

  Object::PyObjPtr
  emit(const Object::PyObjPtr& obj, const Object::PyObjPtr& codeList) override;

  Object::PyObjPtr print(const Object::PyObjPtr& obj) override;
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

}  // namespace tensorslow::IR

#endif