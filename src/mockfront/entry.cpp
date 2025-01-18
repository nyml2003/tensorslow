#include "Collections/BytesHelper.h"
#include "Collections/IntegerHelper.h"
#include "Collections/StringHelper.h"
#include "Object/PyBytes.h"
#include "Object/PyCode.h"
#include "Object/PyInst.h"
#include "Object/PyInteger.h"
#include "Object/PyList.h"
#include "Object/PyNone.h"
#include "Object/PyObject.h"
#include "Object/PyString.h"

#include <functional>
#include <iostream>
#include <memory>

using namespace torchlight::Object;
using namespace torchlight::Collections;

String test_dir = CreateStringWithCString("/app/test/integration/");

String CreateFilename(const String& name) {
  // 当前目录下创建文件{name}.pyc
  return test_dir.Add(name).Add(CreateStringWithCString(".pyc"));
}

void createTask(
  const String& name,
  const std::function<void(const String&)>& task
) {
  task(name);
}

void CleanTestDir() {
  // 清空当前目录下的所有文件
  std::cout << "Cleaning test dir" << std::endl;
  std::cout << "rm -rf " << ToCppString(test_dir) << std::endl;
  system(("rm -rf " + ToCppString(test_dir)).c_str());
}

int main() {
  // createTask(
  //   CreateStringWithCString("Add_123_456"),
  //   [](const String& testname) {
  //     String filename = CreateFilename(testname);
  //     List<PyObjPtr> consts;
  //     consts.Push(
  //       CreatePyInteger(CreateIntegerWithString(CreateStringWithCString("123")))
  //     );
  //     consts.Push(
  //       CreatePyInteger(CreateIntegerWithString(CreateStringWithCString("456")))
  //     );
  //     PyListPtr constsObject = std::make_shared<PyList>(consts);

  //     List<PyObjPtr> instructions;
  //     instructions.Push(CreateLoadConst(0));
  //     instructions.Push(CreateLoadConst(1));
  //     instructions.Push(CreateBinaryAdd());
  //     instructions.Push(CreatePrint());
  //     PyListPtr instructionsObject = std::make_shared<PyList>(instructions);

  //     List<PyObjPtr> names;
  //     PyListPtr namesObject = std::make_shared<PyList>(names);

  //     List<PyObjPtr> varNames;
  //     PyListPtr varNamesObject = std::make_shared<PyList>(varNames);

  //     torchlight::Index nLocals = 0;

  //     PyCodePtr code = std::make_shared<PyCode>(
  //       instructionsObject->_serialize_(), constsObject, namesObject,
  //       varNamesObject, std::make_shared<PyString>(filename), nLocals
  //     );

  //     String codeStr =
  //       std::dynamic_pointer_cast<PyString>(code->repr())->Value();
  //     std::cout << ToCppString(codeStr) << std::endl;
  //     Bytes serialized =
  //       std::dynamic_pointer_cast<PyBytes>(code->_serialize_())->Value();
  //     Write(serialized, filename);
  //   }
  // );

  // createTask(
  //   CreateStringWithCString("Add_123_456_From_Var"),
  //   [](const String& testname) {
  //     String filename = CreateFilename(testname);
  //     List<PyObjPtr> consts;
  //     consts.Push(PyNone::Instance());
  //     consts.Push(std::make_shared<PyInteger>(
  //       CreateIntegerWithString(CreateStringWithCString("123"))
  //     ));
  //     consts.Push(std::make_shared<PyInteger>(
  //       CreateIntegerWithString(CreateStringWithCString("456"))
  //     ));
  //     PyListPtr constsObject = std::make_shared<PyList>(consts);

  //     List<PyObjPtr> instructions;
  //     instructions.Push(CreateLoadConst(1));
  //     instructions.Push(CreateStoreFast(0));
  //     instructions.Push(CreateLoadConst(2));
  //     instructions.Push(CreateStoreFast(1));

  //     instructions.Push(CreateLoadFast(0));
  //     instructions.Push(CreateLoadFast(1));
  //     instructions.Push(CreateBinaryAdd());
  //     instructions.Push(CreateStoreFast(2));
  //     instructions.Push(CreateLoadFast(2));
  //     instructions.Push(CreatePrint());
  //     PyListPtr instructionsObject = std::make_shared<PyList>(instructions);

  //     List<PyObjPtr> names;
  //     PyListPtr namesObject = std::make_shared<PyList>(names);

  //     List<PyObjPtr> varNames;
  //     varNames.Push(std::make_shared<PyString>(CreateStringWithCString("a")));
  //     varNames.Push(std::make_shared<PyString>(CreateStringWithCString("b")));
  //     varNames.Push(std::make_shared<PyString>(CreateStringWithCString("c")));
  //     PyListPtr varNamesObject = std::make_shared<PyList>(varNames);

  //     torchlight::Index nLocals = 3;

  //     PyCodePtr code = std::make_shared<PyCode>(
  //       instructionsObject->_serialize_(), constsObject, namesObject,
  //       varNamesObject, std::make_shared<PyString>(filename), nLocals
  //     );

  //     String codeStr =
  //       std::dynamic_pointer_cast<PyString>(code->repr())->Value();
  //     std::cout << ToCppString(codeStr) << std::endl;
  //     Bytes serialized =
  //       std::dynamic_pointer_cast<PyBytes>(code->_serialize_())->Value();
  //     Write(serialized, filename);
  //   }
  // );

  // createTask(
  //   CreateStringWithCString("add_from_1_to_10"),
  //   [](const String& testname) {
  //     String filename = CreateFilename(testname);
  //     List<PyObjPtr> consts;
  //     consts.Push(PyNone::Instance());
  //     consts.Push(std::make_shared<PyInteger>(
  //       CreateIntegerWithString(CreateStringWithCString("0"))
  //     ));
  //     consts.Push(std::make_shared<PyInteger>(
  //       CreateIntegerWithString(CreateStringWithCString("10"))
  //     ));
  //     consts.Push(std::make_shared<PyInteger>(
  //       CreateIntegerWithString(CreateStringWithCString("1"))
  //     ));
  //     PyListPtr constsObject = std::make_shared<PyList>(consts);

  //     List<PyObjPtr> instructions;
  //     instructions.Push(CreateLoadConst(1));  // instructions[0]
  //     instructions.Push(CreateStoreFast(0));  // instructions[1]

  //     instructions.Push(CreateLoadConst(1));  // instructions[2]
  //     instructions.Push(CreateStoreFast(1));  // instructions[3]

  //     instructions.Push(CreateLoadFast(0));   // instructions[4]
  //     instructions.Push(CreateLoadConst(2));  // instructions[5]
  //     instructions.Push(CreateCompareOp(CompareOp::LESS_THAN)
  //     );                                           // instructions[6]
  //     instructions.Push(CreatePopJumpIfFalse(13));  // instructions[7]

  //     instructions.Push(CreateLoadFast(1));   // instructions[8]
  //     instructions.Push(CreateLoadFast(0));   // instructions[9]
  //     instructions.Push(CreateBinaryAdd());   // instructions[10]
  //     instructions.Push(CreateStoreFast(1));  // instructions[11]

  //     instructions.Push(CreateLoadFast(0));   // instructions[12]
  //     instructions.Push(CreateLoadConst(3));  // instructions[13]
  //     instructions.Push(CreateBinaryAdd());   // instructions[14]
  //     instructions.Push(CreateStoreFast(0));  // instructions[15]

  //     instructions.Push(CreateLoadFast(0));   // instructions[16]
  //     instructions.Push(CreateLoadConst(2));  // instructions[17]
  //     instructions.Push(CreateCompareOp(CompareOp::LESS_THAN_EQUAL)
  //     );                                           // instructions[18]
  //     instructions.Push(CreatePopJumpIfTrue(-11));  // instructions[19]

  //     instructions.Push(CreateLoadFast(1));  // instructions[20]
  //     instructions.Push(CreatePrint());
  //     PyListPtr instructionsObject = std::make_shared<PyList>(instructions);

  //     List<PyObjPtr> names;
  //     PyListPtr namesObject = std::make_shared<PyList>(names);

  //     List<PyObjPtr> varNames;
  //     varNames.Push(std::make_shared<PyString>(CreateStringWithCString("i")));
  //     varNames.Push(std::make_shared<PyString>(CreateStringWithCString("sum")));
  //     PyListPtr varNamesObject = std::make_shared<PyList>(varNames);

  //     torchlight::Index nLocals = 2;

  //     PyCodePtr code = std::make_shared<PyCode>(
  //       instructionsObject->_serialize_(), constsObject, namesObject,
  //       varNamesObject, std::make_shared<PyString>(filename), nLocals
  //     );

  //     String codeStr =
  //       std::dynamic_pointer_cast<PyString>(code->repr())->Value();
  //     std::cout << ToCppString(codeStr) << std::endl;
  //     Bytes serialized =
  //       std::dynamic_pointer_cast<PyBytes>(code->_serialize_())->Value();
  //     Write(serialized, filename);
  //   }
  // );

  // createTask(
  //   CreateStringWithCString("make_function"),
  //   [](const String& testname) {
  //     String filename = CreateFilename(testname);
  //     // create the code object of the file
  //     PyCodePtr code;
  //     {
  //       List<PyObjPtr> consts;
  //       consts.Push(PyNone::Instance());
  //       consts.Push(std::make_shared<PyInteger>(
  //         CreateIntegerWithString(CreateStringWithCString("0"))
  //       ));
  //       consts.Push(std::make_shared<PyInteger>(
  //         CreateIntegerWithString(CreateStringWithCString("10"))
  //       ));
  //       consts.Push(std::make_shared<PyInteger>(
  //         CreateIntegerWithString(CreateStringWithCString("1"))
  //       ));
  //       PyListPtr constsObject = std::make_shared<PyList>(consts);

  //       List<PyObjPtr> instructions;
  //       instructions.Push(CreateLoadConst(1));  // instructions[0]
  //       instructions.Push(CreateStoreFast(0));  // instructions[1]

  //       instructions.Push(CreateLoadConst(1));  // instructions[2]
  //       instructions.Push(CreateStoreFast(1));  // instructions[3]

  //       instructions.Push(CreateLoadFast(0));   // instructions[4]
  //       instructions.Push(CreateLoadConst(2));  // instructions[5]
  //       instructions.Push(CreateCompareOp(CompareOp::LESS_THAN)
  //       );                                           // instructions[6]
  //       instructions.Push(CreatePopJumpIfFalse(13));  // instructions[7]

  //       instructions.Push(CreateLoadFast(1));   // instructions[8]
  //       instructions.Push(CreateLoadFast(0));   // instructions[9]
  //       instructions.Push(CreateBinaryAdd());   // instructions[10]
  //       instructions.Push(CreateStoreFast(1));  // instructions[11]

  //       instructions.Push(CreateLoadFast(0));   // instructions[12]
  //       instructions.Push(CreateLoadConst(3));  // instructions[13]
  //       instructions.Push(CreateBinaryAdd());   // instructions[14]
  //       instructions.Push(CreateStoreFast(0));  // instructions[15]

  //       instructions.Push(CreateLoadFast(0));   // instructions[16]
  //       instructions.Push(CreateLoadConst(2));  // instructions[17]
  //       instructions.Push(CreateCompareOp(CompareOp::LESS_THAN_EQUAL)
  //       );                                           // instructions[18]
  //       instructions.Push(CreatePopJumpIfTrue(-11));  // instructions[19]

  //       instructions.Push(CreateLoadFast(1));  // instructions[20]
  //       instructions.Push(CreateReturnValue());
  //       PyListPtr instructionsObject =
  //       std::make_shared<PyList>(instructions);

  //       List<PyObjPtr> names;
  //       PyListPtr namesObject = std::make_shared<PyList>(names);

  //       List<PyObjPtr> varNames;
  //       varNames.Push(std::make_shared<PyString>(CreateStringWithCString("i")));
  //       varNames.Push(std::make_shared<PyString>(CreateStringWithCString("sum"))
  //       );
  //       PyListPtr varNamesObject = std::make_shared<PyList>(varNames);

  //       torchlight::Index nLocals = 2;

  //       code = std::make_shared<PyCode>(
  //         instructionsObject->_serialize_(), constsObject, namesObject,
  //         varNamesObject,
  //         std::make_shared<PyString>(CreateStringWithCString("f")), nLocals
  //       );
  //     }
  //     List<PyObjPtr> consts;
  //     consts.Push(CreatePyNone());
  //     consts.Push(code);
  //     PyListPtr constsObject = std::make_shared<PyList>(consts);

  //     List<PyObjPtr> instructions;
  //     instructions.Push(CreateLoadConst(1));
  //     instructions.Push(CreateMakeFunction());
  //     instructions.Push(CreateStoreFast(0));
  //     instructions.Push(CreateLoadFast(0));
  //     instructions.Push(CreateCallFunction(0));
  //     instructions.Push(CreatePrint());
  //     PyListPtr instructionsObject = std::make_shared<PyList>(instructions);

  //     List<PyObjPtr> names;
  //     PyListPtr namesObject = std::make_shared<PyList>(names);

  //     List<PyObjPtr> varNames;
  //     varNames.Push(std::make_shared<PyString>(CreateStringWithCString("f")));
  //     PyListPtr varNamesObject = std::make_shared<PyList>(varNames);

  //     torchlight::Index nLocals = 1;
  //     PyCodePtr code2 = std::make_shared<PyCode>(
  //       instructionsObject->_serialize_(), constsObject, namesObject,
  //       varNamesObject, std::make_shared<PyString>(filename), nLocals
  //     );

  //     String codeStr =
  //       std::dynamic_pointer_cast<PyString>(code2->repr())->Value();
  //     std::cout << ToCppString(codeStr) << std::endl;

  //     Bytes serialized =
  //       std::dynamic_pointer_cast<PyBytes>(code2->_serialize_())->Value();
  //     Write(serialized, filename);
  //   }
  // );

  // createTask(
  //   CreateStringWithCString("fibonacci"),
  //   [](const String& testname) {
  //     String filename = CreateFilename(testname);
  //     // create the code object of the file
  //     PyCodePtr code;
  //     {
  //       List<PyObjPtr> consts;
  //       consts.Push(PyNone::Instance());
  //       consts.Push(std::make_shared<PyInteger>(
  //         CreateIntegerWithString(CreateStringWithCString("1"))
  //       ));
  //       consts.Push(std::make_shared<PyInteger>(
  //         CreateIntegerWithString(CreateStringWithCString("2"))
  //       ));
  //       PyListPtr constsObject = std::make_shared<PyList>(consts);

  //       List<PyObjPtr> instructions;
  //       instructions.Push(CreateLoadFast(0));                  //
  //       instructions[0] instructions.Push(CreateLoadConst(1)); //
  //       instructions[1] instructions.Push(CreateCompareOp(CompareOp::EQUAL));
  //       // instructions[2] instructions.Push(CreatePopJumpIfTrue(7)); //
  //       instructions[3]

  //       instructions.Push(CreateLoadFast(0));                  //
  //       instructions[4] instructions.Push(CreateLoadConst(2)); //
  //       instructions[5] instructions.Push(CreateCompareOp(CompareOp::EQUAL));
  //       // instructions[6] instructions.Push(CreatePopJumpIfFalse(3)); //
  //       instructions[7]

  //       instructions.Push(CreateLoadConst(1));   // instructions[8]
  //       instructions.Push(CreateReturnValue());  // instructions[9]

  //       instructions.Push(CreateLoadGlobal(0));  // instructions[10]
  //       instructions.Push(CreateLoadFast(0));
  //       instructions.Push(CreateLoadConst(1));
  //       instructions.Push(CreateBinarySubtract());
  //       instructions.Push(CreateCallFunction(1));

  //       instructions.Push(CreateLoadGlobal(0));
  //       instructions.Push(CreateLoadFast(0));
  //       instructions.Push(CreateLoadConst(2));
  //       instructions.Push(CreateBinarySubtract());
  //       instructions.Push(CreateCallFunction(1));

  //       instructions.Push(CreateBinaryAdd());
  //       instructions.Push(CreateReturnValue());
  //       PyListPtr instructionsObject =
  //       std::make_shared<PyList>(instructions);

  //       List<PyObjPtr> names;
  //       names.Add(std::make_shared<PyString>(CreateStringWithCString("fibonacci"
  //       )));
  //       PyListPtr namesObject = std::make_shared<PyList>(names);

  //       List<PyObjPtr> varNames;
  //       varNames.Push(std::make_shared<PyString>(CreateStringWithCString("n")));
  //       PyListPtr varNamesObject = std::make_shared<PyList>(varNames);

  //       torchlight::Index nLocals = 1;

  //       code = std::make_shared<PyCode>(
  //         instructionsObject->_serialize_(), constsObject, namesObject,
  //         varNamesObject,
  //         std::make_shared<PyString>(CreateStringWithCString("fibonacci")),
  //         nLocals
  //       );
  //     }
  //     List<PyObjPtr> consts;
  //     consts.Push(std::make_shared<PyInteger>(
  //       CreateIntegerWithString(CreateStringWithCString("1"))
  //     ));
  //     consts.Push(code);
  //     consts.Push(std::make_shared<PyString>(CreateStringWithCString("fibonacci")
  //     ));
  //     consts.Push(PyNone::Instance());
  //     PyListPtr constsObject = std::make_shared<PyList>(consts);

  //     List<PyObjPtr> names;
  //     names.Add(std::make_shared<PyString>(CreateStringWithCString("x")));
  //     names.Add(std::make_shared<PyString>(CreateStringWithCString("fibonacci"))
  //     );
  //     PyListPtr namesObject = std::make_shared<PyList>(names);

  //     torchlight::Index nLocals = 0;

  //     List<PyObjPtr> instructions;
  //     instructions.Push(CreateLoadConst(0));
  //     instructions.Push(CreateStoreName(0));
  //     instructions.Push(CreateLoadConst(1));
  //     instructions.Push(CreateMakeFunction());
  //     instructions.Push(CreateStoreName(1));
  //     instructions.Push(CreateLoadName(1));
  //     instructions.Push(CreateLoadName(0));
  //     instructions.Push(CreateCallFunction(1));
  //     instructions.Push(CreatePrint());

  //     PyListPtr instructionsObject = std::make_shared<PyList>(instructions);

  //     PyListPtr varNamesObject = std::make_shared<PyList>(List<PyObjPtr>());

  //     PyCodePtr code2 = std::make_shared<PyCode>(
  //       instructionsObject->_serialize_(), constsObject, namesObject,
  //       varNamesObject, std::make_shared<PyString>(filename), nLocals
  //     );

  //     String codeStr =
  //       std::dynamic_pointer_cast<PyString>(code2->repr())->Value();
  //     std::cout << ToCString(codeStr).get() << std::endl;

  //     Bytes serialized =
  //       std::dynamic_pointer_cast<PyBytes>(code2->_serialize_())->Value();
  //     Write(serialized, filename);
  //   }

  // );

  return 0;
}
