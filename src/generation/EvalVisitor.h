#ifndef TORCHLIGHT_EVALVISITOR_H
#define TORCHLIGHT_EVALVISITOR_H

#include <antlr4-runtime.h>
#include <fstream>

#include "CalculatorBaseVisitor.h"

class EvalVisitor : public CalculatorBaseVisitor {
 private:
  std::ofstream output;

 public:
  explicit EvalVisitor(const std::string& outputFilename);
  antlrcpp::Any visitProg(CalculatorParser::ProgContext* ctx) override;
  antlrcpp::Any visitPrimaryExpr(CalculatorParser::PrimaryExprContext* ctx
  ) override;
  antlrcpp::Any visitMulDivExpr(CalculatorParser::MulDivExprContext* ctx
  ) override;
  antlrcpp::Any visitAddSubExpr(CalculatorParser::AddSubExprContext* ctx
  ) override;
  antlrcpp::Any visitExpr(CalculatorParser::ExprContext* ctx) override;

  antlrcpp::Any visitStatement(CalculatorParser::StatementContext* ctx
  ) override;
};

#endif  // TORCHLIGHT_EVALVISITOR_H