#include "test_default.h"

#include "collections/Integer.h"
#include "collections/impl/Integer.h"
#include "collections/impl/String.h"

using torchlight::collections::CreateIntegerWithCString;
using torchlight::collections::Integer;
using torchlight::collections::ToCString;

TEST(Integer, IntegerAddition) {
  Integer a = CreateIntegerWithCString("123");
  Integer b = CreateIntegerWithCString("456");
  Integer c = a.Add(b);
  ASSERT_STREQ(ToCString(c.ToString()).get(), "579");
}

TEST(Integer, IntegerAdditionWithNegative) {
  Integer a = CreateIntegerWithCString("-123");
  Integer b = CreateIntegerWithCString("456");
  Integer c = a.Add(b);
  ASSERT_STREQ(ToCString(c.ToString()).get(), "333");
}

TEST(Integer, IntegerSubtraction) {
  Integer a = CreateIntegerWithCString("123");
  Integer b = CreateIntegerWithCString("456");
  Integer c = a.Subtract(b);
  ASSERT_STREQ(ToCString(c.ToString()).get(), "-333");
}

TEST(Integer, IntegerSubtractionWithNegative) {
  Integer a = CreateIntegerWithCString("-123");
  Integer b = CreateIntegerWithCString("-456");
  Integer c = a.Subtract(b);
  ASSERT_STREQ(ToCString(c.ToString()).get(), "333");
}

TEST(Integer, IntegerMultiplication) {
  Integer a = CreateIntegerWithCString("123");
  Integer b = CreateIntegerWithCString("456");
  Integer c = a.Multiply(b);
  ASSERT_STREQ(ToCString(c.ToString()).get(), "56088");
}

TEST(Integer, IntegerDivision) {
  Integer a = CreateIntegerWithCString("123456");
  Integer b = CreateIntegerWithCString("123");
  Integer c = a.Divide(b);
  ASSERT_STREQ(ToCString(c.ToString()).get(), "1003");
}

TEST(Integer, IntegerModulo) {
  Integer a = CreateIntegerWithCString("123456");
  Integer b = CreateIntegerWithCString("123");
  Integer c = a.Modulo(b);
  ASSERT_STREQ(ToCString(c.ToString()).get(), "87");
}

TEST(Integer, IntegerGreaterThan) {
  Integer a = CreateIntegerWithCString("123");
  Integer b = CreateIntegerWithCString("456");
  ASSERT_FALSE(a.GreaterThan(b));
  ASSERT_TRUE(b.GreaterThan(a));
}

TEST(Integer, IntegerGreaterThanWithNegative) {
  Integer a = CreateIntegerWithCString("-123");
  Integer b = CreateIntegerWithCString("456");
  ASSERT_FALSE(a.GreaterThan(b));
  ASSERT_TRUE(b.GreaterThan(a));
}

TEST(Integer, IntegerEqual) {
  Integer a = CreateIntegerWithCString("123");
  Integer b = CreateIntegerWithCString("123");
  ASSERT_TRUE(a.Equal(b));
}

TEST(Integer, IntegerEqualWithNegative) {
  Integer a = CreateIntegerWithCString("-123");
  Integer b = CreateIntegerWithCString("-123");
  ASSERT_TRUE(a.Equal(b));
}

TEST(Integer, IntegerZero) {
  Integer a = CreateIntegerWithCString("0");
  ASSERT_TRUE(a.IsZero());
}

TEST(Integer, IntegerDivisionByZero) {
  Integer a = CreateIntegerWithCString("123");
  Integer b = CreateIntegerWithCString("0");
  ASSERT_THROW(a.Divide(b), std::runtime_error);
}

TEST(Integer, IntegerToHexString) {
  Integer a = CreateIntegerWithCString("255");
  ASSERT_STREQ(ToCString(a.ToHexString()).get(), "0xFF");
}

TEST(Integer, IntegerBitWiseAnd) {
  Integer a = CreateIntegerWithCString("15");
  Integer b = CreateIntegerWithCString("11");
  Integer c = a.BitWiseAnd(b);
  ASSERT_STREQ(ToCString(c.ToString()).get(), "11");
}

TEST(Integer, IntegerBitWiseOr) {
  Integer a = CreateIntegerWithCString("15");
  Integer b = CreateIntegerWithCString("11");
  Integer c = a.BitWiseOr(b);
  ASSERT_STREQ(ToCString(c.ToString()).get(), "15");
}

TEST(Integer, IntegerBitWiseXor) {
  Integer a = CreateIntegerWithCString("15");
  Integer b = CreateIntegerWithCString("11");
  Integer c = a.BitWiseXor(b);
  ASSERT_STREQ(ToCString(c.ToString()).get(), "4");
}

