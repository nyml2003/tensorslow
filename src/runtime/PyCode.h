#ifndef TORCHLIGHT_RUNTIME_PYCODE_H
#define TORCHLIGHT_RUNTIME_PYCODE_H

#include "object/Klass.h"
#include "object/PyBytes.h"
#include "object/common.h"

namespace torchlight::runtime {

class PyCode : public object::PyObject {
 private:
  object::PyBytesPtr byteCodes;

 public:
  explicit PyCode(object::PyBytesPtr byteCodes);

  [[nodiscard]] object::PyBytesPtr ByteCodes() const;
};

using PyCodePtr = std::shared_ptr<PyCode>;

class CodeKlass : public object::Klass {
 public:
  explicit CodeKlass();
  static object::KlassPtr Self();
};

}  // namespace torchlight::runtime

#endif  // TORCHLIGHT_RUNTIME_PYCODE_H
