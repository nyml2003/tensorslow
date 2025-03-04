#include "Runtime/PyGenerator.h"

namespace torchlight::Runtime {

Object::PyObjPtr GeneratorKlass::next(const Object::PyObjPtr& obj) {
  return obj->as<PyGenerator>()->Next();
}

}  // namespace torchlight::Runtime