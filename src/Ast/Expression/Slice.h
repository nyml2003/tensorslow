#ifndef TORCHLIGHT_AST_SLICE_H
#define TORCHLIGHT_AST_SLICE_H

#include "Ast/INode.h"
#include "Object/ObjectHelper.h"

namespace torchlight::Ast {

class SliceKlass : public INodeKlass {
 public:
  SliceKlass() = default;

  static Object::KlassPtr Self() {
    static auto instance = std::make_shared<SliceKlass>();
    Object::LoadClass(
      Object::CreatePyString("Slice")->as<Object::PyString>(), instance
    );
    Object::ConfigureBasicAttributes(instance);
    return instance;
  }

  Object::PyObjPtr visit(
    const Object::PyObjPtr& obj,
    const Object::PyObjPtr& codeList
  ) override;

  Object::PyObjPtr emit(
    const Object::PyObjPtr& obj,
    const Object::PyObjPtr& codeList
  ) override;
};

// 作为右值的list
class Slice : public INode {
 public:
  explicit Slice(Object::PyListPtr elements, INodePtr parent)
    : INode(SliceKlass::Self(), std::move(parent)),
      elements(std::move(elements)) {}

  [[nodiscard]] Object::PyListPtr Elements() const { return elements; }

 private:
  Object::PyListPtr elements;
};

using SlicePtr = std::shared_ptr<Slice>;

inline INodePtr
CreateSlice(const Object::PyListPtr& elements, const INodePtr& parent) {
  return std::make_shared<Slice>(elements, parent);
}

}  // namespace torchlight::Ast

#endif