#ifndef TORCHLIGHT_COLLECTIONS_BYTES_IMPL_H
#define TORCHLIGHT_COLLECTIONS_BYTES_IMPL_H

#include "collections/Bytes.h"
#include "collections/Integer.h"
#include "collections/String.h"

#include <fstream>

namespace torchlight::collections {

Bytes CreateBytesWithCString(const char* str);

Bytes ToBytes(const String& str);

void Write(Bytes& bytes, const String& filename);

std::unique_ptr<char[]> ToCString(const Bytes& bytes);

Bytes Serialize(double value);

Bytes Serialize(uint64_t value);

Bytes Serialize(uint32_t value);

Bytes Serialize(int32_t value);

Bytes Serialize(uint16_t value);

Bytes Serialize(const Integer& value);

Bytes Serialize(const String& value);

}  // namespace torchlight::collections

#endif