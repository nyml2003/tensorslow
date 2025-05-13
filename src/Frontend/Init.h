//
// Created by venty on 2025/5/13.
//

#ifndef TENSORSLOW_FRONTEND_INIT_H
#define TENSORSLOW_FRONTEND_INIT_H
#include "Collections/String/BytesHelper.h"
#include "Generation/Generator.h"
#include "IR/IRHelper.h"
#include "Python3Lexer.h"
#include "Python3Parser.h"
#include "Tools/Config/Config.h"
#include "Tools/Config/Schema.h"
#include "Tools/Logger/ConsoleLogger.h"
#include "Tools/Logger/IntermediateCodeTreeLogger.h"
#include "Tools/Logger/LexicalAnalysisLogger.h"
#include "Tools/Logger/SyntaxAnalysisLogger.h"
#include "antlr4-runtime.h"

#include <filesystem>
#include <fstream>

namespace tensorslow {

void DefineOption() {
  Schema::Accept(
    {OptionConvention(
       "file",
       [](const std::string& value) {
         if (value.empty()) {
           return false;
         }
         // 文件系统里有没有这个文件
         bool file_exists = std::filesystem::exists(value);
         // 后缀名是.py 且文件是一个普通文件
         bool is_py = value.substr(value.find_last_of('.') + 1) == "py";
         bool is_regular = std::filesystem::is_regular_file(value);
         return file_exists && is_py && is_regular;
       },
       "", "单文件模式，指定要解析的文件"
     ),
     OptionConvention(
       "show_ast",
       [](const std::string& value) {
         // value 是 "true" 或 "false"
         return value == "true" || value.empty();
       },
       "true", "是否打印抽象语法树"
     ),
     OptionConvention(
       "show_bc",
       [](const std::string& value) {
         // value 是 "true" 或 "false"
         return value == "true" || value.empty();
       },
       "true", "是否打印字节码"
     ),
     OptionConvention(
       "show_tokens",
       [](const std::string& value) {
         // value 是 "true" 或 "false"
         return value == "true" || value.empty();
       },
       "true", "是否打印词法单元流"
     ),
     OptionConvention(
       "show_ir",
       [](const std::string& value) {
         // value 是 "true" 或 "false"
         return value == "true" || value.empty();
       },
       "true", "是否显示中间代码树"
     )}
  );
}
void InitFrontendClasses() {
  Object::LoadBootstrapClasses();
  Object::LoadRuntimeSupportClasses();
  IR::RegisterIRClasses();
}

void ParseAndGenerate(const std::filesystem::path& filePath) {
  std::ifstream stream(filePath);
  if (!stream.is_open()) {
    std::cerr << "Failed to open file: " << filePath << std::endl;
    return;
  }
  ConsoleLogger::getInstance().log("正在解析文件 ");
  ConsoleLogger::getInstance().log(filePath.string());
  ConsoleLogger::getInstance().log("\n");
  antlr4::ANTLRInputStream inputStream(stream);
  Python3Lexer lexer(&inputStream);
  antlr4::CommonTokenStream tokens(&lexer);
  Python3Parser parser(&tokens);

  antlr4::tree::ParseTree* tree = parser.file_input();

  //  // 打印词法
  if (Config::Has("show_tokens")) {
    for (const auto& token : tokens.getTokens()) {
      LexicalAnalysisLogger::getInstance().log(token->toString());
      LexicalAnalysisLogger::getInstance().log("\n");
    }
    ConsoleLogger::getInstance().log("词法单元流生成完毕\n");
  }
  if (Config::Has("show_ast")) {
    SyntaxAnalysisLogger::getInstance().log(tree->toStringTree(&parser));
    ConsoleLogger::getInstance().log("\n抽象语法树生成完毕\n");
  }

  Generation::Generator visitor(
    Object::CreatePyString(filePath.string())->as<Object::PyString>()
  );

  visitor.visit(tree);
  visitor.Visit();
  visitor.Emit();
  if (Config::Has("show_ir")) {
    visitor.Print();
    IntermediateCodeLogger::getInstance().terminate();
    ConsoleLogger::getInstance().log("中间代码树生成完毕\n");
  }
  auto code = visitor.Code();
  if (Config::Has("show_bc")) {
    Object::PrintCode(code);
  }
  auto data = code->_serialize_()->as<Object::PyBytes>();
  const auto& bytes = data->Value();
  auto writePath = std::filesystem::path(filePath).replace_extension(".pyc");
  Collections::Write(bytes, writePath.string());
}

void InitEnv(int argc, char** argv) {
  DefineOption();
  InitFrontendClasses();
  Config::Accept(argc, argv);
}

}  // namespace tensorslow

#endif  // TENSORSLOW_FRONTEND_INIT_H
