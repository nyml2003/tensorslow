#include "Collections/StringHelper.h"
#include "Object/PyString.h"
#include "Runtime/PyFunction.h"

namespace torchlight::Runtime {

PyFunction::PyFunction(Object::PyCodePtr code, Object::PyDictPtr globals)
  : Object::PyObject(FunctionKlass::Self()),
    code(std::move(code)),
    globals(std::move(globals)) {}

Object::PyCodePtr PyFunction::Code() const {
  return code;
}

Object::PyDictPtr& PyFunction::Globals() {
  return globals;
}

Object::PyStrPtr PyFunction::Name() const {
  return code->Name();
}

FunctionKlass::FunctionKlass()
  : Object::Klass(Collections::CreateStringWithCString("function")) {}

Object::KlassPtr FunctionKlass::Self() {
  static Object::KlassPtr instance = std::make_shared<FunctionKlass>();
  return instance;
}

Object::PyObjPtr FunctionKlass::repr(Object::PyObjPtr self) {
  if (self->Klass() != Self()) {
    throw std::runtime_error("Function does not support repr operation");
  }
  auto function = std::dynamic_pointer_cast<PyFunction>(self);
  return std::make_shared<Object::PyString>(
    Collections::CreateStringWithCString("<function ")
      .Add(function->Name()->Value())
      .Add(Collections::CreateStringWithCString(" at "))
      .Add(Collections::ToString(reinterpret_cast<uint64_t>(self.get())))
      .Add(Collections::CreateStringWithCString(">\n"))
  );
}

}  // namespace torchlight::Runtime
