//
// Created by venty on 2025/5/13.
//

#ifndef TENSORSLOW_ENGINE_INIT_H
#define TENSORSLOW_ENGINE_INIT_H
#include "Collections/String/BytesHelper.h"
#include "Generation/Generator.h"
#include "IR/IRHelper.h"
#include "Python3Lexer.h"
#include "Python3Parser.h"
#include "Runtime/BinaryFileParser.h"
#include "Runtime/Interpreter.h"
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
         if (value.empty())
           return false;
         bool file_exists = std::filesystem::exists(value);
         std::string extension =
           std::filesystem::path(value).extension().string();
         bool is_py = extension == ".py" || extension == ".pyc";
         bool is_regular = std::filesystem::is_regular_file(value);
         return file_exists && is_py && is_regular;
       },
       "", "单文件模式，指定要解析的文件"
     ),
     OptionConvention(
       "show_ast",
       [](const std::string& value) {
         return value == "true" || value.empty();
       },
       "true", "是否显示抽象语法树"
     ),
     OptionConvention(
       "show_bc",
       [](const std::string& value) {
         return value == "true" || value.empty();
       },
       "true", "是否显示生成的code object"
     ),
     OptionConvention(
       "show_tokens",
       [](const std::string& value) {
         return value == "true" || value.empty();
       },
       "true", "是否显示词法分析结果"
     ),
     OptionConvention(
       "show_ir",
       [](const std::string& value) {
         return value == "true" || value.empty();
       },
       "true", "是否显示中间代码树"
     ),
     OptionConvention(
       "show_result",
       [](const std::string& value) {
         return value == "true" || value.empty();
       },
       "true", "是否直接输出结果"
     ),
     OptionConvention(
       "compile",
       [](const std::string& value) {
         return value == "true" || value.empty();
       },
       "true", "是否编译成字节码"
     ),
     OptionConvention(
       "interpret",
       [](const std::string& value) {
         return value == "true" || value.empty();
       },
       "true", "是否直接解释执行源代码"
     ),
     OptionConvention(
       "interpret_bytecode",
       [](const std::string& value) {
         return value == "true" || value.empty();
       },
       "true", "是否解释执行字节码"
     ),
     OptionConvention(
       "source", [](const std::string& value) { return !value.empty(); }, "",
       "字符串模式，指定要解析的源代码字符串"
     )}
  );
}

void ValidateOptions() {
  // 检查执行方式唯一性
  int mode_count = Config::Has("interpret") + Config::Has("compile") +
                   Config::Has("interpret_bytecode");
  if (mode_count != 1) {
    ConsoleLogger::getInstance().log(
      "错误: 必须指定且只能指定一个执行方式：--interpret、--compile 或 "
      "--interpret_bytecode\n"
    );
    Schema::PrintUsage();
    exit(1);
  }

  // 检查来源唯一性
  if (!(Config::Has("file") ^ Config::Has("source"))) {
    ConsoleLogger::getInstance().log(
      "错误: 必须指定且只能指定一个来源：--file 或 --source\n"
    );
    Schema::PrintUsage();
    exit(1);
  }

  // 检查 source 与 interpret_bytecode 互斥
  if (Config::Has("source") && Config::Has("interpret_bytecode")) {
    ConsoleLogger::getInstance().log(
      "错误: 当使用 --source 时，不能启用 --interpret_bytecode 模式\n"
    );
    Schema::PrintUsage();
    exit(1);
  }

  // 检查 source 与 compile 的依赖
  if (Config::Has("source") && !Config::Has("interpret")) {
    ConsoleLogger::getInstance().log(
      "错误: source 模式需要启用 --interpret 模式\n"
    );
    Schema::PrintUsage();
    exit(1);
  }

  // 处理文件扩展名校验
  if (Config::Has("file")) {
    std::string file_path = Config::Get("file");
    std::string ext = std::filesystem::path(file_path).extension().string();
    std::transform(ext.begin(), ext.end(), ext.begin(), ::tolower);

    std::string mode;
    if (Config::Has("interpret"))
      mode = "interpret";
    else if (Config::Has("interpret_bytecode"))
      mode = "interpret_bytecode";
    else
      mode = "compile";

    if ((mode == "interpret" && ext != ".py") || (mode == "interpret_bytecode" && ext != ".pyc") || (mode == "compile" && ext != ".py")) {
      ConsoleLogger::getInstance().log(
        "错误: " + mode +
        " 模式要求文件扩展名为 .py（interpret/compile）或 "
        ".pyc（interpret_bytecode），但当前文件为: " +
        ext + "\n"
      );
      Schema::PrintUsage();
      exit(1);
    }
  }
}

void InitRuntimeSupport() {
  Object::LoadBootstrapClasses();
  Object::LoadRuntimeSupportClasses();
  IR::RegisterIRClasses();
}

antlr4::ANTLRInputStream* CreateANTLRInputStream() {
  if (Config::Has("file")) {
    ConsoleLogger::getInstance().log("文件名: " + Config::Get("file") + "\n");
    std::ifstream file(Config::Get("file"));
    return new antlr4::ANTLRInputStream(file);
  }
  if (Config::Has("source")) {
    return new antlr4::ANTLRInputStream(Config::Get("source"));
  }
  throw std::runtime_error("未指定文件或源码");
}

void DestroyANTLRInputStream(antlr4::ANTLRInputStream* input) {
  delete input;
}

Object::PyCodePtr Compile(antlr4::ANTLRInputStream* inputStream) {
  Python3Lexer lexer(inputStream);
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
  std::string moduleName = Config::Has("file")     ? Config::Get("file")
                           : Config::Has("source") ? "temporaryModule"
                                                   : "unreached";
  Generation::Generator visitor(tensorslow::Object::CreatePyString(moduleName));

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
  return code;
}

void Interpret(const tensorslow::Object::PyCodePtr& code) {
  try {
    tensorslow::Runtime::Interpreter::Run(code);
  } catch (const std::exception& e) {
    PrintFrame(tensorslow::Runtime::Interpreter::Instance().CurrentFrame());
    std::cerr << "Caught exception: " << e.what() << std::endl;
    throw;
  }
}

void HandleInterpret() {
  auto inputStream = CreateANTLRInputStream();
  auto code = Compile(inputStream);
  DestroyANTLRInputStream(inputStream);
  Interpret(code);
}

void HandleInterpretBytecode() {
  auto filename = Config::Get("file");
  tensorslow::Runtime::BinaryFileParser parser(filename);
  auto code = parser.Parse();
  Interpret(code);
}

void HandleCompile() {
  auto inputStream = CreateANTLRInputStream();
  auto code = Compile(inputStream);
  DestroyANTLRInputStream(inputStream);

  auto data = code->_serialize_()->as<tensorslow::Object::PyBytes>();
  const auto& bytes = data->Value();
  auto filePath = Config::Get("file");
  auto writePath = std::filesystem::path(filePath).replace_extension(".pyc");
  tensorslow::Collections::Write(bytes, writePath.string());
}

void InitEnv(int argc, char** argv) {
  DefineOption();
  InitRuntimeSupport();
  Config::Accept(argc, argv);
  ValidateOptions();
}

}  // namespace tensorslow

#endif  // TENSORSLOW_ENGINE_INIT_H
