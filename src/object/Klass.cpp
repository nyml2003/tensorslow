#include "Function/PyFunction.h"
#include "Function/PyMethod.h"
#include "Function/PyNativeFunction.h"
#include "Object/Common.h"
#include "Object/Klass.h"
#include "Object/MixinCollections.h"
#include "Object/PyBoolean.h"
#include "Object/PyDictionary.h"
#include "Object/PyInteger.h"
#include "Object/PyNone.h"
#include "Object/PyObject.h"
#include "Object/PyString.h"
#include "Object/PyType.h"

#include <iostream>

namespace torchlight::Object {

Klass::Klass() {
  name = nullptr;
  attributes = nullptr;
  type = nullptr;
}

void Klass::Initialize() {
  auto dict = std::dynamic_pointer_cast<PyDictionary>(attributes);
  dict->setitem(CreatePyString("__name__"), name);
  dict->setitem(CreatePyString("__class__"), type);
  dict->setitem(CreatePyString("print"), CreatePyNativeFunction(Print));
}

Klass::~Klass() = default;

PyStrPtr Klass::Name() const {
  return name;
}

void Klass::SetName(PyObjPtr name) {
  this->name = std::move(std::dynamic_pointer_cast<PyString>(name));
}

PyDictPtr Klass::Attributes() const {
  return attributes;
}

void Klass::SetAttributes(PyObjPtr attributes) {
  this->attributes =
    std::move(std::dynamic_pointer_cast<PyDictionary>(attributes));
}

PyTypePtr Klass::Type() const {
  return type;
}

void Klass::SetType(PyObjPtr type) {
  if (type->Klass() != TypeKlass::Self()) {
    throw std::runtime_error("Cannot set non-type object as type");
  }
  this->type = std::dynamic_pointer_cast<PyType>(type);
}

void ThrowUnsupportedOperandError(
  PyObjPtr lhs,
  PyObjPtr rhs,
  PyObjPtr magicMethod
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

PyObjPtr Klass::add(PyObjPtr lhs, PyObjPtr rhs) {
  ThrowUnsupportedOperandError(lhs, rhs, CreatePyString("__add__"));
  return CreatePyNone();
}

PyObjPtr Klass::sub(PyObjPtr lhs, PyObjPtr rhs) {
  ThrowUnsupportedOperandError(lhs, rhs, CreatePyString("__sub__"));
  return CreatePyNone();
}

PyObjPtr Klass::mul(PyObjPtr lhs, PyObjPtr rhs) {
  ThrowUnsupportedOperandError(lhs, rhs, CreatePyString("__mul__"));
  return CreatePyNone();
}

PyObjPtr Klass::div(PyObjPtr lhs, PyObjPtr rhs) {
  ThrowUnsupportedOperandError(lhs, rhs, CreatePyString("__div__"));
  return CreatePyNone();
}

PyObjPtr Klass::repr(PyObjPtr self) {
  return CreatePyString("<")
    ->add(self->getattr(CreatePyString("__class__"))
            ->getattr(CreatePyString("__name__")))
    ->add(CreatePyString(" object at ")
            ->add(CreatePyInteger(reinterpret_cast<uint64_t>(self.get()))->str()
            ))
    ->add(CreatePyString(">"));
}

PyObjPtr Klass::gt(PyObjPtr lhs, PyObjPtr rhs) {
  ThrowUnsupportedOperandError(lhs, rhs, CreatePyString("__gt__"));
  return CreatePyNone();
}

PyObjPtr Klass::lt(PyObjPtr lhs, PyObjPtr rhs) {
  return And(Not(lhs->gt(rhs)), Not(lhs->eq(rhs)));
}

PyObjPtr Klass::eq(PyObjPtr lhs, PyObjPtr rhs) {
  return CreatePyBoolean(false);
}

PyObjPtr Klass::ge(PyObjPtr lhs, PyObjPtr rhs) {
  return Or(lhs->gt(rhs), lhs->eq(rhs));
}

PyObjPtr Klass::le(PyObjPtr lhs, PyObjPtr rhs) {
  return Not(lhs->gt(rhs));
}

PyObjPtr Klass::ne(PyObjPtr lhs, PyObjPtr rhs) {
  return Not(lhs->eq(rhs));
}

PyObjPtr Klass::_bool_(PyObjPtr obj) {
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
PyObjPtr Klass::_serialize_(PyObjPtr obj) {
  throw std::runtime_error(
    Collections::ToCppString(name) + " does not support _serialize_ operation"
  );
}

PyObjPtr Klass::getitem(PyObjPtr obj, PyObjPtr key) {
  throw std::runtime_error(
    Collections::ToCppString(name) + " does not support getitem operation"
  );
}

PyObjPtr Klass::setitem(PyObjPtr obj, PyObjPtr key, PyObjPtr value) {
  throw std::runtime_error(
    Collections::ToCppString(name) + " does not support setitem operation"
  );
}

PyObjPtr Klass::delitem(PyObjPtr obj, PyObjPtr key) {
  throw std::runtime_error(
    Collections::ToCppString(name) + " does not support delitem operation"
  );
}

PyObjPtr Klass::contains(PyObjPtr obj, PyObjPtr key) {
  throw std::runtime_error(
    Collections::ToCppString(name) + " does not support contains operation"
  );
}

PyObjPtr Klass::len(PyObjPtr obj) {
  throw std::runtime_error(
    Collections::ToCppString(name) + " does not support len operation"
  );
}

PyObjPtr Klass::getattr(PyObjPtr obj, PyObjPtr key) {
  if (!attributes->contains(key)) {
    throw std::runtime_error(
      "AttributeError: " + Collections::ToCppString(key->repr()) +
      " not found in " + Collections::ToCppString(obj->repr())
    );
  }
  auto dict = std::dynamic_pointer_cast<PyDictionary>(attributes);
  auto dictValue = dict->Value();
  auto attr = dictValue.Get(key);
  if (attr->Klass() == NativeFunctionKlass::Self()) {
    return CreatePyMethod(obj, attr);
  }
  if (attr->Klass() == FunctionKlass::Self()) {
    return CreatePyMethod(obj, attr);
  }
  return attr;
}

PyObjPtr Klass::str(PyObjPtr obj) {
  return obj->repr();
}

PyObjPtr Klass::matmul(PyObjPtr lhs, PyObjPtr rhs) {
  ThrowUnsupportedOperandError(lhs, rhs, CreatePyString("__matmul__"));
  return CreatePyNone();
}

}  // namespace torchlight::Object