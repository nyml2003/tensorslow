#include "Tools/Tools.h"  // 包含你的代码文件
#include "gtest/gtest.h"
using namespace torchlight;

class ParameterTest : public ::testing::Test {
 protected:
  Parameter param;

  ParameterTest()
    : param(
        "name",
        [](const std::string& value) {
          return value.size() > 0;  // 示例验证函数：非空字符串
        },
        "default"
      ) {}
};

TEST_F(ParameterTest, ValidateNonEmpty) {
  EXPECT_TRUE(param.validate("non_empty_value"));
}

TEST_F(ParameterTest, ValidateEmpty) {
  EXPECT_FALSE(param.validate(""));
}

class SchemaTest : public ::testing::Test {
 protected:
  Schema schema;
  Parameter param1;

  SchemaTest()
    : param1(
        "option1",
        [](const std::string& value) {
          return value == "value1";  // 示例验证函数
        },
        "default1"
      ) {
    schema.Add(param1);
  }
};

TEST_F(SchemaTest, FindExistingParameter) {
  Parameter p = schema.Find("option1");
  EXPECT_EQ(p.Name(), "option1");
  EXPECT_EQ(p.DefaultValue(), "default1");
}

TEST_F(SchemaTest, FindNonExistingParameter) {
  EXPECT_THROW(schema.Find("non_existing"), std::out_of_range);
}

class ArgsHelperTest : public ::testing::Test {
 protected:
  Schema schema;
  ArgsHelper& processor;
  char** argv;
  int argc;

  ArgsHelperTest() : processor(ArgsHelper::Instance()) {
    // 添加示例参数
    schema.Add(Parameter(
      "option1",
      [](const std::string& value) {
        return value == "valid";  // 只接受 "valid" 作为有效值
      },
      "valid"
    ));

    processor.SetSchema(schema);
  }

  void SetUp() override {
    // 模拟 argc 和 argv
    argv = new char*[2];
    argv[0] = const_cast<char*>("test_program");
    argv[1] = const_cast<char*>("--option1=valid");
    argc = 2;
  }

  void TearDown() override { delete[] argv; }
};

TEST_F(ArgsHelperTest, ValidInput) {
  // 测试有效输入
  ASSERT_NO_THROW(processor.Accept(argc, argv))
    << "Valid input failed validation.";
}

TEST_F(ArgsHelperTest, InvalidOption) {
  // 测试无效选项
  argv[1] = const_cast<char*>("--invalid_option=value");
  EXPECT_THROW(processor.Accept(argc, argv), std::out_of_range);
}

TEST_F(ArgsHelperTest, InvalidValue) {
  // 测试无效值
  argv[1] = const_cast<char*>("--option1=invalid_value");
  EXPECT_THROW(processor.Accept(argc, argv), std::invalid_argument);
}

TEST_F(ArgsHelperTest, DefaultValueHandling) {
  // 测试未提供值时处理默认值的情况
  argv[1] = const_cast<char*>("--option1");
  ASSERT_NO_THROW(processor.Accept(argc, argv));
}