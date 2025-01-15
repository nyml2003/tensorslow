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

double DeserializeDouble(const Bytes& bytes);

Bytes Serialize(uint64_t value);

uint64_t DeserializeUInt64(const Bytes& bytes);

Bytes Serialize(int64_t value);

int64_t DeserializeInt64(const Bytes& bytes);

Bytes Serialize(uint32_t value);

uint32_t DeserializeUInt32(const Bytes& bytes);

Bytes Serialize(int32_t value);

int32_t DeserializeInt32(const Bytes& bytes);

Bytes Serialize(uint16_t value);

uint16_t DeserializeUInt16(const Bytes& bytes);

Bytes Serialize(const Integer& value);

Integer DeserializeInteger(const Bytes& bytes);

Bytes Serialize(const Decimal& value);

Decimal DeserializeDecimal(const Bytes& bytes);

Bytes Serialize(const String& value);

String DeserializeString(const Bytes& bytes);

Bytes Serialize(const Bytes& value);

Bytes DeserializeBytes(const Bytes& bytes);

}  // namespace torchlight::collections

#endif