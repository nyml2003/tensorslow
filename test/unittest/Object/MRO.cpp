#include <memory>
#include "../test_default.h"

#include "../Collections/Collections.h"
#include "ByteCode/ByteCode.h"
#include "Function/BuiltinFunction.h"
#include "Object.h"
#include "Object/Core/Klass.h"
#include "Object/Number/PyInteger.h"
#include "Object/String/PyString.h"

using namespace tensorslow::Object;
using namespace tensorslow::Collections;

class MROTest : public ::testing::Test {
 protected:
  void SetUp() override {
    // 初始化操作，如创建测试对象等
    LoadBootstrapClasses();
    LoadRuntimeSupportClasses();
  }
};

TEST_F(MROTest, Init) {
  auto typeO =
    CreatePyType(
      CreatePyKlass(
        CreatePyString("O")->as<PyString>(), CreatePyDict()->as<PyDictionary>(),
        CreatePyList({CreatePyType(ObjectKlass::Self())->as<PyType>()})
          ->as<PyList>()
      )
    )
      ->as<PyType>();
  auto typeA = CreatePyType(CreatePyKlass(
                              CreatePyString("A")->as<PyString>(),
                              CreatePyDict()->as<PyDictionary>(),
                              CreatePyList({typeO})->as<PyList>()
                            ))
                 ->as<PyType>();
  auto typeB = CreatePyType(CreatePyKlass(
                              CreatePyString("B")->as<PyString>(),
                              CreatePyDict()->as<PyDictionary>(),
                              CreatePyList({typeO})->as<PyList>()
                            ))
                 ->as<PyType>();
  auto typeC = CreatePyType(CreatePyKlass(
                              CreatePyString("C")->as<PyString>(),
                              CreatePyDict()->as<PyDictionary>(),
                              CreatePyList({typeO})->as<PyList>()
                            ))
                 ->as<PyType>();
  auto typeE = CreatePyType(CreatePyKlass(
                              CreatePyString("E")->as<PyString>(),
                              CreatePyDict()->as<PyDictionary>(),
                              CreatePyList({typeA, typeB})->as<PyList>()
                            ))
                 ->as<PyType>();
  auto typeF = CreatePyType(CreatePyKlass(
                              CreatePyString("F")->as<PyString>(),
                              CreatePyDict()->as<PyDictionary>(),
                              CreatePyList({typeB, typeC})->as<PyList>()
                            ))

                 ->as<PyType>();
  auto typeG = CreatePyType(CreatePyKlass(
                              CreatePyString("G")->as<PyString>(),
                              CreatePyDict()->as<PyDictionary>(),
                              CreatePyList({typeE, typeF})->as<PyList>()
                            ))
                 ->as<PyType>();
  auto mroOfG = ComputeMro(typeG);
  /**
   * MRO of G: ['G', 'E', 'A', 'F', 'B', 'C', 'O', 'object']
MRO of E: ['E', 'A', 'B', 'O', 'object']
MRO of F: ['F', 'B', 'C', 'O', 'object']


   */
  EXPECT_STREQ(
    mroOfG->GetItem(0)->str()->as<PyString>()->ToCppString().c_str(),
    "<class 'G'>"
  );
  EXPECT_STREQ(
    mroOfG->GetItem(1)->str()->as<PyString>()->ToCppString().c_str(),
    "<class 'E'>"
  );
  EXPECT_STREQ(
    mroOfG->GetItem(2)->str()->as<PyString>()->ToCppString().c_str(),
    "<class 'A'>"
  );
  EXPECT_STREQ(
    mroOfG->GetItem(3)->str()->as<PyString>()->ToCppString().c_str(),
    "<class 'F'>"
  );
  EXPECT_STREQ(
    mroOfG->GetItem(4)->str()->as<PyString>()->ToCppString().c_str(),
    "<class 'B'>"
  );
  EXPECT_STREQ(
    mroOfG->GetItem(5)->str()->as<PyString>()->ToCppString().c_str(),
    "<class 'C'>"
  );
  EXPECT_STREQ(
    mroOfG->GetItem(6)->str()->as<PyString>()->ToCppString().c_str(),
    "<class 'O'>"
  );
  EXPECT_STREQ(
    mroOfG->GetItem(7)->str()->as<PyString>()->ToCppString().c_str(),
    "<class 'object'>"
  );
}