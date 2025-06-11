#ifndef TENSORSLOW_OBJECT_PYPROMISE_H
#define TENSORSLOW_OBJECT_PYPROMISE_H

#include "Object/Core/Klass.h"
#include "Object/Core/PyObject.h"
#include "Object/Object.h"

namespace tensorslow::Object {

class PyPromise;
using PyPromisePtr = std::shared_ptr<PyPromise>;

class PyPromise : public PyObject {
 public:
  enum class State { PENDING, FULFILLED, REJECTED };

  explicit PyPromise(PyObjPtr executor);

  PyPromisePtr Then(const PyObjPtr& onFulfilled);
  PyPromisePtr Catch(const PyObjPtr& onRejected);

  State GetState() const { return state; }
  PyObjPtr GetValue() const { return value; }

  void SetState(State newState) { state = newState; }

  void SetValue(const PyObjPtr& newValue) { value = newValue; }

  PyListPtr GetOnFulfilledCallbacks() const { return onFulfilledCallbacks; }

  PyListPtr GetOnRejectedCallbacks() const { return onRejectedCallbacks; }

 private:
  State state;
  PyObjPtr value;
  PyListPtr onFulfilledCallbacks;
  PyListPtr onRejectedCallbacks;
  PyObjPtr executor;
};

PyPromisePtr CreatePyPromise(const PyObjPtr& executor);

class PromiseKlass : public Klass {
 public:
  static KlassPtr Self();
  void Initialize() override;
  PyObjPtr init(const PyObjPtr& typeObj, const PyObjPtr& args) override;
};

}  // namespace tensorslow::Object

#endif  // TENSORSLOW_OBJECT_PYPROMISE_H