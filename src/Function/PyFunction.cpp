#include "Function/PyFunction.h"
#include "Collections/StringHelper.h"
#include "Object/PyDictionary.h"
#include "Object/PyString.h"
#include "Object/PyType.h"

namespace torchlight::Object {

PyFunction::PyFunction(const PyObjPtr& code, const PyObjPtr& globals)
  : PyObject(FunctionKlass::Self()) {
  this->code = std::dynamic_pointer_cast<PyCode>(code);
  this->globals = std::dynamic_pointer_cast<PyDictionary>(globals);
}

PyObjPtr CreatePyFunction(const PyObjPtr& code, const PyObjPtr& globals) {
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

}  // namespace torchlight::Object
