#ifndef TORCHLIGHT_OBJECT_PYINTEGER_H
#define TORCHLIGHT_OBJECT_PYINTEGER_H

#include "collections/Integer.h"
#include "object/Klass.h"
#include "object/PyObject.h"
#include "object/common.h"

namespace torchlight::object {
class PyInteger : public PyObject {
 private:
  collections::Integer value;

 public:
  explicit PyInteger(collections::Integer value);

  [[nodiscard]] collections::Integer Value() const;
};

using PyIntPtr = std::shared_ptr<PyInteger>;

class IntegerKlass : public Klass {
 public:
  explicit IntegerKlass();

  static KlassPtr Self();

  ~IntegerKlass() override;

  PyObjPtr add(PyObjPtr lhs, PyObjPtr rhs) override;

  PyObjPtr sub(PyObjPtr lhs, PyObjPtr rhs) override;

  PyObjPtr mul(PyObjPtr lhs, PyObjPtr rhs) override;

  PyObjPtr div(PyObjPtr lhs, PyObjPtr rhs) override;

  PyObjPtr gt(PyObjPtr lhs, PyObjPtr rhs) override;

  PyObjPtr lt(PyObjPtr lhs, PyObjPtr rhs) override;

  PyObjPtr eq(PyObjPtr lhs, PyObjPtr rhs) override;

  PyObjPtr ge(PyObjPtr lhs, PyObjPtr rhs) override;

  PyObjPtr le(PyObjPtr lhs, PyObjPtr rhs) override;

  PyObjPtr ne(PyObjPtr lhs, PyObjPtr rhs) override;

  PyObjPtr repr(PyObjPtr obj) override;
};

}  // namespace torchlight::object

#endif  // TORCHLIGHT_OBJECT_PYINTEGER_H