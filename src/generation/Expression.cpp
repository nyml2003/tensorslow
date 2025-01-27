#include "Generation/Expression.h"

#include <utility>
#include "Object/Common.h"

namespace torchlight::Generation {

Expression::Expression(ExpressionKind kind) : kind(std::move(kind)) {}

Expr CreateBinary(BinaryOperator oprt, Expr left, Expr right) {
  return std::make_shared<Expression>(
    Binary{.oprt = oprt, .left = std::move(left), .right = std::move(right)}
  );
}

Expr CreateUnary(UnaryOperator oprt, Expr operand) {
  return std::make_shared<Expression>(
    Unary{.oprt = oprt, .operand = std::move(operand)}
  );
}

Expr CreateAtom(Object::PyObjPtr obj) {
  return std::make_shared<Expression>(Atom{.obj = std::move(obj)});
}

Expr CreateFunctionCall(Identifier functionName, List arguments) {
  return std::make_shared<Expression>(FunctionCall{
    .functionName = std::move(functionName), .arguments = std::move(arguments)
  });
}

Expr CreateIdentifier(Object::PyObjPtr name) {
  return std::make_shared<Expression>(Identifier{.name = std::move(name)});
}

Expr CreateList(Collections::List<Expr> elements) {
  return std::make_shared<Expression>(List{.elements = std::move(elements)});
}

}  // namespace torchlight::Generation