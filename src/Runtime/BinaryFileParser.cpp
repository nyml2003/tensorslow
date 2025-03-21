#include "Runtime/BinaryFileParser.h"
#include "ByteCode/PyCode.h"
#include "Collections/List.h"
#include "Runtime/Serialize.h"


#include <cstdio>

namespace torchlight::Runtime {

BinaryFileParser::BinaryFileParser(BufferedInputStreamPtr inputStream)
  : inputStream(std::move(inputStream)) {}

Object::PyCodePtr BinaryFileParser::Parse() {
  auto code = ParseCode();
  return code;
}

Object::PyCodePtr BinaryFileParser::ParseCode() {
  Collections::List<Byte> byteCodes;
  while (true) {
    std::optional<uint8_t> byte = inputStream->ReadU8();
    if (!byte.has_value()) {
      break;
    }
    byteCodes.Push(byte.value());
  }
  return MakeCode(Object::CreatePyBytes(Collections::Bytes(byteCodes)));
}
}  // namespace torchlight::Runtime