
#include "Collections/String/BytesHelper.h"
#include "Collections/String/StringHelper.h"
#include "Function/BuiltinFunction.h"
#include "Generation/Generator.h"
#include "Object/Runtime/PyCode.h"
#include "Object/String/PyString.h"
#include "Python3Lexer.h"
#include "Python3Parser.h"
#include "Tools/Config/Config.h"
#include "Tools/Config/Schema.h"
#ifdef _WIN32
#include <Windows.h>
#endif
#include <filesystem>
#include <fstream>
#include <iostream>
#include <string>
#include "IR/AstHelper.h"
#include "Tools/Tools.h"
#include "antlr4-runtime.h"
namespace fs = std::filesystem;

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
     ),
     OptionConvention(
       "show_ast",
       [](const std::string& value) {
         // value 是 "true" 或 "false"
         return value == "true" || value.empty();
       },
       "true", "是否显示AST树"
     ),
     OptionConvention(
       "show_code",
       [](const std::string& value) {
         // value 是 "true" 或 "false"
         return value == "true" || value.empty();
       },
       "true", "是否显示生成的code object"
     ),
     OptionConvention(
       "show_tokens",
       [](const std::string& value) {
         // value 是 "true" 或 "false"
         return value == "true" || value.empty();
       },
       "true", "是否显示词法分析结果"
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
void InitPyObj() {
  Object::LoadBootstrapClasses();
  Object::LoadRuntimeSupportClasses();
  IR::RegisterAstKlass();
}
}  // namespace tensorslow

// 使用ANTLR解析文件
void ParseAndGenerate(const fs::path& filePath) {
  std::ifstream stream(filePath);
  if (!stream.is_open()) {
    std::cerr << "Failed to open file: " << filePath << std::endl;
    return;
  }
  // std::cout << "正在解析文件: " << filePath << std::endl;

  antlr4::ANTLRInputStream inputStream(stream);
  Python3Lexer lexer(&inputStream);
  antlr4::CommonTokenStream tokens(&lexer);
  Python3Parser parser(&tokens);

  antlr4::tree::ParseTree* tree = parser.file_input();

  //  // 打印词法
  if (tensorslow::Config::Has("show_tokens")) {
    std::cout << "词法分析结果: " << std::endl;
    for (const auto& token : tokens.getTokens()) {
      std::cout << token->toString() << " ";
    }
    std::cout << std::endl;
  }
  if (tensorslow::Config::Has("show_ast")) {
    std::cout << "抽象语法树: " << std::endl;
    std::cout << tree->toStringTree(&parser) << std::endl;
  }

  tensorslow::Generation::Generator visitor(
    tensorslow::Object::CreatePyString(filePath.string())
      ->as<tensorslow::Object::PyString>()
  );

  visitor.visit(tree);

  visitor.Visit();
  visitor.Emit();
  if (tensorslow::Config::Has("show_ir")) {
    std::cout << "中间代码树: " << std::endl;
    std::cout << "```mermaid" << std::endl;
    std::cout << "graph TD" << std::endl;
    visitor.Print();
    std::cout << "```" << std::endl;
  }
  auto code = visitor.Code();
  if (tensorslow::Config::Has("show_code")) {
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
  tensorslow::DefineOption();
  tensorslow::Config::Accept(argc, argv);
  tensorslow::InitPyObj();

  if (tensorslow::Config::Has("file")) {
    ParseAndGenerate(tensorslow::Config::Get("file"));
    return 0;
  }
  if (tensorslow::Config::Has("dir")) {
    auto dir = tensorslow::Config::Get("dir");
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
  auto file = tensorslow::Config::Get("file");
  if (file.empty()) {
    tensorslow::Schema::PrintUsage();
  } else {
    ParseAndGenerate(file);
  }

  return 0;
}