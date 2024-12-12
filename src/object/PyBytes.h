#ifndef TORCHLIGHT_OBJECT_PYBYTES_H
#define TORCHLIGHT_OBJECT_PYBYTES_H

#include "object/Klass.h"
#include "object/PyObject.h"
#include "object/common.h"

#include "collections/Bytes.h"

namespace torchlight::object {

class PyBytes : public PyObject {
 private:
  collections::Bytes value;

 public:
  explicit PyBytes(collections::Bytes value);

  [[nodiscard]] collections::Bytes Value() const;
};

using PyBytesPtr = std::shared_ptr<PyBytes>;

class BytesKlass : public Klass {
 public:
  explicit BytesKlass();

  static KlassPtr Self();
};

}  // namespace torchlight::object

#endif  // TORCHLIGHT_OBJECT_PYSTRING_H
