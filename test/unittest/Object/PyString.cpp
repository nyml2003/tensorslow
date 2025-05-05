#include <memory>
#include "../test_default.h"

#include "../Collections/Collections.h"
#include "Object.h"

using namespace tensorslow::Object;
using namespace tensorslow::Collections;

namespace tensorslow::Object {

class PyStringTest : public ::testing::Test {
 protected:
  void SetUp() override {
    str1 = std::dynamic_pointer_cast<PyString>(
      CreatePyString(Collections::CreateStringWithCString("hello"))
    );
    str2 = std::dynamic_pointer_cast<PyString>(
      CreatePyString(Collections::CreateStringWithCString("world"))
    );
    str3 = std::dynamic_pointer_cast<PyString>(
      CreatePyString(Collections::CreateStringWithCString("hello"))
    );
  }

  PyStrPtr str1;
  PyStrPtr str2;
  PyStrPtr str3;
};

TEST_F(PyStringTest, Constructor) {
  PyStrPtr str = std::dynamic_pointer_cast<PyString>(
    CreatePyString(Collections::CreateStringWithCString("test"))
  );
  EXPECT_EQ(str->value.ToCppString(), "test");
}

TEST_F(PyStringTest, Add) {
  auto result = StringKlass::Self()->add(str1, str2);
  auto pystr = std::dynamic_pointer_cast<PyString>(result);
  EXPECT_EQ(pystr->value.ToCppString(), "helloworld");
}

TEST_F(PyStringTest, Repr) {
  auto result = StringKlass::Self()->repr(str1);
  auto pystr = std::dynamic_pointer_cast<PyString>(result);
  EXPECT_EQ(pystr->value.ToCppString(), "\'hello\'");
}

TEST_F(PyStringTest, Eq) {
  {
    auto result = StringKlass::Self()->eq(str1, str2);
    auto pybool = std::dynamic_pointer_cast<PyBoolean>(result);
    EXPECT_FALSE(pybool->value);
  }
  {
    auto result = StringKlass::Self()->eq(str1, str3);
    auto pybool = std::dynamic_pointer_cast<PyBoolean>(result);
    EXPECT_TRUE(pybool->value);
  }
}

TEST_F(PyStringTest, Boolean) {
  auto result = CreatePyString("hello");
  auto resultId =
    Collections::CreateIntegerWithU64(reinterpret_cast<uint64_t>(result.get()))
      .ToHexString();
  auto resultIdString = CreatePyString(resultId);
  resultIdString->PrintLine();
}

}  // namespace tensorslow::Object