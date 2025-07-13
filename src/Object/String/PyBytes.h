#ifndef TENSORSLOW_OBJECT_PYBYTES_H
#define TENSORSLOW_OBJECT_PYBYTES_H

#include "Object/Core/CoreHelper.h"
#include "Object/String/PyString.h"

namespace tensorslow::Object {

class BytesKlass : public KlassBase<BytesKlass> {
 public:
  explicit BytesKlass() = default;



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
};
class PyBytes;
using PyBytesPtr = std::shared_ptr<PyBytes>;
class PyBytes : public PyObject {
 private:
  Collections::String value;

 public:
  explicit PyBytes(Collections::String&& value)
    : PyObject(BytesKlass::Self()), value(std::move(value)) {}

  [[nodiscard]] const Collections::String& Value() { return value; }
};

inline PyBytesPtr CreatePyBytes(Collections::String&& value) {
  return std::make_shared<PyBytes>(std::move(value));
}

}  // namespace tensorslow::Object

#endif  // TENSORSLOW_OBJECT_PYSTRING_H
