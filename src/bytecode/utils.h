#ifndef TORCHLIGHT_BYTECODE_UTILS_H
#define TORCHLIGHT_BYTECODE_UTILS_H

#include "collections/String.h"

#include "bytecode/ByteCode.h"

namespace torchlight::bytecode {
extern const char* integrationTestDir;

using collections::Byte;
using collections::List;
using collections::String;

Byte SerializeByteCode(ByteCode code);

List<Byte> SerializeUInt32(uint32_t value);

List<Byte> SerializeUInt64(uint64_t value);

void SerializeInstStream(const InstStream& stream, const String& filename);
}  // namespace torchlight::bytecode

#endif