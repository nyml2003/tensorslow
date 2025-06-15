#ifndef TENSORSLOW_AST_YIELD_EXPRESSION_H
#define TENSORSLOW_AST_YIELD_EXPRESSION_H

#include "IR/INode.h"

namespace tensorslow::IR {

class YieldExprKlass : public INodeKlass {
 public:
  explicit YieldExprKlass() = default;

  void Initialize() override {
    if (this->isInitialized) {
      return;
    }
    InitKlass(Object::CreatePyString("ast_YieldExpr"), Self());
    this->isInitialized = true;
  }

  static Object::KlassPtr Self() {
    static auto instance = std::make_shared<YieldExprKlass>();
    return instance;
  }

  Object::PyObjPtr
  visit(const Object::PyObjPtr& obj, const Object::PyObjPtr& codeList) override;

  Object::PyObjPtr
  emit(const Object::PyObjPtr& obj, const Object::PyObjPtr& codeList) override;

  Object::PyObjPtr print(const Object::PyObjPtr& obj) override;
};

class YieldExpr : public INode {
 public:
  explicit YieldExpr(INodePtr content, INodePtr parent)
    : INode(YieldExprKlass::Self(), std::move(parent)),
      content(std::move(content)) {}

  [[nodiscard]] INodePtr Content() const { return content; }

 private:
  INodePtr content;
};

inline INodePtr CreateYieldExpr(INodePtr content, INodePtr parent) {
  return std::make_shared<YieldExpr>(std::move(content), std::move(parent));
}

}  // namespace tensorslow::IR

#endif