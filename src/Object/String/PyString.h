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

  void Initialize() override;

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
  static std::unordered_map<size_t, std::shared_ptr<PyString>> stringPool;
  static std::mutex poolMutex;

 public:
  explicit PyString(const Collections::String& _value)
    : PyObject(StringKlass::Self()), value(_value) {}
  static void IncreaseIndent() { indent++; }
  static void DecreaseIndent() { indent--; }

  Index Length() { return value.GetCodePointCount(); }

  PyStrPtr GetItem(Index index);

  PyStrPtr Join(const PyObjPtr& iterable);

  //  PyListPtr Split(const PyStrPtr& delimiter);

  PyStrPtr Add(const PyStrPtr& other);

  void Print(bool enableIndent = true) const;
  void PrintLine(bool enableIndent = true) const;

  std::string ToCppString() const;

  bool Equal(const PyStrPtr& other);

  PyStrPtr Upper();

  Collections::String Value() const { return value.Copy(); }
  static PyStrPtr Create(const Collections::String& value);
  size_t Hash() { return value.HashValue(); }
};

using PyStrPtr = std::shared_ptr<PyString>;

PyObjPtr StringUpper(const PyObjPtr& args);

PyObjPtr StringJoin(const PyObjPtr& args);

// PyObjPtr StringSplit(const PyObjPtr& args);

PyObjPtr StringConcat(const PyObjPtr& args);

PyStrPtr CreatePyString(const Collections::String& value, bool pooling = true);
PyStrPtr CreatePyString(const char* value);
PyStrPtr CreatePyString(const std::string& value);

}  // namespace torchlight::Object

#endif  // TORCHLIGHT_OBJECT_PYSTRING_H
