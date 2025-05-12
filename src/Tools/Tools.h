#ifndef TENSORSLOW_TOOLS_H
#define TENSORSLOW_TOOLS_H

#include <filesystem>
#include <fstream>

namespace fs = std::filesystem;

namespace tensorslow {

std::vector<fs::path> GetFilesInDirectory(
  const std::string& directoryPath,
  const std::string& extension
);

class RedirectCout {
 public:
  RedirectCout();
  ~RedirectCout();

  void redirectToFile(const std::string& filename);
  void restore();

 private:
  std::streambuf* originalBuffer;  // 保存 std::cout 的原始缓冲区
  std::ofstream file;              // 用于文件输出的文件流
};

}  // namespace tensorslow

#endif  // TENSORSLOW_TOOLS_H