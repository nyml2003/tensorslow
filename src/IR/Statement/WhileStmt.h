#ifndef TENSORSLOW_AST_WHILE_STATEMENT_H
#define TENSORSLOW_AST_WHILE_STATEMENT_H
#include "Function/BuiltinFunction.h"
#include "IR/INode.h"

namespace tensorslow::IR {

class WhileStmtKlass : public INodeKlass {
 public:
  explicit WhileStmtKlass() = default;

  void Initialize() override {
    if (this->isInitialized) {
      return;
    }
    InitKlass(Object::CreatePyString("ast_whilestmt"), Self());
    this->isInitialized = true;
  }

  static Object::KlassPtr Self() {
    static auto instance = std::make_shared<WhileStmtKlass>();
    return instance;
  }

  Object::PyObjPtr
  visit(const Object::PyObjPtr& obj, const Object::PyObjPtr& codeList) override;

  Object::PyObjPtr
  emit(const Object::PyObjPtr& obj, const Object::PyObjPtr& codeList) override;

  Object::PyObjPtr print(const Object::PyObjPtr& obj) override;
};

class WhileStmt : public INode {
 public:
  explicit WhileStmt(
    INodePtr condition,
    Object::PyListPtr body,
    INodePtr parent
  )
    : INode(WhileStmtKlass::Self(), std::move(parent)),
      condition(std::move(condition)),
      body(std::move(body)) {}

  INodePtr Condition() const { return condition; }

  Object::PyListPtr Body() const { return body; }

 private:
  INodePtr condition;
  Object::PyListPtr body;
};

inline INodePtr CreateWhileStmt(
  INodePtr condition,
  const Object::PyListPtr& body,
  INodePtr parent
) {
  return std::make_shared<WhileStmt>(
    std::move(condition), body, std::move(parent)
  );
}

}  // namespace tensorslow::IR

#endif