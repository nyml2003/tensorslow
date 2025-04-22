#ifndef TORCHLIGHT_AST_SLICE_H
#define TORCHLIGHT_AST_SLICE_H

#include "Function/BuiltinFunction.h"
#include "IR/INode.h"

namespace torchlight::IR {

class SliceKlass : public INodeKlass {
 public:
  SliceKlass() = default;

  void Initialize() override {
    if (this->isInitialized) {
      return;
    }
    InitKlass(Object::CreatePyString("ast_slice"), Self());
    this->isInitialized = true;
  }

  static Object::KlassPtr Self() {
    static auto instance = std::make_shared<SliceKlass>();
    return instance;
  }

  Object::PyObjPtr
  visit(const Object::PyObjPtr& obj, const Object::PyObjPtr& codeList) override;

  Object::PyObjPtr
  emit(const Object::PyObjPtr& obj, const Object::PyObjPtr& codeList) override;
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

}  // namespace torchlight::IR

#endif