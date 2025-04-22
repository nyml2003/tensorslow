#ifndef TORCHLIGHT_AST_FOR_STATEMENT_H
#define TORCHLIGHT_AST_FOR_STATEMENT_H

#include "Function/BuiltinFunction.h"
#include "IR/INode.h"

namespace torchlight::IR {

class ForStmtKlass : public INodeKlass {
 public:
  explicit ForStmtKlass() = default;

  void Initialize() override {
    if (this->isInitialized) {
      return;
    }
    InitKlass(Object::CreatePyString("ast_forstmt"), Self());
    this->isInitialized = true;
  }

  static Object::KlassPtr Self() {
    static auto instance = std::make_shared<ForStmtKlass>();
    return instance;
  }

  Object::PyObjPtr
  visit(const Object::PyObjPtr& obj, const Object::PyObjPtr& codeList) override;

  Object::PyObjPtr
  emit(const Object::PyObjPtr& obj, const Object::PyObjPtr& codeList) override;
};

class ForStmt : public INode {
 public:
  explicit ForStmt(
    INodePtr target,
    INodePtr iter,
    Object::PyListPtr body,
    INodePtr parent
  )
    : INode(ForStmtKlass::Self(), std::move(parent)),
      target(std::move(target)),
      iter(std::move(iter)),
      body(std::move(body)) {}

  INodePtr Target() const { return target; }

  INodePtr Iter() const { return iter; }

  Object::PyListPtr Body() const { return body; }

 private:
  INodePtr target;
  INodePtr iter;
  Object::PyListPtr body;
};

inline INodePtr CreateForStmt(
  const INodePtr& target,
  const INodePtr& iter,
  const Object::PyListPtr& body,
  const INodePtr& parent
) {
  return std::make_shared<ForStmt>(target, iter, body, parent);
}

}  // namespace torchlight::IR

#endif