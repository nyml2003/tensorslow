#ifndef TORCHLIGHT_AST_YIELD_STATEMENT_H
#define TORCHLIGHT_AST_YIELD_STATEMENT_H

#include "Ast/INode.h"

namespace torchlight::Ast {

class YieldStmtKlass : public INodeKlass {
 public:
  explicit YieldStmtKlass() = default;

  void Initialize() override {
    if (this->isInitialized) {
      return;
    }
    InitKlass(
      Object::CreatePyString("ast_yieldstmt")->as<Object::PyString>(), Self()
    );
    this->isInitialized = true;
  }

  static Object::KlassPtr Self() {
    static auto instance = std::make_shared<YieldStmtKlass>();
    return instance;
  }

  Object::PyObjPtr
  visit(const Object::PyObjPtr& obj, const Object::PyObjPtr& codeList) override;

  Object::PyObjPtr
  emit(const Object::PyObjPtr& obj, const Object::PyObjPtr& codeList) override;
};

class YieldStmt : public INode {
 public:
  explicit YieldStmt(INodePtr content, INodePtr parent)
    : INode(YieldStmtKlass::Self(), std::move(parent)),
      content(std::move(content)) {}

  [[nodiscard]] INodePtr Content() const { return content; }

 private:
  INodePtr content;
};

inline INodePtr CreateYieldStmt(INodePtr content, INodePtr parent) {
  return std::make_shared<YieldStmt>(std::move(content), std::move(parent));
}

}  // namespace torchlight::Ast

#endif