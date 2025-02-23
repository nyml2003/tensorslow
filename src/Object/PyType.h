#ifndef TORCHLIGHT_OBJECT_PYTYPE_H
#define TORCHLIGHT_OBJECT_PYTYPE_H

#include "Object/Klass.h"
#include "Object/PyObject.h"

namespace torchlight::Object {
class PyType : public PyObject {
 private:
  KlassPtr owner;

 public:
  explicit PyType(KlassPtr owner);

  [[nodiscard]] KlassPtr Owner() const;
};

class TypeKlass : public Klass {
 public:
  explicit TypeKlass();

  static KlassPtr Self();

  void Initialize() override;

  PyObjPtr repr(const PyObjPtr& obj) override;
};

using PyTypePtr = std::shared_ptr<PyType>;

PyObjPtr CreatePyType(KlassPtr owner);
}  // namespace torchlight::Object

#endif