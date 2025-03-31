#ifndef TORCHLIGHT_AST_ASSIGN_STATEMENT_H
#define TORCHLIGHT_AST_ASSIGN_STATEMENT_H

#include "Ast/INode.h"
#include "Function/ObjectHelper.h"

namespace torchlight::Ast {

class AssignStmtKlass : public INodeKlass {
 public:
  explicit AssignStmtKlass() = default;

  void Initialize() override {
    if (this->isInitialized) {
      return;
    }
    InitKlass(
      Object::CreatePyString("ast_assignstmt")->as<Object::PyString>(), Self()
    );
    this->isInitialized = true;
  }

  static Object::KlassPtr Self() {
    static auto instance = std::make_shared<AssignStmtKlass>();
    return instance;
  }

  Object::PyObjPtr
  visit(const Object::PyObjPtr& obj, const Object::PyObjPtr& codeList) override;

  Object::PyObjPtr
  emit(const Object::PyObjPtr& obj, const Object::PyObjPtr& codeList) override;
};

class AssignStmt : public INode {
 public:
  explicit AssignStmt(INodePtr target, INodePtr source, const INodePtr& parent)
    : INode(AssignStmtKlass::Self(), parent),
      target(std::move(target)),
      source(std::move(source)) {}

  INodePtr Target() const { return target; }

  INodePtr Source() const { return source; }

 private:
  INodePtr target;
  INodePtr source;
};

inline INodePtr
CreateAssignStmt(INodePtr target, INodePtr source, INodePtr parent) {
  return std::make_shared<AssignStmt>(
    std::move(target), std::move(source), std::move(parent)
  );
}

}  // namespace torchlight::Ast

#endif