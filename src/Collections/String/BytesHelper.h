#ifndef TORCHLIGHT_COLLECTIONS_BYTES_HELPER_H
#define TORCHLIGHT_COLLECTIONS_BYTES_HELPER_H
#include "Collections/Integer/Decimal.h"
#include "Collections/Integer/Integer.h"
#include "Collections/String/String.h"
namespace torchlight::Collections {

void Write(const String& bytes, const String& filename);
std::string ToCppString(const String& bytes);
String ReprByte(Byte byte);
String Serialize(double value);
double DeserializeDouble(const List<Byte>& bytes);
String Serialize(uint64_t value);
uint64_t DeserializeU64(const List<Byte>& bytes);
uint64_t DeserializeU64(const List<Byte>& bytes, Index& offset);
String Serialize(int64_t value);
int64_t DeserializeI64(const List<Byte>& bytes);
int64_t DeserializeI64(const List<Byte>& bytes, Index& offset);
String Serialize(uint32_t value);
uint32_t DeserializeU32(const List<Byte>& bytes);
String Serialize(int32_t value);
int32_t DeserializeI32(const List<Byte>& bytes);
String Serialize(uint16_t value);
uint16_t DeserializeU16(const List<Byte>& bytes);
String Serialize(const Integer& value);
Integer DeserializeInteger(const List<Byte>& bytes);
String Serialize(const Decimal& value);
Decimal DeserializeDecimal(const List<Byte>& bytes);
String Serialize(const String& value);
String DeserializeString(const List<Byte>& bytes);
}  // namespace torchlight::Collections
#endif