
// Generated from /app/grammar/Calculator.g4 by ANTLR 4.9.2

#pragma once


#include "antlr4-runtime.h"
#include "CalculatorListener.h"


/**
 * This class provides an empty implementation of CalculatorListener,
 * which can be extended to create a listener which only needs to handle a subset
 * of the available methods.
 */
class  CalculatorBaseListener : public CalculatorListener {
public:

  virtual void enterProg(CalculatorParser::ProgContext * /*ctx*/) override { }
  virtual void exitProg(CalculatorParser::ProgContext * /*ctx*/) override { }

  virtual void enterPrimaryExpr(CalculatorParser::PrimaryExprContext * /*ctx*/) override { }
  virtual void exitPrimaryExpr(CalculatorParser::PrimaryExprContext * /*ctx*/) override { }

  virtual void enterMulDivExpr(CalculatorParser::MulDivExprContext * /*ctx*/) override { }
  virtual void exitMulDivExpr(CalculatorParser::MulDivExprContext * /*ctx*/) override { }

  virtual void enterAddSubExpr(CalculatorParser::AddSubExprContext * /*ctx*/) override { }
  virtual void exitAddSubExpr(CalculatorParser::AddSubExprContext * /*ctx*/) override { }

  virtual void enterExpr(CalculatorParser::ExprContext * /*ctx*/) override { }
  virtual void exitExpr(CalculatorParser::ExprContext * /*ctx*/) override { }

  virtual void enterStatement(CalculatorParser::StatementContext * /*ctx*/) override { }
  virtual void exitStatement(CalculatorParser::StatementContext * /*ctx*/) override { }


  virtual void enterEveryRule(antlr4::ParserRuleContext * /*ctx*/) override { }
  virtual void exitEveryRule(antlr4::ParserRuleContext * /*ctx*/) override { }
  virtual void visitTerminal(antlr4::tree::TerminalNode * /*node*/) override { }
  virtual void visitErrorNode(antlr4::tree::ErrorNode * /*node*/) override { }

};

