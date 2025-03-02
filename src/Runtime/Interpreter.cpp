#include "Runtime/Interpreter.h"
#include "ByteCode/PyCode.h"
#include "Function/PyFunction.h"
#include "Function/PyMethod.h"
#include "Function/PyNativeFunction.h"
#include "Object/Object.h"
#include "Object/PyDictionary.h"
#include "Object/PyNone.h"
#include "Object/PyObject.h"
#include "Object/PyType.h"
#include "Runtime/Genesis.h"
#include "Runtime/PyFrame.h"

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
  if (!result->is<Object::PyNone>()) {
    throw std::runtime_error("Module code did not return None");
  }
}

Object::PyObjPtr Interpreter::EvalConstructor(
  const Object::PyTypePtr& type,
  const Object::PyListPtr& arguments
) {
  return type->Owner()->construct(type, arguments);
}

Object::PyObjPtr Interpreter::EvalMethod(
  const Object::PyMethodPtr& func,
  const Object::PyListPtr& arguments
) {
  auto owner = func->Owner();
  auto function = func->Method();
  return Eval(function, arguments->Prepend(owner));
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
  if (func->is<Object::PyMethod>()) {
    auto method = func->as<Object::PyMethod>();
    return EvalMethod(method, arguments);
  }
  if (func->is<Object::PyFunction>()) {
    auto pyFunction = func->as<Object::PyFunction>();
    return EvalPyFunction(pyFunction, arguments);
  }
  if (func->is<Object::PyNativeFunction>()) {
    auto nativeFunction = func->as<Object::PyNativeFunction>();
    return EvalNativeFunction(nativeFunction, arguments);
  }
  if (func->is<Object::PyType>()) {
    auto type = func->as<Object::PyType>();
    return EvalConstructor(type, arguments);
  }
  throw std::runtime_error("Unknown function type");
}

Object::PyDictPtr Interpreter::Builtins() const {
  return builtins;
}

void Interpreter::BackToParentFrame() {
  if (!frame->is<PyFrame>()) {
    throw std::runtime_error("Cannot destroy non-frame object");
  }
  frame = std::dynamic_pointer_cast<PyFrame>(frame)->Caller();
}

}  // namespace torchlight::Runtime