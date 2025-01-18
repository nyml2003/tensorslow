#include "../test_default.h"

#include "../Collections/Collections.h"
#include "Object.h"
#include "Object/ByteCode.h"

using namespace torchlight::Object;
using namespace torchlight::Collections;

namespace torchlight::Object {

class PyIntegerTest : public ::testing::Test {
 protected:
  void SetUp() override {
    // 初始化操作，如创建测试对象等
    integer1 = CreatePyInteger(10);
    integer2 = CreatePyInteger(20);
    integer3 = CreatePyInteger(10);
  }

  PyIntPtr integer1;
  PyIntPtr integer2;
  PyIntPtr integer3;
};

TEST_F(PyIntegerTest, TestValue) {
  EXPECT_TRUE(integer1->Value().Equal(CreateIntegerWithCString("10")));
  EXPECT_TRUE(integer2->Value().Equal(CreateIntegerWithCString("20")));
}

TEST_F(PyIntegerTest, TestAdd) {
  auto result = IntegerKlass::Self()->add(integer1, integer2);
  EXPECT_TRUE(std::dynamic_pointer_cast<PyInteger>(result)->Value().Equal(
    CreateIntegerWithCString("30")
  ));
}

TEST_F(PyIntegerTest, TestSub) {
  auto result = IntegerKlass::Self()->sub(integer2, integer1);
  EXPECT_TRUE(std::dynamic_pointer_cast<PyInteger>(result)->Value().Equal(
    CreateIntegerWithCString("10")
  ));
}

TEST_F(PyIntegerTest, TestMul) {
  auto result = IntegerKlass::Self()->mul(integer1, integer2);
  EXPECT_TRUE(std::dynamic_pointer_cast<PyInteger>(result)->Value().Equal(
    CreateIntegerWithCString("200")
  ));
}

TEST_F(PyIntegerTest, TestDiv) {
  auto result = IntegerKlass::Self()->div(integer2, integer1);
  EXPECT_TRUE(std::dynamic_pointer_cast<PyInteger>(result)->Value().Equal(
    CreateIntegerWithCString("2")
  ));
}

TEST_F(PyIntegerTest, TestRepr) {
  auto result = IntegerKlass::Self()->repr(integer1);
  EXPECT_TRUE(std::dynamic_pointer_cast<PyString>(result)->Value().Equal(
    CreateStringWithCString("<int 10>")
  ));
}

TEST_F(PyIntegerTest, TestGt) {
  auto result = IntegerKlass::Self()->gt(integer2, integer1);
  EXPECT_TRUE(std::dynamic_pointer_cast<PyBoolean>(result)->Value());
}

TEST_F(PyIntegerTest, TestLt) {
  auto result = IntegerKlass::Self()->lt(integer1, integer2);
  EXPECT_TRUE(std::dynamic_pointer_cast<PyBoolean>(result)->Value());
}

TEST_F(PyIntegerTest, TestEq) {
  auto result = IntegerKlass::Self()->eq(integer1, integer3);
  EXPECT_TRUE(std::dynamic_pointer_cast<PyBoolean>(result)->Value());
}

TEST_F(PyIntegerTest, TestGe) {
  auto result = IntegerKlass::Self()->ge(integer2, integer1);
  EXPECT_TRUE(std::dynamic_pointer_cast<PyBoolean>(result)->Value());
}

TEST_F(PyIntegerTest, TestLe) {
  auto result = IntegerKlass::Self()->le(integer1, integer2);
  EXPECT_TRUE(std::dynamic_pointer_cast<PyBoolean>(result)->Value());
}

TEST_F(PyIntegerTest, TestNe) {
  auto result = IntegerKlass::Self()->ne(integer1, integer2);
  EXPECT_TRUE(std::dynamic_pointer_cast<PyBoolean>(result)->Value());
}

TEST_F(PyIntegerTest, TestSerialize) {
  auto result = IntegerKlass::Self()->_serialize_(integer1);
  auto bytes = std::dynamic_pointer_cast<PyBytes>(result)->Value();
  EXPECT_EQ(bytes.Value().First(), static_cast<Byte>(Literal::INTEGER));
  Bytes content(bytes.Value().Slice(1, bytes.Size()));
  EXPECT_TRUE(Collections::DeserializeInteger(content).Equal(
    CreateIntegerWithCString("10")
  ));
}

}  // namespace torchlight::Object

int main(int argc, char** argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}