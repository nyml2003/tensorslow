
#include "Collections/String/BytesHelper.h"
#include "Collections/String/StringHelper.h"
#include "Function/BuiltinFunction.h"
#include "Generation/Generator.h"
#include "Object/Runtime/PyCode.h"
#include "Object/String/PyString.h"
#include "Python3Lexer.h"
#include "Python3Parser.h"
#include "Tools/Tools.h"
#ifdef _WIN32
#include <Windows.h>
#endif
#include <filesystem>
#include <iostream>
#include <string>
#include "IR/AstHelper.h"
#include "Runtime/BinaryFileParser.h"
#include "Runtime/Interpreter.h"
#include "antlr4-runtime.h"
namespace fs = std::filesystem;
using antlr4::ANTLRInputStream;
using antlr4::CommonTokenStream;

using tensorslow::Config;
using tensorslow::OptionConvention;
using tensorslow::Schema;
using tensorslow::Generation::Generator;

void DefineOption() {
  Schema schema;
  schema.Add(OptionConvention(
    "file",
    [](const std::string& value) {
      if (value.empty() && !std::filesystem::exists(value)) {
        return false;
      }
      // 后缀名
      std::string extension = fs::path(value).extension().string();
      bool is_py = extension == ".py" || extension == ".pyc";
      bool is_regular = std::filesystem::is_regular_file(value);
      return is_py && is_regular;
    },
    "", "单文件模式，指定要解析的文件"
  ));
  schema.Add(OptionConvention(
    "show_ast",
    [](const std::string& value) {
      // value 是 "true" 或 "false"
      return value == "true" || value.empty();
    },
    "true", "是否显示抽象语法树"
  ));
  schema.Add(OptionConvention(
    "show_code",
    [](const std::string& value) {
      // value 是 "true" 或 "false"
      return value == "true" || value.empty();
    },
    "true", "是否显示生成的code object"
  ));
  schema.Add(OptionConvention(
    "show_tokens",
    [](const std::string& value) {
      // value 是 "true" 或 "false"
      return value == "true" || value.empty();
    },
    "true", "是否显示词法分析结果"
  ));
  schema.Add(OptionConvention(
    "show_ir",
    [](const std::string& value) {
      // value 是 "true" 或 "false"
      return value == "true" || value.empty();
    },
    "true", "是否显示中间代码树"
  ));
  schema.Add(OptionConvention(
    "show_result",
    [](const std::string& value) {
      // value 是 "true" 或 "false"
      return value == "true" || value.empty();
    },
    "true", "是否直接输出结果"
  ));
  schema.Add(OptionConvention(
    "compile",
    [](const std::string& value) { return value == "true" || value.empty(); },
    "true", "是否编译成字节码"
  ));
  schema.Add(OptionConvention(
    "interpret",
    [](const std::string& value) { return value == "true" || value.empty(); },
    "true", "是否直接解释执行源代码"
  ));
  schema.Add(OptionConvention(
    "interpret_bytecode",
    [](const std::string& value) { return value == "true" || value.empty(); },
    "true", "是否解释执行字节码"
  ));
  schema.Add(OptionConvention(
    "source", [](const std::string& value) { return !value.empty(); }, "",
    "字符串模式，指定要解析的源代码字符串"
  ));
  Config::SetSchema(schema);
}

