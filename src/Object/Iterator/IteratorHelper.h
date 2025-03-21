#ifndef TORCHLIGHT_OBJECT_ITERATOR_HELPER_H
#define TORCHLIGHT_OBJECT_ITERATOR_HELPER_H

#include <functional>
#include "Object/Object.h"
#include "Common.h"

namespace torchlight::Object {
void ForEach(
  const Object::PyObjPtr& obj,
  const std::function<void(
    const Object::PyObjPtr& value,
    Index index,
    const Object::PyObjPtr& obj
  )>& func
);
Object::PyObjPtr Map(
  const Object::PyObjPtr& iterable,
  const std::function<Object::PyObjPtr(const Object::PyObjPtr& value)>& func
);
}  // namespace torchlight::Object

#endif