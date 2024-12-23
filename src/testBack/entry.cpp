
#include "runtime/BinaryFileParser.h"
#include "runtime/BufferedInputStream.h"
#include "runtime/PyFrame.h"

#include <filesystem>
#include <iostream>
#include <string>
#include <vector>

namespace fs = std::filesystem;

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

int main() {
  std::string integrationTestDir = "/app/test/integration";
  for (const auto& file : getFilesInDirectory(integrationTestDir)) {
    std::cout << "Running test: " << file.stem() << std::endl;
    torchlight::runtime::BinaryFileParser parser(
      std::make_unique<torchlight::runtime::BufferedInputStream>(
        file.string().c_str()
      )
    );

    auto code = parser.Parse();

    auto frame = std::make_shared<torchlight::runtime::PyFrame>(code);

    frame->Run();
  }

  return 0;
}