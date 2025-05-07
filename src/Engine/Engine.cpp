
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

using tensorslow::ArgsHelper;
using tensorslow::Parameter;
using tensorslow::Schema;
using tensorslow::Generation::Generator;

void DefineOption() {
  Schema schema;
  schema.Add(Parameter(
    "file",
    [](const std::string& value) {
      if (value.empty() && !std::filesystem::exists(value)) {
        return false;
      }
      // 后缀名
      std::string extension = fs::path(value).extension().string();
      bool is_py = extension == ".py" || extension == ".pyc";
      bool is_regular = std::filesystem::is_regular_file(value);
      return  is_py && is_regular;
    },
    "", "单文件模式，指定要解析的文件"
  ));
  schema.Add(Parameter(
    "show_ast",
    [](const std::string& value) {
      // value 是 "true" 或 "false"
      return value == "true" || value.empty();
    },
    "true", "是否显示抽象语法树"
  ));
  schema.Add(Parameter(
    "show_code",
    [](const std::string& value) {
      // value 是 "true" 或 "false"
      return value == "true" || value.empty();
    },
    "true", "是否显示生成的code object"
  ));
  schema.Add(Parameter(
    "show_tokens",
    [](const std::string& value) {
      // value 是 "true" 或 "false"
      return value == "true" || value.empty();
    },
    "true", "是否显示词法分析结果"
  ));
  schema.Add(Parameter(
    "show_ir",
    [](const std::string& value) {
      // value 是 "true" 或 "false"
      return value == "true" || value.empty();
    },
    "true", "是否显示中间代码树"
  ));
  schema.Add(Parameter(
    "show_result",
    [](const std::string& value) {
      // value 是 "true" 或 "false"
      return value == "true" || value.empty();
    },
    "true", "是否直接输出结果"
  ));
  schema.Add(Parameter(
    "compile",
    [](const std::string& value) { return value == "true" || value.empty(); },
    "true", "是否编译成字节码"
  ));
  schema.Add(Parameter(
    "interpret",
    [](const std::string& value) { return value == "true" || value.empty(); },
    "true", "是否直接解释执行源代码"
  ));
  schema.Add(Parameter(
    "interpret_bytecode",
    [](const std::string& value) { return value == "true" || value.empty(); },
    "true", "是否解释执行字节码"
  ));
  schema.Add(Parameter(
    "source",
    [](const std::string& value) {
      return !value.empty();
    },
    "", "字符串模式，指定要解析的源代码字符串"
  ));
  ArgsHelper::SetSchema(schema);
}

void DefaultExit(const std::string& error) {
  std::cerr << error << std::endl;
  ArgsHelper::PrintUsage();
  exit(1);
}

