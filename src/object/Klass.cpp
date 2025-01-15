#include "object/Klass.h"
#include "object/PyString.h"

namespace torchlight::object {

Klass::Klass(collections::String value) : name(std::move(value)) {}
Klass::~Klass() = default;

PyStrPtr Klass::Name() const {
  return std::make_shared<PyString>(name);
}

PyObjPtr Klass::add(PyObjPtr, PyObjPtr) {
  return nullptr;
}

PyObjPtr Klass::sub(PyObjPtr, PyObjPtr) {
  return nullptr;
}

PyObjPtr Klass::mul(PyObjPtr, PyObjPtr) {
  return nullptr;
}

PyObjPtr Klass::div(PyObjPtr, PyObjPtr) {
  return nullptr;
}

PyObjPtr Klass::repr(PyObjPtr obj) {
  return nullptr;
}

PyObjPtr Klass::gt(PyObjPtr, PyObjPtr) {
  return nullptr;
}

PyObjPtr Klass::lt(PyObjPtr, PyObjPtr) {
  return nullptr;
}

PyObjPtr Klass::eq(PyObjPtr, PyObjPtr) {
  return nullptr;
}

PyObjPtr Klass::ge(PyObjPtr, PyObjPtr) {
  return nullptr;
}

PyObjPtr Klass::le(PyObjPtr, PyObjPtr) {
  return nullptr;
}

PyObjPtr Klass::ne(PyObjPtr, PyObjPtr) {
  return nullptr;
}

PyObjPtr Klass::_bool_(PyObjPtr obj) {
  return nullptr;
}

PyObjPtr Klass::_serialize_(PyObjPtr obj) {
  return nullptr;
}

PyObjPtr Klass::getitem(PyObjPtr obj, PyObjPtr key) {
  return nullptr;
}

PyObjPtr Klass::setitem(PyObjPtr obj, PyObjPtr key, PyObjPtr value) {
  return nullptr;
}

PyObjPtr Klass::delitem(PyObjPtr obj, PyObjPtr key) {
  return nullptr;
}

}  // namespace torchlight::object