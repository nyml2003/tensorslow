#ifndef TORCHLIGHT_OBJECT_HELPER_H
#define TORCHLIGHT_OBJECT_HELPER_H

#include "Object/Common.h"

namespace torchlight::Object {
PyObjPtr Invoke(
  PyObjPtr obj,
  PyObjPtr methodName,
  std::initializer_list<PyObjPtr> arguments
);
}

#endif