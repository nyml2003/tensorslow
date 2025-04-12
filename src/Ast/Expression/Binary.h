#ifndef TORCHLIGHT_AST_BINARY_H
#define TORCHLIGHT_AST_BINARY_H

#include "Ast/INode.h"
#include "Function/BuiltinFunction.h"

namespace torchlight::Ast {

class BinaryKlass : public INodeKlass {
 public:
  explicit BinaryKlass() = default;

  void Initialize() override {
    if (this->isInitialized) {
      return;
    }
    InitKlass(Object::CreatePyString("ast_binary"), Self());
    this->isInitialized = true;
  }

  static Object::KlassPtr Self() {
    static auto instance = std::make_shared<BinaryKlass>();
    return instance;
  }

  Object::PyObjPtr
  visit(const Object::PyObjPtr& obj, const Object::PyObjPtr& codeList) override;

  Object::PyObjPtr
  emit(const Object::PyObjPtr& obj, const Object::PyObjPtr& codeList) override;
};

class Binary : public Ast::INode {
 public:
  enum class Operator {
    IN_OP,         // in
    LT,            // <
    GT,            // >
    EQ,            // ==
    GE,            // >=
    LE,            // <=
    NE,            // "!="
    NOT_IN,        // not in
    IS,            // is
    IS_NOT,        // is not
    ADD,           // +
    SUB,           // -
    MUL,           // "*"
    DIV,           // "/"
    MATMUL,        // @
    MOD,           // %
    FLOOR_DIV,     // "//"
    SUBSCR,        // []
    STORE_SUBSCR,  // []=
    AND,           // and
    OR,            // or
    XOR,           // xor
    LSHIFT,        // <<
    RSHIFT,        // >>
    POWER,         // "**"
  };

  explicit Binary(Operator oprt, INodePtr left, INodePtr right, INodePtr parent)
    : INode(BinaryKlass::Self(), std::move(parent)),
      oprt(oprt),
      left(std::move(left)),
      right(std::move(right)) {}

  [[nodiscard]] INodePtr Left() const { return left; }

  [[nodiscard]] INodePtr Right() const { return right; }

  [[nodiscard]] Operator Oprt() const { return oprt; }

  void SetOprt(Operator oprt) { this->oprt = oprt; }

 private:
  Operator oprt;
  INodePtr left;
  INodePtr right;
};

inline INodePtr CreateBinary(
  Binary::Operator oprt,
  const INodePtr& left,
  const INodePtr& right,
  const INodePtr& parent
) {
  return std::make_shared<Binary>(oprt, left, right, parent);
}

}  // namespace torchlight::Ast

#endif