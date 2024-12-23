

#include <cstring>
#include <fstream>
#include <iostream>
#include "collections/String.h"
#include "collections/common.h"

#include "bytecode/utils.h"

namespace torchlight::bytecode {

using collections::Index;
using std::ofstream;

const char* integrationTestDir = "/app/test/integration";

void SerializeInstStream(const InstStream& stream, const String& filename) {
  String fileFullPath = String(integrationTestDir)
                          .Concat(String("/"))
                          .Concat(filename)
                          .Concat(String(".pyc"));
  ofstream file(fileFullPath.ToUTF8(), std::ios::binary);
  Bytes buffer;
  for (Index i = 0; i < stream.Size(); ++i) {
    buffer = buffer.Concat(stream.Get(i)->ToString());
  }
  for (Index i = 0; i < buffer.Size(); ++i) {
    file << buffer.Get(i);
  }
  file.close();
}

Byte SerializeByteCode(ByteCode code) {
  return static_cast<Byte>(code);
}

List<Byte> SerializeUInt32(uint32_t value) {
  List<Byte> result;
  result.Expand(4);
  for (collections::Index i = 0; i < 4; ++i) {
    result.Add(static_cast<Byte>((value >> (i * 8)) & 0xFF));
  }
  return result;
}

List<Byte> SerializeUInt64(uint64_t value) {
  List<Byte> result;
  result.Expand(8);
  for (collections::Index i = 0; i < 8; ++i) {
    result.Add(static_cast<Byte>((value >> (i * 8)) & 0xFF));
  }
  return result;
}

}  // namespace torchlight::bytecode