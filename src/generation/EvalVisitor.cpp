#include <algorithm>
#include <fstream>
#include "bytecode/ByteCode.h"
#include "generation/EvalVisitor.h"

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