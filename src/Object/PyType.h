#ifndef TORCHLIGHT_OBJECT_PYTYPE_H
#define TORCHLIGHT_OBJECT_PYTYPE_H

#include "Object/PyObject.h"

namespace torchlight::Object {

class TypeKlass : public Klass {
 public:
  explicit TypeKlass() = default;

  static KlassPtr Self() {
    static KlassPtr instance = std::make_shared<TypeKlass>();
    return instance;
  }

  static void Initialize();

  PyObjPtr eq(const PyObjPtr& lhs, const PyObjPtr& rhs) override;

  PyObjPtr repr(const PyObjPtr& obj) override;


};

class PyType : public PyObject {
 private:
  KlassPtr owner;

 public:
  explicit PyType(KlassPtr owner)
    : PyObject(TypeKlass::Self()), owner(std::move(owner)) {}

  [[nodiscard]] KlassPtr Owner() const { return owner; }
};

using PyTypePtr = std::shared_ptr<PyType>;

inline PyObjPtr CreatePyType(KlassPtr owner) {
  return std::make_shared<PyType>(owner);
}
}  // namespace torchlight::Object

#endif