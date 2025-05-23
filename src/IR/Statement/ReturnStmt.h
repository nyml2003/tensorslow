#ifndef TENSORSLOW_AST_RETURN_STATEMENT_H
#define TENSORSLOW_AST_RETURN_STATEMENT_H

#include "IR/INode.h"

namespace tensorslow::IR {

class ReturnStmtKlass : public INodeKlass {
 public:
  explicit ReturnStmtKlass() = default;

  void Initialize() override {
    if (this->isInitialized) {
      return;
    }
    InitKlass(Object::CreatePyString("ast_returnstmt"), Self());
    this->isInitialized = true;
  }

  static Object::KlassPtr Self() {
    static auto instance = std::make_shared<ReturnStmtKlass>();
    return instance;
  }

  Object::PyObjPtr
  visit(const Object::PyObjPtr& obj, const Object::PyObjPtr& codeList) override;

  Object::PyObjPtr
  emit(const Object::PyObjPtr& obj, const Object::PyObjPtr& codeList) override;

  Object::PyObjPtr print(const Object::PyObjPtr& obj) override;
};

class ReturnStmt : public INode {
 public:
  explicit ReturnStmt(INodePtr content, INodePtr parent)
    : INode(ReturnStmtKlass::Self(), std::move(parent)),
      content(std::move(content)) {}

  [[nodiscard]] INodePtr Content() const { return content; }

 private:
  INodePtr content;
};

inline INodePtr CreateReturnStmt(INodePtr content, INodePtr parent) {
  return std::make_shared<ReturnStmt>(std::move(content), std::move(parent));
}

}  // namespace tensorslow::IR

#endif