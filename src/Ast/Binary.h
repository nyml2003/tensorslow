#ifndef TORCHLIGHT_AST_BINARY_H
#define TORCHLIGHT_AST_BINARY_H

#include "Ast/INode.h"
namespace torchlight::Ast {

class Binary : public Ast::INode {
 public:
  enum class Operator {
    Error = 0,
    LT,         // <
    GT,         // >
    EQ,         // ==
    GE,         // >=
    LE,         // <=
    NE,         // "!="
    IN,         // in
    NOT_IN,     // not in
    IS,         // is
    IS_NOT,     // is not
    ADD,        // +
    SUB,        // -
    MUL,        // *
    DIV,        // "/"
    MATMUL,     // @
    MOD,        // %
    FLOOR_DIV,  // "//"
    SUBSCR,     // []
  };

  explicit Binary(
    Operator oprt,
    Ast::INodePtr left,
    Ast::INodePtr right,
    Ast::INodePtr parent
  );

  [[nodiscard]] Ast::INodePtr Left() const;

  [[nodiscard]] Ast::INodePtr Right() const;

  [[nodiscard]] Operator Oprt() const;

 private:
  Operator oprt;
  Ast::INodePtr parent;
  Ast::INodePtr left;
  Ast::INodePtr right;
};

class BinaryKlass : public INodeKlass {
 public:
  BinaryKlass();

  static Object::KlassPtr Self();

  Object::PyObjPtr visit(Object::PyObjPtr obj, Object::PyObjPtr codeList)
    override;

  Object::PyObjPtr emit(Object::PyObjPtr obj, Object::PyObjPtr codeList)
    override;

  void Initialize() override;
};

using BinaryPtr = std::shared_ptr<Binary>;
Ast::INodePtr CreateBinary(
  Binary::Operator oprt,
  Ast::INodePtr left,
  Ast::INodePtr right,
  Ast::INodePtr parent
);

}  // namespace torchlight::Ast

#endif