#include "Object/Klass.h"
#include "Object/Object.h"
#include "Object/ObjectHelper.h"
#include "Object/PyBoolean.h"
#include "Object/PyDictionary.h"
#include "Object/PyInteger.h"
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

PyObjPtr Klass::init(const PyObjPtr& type, const PyObjPtr& args) {
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

PyObjPtr Klass::floordiv(const PyObjPtr& lhs, const PyObjPtr& rhs) {
  return Invoke(
    lhs, CreatePyString("__floordiv__"), CreatePyList({rhs})->as<PyList>()
  );
}

PyObjPtr Klass::truediv(const PyObjPtr& lhs, const PyObjPtr& rhs) {
  return Invoke(
    lhs, CreatePyString("__truediv__"), CreatePyList({rhs})->as<PyList>()
  );
}

PyObjPtr Klass::pos(const PyObjPtr& obj) {
  return Invoke(obj, CreatePyString("__pos__"), {});
}

PyObjPtr Klass::neg(const PyObjPtr& obj) {
  return Invoke(obj, CreatePyString("__neg__"), {});
}

PyObjPtr Klass::invert(const PyObjPtr& obj) {
  return Invoke(obj, CreatePyString("__invert__"), {});
}

PyObjPtr Klass::_and_(const PyObjPtr& lhs, const PyObjPtr& rhs) {
  return Invoke(
    lhs, CreatePyString("__and__"), CreatePyList({rhs})->as<PyList>()
  );
}

PyObjPtr Klass::_or_(const PyObjPtr& lhs, const PyObjPtr& rhs) {
  return Invoke(
    lhs, CreatePyString("__or__"), CreatePyList({rhs})->as<PyList>()
  );
}

PyObjPtr Klass::_xor_(const PyObjPtr& lhs, const PyObjPtr& rhs) {
  return Invoke(
    lhs, CreatePyString("__xor__"), CreatePyList({rhs})->as<PyList>()
  );
}

PyObjPtr Klass::lshift(const PyObjPtr& lhs, const PyObjPtr& rhs) {
  return Invoke(
    lhs, CreatePyString("__lshift__"), CreatePyList({rhs})->as<PyList>()
  );
}

PyObjPtr Klass::rshift(const PyObjPtr& lhs, const PyObjPtr& rhs) {
  return Invoke(
    lhs, CreatePyString("__rshift__"), CreatePyList({rhs})->as<PyList>()
  );
}

PyObjPtr Klass::mod(const PyObjPtr& lhs, const PyObjPtr& rhs) {
  return Invoke(
    lhs, CreatePyString("__mod__"), CreatePyList({rhs})->as<PyList>()
  );
}

PyObjPtr Klass::divmod(const PyObjPtr& lhs, const PyObjPtr& rhs) {
  return Invoke(
    lhs, CreatePyString("__divmod__"), CreatePyList({rhs})->as<PyList>()
  );
}

PyObjPtr Klass::pow(const PyObjPtr& lhs, const PyObjPtr& rhs) {
  return Invoke(
    lhs, CreatePyString("__pow__"), CreatePyList({rhs})->as<PyList>()
  );
}

PyObjPtr Klass::repr(const PyObjPtr& self) {
  auto reprFunc = GetAttr(self, CreatePyString("__repr__")->as<PyString>());
  if (reprFunc != nullptr) {
    return Runtime::Interpreter::Eval(reprFunc, CreatePyList({})->as<PyList>());
  }
  return StringConcat(CreatePyList(
    {CreatePyString("<"),
     self->getattr(CreatePyString("__name__")->as<PyString>()),
     CreatePyString(" object at "), Identity(self), CreatePyString(">")}
  ));
}

PyObjPtr Klass::gt(const PyObjPtr& lhs, const PyObjPtr& rhs) {
  return Invoke(
    lhs, CreatePyString("__gt__"), CreatePyList({rhs})->as<PyList>()
  );
}

PyObjPtr Klass::eq(const PyObjPtr& lhs, const PyObjPtr& rhs) {
  return Invoke(
    lhs, CreatePyString("__eq__"), CreatePyList({rhs})->as<PyList>()
  );
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
  auto boolFunc = obj->getattr(CreatePyString("__bool__")->as<PyString>());
  if (boolFunc != nullptr) {
    return Runtime::Interpreter::Eval(boolFunc, CreatePyList({})->as<PyList>());
  }
  auto lenFunc = obj->getattr(CreatePyString("__len__")->as<PyString>());
  if (lenFunc != nullptr) {
    auto len =
      Runtime::Interpreter::Eval(lenFunc, CreatePyList({})->as<PyList>());
    return len->ne(CreatePyInteger(0));
  }
  return CreatePyBoolean(true);
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
  return nullptr;
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
  auto strFunc = self->getattr(CreatePyString("__str__")->as<PyString>());
  if (strFunc != nullptr) {
    return Runtime::Interpreter::Eval(strFunc, CreatePyList({})->as<PyList>());
  }
  auto reprFunc = self->getattr(CreatePyString("__repr__")->as<PyString>());
  if (reprFunc != nullptr) {
    return Runtime::Interpreter::Eval(reprFunc, CreatePyList({})->as<PyList>());
  }
  return repr(self);
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
  attributes->Put(key, value);
}

}  // namespace torchlight::Object