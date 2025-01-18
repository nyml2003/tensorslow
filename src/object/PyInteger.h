#ifndef TORCHLIGHT_OBJECT_PYINTEGER_H
#define TORCHLIGHT_OBJECT_PYINTEGER_H

#include "Collections/Integer.h"
#include "Object/Common.h"
#include "Object/Klass.h"
#include "Object/PyObject.h"

namespace torchlight::Object {

class PyInteger : public PyObject {
 private:
  Collections::Integer value;

 public:
  explicit PyInteger(Collections::Integer value);

  [[nodiscard]] Collections::Integer Value() const;
};

using PyIntPtr = std::shared_ptr<PyInteger>;

PyIntPtr CreatePyInteger(Collections::Integer value);

PyIntPtr CreatePyInteger(uint64_t value);

class IntegerKlass : public Klass {
 public:
  explicit IntegerKlass();

  static KlassPtr Self();

  ~IntegerKlass() override;

  IntegerKlass(const IntegerKlass& other) = delete;

  IntegerKlass& operator=(const IntegerKlass& other) = delete;

  IntegerKlass(IntegerKlass&& other) noexcept = delete;

  IntegerKlass& operator=(IntegerKlass&& other) noexcept = delete;

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

  PyObjPtr _serialize_(PyObjPtr obj) override;
};

}  // namespace torchlight::Object

#endif  // TORCHLIGHT_OBJECT_PYINTEGER_H