void OptionEnhance() {
  // 至少选一个执行方式：interpret / compile / interpret_bytecode
  if ((!ArgsHelper::Has("interpret") && !ArgsHelper::Has("compile") && ArgsHelper::Has("interpret_bytecode"))
      ||
      (!ArgsHelper::Has("interpret") && ArgsHelper::Has("compile") && !ArgsHelper::Has("interpret_bytecode"))
      ||
      (ArgsHelper::Has("interpret") && !ArgsHelper::Has("compile") && !ArgsHelper::Has("interpret_bytecode"))
    )
  {
    DefaultExit("错误: 至少需要启用 --interpret、--compile 或 --interpret_bytecode 中的一个");
  }

  // 检查是否指定了 file 或 source
  if (!ArgsHelper::Has("file") && ArgsHelper::Has("source")
      || ArgsHelper::Has("file") && !ArgsHelper::Has("source")
      ) {
    DefaultExit("错误: 需要指定要执行的文件或源代码字符串");
  }

  // 检查是否同时指定了 file 和 source
  if (ArgsHelper::Has("file") && ArgsHelper::Has("source")) {
    DefaultExit("错误: 不能同时指定 --file 和 --source");
  }

  // 检查 source 与 interpret_bytecode 互斥
  if (ArgsHelper::Has("source") && ArgsHelper::Has("interpret_bytecode")) {
    DefaultExit("错误: 当使用 --source 时，不能启用 --interpret_bytecode 模式");
  }

  // 处理 file 相关的校验
  if (ArgsHelper::Has("file")) {
    std::string file_path = ArgsHelper::Get("file");
    std::string ext = std::filesystem::path(file_path).extension().string();

    if (ext != ".py" && ArgsHelper::Has("interpret")) {
      DefaultExit("错误: interpret 模式只支持 .py 文件");
    }

    if (ext != ".pyc" && ArgsHelper::Has("interpret_bytecode")) {
      DefaultExit("错误: interpret_bytecode 模式只支持 .pyc 文件");
    }

    if (ext != ".py" && ArgsHelper::Has("compile")) {
      DefaultExit("错误: compile 模式只支持 .py 文件");
    }
  }
  if (ArgsHelper::Has("source")) {
    if (!ArgsHelper::Has("compile")) {
      DefaultExit("错误: source 模式需要启用 compile 模式");
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
  if (ArgsHelper::Has("show_tokens")) {
    std::cout << "词法分析结果: " << std::endl;
    for (const auto& token : tokens.getTokens()) {
      std::cout << token->toString() << " ";
    }
    std::cout << std::endl;
  }
  if (ArgsHelper::Has("show_ast")) {
    std::cout << "抽象语法树: " << std::endl;
    std::cout << tree->toStringTree(&parser) << std::endl;
  }
  std::string moduleName = ArgsHelper::Has("file") ? ArgsHelper::Get("file") : ArgsHelper::Has("source") ? "temporaryModule" : "unreached";
  Generator visitor(tensorslow::Object::CreatePyString(moduleName));
  visitor.visit(tree);
  visitor.Visit();
  visitor.Emit();
  if (ArgsHelper::Has("show_ir")) {
    std::cout << "中间代码树: " << std::endl;
    std::cout << "```mermaid" << std::endl;
    std::cout << "graph TD" << std::endl;
    visitor.Print();
    std::cout << "```" << std::endl;
  }
  auto code = visitor.Code();
  if (ArgsHelper::Has("show_code")) {
    tensorslow::Object::PrintCode(code);
  }
  return code;
}

ANTLRInputStream* CreateANTLRInputStream(){
  if (ArgsHelper::Has("file")) {
    std::cout << "文件名: " << ArgsHelper::Get("file") << std::endl;
    std::ifstream file(ArgsHelper::Get("file"));
    return new ANTLRInputStream(file);
  }
  if (ArgsHelper::Has("source")) {
    return new ANTLRInputStream(ArgsHelper::Get("source"));
  }
  throw std::runtime_error("未指定文件或源码");
}

void DestoryANTLRInputStream(ANTLRInputStream* input){
  delete input;
}


void Interpret(const tensorslow::Object::PyCodePtr& code){
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
  DestoryANTLRInputStream(inputStream);
  Interpret(code);
}

void HandleInterpretBytecode() {
  auto filename = ArgsHelper::Get("file");
  tensorslow::Runtime::BinaryFileParser parser(filename);
  auto code = parser.Parse();
  Interpret(code);
}

void HandleCompile() {
  auto inputStream = CreateANTLRInputStream();
  auto code = Compile(inputStream);
  DestoryANTLRInputStream(inputStream);

  auto data = code->_serialize_()->as<tensorslow::Object::PyBytes>();
  const auto& bytes = data->Value();
  auto filePath = ArgsHelper::Get("file");
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
  OptionEnhance();
  ArgsHelper::Instance().Accept(argc, argv);
  InitPyObj();

  if (ArgsHelper::Has("compile")) {
    HandleCompile();
  } else if (ArgsHelper::Has("interpret")) {
    HandleInterpret();
  } else if (ArgsHelper::Has("interpret_bytecode")){
    HandleInterpretBytecode();
  }
  return 0;
}