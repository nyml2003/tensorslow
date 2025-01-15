#ifndef TORCHLIGHT_RUNTIME_UNIVERSE_H
#define TORCHLIGHT_RUNTIME_UNIVERSE_H

#include "object/Klass.h"
#include "object/PyObject.h"

namespace torchlight::runtime {

struct Universe {
  object::KlassPtr stringKlass;
  object::KlassPtr integerKlass;
  object::KlassPtr booleanKlass;
  object::KlassPtr noneKlass;
  object::KlassPtr listKlass;
  object::KlassPtr dictKlass;
  object::KlassPtr bytesKlass;
  object::KlassPtr floatKlass;

  object::PyObjPtr True;
  object::PyObjPtr False;
  object::PyObjPtr None;
};

void BuildUniverse();

using UniversePtr = std::shared_ptr<Universe>;

extern UniversePtr universe;

}  // namespace torchlight::runtime

#endif