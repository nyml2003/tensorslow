#ifndef TORCHLIGHT_RUNTIME_BINARYFILEPARSER_H
#define TORCHLIGHT_RUNTIME_BINARYFILEPARSER_H

#include "object/PyCode.h"
#include "runtime/BufferedInputStream.h"

namespace torchlight::runtime {

using object::PyCodePtr;

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
