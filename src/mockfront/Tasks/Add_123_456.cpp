
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

class Task_Add_123_456 {
 public:
  static Object::PyCodePtr Run(const Collections::String& testname) {
    auto constsObject = Object::CreatePyList(
      {Object::CreatePyInteger(Collections::CreateIntegerWithString(
         Collections::CreateStringWithCString("123")
       )),
       Object::CreatePyInteger(Collections::CreateIntegerWithString(
         Collections::CreateStringWithCString("456")
       )),
       Object::CreatePyNone()}
    );

    auto instructionsObject = Object::CreatePyList(
      {Object::CreateLoadConst(0), Object::CreateStoreName(0),
       Object::CreateLoadConst(1), Object::CreateStoreName(1),
       Object::CreateLoadName(2), Object::CreateLoadName(0),
       Object::CreateLoadName(1), Object::CreateBinaryAdd(),
       Object::CreateCallFunction(1), Object::CreatePopTop()}
    );

    auto namesObject = Object::CreatePyList(
      {Object::CreatePyString(Collections::CreateStringWithCString("a")),
       Object::CreatePyString(Collections::CreateStringWithCString("b")),
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

REGISTER_TASK(Task_Add_123_456, "Add_123_456");

}  // namespace torchlight::MockFront