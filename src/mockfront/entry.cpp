

#include "collections/Bytes.h"
#include "collections/impl/Bytes.h"
#include "collections/impl/Integer.h"
#include "collections/impl/String.h"
#include "object/PyBytes.h"
#include "object/PyCode.h"
#include "object/PyInst.h"
#include "object/PyInteger.h"
#include "object/PyList.h"
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
using torchlight::object::CreateBinaryAdd;
using torchlight::object::CreateLoadConst;
using torchlight::object::CreatePrint;
using torchlight::object::PyBytes;
using torchlight::object::PyCode;
using torchlight::object::PyCodePtr;
using torchlight::object::PyInteger;
using torchlight::object::PyList;
using torchlight::object::PyListPtr;
using torchlight::object::PyObjPtr;
using torchlight::object::PyString;

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
  createTask(CreateStringWithCString("Add_123_456"), [](const String& testname) {
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

    PyCodePtr code = std::make_shared<PyCode>(
      instructionsObject->_serialize_(), constsObject, namesObject,
      std::make_shared<PyString>(filename)
    );

    String codeStr = std::dynamic_pointer_cast<PyString>(code->repr())->Value();
    std::cout << ToCString(codeStr).get() << std::endl;
    Bytes serialized =
      std::dynamic_pointer_cast<PyBytes>(code->_serialize_())->Value();
    Write(serialized, filename);
  });

  createTask(CreateStringWithCString("Add_1_2"), [](const String& testname) {
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

    PyCodePtr code = std::make_shared<PyCode>(
      instructionsObject->_serialize_(), constsObject, namesObject,
      std::make_shared<PyString>(filename)
    );

    String codeStr = std::dynamic_pointer_cast<PyString>(code->repr())->Value();
    std::cout << ToCString(codeStr).get() << std::endl;
    Bytes serialized =
      std::dynamic_pointer_cast<PyBytes>(code->_serialize_())->Value();
    Write(serialized, filename);
  });

  // createTask(CreateStringWithCString("Compare_1_2"), [](const String& name) {
  //   InstStream stream;
  //   stream.Add(torchlight::bytecode::CreateLoadConst(Bytes("1")));
  //   stream.Add(torchlight::bytecode::CreateLoadConst(Bytes("2")));
  //   stream.Add(torchlight::bytecode::CreateCompareOp(
  //     torchlight::bytecode::CompareOp::GREATER_THAN
  //   ));
  //   stream.Add(torchlight::bytecode::CreatePopJumpIfFalse(2));
  //   stream.Add(torchlight::bytecode::CreateLoadConst(Bytes("2")));
  //   stream.Add(torchlight::bytecode::CreatePrint());

  //   stream.Add(torchlight::bytecode::CreateLoadConst(Bytes("1")));
  //   stream.Add(torchlight::bytecode::CreatePrint());
  //   SerializeInstStream(stream, name);
  // });

  // createTask(CreateStringWithCString("Compare_2_1"), [](const String& name) {
  //   InstStream stream;
  //   stream.Add(torchlight::bytecode::CreateLoadConst(Bytes("2")));
  //   stream.Add(torchlight::bytecode::CreateLoadConst(Bytes("1")));
  //   stream.Add(torchlight::bytecode::CreateCompareOp(
  //     torchlight::bytecode::CompareOp::GREATER_THAN
  //   ));
  //   stream.Add(torchlight::bytecode::CreatePopJumpIfFalse(2));
  //   stream.Add(torchlight::bytecode::CreateLoadConst(Bytes("2")));
  //   stream.Add(torchlight::bytecode::CreatePrint());

  //   stream.Add(torchlight::bytecode::CreateLoadConst(Bytes("1")));
  //   stream.Add(torchlight::bytecode::CreatePrint());
  //   SerializeInstStream(stream, name);
  // });

  return 0;
}
