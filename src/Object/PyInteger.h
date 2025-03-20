#ifndef TORCHLIGHT_OBJECT_PYINTEGER_H
#define TORCHLIGHT_OBJECT_PYINTEGER_H

#include "Collections/Integer.h"
#include "Collections/IntegerHelper.h"
#include "Object/Klass.h"
#include "Object/Object.h"
#include "Object/ObjectHelper.h"
#include "Object/PyString.h"

namespace torchlight::Object {

class IntegerKlass : public Klass {
 public:
  explicit IntegerKlass() = default;
  static KlassPtr Self() {
    static KlassPtr instance = std::make_shared<IntegerKlass>();
    return instance;
  }
  static void Initialize();
  PyObjPtr init(const PyObjPtr& klass, const PyObjPtr& args) override;
  PyObjPtr add(const PyObjPtr& lhs, const PyObjPtr& rhs) override;
  PyObjPtr sub(const PyObjPtr& lhs, const PyObjPtr& rhs) override;
  PyObjPtr mul(const PyObjPtr& lhs, const PyObjPtr& rhs) override;
  PyObjPtr floordiv(const PyObjPtr& lhs, const PyObjPtr& rhs) override;
  PyObjPtr truediv(const PyObjPtr& lhs, const PyObjPtr& rhs) override;
  PyObjPtr pow(const PyObjPtr& lhs, const PyObjPtr& rhs) override;
  PyObjPtr pos(const PyObjPtr& obj) override;
  PyObjPtr neg(const PyObjPtr& obj) override;
  PyObjPtr invert(const PyObjPtr& obj) override;
  PyObjPtr boolean(const PyObjPtr& obj) override;
  PyObjPtr hash(const PyObjPtr& obj) override;
  PyObjPtr _and_(const PyObjPtr& lhs, const PyObjPtr& rhs) override;
  PyObjPtr _or_(const PyObjPtr& lhs, const PyObjPtr& rhs) override;
  PyObjPtr _xor_(const PyObjPtr& lhs, const PyObjPtr& rhs) override;
  PyObjPtr lshift(const PyObjPtr& lhs, const PyObjPtr& rhs) override;
  PyObjPtr rshift(const PyObjPtr& lhs, const PyObjPtr& rhs) override;
  PyObjPtr mod(const PyObjPtr& lhs, const PyObjPtr& rhs) override;
  PyObjPtr gt(const PyObjPtr& lhs, const PyObjPtr& rhs) override;
  PyObjPtr eq(const PyObjPtr& lhs, const PyObjPtr& rhs) override;
  PyObjPtr repr(const PyObjPtr& obj) override;
  PyObjPtr str(const PyObjPtr& obj) override;
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

  [[nodiscard]] bool IsBigNumber() const { return Collections::IsBigNumber(value); }

  Collections::Integer::IntSign GetSign() const { return value.GetSign(); }

  int64_t ToI64() const { return Collections::ToI64(value); }

  bool LessThan(const PyObjPtr& other) const; 
};

}  // namespace torchlight::Object

#endif  // TORCHLIGHT_OBJECT_PYINTEGER_H