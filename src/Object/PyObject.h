#ifndef TORCHLIGHT_OBJECT_PYOBJECT_H
#define TORCHLIGHT_OBJECT_PYOBJECT_H

#include "Object/Klass.h"
#include "Object/Object.h"

namespace torchlight::Object {

class PyObject : public std::enable_shared_from_this<PyObject> {
 private:
  KlassPtr klass;

 protected:
  void setKlass(KlassPtr klass);

 public:
  explicit PyObject(KlassPtr klass);

  [[nodiscard]] KlassPtr Klass() const;

  virtual ~PyObject();

  PyObject(const PyObject&) = delete;

  PyObject& operator=(const PyObject&) = delete;

  PyObject(PyObject&&) = delete;

  PyObject& operator=(PyObject&&) = delete;

  PyObjPtr add(PyObjPtr other);

  PyObjPtr sub(PyObjPtr other);

  PyObjPtr mul(PyObjPtr other);

  PyObjPtr div(PyObjPtr other);

  PyObjPtr matmul(PyObjPtr other);

  PyObjPtr gt(PyObjPtr other);

  PyObjPtr lt(PyObjPtr other);

  PyObjPtr eq(PyObjPtr other);

  PyObjPtr ge(PyObjPtr other);

  PyObjPtr le(PyObjPtr other);

  PyObjPtr ne(PyObjPtr other);

  PyObjPtr repr();

  PyObjPtr str();

  PyObjPtr getitem(PyObjPtr key);

  PyObjPtr setitem(PyObjPtr key, PyObjPtr value);

  PyObjPtr delitem(PyObjPtr key);

  PyObjPtr contains(PyObjPtr key);

  PyObjPtr len();

  PyObjPtr _bool_();

  PyObjPtr _serialize_();

  PyObjPtr getattr(PyObjPtr key);

  PyObjPtr setattr(PyObjPtr key, PyObjPtr value);

  PyObjPtr iter();

  PyObjPtr next();
};

bool operator==(const PyObjPtr& lhs, const PyObjPtr& rhs);

bool operator!=(const PyObjPtr& lhs, const PyObjPtr& rhs);

void DebugPrint(const PyObjPtr& obj);

PyObjPtr Print(const PyObjPtr& args);

PyObjPtr Len(const PyObjPtr& args);

using PyObjPtr = std::shared_ptr<PyObject>;

}  // namespace torchlight::Object

#endif  // TORCHLIGHT_OBJECT_PYOBJECT_H
