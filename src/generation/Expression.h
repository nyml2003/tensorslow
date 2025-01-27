#ifndef TORCHLIGHT_GENERATION_EXPRESSION_H
#define TORCHLIGHT_GENERATION_EXPRESSION_H

#include "Collections/List.h"
#include "Generation/Common.h"
#include "Object/Common.h"

namespace torchlight::Generation {

enum class BinaryOperator {
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
};

enum class UnaryOperator {
  Error = 0,
  Add,  // +
  Sub,  // -
};

struct Binary {
  BinaryOperator oprt;
  Expr left;
  Expr right;
};

struct Unary {
  UnaryOperator oprt;
  Expr operand;
};

struct Identifier {
  Object::PyObjPtr name;
};

struct Atom {
  Object::PyObjPtr obj;
};

struct List {
  Collections::List<Expr> elements;
};

struct FunctionCall {
  Identifier functionName;
  List arguments;
};

struct Expression {
  ExpressionKind kind;
  explicit Expression(ExpressionKind kind);
};

Expr CreateBinary(BinaryOperator oprt, Expr left, Expr right);

Expr CreateUnary(UnaryOperator oprt, Expr operand);

Expr CreateAtom(Object::PyObjPtr obj);

Expr CreateFunctionCall(Identifier functionName, List arguments);

Expr CreateIdentifier(Object::PyObjPtr name);

Expr CreateList(Collections::List<Expr> elements);
}  // namespace torchlight::Generation

#endif  // TORCHLIGHT_GENERATION_EXPRESSION_H