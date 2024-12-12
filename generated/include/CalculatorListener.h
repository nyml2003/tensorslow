
// Generated from /app/grammar/Calculator.g4 by ANTLR 4.9.2

#pragma once


#include "antlr4-runtime.h"
#include "CalculatorParser.h"


/**
 * This interface defines an abstract listener for a parse tree produced by CalculatorParser.
 */
class  CalculatorListener : public antlr4::tree::ParseTreeListener {
public:

  virtual void enterProg(CalculatorParser::ProgContext *ctx) = 0;
  virtual void exitProg(CalculatorParser::ProgContext *ctx) = 0;

  virtual void enterPrimaryExpr(CalculatorParser::PrimaryExprContext *ctx) = 0;
  virtual void exitPrimaryExpr(CalculatorParser::PrimaryExprContext *ctx) = 0;

  virtual void enterMulDivExpr(CalculatorParser::MulDivExprContext *ctx) = 0;
  virtual void exitMulDivExpr(CalculatorParser::MulDivExprContext *ctx) = 0;

  virtual void enterAddSubExpr(CalculatorParser::AddSubExprContext *ctx) = 0;
  virtual void exitAddSubExpr(CalculatorParser::AddSubExprContext *ctx) = 0;

  virtual void enterExpr(CalculatorParser::ExprContext *ctx) = 0;
  virtual void exitExpr(CalculatorParser::ExprContext *ctx) = 0;

  virtual void enterStatement(CalculatorParser::StatementContext *ctx) = 0;
  virtual void exitStatement(CalculatorParser::StatementContext *ctx) = 0;


};

