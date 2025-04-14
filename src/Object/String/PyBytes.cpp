#include "Object/String/PyBytes.h"
#include "ByteCode/ByteCode.h"
#include "Collections/Iterator.h"
#include "Collections/String/BytesHelper.h"
#include "Collections/String/StringHelper.h"
#include "Object/Container/PyList.h"
#include "Object/Core/PyBoolean.h"
#include "Object/Core/PyObject.h"
#include "Object/String/PyString.h"

namespace torchlight::Object {

PyObjPtr BytesKlass::_serialize_(const PyObjPtr& obj) {
  if (!obj->is(Self())) {
    throw std::runtime_error("PyBytes::_serialize_(): obj is not a bytes");
  }
  auto bytes = obj->as<PyBytes>();
  auto literal = Collections::Serialize(Literal::BYTES);
  literal.Concat(Collections::Serialize(bytes->Value()));
  return CreatePyBytes(std::move(literal));
}

PyObjPtr BytesKlass::repr(const PyObjPtr& obj) {
  if (!obj->is(Self())) {
    throw std::runtime_error("PyBytes::repr(): obj is not a bytes");
  }
  auto bytes = obj->as<PyBytes>();
  const Collections::List<Byte>& byteArray = bytes->Value().Value();
  Collections::StringBuilder sb(Collections::CreateStringWithCString("b'"));
  for (Index i = 0; i < byteArray.Size(); i++) {
    auto byte = byteArray[i];
    sb.Append(Collections::ReprByte(byte));
  }
  sb.Append(Collections::CreateStringWithCString("'"));
  return CreatePyString(sb.ToString());
}

PyObjPtr BytesKlass::eq(const PyObjPtr& lhs, const PyObjPtr& rhs) {
  if (!lhs->is(BytesKlass::Self()) || !rhs->is(BytesKlass::Self())) {
    throw std::runtime_error("Bytes does not support eq operation");
  }
  auto left = lhs->as<PyBytes>();
  auto right = rhs->as<PyBytes>();
  return CreatePyBoolean(left->Equals(right));
}

void PyBytes::Concat(const PyBytesPtr& other) {
  value.Concat(other->Value());
}

bool PyBytes::Equals(const PyBytesPtr& other) const {
  return value.Equal(other->Value());
}

}  // namespace torchlight::Object