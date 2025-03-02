#include <memory>
#include "../test_default.h"

#include "../Collections/Collections.h"
#include "ByteCode/ByteCode.h"
#include "Object.h"
#include "Object/Klass.h"
#include "Object/ObjectHelper.h"
#include "Object/PyInteger.h"
#include "Object/PyString.h"

using namespace torchlight::Object;
using namespace torchlight::Collections;

class MROTest : public ::testing::Test {
 protected:
  void SetUp() override {
    // 初始化操作，如创建测试对象等
    BasicKlassLoad();
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
  DebugPrint(ComputeMro(typeG));
}