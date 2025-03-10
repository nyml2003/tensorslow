#include "Runtime/Genesis.h"
#include "Function/PyFunction.h"
#include "Function/PyNativeFunction.h"
#include "Object/ObjectHelper.h"
#include "Object/PyBoolean.h"
#include "Object/PyDictionary.h"
#include "Object/PyFloat.h"
#include "Object/PyList.h"
#include "Object/PyMatrix.h"
#include "Object/PyNone.h"
#include "Object/PyObject.h"
#include "Object/PyString.h"
#include "Object/PyType.h"
#include "Runtime/Interpreter.h"
#include "Runtime/PyFrame.h"

namespace torchlight::Runtime {

Object::PyObjPtr Genesis() {
  Object::BasicKlassLoad();
  auto builtins = Object::CreatePyDict()->as<Object::PyDictionary>();
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
    Object::CreatePyString("__build_class__"),
    CreatePyNativeFunction(BuildClass)
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
    Object::CreatePyString("int"), std::dynamic_pointer_cast<Object::PyObject>(
                                     Object::IntegerKlass::Self()->Type()
                                   )
  );
  builtins->setitem(
    Object::CreatePyString("float"),
    std::dynamic_pointer_cast<Object::PyObject>(
      Object::FloatKlass::Self()->Type()
    )
  );
  builtins->setitem(
    Object::CreatePyString("str"), std::dynamic_pointer_cast<Object::PyObject>(
                                     Object::StringKlass::Self()->Type()
                                   )
  );
  builtins->setitem(
    Object::CreatePyString("list"), std::dynamic_pointer_cast<Object::PyObject>(
                                      Object::ListKlass::Self()->Type()
                                    )
  );
  builtins->setitem(
    Object::CreatePyString("dict"), std::dynamic_pointer_cast<Object::PyObject>(
                                      Object::DictionaryKlass::Self()->Type()
                                    )
  );
  builtins->setitem(
    Object::CreatePyString("object"),
    std::dynamic_pointer_cast<Object::PyObject>(
      Object::ObjectKlass::Self()->Type()
    )
  );
  builtins->setitem(
    Object::CreatePyString("type"), CreatePyNativeFunction(Type)
  );
  builtins->Put(
    Object::CreatePyString("input"), CreatePyNativeFunction(Object::Input)
  );
  builtins->Put(
    Object::CreatePyString("sleep"), CreatePyNativeFunction(Object::Sleep)
  );
  builtins->Put(
    Object::CreatePyString("randint"), CreatePyNativeFunction(Object::RandInt)
  );
  builtins->Put(
    Object::CreatePyString("slice"), Object::SliceKlass::Self()->Type()
  );
  return builtins;
}

Object::PyObjPtr BuildClass(const Object::PyObjPtr& args) {
  auto argList = args->as<Object::PyList>();
  // 解析参数：函数、类名和基类
  auto function = argList->GetItem(0)->as<Object::PyFunction>();
  auto name = argList->GetItem(1)->as<Object::PyString>();
  auto bases = argList->GetItem(2)->as<Object::PyList>();

  // 创建执行环境
  auto globals = function->Globals();
  auto preFrame = Runtime::Interpreter::Instance().CurrentFrame();
  auto _name_ = globals->getitem(Object::CreatePyString("__name__"));
  // 保存当前帧
  // 创建新帧并执行类定义函数
  auto frame = Runtime::CreateFrameWithPyFunction(
    function, Object::CreatePyList({})->as<Object::PyList>()
  );
  auto result = frame->Eval();
  Runtime::Interpreter::Instance().BackToParentFrame();
  if (!result->is<Object::PyNone>()) {
    throw std::runtime_error("Class definition failed");
  }
  // 获取执行结果
  auto class_dict = frame->CurrentLocals();
  // 创建新的类型对象
  auto type_name =
    StringConcat(
      Object::CreatePyList({_name_, Object::CreatePyString("."), name})
    )
      ->as<Object::PyString>();
  auto klass = Object::CreatePyKlass(type_name, class_dict, bases);
  return Object::CreatePyType(klass);
}

Object::PyObjPtr Type(const Object::PyObjPtr& args) {
  CheckNativeFunctionArgumentsWithExpectedLength(args, 1);
  auto obj = args->getitem(Object::CreatePyInteger(0));
  return obj->Klass()->Type();
}

}  // namespace torchlight::Runtime
