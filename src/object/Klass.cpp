#include "Collections/StringHelper.h"
#include "Object/Klass.h"
#include "Object/PyNone.h"
#include "Object/PyString.h"

namespace torchlight::Object {

Klass::Klass(Collections::String value) : name(std::move(value)) {}
Klass::~Klass() = default;

PyStrPtr Klass::Name() const {
  return std::make_shared<PyString>(name);
}

PyObjPtr Klass::add(PyObjPtr, PyObjPtr) {
  throw std::runtime_error(
    Collections::ToCppString(name) + " does not support add operation"
  );
}

PyObjPtr Klass::sub(PyObjPtr, PyObjPtr) {
  throw std::runtime_error(
    Collections::ToCppString(name) + " does not support sub operation"
  );
}

PyObjPtr Klass::mul(PyObjPtr, PyObjPtr) {
  throw std::runtime_error(
    Collections::ToCppString(name) + " does not support mul operation"
  );
}

PyObjPtr Klass::div(PyObjPtr, PyObjPtr) {
  throw std::runtime_error(
    Collections::ToCppString(name) + " does not support div operation"
  );
}

PyObjPtr Klass::repr(PyObjPtr obj) {
  throw std::runtime_error(
    Collections::ToCppString(name) + " does not support repr operation"
  );
}

PyObjPtr Klass::gt(PyObjPtr, PyObjPtr) {
  throw std::runtime_error(
    Collections::ToCppString(name) + " does not support gt operation"
  );
}

PyObjPtr Klass::lt(PyObjPtr, PyObjPtr) {
  throw std::runtime_error(
    Collections::ToCppString(name) + " does not support lt operation"
  );
}

PyObjPtr Klass::eq(PyObjPtr, PyObjPtr) {
  throw std::runtime_error(
    Collections::ToCppString(name) + " does not support eq operation"
  );
}

PyObjPtr Klass::ge(PyObjPtr, PyObjPtr) {
  throw std::runtime_error(
    Collections::ToCppString(name) + " does not support ge operation"
  );
}

PyObjPtr Klass::le(PyObjPtr, PyObjPtr) {
  throw std::runtime_error(
    Collections::ToCppString(name) + " does not support le operation"
  );
}

PyObjPtr Klass::ne(PyObjPtr, PyObjPtr) {
  throw std::runtime_error(
    Collections::ToCppString(name) + " does not support le operation"
  );
}

PyObjPtr Klass::_bool_(PyObjPtr obj) {
  throw std::runtime_error(
    Collections::ToCppString(name) + " does not support le operation"
  );
}

PyObjPtr Klass::_serialize_(PyObjPtr obj) {
  throw std::runtime_error(
    Collections::ToCppString(name) + " does not support le operation"
  );
}

PyObjPtr Klass::getitem(PyObjPtr obj, PyObjPtr key) {
  throw std::runtime_error(
    Collections::ToCppString(name) + " does not support le operation"
  );
}

PyObjPtr Klass::setitem(PyObjPtr obj, PyObjPtr key, PyObjPtr value) {
  throw std::runtime_error(
    Collections::ToCppString(name) + " does not support le operation"
  );
}

PyObjPtr Klass::delitem(PyObjPtr obj, PyObjPtr key) {
  throw std::runtime_error(
    Collections::ToCppString(name) + " does not support le operation"
  );
}

}  // namespace torchlight::Object