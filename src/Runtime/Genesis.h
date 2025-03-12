#ifndef TORCHLIGHT_RUNTIME_GENESIS_H
#define TORCHLIGHT_RUNTIME_GENESIS_H

#include "Object/PyObject.h"

namespace torchlight::Runtime {

Object::PyObjPtr Genesis();

Object::PyObjPtr BuildClass(const Object::PyObjPtr& args);
Object::PyObjPtr Type(const Object::PyObjPtr& args);

Object::PyObjPtr BuiltinMatrix();
}  // namespace torchlight::Runtime

#endif