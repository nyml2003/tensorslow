

#include "collections/Bytes.h"
#include "collections/impl/Bytes.h"
#include "collections/impl/Integer.h"
#include "collections/impl/String.h"
#include "object/PyBytes.h"
#include "object/PyCode.h"
#include "object/PyInst.h"
#include "object/PyInteger.h"
#include "object/PyList.h"
#include "object/PyNone.h"
#include "object/PyObject.h"
#include "object/PyString.h"

#include <functional>
#include <iostream>
#include <memory>

using torchlight::collections::Byte;
using torchlight::collections::Bytes;
using torchlight::collections::CreateIntegerWithString;
using torchlight::collections::CreateStringWithCString;
using torchlight::collections::List;
using torchlight::collections::String;
using torchlight::collections::Write;
using namespace torchlight::object;

String test_dir = CreateStringWithCString("/app/test/integration/");

String CreateFilename(const String& name) {
  // 当前目录下创建文件{name}.pyc
  return test_dir.Concat(name).Concat(CreateStringWithCString(".pyc"));
}

void createTask(
  const String& name,
  const std::function<void(const String&)>& task
) {
  task(name);
}

int main() {
  createTask(
    CreateStringWithCString("Add_123_456"),
    [](const String& testname) {
      String filename = CreateFilename(testname);
      List<PyObjPtr> consts;
      consts.Add(std::make_shared<PyInteger>(
        CreateIntegerWithString(CreateStringWithCString("123"))
      ));
      consts.Add(std::make_shared<PyInteger>(
        CreateIntegerWithString(CreateStringWithCString("456"))
      ));
      PyListPtr constsObject = std::make_shared<PyList>(consts);

      List<PyObjPtr> instructions;
      instructions.Add(CreateLoadConst(0));
      instructions.Add(CreateLoadConst(1));
      instructions.Add(CreateBinaryAdd());
      instructions.Add(CreatePrint());
      PyListPtr instructionsObject = std::make_shared<PyList>(instructions);

      List<PyObjPtr> names;
      PyListPtr namesObject = std::make_shared<PyList>(names);

      List<PyObjPtr> varNames;
      PyListPtr varNamesObject = std::make_shared<PyList>(varNames);

      PyCodePtr code = std::make_shared<PyCode>(
        instructionsObject->_serialize_(), constsObject, namesObject,
        varNamesObject, std::make_shared<PyString>(filename)
      );

      String codeStr =
        std::dynamic_pointer_cast<PyString>(code->repr())->Value();
      std::cout << ToCString(codeStr).get() << std::endl;
      Bytes serialized =
        std::dynamic_pointer_cast<PyBytes>(code->_serialize_())->Value();
      Write(serialized, filename);
    }
  );

  createTask(
    CreateStringWithCString("Add_123_456_From_Var"),
    [](const String& testname) {
      String filename = CreateFilename(testname);
      List<PyObjPtr> consts;
      consts.Add(PyNone::Instance());
      consts.Add(std::make_shared<PyInteger>(
        CreateIntegerWithString(CreateStringWithCString("123"))
      ));
      consts.Add(std::make_shared<PyInteger>(
        CreateIntegerWithString(CreateStringWithCString("456"))
      ));
      PyListPtr constsObject = std::make_shared<PyList>(consts);

      List<PyObjPtr> instructions;
      instructions.Add(CreateLoadConst(1));
      instructions.Add(CreateStoreFast(0));
      instructions.Add(CreateLoadConst(2));
      instructions.Add(CreateStoreFast(1));

      instructions.Add(CreateLoadFast(0));
      instructions.Add(CreateLoadFast(1));
      instructions.Add(CreateBinaryAdd());
      instructions.Add(CreateStoreFast(2));
      instructions.Add(CreateLoadFast(2));
      instructions.Add(CreatePrint());
      PyListPtr instructionsObject = std::make_shared<PyList>(instructions);

      List<PyObjPtr> names;
      PyListPtr namesObject = std::make_shared<PyList>(names);

      List<PyObjPtr> varNames;
      varNames.Add(std::make_shared<PyString>(CreateStringWithCString("a")));
      varNames.Add(std::make_shared<PyString>(CreateStringWithCString("b")));
      varNames.Add(std::make_shared<PyString>(CreateStringWithCString("c")));
      PyListPtr varNamesObject = std::make_shared<PyList>(varNames);

      PyCodePtr code = std::make_shared<PyCode>(
        instructionsObject->_serialize_(), constsObject, namesObject,
        varNamesObject, std::make_shared<PyString>(filename)
      );

      String codeStr =
        std::dynamic_pointer_cast<PyString>(code->repr())->Value();
      std::cout << ToCString(codeStr).get() << std::endl;
      Bytes serialized =
        std::dynamic_pointer_cast<PyBytes>(code->_serialize_())->Value();
      Write(serialized, filename);
    }
  );

  createTask(
    CreateStringWithCString("add_from_1_to_10"),
    [](const String& testname) {
      String filename = CreateFilename(testname);
      List<PyObjPtr> consts;
      consts.Add(PyNone::Instance());
      consts.Add(std::make_shared<PyInteger>(
        CreateIntegerWithString(CreateStringWithCString("0"))
      ));
      consts.Add(std::make_shared<PyInteger>(
        CreateIntegerWithString(CreateStringWithCString("10"))
      ));
      consts.Add(std::make_shared<PyInteger>(
        CreateIntegerWithString(CreateStringWithCString("1"))
      ));
      PyListPtr constsObject = std::make_shared<PyList>(consts);

      List<PyObjPtr> instructions;
      instructions.Add(CreateLoadConst(1));  // instructions[0]
      instructions.Add(CreateStoreFast(0));  // instructions[1]

      instructions.Add(CreateLoadConst(1));  // instructions[2]
      instructions.Add(CreateStoreFast(1));  // instructions[3]

      instructions.Add(CreateLoadFast(0));   // instructions[4]
      instructions.Add(CreateLoadConst(2));  // instructions[5]
      instructions.Add(CreateCompareOp(CompareOp::LESS_THAN)
      );                                           // instructions[6]
      instructions.Add(CreatePopJumpIfFalse(13));  // instructions[7]

      instructions.Add(CreateLoadFast(1));   // instructions[8]
      instructions.Add(CreateLoadFast(0));   // instructions[9]
      instructions.Add(CreateBinaryAdd());   // instructions[10]
      instructions.Add(CreateStoreFast(1));  // instructions[11]

      instructions.Add(CreateLoadFast(0));   // instructions[12]
      instructions.Add(CreateLoadConst(3));  // instructions[13]
      instructions.Add(CreateBinaryAdd());   // instructions[14]
      instructions.Add(CreateStoreFast(0));  // instructions[15]

      instructions.Add(CreateLoadFast(0));   // instructions[16]
      instructions.Add(CreateLoadConst(2));  // instructions[17]
      instructions.Add(CreateCompareOp(CompareOp::LESS_THAN_EQUAL)
      );                                           // instructions[18]
      instructions.Add(CreatePopJumpIfTrue(-11));  // instructions[19]

      instructions.Add(CreateLoadFast(1));  // instructions[20]
      instructions.Add(CreatePrint());
      PyListPtr instructionsObject = std::make_shared<PyList>(instructions);

      List<PyObjPtr> names;
      PyListPtr namesObject = std::make_shared<PyList>(names);

      List<PyObjPtr> varNames;
      varNames.Add(std::make_shared<PyString>(CreateStringWithCString("i")));
      varNames.Add(std::make_shared<PyString>(CreateStringWithCString("sum")));
      PyListPtr varNamesObject = std::make_shared<PyList>(varNames);

      PyCodePtr code = std::make_shared<PyCode>(
        instructionsObject->_serialize_(), constsObject, namesObject,
        varNamesObject, std::make_shared<PyString>(filename)
      );

      String codeStr =
        std::dynamic_pointer_cast<PyString>(code->repr())->Value();
      std::cout << ToCString(codeStr).get() << std::endl;
      Bytes serialized =
        std::dynamic_pointer_cast<PyBytes>(code->_serialize_())->Value();
      Write(serialized, filename);
    }
  );

  return 0;
}
