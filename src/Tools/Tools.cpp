#include "Tools/Tools.h"
#include <iostream>
#include <stdexcept>
namespace tensorslow {

std::vector<fs::path> GetFilesInDirectory(
  const std::string& directoryPath,
  const std::string& extension
) {
  std::vector<fs::path> fileNames;
  if (fs::exists(directoryPath) && fs::is_directory(directoryPath)) {
    for (const auto& entry : fs::directory_iterator(directoryPath)) {
      if (fs::is_regular_file(entry.status()) && entry.path().extension() == extension) {
        fileNames.push_back(entry.path());
      }
    }
  } else {
    std::cerr << "The directory does not exist or is not a directory."
              << std::endl;
  }
  return fileNames;
}

RedirectCout::RedirectCout() : originalBuffer(std::cout.rdbuf()) {}

RedirectCout::~RedirectCout() {
  if (originalBuffer) {
    std::cout.rdbuf(originalBuffer);  // 恢复原始缓冲区
  }
}

void RedirectCout::redirectToFile(const std::string& filename) {
  if (file.is_open()) {
    file.close();  // 如果之前已经打开文件，先关闭
  }
  file.open(filename, std::ios::out);  // 打开文件
  std::cout.rdbuf(file.rdbuf());  // 将 std::cout 的缓冲区替换为文件的缓冲区
}

void RedirectCout::restore() {
  if (file.is_open()) {
    file.close();  // 关闭文件
  }
  std::cout.rdbuf(originalBuffer);  // 恢复 std::cout 的原始缓冲区
}

}  // namespace tensorslow