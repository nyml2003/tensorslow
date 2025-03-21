#ifndef TORCHLIGHT_AST_WHILE_STATEMENT_H
#define TORCHLIGHT_AST_WHILE_STATEMENT_H
#include "Ast/INode.h"
#include "Function/ObjectHelper.h"

namespace torchlight::Ast {

class WhileStmtKlass : public INodeKlass {
 public:
  explicit WhileStmtKlass() = default;

  static Object::KlassPtr Self() {
    static auto instance = std::make_shared<WhileStmtKlass>();
    LoadClass(
      Object::CreatePyString("WhileStmt")->as<Object::PyString>(), instance
    );
    ConfigureBasicAttributes(instance);
    return instance;
  }

  Object::PyObjPtr
  visit(const Object::PyObjPtr& obj, const Object::PyObjPtr& codeList) override;

  Object::PyObjPtr
  emit(const Object::PyObjPtr& obj, const Object::PyObjPtr& codeList) override;
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
  const Object::PyObjPtr& body,
  INodePtr parent
) {
  return std::make_shared<WhileStmt>(
    std::move(condition), body->as<Object::PyList>(), std::move(parent)
  );
}

}  // namespace torchlight::Ast

#endif