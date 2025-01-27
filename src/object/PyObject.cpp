#include "Collections/Iterator.h"
#include "Collections/StringHelper.h"
#include "Object/MixinCollections.h"
#include "Object/PyBoolean.h"
#include "Object/PyList.h"
#include "Object/PyNone.h"
#include "Object/PyObject.h"
#include "Object/PyString.h"

#include <iostream>

namespace torchlight::Object {

PyObject::PyObject(KlassPtr klass) : klass(std::move(klass)) {}

void PyObject::setKlass(KlassPtr klass) {
  this->klass = std::move(klass);
}

KlassPtr PyObject::Klass() const {
  return klass;
}

PyObject::~PyObject() = default;

PyObjPtr PyObject::add(PyObjPtr other) {
  return klass->add(shared_from_this(), std::move(other));
}

PyObjPtr PyObject::sub(PyObjPtr other) {
  return klass->sub(shared_from_this(), std::move(other));
}

PyObjPtr PyObject::mul(PyObjPtr other) {
  return klass->mul(shared_from_this(), std::move(other));
}

PyObjPtr PyObject::div(PyObjPtr other) {
  return klass->div(shared_from_this(), std::move(other));
}

PyObjPtr PyObject::matmul(PyObjPtr other) {
  return klass->matmul(shared_from_this(), std::move(other));
}

PyObjPtr PyObject::gt(PyObjPtr other) {
  return klass->gt(shared_from_this(), std::move(other));
}

PyObjPtr PyObject::lt(PyObjPtr other) {
  return klass->lt(shared_from_this(), std::move(other));
}

PyObjPtr PyObject::eq(PyObjPtr other) {
  return klass->eq(shared_from_this(), std::move(other));
}

PyObjPtr PyObject::ge(PyObjPtr other) {
  return klass->ge(shared_from_this(), std::move(other));
}

PyObjPtr PyObject::le(PyObjPtr other) {
  return klass->le(shared_from_this(), std::move(other));
}

PyObjPtr PyObject::ne(PyObjPtr other) {
  return klass->ne(shared_from_this(), std::move(other));
}

PyObjPtr PyObject::repr() {
  return klass->repr(shared_from_this());
}

PyObjPtr PyObject::str() {
  return klass->str(shared_from_this());
}

PyObjPtr PyObject::_bool_() {
  return klass->_bool_(shared_from_this());
}

PyObjPtr PyObject::_serialize_() {
  return klass->_serialize_(shared_from_this());
}

PyObjPtr PyObject::getitem(PyObjPtr key) {
  return klass->getitem(shared_from_this(), std::move(key));
}

PyObjPtr PyObject::setitem(PyObjPtr key, PyObjPtr value) {
  return klass->setitem(shared_from_this(), std::move(key), std::move(value));
}

PyObjPtr PyObject::delitem(PyObjPtr key) {
  return klass->delitem(shared_from_this(), std::move(key));
}

PyObjPtr PyObject::contains(PyObjPtr key) {
  return klass->contains(shared_from_this(), std::move(key));
}

PyObjPtr PyObject::len() {
  return klass->len(shared_from_this());
}

PyObjPtr PyObject::getattr(PyObjPtr key) {
  return klass->getattr(shared_from_this(), std::move(key));
}

bool operator==(const PyObjPtr& lhs, const PyObjPtr& rhs) {
  auto equal = lhs->eq(rhs);
  return std::dynamic_pointer_cast<PyBoolean>(equal)->Value();
}

bool operator!=(const PyObjPtr& lhs, const PyObjPtr& rhs) {
  return !(lhs == rhs);
}

void DebugPrint(const PyObjPtr& obj) {
  auto repr = obj->str();
  auto str = std::dynamic_pointer_cast<PyString>(repr)->Value();
  std::cout << Collections::ToCppString(str) << std::endl;
}

PyObjPtr Print(PyObjPtr args) {
  if (args->Klass() != ListKlass::Self()) {
    throw std::runtime_error("print() argument must be a list");
  }
  Collections::List<PyObjPtr> rawList =
    std::dynamic_pointer_cast<PyList>(args)->Value();
  for (auto it = Collections::Iterator<PyObjPtr>::Begin(rawList); !it.End();
       it.Next()) {
    auto value = it.Get();
    if (it.First()) {
      std::cout << Collections::ToCppString(value->str());
    } else {
      std::cout << "," << Collections::ToCppString(value->str());
    }
  }
  std::cout << std::endl;
  return CreatePyNone();
}
}  // namespace torchlight::Object