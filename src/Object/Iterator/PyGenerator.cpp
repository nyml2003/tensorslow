#include "Object/Iterator/PyGenerator.h"

namespace tensorslow::Object {

PyObjPtr GeneratorKlass::next(const PyObjPtr& obj) {
  return obj->as<PyGenerator>()->Next();
}

}  // namespace tensorslow::Object