#ifndef TORCHLIGHT_OBJECT_HELPER_H
#define TORCHLIGHT_OBJECT_HELPER_H
#include "Common.h"
#include "Object/Object.h"
#include "Object/PyObject.h"

#include <functional>

namespace torchlight::Object {
PyObjPtr
Invoke(const PyObjPtr& obj, const PyObjPtr& methodName, const PyListPtr& args);
void BasicKlassLoad();
void ForEach(
  const PyObjPtr& obj,
  const std::function<
    void(const PyObjPtr& value, Index index, const PyObjPtr& obj)>& func
);
PyObjPtr Map(
  const PyObjPtr& iterable,
  const std::function<PyObjPtr(const PyObjPtr& value)>& func
);
PyObjPtr SolveStr(const KlassPtr& klass, const PyObjPtr& self);
// 内置函数str
PyObjPtr Str(const PyObjPtr& args);
// object.__str__
PyObjPtr KlassStr(const PyObjPtr& args);
// 内置函数repr
PyObjPtr Repr(const PyObjPtr& args);
// object.__repr__
PyObjPtr KlassRepr(const PyObjPtr& args);
// 内置函数bool
PyObjPtr Bool(const PyObjPtr& args);
// object.__bool__
PyObjPtr KlassBool(const PyObjPtr& args);
PyObjPtr Identity(const PyObjPtr& obj);
PyObjPtr RandInt(const PyObjPtr& args);
PyObjPtr Sleep(const PyObjPtr& args);
PyObjPtr Input(const PyObjPtr& args);
PyObjPtr Normal(const PyObjPtr& args);
PyObjPtr Shuffle(const PyObjPtr& args);
PyObjPtr CreatePyClass(const PyTypePtr& type);
PyObjPtr GetBases(const PyObjPtr& args);
PyObjPtr GetMro(const PyObjPtr& args);
PyObjPtr GetDict(const PyObjPtr& args);
PyListPtr MergeMro(const PyListPtr& mros);
PyListPtr ComputeMro(const PyTypePtr& type);
bool FirstOrNotInMro(const PyListPtr& mro, const PyTypePtr& type);
bool CouldTypePlaceAhead(
  const PyListPtr& mros,
  const PyTypePtr& type,
  Index ignore
);
void CleanMros(const PyListPtr& mros);
void DebugPrint(const PyObjPtr& obj);
PyObjPtr Print(const PyObjPtr& args);
PyObjPtr Len(const PyObjPtr& args);
PyObjPtr Next(const PyObjPtr& args);
KlassPtr CreatePyKlass(
  const PyStrPtr& name,
  const PyDictPtr& attributes,
  const PyListPtr& super
);
void LoadClass(const PyStrPtr& name, const KlassPtr& klass);
void ConfigureBasicAttributes(const KlassPtr& klass);
PyObjPtr GetAttr(const PyObjPtr& obj, const PyStrPtr& attrName) noexcept;
PyObjPtr AttrWrapper(const PyObjPtr& obj, const PyObjPtr& attr);
}  // namespace torchlight::Object

#endif