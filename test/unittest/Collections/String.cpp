#include "../test_default.h"

#include "Collections.h"

using namespace torchlight::Collections;

TEST(String, CreateStringWithCString) {
  String str = CreateStringWithCString("Hello, World!");
  ASSERT_EQ(str.Size(), 13);
  ASSERT_EQ(ToCppString(str), "Hello, World!");
}

TEST(String, ComplexString) {
  String str = CreateStringWithCString("O(∩_∩)O~~");
  ASSERT_EQ(str.Size(), 9);
  ASSERT_EQ(ToCppString(str), "O(∩_∩)O~~");
  str = CreateStringWithCString("αββγδδδεεζηθãäèèÄゲグデバタヒɔ:aiwjd❉♂◙㊦㊨");
  ASSERT_EQ(str.Size(), 35);
  ASSERT_EQ(ToCppString(str), "αββγδδδεεζηθãäèèÄゲグデバタヒɔ:aiwjd❉♂◙㊦㊨");
  str = CreateStringWithCString("👨‍👩‍👧‍👦");
  ASSERT_EQ(str.Size(), 7);
  ASSERT_EQ(ToCppString(str), "👨‍👩‍👧‍👦");
}

TEST(String, CreateStringWithBytes) {
  torchlight::Collections::Bytes bytes = CreateBytesWithCString("Hello");
  String str = CreateStringWithBytes(bytes.Value());
  ASSERT_EQ(str.Size(), 5);
  ASSERT_EQ(str.Get(0), 'H');
  ASSERT_EQ(str.Get(1), 'e');
  ASSERT_EQ(str.Get(2), 'l');
  ASSERT_EQ(str.Get(3), 'l');
  ASSERT_EQ(str.Get(4), 'o');
}

TEST(String, Concat) {
  String str1 = CreateStringWithCString("Hello");
  String str2 = CreateStringWithCString(" World");
  StringBuilder sb;
  sb.Append(str1);
  sb.Append(str2);
  String str3 = sb.ToString();
  ASSERT_EQ(str3.Size(), 11);
  ASSERT_TRUE(str3.Equal(CreateStringWithCString("Hello World")));
  ASSERT_TRUE(str3 == CreateStringWithCString("Hello World"));
  ASSERT_TRUE(str2[0] == ' ');
}

TEST(String, Copy) {
  String str1 = CreateStringWithCString("Hello");
  String str2 = str1.Copy();
  ASSERT_EQ(str1.Size(), str2.Size());
  for (size_t i = 0; i < str1.Size(); ++i) {
    ASSERT_EQ(str1.Get(i), str2.Get(i));
  }
}

TEST(String, Clear) {
  StringBuilder sb(CreateStringWithCString("Hello"));
  sb.Clear();
  ASSERT_EQ(sb.Size(), 0);
}

TEST(String, Push) {
  StringBuilder sb;
  sb.Append('H');
  sb.Append('e');
  sb.Append('l');
  sb.Append('l');
  sb.Append('o');
  ASSERT_EQ(sb.Size(), 5);
  ASSERT_TRUE(sb.ToString().Equal(CreateStringWithCString("Hello")));
}

TEST(String, Slice) {
  String str = CreateStringWithCString("Hello World");
  String slicedStr = str.Slice(0, 5);
  ASSERT_EQ(slicedStr.Size(), 5);
  ASSERT_TRUE(slicedStr.Equal(CreateStringWithCString("Hello")));
  // error
  ASSERT_THROW(str.Slice(0, 12), std::runtime_error);
  ASSERT_THROW(str.Slice(0, 0), std::runtime_error);
  ASSERT_THROW(str.Slice(5, 0), std::runtime_error);
  ASSERT_THROW(str.Slice(5, 5), std::runtime_error);
  ASSERT_THROW(str.Slice(5, 4), std::runtime_error);
}

TEST(String, Find) {
  String str = CreateStringWithCString("Hello World");
  String sub = CreateStringWithCString("ll");
  ASSERT_EQ(str.Find(sub, 0), 2);
  String empty = CreateStringWithCString("");
  ASSERT_EQ(str.Find(empty, 0), 0);
  ASSERT_THROW(str.Find(sub, 12), std::runtime_error);
  ASSERT_THROW(str.Find(sub, 10), std::runtime_error);
  str = CreateStringWithCString("abababab");
  sub = CreateStringWithCString("bab");
  ASSERT_EQ(str.Find(sub, 0), 1);
}

TEST(String, Equal) {
  String str1 = CreateStringWithCString("Hello");
  String str2 = CreateStringWithCString("Hello");
  ASSERT_TRUE(str1.Equal(str2));
}

