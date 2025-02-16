#ifndef TORCHLIGHT_OBJECT_HELPER_H
#define TORCHLIGHT_OBJECT_HELPER_H

#include "Object/Common.h"

namespace torchlight::Object {
PyObjPtr Invoke(
  const PyObjPtr& obj,
  const PyObjPtr& methodName,
  std::initializer_list<PyObjPtr> arguments
);
void BasicKlassLoad();
}  // namespace torchlight::Object

#endif