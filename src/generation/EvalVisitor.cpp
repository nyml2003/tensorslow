#include <algorithm>
#include <fstream>
#include "bytecode/ByteCode.h"
#include "generation/EvalVisitor.h"
#include "support/Any.h"

EvalVisitor::EvalVisitor() = default;

void EvalVisitor::WriteToFile(const char* filename) {
  std::ofstream file(filename);
  for (auto x = output.rbegin(); x != output.rend(); x++) {
    for (auto y = x->begin(); y != x->end(); y++) {
      uint8_t byte = *y;
      file.put(byte);
    }
  }
}

antlrcpp::Any EvalVisitor::visitAtom(Python3Parser::AtomContext* ctx) {
  if (ctx->NUMBER()) {
    torchlight::bytecode::WriteByteCodeStoreInt(
      output, ctx->NUMBER()->getText()
    );
  } else if (ctx->name()->NAME()->getText() == "print") {
    torchlight::bytecode::WriteByteCodePrint(output);
  }
  return visitChildren(ctx);
}

antlrcpp::Any EvalVisitor::visitExpr(Python3Parser::ExprContext* ctx) {
  if (ctx->ADD(0)) {
    torchlight::bytecode::WriteByteCodeOperatorAdd(output);
  } else if (ctx->MINUS(0)) {
    torchlight::bytecode::WriteByteCodeOperatorSub(output);
  } else if (ctx->STAR()) {
    torchlight::bytecode::WriteByteCodeOperatorMul(output);
  } else if (ctx->DIV()) {
    torchlight::bytecode::WriteByteCodeOperatorDiv(output);
  }
  return visitChildren(ctx);
}

antlrcpp::Any EvalVisitor::visitIf_stmt(Python3Parser::If_stmtContext* ctx) {
  if (ctx->IF()) {
    std::cout << "IF" << std::endl;
  }
  if (ctx->ELSE()) {
    std::cout << "ELSE" << std::endl;
  }

  return nullptr;
}

antlrcpp::Any EvalVisitor::visitComparison(Python3Parser::ComparisonContext* ctx
) {
  antlrcpp::Any op_any = visitComp_op(ctx->comp_op(0));
  std::string op_str = op_any.as<std::string>();
  std::cout << "op: " << op_str << std::endl;
  for (auto i : ctx->expr()) {
    visitExpr(i);
  }
  return nullptr;
}

antlrcpp::Any EvalVisitor::visitComp_op(Python3Parser::Comp_opContext* ctx) {
  if (ctx->LESS_THAN()) {
    return ctx->LESS_THAN()->getText();
  }
  if (ctx->GREATER_THAN()) {
    return ctx->GREATER_THAN()->getText();
  }
  if (ctx->EQUALS()) {
    return ctx->EQUALS()->getText();
  }
  if (ctx->GT_EQ()) {
    return ctx->GT_EQ()->getText();
  }
  if (ctx->LT_EQ()) {
    return ctx->LT_EQ()->getText();
  }
  if (ctx->NOT_EQ_1()) {
    return ctx->NOT_EQ_1()->getText();
  }
  if (ctx->NOT_EQ_2()) {
    return ctx->NOT_EQ_2()->getText();
  }
  if (ctx->IN()) {
    return ctx->IN()->getText();
  }
  if (ctx->NOT()) {
    return ctx->NOT()->getText();
  }
  if (ctx->IS()) {
    return ctx->IS()->getText();
  }
}