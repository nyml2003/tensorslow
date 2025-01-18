#ifndef TORCHLIGHT_OBJECT_MIXIN_COLLECTIONS_H
#define TORCHLIGHT_OBJECT_MIXIN_COLLECTIONS_H
#include "Collections/StringHelper.h"
#include "Object/MixinCollections.h"
#include "Object/PyString.h"
namespace torchlight::Collections {

std::string ToCppString(const Object::PyObjPtr& obj) {
  auto repr = obj->repr();
  if (repr->Klass() != Object::StringKlass::Self()) {
    throw std::runtime_error("obj is not a string");
  }
  auto str = std::dynamic_pointer_cast<Object::PyString>(repr);
  return ToCppString(str->Value());
}
}  // namespace torchlight::Collections

#endif