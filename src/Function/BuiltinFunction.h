#ifndef TORCHLIGHT_BUILTIN_FUNCTION_H
#define TORCHLIGHT_BUILTIN_FUNCTION_H
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
Object::PyObjPtr Time(const Object::PyObjPtr& args);
Object::PyObjPtr Range(const Object::PyObjPtr& args);
Object::PyObjPtr Type(const Object::PyObjPtr& args);
Object::PyObjPtr BuildClass(const Object::PyObjPtr& args);
auto LogisticLoss(const Object::PyObjPtr& args) noexcept -> Object::PyObjPtr;
auto LogisticLossDerivative(const Object::PyObjPtr& args) noexcept
  -> Object::PyObjPtr;
auto Sum(const Object::PyObjPtr& args) noexcept -> Object::PyObjPtr;
auto Log(const Object::PyObjPtr& args) noexcept -> Object::PyObjPtr;
auto SoftMax(const Object::PyObjPtr& args) noexcept -> Object::PyObjPtr;
auto Max(const Object::PyObjPtr& args) noexcept -> Object::PyObjPtr;
auto ArgMax(const Object::PyObjPtr& args) noexcept -> Object::PyObjPtr;
auto Hash(const Object::PyObjPtr& args) noexcept -> Object::PyObjPtr;
}  // namespace torchlight::Function

#endif