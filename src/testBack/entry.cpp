#include "Runtime/BinaryFileParser.h"
#include "Runtime/BufferedInputStream.h"
#include "Runtime/Interpreter.h"
#include "Runtime/PyFrame.h"

#include <filesystem>
#include <iostream>
#include <string>
#include <vector>

namespace fs = std::filesystem;

std::vector<fs::path> getFilesInDirectory(const fs::path& directoryPath) {
  std::vector<fs::path> fileNames;
  if (fs::exists(directoryPath) && fs::is_directory(directoryPath)) {
    for (const auto& entry : fs::directory_iterator(directoryPath)) {
      if (fs::is_regular_file(entry.status()) &&
          entry.path().extension() == ".pyc") {
        fileNames.push_back(entry.path());
      }
    }
  } else {
    std::cerr << "The directory does not exist or is not a directory."
              << std::endl;
  }
  return fileNames;
}

void runTest(const fs::path& file) {
  torchlight::Runtime::BinaryFileParser parser(
    std::make_unique<torchlight::Runtime::BufferedInputStream>(
      file.string().c_str()
    )
  );

  auto code = parser.Parse();

  torchlight::Runtime::Interpreter interpreter;
  interpreter.Run(code);
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

  // 重定向std::cout到log.txt（如果需要）
   // std::freopen("/app/log/log.txt", "w", stdout);

  if (!singleFile.empty()) {
    // 如果指定了单个文件，则只运行该文件
    fs::path filePath(singleFile);
    if (fs::exists(filePath) && filePath.extension() == ".pyc") {
      runTest(filePath);
    } else {
      std::cerr << "Invalid file or not a .pyc file: " << singleFile
                << std::endl;
      return 1;
    }
  } else {
    // 否则扫描目录下的所有.pyc文件并运行
    for (const auto& file : getFilesInDirectory(integrationTestDir)) {
      runTest(file);
    }
  }

  return 0;
}