#include "Runtime/Genesis.h"
#include "Function/ObjectHelper.h"
#include "Object/Container/PyDictionary.h"
#include "Object/Container/PyList.h"
#include "Object/Core/CoreHelper.h"
#include "Object/Core/PyBoolean.h"
#include "Object/Core/PyNone.h"
#include "Object/Core/PyObject.h"
#include "Object/Core/PyType.h"
#include "Object/Function/PyFunction.h"
#include "Object/Function/PyNativeFunction.h"
#include "Object/Number/PyFloat.h"
#include "Object/PyMatrix.h"
#include "Object/Runtime/PyFrame.h"
#include "Object/String/PyString.h"
#include "Runtime/Interpreter.h"

namespace torchlight::Runtime {

Object::PyDictPtr Genesis() {
  Object::BasicKlassLoad();
  Object::NativeClassLoad();
  auto builtins = Object::CreatePyDict()->as<Object::PyDictionary>();
  // 注册内置函数和类型
  builtins->Put(Object::CreatePyString("None"), Object::CreatePyNone());
  builtins->Put(Object::CreatePyString("True"), Object::CreatePyBoolean(true));
  builtins->Put(
    Object::CreatePyString("False"), Object::CreatePyBoolean(false)
  );

  // 注册内置函数
  builtins->Put(
    Object::CreatePyString("print"), CreatePyNativeFunction(Function::Print)
  );
  builtins->Put(
    Object::CreatePyString("len"), CreatePyNativeFunction(Function::Len)
  );
  builtins->Put(
    Object::CreatePyString("next"), CreatePyNativeFunction(Function::Next)
  );
  builtins->Put(
    Object::CreatePyString("iter"), CreatePyNativeFunction(Function::Iter)
  );
  builtins->Put(
    Object::CreatePyString("str"), CreatePyNativeFunction(Object::Str)
  );
  builtins->Put(
    Object::CreatePyString("repr"), CreatePyNativeFunction(Object::Repr)
  );
  builtins->Put(
    Object::CreatePyString("bool"), CreatePyNativeFunction(Object::Bool)
  );
  builtins->Put(
    Object::CreatePyString("id"), CreatePyNativeFunction(Function::Identity)
  );
  builtins->Put(
    Object::CreatePyString("__build_class__"),
    CreatePyNativeFunction(BuildClass)
  );
  builtins->Put(Object::CreatePyString("type"), CreatePyNativeFunction(Type));

  // 内置全局对象
  builtins->Put(
    Object::CreatePyString("Array"),
    Object::CreatePyNativeFunction(Object::Matrix)
  );
  builtins->Put(
    Object::CreatePyString("Eye"), Object::CreatePyNativeFunction(Object::Eye)
  );
  builtins->Put(
    Object::CreatePyString("Zeros"),
    Object::CreatePyNativeFunction(Object::Zeros)
  );
  builtins->Put(
    Object::CreatePyString("Ones"), Object::CreatePyNativeFunction(Object::Ones)
  );
  builtins->Put(
    Object::CreatePyString("Diag"),
    Object::CreatePyNativeFunction(Object::Diagnostic)
  );
  builtins->Put(
    Object::CreatePyString("Transpose"),
    Object::CreatePyNativeFunction(Object::Transpose)
  );
  builtins->Put(
    Object::CreatePyString("Reshape"),
    Object::CreatePyNativeFunction(Object::Reshape)
  );
  builtins->Put(
    Object::CreatePyString("Shape"),
    Object::CreatePyNativeFunction(Object::Shape)
  );
  builtins->Put(
    Object::CreatePyString("Where"),
    Object::CreatePyNativeFunction(Object::Where)
  );
  builtins->Put(
    Object::CreatePyString("Concatenate"),
    Object::CreatePyNativeFunction(Object::Concatenate)
  );
  builtins->Put(
    Object::CreatePyString("Ravel"),
    Object::CreatePyNativeFunction(Object::Ravel)
  );
  builtins->Put(
    Object::CreatePyString("Normal"),
    Object::CreatePyNativeFunction(Function::Normal)
  );
  builtins->Put(
    Object::CreatePyString("Shuffle"),
    Object::CreatePyNativeFunction(Function::Shuffle)
  );

  // 系统相关函数
  builtins->Put(
    Object::CreatePyString("input"), CreatePyNativeFunction(Function::Input)
  );
  builtins->Put(
    Object::CreatePyString("sleep"), CreatePyNativeFunction(Function::Sleep)
  );
  builtins->Put(
    Object::CreatePyString("randint"), CreatePyNativeFunction(Function::RandInt)
  );

  // 注册切片类型
  builtins->Put(
    Object::CreatePyString("slice"), Object::SliceKlass::Self()->Type()
  );

  // 注册内置类型
  builtins->Put(
    Object::CreatePyString("int"), Object::IntegerKlass::Self()->Type()
  );
  builtins->Put(
    Object::CreatePyString("float"), Object::FloatKlass::Self()->Type()
  );
  builtins->Put(
    Object::CreatePyString("list"), Object::ListKlass::Self()->Type()

  );
  builtins->Put(
    Object::CreatePyString("dict"), Object::DictionaryKlass::Self()->Type()

  );
  builtins->Put(
    Object::CreatePyString("object"),

    Object::ObjectKlass::Self()->Type()

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
  auto frame = Object::CreateFrameWithPyFunction(
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
  auto type = Object::CreatePyType(klass);
  return type;
}

Object::PyObjPtr Type(const Object::PyObjPtr& args) {
  CheckNativeFunctionArgumentsWithExpectedLength(args, 1);
  auto obj = args->getitem(Object::CreatePyInteger(0));
  return obj->Klass()->Type();
}

Object::PyObjPtr BuiltinMatrix() {
  auto matrixModuleKlass = Object::CreatePyKlass(
    Object::CreatePyString("matrix_module")->as<Object::PyString>(),
    Object::CreatePyDict()->as<Object::PyDictionary>(),
    Object::CreatePyList({Object::CreatePyType(Object::ObjectKlass::Self())})
      ->as<Object::PyList>()
  );
  matrixModuleKlass->AddAttribute(
    Object::CreatePyString("array")->as<Object::PyString>(),
    Object::CreatePyNativeFunction(Object::Matrix)
  );
  matrixModuleKlass->AddAttribute(
    Object::CreatePyString("eye")->as<Object::PyString>(),
    Object::CreatePyNativeFunction(Object::Eye)
  );
  matrixModuleKlass->AddAttribute(
    Object::CreatePyString("zeros")->as<Object::PyString>(),
    Object::CreatePyNativeFunction(Object::Zeros)
  );
  matrixModuleKlass->AddAttribute(
    Object::CreatePyString("ones")->as<Object::PyString>(),
    Object::CreatePyNativeFunction(Object::Ones)
  );
  matrixModuleKlass->AddAttribute(
    Object::CreatePyString("diag")->as<Object::PyString>(),
    Object::CreatePyNativeFunction(Object::Diagnostic)
  );
  matrixModuleKlass->AddAttribute(
    Object::CreatePyString("transpose")->as<Object::PyString>(),
    Object::CreatePyNativeFunction(Object::Transpose)
  );
  matrixModuleKlass->AddAttribute(
    Object::CreatePyString("reshape")->as<Object::PyString>(),
    Object::CreatePyNativeFunction(Object::Reshape)
  );
  matrixModuleKlass->AddAttribute(
    Object::CreatePyString("shape")->as<Object::PyString>(),
    Object::CreatePyNativeFunction(Object::Shape)
  );
  matrixModuleKlass->AddAttribute(
    Object::CreatePyString("where")->as<Object::PyString>(),
    Object::CreatePyNativeFunction(Object::Where)
  );
  matrixModuleKlass->AddAttribute(
    Object::CreatePyString("concatenate")->as<Object::PyString>(),
    Object::CreatePyNativeFunction(Object::Concatenate)
  );
  matrixModuleKlass->AddAttribute(
    Object::CreatePyString("ravel")->as<Object::PyString>(),
    Object::CreatePyNativeFunction(Object::Ravel)
  );
  matrixModuleKlass->AddAttribute(
    Object::CreatePyString("normal")->as<Object::PyString>(),
    Object::CreatePyNativeFunction(Function::Normal)
  );
  matrixModuleKlass->AddAttribute(
    Object::CreatePyString("shuffle")->as<Object::PyString>(),
    Object::CreatePyNativeFunction(Function::Shuffle)
  );
  auto matrixModule = std::make_shared<Object::PyObject>(matrixModuleKlass);
  return matrixModule;
}

}  // namespace torchlight::Runtime
