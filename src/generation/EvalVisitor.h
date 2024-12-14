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

  antlrcpp::Any visitIf_stmt(Python3Parser::If_stmtContext* ctx) override;

  antlrcpp::Any visitComparison(Python3Parser::ComparisonContext* ctx) override;

  antlrcpp::Any visitComp_op(Python3Parser::Comp_opContext* ctx) override;
};

#endif  // TORCHLIGHT_EVALVISITOR_H