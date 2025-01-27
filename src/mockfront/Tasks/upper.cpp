
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

class Task_Upper {
 public:
  static Object::PyCodePtr Run(const Collections::String& testname) {
    auto constsObject = Object::CreatePyList(
      {Object::CreatePyString(Collections::CreateStringWithCString(
         "this is a string with lower case characters"
       )),
       Object::CreatePyNone()}
    );
    /*
    bytecode:
  1           0 LOAD_CONST               0 ('this is a string with lower case
  characters') 2 STORE_NAME               0 (lower_string)

  bytecode:
  1           0 LOAD_CONST               0 ('this is a string with lower case
  characters') 2 STORE_NAME               0 (lower_string)

  2           4 LOAD_NAME                0 (lower_string)
              6 LOAD_ATTR                1 (upper)
              8 CALL_FUNCTION            0
             10 STORE_NAME               2 (upper_string)

  3          12 LOAD_NAME                3 (print)
             14 LOAD_NAME                2 (upper_string)
             16 CALL_FUNCTION            1
             18 POP_TOP
             20 LOAD_CONST               1 (None)
             22 RETURN_VALUE*/
    auto instructionsObject = Object::CreatePyList(
      {Object::CreateLoadConst(0), Object::CreateStoreName(0),
       Object::CreateLoadName(0), Object::CreateLoadAttr(1),
       Object::CreateCallFunction(0), Object::CreateStoreName(2),
       Object::CreateLoadName(3), Object::CreateLoadName(2),
       Object::CreateCallFunction(1), Object::CreatePopTop()}
    );

    auto namesObject = Object::CreatePyList(
      {Object::CreatePyString(
         Collections::CreateStringWithCString("lower_string")
       ),
       Object::CreatePyString(Collections::CreateStringWithCString("upper")),
       Object::CreatePyString(
         Collections::CreateStringWithCString("upper_string")
       ),
       Object::CreatePyString(Collections::CreateStringWithCString("print"))}
    );
    auto varNamesObject = Object::CreatePyList({});

    torchlight::Index nLocals = 0;

    Object::PyCodePtr code = std::make_shared<Object::PyCode>(
      instructionsObject->_serialize_(), constsObject, namesObject,
      varNamesObject, Object::CreatePyString(CreateFilename(testname)), nLocals
    );
    return code;
  }
};

// REGISTER_TASK(Task_Upper, "Upper");

}  // namespace torchlight::MockFront