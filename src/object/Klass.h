#ifndef TORCHLIGHT_OBJECT_KLASS_H
#define TORCHLIGHT_OBJECT_KLASS_H

#include "collections/String.h"
#include "object/PyObject.h"
#include "object/common.h"

namespace torchlight::object {
class Klass {
 private:
  collections::String name;

 public:
  explicit Klass(collections::String value);

  // Copy constructor
  Klass(const Klass& other) = delete;

  // Copy assignment operator
  Klass& operator=(const Klass& other) = delete;

  // Move constructor
  Klass(Klass&& other) noexcept = delete;

  // Move assignment operator
  Klass& operator=(Klass&& other) noexcept = delete;

  virtual ~Klass();

  [[nodiscard]] PyStrPtr Name() const;

  virtual PyObjPtr add(PyObjPtr lhs, PyObjPtr rhs);

  virtual PyObjPtr sub(PyObjPtr lhs, PyObjPtr rhs);

  virtual PyObjPtr mul(PyObjPtr lhs, PyObjPtr rhs);

  virtual PyObjPtr div(PyObjPtr lhs, PyObjPtr rhs);

  virtual PyObjPtr gt(PyObjPtr lhs, PyObjPtr rhs);

  virtual PyObjPtr lt(PyObjPtr lhs, PyObjPtr rhs);

  virtual PyObjPtr eq(PyObjPtr lhs, PyObjPtr rhs);

  virtual PyObjPtr ge(PyObjPtr lhs, PyObjPtr rhs);

  virtual PyObjPtr le(PyObjPtr lhs, PyObjPtr rhs);

  virtual PyObjPtr ne(PyObjPtr lhs, PyObjPtr rhs);

  virtual PyObjPtr repr(PyObjPtr obj);

  virtual PyObjPtr _bool_(PyObjPtr obj);
};

}  // namespace torchlight::object

#endif  // TORCHLIGHT_OBJECT_KLASS_H