#include "Runtime/Interpreter.h"
#include "ByteCode/PyCode.h"
#include "Collections/List.h"
#include "Function/PyFunction.h"
#include "Function/PyMethod.h"
#include "Function/PyNativeFunction.h"
#include "Object/Object.h"
#include "Object/ObjectHelper.h"
#include "Object/PyDictionary.h"
#include "Object/PyNone.h"
#include "Object/PyObject.h"
#include "Object/PyType.h"
#include "Runtime/Genesis.h"
#include "Runtime/PyFrame.h"

#include <memory>
#include <stdexcept>
namespace torchlight::Runtime {

Interpreter::Interpreter() {
  frame = nullptr;
  builtins = std::dynamic_pointer_cast<Object::PyDictionary>(Genesis());
}

Interpreter& Interpreter::Instance() {
  static Interpreter instance;
  return instance;
}

PyFramePtr Interpreter::CurrentFrame() const {
  return frame;
}

void Interpreter::SetFrame(const PyFramePtr& child) {
  frame = child;
}

void Interpreter::Run(const Object::PyCodePtr& code) {
  auto result = CreateModuleEntryFrame(code)->EvalWithDestory();
  if (!Object::IsType(result, Object::NoneKlass::Self())) {
    throw std::runtime_error("Module code did not return None");
  }
}

Object::PyObjPtr Interpreter::EvalConstructor(
  const Object::PyTypePtr& type,
  const Object::PyListPtr& arguments
) {
  return type->Owner()->allocateInstance(type, arguments);
}

Object::PyObjPtr Interpreter::EvalMethod(
  const Object::PyMethodPtr& func,
  const Object::PyListPtr& arguments
) {
  auto owner = func->Owner();
  auto function = func->Method();
  auto extendArguments = std::dynamic_pointer_cast<Object::PyList>(
    Object::CreatePyList({owner})->add(arguments)
  );
  return Eval(function, extendArguments);
}

Object::PyObjPtr Interpreter::EvalPyFunction(
  const Object::PyFunctionPtr& func,
  const Object::PyListPtr& arguments
) {
  return CreateFrameWithPyFunction(func, arguments)->EvalWithDestory();
}

Object::PyObjPtr Interpreter::EvalNativeFunction(
  const Object::PyNativeFunctionPtr& func,
  const Object::PyListPtr& arguments
) {
  return func->Call(arguments);
}

Object::PyObjPtr Interpreter::Eval(
  const Object::PyObjPtr& func,
  const Object::PyListPtr& arguments
) {
  if (Object::IsType(func, Object::MethodKlass::Self())) {
    auto method = std::dynamic_pointer_cast<Object::PyMethod>(func);
    return EvalMethod(method, arguments);
  }
  if (Object::IsType(func, Object::FunctionKlass::Self())) {
    auto pyFunction = std::dynamic_pointer_cast<Object::PyFunction>(func);
    return EvalPyFunction(pyFunction, arguments);
  }
  if (Object::IsType(func, Object::NativeFunctionKlass::Self())) {
    auto nativeFunction =
      std::dynamic_pointer_cast<Object::PyNativeFunction>(func);
    return EvalNativeFunction(nativeFunction, arguments);
  }
  if (Object::IsType(func, Object::TypeKlass::Self())) {
    auto type = std::dynamic_pointer_cast<Object::PyType>(func);
    return EvalConstructor(type, arguments);
  }
  throw std::runtime_error("Unknown function type");
}

Object::PyDictPtr Interpreter::Builtins() const {
  return builtins;
}

void Interpreter::BackToParentFrame() {
  if (!Object::IsType(frame, FrameKlass::Self())) {
    throw std::runtime_error("Cannot destroy non-frame object");
  }
  frame = std::dynamic_pointer_cast<PyFrame>(frame)->Caller();
}

}  // namespace torchlight::Runtime