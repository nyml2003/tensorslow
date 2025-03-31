
#include "Collections/String/BytesHelper.h"
#include "Collections/String/StringHelper.h"
#include "Function/ObjectHelper.h"
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
#include "Ast/AstHelper.h"
#include "antlr4-runtime.h"
namespace fs = std::filesystem;
using antlr4::ANTLRInputStream;
using antlr4::CommonTokenStream;

using torchlight::ArgsHelper;
using torchlight::Parameter;
using torchlight::Schema;
using torchlight::Generation::Generator;

void DefineOption() {
  Schema schema;
  schema.Add(Parameter(
    "file",
    [](const std::string& value) {
      // 文件系统里有没有这个文件
      bool file_exists = std::filesystem::exists(value);
      // 后缀名是.py 且文件是一个普通文件
      bool is_py = value.substr(value.find_last_of('.') + 1) == "py";
      bool is_regular = std::filesystem::is_regular_file(value);
      return file_exists && is_py && is_regular;
    },
    "D:\\code\\project\\torchlight\\test\\dev\\dev.py",
    "单文件模式，指定要解析的文件"
  ));
  schema.Add(Parameter(
    "dir",
    [](const std::string& value) {
      // 文件系统里有没有这个文件夹
      bool dir_exists = std::filesystem::exists(value);
      // 文件是一个目录
      bool is_dir = std::filesystem::is_directory(value);
      return dir_exists && is_dir;
    },
    "D:\\code\\project\\torchlight\\test\\integration",
    "目录模式，指定要解析的目录, "
    "认为目录下有且仅有包，将每个包下的所有.py文件都解析"
  ));
  schema.Add(Parameter(
    "show_ast",
    [](const std::string& value) {
      // value 是 "true" 或 "false"
      return value == "true" || value == "";
    },
    "true", "是否显示AST树"
  ));
  schema.Add(Parameter(
    "show_code",
    [](const std::string& value) {
      // value 是 "true" 或 "false"
      return value == "true" || value == "";
    },
    "true", "是否显示生成的code object"
  ));
  ArgsHelper::SetSchema(schema);
}
void InitPyObj() {
  torchlight::Object::BasicKlassLoad();
  torchlight::Object::NativeClassLoad();
  torchlight::Ast::RegisterAstKlass();
}

// 使用ANTLR解析文件
void ParseAndGenerate(const fs::path& filePath) {
  std::ifstream stream(filePath);
  if (!stream.is_open()) {
    std::cerr << "Failed to open file: " << filePath << std::endl;
    return;
  }
  std::cout << "正在解析文件: " << filePath << std::endl;

  ANTLRInputStream inputStream(stream);
  Python3Lexer lexer(&inputStream);
  CommonTokenStream tokens(&lexer);
  Python3Parser parser(&tokens);

  antlr4::tree::ParseTree* tree = parser.file_input();

  if (ArgsHelper::Instance().Has("show_ast")) {
    std::cout << "AST tree: " << std::endl;
    std::cout << tree->toStringTree(&parser) << std::endl;
  }

  Generator visitor(torchlight::Object::CreatePyString(filePath.string())
                      ->as<torchlight::Object::PyString>());
  try {
    visitor.visit(tree);
  } catch (const std::bad_any_cast&) {
    std::cerr << "Bad any_cast occurred!" << std::endl;
    return;
  }
  visitor.Visit();
  visitor.Emit();
  auto code = visitor.Code();
  if (ArgsHelper::Instance().Has("show_code")) {
    torchlight::Object::PrintCode(code);
  }
  torchlight::Collections::Bytes data =
    code->_serialize_()->as<torchlight::Object::PyBytes>()->Value();
  auto writePath = fs::path(filePath).replace_extension(".pyc");
  torchlight::Collections::Write(
    data,
    torchlight::Collections::CreateStringWithCString(writePath.string().c_str())
  );
}

int main(int argc, char** argv) {
#ifdef _WIN32
  SetConsoleOutputCP(CP_UTF8);  // 在Windows平台上设置控制台输出为UTF-8编码
#endif
  DefineOption();
  ArgsHelper::Instance().Accept(argc, argv);
  InitPyObj();

  if (ArgsHelper::Instance().Has("file")) {
    ParseAndGenerate(ArgsHelper::Instance().Get("file"));
    return 0;
  }
  if (ArgsHelper::Instance().Has("dir")) {
    auto dir = ArgsHelper::Instance().Get("dir");
    std::vector<fs::path> subdirs;
    for (const auto& entry : fs::directory_iterator(dir)) {
      if (entry.is_directory()) {
        subdirs.push_back(entry.path());
      }
    }
    for (const auto& subdir : subdirs) {
      auto files = torchlight::GetFilesInDirectory(subdir.string(), ".py");
      std::cout << "测试用例:" << subdir.filename().string() << std::endl;
      for (const auto& file : files) {
        ParseAndGenerate(file);
      }
    }
    return 0;
  }
  auto file = ArgsHelper::Instance().Get("file");
  ParseAndGenerate(file);

  return 0;
}