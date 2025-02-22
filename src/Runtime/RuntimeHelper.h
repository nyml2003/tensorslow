#ifndef TORCHLIGHT_RUNTIME_HELPER_H
#define TORCHLIGHT_RUNTIME_HELPER_H

#include "Object/PyObject.h"

namespace torchlight::Runtime {
Object::PyObjPtr RandInt(Object::PyObjPtr args);
Object::PyObjPtr Sleep(Object::PyObjPtr args);
Object::PyObjPtr Input(Object::PyObjPtr args);
}  // namespace torchlight::Runtime

#endif