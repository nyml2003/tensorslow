
#include "runtime/BinaryFileParser.h"
#include "runtime/BufferedInputStream.h"
#include "runtime/PyFrame.h"

#include <string>

int main(int argc, char** argv) {
  std::string input;
  if (argc > 1) {
    input = argv[1];
  } else {
    input = "/app/test/a.pyc";
  }

  torchlight::runtime::BinaryFileParser parser(
    std::make_unique<torchlight::runtime::BufferedInputStream>(input.c_str())
  );

  auto code = parser.Parse();

  auto frame = std::make_shared<torchlight::runtime::PyFrame>(code);

  frame->Run();

  return 0;
}