#ifndef TORCHLIGHT_OBJECT_KLASS_H
#define TORCHLIGHT_OBJECT_KLASS_H
#include "Object/Object.h"

namespace torchlight::Object {
class Klass : public std::enable_shared_from_this<Klass> {
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
  void SetType(const PyTypePtr& type);
  void SetNative() { this->isNative = true; }
  void SetSuper(const PyObjPtr& super);
  void SetMro(const PyObjPtr& mro);
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
  virtual PyObjPtr init(const PyObjPtr& type, const PyObjPtr& args);
  virtual PyObjPtr add(const PyObjPtr& lhs, const PyObjPtr& rhs);
  virtual PyObjPtr sub(const PyObjPtr& lhs, const PyObjPtr& rhs);
  virtual PyObjPtr mul(const PyObjPtr& lhs, const PyObjPtr& rhs);
  virtual PyObjPtr floordiv(const PyObjPtr& lhs, const PyObjPtr& rhs);
  virtual PyObjPtr truediv(const PyObjPtr& lhs, const PyObjPtr& rhs);
  virtual PyObjPtr matmul(const PyObjPtr& lhs, const PyObjPtr& rhs);
  virtual PyObjPtr pos(const PyObjPtr& obj);
  virtual PyObjPtr neg(const PyObjPtr& obj);
  virtual PyObjPtr invert(const PyObjPtr& obj);
  virtual PyObjPtr _and_(const PyObjPtr& lhs, const PyObjPtr& rhs);
  virtual PyObjPtr _or_(const PyObjPtr& lhs, const PyObjPtr& rhs);
  virtual PyObjPtr _xor_(const PyObjPtr& lhs, const PyObjPtr& rhs);
  virtual PyObjPtr hash(const PyObjPtr& obj);
  virtual PyObjPtr gt(const PyObjPtr& lhs, const PyObjPtr& rhs);
  virtual PyObjPtr lt(const PyObjPtr& lhs, const PyObjPtr& rhs);
  virtual PyObjPtr eq(const PyObjPtr& lhs, const PyObjPtr& rhs);
  virtual PyObjPtr ge(const PyObjPtr& lhs, const PyObjPtr& rhs);
  virtual PyObjPtr le(const PyObjPtr& lhs, const PyObjPtr& rhs);
  virtual PyObjPtr ne(const PyObjPtr& lhs, const PyObjPtr& rhs);
  virtual PyObjPtr lshift(const PyObjPtr& lhs, const PyObjPtr& rhs);
  virtual PyObjPtr rshift(const PyObjPtr& lhs, const PyObjPtr& rhs);
  virtual PyObjPtr mod(const PyObjPtr& lhs, const PyObjPtr& rhs);
  virtual PyObjPtr divmod(const PyObjPtr& lhs, const PyObjPtr& rhs);
  virtual PyObjPtr pow(const PyObjPtr& lhs, const PyObjPtr& rhs);
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
  virtual PyObjPtr reversed(const PyObjPtr& obj);
  virtual PyObjPtr _serialize_(const PyObjPtr& obj);
};
}  // namespace torchlight::Object

#endif  // TORCHLIGHT_OBJECT_KLASS_H