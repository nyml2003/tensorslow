#ifndef TORCHLIGHT_OBJECT_KLASS_H
#define TORCHLIGHT_OBJECT_KLASS_H

#include "Object/Common.h"

#include <stdexcept>

namespace torchlight::Object {
class Klass {
 private:
  PyStrPtr name;
  PyDictPtr attributes;
  PyTypePtr type;

 protected:
  void SetName(PyObjPtr name);
  void SetAttributes(PyObjPtr attributes);
  void SetType(PyObjPtr type);

 public:
  explicit Klass();

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

  virtual PyObjPtr add(PyObjPtr lhs, PyObjPtr rhs);

  virtual PyObjPtr sub(PyObjPtr lhs, PyObjPtr rhs);

  virtual PyObjPtr mul(PyObjPtr lhs, PyObjPtr rhs);

  virtual PyObjPtr div(PyObjPtr lhs, PyObjPtr rhs);

  virtual PyObjPtr matmul(PyObjPtr lhs, PyObjPtr rhs);

  virtual PyObjPtr gt(PyObjPtr lhs, PyObjPtr rhs);

  virtual PyObjPtr lt(PyObjPtr lhs, PyObjPtr rhs);

  virtual PyObjPtr eq(PyObjPtr lhs, PyObjPtr rhs);

  virtual PyObjPtr ge(PyObjPtr lhs, PyObjPtr rhs);

  virtual PyObjPtr le(PyObjPtr lhs, PyObjPtr rhs);

  virtual PyObjPtr ne(PyObjPtr lhs, PyObjPtr rhs);

  virtual PyObjPtr repr(PyObjPtr obj);

  virtual PyObjPtr str(PyObjPtr obj);

  virtual PyObjPtr _bool_(PyObjPtr obj);

  virtual PyObjPtr _serialize_(PyObjPtr obj);

  virtual PyObjPtr getitem(PyObjPtr obj, PyObjPtr key);

  virtual PyObjPtr setitem(PyObjPtr obj, PyObjPtr key, PyObjPtr value);

  virtual PyObjPtr delitem(PyObjPtr obj, PyObjPtr key);

  virtual PyObjPtr contains(PyObjPtr obj, PyObjPtr key);

  virtual PyObjPtr len(PyObjPtr obj);

  virtual PyObjPtr getattr(PyObjPtr obj, PyObjPtr key);

  virtual PyObjPtr setattr(PyObjPtr obj, PyObjPtr key, PyObjPtr value);
};

void ThrowUnsupportedOperandError(
  PyObjPtr lhs,
  PyObjPtr rhs,
  PyObjPtr magicMethod
);

class UnsupportedOperandError : public std::runtime_error {
 public:
  explicit UnsupportedOperandError(const std::string& message);
};

}  // namespace torchlight::Object

#endif  // TORCHLIGHT_OBJECT_KLASS_H