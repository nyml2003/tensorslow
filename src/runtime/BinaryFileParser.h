#ifndef TORCHLIGHT_RUNTIME_BINARYFILEPARSER_H
#define TORCHLIGHT_RUNTIME_BINARYFILEPARSER_H

#include "runtime/BufferedInputStream.h"
#include "runtime/PyCode.h"

namespace torchlight::runtime {

class BinaryFileParser {
 private:
  BufferedInputStreamPtr inputStream;

 public:
  explicit BinaryFileParser(BufferedInputStreamPtr inputStream);

  PyCodePtr Parse();

  PyCodePtr ParseCode();
};

}  // namespace torchlight::runtime

#endif  // TORCHLIGHT_BINARYFILEPARSER_H
