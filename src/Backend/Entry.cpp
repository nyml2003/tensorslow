#include "Runtime/BinaryFileParser.h"
#include "Runtime/BufferedInputStream.h"
#include "Runtime/Interpreter.h"
#include "Tools/Tools.h"

#include <filesystem>
#include <fstream>
#include <iostream>
#include <string>
using namespace torchlight;
RedirectCout redirectCout;
void DefineOption() {
  Schema schema;
  schema.Add(Parameter(
    "file",
    [](const std::string& value) {
      // 文件系统里有没有这个文件
      bool file_exists = std::filesystem::exists(value);
      // 后缀名是.py 且文件是一个普通文件
      bool is_py = value.substr(value.find_last_of('.') + 1) == "pyc";
      bool is_regular = std::filesystem::is_regular_file(value);
      return file_exists && is_py && is_regular;
    },
    "/app/test/dev/dev.pyc"
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
    "/app/test/integration"
  ));
  schema.Add(Parameter(
    "debug",
    [](const std::string& value) {
      // value 是 "true" 或 "false"
      return value == "true" || value == "false";
    },
    "false"
  ));
  schema.Add(Parameter(
    "compare_result",
    [](const std::string& value) {
      // value 是 "true" 或 "false"
      return value == "true" || value == "false";
    },
    "false"
  ));
  schema.Add(Parameter(
    "show_result",
    [](const std::string& value) {
      // value 是 "true" 或 "false"
      return value == "true" || value == "false";
    },
    "false"
  ));
  ArgsHelper::SetSchema(schema);
}

void HandleResultBegin(fs::path filename) {
  bool compare_result = ArgsHelper::Instance().Get("compare_result") == "true";
  bool show_result = ArgsHelper::Instance().Get("show_result") == "true";
  bool debug = ArgsHelper::Instance().Get("debug") == "true";
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
    std::cout << "本次测试模式：和预期结果比较" << std::endl;
    auto filename_dir = filename.parent_path();
    auto write_filename =
      filename_dir / filename_dir.filename().replace_extension(".out");
    std::cout << "输出结果到: " << write_filename << std::endl;
    redirectCout.redirectToFile(write_filename.string());
    return;
  }
  if (show_result) {
    std::cout << "本次测试模式：直接输出结果" << std::endl;
    return;
  }
  if (debug) {
    std::cout << "本次测试模式：调试模式" << std::endl;
    redirectCout.redirectToFile("/app/log/" / filename.filename() / ".log");
    return;
  }
}

void HandleResultEnd(fs::path filename) {
  redirectCout.restore();
  bool compare_result = ArgsHelper::Instance().Get("compare_result") == "true";
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
        std::cout << "❌ 测试失败" << std::endl;
        exit(1);
        return;
      }
    }
    std::cout << "✅ 测试通过" << std::endl << std::endl;
    return;
  }
}
void RunTest(const fs::path& filename) {
  std::cout << "解析字节码文件: " << filename << std::endl;
  Runtime::BinaryFileParser parser(
    std::make_unique<Runtime::BufferedInputStream>(filename.string().c_str())
  );
  auto code = parser.Parse();
  Runtime::Interpreter interpreter;
  HandleResultBegin(filename);
  interpreter.Run(code);
  HandleResultEnd(filename);
}
int main(int argc, char** argv) {
  DefineOption();
  ArgsHelper::Instance().Accept(argc, argv);
  if (ArgsHelper::Instance().Has("dir")) {
    auto dir = ArgsHelper::Instance().Get("dir");
    std::vector<fs::path> subdirs;
    for (const auto& entry : fs::directory_iterator(dir)) {
      if (entry.is_directory()) {
        subdirs.push_back(entry.path());
      }
    }
    for (const auto& subdir : subdirs) {
      auto files = GetFilesInDirectory(subdir.string(), ".pyc");
      std::cout << std::endl
                << "测试用例:" << subdir.filename().string() << std::endl;
      for (const auto& file : files) {
        RunTest(file);
      }
    }
    return 0;
  }
  if (ArgsHelper::Instance().Has("file")) {
    auto file = ArgsHelper::Instance().Get("file");

    RunTest(file);

    return 0;
  }
  auto file = ArgsHelper::Instance().Get("file");

  RunTest(file);

  return 0;
}