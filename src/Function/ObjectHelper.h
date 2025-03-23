#ifndef TORCHLIGHT_FUNCTION_H
#define TORCHLIGHT_FUNCTION_H
#include "Common.h"
#include "Object/Core/PyObject.h"
#include "Object/Object.h"

#include <functional>

namespace torchlight::Function {
Object::PyObjPtr Identity(const Object::PyObjPtr& args);
Object::PyObjPtr RandInt(const Object::PyObjPtr& args);
Object::PyObjPtr Sleep(const Object::PyObjPtr& args);
Object::PyObjPtr Input(const Object::PyObjPtr& args);
Object::PyObjPtr Normal(const Object::PyObjPtr& args);
Object::PyObjPtr Shuffle(const Object::PyObjPtr& args);
void DebugPrint(const Object::PyObjPtr& obj);
Object::PyObjPtr Print(const Object::PyObjPtr& args);
Object::PyObjPtr Len(const Object::PyObjPtr& args);
Object::PyObjPtr Next(const Object::PyObjPtr& args);
Object::PyObjPtr Iter(const Object::PyObjPtr& args);
}  // namespace torchlight::Object

#endif