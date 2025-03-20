#include "Object/PyInteger.h"
#include "ByteCode/ByteCode.h"
#include "Collections/BytesHelper.h"
#include "Collections/IntegerHelper.h"
#include "Object/PyBoolean.h"
#include "Object/PyBytes.h"
#include "Object/PyFloat.h"
#include "Object/PyList.h"
#include "Object/PyString.h"
#include "Object/PyType.h"

namespace torchlight::Object {

PyObjPtr CreatePyInteger(Collections::Integer value) {
  return std::make_shared<PyInteger>(value);
}

PyObjPtr CreatePyInteger(uint64_t value) {
  return std::make_shared<PyInteger>(Collections::CreateIntegerWithU64(value));
}

void IntegerKlass::Initialize() {
  LoadClass(CreatePyString("int")->as<PyString>(), Self());
  ConfigureBasicAttributes(Self());
}

PyObjPtr IntegerKlass::init(const PyObjPtr& klass, const PyObjPtr& args) {
  if (klass->as<PyType>()->Owner() != Self()) {
    throw std::runtime_error("PyInteger::init(): klass is not an integer");
  }
  auto argList = args->as<PyList>();
  if (argList->Length() == 0) {
    return CreatePyInteger(Collections::CreateIntegerZero());
  }
  if (argList->Length() != 1) {
    throw std::runtime_error(
      "PyInteger::init(): args must be a list with one element"
    );
  }
  auto value = argList->GetItem(0);
  if (value->is<PyInteger>()) {
    return value;
  }
  if (value->is<PyString>()) {
    auto str = std::dynamic_pointer_cast<PyString>(value);
    return CreatePyInteger(Collections::CreateIntegerWithString(str->Value()));
  }
  throw std::runtime_error("PyInteger::init(): value is not an integer");
}

PyObjPtr IntegerKlass::add(const PyObjPtr& lhs, const PyObjPtr& rhs) {
  if (lhs->Klass() != Self() || rhs->Klass() != Self()) {
    throw std::runtime_error("PyInteger::add(): lhs or rhs is not an integer");
  }
  auto left = std::dynamic_pointer_cast<PyInteger>(lhs);
  auto right = std::dynamic_pointer_cast<PyInteger>(rhs);
  return CreatePyInteger(left->value.Add(right->value));
}

PyObjPtr IntegerKlass::sub(const PyObjPtr& lhs, const PyObjPtr& rhs) {
  if (lhs->Klass() != Self() || rhs->Klass() != Self()) {
    throw std::runtime_error("PyInteger::sub(): lhs or rhs is not an integer");
  }
  auto left = std::dynamic_pointer_cast<PyInteger>(lhs);
  auto right = std::dynamic_pointer_cast<PyInteger>(rhs);
  return CreatePyInteger(left->value.Subtract(right->value));
}

PyObjPtr IntegerKlass::mul(const PyObjPtr& lhs, const PyObjPtr& rhs) {
  if (lhs->Klass() != Self() || rhs->Klass() != Self()) {
    throw std::runtime_error("PyInteger::mul(): lhs or rhs is not an integer");
  }
  auto left = std::dynamic_pointer_cast<PyInteger>(lhs);
  auto right = std::dynamic_pointer_cast<PyInteger>(rhs);
  return CreatePyInteger(left->value.Multiply(right->value));
}

PyObjPtr IntegerKlass::floordiv(const PyObjPtr& lhs, const PyObjPtr& rhs) {
  if (lhs->Klass() != Self() || rhs->Klass() != Self()) {
    throw std::runtime_error("PyInteger::div(): lhs or rhs is not an integer");
  }
  auto left = std::dynamic_pointer_cast<PyInteger>(lhs);
  auto right = std::dynamic_pointer_cast<PyInteger>(rhs);
  return CreatePyInteger(left->value.Divide(right->value));
}

PyObjPtr IntegerKlass::truediv(const PyObjPtr& lhs, const PyObjPtr& rhs) {
  if (!lhs->is<PyInteger>() || !rhs->is<PyInteger>()) {
    throw std::runtime_error("PyInteger::div(): lhs or rhs is not an integer");
  }
  auto left = static_cast<double>(lhs->as<PyInteger>()->ToU64());
  auto right = static_cast<double>(rhs->as<PyInteger>()->ToU64());
  return CreatePyFloat(left / right);
}

PyObjPtr IntegerKlass::mod(const PyObjPtr& lhs, const PyObjPtr& rhs) {
  if (lhs->Klass() != Self() || rhs->Klass() != Self()) {
    throw std::runtime_error("PyInteger::mod(): lhs or rhs is not an integer");
  }
  auto left = std::dynamic_pointer_cast<PyInteger>(lhs);
  auto right = std::dynamic_pointer_cast<PyInteger>(rhs);
  return CreatePyInteger(left->value.Modulo(right->value));
}

PyObjPtr IntegerKlass::pow(const PyObjPtr& lhs, const PyObjPtr& rhs) {
  if (lhs->Klass() != Self() || rhs->Klass() != Self()) {
    throw std::runtime_error("PyInteger::pow(): lhs or rhs is not an integer");
  }
  auto left = std::dynamic_pointer_cast<PyInteger>(lhs);
  auto right = std::dynamic_pointer_cast<PyInteger>(rhs);
  return CreatePyInteger(left->value.Power(right->value));
}

PyObjPtr IntegerKlass::pos(const PyObjPtr& obj) {
  if (obj->Klass() != Self()) {
    throw std::runtime_error("PyInteger::pos(): obj is not an integer");
  }
  return obj;
}

PyObjPtr IntegerKlass::neg(const PyObjPtr& obj) {
  if (!obj->is<PyInteger>()) {
    throw std::runtime_error("PyInteger::neg(): obj is not an integer");
  }
  auto integer = obj->as<PyInteger>();
  return CreatePyInteger(integer->value.Negate());
}

PyObjPtr IntegerKlass::boolean(const PyObjPtr& obj) {
  if (!obj->is<PyInteger>()) {
    throw std::runtime_error("PyInteger::boolean(): obj is not an integer");
  }
  auto integer = obj->as<PyInteger>();
  return CreatePyBoolean(!integer->value.IsZero());
}

PyObjPtr IntegerKlass::hash(const PyObjPtr& obj) {
  if (!obj->is<PyInteger>()) {
    throw std::runtime_error("PyInteger::hash(): obj is not an integer");
  }
  if (obj->as<PyInteger>()->IsBigNumber()) {
    return CreatePyInteger(
      Collections::CreateIntegerWithU64(reinterpret_cast<uint64_t>(obj.get()))
    );
  }
  return obj;
}

PyObjPtr IntegerKlass::_and_(const PyObjPtr& lhs, const PyObjPtr& rhs) {
  return lhs->boolean()->_and_(rhs);
}

PyObjPtr IntegerKlass::_or_(const PyObjPtr& lhs, const PyObjPtr& rhs) {
  return lhs->boolean()->_or_(rhs);
}

PyObjPtr IntegerKlass::_xor_(const PyObjPtr& lhs, const PyObjPtr& rhs) {
  if (lhs->Klass() != Self() || rhs->Klass() != Self()) {
    throw std::runtime_error("PyInteger::_xor_(): lhs or rhs is not an integer"
    );
  }
  auto left = std::dynamic_pointer_cast<PyInteger>(lhs);
  auto right = std::dynamic_pointer_cast<PyInteger>(rhs);
  return CreatePyInteger(left->value.BitWiseXor(right->value));
}

PyObjPtr IntegerKlass::invert(const PyObjPtr& obj) {
  if (obj->Klass() != Self()) {
    throw std::runtime_error("PyInteger::invert(): obj is not an integer");
  }
  auto integer = std::dynamic_pointer_cast<PyInteger>(obj);
  return CreatePyInteger(integer->value.BitWiseNot());
}

PyObjPtr IntegerKlass::lshift(const PyObjPtr& lhs, const PyObjPtr& rhs) {
  if (lhs->Klass() != Self() || rhs->Klass() != Self()) {
    throw std::runtime_error("PyInteger::lshift(): lhs or rhs is not an integer"
    );
  }
  auto left = std::dynamic_pointer_cast<PyInteger>(lhs);
  auto right = std::dynamic_pointer_cast<PyInteger>(rhs);
  return CreatePyInteger(left->value.LeftShift(right->value));
}

PyObjPtr IntegerKlass::rshift(const PyObjPtr& lhs, const PyObjPtr& rhs) {
  if (lhs->Klass() != Self() || rhs->Klass() != Self()) {
    throw std::runtime_error("PyInteger::rshift(): lhs or rhs is not an integer"
    );
  }
  auto left = std::dynamic_pointer_cast<PyInteger>(lhs);
  auto right = std::dynamic_pointer_cast<PyInteger>(rhs);
  return CreatePyInteger(left->value.RightShift(right->value));
}
PyObjPtr IntegerKlass::repr(const PyObjPtr& obj) {
  if (obj->Klass() != Self()) {
    throw std::runtime_error("PyInteger::repr(): obj is not an integer");
  }
  auto integer = std::dynamic_pointer_cast<PyInteger>(obj);
  return CreatePyString((integer->value).ToString());
}
PyObjPtr IntegerKlass::str(const PyObjPtr& obj) {
  return repr(obj);
}

PyObjPtr IntegerKlass::gt(const PyObjPtr& lhs, const PyObjPtr& rhs) {
  if (lhs->Klass() != Self() || rhs->Klass() != Self()) {
    DebugPrint(lhs);
    DebugPrint(rhs);
    throw std::runtime_error("PyInteger::gt(): lhs or rhs is not an integer");
  }
  auto left = std::dynamic_pointer_cast<PyInteger>(lhs);
  auto right = std::dynamic_pointer_cast<PyInteger>(rhs);
  return CreatePyBoolean(left->value.GreaterThan(right->value));
}

PyObjPtr IntegerKlass::eq(const PyObjPtr& lhs, const PyObjPtr& rhs) {
  if (lhs->Klass() != Self() || rhs->Klass() != Self()) {
    throw std::runtime_error("PyInteger::eq(): lhs or rhs is not an integer");
  }
  auto left = std::dynamic_pointer_cast<PyInteger>(lhs);
  auto right = std::dynamic_pointer_cast<PyInteger>(rhs);
  return CreatePyBoolean(left->value.Equal(right->value));
}

PyObjPtr IntegerKlass::_serialize_(const PyObjPtr& obj) {
  if (obj->Klass() != Self()) {
    throw std::runtime_error("PyInteger::_serialize_(): obj is not an integer");
  }
  auto integer = std::dynamic_pointer_cast<PyInteger>(obj);
  if (integer->value.IsZero()) {
    return CreatePyBytes(Collections::Serialize(Literal::ZERO));
  }
  return CreatePyBytes(Collections::Serialize(Literal::INTEGER)
                         .Add(Collections::Serialize(integer->value)));
}

bool PyInteger::LessThan(const PyObjPtr& other) const {
  if (!other->is<PyInteger>()) {
    throw std::runtime_error("PyInteger::LessThan(): other is not an integer");
  }
  auto otherInteger = other->as<PyInteger>();
  return value.LessThan(otherInteger->value);
}

}  // namespace torchlight::Object