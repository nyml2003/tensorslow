#ifndef TORCHLIGHT_OBJECT_PYOBJECT_H
#define TORCHLIGHT_OBJECT_PYOBJECT_H

#include "Object/Klass.h"
#include "Object/Object.h"

namespace torchlight::Object {

class PyObject : public std::enable_shared_from_this<PyObject> {
 private:
  KlassPtr klass;
  PyDictPtr attributes;

 public:
  explicit PyObject(KlassPtr klass);
  [[nodiscard]] KlassPtr Klass() const { return klass; }
  [[nodiscard]] PyDictPtr Attributes();
  void SetAttributes(const PyDictPtr& _attributes) { attributes = _attributes; }
  void SetKlass(const KlassPtr& _klass) { klass = _klass; }
  virtual ~PyObject() = default;
  PyObject(const PyObject&) = default;
  PyObject& operator=(const PyObject&) = default;
  PyObject(PyObject&&) = default;
  PyObject& operator=(PyObject&&) = default;
  PyObjPtr add(const PyObjPtr& other) {
    return klass->add(shared_from_this(), other);
  }
  PyObjPtr sub(const PyObjPtr& other) {
    return klass->sub(shared_from_this(), other);
  }
  PyObjPtr mul(const PyObjPtr& other) {
    return klass->mul(shared_from_this(), other);
  }
  PyObjPtr floordiv(const PyObjPtr& other) {
    return klass->floordiv(shared_from_this(), other);
  }
  PyObjPtr mod(const PyObjPtr& other) {
    return klass->mod(shared_from_this(), other);
  }
  PyObjPtr truediv(const PyObjPtr& other) {
    return klass->truediv(shared_from_this(), other);
  }
  PyObjPtr matmul(const PyObjPtr& other) {
    return klass->matmul(shared_from_this(), other);
  }
  PyObjPtr pos() { return klass->pos(shared_from_this()); }
  PyObjPtr neg() { return klass->neg(shared_from_this()); }
  PyObjPtr invert() { return klass->invert(shared_from_this()); }
  PyObjPtr _and_(const PyObjPtr& other) {
    return klass->_and_(shared_from_this(), other);
  }
  PyObjPtr _or_(const PyObjPtr& other) {
    return klass->_or_(shared_from_this(), other);
  }
  PyObjPtr _xor_(const PyObjPtr& other) {
    return klass->_xor_(shared_from_this(), other);
  }
  PyObjPtr lshift(const PyObjPtr& other) {
    return klass->lshift(shared_from_this(), other);
  }
  PyObjPtr rshift(const PyObjPtr& other) {
    return klass->rshift(shared_from_this(), other);
  }
  PyObjPtr pow(const PyObjPtr& other) {
    return klass->pow(shared_from_this(), other);
  }
  PyObjPtr gt(const PyObjPtr& other) {
    return klass->gt(shared_from_this(), other);
  }
  PyObjPtr lt(const PyObjPtr& other) {
    return klass->lt(shared_from_this(), other);
  }
  PyObjPtr eq(const PyObjPtr& other) {
    return klass->eq(shared_from_this(), other);
  }
  PyObjPtr ge(const PyObjPtr& other) {
    return klass->ge(shared_from_this(), other);
  }
  PyObjPtr le(const PyObjPtr& other) {
    return klass->le(shared_from_this(), other);
  }
  PyObjPtr ne(const PyObjPtr& other) {
    return klass->ne(shared_from_this(), other);
  }
  PyObjPtr hash() { return klass->hash(shared_from_this()); }
  PyObjPtr repr() { return klass->repr(shared_from_this()); }
  PyObjPtr str() { return klass->str(shared_from_this()); }
  PyObjPtr getitem(const PyObjPtr& key) {
    return klass->getitem(shared_from_this(), key);
  }
  PyObjPtr setitem(const PyObjPtr& key, const PyObjPtr& value) {
    return klass->setitem(shared_from_this(), key, value);
  }
  PyObjPtr delitem(const PyObjPtr& key) {
    return klass->delitem(shared_from_this(), key);
  }
  PyObjPtr contains(const PyObjPtr& key) {
    return klass->contains(shared_from_this(), key);
  }
  PyObjPtr len() { return klass->len(shared_from_this()); }
  PyObjPtr boolean() { return klass->boolean(shared_from_this()); }
  PyObjPtr getattr(const PyObjPtr& key) {
    return klass->getattr(shared_from_this(), key);
  }
  PyObjPtr setattr(const PyObjPtr& key, const PyObjPtr& value) {
    return klass->setattr(shared_from_this(), key, value);
  }
  PyObjPtr iter() { return klass->iter(shared_from_this()); }
  PyObjPtr next() { return klass->next(shared_from_this()); }
  // TODO
  PyObjPtr _serialize_() { return klass->_serialize_(shared_from_this()); }
  template <typename T>
  std::shared_ptr<T> as() {
    return std::dynamic_pointer_cast<T>(shared_from_this());
  }

  template <typename T>
  bool is() {
    return std::dynamic_pointer_cast<T>(shared_from_this()) != nullptr;
  }
  static PyObjPtr Instance();
};

using PyObjPtr = std::shared_ptr<PyObject>;

class ObjectKlass : public Klass {
 public:
  explicit ObjectKlass() = default;
  static KlassPtr Self();
};

bool operator==(const PyObjPtr& lhs, const PyObjPtr& rhs);

bool operator<(const PyObjPtr& lhs, const PyObjPtr& rhs);

bool operator!=(const PyObjPtr& lhs, const PyObjPtr& rhs);

PyObjPtr ObjectInit(const PyObjPtr& args);

}  // namespace torchlight::Object

#endif  // TORCHLIGHT_OBJECT_PYOBJECT_H
