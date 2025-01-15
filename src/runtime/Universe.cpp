#include "object/PyBoolean.h"
#include "object/PyBytes.h"
#include "object/PyDictionary.h"
#include "object/PyFloat.h"
#include "object/PyInteger.h"
#include "object/PyList.h"
#include "object/PyNone.h"
#include "object/PyString.h"
#include "runtime/Universe.h"

namespace torchlight::runtime {

UniversePtr universe = nullptr;

void BuildUniverse() {
  object::KlassPtr listKlass = std::make_shared<object::ListKlass>();
  object::KlassPtr dictKlass = std::make_shared<object::DictionaryKlass>();
  object::KlassPtr stringKlass = std::make_shared<object::StringKlass>();
  object::KlassPtr integerKlass = std::make_shared<object::IntegerKlass>();
  object::KlassPtr booleanKlass = std::make_shared<object::BooleanKlass>();
  object::KlassPtr noneKlass = std::make_shared<object::NoneKlass>();
  object::KlassPtr bytesKlass = std::make_shared<object::BytesKlass>();
  object::KlassPtr floatKlass = std::make_shared<object::FloatKlass>();

  object::PyObjPtr True = std::make_shared<object::PyBoolean>(true);

  object::PyObjPtr False = std::make_shared<object::PyBoolean>(false);

  object::PyObjPtr None = std::make_shared<object::PyNone>();

  universe = std::make_shared<Universe>(Universe{
    .stringKlass = stringKlass,
    .integerKlass = integerKlass,
    .booleanKlass = booleanKlass,
    .noneKlass = noneKlass,
    .listKlass = listKlass,
    .dictKlass = dictKlass,
    .bytesKlass = bytesKlass,
    .floatKlass = floatKlass,
    .True = True,
    .False = False,
    .None = None,
  });
}

}  // namespace torchlight::runtime