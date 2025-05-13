#include "Init.h"
#include "Tools/Config/Config.h"

#ifdef _WIN32
#include <Windows.h>
#endif
namespace tensorslow {}  // namespace tensorslow

int main(int argc, char** argv) {
#ifdef _WIN32
  SetConsoleOutputCP(CP_UTF8);  // 在Windows平台上设置控制台输出为UTF-8编码
#endif
  tensorslow::InitEnv(argc, argv);
  auto file = tensorslow::Config::Get("file");
  if (!file.empty()) {
    tensorslow::RunTest(file);
  } else {
    tensorslow::Schema::PrintUsage();
  }
  return 0;
}