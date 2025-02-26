#ifndef TORCHLIGHT_RUNTIME_GENESIS_H
#define TORCHLIGHT_RUNTIME_GENESIS_H

#include "Object/PyObject.h"

namespace torchlight::Runtime {

Object::PyObjPtr Genesis();

void RuntimeKlassLoad();

Object::PyObjPtr BuildClass(const Object::PyObjPtr& args);
}  // namespace torchlight::Runtime

#endif