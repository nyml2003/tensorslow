#include "object/Klass.h"
#include "object/PyObject.h"

#include <utility>

namespace torchlight::object {

PyObject::PyObject(KlassPtr klass) : klass(std::move(klass)) {}

void PyObject::setKlass(KlassPtr klass) {
  this->klass = std::move(klass);
}

KlassPtr PyObject::Klass() const {
  return klass;
}

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

PyObjPtr PyObject::_bool_() {
  return klass->_bool_(shared_from_this());
}


}  // namespace torchlight::object