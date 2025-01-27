#ifndef TORCHLIGHT_GENERATION_COMMON_H
#define TORCHLIGHT_GENERATION_COMMON_H

#include <memory>
#include <variant>

namespace torchlight::Generation {

enum class BinaryOperator;
enum class UnaryOperator;

struct Binary;
struct Unary;
struct FunctionCall;
struct Identifier;
struct Atom;
struct List;
struct MemberAccess;
struct AtomList;

using ExpressionKind = std::variant<
  Binary,
  Unary,
  Atom,
  FunctionCall,
  Identifier,
  List,
  MemberAccess,
  AtomList>;

struct Expression;

using Expr = std::shared_ptr<Expression>;

}  // namespace torchlight::Generation

#endif