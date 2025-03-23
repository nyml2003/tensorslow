#include "Object/Iterator/IteratorHelper.h"
#include "Object/Iterator/Iterator.h"

namespace torchlight::Object {
void ForEach(
  const PyObjPtr& obj,
  const std::function<
    void(const PyObjPtr& value, Index index, const PyObjPtr& obj)>& func
) {
  auto iter = obj->iter();
  auto iterable = iter->as<IIterator>();
  if (!iterable) {
    throw std::runtime_error("object is not iterable");
  }
  auto value = iter->next();
  while (!value->is<IterDone>()) {
    func(value, iterable->CurrentIndex(), obj);
    value = iter->next();
  }
}

PyObjPtr Map(
  const PyObjPtr& iterable,
  const std::function<PyObjPtr(const PyObjPtr& value)>& func
) {
  auto iter = iterable->iter();
  auto iterableObj = iter->as<IIterator>();
  if (!iterableObj) {
    throw std::runtime_error("object is not iterable");
  }
  auto value = iter->next();
  Collections::List<PyObjPtr> result;
  while (!value->is<IterDone>()) {
    result.Push(func(value));
    value = iter->next();
  }
  return CreatePyList(result)->as<PyList>();
}

}  // namespace torchlight::Object