
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
#include <fstream>
#include <iostream>
#include <string>
#include "IR/AstHelper.h"
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
  ));
  schema.Add(Parameter(
    "dir",
    [](const std::string& value) {
      if (value.empty()) {
        return false;
      }
      // 文件系统里有没有这个文件夹
      bool dir_exists = std::filesystem::exists(value);
      // 文件是一个目录
      bool is_dir = std::filesystem::is_directory(value);
      return dir_exists && is_dir;
    },
    "",
    "目录模式，指定要解析的目录, "
    "认为目录下有且仅有包，将每个包下的所有.py文件都解析"
  ));
  schema.Add(Parameter(
    "show_ast",
    [](const std::string& value) {
      // value 是 "true" 或 "false"
      return value == "true" || value.empty();
    },
    "true", "是否显示AST树"
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
  ArgsHelper::SetSchema(schema);
}
void InitPyObj() {
  tensorslow::Object::LoadBootstrapClasses();
  tensorslow::Object::LoadRuntimeSupportClasses();
  tensorslow::IR::RegisterAstKlass();
}

// 使用ANTLR解析文件
void ParseAndGenerate(const fs::path& filePath) {
  std::ifstream stream(filePath);
  if (!stream.is_open()) {
    std::cerr << "Failed to open file: " << filePath << std::endl;
    return;
  }
  // std::cout << "正在解析文件: " << filePath << std::endl;

  ANTLRInputStream inputStream(stream);
  Python3Lexer lexer(&inputStream);
  CommonTokenStream tokens(&lexer);
  Python3Parser parser(&tokens);

  antlr4::tree::ParseTree* tree = parser.file_input();

  //  // 打印词法
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

  Generator visitor(tensorslow::Object::CreatePyString(filePath.string())
                      ->as<tensorslow::Object::PyString>());

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
  auto data = code->_serialize_()->as<tensorslow::Object::PyBytes>();
  const auto& bytes = data->Value();
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
  ArgsHelper::Instance().Accept(argc, argv);
  InitPyObj();

  if (ArgsHelper::Has("file")) {
    ParseAndGenerate(ArgsHelper::Get("file"));
    return 0;
  }
  if (ArgsHelper::Has("dir")) {
    auto dir = ArgsHelper::Get("dir");
    std::vector<fs::path> subdirs;
    for (const auto& entry : fs::directory_iterator(dir)) {
      if (entry.is_directory()) {
        subdirs.push_back(entry.path());
      }
    }
    for (const auto& subdir : subdirs) {
      auto files = tensorslow::GetFilesInDirectory(subdir.string(), ".py");
      std::cout << "测试用例:" << subdir.filename().string() << std::endl;
      for (const auto& file : files) {
        ParseAndGenerate(file);
      }
    }
    return 0;
  }
  auto file = ArgsHelper::Get("file");
  if (file.empty()) {
    ArgsHelper::PrintUsage();
  } else {
    ParseAndGenerate(file);
  }

  return 0;
}