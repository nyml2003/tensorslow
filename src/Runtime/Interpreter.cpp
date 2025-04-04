#include "Runtime/Interpreter.h"
#include "Object/Container/PyDictionary.h"
#include "Object/Core/PyNone.h"
#include "Object/Core/PyObject.h"
#include "Object/Core/PyType.h"
#include "Object/Function/PyFunction.h"
#include "Object/Function/PyMethod.h"
#include "Object/Function/PyNativeFunction.h"
#include "Object/Object.h"
#include "Object/Runtime/PyCode.h"
#include "Object/Runtime/PyFrame.h"
#include "Runtime/Genesis.h"

namespace torchlight::Runtime {

Interpreter::Interpreter() {
  frame = nullptr;
  builtins = Genesis();
}

Interpreter& Interpreter::Instance() {
  static Interpreter instance;
  return instance;
}

Object::PyFramePtr Interpreter::CurrentFrame() const {
  return frame;
}

void Interpreter::SetFrame(const Object::PyFramePtr& child) {
  frame = child;
}

void Interpreter::Run(const Object::PyCodePtr& code) {
  auto result = CreateModuleEntryFrame(code)->EvalWithDestory();
  if (!result->is(Object::NoneKlass::Self())) {
    throw std::runtime_error("Module code did not return None");
  }
}

Object::PyObjPtr Interpreter::EvalConstructor(
  const Object::PyTypePtr& type,
  const Object::PyListPtr& arguments
) {
  return type->Owner()->init(type, arguments);
}

Object::PyObjPtr Interpreter::EvalMethod(
  const Object::PyMethodPtr& func,
  const Object::PyListPtr& arguments
) {
  auto owner = func->Owner();
  auto function = func->Method();
  return Eval(function, arguments->Prepend(owner)->as<Object::PyList>());
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
  if (func->is(Object::MethodKlass::Self())) {
    auto method = func->as<Object::PyMethod>();
    return EvalMethod(method, arguments);
  }
  if (func->is(Object::FunctionKlass::Self())) {
    auto pyFunction = func->as<Object::PyFunction>();
    return EvalPyFunction(pyFunction, arguments);
  }
  if (func->is(Object::NativeFunctionKlass::Self())) {
    auto nativeFunction = func->as<Object::PyNativeFunction>();
    return EvalNativeFunction(nativeFunction, arguments);
  }
  if (func->is(Object::TypeKlass::Self())) {
    auto type = func->as<Object::PyType>();
    return EvalConstructor(type, arguments);
  }
  throw std::runtime_error("Unknown function type");
}

Object::PyDictPtr Interpreter::Builtins() const {
  return builtins;
}

void Interpreter::BackToParentFrame() {
  if (!frame->is(Object::FrameKlass::Self())) {
    throw std::runtime_error("Cannot destroy non-frame object");
  }
  frame = frame->as<Object::PyFrame>()->Caller();
}

}  // namespace torchlight::Runtime