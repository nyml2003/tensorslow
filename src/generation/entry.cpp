
#include "Python3Lexer.h"
#include "Python3Parser.h"
#include "Python3ParserBaseVisitor.h"
#include "generation/EvalVisitor.h"

#include <antlr4-runtime.h>

using antlr4::ANTLRInputStream;
using antlr4::CommonTokenStream;

int main(int argc, char** argv) {
  // 创建输入流
  std::string input;
  if (argc > 1) {
    input = argv[1];
  } else {
    input = "/app/test/a.py";
  }

  // 创建字符流
  std::ifstream stream(input);
  ANTLRInputStream inputStream(stream);

  Python3Lexer lexer(&inputStream);

  CommonTokenStream tokens(&lexer);

  Python3Parser parser(&tokens);

  antlr4::tree::ParseTree* tree = parser.file_input();

  // 输出 AST
  std::cout << tree->toStringTree(&parser) << std::endl;

  // // 创建 Lexer
  // CalculatorLexer lexer(&inputStream);
  // CommonTokenStream tokens(&lexer);

  // // 创建 Parser
  // CalculatorParser parser(&tokens);

  // // 解析表达式
  // antlr4::tree::ParseTree* tree = parser.prog();

  EvalVisitor visitor;
  visitor.visit(tree);

  visitor.WriteToFile("/app/test/a.pyc");

  return 0;
}