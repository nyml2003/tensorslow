#ifndef TORCHLIGHT_AST_PASSSTMT_H
#define TORCHLIGHT_AST_PASSSTMT_H

#include "Function/BuiltinFunction.h"
#include "IR/INode.h"
#include "Object/Core/PyNone.h"

namespace torchlight::IR {

class PassStmtKlass : public INodeKlass {
 public:
  explicit PassStmtKlass() = default;

  void Initialize() override {
    if (this->isInitialized) {
      return;
    }
    InitKlass(Object::CreatePyString("ast_passstmt"), Self());
    this->isInitialized = true;
  }

  static Object::KlassPtr Self() {
    static auto instance = std::make_shared<PassStmtKlass>();
    return instance;
  }

  Object::PyObjPtr visit(
    const Object::PyObjPtr& /*obj*/,
    const Object::PyObjPtr& /*codeList*/
  ) override {
    return Object::CreatePyNone();
  }

  Object::PyObjPtr
  emit(const Object::PyObjPtr& obj, const Object::PyObjPtr& codeList) override;
};

class PassStmt : public INode {
 public:
  explicit PassStmt(const INodePtr& parent)
    : INode(PassStmtKlass::Self(), parent) {}
};

inline INodePtr CreatePassStmt(const INodePtr& parent) {
  return std::make_shared<PassStmt>(parent);
}

}  // namespace torchlight::IR

#endif