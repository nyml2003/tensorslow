
#include "ByteCode/ByteCode.h"
#include "ByteCode/PyCode.h"
#include "ByteCode/PyInst.h"
#include "Collections/IntegerHelper.h"
#include "Collections/StringHelper.h"
#include "MockFront/TaskRegister.h"
#include "MockFront/utils.h"
#include "Object/PyInteger.h"
#include "Object/PyList.h"
#include "Object/PyNone.h"
#include "Object/PyString.h"

namespace torchlight::MockFront {

class Task_fibonacci {
 public:
  static Object::PyCodePtr Run(const Collections::String& testname) {
    Object::PyCodePtr fibonacciCode;
    {
      // consts: (None, 1, 2)
      auto consts = Object::CreatePyList(
        {Object::CreatePyNone(),
         Object::CreatePyInteger(Collections::CreateIntegerWithString(
           Collections::CreateStringWithCString("1")
         )),
         Object::CreatePyInteger(Collections::CreateIntegerWithString(
           Collections::CreateStringWithCString("2")
         ))}
      );
      // varnames: ('n',)
      auto varnames = Object::CreatePyList(
        {Object::CreatePyString(Collections::CreateStringWithCString("n"))}
      );
      // names: ('fibonacci',)
      auto names = Object::CreatePyList({Object::CreatePyString(
        Collections::CreateStringWithCString("fibonacci")
      )});
      Index nLocals = 1;

      auto instructions = Object::CreatePyList(
        {Object::CreateLoadFast(0),
         Object::CreateLoadConst(1),
         Object::CreateCompareOp(Object::CompareOp::EQUAL),
         Object::CreatePopJumpIfTrue(5),
         Object::CreateLoadFast(0),
         Object::CreateLoadConst(2),
         Object::CreateCompareOp(Object::CompareOp::EQUAL),
         Object::CreatePopJumpIfFalse(3),
         Object::CreateLoadConst(1),
         Object::CreateReturnValue(),
         Object::CreateLoadGlobal(0),
         Object::CreateLoadFast(0),
         Object::CreateLoadConst(1),
         Object::CreateBinarySubtract(),
         Object::CreateCallFunction(1),
         Object::CreateLoadGlobal(0),
         Object::CreateLoadFast(0),
         Object::CreateLoadConst(2),
         Object::CreateBinarySubtract(),
         Object::CreateCallFunction(1),
         Object::CreateBinaryAdd(),
         Object::CreateReturnValue()}
      );
      fibonacciCode = std::make_shared<Object::PyCode>(
        instructions->_serialize_(), consts, names, varnames,
        Object::CreatePyString(Collections::CreateStringWithCString("fibonacci")
        ),
        nLocals
      );
    }

    auto consts = Object::CreatePyList(
      {fibonacciCode,
       Object::CreatePyString(Collections::CreateStringWithCString("fibonacci")
       ),
       Object::CreatePyInteger(Collections::CreateIntegerWithString(
         Collections::CreateStringWithCString("20")
       )),
       Object::CreatePyNone()}
    );
    auto names = Object::CreatePyList(
      {Object::CreatePyString(Collections::CreateStringWithCString("fibonacci")
       ),
       Object::CreatePyString(Collections::CreateStringWithCString("print"))}
    );
    auto varnames = Object::CreatePyList({});
    Index nLocals = 0;
    auto instructions = Object::CreatePyList(
      {Object::CreateLoadConst(0), Object::CreateLoadConst(1),
       Object::CreateMakeFunction(), Object::CreateStoreName(0),
       Object::CreateLoadName(1), Object::CreateLoadName(0),
       Object::CreateLoadConst(2), Object::CreateCallFunction(1),
       Object::CreateCallFunction(1), Object::CreatePopTop()}
    );
    auto code = std::make_shared<Object::PyCode>(
      instructions->_serialize_(), consts, names, varnames,
      Object::CreatePyString(CreateFilename(testname)), nLocals
    );
    return code;
  }
};

// REGISTER_TASK(Task_fibonacci, "fibonacci");

}  // namespace torchlight::MockFront