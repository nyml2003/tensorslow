#ifndef TORCHLIGHT_OBJECT_HELPER_H
#define TORCHLIGHT_OBJECT_HELPER_H
#include "Common.h"
#include "Object/PyObject.h"

#include <functional>

namespace torchlight::Object {
PyObjPtr Invoke(
  const PyObjPtr& obj,
  const PyObjPtr& methodName,
  std::initializer_list<PyObjPtr> arguments
);
void BasicKlassLoad();
void ForEach(
  const PyObjPtr& obj,
  const std::function<
    void(const PyObjPtr& value, Index index, const PyObjPtr& obj)>& func
);
PyObjPtr Identity(const PyObjPtr& obj);

}  // namespace torchlight::Object

#endif