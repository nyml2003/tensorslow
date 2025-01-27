#include <memory>
#include "../test_default.h"

#include "../Collections/Collections.h"
#include "ByteCode/ByteCode.h"
#include "Object.h"

using namespace torchlight::Object;
using namespace torchlight::Collections;

namespace torchlight::Object {

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
  PyStrPtr str = std::dynamic_pointer_cast<PyString>(CreatePyString(Collections::CreateStringWithCString("test")));
  EXPECT_EQ(str->Value(), Collections::CreateStringWithCString("test"));
}

TEST_F(PyStringTest, Add) {
  auto result = StringKlass::Self()->add(str1, str2);
  auto pystr = std::dynamic_pointer_cast<PyString>(result);
  EXPECT_EQ(pystr->Value(), Collections::CreateStringWithCString("helloworld"));
}

TEST_F(PyStringTest, Repr) {
  auto result = StringKlass::Self()->repr(str1);
  auto pystr = std::dynamic_pointer_cast<PyString>(result);
  EXPECT_EQ(pystr->Value(), Collections::CreateStringWithCString("\"hello\""));
}

TEST_F(PyStringTest, Eq) {
  {
    auto result = StringKlass::Self()->eq(str1, str2);
    auto pybool = std::dynamic_pointer_cast<PyBoolean>(result);
    EXPECT_FALSE(pybool->Value());
  }
  {
    auto result = StringKlass::Self()->eq(str1, str3);
    auto pybool = std::dynamic_pointer_cast<PyBoolean>(result);
    EXPECT_TRUE(pybool->Value());
  }
}

}  // namespace torchlight::Object