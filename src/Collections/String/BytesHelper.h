#ifndef TORCHLIGHT_COLLECTIONS_BYTES_HELPER_H
#define TORCHLIGHT_COLLECTIONS_BYTES_HELPER_H
#include "Collections/Integer/Decimal.h"
#include "Collections/Integer/Integer.h"
#include "Collections/String/Bytes.h"
#include "Collections/String/String.h"
namespace torchlight::Collections {
Bytes CreateBytesWithCString(const char* str);
Bytes ToBytes(const String& str);
void Write(const Bytes& bytes, const String& filename);
std::string ToCppString(const Bytes& bytes);
String ReprByte(Byte byte);
Bytes Serialize(double value);
double DeserializeDouble(const Bytes& bytes);
Bytes Serialize(uint64_t value);
uint64_t DeserializeU64(const Bytes& bytes);
Bytes Serialize(int64_t value);
int64_t DeserializeI64(const Bytes& bytes);
Bytes Serialize(uint32_t value);
uint32_t DeserializeU32(const Bytes& bytes);
Bytes Serialize(int32_t value);
int32_t DeserializeI32(const Bytes& bytes);
Bytes Serialize(uint16_t value);
uint16_t DeserializeU16(const Bytes& bytes);
Bytes Serialize(const Integer& value);
Integer DeserializeInteger(const Bytes& bytes);
Bytes Serialize(const Decimal& value);
Decimal DeserializeDecimal(const Bytes& bytes);
Bytes Serialize(const String& value);
String DeserializeString(const Bytes& bytes);
Bytes Serialize(const Bytes& value);
Bytes DeserializeBytes(const Bytes& bytes);
}  // namespace torchlight::Collections
#endif