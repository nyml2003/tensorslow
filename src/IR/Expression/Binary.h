#ifndef TORCHLIGHT_AST_BINARY_H
#define TORCHLIGHT_AST_BINARY_H

#include "Function/BuiltinFunction.h"
#include "IR/INode.h"

namespace torchlight::IR {

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

  Object::PyObjPtr print(const Object::PyObjPtr& obj) override;
};

class Binary : public IR::INode {
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

inline Object::PyStrPtr Stringify(Binary::Operator oprt) {
  switch (oprt) {
    case Binary::Operator::IN_OP:
      return Object::CreatePyString("in");
    case Binary::Operator::LT:
      return Object::CreatePyString("<");
    case Binary::Operator::GT:
      return Object::CreatePyString(">");
    case Binary::Operator::EQ:
      return Object::CreatePyString("==");
    case Binary::Operator::GE:
      return Object::CreatePyString(">=");
    case Binary::Operator::LE:
      return Object::CreatePyString("<=");
    case Binary::Operator::NE:
      return Object::CreatePyString("!=");
    case Binary::Operator::NOT_IN:
      return Object::CreatePyString("not in");
    case Binary::Operator::IS:
      return Object::CreatePyString("is");
    case Binary::Operator::IS_NOT:
      return Object::CreatePyString("is not");
    case Binary::Operator::ADD:
      return Object::CreatePyString("+");
    case Binary::Operator::SUB:
      return Object::CreatePyString("-");
    case Binary::Operator::MUL:
      return Object::CreatePyString("*");
    case Binary::Operator::DIV:
      return Object::CreatePyString("/");
    case Binary::Operator::MATMUL:
      return Object::CreatePyString("@");
    case Binary::Operator::MOD:
      return Object::CreatePyString("%");
    case Binary::Operator::FLOOR_DIV:
      return Object::CreatePyString("//");
    case Binary::Operator::SUBSCR:
      return Object::CreatePyString("[]");
    case Binary::Operator::STORE_SUBSCR:
      return Object::CreatePyString("[]=");
    case Binary::Operator::AND:
      return Object::CreatePyString("and");
    case Binary::Operator::OR:
      return Object::CreatePyString("or");
  }
}
}  // namespace torchlight::IR

#endif