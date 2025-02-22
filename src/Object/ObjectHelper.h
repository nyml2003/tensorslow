#ifndef TORCHLIGHT_OBJECT_HELPER_H
#define TORCHLIGHT_OBJECT_HELPER_H

#include <functional>
#include "Common.h"
#include "Object/Object.h"
#include "Object/PyObject.h"

namespace torchlight::Object {
PyObjPtr Invoke(
  const PyObjPtr& obj,
  const PyObjPtr& methodName,
  std::initializer_list<PyObjPtr> arguments
);
void BasicKlassLoad();
bool IsType(const PyObjPtr& obj, const KlassPtr& type);
void ForEach(
  const PyObjPtr& obj,
  const std::function<
    void(const PyObjPtr& value, Index index, const PyObjPtr& list)>& func
);
}  // namespace torchlight::Object

#endif