#ifndef TORCHLIGHT_RUNTIME_PYCODE_H
#define TORCHLIGHT_RUNTIME_PYCODE_H

#include "collections/List.h"
#include "object/Klass.h"
#include "object/PyBytes.h"
#include "object/PyObject.h"
#include "object/common.h"

namespace torchlight::object {

using collections::Byte;
using collections::Bytes;
using collections::List;
using collections::String;

class PyCode : public PyObject {
  friend class CodeKlass;

 private:
  PyBytesPtr byteCode;
  PyListPtr instructions;
  PyListPtr consts;
  PyListPtr names;
  PyListPtr varNames;
  PyStrPtr filename;

 public:
  explicit PyCode(
    const PyObjPtr& byteCodes,
    const PyObjPtr& consts,
    const PyObjPtr& names,
    const PyObjPtr& varNames,
    const PyObjPtr& filename
  );

  [[nodiscard]] PyListPtr Instructions();

  void SetInstructions(const PyListPtr& insts);

  PyBytesPtr ByteCode() const;

  [[nodiscard]] PyListPtr Consts() const;

  [[nodiscard]] PyListPtr Names() const;

  [[nodiscard]] PyStrPtr Filename() const;

  [[nodiscard]] PyListPtr VarNames() const;
};

using PyCodePtr = std::shared_ptr<PyCode>;

class CodeKlass : public object::Klass {
 public:
  explicit CodeKlass();
  static object::KlassPtr Self();

  PyObjPtr repr(PyObjPtr self) override;

  PyObjPtr _serialize_(PyObjPtr self) override;
};

}  // namespace torchlight::object

#endif  // TORCHLIGHT_RUNTIME_PYCODE_H
