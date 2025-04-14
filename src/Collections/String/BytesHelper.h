#ifndef TORCHLIGHT_COLLECTIONS_BYTES_HELPER_H
#define TORCHLIGHT_COLLECTIONS_BYTES_HELPER_H
#include "Collections/Integer/Decimal.h"
#include "Collections/Integer/Integer.h"
#include "Collections/String/Bytes.h"
#include "Collections/String/String.h"
namespace torchlight::Collections {
Bytes CreateBytesWithCString(const char* str);
Bytes ToBytes(const String& str) noexcept;
void Write(const Bytes& bytes, const String& filename);
std::string ToCppString(const Bytes& bytes);
String ReprByte(Byte byte);
Bytes Serialize(double value);
double DeserializeDouble(const List<Byte>& bytes);
Bytes Serialize(uint64_t value);
uint64_t DeserializeU64(const List<Byte>& bytes);
uint64_t DeserializeU64(const List<Byte>& bytes, Index& offset);
Bytes Serialize(int64_t value);
int64_t DeserializeI64(const List<Byte>& bytes);
int64_t DeserializeI64(const List<Byte>& bytes, Index& offset);
Bytes Serialize(uint32_t value);
uint32_t DeserializeU32(const List<Byte>& bytes);
Bytes Serialize(int32_t value);
int32_t DeserializeI32(const List<Byte>& bytes);
Bytes Serialize(uint16_t value);
uint16_t DeserializeU16(const List<Byte>& bytes);
Bytes Serialize(const Integer& value);
Integer DeserializeInteger(const List<Byte>& bytes);
Bytes Serialize(const Decimal& value);
Decimal DeserializeDecimal(const List<Byte>& bytes);
Bytes Serialize(const String& value);
String DeserializeString(const List<Byte>& bytes);
Bytes Serialize(const Bytes& value);
Bytes DeserializeBytes(const List<Byte>& bytes);
}  // namespace torchlight::Collections
#endif