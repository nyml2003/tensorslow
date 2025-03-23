#ifndef TORCHLIGHT_OBJECT_PYSTRING_H
#define TORCHLIGHT_OBJECT_PYSTRING_H

#include "Collections/String/String.h"
#include "Object/Core/PyObject.h"
#include "Object/Object.h"


#include <mutex>
#include <unordered_map>
namespace torchlight::Object {

class StringKlass : public Klass {
 public:
  explicit StringKlass() = default;

  static KlassPtr Self() {
    static KlassPtr instance = std::make_shared<StringKlass>();
    return instance;
  }

  static void Initialize();

  PyObjPtr init(const PyObjPtr& klass, const PyObjPtr& args) override;
  PyObjPtr add(const PyObjPtr& lhs, const PyObjPtr& rhs) override;
  PyObjPtr eq(const PyObjPtr& lhs, const PyObjPtr& rhs) override;
  PyObjPtr len(const PyObjPtr& obj) override;
  PyObjPtr str(const PyObjPtr& obj) override;
  PyObjPtr repr(const PyObjPtr& obj) override;
  PyObjPtr iter(const PyObjPtr& obj) override;
  PyObjPtr hash(const PyObjPtr& obj) override;
  PyObjPtr boolean(const PyObjPtr& obj) override;
  PyObjPtr _serialize_(const PyObjPtr& obj) override;
};

class PyString : public PyObject {
  friend class StringKlass;

 private:
  Collections::String value;
  // 缩进深度
  static Index indent;
  static std::unordered_map<Collections::String, PyObjPtr> stringPool;
  static std::mutex poolMutex;

 public:
  explicit PyString(Collections::String value)
    : PyObject(StringKlass::Self()), value(std::move(value)) {}
  static void IncreaseIndent() { indent++; }
  static void DecreaseIndent() { indent--; }

  Index Length() const { return value.Size(); }

  PyStrPtr GetItem(Index index) const;

  PyStrPtr Join(const PyObjPtr& iterable);

  PyListPtr Split(const PyStrPtr& delimiter);

  PyStrPtr Add(const PyStrPtr& other);

  void Print(bool enableIndent = true) const;
  void PrintLine(bool enableIndent = true) const;

  std::string ToCppString() const;

  bool Equal(const PyStrPtr& other) const;

  PyStrPtr Upper() const;

  Collections::String Value() const { return value; }
  static PyObjPtr Create(const Collections::String& value);
};

using PyStrPtr = std::shared_ptr<PyString>;

PyObjPtr StringUpper(const PyObjPtr& args);

PyObjPtr StringJoin(const PyObjPtr& args);

PyObjPtr StringSplit(const PyObjPtr& args);

PyObjPtr StringConcat(const PyObjPtr& args);

PyObjPtr CreatePyString(const Collections::String& value);
PyObjPtr CreatePyString(const char* value);
PyObjPtr CreatePyString(const std::string& value);

}  // namespace torchlight::Object

#endif  // TORCHLIGHT_OBJECT_PYSTRING_H
