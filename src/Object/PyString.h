#ifndef TORCHLIGHT_OBJECT_PYSTRING_H
#define TORCHLIGHT_OBJECT_PYSTRING_H

#include "Collections/String.h"
#include "Collections/StringHelper.h"
#include "Object/PyObject.h"

namespace torchlight::Object {

class StringKlass : public Klass {
 public:
  explicit StringKlass() = default;

  static KlassPtr Self() {
    static KlassPtr instance = std::make_shared<StringKlass>();
    return instance;
  }

  static void Initialize();

  PyObjPtr construct(const PyObjPtr& klass, const PyObjPtr& args) override;
  PyObjPtr add(const PyObjPtr& lhs, const PyObjPtr& rhs) override;
  PyObjPtr eq(const PyObjPtr& lhs, const PyObjPtr& rhs) override;
  PyObjPtr len(const PyObjPtr& obj) override;
  PyObjPtr str(const PyObjPtr& obj) override;
  PyObjPtr repr(const PyObjPtr& obj) override;
  PyObjPtr iter(const PyObjPtr& obj) override;

  PyObjPtr _serialize_(const PyObjPtr& obj) override;
};

class PyString : public PyObject {
  friend class StringKlass;

 private:
  Collections::String value;

 public:
  explicit PyString(Collections::String value)
    : PyObject(StringKlass::Self()), value(std::move(value)) {}

  Index Length() const { return value.Size(); }

  PyStrPtr GetItem(Index index) const;

  PyStrPtr Join(const PyObjPtr& iterable);

  PyListPtr Split(const PyStrPtr& delimiter);

  PyStrPtr Add(const PyStrPtr& other);

  void Print() const;

  void PrintLine() const;

  std::string ToCppString() const;

  bool Equal(const PyStrPtr& other) const;

  PyStrPtr Upper() const;

  Collections::String Value() const { return value; }
};
using PyStrPtr = std::shared_ptr<PyString>;

inline PyObjPtr CreatePyString(const Collections::String& value) {
  return std::make_shared<PyString>(value);
}
inline PyObjPtr CreatePyString(const char* value) {
  return CreatePyString(Collections::CreateStringWithCString(value));
}
inline PyObjPtr CreatePyString(const std::string& value) {
  return CreatePyString(Collections::CreateStringWithCString(value.c_str()));
}

PyObjPtr StringUpper(const PyObjPtr& args);

PyObjPtr StringJoin(const PyObjPtr& args);

PyObjPtr StringSplit(const PyObjPtr& args);

PyObjPtr StringConcat(const PyObjPtr& args);

}  // namespace torchlight::Object

#endif  // TORCHLIGHT_OBJECT_PYSTRING_H
