#ifndef TORCHLIGHT_RUNTIME_BINARYFILEPARSER_H
#define TORCHLIGHT_RUNTIME_BINARYFILEPARSER_H

#include "Object/PyCode.h"
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

#endif  // TORCHLIGHT_BINARYFILEPARSER_H
