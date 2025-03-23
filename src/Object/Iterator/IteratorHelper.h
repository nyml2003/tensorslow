#ifndef TORCHLIGHT_OBJECT_ITERATOR_HELPER_H
#define TORCHLIGHT_OBJECT_ITERATOR_HELPER_H

#include <functional>
#include "Common.h"
#include "Object/Object.h"

namespace torchlight::Object {
void ForEach(
  const PyObjPtr& obj,
  const std::function<
    void(const PyObjPtr& value, Index index, const PyObjPtr& obj)>& func
);
PyObjPtr Map(
  const PyObjPtr& iterable,
  const std::function<PyObjPtr(const PyObjPtr& value)>& func
);
}  // namespace torchlight::Object

#endif