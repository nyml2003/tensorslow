#ifndef TORCHLIGHT_RUNTIME_BINARY_FILEPARSER_H
#define TORCHLIGHT_RUNTIME_BINARY_FILEPARSER_H

#include "Object/Runtime/PyCode.h"
#include "Runtime/BufferedInputStream.h"

namespace torchlight::Runtime {

class BinaryFileParser {
 private:
  BufferedInputStreamPtr inputStream;

 public:
  explicit BinaryFileParser(BufferedInputStreamPtr inputStream);

  Object::PyCodePtr Parse();

  Object::PyCodePtr ParseCode();
};

}  // namespace torchlight::Runtime

#endif  // TORCHLIGHT_RUNTIME_BINARY_FILEPARSER_H
