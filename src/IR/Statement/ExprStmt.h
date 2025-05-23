#ifndef TENSORSLOW_AST_EXPRESSION_STATEMENT_H
#define TENSORSLOW_AST_EXPRESSION_STATEMENT_H

#include "Function/BuiltinFunction.h"
#include "IR/INode.h"

namespace tensorslow::IR {

class ExprStmtKlass : public INodeKlass {
 public:
  explicit ExprStmtKlass() = default;

  void Initialize() override {
    if (this->isInitialized) {
      return;
    }
    InitKlass(Object::CreatePyString("ast_exprstmt"), Self());
    this->isInitialized = true;
  }

  static Object::KlassPtr Self() {
    static auto instance = std::make_shared<ExprStmtKlass>();
    return instance;
  }

  Object::PyObjPtr
  visit(const Object::PyObjPtr& obj, const Object::PyObjPtr& codeList) override;

  Object::PyObjPtr
  emit(const Object::PyObjPtr& obj, const Object::PyObjPtr& codeList) override;

  Object::PyObjPtr print(const Object::PyObjPtr& obj) override;
};

class ExprStmt : public INode {
 public:
  explicit ExprStmt(INodePtr content, INodePtr parent)
    : INode(ExprStmtKlass::Self(), std::move(parent)),
      content(std::move(content)) {}

  [[nodiscard]] INodePtr Content() const { return content; }

 private:
  INodePtr content;
};

inline INodePtr
CreateExprStmt(const INodePtr& content, const INodePtr& parent) {
  return std::make_shared<ExprStmt>(content, parent);
}

}  // namespace tensorslow::IR

#endif