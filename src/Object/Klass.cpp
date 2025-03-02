#include "Object/Klass.h"
#include "Collections/IntegerHelper.h"
#include "Function/PyFunction.h"
#include "Function/PyIife.h"
#include "Function/PyMethod.h"
#include "Function/PyNativeFunction.h"
#include "Object/Object.h"
#include "Object/ObjectHelper.h"
#include "Object/PyBoolean.h"
#include "Object/PyDictionary.h"
#include "Object/PyList.h"
#include "Object/PyNone.h"
#include "Object/PyObject.h"
#include "Object/PyString.h"
#include "Object/PyType.h"

namespace torchlight::Object {

void Klass::SetName(const PyObjPtr& name) {
  this->name = name->as<PyString>();
}

void Klass::SetAttributes(const PyObjPtr& attributes) {
  this->attributes = attributes->as<PyDictionary>();
}

void Klass::SetType(const PyObjPtr& type) {
  if (type->Klass() != TypeKlass::Self()) {
    throw std::runtime_error("Cannot set non-type object as type");
  }
  this->type = std::dynamic_pointer_cast<PyType>(type);
}

void Klass::SetSuper(const PyObjPtr& super) {
  this->super = super->as<PyList>();
}

void Klass::SetMro(const PyObjPtr& mro) {
  this->mro = mro->as<PyList>();
}

PyObjPtr Klass::construct(const PyObjPtr& type, const PyObjPtr& args) {
  auto klass = type->as<PyType>()->Owner();
  auto instance = std::make_shared<PyObject>(klass);
  if (klass->IsNative()) {
    return instance;
  }
  return Invoke(instance, CreatePyString("__init__"), {args});
}

PyObjPtr Klass::add(const PyObjPtr& lhs, const PyObjPtr& rhs) {
  return Invoke(lhs, CreatePyString("__add__"), {rhs});
}

PyObjPtr Klass::sub(const PyObjPtr& lhs, const PyObjPtr& rhs) {
  return Invoke(lhs, CreatePyString("__sub__"), {rhs});
}

PyObjPtr Klass::mul(const PyObjPtr& lhs, const PyObjPtr& rhs) {
  return Invoke(lhs, CreatePyString("__mul__"), {rhs});
}

PyObjPtr Klass::div(const PyObjPtr& lhs, const PyObjPtr& rhs) {
  return Invoke(lhs, CreatePyString("__div__"), {rhs});
}

PyObjPtr Klass::repr(const PyObjPtr& self) {
  // self->Klass()->Name()->PrintLine();
  // throw std::runtime_error("Cannot repr non-object");
  return CreatePyString("<")
    ->add(self->getattr(CreatePyString("__name__")->str()))
    ->add(CreatePyString(" object at ")
            ->add(CreatePyString(Collections::CreateIntegerWithU64(
                                   reinterpret_cast<uint64_t>(self.get())
            )
                                   .ToHexString())))
    ->add(CreatePyString(">"));
}

PyObjPtr Klass::gt(const PyObjPtr& lhs, const PyObjPtr& rhs) {
  return Invoke(lhs, CreatePyString("__gt__"), {rhs});
}

PyObjPtr Klass::eq(const PyObjPtr& lhs, const PyObjPtr& rhs) {
  auto eq = Invoke(lhs, CreatePyString("__eq__"), {rhs});
  if (!eq->is<PyBoolean>()) {
    DebugPrint(eq);
    DebugPrint(lhs);
    DebugPrint(rhs);
    throw std::runtime_error("eq should return boolean");
  }
  return eq;
}

PyObjPtr Klass::lt(const PyObjPtr& lhs, const PyObjPtr& rhs) {
  return Not(lhs->ge(rhs));
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

PyObjPtr Klass::boolean(const PyObjPtr& obj) {
  return Invoke(obj, CreatePyString("__bool__"), {});
}

PyObjPtr Klass::getitem(const PyObjPtr& obj, const PyObjPtr& key) {
  return Invoke(obj, CreatePyString("__getitem__"), {key});
}

PyObjPtr Klass::setitem(
  const PyObjPtr& obj,
  const PyObjPtr& key,
  const PyObjPtr& value
) {
  return Invoke(obj, CreatePyString("__setitem__"), {key, value});
}

PyObjPtr Klass::delitem(const PyObjPtr& obj, const PyObjPtr& key) {
  return Invoke(obj, CreatePyString("__delitem__"), {key});
}

PyObjPtr Klass::contains(const PyObjPtr& obj, const PyObjPtr& key) {
  return Invoke(obj, CreatePyString("__contains__"), {key});
}

PyObjPtr Klass::len(const PyObjPtr& obj) {
  return Invoke(obj, CreatePyString("__len__"), {});
}

PyObjPtr Klass::getattr(const PyObjPtr& obj, const PyObjPtr& key) {
  if (!attributes->contains(key)) {
    auto errorMessge = CreatePyString("AttributeError: ")
                         ->add(obj->str())
                         ->add(CreatePyString(" has no attribute "))
                         ->add(key->str())
                         ->as<PyString>();
    throw std::runtime_error(errorMessge->ToCppString());
  }
  auto attr = attributes->Get(key);
  if (attr->is<PyNativeFunction>()) {
    return CreatePyMethod(obj, attr);
  }
  if (attr->is<PyFunction>()) {
    return CreatePyMethod(obj, attr);
  }
  if (attr->is<PyIife>()) {
    return attr->as<PyIife>()->Call(CreatePyList({obj}));
  }
  return attr;
}

PyObjPtr Klass::setattr(
  const PyObjPtr& /*obj*/,
  const PyObjPtr& key,
  const PyObjPtr& value
) {
  attributes->Put(key, value);
  return CreatePyNone();
}

PyObjPtr Klass::str(const PyObjPtr& self) {
  return self->repr();
}

PyObjPtr Klass::matmul(const PyObjPtr& lhs, const PyObjPtr& rhs) {
  return Invoke(lhs, CreatePyString("__matmul__"), {rhs});
}

PyObjPtr Klass::iter(const PyObjPtr& obj) {
  return Invoke(obj, CreatePyString("__iter__"), {});
}

PyObjPtr Klass::next(const PyObjPtr& obj) {
  return Invoke(obj, CreatePyString("__next__"), {});
}

PyObjPtr Klass::_serialize_(const PyObjPtr& obj) {
  return Invoke(obj, CreatePyString("_serialize_"), {});
}

KlassPtr CreatePyKlass(
  const PyStrPtr& name,
  const PyDictPtr& attributes,
  const PyListPtr& super
) {
  auto klass = std::make_shared<Klass>();
  klass->SetName(name);
  klass->SetAttributes(attributes);
  klass->SetType(CreatePyType(klass));
  klass->SetSuper(super);
  klass->SetMro(ComputeMro(klass->Type()));
  ConfigureBasicAttributes(klass);
  return klass;
}

void Klass::AddAttribute(const PyStrPtr& key, const PyObjPtr& value) {
  attributes->as<PyDictionary>()->Put(key, value);
}



}  // namespace torchlight::Object