void DefaultExit(const std::string& error) {
  std::cerr << error << std::endl;
  Config::PrintUsage();
  exit(1);
}
void OptionEnhance() {
  // 检查执行方式唯一性
  int mode_count = Config::Has("interpret") + Config::Has("compile") +
                   Config::Has("interpret_bytecode");
  if (mode_count != 1) {
    DefaultExit(
      "错误: 必须指定且只能指定一个执行方式：--interpret、--compile 或 "
      "--interpret_bytecode"
    );
  }

  // 检查来源唯一性
  if (!(Config::Has("file") ^ Config::Has("source"))) {
    DefaultExit("错误: 必须指定且只能指定一个来源：--file 或 --source");
  }

  // 检查 source 与 interpret_bytecode 互斥
  if (Config::Has("source") && Config::Has("interpret_bytecode")) {
    DefaultExit("错误: 当使用 --source 时，不能启用 --interpret_bytecode 模式");
  }

  // 检查 source 与 compile 的依赖
  if (Config::Has("source") && !Config::Has("interpret")) {
    DefaultExit("错误: source 模式需要启用 --interpret 模式");
  }

  // 处理 file 校验
  if (Config::Has("file")) {
    std::string file_path = Config::Get("file");
    if (file_path.empty()) {
      DefaultExit("错误: --file 参数值为空");
    }
    std::string ext = std::filesystem::path(file_path).extension().string();
    std::transform(
      ext.begin(), ext.end(), ext.begin(), ::tolower
    );  // 处理大小写

    std::string mode;
    if (Config::Has("interpret"))
      mode = "interpret";
    else if (Config::Has("interpret_bytecode"))
      mode = "interpret_bytecode";
    else
      mode = "compile";

    if ((mode == "interpret" && ext != ".py") || (mode == "interpret_bytecode" && ext != ".pyc") || (mode == "compile" && ext != ".py")) {
      DefaultExit(
        "错误: " + mode +
        " 模式要求文件扩展名为 .py（interpret/compile）或 "
        ".pyc（interpret_bytecode），但当前文件为: " +
        ext
      );
    }
  }
}
void InitPyObj() {
  tensorslow::Object::LoadBootstrapClasses();
  tensorslow::Object::LoadRuntimeSupportClasses();
  tensorslow::IR::RegisterAstKlass();
}

// 使用ANTLR解析文件
tensorslow::Object::PyCodePtr Compile(ANTLRInputStream* inputStream) {
  Python3Lexer lexer(inputStream);
  CommonTokenStream tokens(&lexer);
  Python3Parser parser(&tokens);
  antlr4::tree::ParseTree* tree = parser.file_input();
  // 打印词法
  if (Config::Has("show_tokens")) {
    std::cout << "词法分析结果: " << std::endl;
    for (const auto& token : tokens.getTokens()) {
      std::cout << token->toString() << " ";
    }
    std::cout << std::endl;
  }
  if (Config::Has("show_ast")) {
    std::cout << "抽象语法树: " << std::endl;
    std::cout << tree->toStringTree(&parser) << std::endl;
  }
  std::string moduleName = Config::Has("file")     ? Config::Get("file")
                           : Config::Has("source") ? "temporaryModule"
                                                   : "unreached";
  Generator visitor(tensorslow::Object::CreatePyString(moduleName));
  visitor.visit(tree);
  visitor.Visit();
  visitor.Emit();
  if (Config::Has("show_ir")) {
    std::cout << "中间代码树: " << std::endl;
    std::cout << "```mermaid" << std::endl;
    std::cout << "graph TD" << std::endl;
    visitor.Print();
    std::cout << "```" << std::endl;
  }
  auto code = visitor.Code();
  if (Config::Has("show_code")) {
    tensorslow::Object::PrintCode(code);
  }
  return code;
}

ANTLRInputStream* CreateANTLRInputStream() {
  if (Config::Has("file")) {
    std::cout << "文件名: " << Config::Get("file") << std::endl;
    std::ifstream file(Config::Get("file"));
    return new ANTLRInputStream(file);
  }
  if (Config::Has("source")) {
    return new ANTLRInputStream(Config::Get("source"));
  }
  throw std::runtime_error("未指定文件或源码");
}

void DestroyANTLRInputStream(ANTLRInputStream* input) {
  delete input;
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
  auto writePath = fs::path(filePath).replace_extension(".pyc");
  tensorslow::Collections::Write(
    bytes,
    tensorslow::Collections::CreateStringWithCString(writePath.string().c_str())
  );
}

int main(int argc, char** argv) {
#ifdef _WIN32
  SetConsoleOutputCP(CP_UTF8);  // 在Windows平台上设置控制台输出为UTF-8编码
#endif
  DefineOption();
  Config::Instance().Accept(argc, argv);
  OptionEnhance();

  InitPyObj();

  if (Config::Has("compile")) {
    HandleCompile();
  } else if (Config::Has("interpret")) {
    HandleInterpret();
  } else if (Config::Has("interpret_bytecode")) {
    HandleInterpretBytecode();
  }
  return 0;
}