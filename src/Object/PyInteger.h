#ifndef TORCHLIGHT_OBJECT_PYINTEGER_H
#define TORCHLIGHT_OBJECT_PYINTEGER_H

#include "Collections/Integer.h"
#include "Collections/IntegerHelper.h"
#include "Object/Klass.h"
#include "Object/PyString.h"

namespace torchlight::Object {

class IntegerKlass : public Klass {
 public:
  explicit IntegerKlass() = default;
  static KlassPtr Self() {
    static KlassPtr instance = std::make_shared<IntegerKlass>();
    LoadClass(CreatePyString("int")->as<PyString>(), instance);
    ConfigureBasicAttributes(instance);
    return instance;
  }
  PyObjPtr construct(const PyObjPtr& klass, const PyObjPtr& args) override;
  PyObjPtr add(const PyObjPtr& lhs, const PyObjPtr& rhs) override;
  PyObjPtr sub(const PyObjPtr& lhs, const PyObjPtr& rhs) override;
  PyObjPtr mul(const PyObjPtr& lhs, const PyObjPtr& rhs) override;
  PyObjPtr div(const PyObjPtr& lhs, const PyObjPtr& rhs) override;
  PyObjPtr gt(const PyObjPtr& lhs, const PyObjPtr& rhs) override;
  PyObjPtr eq(const PyObjPtr& lhs, const PyObjPtr& rhs) override;
  PyObjPtr repr(const PyObjPtr& obj) override;
  PyObjPtr _serialize_(const PyObjPtr& obj) override;
};

PyObjPtr CreatePyInteger(Collections::Integer value);

PyObjPtr CreatePyInteger(uint64_t value);

class PyInteger;

using PyIntPtr = std::shared_ptr<PyInteger>;

class PyInteger : public PyObject {
  friend class IntegerKlass;

 private:
  Collections::Integer value;

 public:
  explicit PyInteger(Collections::Integer value)
    : PyObject(IntegerKlass::Self()), value(std::move(value)) {}

  [[nodiscard]] Index ToU64() const { return Collections::ToU64(value); }
};

}  // namespace torchlight::Object

#endif  // TORCHLIGHT_OBJECT_PYINTEGER_H