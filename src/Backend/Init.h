//
// Created by venty on 2025/5/13.
//

#ifndef TENSORSLOW_BACKEND_INIT_H
#define TENSORSLOW_BACKEND_INIT_H
#include "Runtime/BinaryFileParser.h"
#include "Runtime/Interpreter.h"
#include "Tools/Config/Config.h"
#include "Tools/Config/Schema.h"
#include "Tools/Logger/ConsoleLogger.h"
#include "Tools/Logger/ErrorLogger.h"
#include "Tools/Logger/VerboseLogger.h"

#include <filesystem>

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
         bool is_py = value.substr(value.find_last_of('.') + 1) == "pyc";
         bool is_regular = std::filesystem::is_regular_file(value);
         return file_exists && is_py && is_regular;
       },
       "", "单文件模式，指定要解析的文件"
     ),
     OptionConvention(
       "verbose",
       [](const std::string& value) {
         if (value.empty()) {
           return false;
         }
         bool dir_exists = std::filesystem::exists(value);
         bool is_dir = std::filesystem::is_directory(value);
         return dir_exists && is_dir;
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

void BeforeRun(const std::filesystem::path& filename) {
  bool compare_result = Config::Has("compare_result");
  bool show_result = Config::Has("show_result");
  bool verbose = Config::Has("verbose");
  if (compare_result && show_result) {
    throw std::runtime_error("compare_result 和 show_result 不能同时为 true");
  }
  if (compare_result && verbose) {
    throw std::runtime_error("compare_result 和 verbose 不能同时为 true");
  }
  if (show_result && verbose) {
    throw std::runtime_error("show_result 和 verbose 不能同时为 true");
  }
  if (compare_result) {
    ConsoleLogger::getInstance().log("本次测试模式：和预期结果比较\n");
    auto filename_dir = filename.parent_path();
    auto write_filename =
      filename_dir / filename_dir.filename().replace_extension(".out");
    ConsoleLogger::getInstance().log("输出结果到: ");
    ConsoleLogger::getInstance().log(write_filename.string());
    ConsoleLogger::getInstance().log("\n");
    ConsoleLogger::getInstance().setCallback(
      std::make_shared<FileLogStrategy>(write_filename.string())
    );
    return;
  }
  if (show_result) {
    ConsoleLogger::getInstance().log("本次测试模式：直接输出结果\n");
    return;
  }
  if (verbose) {
    auto verbose_dir = Config::Get("verbose");
    auto log_file =
      (std::filesystem::path(verbose_dir) /
       (filename.stem().replace_extension(".log")).filename());
    ConsoleLogger::getInstance().log("本次测试模式：调试模式\n");
    ConsoleLogger::getInstance().log("输出结果到: ");
    ConsoleLogger::getInstance().log(log_file.string());
    ConsoleLogger::getInstance().log("\n");
    ConsoleLogger::getInstance().setCallback(
      std::make_shared<FileLogStrategy>(log_file.string())
    );
    return;
  }
}

void AfterRun(const std::filesystem::path& filename) {
  ConsoleLogger::getInstance().setCallback(std::make_shared<DefaultLogStrategy>(
  ));
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
        ConsoleLogger::getInstance().log("❌ 测试失败\n");
        ConsoleLogger::getInstance().log("预期结果: ");
        ConsoleLogger::getInstance().log(expected_line);
        ConsoleLogger::getInstance().log("\n");
        ConsoleLogger::getInstance().log("实际结果: ");
        ConsoleLogger::getInstance().log(write_line);
        ConsoleLogger::getInstance().log("\n");
        exit(1);
      }
    }
    ConsoleLogger::getInstance().log("✅ 测试通过\n");
    return;
  }
}

void RunTest(const std::filesystem::path& filename) {
  ConsoleLogger::getInstance().log("解析字节码文件: ");
  ConsoleLogger::getInstance().log(filename.string());
  ConsoleLogger::getInstance().log("\n");
  Runtime::BinaryFileParser parser(filename);
  auto code = parser.Parse();

  BeforeRun(filename);
  try {
    Runtime::Interpreter::Run(code);
  } catch (const std::exception& e) {
    VerboseLogger::getInstance().setCallback(
      std::make_shared<ProxyLogStrategy>(&ErrorLogger::getInstance())
    );
    PrintFrame(Runtime::Interpreter::Instance().CurrentFrame());
    ErrorLogger::getInstance().log(e.what());
    throw;
  }

  AfterRun(filename);
}

void InitEnv(int argc, char** argv) {
  DefineOption();
  Config::Accept(argc, argv);
}

}  // namespace tensorslow

#endif  // TENSORSLOW_BACKEND_INIT_H
