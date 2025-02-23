#include "Object/Klass.h"
#include "Function/PyFunction.h"
#include "Function/PyIife.h"
#include "Function/PyMethod.h"
#include "Function/PyNativeFunction.h"
#include "Object/MixinCollections.h"
#include "Object/PyBoolean.h"
#include "Object/PyDictionary.h"
#include "Object/PyInteger.h"
#include "Object/PyNone.h"
#include "Object/PyObject.h"
#include "Object/PyString.h"
#include "Object/PyType.h"

#include <iostream>
#include <memory>

namespace torchlight::Object {

Klass::Klass() {
  name = nullptr;
  attributes = nullptr;
  type = nullptr;
}

void Klass::Initialize() {
  if (initialized) {
    return;
  }
  initialized = true;
  auto attrs = std::dynamic_pointer_cast<PyDictionary>(attributes);
  attrs->Put(CreatePyString("__name__"), name);
  attrs->Put(CreatePyString("__class__"), type);
  attrs->Put(
    CreatePyString("__setitem__"),
    CreatePyNativeFunction([](const PyObjPtr& args) {
      auto self = args->getitem(CreatePyInteger(0));
      auto key = args->getitem(CreatePyInteger(1));
      auto value = args->getitem(CreatePyInteger(2));
      return self->setitem(key, value);
    })
  );
  attrs->Put(CreatePyString("print"), CreatePyNativeFunction(Print));
  SetAttributes(attrs);
}

Klass::~Klass() = default;

PyStrPtr Klass::Name() const {
  return name;
}

void Klass::SetName(const PyObjPtr& name) {
  this->name = std::dynamic_pointer_cast<PyString>(name);
}

PyDictPtr Klass::Attributes() const {
  return attributes;
}

void Klass::SetAttributes(const PyObjPtr& attributes) {
  this->attributes = std::dynamic_pointer_cast<PyDictionary>(attributes);
}

PyTypePtr Klass::Type() const {
  return type;
}

void Klass::SetType(const PyObjPtr& type) {
  if (type->Klass() != TypeKlass::Self()) {
    throw std::runtime_error("Cannot set non-type object as type");
  }
  this->type = std::dynamic_pointer_cast<PyType>(type);
}

void ThrowUnsupportedOperandError(
  const PyObjPtr& lhs,
  const PyObjPtr& rhs,
  const PyObjPtr& magicMethod
) {
  // DebugPrint(magicMethod);
  DebugPrint(lhs);
  std::cout << "----------- " << std::endl;
  DebugPrint(rhs);
  // throw UnsupportedOperandError(
  //   "TypeError: unsupported operand type(s) for " +
  //   Collections::ToCppString(magicMethod->repr()) + ": " +
  //   Collections::ToCppString(lhs->Klass()->Type()->Owner()->Name()->repr()) +
  //   " and " +
  //   Collections::ToCppString(rhs->Klass()->Type()->Owner()->Name()->repr())
  // );
  throw UnsupportedOperandError(
    "TypeError: unsupported operand type(s) for " +
    Collections::ToCppString(magicMethod->repr())
  );
}

UnsupportedOperandError::UnsupportedOperandError(const std::string& message)
  : std::runtime_error(message) {}

PyObjPtr Klass::allocateInstance(const PyObjPtr& klass, const PyObjPtr& args) {
  ThrowUnsupportedOperandError(klass, args, CreatePyString("allocateInstance"));
  return CreatePyNone();
}

PyObjPtr Klass::add(const PyObjPtr& lhs, const PyObjPtr& rhs) {
  ThrowUnsupportedOperandError(lhs, rhs, CreatePyString("__add__"));
  return CreatePyNone();
}

PyObjPtr Klass::sub(const PyObjPtr& lhs, const PyObjPtr& rhs) {
  ThrowUnsupportedOperandError(lhs, rhs, CreatePyString("__sub__"));
  return CreatePyNone();
}

PyObjPtr Klass::mul(const PyObjPtr& lhs, const PyObjPtr& rhs) {
  ThrowUnsupportedOperandError(lhs, rhs, CreatePyString("__mul__"));
  return CreatePyNone();
}

PyObjPtr Klass::div(const PyObjPtr& lhs, const PyObjPtr& rhs) {
  ThrowUnsupportedOperandError(lhs, rhs, CreatePyString("__div__"));
  return CreatePyNone();
}

PyObjPtr Klass::repr(const PyObjPtr& self) {
  return CreatePyString("<")
    ->add(self->getattr(CreatePyString("__name__")->str()))
    ->add(CreatePyString(" object at ")
            ->add(CreatePyInteger(reinterpret_cast<uint64_t>(self.get()))->str()
            ))
    ->add(CreatePyString(">"));
}

PyObjPtr Klass::gt(const PyObjPtr& lhs, const PyObjPtr& rhs) {
  ThrowUnsupportedOperandError(lhs, rhs, CreatePyString("__gt__"));
  return CreatePyNone();
}

PyObjPtr Klass::lt(const PyObjPtr& lhs, const PyObjPtr& rhs) {
  return And(Not(lhs->gt(rhs)), Not(lhs->eq(rhs)));
}

PyObjPtr Klass::eq(const PyObjPtr& /*lhs*/, const PyObjPtr& /*rhs*/) {
  return CreatePyBoolean(false);
}

PyObjPtr Klass::ge(const PyObjPtr& lhs, const PyObjPtr& rhs) {
  return Or(lhs->gt(rhs), lhs->eq(rhs));
}

PyObjPtr Klass::le(const PyObjPtr& lhs, const PyObjPtr& rhs) {
  return Not(lhs->gt(rhs));
}

PyObjPtr Klass::ne(const PyObjPtr& lhs, const PyObjPtr& rhs) {
  return Not(lhs->eq(rhs));
}

PyObjPtr Klass::_bool_(const PyObjPtr& obj) {
  try {
    return obj->_bool_();
  } catch (const UnsupportedOperandError&) {
    try {
      return obj->len()->ne(CreatePyInteger(0));
    } catch (const UnsupportedOperandError&) {
      return CreatePyBoolean(true);
    }
  }
}
PyObjPtr Klass::_serialize_(const PyObjPtr& /*obj*/) {
  throw std::runtime_error(
    Collections::ToCppString(name) + " does not support _serialize_ operation"
  );
}

PyObjPtr Klass::getitem(const PyObjPtr& /*obj*/, const PyObjPtr& /*key*/) {
  throw std::runtime_error(
    Collections::ToCppString(name) + " does not support getitem operation"
  );
}

PyObjPtr Klass::setitem(
  const PyObjPtr& /*obj*/,
  const PyObjPtr& /*key*/,
  const PyObjPtr& /*value*/
) {
  throw std::runtime_error(
    Collections::ToCppString(name) + " does not support setitem operation"
  );
}

PyObjPtr Klass::delitem(const PyObjPtr& /*obj*/, const PyObjPtr& /*key*/) {
  throw std::runtime_error(
    Collections::ToCppString(name) + " does not support delitem operation"
  );
}

PyObjPtr Klass::contains(const PyObjPtr& /*obj*/, const PyObjPtr& /*key*/) {
  throw std::runtime_error(
    Collections::ToCppString(name) + " does not support contains operation"
  );
}

PyObjPtr Klass::len(const PyObjPtr& /*obj*/) {
  throw std::runtime_error(
    Collections::ToCppString(name) + " does not support len operation"
  );
}

PyObjPtr Klass::getattr(const PyObjPtr& obj, const PyObjPtr& key) {
  if (!attributes->contains(key)) {
    throw std::runtime_error(
      "AttributeError: " + Collections::ToCppString(key->repr()) +
      " not found in " + Collections::ToCppString(obj->repr())
    );
  }
  auto dict = std::dynamic_pointer_cast<PyDictionary>(attributes);
  auto attr = dict->Get(key);
  if (attr->Klass() == NativeFunctionKlass::Self()) {
    return CreatePyMethod(obj, attr);
  }
  if (attr->Klass() == FunctionKlass::Self()) {
    return CreatePyMethod(obj, attr);
  }
  if (attr->Klass() == IifeKlass::Self()) {
    return std::dynamic_pointer_cast<PyIife>(attr)->Call(CreatePyList({obj}));
  }
  return attr;
}

PyObjPtr Klass::setattr(
  const PyObjPtr& /*obj*/,
  const PyObjPtr& key,
  const PyObjPtr& value
) {
  auto dict = std::dynamic_pointer_cast<PyDictionary>(attributes);
  dict->Put(key, value);
  return CreatePyNone();
}

PyObjPtr Klass::str(const PyObjPtr& self) {
  return self->repr();
}

PyObjPtr Klass::matmul(const PyObjPtr& lhs, const PyObjPtr& rhs) {
  ThrowUnsupportedOperandError(lhs, rhs, CreatePyString("__matmul__"));
  return CreatePyNone();
}

PyObjPtr Klass::iter(const PyObjPtr& /*obj*/) {
  throw std::runtime_error(
    Collections::ToCppString(name) + " does not support iter operation"
  );
}

PyObjPtr Klass::next(const PyObjPtr& /*obj*/) {
  throw std::runtime_error(
    Collections::ToCppString(name) + " does not support next operation"
  );
}

}  // namespace torchlight::Object