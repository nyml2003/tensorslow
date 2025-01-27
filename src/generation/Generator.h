#ifndef TORCHLIGHT_EVALVISITOR_H
#define TORCHLIGHT_EVALVISITOR_H

#include <antlr4-runtime.h>
#include "Generation/Expression.h"
#include "Object/Common.h"
#include "Python3ParserBaseVisitor.h"

namespace torchlight::Generation {

class Generator : public Python3ParserBaseVisitor {
 private:
  Object::PyObjPtr consts;
  Object::PyObjPtr names;
  Object::PyObjPtr instructions;
  Object::PyObjPtr filename;

 public:
  explicit Generator(Object::PyObjPtr filename);
  Object::PyObjPtr Generate();
  antlrcpp::Any visitFile_input(Python3Parser::File_inputContext* ctx) override;
  antlrcpp::Any visitAtom(Python3Parser::AtomContext* ctx) override;

  antlrcpp::Any visitExpr(Python3Parser::ExprContext* ctx) override;

  antlrcpp::Any visitAtom_expr(Python3Parser::Atom_exprContext* ctx) override;

  antlrcpp::Any visitExpr_stmt(Python3Parser::Expr_stmtContext* ctx) override;

  antlrcpp::Any visitArglist(Python3Parser::ArglistContext* ctx) override;

  antlrcpp::Any visitTestlist_star_expr(
    Python3Parser::Testlist_star_exprContext* ctx
  ) override;

  antlrcpp::Any visitArgument(Python3Parser::ArgumentContext* ctx) override;

  antlrcpp::Any visitTest(Python3Parser::TestContext* ctx) override;

  antlrcpp::Any visitOr_test(Python3Parser::Or_testContext* ctx) override;

  antlrcpp::Any visitAnd_test(Python3Parser::And_testContext* ctx) override;

  antlrcpp::Any visitNot_test(Python3Parser::Not_testContext* ctx) override;

  antlrcpp::Any visitComparison(Python3Parser::ComparisonContext* ctx) override;
};

void LoadConst(
  const Object::PyObjPtr& obj,
  const Object::PyObjPtr& consts,
  const Object::PyObjPtr& instructions
);

void LoadName(
  const Object::PyObjPtr& name,
  const Object::PyObjPtr& names,
  const Object::PyObjPtr& instructions
);

void StoreName(
  const Object::PyObjPtr& name,
  const Object::PyObjPtr& names,
  const Object::PyObjPtr& instructions
);

void CallFunction(Index nArgs, const Object::PyObjPtr& instructions);

void CodegenExpr(
  const Expr& expr,
  const Object::PyObjPtr& consts,
  const Object::PyObjPtr& names,
  const Object::PyObjPtr& instructions
);

void CodegenAtom(
  const Atom& atom,
  const Object::PyObjPtr& consts,
  const Object::PyObjPtr& instructions
);

void CodegenBinary(
  const Binary& binary,
  const Object::PyObjPtr& consts,
  const Object::PyObjPtr& names,
  const Object::PyObjPtr& instructions
);

void CodegenUnary(
  const Unary& unary,
  const Object::PyObjPtr& consts,
  const Object::PyObjPtr& names,
  const Object::PyObjPtr& instructions
);

void CodegenFunctionCall(
  const FunctionCall& call,
  const Object::PyObjPtr& consts,
  const Object::PyObjPtr& names,
  const Object::PyObjPtr& instructions
);

void CodegenIdentifier(
  const Identifier& identifier,
  const Object::PyObjPtr& names,
  const Object::PyObjPtr& instructions
);

void CodegenList(
  const List& list,
  const Object::PyObjPtr& consts,
  const Object::PyObjPtr& names,
  const Object::PyObjPtr& instructions
);

Object::PyObjPtr
IndexOfConst(const Object::PyObjPtr& obj, const Object::PyObjPtr& consts);

Object::PyObjPtr
IndexOfName(const Object::PyObjPtr& name, const Object::PyObjPtr& names);

}  // namespace torchlight::Generation

#endif  // TORCHLIGHT_EVALVISITOR_H