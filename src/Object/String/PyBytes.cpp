#include "Object/String/PyBytes.h"
#include "ByteCode/ByteCode.h"
#include "Collections/Iterator.h"
#include "Collections/String/BytesHelper.h"
#include "Collections/String/StringHelper.h"
#include "Object/Core/PyBoolean.h"
#include "Object/Core/PyObject.h"
#include "Object/String/PyString.h"

namespace torchlight::Object {

PyObjPtr BytesKlass::add(const PyObjPtr& lhs, const PyObjPtr& rhs) {
  if (!lhs->is<PyBytes>() || !rhs->is<PyBytes>()) {
    throw std::runtime_error("Bytes does not support add operation");
  }
  auto left = lhs->as<PyBytes>();
  auto right = rhs->as<PyBytes>();
  return CreatePyBytes(left->Value().Add(right->Value()));
}

PyObjPtr BytesKlass::_serialize_(const PyObjPtr& obj) {
  if (!obj->is<PyBytes>()) {
    throw std::runtime_error("PyBytes::_serialize_(): obj is not a bytes");
  }
  return CreatePyBytes(Collections::Serialize(Literal::BYTES)
                         .Add(Serialize(obj->as<PyBytes>()->Value())));
}

PyObjPtr BytesKlass::repr(const PyObjPtr& obj) {
  if (!obj->is<PyBytes>()) {
    throw std::runtime_error("PyBytes::repr(): obj is not a bytes");
  }
  auto bytes = obj->as<PyBytes>();
  Collections::List<Collections::String> reprs;
  auto bytesValue = bytes->Value().Value();
  for (auto it = Collections::Iterator<Byte>::Begin(bytesValue); !it.End();
       it.Next()) {
    reprs.Push(Collections::ReprByte(it.Get()));
  }
  return CreatePyString(Collections::CreateStringWithCString("b'").Add(
    Collections::Join(reprs, Collections::CreateStringWithCString(""))
      .Add(Collections::CreateStringWithCString("'"))
  ));
}

PyObjPtr BytesKlass::eq(const PyObjPtr& lhs, const PyObjPtr& rhs) {
  if (!lhs->is<PyBytes>() || !rhs->is<PyBytes>()) {
    throw std::runtime_error("Bytes does not support eq operation");
  }
  auto left = lhs->as<PyBytes>();
  auto right = rhs->as<PyBytes>();
  return CreatePyBoolean(left->Value().Equal(right->Value()));
}

}  // namespace torchlight::Object