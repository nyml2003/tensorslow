#include "Object/Iterator/PyGenerator.h"

namespace torchlight::Object {

PyObjPtr GeneratorKlass::next(const PyObjPtr& obj) {
  return obj->as<PyGenerator>()->Next();
}

}  // namespace torchlight::Object