TEST(String, GreaterThan) {
  String str1 = CreateStringWithCString("Hello");
  String str2 = CreateStringWithCString("Hello World");
  ASSERT_TRUE(str2.GreaterThan(str1));
  str1 = CreateStringWithCString("Heaven");
  str2 = CreateStringWithCString("Hello");
  ASSERT_TRUE(str2.GreaterThan(str1));
}

TEST(String, LessThan) {
  String str1 = CreateStringWithCString("Hello");
  String str2 = CreateStringWithCString("Hello World");
  ASSERT_TRUE(str1.LessThan(str2));
  str1 = CreateStringWithCString("Heaven");
  str2 = CreateStringWithCString("Hello");
  ASSERT_TRUE(str1.LessThan(str2));
}

TEST(String, GreaterThanOrEqual) {
  String str1 = CreateStringWithCString("Hello");
  String str2 = CreateStringWithCString("Hello");
  ASSERT_TRUE(str1.GreaterThanOrEqual(str2));
  str1 = CreateStringWithCString("Heaven");
  str2 = CreateStringWithCString("Hello");
  ASSERT_FALSE(str1.GreaterThanOrEqual(str2));
}

TEST(String, LessThanOrEqual) {
  String str1 = CreateStringWithCString("Hello");
  String str2 = CreateStringWithCString("Hello");
  ASSERT_TRUE(str1.LessThanOrEqual(str2));
  str1 = CreateStringWithCString("Heaven");
  str2 = CreateStringWithCString("Hello");
  ASSERT_TRUE(str1.LessThanOrEqual(str2));
}

TEST(String, NotEqual) {
  String str1 = CreateStringWithCString("Hello");
  String str2 = CreateStringWithCString("World");
  ASSERT_TRUE(str1.NotEqual(str2));
}

TEST(String, ToString) {
  double value = 3.14159;
  String str = ToString(value);
  ASSERT_TRUE(str.Equal(CreateStringWithCString("3.141590")));

  int32_t value2 = 123;
  String str2 = ToString(value2);
  ASSERT_TRUE(str2.Equal(CreateStringWithCString("123")));

  uint64_t value3 = 12345678901234567890;
  String str3 = ToString(value3);
  ASSERT_TRUE(str3.Equal(CreateStringWithCString("12345678901234567890")));

  int64_t value4 = -1234567890123456789;
  String str4 = ToString(value4);
  ASSERT_TRUE(str4.Equal(CreateStringWithCString("-1234567890123456789")));

  uint32_t value5 = 4294967295;
  String str5 = ToString(value5);
  ASSERT_TRUE(str5.Equal(CreateStringWithCString("4294967295")));
}

TEST(String, Add) {
  String str1 = CreateStringWithCString("Hello");
  String str2 = CreateStringWithCString(" World");
  String str3 = str1.Add(str2);
  ASSERT_TRUE(str3.Equal(CreateStringWithCString("Hello World")));
}

TEST(String, Spilt) {
  String str = CreateStringWithCString("Hello, World");
  String delimiter = CreateStringWithCString(", ");
  torchlight::Collections::List<String> list = str.Split(delimiter);
  ASSERT_EQ(list.Size(), 2);
  ASSERT_TRUE(list.Get(0).Equal(CreateStringWithCString("Hello")));
  ASSERT_TRUE(list.Get(1).Equal(CreateStringWithCString("World")));
  str = CreateStringWithCString("h,e,l,l,o");
  delimiter = CreateStringWithCString(",");
  list = str.Split(delimiter);
  ASSERT_EQ(list.Size(), 5);
  ASSERT_TRUE(list.Get(0).Equal(CreateStringWithCString("h")));
  ASSERT_TRUE(list.Get(1).Equal(CreateStringWithCString("e")));
  ASSERT_TRUE(list.Get(2).Equal(CreateStringWithCString("l")));
  ASSERT_TRUE(list.Get(3).Equal(CreateStringWithCString("l")));
  ASSERT_TRUE(list.Get(4).Equal(CreateStringWithCString("o")));
}

TEST(String, Move) {
  String str1 = CreateStringWithCString("Hello");
  String str2 = std::move(str1);
  ASSERT_EQ(str1.Size(), 0);
  ASSERT_EQ(str2.Size(), 5);
  ASSERT_TRUE(str2.Equal(CreateStringWithCString("Hello")));
  String str3(str2);
  ASSERT_EQ(str2.Size(), 5);
  ASSERT_EQ(str3.Size(), 5);
  ASSERT_TRUE(str3.Equal(CreateStringWithCString("Hello")));
}