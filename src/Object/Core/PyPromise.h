#ifndef TENSORSLOW_OBJECT_PYPROMISE_H
#define TENSORSLOW_OBJECT_PYPROMISE_H

#include "Object/Core/Klass.h"
#include "Object/Core/PyObject.h"
#include "Object/Function/PyNativeFunction.h"

namespace tensorslow::Object {

class PyPromise;
using PyPromisePtr = std::shared_ptr<PyPromise>;


class PyPromise : public PyObject {
 public:
  enum class State { PENDING, FULFILLED, REJECTED };

  explicit PyPromise(const PyNativeFunctionPtr& executor);

  PyPromisePtr Then(const PyNativeFunctionPtr& onFulfilled);
  PyPromisePtr Catch(const PyNativeFunctionPtr& onRejected);

  State GetState() const { return state; }
  PyObjPtr GetValue() const { return value; }

 private:
  State state;
  PyObjPtr value;
  PyListPtr onFulfilledCallbacks;
  PyListPtr onRejectedCallbacks;
};

inline PyPromisePtr CreatePyPromise(const PyNativeFunctionPtr& executor) {
  return std::make_shared<PyPromise>(executor);
}

class PromiseKlass : public Klass {
 public:
  static KlassPtr Self();
  void Initialize() override;
};

}  // namespace tensorslow::Object

#endif  // TENSORSLOW_OBJECT_PYPROMISE_H