#ifndef TORCHLIGHT_OBJECT_KLASS_H
#define TORCHLIGHT_OBJECT_KLASS_H
#include "Object/Object.h"

namespace torchlight::Object {
class Klass {
 private:
  PyStrPtr name;
  PyDictPtr attributes;
  PyTypePtr type;
  PyListPtr super;
  PyListPtr mro;
  bool isNative{};

 public:
  explicit Klass()
    : name(nullptr),
      attributes(nullptr),
      type(nullptr),
      super(nullptr),
      mro(nullptr) {}
  void SetName(const PyObjPtr& name);
  void SetAttributes(const PyObjPtr& attributes);
  void SetType(const PyObjPtr& type);
  void SetNative() { this->isNative = true; }
  void SetSuper(const PyObjPtr& super);
  [[nodiscard]] bool IsNative() const { return isNative; }
  void AddAttribute(const PyStrPtr& key, const PyObjPtr& value);
  Klass(const Klass& other) = delete;
  Klass& operator=(const Klass& other) = delete;
  Klass(Klass&& other) noexcept = delete;
  Klass& operator=(Klass&& other) noexcept = delete;
  virtual ~Klass() = default;
  [[nodiscard]] PyStrPtr Name() const { return name; }
  [[nodiscard]] PyTypePtr Type() const { return type; }
  [[nodiscard]] PyDictPtr Attributes() const { return attributes; }
  [[nodiscard]] PyListPtr Super() const { return super; }
  [[nodiscard]] PyListPtr Mro() const { return mro; }
  virtual PyObjPtr construct(const PyObjPtr& type, const PyObjPtr& args);
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
  virtual PyObjPtr boolean(const PyObjPtr& obj);
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
  virtual PyObjPtr _serialize_(const PyObjPtr& obj);
};

KlassPtr CreatePyKlass(
  const PyStrPtr& name,
  const PyDictPtr& attributes,
  const PyListPtr& super
);

void LoadClass(const PyStrPtr& name, const KlassPtr& klass);
void ConfigureBasicAttributes(const KlassPtr& klass);
PyObjPtr KlassRepr(const PyObjPtr& args);

}  // namespace torchlight::Object

#endif  // TORCHLIGHT_OBJECT_KLASS_H