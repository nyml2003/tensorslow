#include "Collections/StringHelper.h"
#include "Function/PyFunction.h"
#include "Object/PyDictionary.h"
#include "Object/PyString.h"
#include "Object/PyType.h"

namespace torchlight::Object {

PyFunction::PyFunction(PyObjPtr code, PyObjPtr globals)
  : PyObject(FunctionKlass::Self()) {
  this->code = std::dynamic_pointer_cast<PyCode>(code);
  this->globals = std::dynamic_pointer_cast<PyDictionary>(globals);
}

PyObjPtr CreatePyFunction(PyObjPtr code, PyObjPtr globals) {
  return std::make_shared<PyFunction>(code, globals);
}

PyCodePtr PyFunction::Code() const {
  return code;
}

PyDictPtr& PyFunction::Globals() {
  return globals;
}

PyStrPtr PyFunction::Name() const {
  return code->Name();
}

FunctionKlass::FunctionKlass() = default;

void FunctionKlass::Initialize() {
  SetType(CreatePyType(Self()));
  SetName(CreatePyString("function"));
  SetAttributes(CreatePyDict());
  Klass::Initialize();
}

KlassPtr FunctionKlass::Self() {
  static KlassPtr instance = std::make_shared<FunctionKlass>();
  return instance;
}

PyObjPtr FunctionKlass::repr(PyObjPtr self) {
  if (self->Klass() != Self()) {
    throw std::runtime_error("Function does not support repr operation");
  }
  auto function = std::dynamic_pointer_cast<PyFunction>(self);
  return std::make_shared<PyString>(
    Collections::CreateStringWithCString("<function ")
      .Add(function->Name()->Value())
      .Add(Collections::CreateStringWithCString(" at "))
      .Add(Collections::ToString(reinterpret_cast<uint64_t>(self.get())))
      .Add(Collections::CreateStringWithCString(">\n"))
  );
}

}  // namespace torchlight::Object
