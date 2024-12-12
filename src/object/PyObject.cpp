#include "object/Klass.h"
#include "object/PyObject.h"

#include <utility>

namespace torchlight::object {

PyObject::PyObject(KlassPtr klass) : klass(std::move(klass)) {}

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

PyObjPtr PyObject::repr() {
  return klass->repr(shared_from_this());
}

}  // namespace torchlight::object