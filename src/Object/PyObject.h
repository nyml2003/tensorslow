#ifndef TORCHLIGHT_OBJECT_PYOBJECT_H
#define TORCHLIGHT_OBJECT_PYOBJECT_H

#include "Object/Klass.h"
#include "Object/Object.h"

namespace torchlight::Object {

class PyObject : public std::enable_shared_from_this<PyObject> {
 private:
  KlassPtr klass;

 protected:
 public:
  explicit PyObject(KlassPtr klass);
  void setKlass(KlassPtr klass);

  [[nodiscard]] KlassPtr Klass() const;

  virtual ~PyObject();

  PyObject(const PyObject&) = delete;

  PyObject& operator=(const PyObject&) = delete;

  PyObject(PyObject&&) = delete;

  PyObject& operator=(PyObject&&) = delete;

  PyObjPtr add(const PyObjPtr& other);

  PyObjPtr sub(const PyObjPtr& other);

  PyObjPtr mul(const PyObjPtr& other);

  PyObjPtr div(const PyObjPtr& other);

  PyObjPtr matmul(const PyObjPtr& other);

  PyObjPtr gt(const PyObjPtr& other);

  PyObjPtr lt(const PyObjPtr& other);

  PyObjPtr eq(const PyObjPtr& other);

  PyObjPtr ge(const PyObjPtr& other);

  PyObjPtr le(const PyObjPtr& other);

  PyObjPtr ne(const PyObjPtr& other);

  PyObjPtr repr();

  PyObjPtr str();

  PyObjPtr getitem(const PyObjPtr& key);

  PyObjPtr setitem(const PyObjPtr& key, const PyObjPtr& value);

  PyObjPtr delitem(const PyObjPtr& key);

  PyObjPtr contains(const PyObjPtr& key);

  PyObjPtr len();

  PyObjPtr _bool_();

  PyObjPtr _serialize_();

  PyObjPtr getattr(const PyObjPtr& key);

  PyObjPtr setattr(const PyObjPtr& key, const PyObjPtr& value);

  PyObjPtr iter();

  PyObjPtr next();
};

bool operator==(const PyObjPtr& lhs, const PyObjPtr& rhs);

bool operator!=(const PyObjPtr& lhs, const PyObjPtr& rhs);

void DebugPrint(const PyObjPtr& obj);

PyObjPtr Print(const PyObjPtr& args);

PyObjPtr Len(const PyObjPtr& args);

using PyObjPtr = std::shared_ptr<PyObject>;

class ObjectKlass : public Klass {
 public:
  explicit ObjectKlass();
  static KlassPtr Self();
  void Initialize() override;
};

}  // namespace torchlight::Object

#endif  // TORCHLIGHT_OBJECT_PYOBJECT_H
