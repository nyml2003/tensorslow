#ifndef TORCHLIGHT_OBJECT_PYOBJECT_H
#define TORCHLIGHT_OBJECT_PYOBJECT_H

#include "Object/Klass.h"
#include "Object/Object.h"

namespace torchlight::Object {

class PyObject : public std::enable_shared_from_this<PyObject> {
 private:
  KlassPtr klass;

 public:
  explicit PyObject(KlassPtr klass) : klass(std::move(klass)) {}
  [[nodiscard]] KlassPtr Klass() const { return klass; }
  virtual ~PyObject() = default;
  PyObject(const PyObject&) = delete;
  PyObject& operator=(const PyObject&) = delete;
  PyObject(PyObject&&) = delete;
  PyObject& operator=(PyObject&&) = delete;
  PyObjPtr add(const PyObjPtr& other) {
    return klass->add(shared_from_this(), other);
  }
  PyObjPtr sub(const PyObjPtr& other) {
    return klass->sub(shared_from_this(), other);
  }
  PyObjPtr mul(const PyObjPtr& other) {
    return klass->mul(shared_from_this(), other);
  }
  PyObjPtr div(const PyObjPtr& other) {
    return klass->div(shared_from_this(), other);
  }
  PyObjPtr matmul(const PyObjPtr& other) {
    return klass->matmul(shared_from_this(), other);
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
};

using PyObjPtr = std::shared_ptr<PyObject>;

bool operator==(const PyObjPtr& lhs, const PyObjPtr& rhs);

bool operator!=(const PyObjPtr& lhs, const PyObjPtr& rhs);

void DebugPrint(const PyObjPtr& obj);

PyObjPtr Print(const PyObjPtr& args);

PyObjPtr Len(const PyObjPtr& args);

class ObjectKlass : public Klass {
 public:
  explicit ObjectKlass() = default;
  static KlassPtr Self();
};

}  // namespace torchlight::Object

#endif  // TORCHLIGHT_OBJECT_PYOBJECT_H
