#ifndef TORCHLIGHT_RUNTIME_GENESIS_H
#define TORCHLIGHT_RUNTIME_GENESIS_H

#include "Object/Common.h"

namespace torchlight::Runtime {

Object::PyObjPtr Genesis();

void RuntimeKlassLoad();
}  // namespace torchlight::Runtime

#endif