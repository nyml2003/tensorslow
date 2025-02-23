#ifndef TORCHLIGHT_OBJECT_PYBYTES_H
#define TORCHLIGHT_OBJECT_PYBYTES_H

#include "Collections/Bytes.h"
#include "Object/Klass.h"
#include "Object/PyObject.h"

namespace torchlight::Object {

class PyBytes : public PyObject {
 private:
  Collections::Bytes value;

 public:
  explicit PyBytes(Collections::Bytes value);

  [[nodiscard]] Collections::Bytes Value() const;
};

class BytesKlass : public Klass {
 public:
  explicit BytesKlass();

  static KlassPtr Self();

  PyObjPtr add(const PyObjPtr& lhs, const PyObjPtr& rhs) override;

  PyObjPtr _serialize_(const PyObjPtr& obj) override;

  PyObjPtr repr(const PyObjPtr& obj) override;

  PyObjPtr eq(const PyObjPtr& lhs, const PyObjPtr& rhs) override;

  void Initialize() override;
};

PyObjPtr CreatePyBytes(Collections::Bytes value);
PyObjPtr CreatePyBytes();
using PyBytesPtr = std::shared_ptr<PyBytes>;
}  // namespace torchlight::Object

#endif  // TORCHLIGHT_OBJECT_PYSTRING_H
