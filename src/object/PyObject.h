#ifndef TORCHLIGHT_OBJECT_PYOBJECT_H
#define TORCHLIGHT_OBJECT_PYOBJECT_H

#include "object/common.h"

namespace torchlight::object {

class PyObject : public std::enable_shared_from_this<PyObject> {
 private:
  KlassPtr klass;

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

  PyObjPtr repr();
};

using PyObjPtr = std::shared_ptr<PyObject>;

}  // namespace torchlight::object

#endif  // TORCHLIGHT_OBJECT_PYOBJECT_H
