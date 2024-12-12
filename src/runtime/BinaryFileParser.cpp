#include <cstdio>
#include "collections/List.h"
#include "object/PyBytes.h"
#include "object/common.h"
#include "runtime/BinaryFileParser.h"

#include <string>

#include <iostream>

namespace torchlight::runtime {

BinaryFileParser::BinaryFileParser(BufferedInputStreamPtr inputStream)
  : inputStream(std::move(inputStream)) {}

PyCodePtr BinaryFileParser::Parse() {
  auto code = ParseCode();
  return code;
}

PyCodePtr BinaryFileParser::ParseCode() {
  collections::List<collections::Byte> byteCodes;
  while (true) {
    std::optional<uint8_t> byte = inputStream->ReadU8();
    if (!byte.has_value()) {
      break;
    }
    byteCodes.Add(byte.value());
  }
  byteCodes.PopBack();
  return std::make_shared<PyCode>(
    std::make_shared<object::PyBytes>(collections::Bytes(byteCodes))
  );
}
}  // namespace torchlight::runtime