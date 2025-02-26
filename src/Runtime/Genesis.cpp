#include "Runtime/Genesis.h"

#include "Function/PyFunction.h"
#include "Function/PyNativeFunction.h"
#include "Object/Klass.h"
#include "Object/ObjectHelper.h"
#include "Object/PyBoolean.h"
#include "Object/PyFloat.h"
#include "Object/PyInteger.h"
#include "Object/PyList.h"
#include "Object/PyMatrix.h"
#include "Object/PyNone.h"
#include "Object/PyObject.h"
#include "Object/PyType.h"
#include "Runtime/Interpreter.h"
#include "Runtime/PyFrame.h"
#include "Runtime/RuntimeHelper.h"

#include <memory>

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

  return builtins;
}

Object::PyObjPtr BuildClass(const Object::PyObjPtr& args) {
  // 解析参数：函数、类名和基类
  auto function = std::dynamic_pointer_cast<Object::PyFunction>(
    args->getitem(Object::CreatePyInteger(0))
  );
  auto name = std::dynamic_pointer_cast<Object::PyString>(
    args->getitem(Object::CreatePyInteger(1))
  );

  // 创建执行环境
  auto globals = function->Globals();

  // 保存当前帧
  // 创建新帧并执行类定义函数
  auto frame = Runtime::CreateFrameWithPyFunction(
    function,
    std::dynamic_pointer_cast<Object::PyList>(Object::CreatePyList({}))
  );
  auto result = frame->Eval();
  Runtime::Interpreter::Instance().BackToParentFrame();
  if (!Object::IsType(result, Object::NoneKlass::Self())) {
    throw std::runtime_error("Class definition failed");
  }
  // 获取执行结果
  auto class_dict = frame->CurrentLocals();
  auto base =
    std::dynamic_pointer_cast<Object::PyList>(Object::CreatePyList({}));
  // 创建新的类型对象
  auto type = Object::CreatePyKlass(name, class_dict, base);
  type->Initialize();
  return Object::CreatePyType(type);
}

}  // namespace torchlight::Runtime
