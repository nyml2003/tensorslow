#include "collections/String.h"
#include "object/Klass.h"
#include "object/PyBytes.h"
#include "object/PyString.h"
#include "runtime/PyCode.h"

namespace torchlight::runtime {

PyCode::PyCode(object::PyBytesPtr byteCodes)
  : object::PyObject(CodeKlass::Self()), byteCodes(std::move(byteCodes)) {}

[[nodiscard]] object::PyBytesPtr PyCode::ByteCodes() const {
  return byteCodes;
}

CodeKlass::CodeKlass()
  : object::Klass(collections::String("code")
    ) {}

object::KlassPtr CodeKlass::Self() {
  static object::KlassPtr instance = std::make_shared<CodeKlass>();
  return instance;
}

}  // namespace torchlight::runtime