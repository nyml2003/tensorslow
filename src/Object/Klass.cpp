#include "Object/Klass.h"
#include "Object/Object.h"
#include "Object/ObjectHelper.h"
#include "Object/PyBoolean.h"
#include "Object/PyDictionary.h"
#include "Object/PyList.h"
#include "Object/PyNone.h"
#include "Object/PyObject.h"
#include "Object/PyString.h"
#include "Object/PyType.h"
#include "Runtime/Interpreter.h"

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
  Invoke(instance, CreatePyString("__init__"), args->as<PyList>());
  return instance;
}

PyObjPtr Klass::add(const PyObjPtr& lhs, const PyObjPtr& rhs) {
  return Invoke(
    lhs, CreatePyString("__add__"), CreatePyList({rhs})->as<PyList>()
  );
}

PyObjPtr Klass::sub(const PyObjPtr& lhs, const PyObjPtr& rhs) {
  return Invoke(
    lhs, CreatePyString("__sub__"), CreatePyList({rhs})->as<PyList>()
  );
}

PyObjPtr Klass::mul(const PyObjPtr& lhs, const PyObjPtr& rhs) {
  return Invoke(
    lhs, CreatePyString("__mul__"), CreatePyList({rhs})->as<PyList>()
  );
}

PyObjPtr Klass::div(const PyObjPtr& lhs, const PyObjPtr& rhs) {
  return Invoke(
    lhs, CreatePyString("__div__"), CreatePyList({rhs})->as<PyList>()
  );
}

PyObjPtr Klass::repr(const PyObjPtr& self) {
  return self->Klass()->Name();
  // return CreatePyString("<")
  //   ->add(self->getattr(CreatePyString("__name__")->str()))
  //   ->add(CreatePyString(" object at ")
  //           ->add(CreatePyString(Collections::CreateIntegerWithU64(
  //                                  reinterpret_cast<uint64_t>(self.get())
  //           )
  //                                  .ToHexString())))
  //   ->add(CreatePyString(">"));
}

PyObjPtr Klass::gt(const PyObjPtr& lhs, const PyObjPtr& rhs) {
  return Invoke(
    lhs, CreatePyString("__gt__"), CreatePyList({rhs})->as<PyList>()
  );
}

PyObjPtr Klass::eq(const PyObjPtr& lhs, const PyObjPtr& rhs) {
  auto eq =
    Invoke(lhs, CreatePyString("__eq__"), CreatePyList({rhs})->as<PyList>());
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
  return Invoke(
    obj, CreatePyString("__bool__"), CreatePyList({})->as<PyList>()
  );
}

PyObjPtr Klass::getitem(const PyObjPtr& obj, const PyObjPtr& key) {
  return Invoke(
    obj, CreatePyString("__getitem__"), CreatePyList({key})->as<PyList>()
  );
}

PyObjPtr Klass::setitem(
  const PyObjPtr& obj,
  const PyObjPtr& key,
  const PyObjPtr& value
) {
  return Invoke(
    obj, CreatePyString("__setitem__"), CreatePyList({key, value})->as<PyList>()
  );
}

PyObjPtr Klass::delitem(const PyObjPtr& obj, const PyObjPtr& key) {
  return Invoke(
    obj, CreatePyString("__delitem__"), CreatePyList({key})->as<PyList>()
  );
}

PyObjPtr Klass::contains(const PyObjPtr& obj, const PyObjPtr& key) {
  return Invoke(
    obj, CreatePyString("__contains__"), CreatePyList({key})->as<PyList>()
  );
}

PyObjPtr Klass::len(const PyObjPtr& obj) {
  return Invoke(obj, CreatePyString("__len__"), {});
}

PyObjPtr Klass::getattr(const PyObjPtr& obj, const PyObjPtr& key) {
  // 如果getattr被重载，那么调用重载的函数
  auto attr = GetAttr(obj, CreatePyString("__getattr__")->as<PyString>());
  if (attr != nullptr) {
    return Runtime::Interpreter::Eval(attr, CreatePyList({key})->as<PyList>());
  }
  // attr为nullptr说明没有重载，直接返回属性
  if (obj->Attributes()->Contains(key->as<PyString>())) {
    return AttrWrapper(obj, obj->Attributes()->Get(key->as<PyString>()));
  }
  // 对象属性内部没有找到，查找父类
  attr = GetAttr(obj, key->as<PyString>());
  if (attr != nullptr) {
    return AttrWrapper(obj, attr);
  }
  auto errorMessge = CreatePyString("AttributeError: ")
                       ->add(obj->str())
                       ->add(CreatePyString(" has no attribute "))
                       ->add(key->str())
                       ->as<PyString>();
  throw std::runtime_error(errorMessge->ToCppString());
}

PyObjPtr Klass::setattr(
  const PyObjPtr& obj,
  const PyObjPtr& key,
  const PyObjPtr& value
) {
  auto attr = GetAttr(obj, CreatePyString("__setattr__")->as<PyString>());
  if (attr != nullptr) {
    return Runtime::Interpreter::Eval(
      attr, CreatePyList({key, value})->as<PyList>()
    );
    return CreatePyNone();
  }
  obj->Attributes()->Put(key->as<PyString>(), value);
  return CreatePyNone();
}

PyObjPtr Klass::str(const PyObjPtr& self) {
  return self->repr();
}

PyObjPtr Klass::matmul(const PyObjPtr& lhs, const PyObjPtr& rhs) {
  return Invoke(
    lhs, CreatePyString("__matmul__"), CreatePyList({rhs})->as<PyList>()
  );
}

PyObjPtr Klass::iter(const PyObjPtr& obj) {
  return Invoke(
    obj, CreatePyString("__iter__"), CreatePyList({})->as<PyList>()
  );
}

PyObjPtr Klass::next(const PyObjPtr& obj) {
  return Invoke(
    obj, CreatePyString("__next__"), CreatePyList({})->as<PyList>()
  );
}

PyObjPtr Klass::_serialize_(const PyObjPtr& obj) {
  return Invoke(
    obj, CreatePyString("_serialize_"), CreatePyList({})->as<PyList>()
  );
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