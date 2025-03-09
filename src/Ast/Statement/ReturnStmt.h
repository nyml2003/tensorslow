#ifndef TORCHLIGHT_AST_RETURN_STATEMENT_H
#define TORCHLIGHT_AST_RETURN_STATEMENT_H

#include "Ast/INode.h"

namespace torchlight::Ast {

class ReturnStmtKlass : public INodeKlass {
 public:
  explicit ReturnStmtKlass() = default;

  static Object::KlassPtr Self() {
    static auto instance = std::make_shared<ReturnStmtKlass>();
    LoadClass(
      Object::CreatePyString("ReturnStmt")->as<Object::PyString>(), instance
    );
    ConfigureBasicAttributes(instance);
    return instance;
  }

  Object::PyObjPtr
  visit(const Object::PyObjPtr& obj, const Object::PyObjPtr& codeList) override;

  Object::PyObjPtr
  emit(const Object::PyObjPtr& obj, const Object::PyObjPtr& codeList) override;
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

}  // namespace torchlight::Ast

#endif