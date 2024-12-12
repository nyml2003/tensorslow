
// Generated from /app/grammar/Calculator.g4 by ANTLR 4.9.2

#pragma once


#include "antlr4-runtime.h"
#include "CalculatorParser.h"



/**
 * This class defines an abstract visitor for a parse tree
 * produced by CalculatorParser.
 */
class  CalculatorVisitor : public antlr4::tree::AbstractParseTreeVisitor {
public:

  /**
   * Visit parse trees produced by CalculatorParser.
   */
    virtual antlrcpp::Any visitProg(CalculatorParser::ProgContext *context) = 0;

    virtual antlrcpp::Any visitPrimaryExpr(CalculatorParser::PrimaryExprContext *context) = 0;

    virtual antlrcpp::Any visitMulDivExpr(CalculatorParser::MulDivExprContext *context) = 0;

    virtual antlrcpp::Any visitAddSubExpr(CalculatorParser::AddSubExprContext *context) = 0;

    virtual antlrcpp::Any visitExpr(CalculatorParser::ExprContext *context) = 0;

    virtual antlrcpp::Any visitStatement(CalculatorParser::StatementContext *context) = 0;


};

