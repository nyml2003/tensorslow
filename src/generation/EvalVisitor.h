#ifndef TORCHLIGHT_EVALVISITOR_H
#define TORCHLIGHT_EVALVISITOR_H

#include <antlr4-runtime.h>
#include <sstream>

#include "Python3ParserBaseVisitor.h"

class EvalVisitor : public Python3ParserBaseVisitor {
 private:
  std::vector<std::string> output;

 public:
  explicit EvalVisitor();

  void WriteToFile(const char* filename);

  antlrcpp::Any visitAtom(Python3Parser::AtomContext* ctx) override;

  antlrcpp::Any visitExpr(Python3Parser::ExprContext* ctx) override;

  // antlrcpp::Any visitAtom_expr(Python3Parser::Atom_exprContext* ctx)
  // override;
};

#endif  // TORCHLIGHT_EVALVISITOR_H