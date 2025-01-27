#include "ByteCode/PyInst.h"
#include "Collections/StringHelper.h"
#include "Function/PyFunction.h"
#include "Function/PyMethod.h"
#include "Function/PyNativeFunction.h"
#include "Object/Klass.h"
#include "Object/PyBoolean.h"
#include "Object/PyDictionary.h"
#include "Object/PyNone.h"
#include "Object/PyObject.h"
#include "Object/PyString.h"
#include "Object/PyType.h"
#include "Runtime/Genesis.h"
#include "Runtime/PyFrame.h"

namespace torchlight::Runtime {

Object::PyObjPtr Genesis() {
  Object::StringKlass::Self()->Initialize();
  Object::BooleanKlass::Self()->Initialize();
  Object::NoneKlass::Self()->Initialize();
  Object::ListKlass::Self()->Initialize();
  Object::DictionaryKlass::Self()->Initialize();
  Object::TypeKlass::Self()->Initialize();
  Object::MethodKlass::Self()->Initialize();
  Object::NativeFunctionKlass::Self()->Initialize();
  Object::FunctionKlass::Self()->Initialize();
  Object::InstKlass::Self()->Initialize();
  Object::CodeKlass::Self()->Initialize();
  Runtime::FrameKlass::Self()->Initialize();


  auto builtins = Object::CreatePyDict();
  builtins->setitem(
    Object::CreatePyString(Collections::CreateStringWithCString("None")),
    Object::CreatePyNone()
  );
  builtins->setitem(
    Object::CreatePyString(Collections::CreateStringWithCString("True")),
    Object::CreatePyBoolean(true)
  );
  builtins->setitem(
    Object::CreatePyString(Collections::CreateStringWithCString("False")),
    Object::CreatePyBoolean(false)
  );
  builtins->setitem(
    Object::CreatePyString(Collections::CreateStringWithCString("print")),
    CreatePyNativeFunction(Object::Print)
  );
  return builtins;
}

}  // namespace torchlight::Runtime
