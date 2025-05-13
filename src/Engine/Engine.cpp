#include "Init.h"
#include "Tools/Config/Config.h"
#ifdef _WIN32
#include <Windows.h>
#endif

int main(int argc, char** argv) {
#ifdef _WIN32
  SetConsoleOutputCP(CP_UTF8);  // 在Windows平台上设置控制台输出为UTF-8编码
#endif
  tensorslow::InitEnv(argc, argv);

  if (tensorslow::Config::Has("compile")) {
    tensorslow::HandleCompile();
  } else if (tensorslow::Config::Has("interpret")) {
    tensorslow::HandleInterpret();
  } else if (tensorslow::Config::Has("interpret_bytecode")) {
    tensorslow::HandleInterpretBytecode();
  }
  return 0;
}