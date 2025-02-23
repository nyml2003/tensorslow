#ifndef TORCHLIGHT_OBJECT_PYINTEGER_H
#define TORCHLIGHT_OBJECT_PYINTEGER_H

#include "Collections/Integer.h"
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

class IntegerKlass : public Klass {
 public:
  explicit IntegerKlass();

  static KlassPtr Self();

  ~IntegerKlass() override;

  IntegerKlass(const IntegerKlass& other) = delete;

  IntegerKlass& operator=(const IntegerKlass& other) = delete;

  IntegerKlass(IntegerKlass&& other) noexcept = delete;

  IntegerKlass& operator=(IntegerKlass&& other) noexcept = delete;

  PyObjPtr allocateInstance(const PyObjPtr& klass, const PyObjPtr& args)
    override;

  PyObjPtr add(const PyObjPtr& lhs, const PyObjPtr& rhs) override;

  PyObjPtr sub(const PyObjPtr& lhs, const PyObjPtr& rhs) override;

  PyObjPtr mul(const PyObjPtr& lhs, const PyObjPtr& rhs) override;

  PyObjPtr div(const PyObjPtr& lhs, const PyObjPtr& rhs) override;

  PyObjPtr gt(const PyObjPtr& lhs, const PyObjPtr& rhs) override;

  PyObjPtr eq(const PyObjPtr& lhs, const PyObjPtr& rhs) override;

  PyObjPtr repr(const PyObjPtr& obj) override;

  PyObjPtr _serialize_(const PyObjPtr& obj) override;

  void Initialize() override;
};

PyObjPtr CreatePyInteger(Collections::Integer value);

PyObjPtr CreatePyInteger(uint64_t value);

uint64_t ToU64(const PyObjPtr& obj);
using PyIntPtr = std::shared_ptr<PyInteger>;

}  // namespace torchlight::Object

#endif  // TORCHLIGHT_OBJECT_PYINTEGER_H