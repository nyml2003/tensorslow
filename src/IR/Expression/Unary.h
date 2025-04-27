#ifndef TORCHLIGHT_AST_UNARY_H
#define TORCHLIGHT_AST_UNARY_H

#include "Function/BuiltinFunction.h"
#include "IR/INode.h"

namespace torchlight::IR {

class UnaryKlass : public INodeKlass {
 public:
  explicit UnaryKlass() = default;

  void Initialize() override {
    if (this->isInitialized) {
      return;
    }
    InitKlass(Object::CreatePyString("ast_unary"), Self());
    this->isInitialized = true;
  }

  static Object::KlassPtr Self() {
    static auto instance = std::make_shared<UnaryKlass>();
    return instance;
  }
  Object::PyObjPtr
  visit(const Object::PyObjPtr& obj, const Object::PyObjPtr& codeList) override;

  Object::PyObjPtr
  emit(const Object::PyObjPtr& obj, const Object::PyObjPtr& codeList) override;

  Object::PyObjPtr print(const Object::PyObjPtr& obj) override;
};

class Unary : public IR::INode {
 public:
  enum class Operator {
    PLUS,   // +
    MINUS,  // -
    NOT,    // not
    INVERT  // ~
  };

  explicit Unary(Operator oprt, INodePtr operand, INodePtr parent)
    : INode(UnaryKlass::Self(), std::move(parent)),
      oprt(oprt),
      operand(std::move(operand)) {}

  [[nodiscard]] INodePtr Operand() const { return operand; }

  [[nodiscard]] Operator Oprt() const { return oprt; }

 private:
  Operator oprt;
  INodePtr operand;
};

inline INodePtr
CreateUnary(Unary::Operator oprt, INodePtr operand, INodePtr parent) {
  return std::make_shared<Unary>(oprt, std::move(operand), std::move(parent));
}

}  // namespace torchlight::IR

#endif