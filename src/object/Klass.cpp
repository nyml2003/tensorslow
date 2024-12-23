#include "object/Klass.h"
#include "object/PyString.h"

namespace torchlight::object {

Klass::Klass(collections::String value) : name(std::move(value)) {}
Klass::~Klass() = default;

PyStrPtr Klass::Name() const {
  return std::make_shared<PyString>(name);
}

PyObjPtr Klass::add(PyObjPtr lhs, PyObjPtr rhs) {
  return nullptr;
}

PyObjPtr Klass::sub(PyObjPtr lhs, PyObjPtr rhs) {
  return nullptr;
}

PyObjPtr Klass::mul(PyObjPtr lhs, PyObjPtr rhs) {
  return nullptr;
}

PyObjPtr Klass::div(PyObjPtr lhs, PyObjPtr rhs) {
  return nullptr;
}

PyObjPtr Klass::repr(PyObjPtr obj) {
  return nullptr;
}

PyObjPtr Klass::gt(PyObjPtr lhs, PyObjPtr rhs) {
  return nullptr;
}

PyObjPtr Klass::lt(PyObjPtr lhs, PyObjPtr rhs) {
  return nullptr;
}

PyObjPtr Klass::eq(PyObjPtr lhs, PyObjPtr rhs) {
  return nullptr;
}

PyObjPtr Klass::ge(PyObjPtr lhs, PyObjPtr rhs) {
  return nullptr;
}

PyObjPtr Klass::le(PyObjPtr lhs, PyObjPtr rhs) {
  return nullptr;
}

PyObjPtr Klass::ne(PyObjPtr lhs, PyObjPtr rhs) {
  return nullptr;
}

PyObjPtr Klass::_bool_(PyObjPtr obj) {
  return nullptr;
}

}  // namespace torchlight::object