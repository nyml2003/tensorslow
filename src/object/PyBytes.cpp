
#include "object/PyBytes.h"

#include "collections/Bytes.h"
#include "collections/String.h"

namespace torchlight::object {

PyBytes::PyBytes(collections::Bytes value)
  : PyObject(BytesKlass::Self()), value(std::move(value)) {}

[[nodiscard]] collections::Bytes PyBytes::Value() const {
  return value;
}

BytesKlass::BytesKlass()
  : Klass(collections::String("bytes")) {}

KlassPtr BytesKlass::Self() {
  static KlassPtr instance = std::make_shared<BytesKlass>();
  return instance;
}

}  // namespace torchlight::object