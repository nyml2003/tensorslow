//
// Created by venty on 2025/5/13.
//

#ifndef TENSORSLOW_BACKEND_INIT_H
#define TENSORSLOW_BACKEND_INIT_H
#include "Runtime/BinaryFileParser.h"
#include "Runtime/VirtualMachine.h"
#include "Tools/Config/Config.h"
#include "Tools/Config/Schema.h"

#include <filesystem>

namespace tensorslow {
inline void DefineOption() {
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

inline void BeforeRun(const std::filesystem::path& filename) {
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
    ConsoleTerminal::get_instance().info("本次测试模式：和预期结果比较");
    auto filename_dir = filename.parent_path();
    auto write_filename =
      filename_dir / filename_dir.filename().replace_extension(".out");
    ConsoleTerminal::get_instance().info("输出结果到: ");
    ConsoleTerminal::get_instance().info(write_filename.string());

    ConsoleTerminal::get_instance().switch_strategy(
      std::make_unique<FileTerminalStrategy>(write_filename.string())
    );
    return;
  }
  if (show_result) {
    ConsoleTerminal::get_instance().info("本次测试模式：直接输出结果");
    return;
  }
  if (verbose) {
    auto verbose_dir = Config::Get("verbose");
    auto log_file =
      (std::filesystem::path(verbose_dir) /
       (filename.stem().replace_extension(".log")).filename());
    ConsoleTerminal::get_instance().info("本次测试模式：调试模式");
    ConsoleTerminal::get_instance().info("输出结果到: ");
    ConsoleTerminal::get_instance().info(log_file.string());

    ConsoleTerminal::get_instance().switch_strategy(
      std::make_unique<FileTerminalStrategy>(log_file.string())
    );
    return;
  }
}

inline void AfterRun(const std::filesystem::path& filename) {
  ConsoleTerminal::get_instance().switch_strategy(
    std::make_unique<StardardTerminalStrategy>()
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
        ConsoleTerminal::get_instance().info("❌ 测试失败");
        ConsoleTerminal::get_instance().info("预期结果: ");
        ConsoleTerminal::get_instance().info(expected_line);

        ConsoleTerminal::get_instance().info("实际结果: ");
        ConsoleTerminal::get_instance().info(write_line);

        exit(1);
      }
    }
    ConsoleTerminal::get_instance().info("✅ 测试通过");
    return;
  }
}

inline void RunTest(const std::filesystem::path& filename) {
  ConsoleTerminal::get_instance().info("解析字节码文件: ");
  ConsoleTerminal::get_instance().info(filename.string());

  Runtime::BinaryFileParser parser(filename);
  auto code = parser.Parse();

  BeforeRun(filename);
  try {
    Runtime::VirtualMachine::Run(code);
  } catch (const std::exception& e) {
    PrintFrame(Runtime::VirtualMachine::Instance().CurrentFrame());
    ConsoleTerminal::get_instance().error(e.what());
    throw;
  }

  AfterRun(filename);
}

inline void InitEnv(int argc, char** argv) {
  DefineOption();
  Config::Accept(argc, argv);
}

}  // namespace tensorslow

#endif  // TENSORSLOW_BACKEND_INIT_H
