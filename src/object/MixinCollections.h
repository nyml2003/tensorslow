#ifndef TORCHLIGHT_OBJECT_MIXIN_COLLECTIONS_H
#define TORCHLIGHT_OBJECT_MIXIN_COLLECTIONS_H

#include "Object/PyObject.h"
namespace torchlight::Collections {

std::string ToCppString(const Object::PyObjPtr& obj);
}  // namespace torchlight::Collections

#endif