#include "runtime/BinaryFileParser.h"

#include "collections/List.h"
#include "object/PyBytes.h"
#include "object/PyCode.h"
#include "runtime/Serialize.h"

#include <cstdio>
#include <memory>

namespace torchlight::runtime {

using collections::Byte;
using collections::Bytes;
using collections::List;
using object::PyCodePtr;

BinaryFileParser::BinaryFileParser(BufferedInputStreamPtr inputStream)
  : inputStream(std::move(inputStream)) {}

PyCodePtr BinaryFileParser::Parse() {
  auto code = ParseCode();
  return code;
}

PyCodePtr BinaryFileParser::ParseCode() {
  List<Byte> byteCodes;
  while (true) {
    std::optional<uint8_t> byte = inputStream->ReadU8();
    if (!byte.has_value()) {
      break;
    }
    byteCodes.Add(byte.value());
  }
  return MakeCode(object::CreateBytes(Bytes(byteCodes)));
}
}  // namespace torchlight::runtime