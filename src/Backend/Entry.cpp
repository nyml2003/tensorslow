#include "Runtime/BinaryFileParser.h"
#include "Runtime/Interpreter.h"
#include "Tools/Config/Config.h"
#include "Tools/Config/Schema.h"
#include "Tools/Logger/ConsoleLogger.h"
#include "Tools/Logger/ErrorLogger.h"
#include "Tools/Tools.h"

#include <filesystem>
#include <fstream>
#include <iostream>

#ifdef _WIN32
#include <Windows.h>
#endif
using namespace tensorslow;

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
         bool is_py = value.substr(value.find_last_of('.') + 1) == "pyc";
         bool is_regular = std::filesystem::is_regular_file(value);
         return file_exists && is_py && is_regular;
       },
       "", "单文件模式，指定要解析的文件"
     ),
     OptionConvention(
       "debug",
       [](const std::string& value) {
         return value == "true" || value.empty();
       },
       "../log", "开启调试模式，并将结果输出到指定目录下"
     ),
     OptionConvention(
       "compare_result",
       [](const std::string& value) {
         return value == "true" || value.empty();
       },
       "true", "是否和预期结果比较"
     ),
     OptionConvention(
       "show_result",
       [](const std::string& value) {
         // value 是 "true" 或 "false"
         return value == "true" || value.empty();
       },
       "true", "是否直接输出结果"
     )}
  );
}

void HandleResultBegin(const fs::path& filename) {
  bool compare_result = Config::Has("compare_result");
  bool show_result = Config::Has("show_result");
  bool debug = Config::Has("debug");
  if (compare_result && show_result) {
    throw std::runtime_error("compare_result 和 show_result 不能同时为 true");
  }
  if (compare_result && debug) {
    throw std::runtime_error("compare_result 和 debug 不能同时为 true");
  }
  if (show_result && debug) {
    throw std::runtime_error("show_result 和 debug 不能同时为 true");
  }
  if (compare_result) {
    tensorslow::ConsoleLogger::getInstance().log(
      "本次测试模式：和预期结果比较\n"
    );
    auto filename_dir = filename.parent_path();
    auto write_filename =
      filename_dir / filename_dir.filename().replace_extension(".out");
    tensorslow::ConsoleLogger::getInstance().log("输出结果到: ");
    tensorslow::ConsoleLogger::getInstance().log(write_filename.string());
    tensorslow::ConsoleLogger::getInstance().log("\n");
    tensorslow::ConsoleLogger::getInstance().setCallback(
      std::make_shared<FileLogStrategy>(write_filename.string())
    );
    return;
  }
  if (show_result) {
    tensorslow::ConsoleLogger::getInstance().log("本次测试模式：直接输出结果\n"
    );
    return;
  }
  if (debug) {
    auto debug_dir = Config::Get("debug");
    auto log_file =
      (fs::path(debug_dir) /
       (filename.stem().replace_extension(".log")).filename());
    tensorslow::ConsoleLogger::getInstance().log("本次测试模式：调试模式\n");
    tensorslow::ConsoleLogger::getInstance().log("输出结果到: ");
    tensorslow::ConsoleLogger::getInstance().log(log_file.string());
    tensorslow::ConsoleLogger::getInstance().log("\n");
    tensorslow::ConsoleLogger::getInstance().setCallback(
      std::make_shared<FileLogStrategy>(log_file.string())
    );
    return;
  }
}

void HandleResultEnd(const fs::path& filename) {
  tensorslow::ConsoleLogger::getInstance().setCallback(
    std::make_shared<DefaultLogStrategy>()
  );
  bool compare_result = Config::Has("compare_result");
  if (compare_result) {
    auto filename_dir = filename.parent_path();
    auto write_filename =
      filename_dir / filename_dir.filename().replace_extension(".out");
    auto expected_filename =
      filename_dir / filename_dir.filename().replace_extension(".expected");
    // 比较结果
    std::ifstream write_stream(write_filename);
    std::ifstream expected_stream(expected_filename);
    std::string write_line;
    std::string expected_line;
    while (std::getline(write_stream, write_line)) {
      std::getline(expected_stream, expected_line);
      if (write_line != expected_line) {
        tensorslow::ConsoleLogger::getInstance().log("❌ 测试失败\n");
        tensorslow::ConsoleLogger::getInstance().log("预期结果: ");
        tensorslow::ConsoleLogger::getInstance().log(expected_line);
        tensorslow::ConsoleLogger::getInstance().log("\n");
        tensorslow::ConsoleLogger::getInstance().log("实际结果: ");
        tensorslow::ConsoleLogger::getInstance().log(write_line);
        tensorslow::ConsoleLogger::getInstance().log("\n");
        exit(1);
      }
    }
    tensorslow::ConsoleLogger::getInstance().log("✅ 测试通过\n");
    return;
  }
}
void RunTest(const fs::path& filename) {
  tensorslow::ConsoleLogger::getInstance().log("解析字节码文件: ");
  tensorslow::ConsoleLogger::getInstance().log(filename.string());
  tensorslow::ConsoleLogger::getInstance().log("\n");
  Runtime::BinaryFileParser parser(filename);
  auto code = parser.Parse();

  HandleResultBegin(filename);
  try {
    Runtime::Interpreter::Run(code);
  } catch (const std::exception& e) {
    PrintFrame(Runtime::Interpreter::Instance().CurrentFrame());
    tensorslow::ErrorLogger::getInstance().log(e.what());
    throw;
  }

  HandleResultEnd(filename);
}

int main(int argc, char** argv) {
#ifdef _WIN32
  SetConsoleOutputCP(CP_UTF8);  // 在Windows平台上设置控制台输出为UTF-8编码
#endif
  DefineOption();
  Config::Accept(argc, argv);
  auto file = Config::Get("file");
  if (!file.empty()) {
    RunTest(file);
  } else {
    Schema::PrintUsage();
  }
  return 0;
}