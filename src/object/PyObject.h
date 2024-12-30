#ifndef TORCHLIGHT_OBJECT_PYOBJECT_H
#define TORCHLIGHT_OBJECT_PYOBJECT_H

#include "object/common.h"

namespace torchlight::object {

class PyObject : public std::enable_shared_from_this<PyObject> {
 private:
  KlassPtr klass;

 protected:
  void setKlass(KlassPtr klass);

 public:
  explicit PyObject(KlassPtr klass);

  [[nodiscard]] KlassPtr Klass() const;

  virtual ~PyObject() = default;

  PyObject(const PyObject&) = delete;

  PyObject& operator=(const PyObject&) = delete;

  PyObject(PyObject&&) = delete;

  PyObject& operator=(PyObject&&) = delete;

  PyObjPtr add(PyObjPtr other);

  PyObjPtr sub(PyObjPtr other);

  PyObjPtr mul(PyObjPtr other);

  PyObjPtr div(PyObjPtr other);

  PyObjPtr gt(PyObjPtr other);

  PyObjPtr lt(PyObjPtr other);

  PyObjPtr eq(PyObjPtr other);

  PyObjPtr ge(PyObjPtr other);

  PyObjPtr le(PyObjPtr other);

  PyObjPtr ne(PyObjPtr other);

  PyObjPtr repr();

  PyObjPtr _bool_();

  PyObjPtr _serialize_();
};

using PyObjPtr = std::shared_ptr<PyObject>;

void print(PyObjPtr obj);

}  // namespace torchlight::object

#endif  // TORCHLIGHT_OBJECT_PYOBJECT_H
