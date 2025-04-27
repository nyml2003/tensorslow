#include "Object/String/PyBytes.h"
#include "ByteCode/ByteCode.h"
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
  Collections::StringBuilder literal(Collections::Serialize(Literal::BYTES));
  literal.Append(Collections::Serialize(bytes->Value()));
  return CreatePyBytes(literal.ToString());
}

PyObjPtr BytesKlass::repr(const PyObjPtr& obj) {
  if (!obj->is(Self())) {
    throw std::runtime_error("PyBytes::repr(): obj is not a bytes");
  }
  auto bytes = obj->as<PyBytes>();
  const auto& byteArray = bytes->Value();
  Collections::StringBuilder sb(Collections::CreateStringWithCString("b'"));
  for (Index i = 0; i < byteArray.GetCodeUnitCount(); i++) {
    auto byte = byteArray.GetCodeUnit(i);
    sb.Append(Collections::ReprByte(byte));
  }
  sb.Append(Collections::CreateStringWithCString("'"));
  return CreatePyString(sb.ToString());
}

}  // namespace torchlight::Object