#ifndef TORCHLIGHT_OBJECT_PYBYTES_H
#define TORCHLIGHT_OBJECT_PYBYTES_H

#include "collections/Bytes.h"
#include "object/Klass.h"
#include "object/PyObject.h"
#include "object/common.h"

namespace torchlight::object {

class PyBytes : public PyObject {
 private:
  collections::Bytes value;

 public:
  explicit PyBytes(collections::Bytes value);

  [[nodiscard]] collections::Bytes Value() const;
};

using PyBytesPtr = std::shared_ptr<PyBytes>;

PyBytesPtr CreateBytes(collections::Bytes value);

class BytesKlass : public Klass {
 public:
  explicit BytesKlass();

  static KlassPtr Self();

  PyObjPtr add(PyObjPtr lhs, PyObjPtr rhs) override;

  PyObjPtr _serialize_(PyObjPtr obj) override;

  PyObjPtr repr(PyObjPtr obj) override;
};

}  // namespace torchlight::object

#endif  // TORCHLIGHT_OBJECT_PYSTRING_H
