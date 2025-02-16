#include "Runtime/Genesis.h"
#include "Function/PyNativeFunction.h"
#include "Object/ObjectHelper.h"
#include "Object/PyBoolean.h"
#include "Object/PyMatrix.h"
#include "Object/PyNone.h"
#include "Runtime/PyFrame.h"
#include "Runtime/RuntimeHelper.h"

namespace torchlight::Runtime {

void RuntimeKlassLoad() {
  Runtime::FrameKlass::Self()->Initialize();
}

Object::PyObjPtr Genesis() {
  Object::BasicKlassLoad();
  RuntimeKlassLoad();
  auto builtins = Object::CreatePyDict();
  builtins->setitem(Object::CreatePyString("None"), Object::CreatePyNone());
  builtins->setitem(
    Object::CreatePyString("True"), Object::CreatePyBoolean(true)
  );
  builtins->setitem(
    Object::CreatePyString("False"), Object::CreatePyBoolean(false)
  );
  builtins->setitem(
    Object::CreatePyString("print"), CreatePyNativeFunction(Object::Print)
  );
  builtins->setitem(
    Object::CreatePyString("len"), CreatePyNativeFunction(Object::Len)
  );
  builtins->setitem(
    Object::CreatePyString("matrix"), CreatePyNativeFunction(Object::Matrix)
  );
  builtins->setitem(
    Object::CreatePyString("eye"), CreatePyNativeFunction(Object::Eye)
  );
  builtins->setitem(
    Object::CreatePyString("zeros"), CreatePyNativeFunction(Object::Zeros)
  );
  builtins->setitem(
    Object::CreatePyString("ones"), CreatePyNativeFunction(Object::Ones)
  );
  builtins->setitem(
    Object::CreatePyString("diag"), CreatePyNativeFunction(Object::Diagnostic)
  );
  builtins->setitem(
    Object::CreatePyString("transpose"),
    CreatePyNativeFunction(Object::Transpose)
  );
  builtins->setitem(
    Object::CreatePyString("reshape"), CreatePyNativeFunction(Object::Reshape)
  );
  builtins->setitem(
    Object::CreatePyString("__name__"), Object::CreatePyString("__main__")
  );
  builtins->setitem(
    Object::CreatePyString("randint"), CreatePyNativeFunction(RandInt)
  );
  builtins->setitem(
    Object::CreatePyString("sleep"), CreatePyNativeFunction(Sleep)
  );
  builtins->setitem(
    Object::CreatePyString("input"), CreatePyNativeFunction(Input)
  );
  return builtins;
}

}  // namespace torchlight::Runtime
