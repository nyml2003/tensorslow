#ifndef TORCHLIGHT_AST_PASSSTMT_H
#define TORCHLIGHT_AST_PASSSTMT_H

#include "Ast/INode.h"
#include "Function/ObjectHelper.h"
#include "Object/Core/PyNone.h"

namespace torchlight::Ast {

class PassStmtKlass : public INodeKlass {
 public:
  static Object::KlassPtr Self() {
    static auto instance = std::make_shared<PassStmtKlass>();
    LoadClass(
      Object::CreatePyString("PassStmt")->as<Object::PyString>(), instance
    );
    ConfigureBasicAttributes(instance);
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

}  // namespace torchlight::Ast

#endif