TEST(Integer, ExtraAdd) {
  ASSERT_TRUE(CreateIntegerWithCString("1234567890")
                .Add(CreateIntegerWithCString("9876543210"))
                .Equal(CreateIntegerWithCString("11111111100")));
  ASSERT_TRUE(CreateIntegerWithCString("5678901234")
                .Add(CreateIntegerWithCString("4321098765"))
                .Equal(CreateIntegerWithCString("9999999999")));
  ASSERT_TRUE(CreateIntegerWithCString("1111111111")
                .Add(CreateIntegerWithCString("2222222222"))
                .Equal(CreateIntegerWithCString("3333333333")));
  ASSERT_TRUE(CreateIntegerWithCString("9999999999")
                .Add(CreateIntegerWithCString("1"))
                .Equal(CreateIntegerWithCString("10000000000")));
  ASSERT_TRUE(CreateIntegerWithCString("3333333333")
                .Add(CreateIntegerWithCString("6666666666"))
                .Equal(CreateIntegerWithCString("9999999999")));
  ASSERT_TRUE(CreateIntegerWithCString("1234567890")
                .Add(CreateIntegerWithCString("1234567890"))
                .Equal(CreateIntegerWithCString("2469135780")));
  ASSERT_TRUE(CreateIntegerWithCString("7777777777")
                .Add(CreateIntegerWithCString("2222222222"))
                .Equal(CreateIntegerWithCString("9999999999")));
  ASSERT_TRUE(CreateIntegerWithCString("4567890124")
                .Add(CreateIntegerWithCString("5432109876"))
                .Equal(CreateIntegerWithCString("10000000000")));
  ASSERT_TRUE(CreateIntegerWithCString("8888888888")
                .Add(CreateIntegerWithCString("1111111111"))
                .Equal(CreateIntegerWithCString("9999999999")));
  ASSERT_TRUE(CreateIntegerWithCString("2345678901")
                .Add(CreateIntegerWithCString("7654321098"))
                .Equal(CreateIntegerWithCString("9999999999")));
  ASSERT_TRUE(CreateIntegerWithCString("9876543210")
                .Subtract(CreateIntegerWithCString("1234567890"))
                .Equal(CreateIntegerWithCString("8641975320")));
  ASSERT_TRUE(CreateIntegerWithCString("5678901234")
                .Subtract(CreateIntegerWithCString("4321098765"))
                .Equal(CreateIntegerWithCString("1357802469")));

  ASSERT_TRUE(CreateIntegerWithCString("2222222222")
                .Subtract(CreateIntegerWithCString("1111111111"))
                .Equal(CreateIntegerWithCString("1111111111")));
  ASSERT_TRUE(CreateIntegerWithCString("9999999999")
                .Subtract(CreateIntegerWithCString("1"))
                .Equal(CreateIntegerWithCString("9999999998")));
  ASSERT_TRUE(CreateIntegerWithCString("6666666666")
                .Subtract(CreateIntegerWithCString("3333333333"))
                .Equal(CreateIntegerWithCString("3333333333")));
  ASSERT_TRUE(CreateIntegerWithCString("1234567890")
                .Subtract(CreateIntegerWithCString("1234567890"))
                .Equal(CreateIntegerWithCString("0")));
  ASSERT_TRUE(CreateIntegerWithCString("7777777777")
                .Subtract(CreateIntegerWithCString("2222222222"))
                .Equal(CreateIntegerWithCString("5555555555")));
  ASSERT_TRUE(CreateIntegerWithCString("5432109876")
                .Subtract(CreateIntegerWithCString("4567890123"))
                .Equal(CreateIntegerWithCString("864219753")));
  ASSERT_TRUE(CreateIntegerWithCString("8888888888")
                .Subtract(CreateIntegerWithCString("1111111111"))
                .Equal(CreateIntegerWithCString("7777777777")));
  ASSERT_TRUE(CreateIntegerWithCString("7654321098")
                .Subtract(CreateIntegerWithCString("2345678901"))
                .Equal(CreateIntegerWithCString("5308642197")));
}

TEST(Integer, HexToInt) {
  ASSERT_TRUE(CreateIntegerWithCString("0x1234567890")
                .Equal(CreateIntegerWithCString("78187493520")));
  ASSERT_TRUE(CreateIntegerWithCString("0x9876543210")
                .Equal(CreateIntegerWithCString("654820258320")));
  ASSERT_TRUE(CreateIntegerWithCString("0x1111111111")
                .Equal(CreateIntegerWithCString("73300775185")));
  ASSERT_TRUE(CreateIntegerWithCString("0x9999999999")
                .Equal(CreateIntegerWithCString("659706976665")));
  ASSERT_TRUE(CreateIntegerWithCString("0x3333333333")
                .Equal(CreateIntegerWithCString("219902325555")));
  ASSERT_TRUE(CreateIntegerWithCString("0x7777777777")
                .Equal(CreateIntegerWithCString("513105426295")));
  ASSERT_TRUE(CreateIntegerWithCString("0x4567890124")
                .Equal(CreateIntegerWithCString("298089775396")));
  ASSERT_TRUE(CreateIntegerWithCString("0x8888888888")
                .Equal(CreateIntegerWithCString("586406201480")));
  ASSERT_TRUE(CreateIntegerWithCString("0x2345678901")
                .Equal(CreateIntegerWithCString("151488268545")));
}