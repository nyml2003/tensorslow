#ifndef TORCHLIGHT_OBJECT_PYBYTES_H
#define TORCHLIGHT_OBJECT_PYBYTES_H

#include <iostream>
#include "Collections/String/Bytes.h"
#include "Function/BuiltinFunction.h"
#include "Object/Core/CoreHelper.h"
#include "Object/String/PyString.h"

namespace torchlight::Object {

class BytesKlass : public Klass {
 public:
  explicit BytesKlass() = default;

  static KlassPtr Self() {
    static KlassPtr instance = std::make_shared<BytesKlass>();
    return instance;
  }

  void Initialize() override {
    if (this->isInitialized) {
      return;
    }
    LoadClass(CreatePyString("bytes")->as<PyString>(), Self());
    ConfigureBasicAttributes(Self());
    this->isInitialized = true;
  }

  PyObjPtr _serialize_(const PyObjPtr& obj) override;

  PyObjPtr repr(const PyObjPtr& obj) override;

  PyObjPtr eq(const PyObjPtr& lhs, const PyObjPtr& rhs) override;
};
class PyBytes;
using PyBytesPtr = std::shared_ptr<PyBytes>;
class PyBytes : public PyObject {
 private:
  Collections::Bytes value;

 public:
  explicit PyBytes(Collections::Bytes value)
    : PyObject(BytesKlass::Self()), value(std::move(value)) {}

  [[nodiscard]] Collections::Bytes& Value() { return value; }

  void Concat(const PyBytesPtr& other);
  bool Equals(const PyBytesPtr& other) const;
};

inline PyBytesPtr CreatePyBytes(Collections::Bytes&& value) {
  return std::make_shared<PyBytes>(std::move(value));
}
inline PyBytesPtr CreatePyBytes() {
  return std::make_shared<PyBytes>(Collections::Bytes());
}

}  // namespace torchlight::Object

#endif  // TORCHLIGHT_OBJECT_PYSTRING_H
