#ifndef TORCHLIGHT_OBJECT_KLASS_H
#define TORCHLIGHT_OBJECT_KLASS_H

#include <stdexcept>
#include "Object/Object.h"

namespace torchlight::Object {
class Klass {
 private:
  PyStrPtr name;
  PyDictPtr attributes;
  PyTypePtr type;
  PyListPtr super;
  PyListPtr mro;
  bool initialized = false;

  void LookupInMro(const PyObjPtr& obj, const PyObjPtr& key);

 protected:
 public:
  static void SetDualOutput(const std::string& filename);
  explicit Klass();
  void SetName(const PyObjPtr& name);
  void SetAttributes(const PyObjPtr& attributes);
  void SetType(const PyObjPtr& type);

  // Copy constructor
  Klass(const Klass& other) = delete;

  // Copy assignment operator
  Klass& operator=(const Klass& other) = delete;

  // Move constructor
  Klass(Klass&& other) noexcept = delete;

  // Move assignment operator
  Klass& operator=(Klass&& other) noexcept = delete;

  virtual ~Klass();

  virtual void Initialize();

  [[nodiscard]] PyStrPtr Name() const;

  [[nodiscard]] PyTypePtr Type() const;

  [[nodiscard]] PyDictPtr Attributes() const;

  virtual PyObjPtr
  allocateInstance(const PyObjPtr& klass, const PyObjPtr& args);

  virtual PyObjPtr add(const PyObjPtr& lhs, const PyObjPtr& rhs);

  virtual PyObjPtr sub(const PyObjPtr& lhs, const PyObjPtr& rhs);

  virtual PyObjPtr mul(const PyObjPtr& lhs, const PyObjPtr& rhs);

  virtual PyObjPtr div(const PyObjPtr& lhs, const PyObjPtr& rhs);

  virtual PyObjPtr matmul(const PyObjPtr& lhs, const PyObjPtr& rhs);

  virtual PyObjPtr gt(const PyObjPtr& lhs, const PyObjPtr& rhs);

  virtual PyObjPtr lt(const PyObjPtr& lhs, const PyObjPtr& rhs);

  virtual PyObjPtr eq(const PyObjPtr& lhs, const PyObjPtr& rhs);

  virtual PyObjPtr ge(const PyObjPtr& lhs, const PyObjPtr& rhs);

  virtual PyObjPtr le(const PyObjPtr& lhs, const PyObjPtr& rhs);

  virtual PyObjPtr ne(const PyObjPtr& lhs, const PyObjPtr& rhs);

  virtual PyObjPtr repr(const PyObjPtr& self);

  virtual PyObjPtr str(const PyObjPtr& self);

  virtual PyObjPtr _bool_(const PyObjPtr& obj);

  virtual PyObjPtr _serialize_(const PyObjPtr& obj);

  virtual PyObjPtr getitem(const PyObjPtr& obj, const PyObjPtr& key);

  virtual PyObjPtr
  setitem(const PyObjPtr& obj, const PyObjPtr& key, const PyObjPtr& value);

  virtual PyObjPtr delitem(const PyObjPtr& obj, const PyObjPtr& key);

  virtual PyObjPtr contains(const PyObjPtr& obj, const PyObjPtr& key);

  virtual PyObjPtr len(const PyObjPtr& obj);

  virtual PyObjPtr getattr(const PyObjPtr& obj, const PyObjPtr& key);

  virtual PyObjPtr
  setattr(const PyObjPtr& obj, const PyObjPtr& key, const PyObjPtr& value);

  virtual PyObjPtr iter(const PyObjPtr& obj);

  virtual PyObjPtr next(const PyObjPtr& obj);
};

void ThrowUnsupportedOperandError(
  const PyObjPtr& lhs,
  const PyObjPtr& rhs,
  const PyObjPtr& magicMethod
);

class UnsupportedOperandError : public std::runtime_error {
 public:
  explicit UnsupportedOperandError(const std::string& message);
};

enum class KlassComparison {
  GREATER,
  LESS,
  EQUAL,
};

KlassComparison CompareKlasses(const PyObjPtr& lhs, const PyObjPtr& rhs);

KlassPtr CreatePyKlass(
  const PyStrPtr& name,
  const PyDictPtr& attributes,
  const PyListPtr& super
);

}  // namespace torchlight::Object

#endif  // TORCHLIGHT_OBJECT_KLASS_H