#include "Object/PyBytes.h"
#include "ByteCode/ByteCode.h"
#include "Collections/BytesHelper.h"
#include "Collections/Iterator.h"
#include "Collections/StringHelper.h"
#include "Object/PyBoolean.h"
#include "Object/PyObject.h"
#include "Object/PyString.h"

namespace torchlight::Object {

PyObjPtr BytesKlass::add(const PyObjPtr& lhs, const PyObjPtr& rhs) {
  if (lhs->Klass() != Self() || rhs->Klass() != Self()) {
    throw std::runtime_error("PyBytes::add(): lhs or rhs is not a bytes");
  }
  auto left = std::dynamic_pointer_cast<PyBytes>(lhs);
  auto right = std::dynamic_pointer_cast<PyBytes>(rhs);
  return CreatePyBytes(left->Value().Add(right->Value()));
}

PyObjPtr BytesKlass::_serialize_(const PyObjPtr& obj) {
  if (obj->Klass() != Self()) {
    throw std::runtime_error("PyBytes::_serialize_(): obj is not a bytes");
  }
  return CreatePyBytes(
    Collections::Serialize(Literal::BYTES)
      .Add(Serialize(std::dynamic_pointer_cast<PyBytes>(obj)->Value()))
  );
}

PyObjPtr BytesKlass::repr(const PyObjPtr& obj) {
  if (obj->Klass() != Self()) {
    throw std::runtime_error("PyBytes::repr(): obj is not a bytes");
  }
  auto bytes = std::dynamic_pointer_cast<PyBytes>(obj);
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
  if (lhs->Klass() != Self() || rhs->Klass() != Self()) {
    return CreatePyBoolean(false);
  }
  auto left = std::dynamic_pointer_cast<PyBytes>(lhs);
  auto right = std::dynamic_pointer_cast<PyBytes>(rhs);
  return CreatePyBoolean(left->Value().Equal(right->Value()));
}

}  // namespace torchlight::Object