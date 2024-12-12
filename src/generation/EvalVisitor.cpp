#include "bytecode/ByteCode.h"
#include "generation/EvalVisitor.h"

EvalVisitor::EvalVisitor(const std::string& outputFilename)
  : output(outputFilename) {}

antlrcpp::Any EvalVisitor::visitProg(CalculatorParser::ProgContext* ctx) {
  visitChildren(ctx);
  return nullptr;
}

antlrcpp::Any EvalVisitor::visitPrimaryExpr(
  CalculatorParser::PrimaryExprContext* ctx
) {
  if (ctx->INT()) {
    torchlight::bytecode::WriteByteCodeStoreInt(output, ctx->INT()->getText());
    return nullptr;
  }
  if (ctx->FLOAT()) {
    torchlight::bytecode::WriteByteCodeStoreDouble(
      output, ctx->FLOAT()->getText()
    );
    return nullptr;
  }
  if (ctx->expr()) {
    visit(ctx->expr());
    return nullptr;
  }
  return nullptr;
}

antlrcpp::Any EvalVisitor::visitMulDivExpr(
  CalculatorParser::MulDivExprContext* ctx
) {
  if (!ctx->op) {
    visit(ctx->primaryExpr());
    return nullptr;
  }
  visit(ctx->primaryExpr());
  visit(ctx->mulDivExpr());
  if (ctx->op->getText() == "*") {
    torchlight::bytecode::WriteByteCodeOperatorMul(output);
  } else {
    torchlight::bytecode::WriteByteCodeOperatorDiv(output);
  }
  return nullptr;
}

antlrcpp::Any EvalVisitor::visitAddSubExpr(
  CalculatorParser::AddSubExprContext* ctx
) {
  if (!ctx->op) {
    visit(ctx->mulDivExpr());
    return nullptr;
  }
  visit(ctx->mulDivExpr());
  visit(ctx->addSubExpr());
  if (ctx->op->getText() == "+") {
    torchlight::bytecode::WriteByteCodeOperatorAdd(output);
  } else {
    torchlight::bytecode::WriteByteCodeOperatorSub(output);
  }
  return nullptr;
}

antlrcpp::Any EvalVisitor::visitExpr(CalculatorParser::ExprContext* ctx) {
  visit(ctx->addSubExpr());
  return nullptr;
}

antlrcpp::Any EvalVisitor::visitStatement(
  CalculatorParser::StatementContext* ctx
) {
  visit(ctx->expr());
  torchlight::bytecode::WriteByteCodePrint(output);
  return nullptr;
}