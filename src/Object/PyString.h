#ifndef TORCHLIGHT_OBJECT_PYSTRING_H
#define TORCHLIGHT_OBJECT_PYSTRING_H

#include "Collections/String.h"
#include "Object/Klass.h"
#include "Object/PyObject.h"

namespace torchlight::Object {

class PyString : public PyObject {
 private:
  Collections::String value;

 public:
  explicit PyString(Collections::String value);

  [[nodiscard]] Collections::String Value() const;
};

class StringKlass : public Klass {
 public:
  explicit StringKlass();

  void Initialize() override;

  static KlassPtr Self();

  PyObjPtr allocateInstance(PyObjPtr klass, PyObjPtr args) override;

  PyObjPtr add(PyObjPtr lhs, PyObjPtr rhs) override;

  PyObjPtr repr(PyObjPtr obj) override;

  PyObjPtr str(PyObjPtr obj) override;

  PyObjPtr eq(PyObjPtr lhs, PyObjPtr rhs) override;

  PyObjPtr _serialize_(PyObjPtr obj) override;
};
PyObjPtr CreatePyString(Collections::String value);
PyObjPtr CreatePyString(const char* value);
PyObjPtr CreatePyString(const std::string& value);

using PyStrPtr = std::shared_ptr<PyString>;

PyObjPtr Upper(PyObjPtr args);

PyObjPtr StartsWith(PyObjPtr args);

}  // namespace torchlight::Object

#endif  // TORCHLIGHT_OBJECT_PYSTRING_H
