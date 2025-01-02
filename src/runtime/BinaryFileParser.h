#ifndef TORCHLIGHT_RUNTIME_BINARYFILEPARSER_H
#define TORCHLIGHT_RUNTIME_BINARYFILEPARSER_H

#include "object/PyCode.h"
#include "runtime/BufferedInputStream.h"

namespace torchlight::runtime {

class BinaryFileParser {
 private:
  BufferedInputStreamPtr inputStream;

 public:
  explicit BinaryFileParser(BufferedInputStreamPtr inputStream);

  object::PyCodePtr Parse();

  object::PyCodePtr ParseCode();
};

}  // namespace torchlight::runtime

#endif  // TORCHLIGHT_BINARYFILEPARSER_H
