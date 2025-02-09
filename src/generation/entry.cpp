#include "Ast/AssignStmt.h"
#include "Ast/Atom.h"
#include "Ast/Binary.h"
#include "Ast/ExprStmt.h"
#include "Ast/FuncDef.h"
#include "Ast/FunctionCall.h"
#include "Ast/ReturnStmt.h"
#include "Ast/Identifier.h"
#include "Ast/List.h"
#include "Ast/MemberAccess.h"
#include "Ast/Module.h"
#include "ByteCode/PyCode.h"
#include "ByteCode/PyInst.h"
#include "Collections/BytesHelper.h"
#include "Collections/StringHelper.h"
#include "Function/PyFunction.h"
#include "Function/PyMethod.h"
#include "Function/PyNativeFunction.h"
#include "Generation/Generator.h"
#include "Object/PyBoolean.h"
#include "Object/PyDictionary.h"
#include "Object/PyList.h"
#include "Object/PyNone.h"
#include "Object/PyObject.h"
#include "Object/PyString.h"
#include "Object/PyType.h"
#include "Python3Lexer.h"
#include "Python3Parser.h"

#include <antlr4-runtime.h>
#include <filesystem>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>

namespace fs = std::filesystem;
using antlr4::ANTLRInputStream;
using antlr4::CommonTokenStream;
using torchlight::Generation::Generator;
using namespace torchlight;
// 获取目录下的所有文件
std::vector<fs::path> getFilesInDirectory(const fs::path& directoryPath) {
  std::vector<fs::path> fileNames;
  if (fs::exists(directoryPath) && fs::is_directory(directoryPath)) {
    for (const auto& entry : fs::directory_iterator(directoryPath)) {
      if (fs::is_regular_file(entry.status())) {
        fileNames.push_back(entry.path());
      }
    }
  } else {
    std::cerr << "The directory does not exist or is not a directory."
              << std::endl;
  }
  return fileNames;
}

void InitPyObj() {
  Object::StringKlass::Self()->Initialize();
  Object::BooleanKlass::Self()->Initialize();
  Object::NoneKlass::Self()->Initialize();
  Object::ListKlass::Self()->Initialize();
  Object::DictionaryKlass::Self()->Initialize();
  Object::TypeKlass::Self()->Initialize();
  Object::MethodKlass::Self()->Initialize();
  Object::NativeFunctionKlass::Self()->Initialize();
  Object::FunctionKlass::Self()->Initialize();
  Object::InstKlass::Self()->Initialize();
  Object::CodeKlass::Self()->Initialize();
  Ast::ModuleKlass::Self()->Initialize();
  Ast::FuncDefKlass::Self()->Initialize();
  Ast::ExprStmtKlass::Self()->Initialize();
  Ast::AssignStmtKlass::Self()->Initialize();
  Ast::AtomKlass::Self()->Initialize();
  Ast::BinaryKlass::Self()->Initialize();
  Ast::FunctionCallKlass::Self()->Initialize();
  Ast::IdentifierKlass::Self()->Initialize();
  Ast::ListKlass::Self()->Initialize();
  Ast::MemberAccessKlass::Self()->Initialize();
  Ast::ReturnStmtKlass::Self()->Initialize();
}

// 使用ANTLR解析文件
void parseFileWithANTLR(const fs::path& filePath) {
  std::ifstream stream(filePath);
  if (!stream.is_open()) {
    std::cerr << "Failed to open file: " << filePath << std::endl;
    return;
  }

  ANTLRInputStream inputStream(stream);
  Python3Lexer lexer(&inputStream);
  CommonTokenStream tokens(&lexer);
  Python3Parser parser(&tokens);

  antlr4::tree::ParseTree* tree = parser.file_input();

  // std::cout << "AST tree: " << std::endl;
  // std::cout << tree->toStringTree(&parser) << std::endl;

  Generator visitor(Object::CreatePyString(filePath.string()));
  visitor.visit(tree);
  visitor.Visit();
  visitor.Emit();
  auto code = visitor.Code();
  Object::DebugPrint(code->repr());
  Collections::Bytes data =
    std::dynamic_pointer_cast<Object::PyBytes>(code->_serialize_())->Value();
  auto writePath = fs::path(filePath).replace_extension(".pyc");
  Collections::Write(
    data, Collections::CreateStringWithCString(writePath.c_str())
  );
}

int main(int argc, char** argv) {
  std::string integrationTestDir = "/app/test/integration";
  std::string singleFile;

  // 解析命令行参数
  for (int i = 1; i < argc; ++i) {
    std::string arg = argv[i];
    if (arg == "-d" && i + 1 < argc) {
      integrationTestDir = argv[++i];
    } else if (arg == "-f" && i + 1 < argc) {
      singleFile = argv[++i];
    } else {
      std::cerr << "Unknown option or missing argument: " << arg << std::endl;
      return 1;
    }
  }

  InitPyObj();

  if (!singleFile.empty()) {
    // 如果指定了单个文件，则只解析该文件
    fs::path filePath(singleFile);
    if (fs::exists(filePath) && filePath.extension() == ".py") {
      parseFileWithANTLR(filePath);
    } else {
      std::cerr << "Invalid file or not a .py file: " << singleFile
                << std::endl;
      return 1;
    }
  } else {
    // 否则扫描目录下的所有文件
    for (const auto& file : getFilesInDirectory(integrationTestDir)) {
      if (file.extension() == ".py") {
        std::cout << "Parsing file: " << file << std::endl;
        parseFileWithANTLR(file);
      }
    }
  }

  return 0;
}