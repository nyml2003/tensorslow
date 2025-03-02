#ifndef TORCHLIGHT_OBJECT_PYBYTES_H
#define TORCHLIGHT_OBJECT_PYBYTES_H

#include "Collections/Bytes.h"
#include "Object/ObjectHelper.h"
#include "Object/PyString.h"

namespace torchlight::Object {

class BytesKlass : public Klass {
 public:
  explicit BytesKlass() = default;

  static KlassPtr Self() {
    static KlassPtr instance = std::make_shared<BytesKlass>();
    LoadClass(CreatePyString("bytes")->as<PyString>(), instance);
    ConfigureBasicAttributes(instance);
    return instance;
  }

  PyObjPtr add(const PyObjPtr& lhs, const PyObjPtr& rhs) override;

  PyObjPtr _serialize_(const PyObjPtr& obj) override;

  PyObjPtr repr(const PyObjPtr& obj) override;

  PyObjPtr eq(const PyObjPtr& lhs, const PyObjPtr& rhs) override;
};

class PyBytes : public PyObject {
 private:
  Collections::Bytes value;

 public:
  explicit PyBytes(Collections::Bytes value)
    : PyObject(BytesKlass::Self()), value(std::move(value)) {}

  [[nodiscard]] Collections::Bytes Value() const { return value; }
};

inline PyObjPtr CreatePyBytes(Collections::Bytes value) {
  return std::make_shared<PyBytes>(value);
}
inline PyObjPtr CreatePyBytes() {
  return std::make_shared<PyBytes>(Collections::Bytes());
}
using PyBytesPtr = std::shared_ptr<PyBytes>;
}  // namespace torchlight::Object

#endif  // TORCHLIGHT_OBJECT_PYSTRING_H
