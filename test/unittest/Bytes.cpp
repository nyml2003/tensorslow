#include "test_default.h"

#include "collections/Bytes.h"
#include "collections/Iterator.h"
#include "collections/List.h"
#include "collections/String.h"
#include "collections/impl/Bytes.h"
#include "collections/impl/String.h"
#include "collections/impl/Integer.h"
#include "collections/impl/Decimal.h"

using torchlight::collections::Bytes;
using torchlight::collections::CreateBytesWithCString;
using torchlight::collections::CreateStringWithBytes;
using torchlight::collections::CreateStringWithCString;
using torchlight::collections::DeserializeDouble;
using torchlight::collections::DeserializeUInt64;
using torchlight::collections::Serialize;
using torchlight::collections::String;
using torchlight::collections::ToCString;
using torchlight::collections::ToString;
using torchlight::collections::Unicode;
using torchlight::collections::Integer;
using torchlight::collections::Decimal;
using torchlight::collections::CreateIntegerWithCString;
using torchlight::collections::CreateDecimalWithCString;

TEST(Bytes, CreateBytesWithCString) {
  Bytes bytes = CreateBytesWithCString("Hello, World!");
  ASSERT_EQ(bytes.Size(), 13);
  ASSERT_STREQ(ToCString(bytes).get(), "Hello, World!");
}

TEST(Bytes, AddBytes) {
  Bytes bytes = CreateBytesWithCString("Hello, ");
  Bytes bytes2 = CreateBytesWithCString("World!");
  Bytes bytes3 = bytes.Add(bytes2);
  ASSERT_EQ(bytes.Size(), 7);
  ASSERT_EQ(bytes2.Size(), 6);
  ASSERT_EQ(bytes3.Size(), 13);
  ASSERT_STREQ(ToCString(bytes3).get(), "Hello, World!");
}

TEST(Bytes, Concat) {
  Bytes bytes = CreateBytesWithCString("Hello, ");
  bytes.Concat(CreateBytesWithCString("World!"));
  ASSERT_EQ(bytes.Size(), 13);
  ASSERT_STREQ(ToCString(bytes).get(), "Hello, World!");
}

TEST(Bytes, ConcatCString) {
  Bytes bytes = CreateBytesWithCString("Hello, ");
  bytes.Concat(CreateBytesWithCString("World!"));
  ASSERT_EQ(bytes.Size(), 13);
  ASSERT_STREQ(ToCString(bytes).get(), "Hello, World!");
}

TEST(Bytes, Serialize) {
  uint64_t value = 1234567890;
  Bytes bytes = Serialize(value);
  uint64_t value_r = DeserializeUInt64(bytes);
  ASSERT_EQ(value, value_r);

  double value2 = 123.125;
  Bytes bytes2 = Serialize(value2);
  double value2_r = DeserializeDouble(bytes2);
  ASSERT_EQ(value2, value2_r);

  int64_t value3 = 1234567890;
  Bytes bytes3 = Serialize(value3);
  int64_t value3_r = DeserializeInt64(bytes3);
  ASSERT_EQ(value3, value3_r);

  uint32_t value4 = 1234567890;
  Bytes bytes4 = Serialize(value4);
  uint32_t value4_r = DeserializeUInt32(bytes4);
  ASSERT_EQ(value4, value4_r);

  int32_t value5 = 1234567890;
  Bytes bytes5 = Serialize(value5);
  int32_t value5_r = DeserializeInt32(bytes5);
  ASSERT_EQ(value5, value5_r);

  uint16_t value6 = 12345;
  Bytes bytes6 = Serialize(value6);
  uint16_t value6_r = DeserializeUInt16(bytes6);
  ASSERT_EQ(value6, value6_r);

  String value7 = CreateStringWithCString("Hello, World!");
  Bytes bytes7 = Serialize(value7);
  String value7_r = DeserializeString(bytes7);
  ASSERT_STREQ(ToCString(value7).get(), ToCString(value7_r).get());

  Bytes value8 = CreateBytesWithCString("Hello, World!");
  Bytes bytes8 = Serialize(value8);
  Bytes value8_r = DeserializeBytes(bytes8);
  ASSERT_EQ(value8.Size(), value8_r.Size());

  Integer value9 = CreateIntegerWithCString("123456789");
  Bytes bytes9 = Serialize(value9);
  Integer value9_r = DeserializeInteger(bytes9);
  ASSERT_TRUE(value9.Equal(value9_r));

  Decimal value10 = CreateDecimalWithCString("123456789");
  Bytes bytes10 = Serialize(value10);
  Decimal value10_r = DeserializeDecimal(bytes10);
  ASSERT_TRUE(value10.Equal(value10_r));
}
