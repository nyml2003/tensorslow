#include <gtest/gtest.h>
#include "../test_default.h"
#include "Collections/Integer.h"
#include "Collections/IntegerHelper.h"

#include "Collections.h"

using namespace torchlight::Collections;

TEST(Integer, IntegerAddition) {
  Integer a = CreateIntegerWithCString("123");
  Integer b = CreateIntegerWithCString("456");
  Integer c = a.Add(b);
  ASSERT_EQ(ToCppString(c.ToString()), "579");
}

TEST(Integer, IntegerAdditionWithNegative) {
  Integer a = CreateIntegerWithCString("-123");
  Integer b = CreateIntegerWithCString("456");
  Integer c = a.Add(b);
  ASSERT_EQ(ToCppString(c.ToString()), "333");
}

TEST(Integer, IntegerSubtraction) {
  Integer a = CreateIntegerWithCString("123");
  Integer b = CreateIntegerWithCString("456");
  Integer c = a.Subtract(b);
  ASSERT_EQ(ToCppString(c.ToString()), "-333");
}

TEST(Integer, IntegerSubtractionWithNegative) {
  Integer a = CreateIntegerWithCString("-123");
  Integer b = CreateIntegerWithCString("-456");
  Integer c = a.Subtract(b);
  ASSERT_EQ(ToCppString(c.ToString()), "333");
}

TEST(Integer, IntegerMultiplication) {
  Integer a = CreateIntegerWithCString("123");
  Integer b = CreateIntegerWithCString("456");
  Integer c = a.Multiply(b);
  ASSERT_EQ(ToCppString(c.ToString()), "56088");
}

TEST(Integer, IntegerDivision) {
  Integer a = CreateIntegerWithCString("123456");
  Integer b = CreateIntegerWithCString("123");
  Integer c = a.Divide(b);
  ASSERT_EQ(ToCppString(c.ToString()), "1003");
}

TEST(Integer, IntegerModulo) {
  Integer a = CreateIntegerWithCString("123456");
  Integer b = CreateIntegerWithCString("123");
  Integer c = a.Modulo(b);
  ASSERT_EQ(ToCppString(c.ToString()), "87");
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
  ASSERT_EQ(ToCppString(a.ToHexString()), "0xFF");
}

TEST(Integer, IntegerBitWiseAnd) {
  Integer a = CreateIntegerWithCString("15");
  Integer b = CreateIntegerWithCString("11");
  Integer c = a.BitWiseAnd(b);
  ASSERT_EQ(ToCppString(c.ToString()), "11");
}

TEST(Integer, IntegerBitWiseOr) {
  Integer a = CreateIntegerWithCString("15");
  Integer b = CreateIntegerWithCString("11");
  Integer c = a.BitWiseOr(b);
  ASSERT_EQ(ToCppString(c.ToString()), "15");
}

TEST(Integer, IntegerBitWiseXor) {
  Integer a = CreateIntegerWithCString("15");
  Integer b = CreateIntegerWithCString("11");
  Integer c = a.BitWiseXor(b);
  ASSERT_EQ(ToCppString(c.ToString()), "4");
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

TEST(Integer, U64) {
  Integer int1 = CreateIntegerWithU64(123456);
  Integer int2 = CreateIntegerWithU64(123456);
  ASSERT_TRUE(int1.Equal(int2));
  ASSERT_TRUE(ToU64(int1) == 123456);
  List<Integer> divmod = int1.DivMod(int2);
  ASSERT_TRUE(divmod.Get(0).Equal(CreateIntegerWithU64(1)));
  ASSERT_TRUE(divmod.Get(1).Equal(CreateIntegerZero()));
  Integer intZero = CreateIntegerWithU64(0);
  ASSERT_TRUE(intZero.IsZero());
  ASSERT_TRUE(ToU64(intZero) == 0);
  Integer int4 = CreateIntegerWithCString("-123456");
  ASSERT_THROW(ToU64(int4), std::runtime_error);
  Integer int5 = CreateIntegerWithCString(
    "0xfedcba9876543210fedcba9876543210FEDCBA9876543210"
  );
  ASSERT_TRUE(int5.Equal(CreateIntegerWithCString(
    "6249203505451628849692820439375744481966954417427815084560"
  )));
  ASSERT_THROW(ToU64(int5), std::runtime_error);
}

TEST(Integer, safeAdd) {
  uint64_t u123 = 123;
  int64_t ip100 = 100;
  int64_t im100 = -100;
  ASSERT_TRUE(safe_add(u123, ip100) == 223);
  ASSERT_TRUE(safe_add(u123, im100) == 23);
}

TEST(Integer, LessThanOrEqual) {
  ASSERT_TRUE(CreateIntegerWithCString("123").LessThanOrEqual(
    CreateIntegerWithCString("456")
  ));
  ASSERT_FALSE(CreateIntegerWithCString("456").LessThanOrEqual(
    CreateIntegerWithCString("123")
  ));
  ASSERT_TRUE(CreateIntegerWithCString("123").LessThanOrEqual(
    CreateIntegerWithCString("123")
  ));
  ASSERT_TRUE(CreateIntegerWithCString("-123").LessThanOrEqual(
    CreateIntegerWithCString("456")
  ));
  ASSERT_FALSE(CreateIntegerWithCString("456").LessThanOrEqual(
    CreateIntegerWithCString("-123")
  ));
  ASSERT_TRUE(CreateIntegerWithCString("-123").LessThanOrEqual(
    CreateIntegerWithCString("-123")
  ));
  ASSERT_TRUE(
    CreateIntegerWithCString("0").LessThanOrEqual(CreateIntegerWithCString("1"))
  );
  ASSERT_FALSE(
    CreateIntegerWithCString("1").LessThanOrEqual(CreateIntegerWithCString("0"))
  );
}