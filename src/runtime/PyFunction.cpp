#include "runtime/PyFunction.h"
#include "collections/impl/String.h"
#include "object/PyString.h"

namespace torchlight::runtime {

PyFunction::PyFunction(object::PyCodePtr code, object::PyDictPtr globals)
  : object::PyObject(FunctionKlass::Self()),
    code(std::move(code)),
    globals(std::move(globals)) {}

object::PyCodePtr PyFunction::Code() const {
  return code;
}

object::PyDictPtr& PyFunction::Globals() {
  return globals;
}

object::PyStrPtr PyFunction::Name() const {
  return code->Name();
}

FunctionKlass::FunctionKlass()
  : object::Klass(collections::CreateStringWithCString("function")) {}

object::KlassPtr FunctionKlass::Self() {
  static object::KlassPtr instance = std::make_shared<FunctionKlass>();
  return instance;
}

object::PyObjPtr FunctionKlass::repr(object::PyObjPtr self) {
  if (self->Klass() != Self()) {
    return nullptr;
  }
  auto function = std::dynamic_pointer_cast<PyFunction>(self);
  return std::make_shared<object::PyString>(
    collections::CreateStringWithCString("<function ")
      .Concat(function->Name()->Value())
      .Concat(collections::CreateStringWithCString(" at "))
      .Concat(collections::ToString(reinterpret_cast<uint64_t>(self.get())))
      .Concat(collections::CreateStringWithCString(">\n"))
  );
}

}  // namespace torchlight::runtime
