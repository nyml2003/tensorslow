#ifndef TORCHLIGHT_BYTECODE_UTILS_H
#define TORCHLIGHT_BYTECODE_UTILS_H

#include "bytecode/ByteCode.h"

namespace torchlight::bytecode {

uint8_t SerializeByteCode(ByteCode code);
}  // namespace torchlight::bytecode

void SerializeUInt32(uint32_t value, const char* value_str);

#endif