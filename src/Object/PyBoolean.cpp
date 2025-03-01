#include "Object/PyBoolean.h"
#include "ByteCode/ByteCode.h"
#include "Collections/BytesHelper.h"
#include "Object/PyBytes.h"
#include "Object/PyList.h"

namespace torchlight::Object {

PyObjPtr BooleanKlass::repr(const PyObjPtr& obj) {
  if (!obj->is<PyBoolean>()) {
    auto errorMessage = StringConcat(CreatePyList(
      {CreatePyString("AttributeError: '"), obj->Klass()->Name(),
       CreatePyString("' object has no attribute '__repr__'")}
    ));
    throw std::runtime_error(errorMessage->as<PyString>()->ToCppString());
  }
  auto boolean = obj->as<PyBoolean>();
  return boolean->Value() ? CreatePyString("True") : CreatePyString("False");
}

PyObjPtr BooleanKlass::eq(const PyObjPtr& lhs, const PyObjPtr& rhs) {
  if (!lhs->is<PyBoolean>() || !rhs->is<PyBoolean>()) {
    throw std::runtime_error("Boolean does not support eq operation");
  }
  auto left = lhs->as<PyBoolean>();
  auto right = rhs->as<PyBoolean>();
  return CreatePyBoolean(left->Value() == right->Value());
}

PyObjPtr BooleanKlass::_serialize_(const PyObjPtr& obj) {
  if (obj->Klass() != Self()) {
    throw std::runtime_error("PyBoolean::_serialize_(): obj is not a bool");
  }
  auto boolean = std::dynamic_pointer_cast<PyBoolean>(obj);
  if (boolean->Value()) {
    return CreatePyBytes(Collections::Serialize(Literal::TRUE));
  }
  return CreatePyBytes(Collections::Serialize(Literal::FALSE));
}

}  // namespace torchlight::Object