

#include "Init.h"

#ifdef _WIN32
#include <Windows.h>
#endif

int main(int argc, char** argv) {
#ifdef _WIN32
  SetConsoleOutputCP(CP_UTF8);  // 在Windows平台上设置控制台输出为UTF-8编码
#endif
  tensorslow::InitEnv(argc, argv);
  auto file = tensorslow::Config::Get("file");
  if (file.empty()) {
    tensorslow::Schema::PrintUsage();
  } else {
    tensorslow::ParseAndGenerate(file);
  }

  return 0;
}