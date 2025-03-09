#ifndef TORCHLIGHT_OBJECT_PYLIST_H
#define TORCHLIGHT_OBJECT_PYLIST_H

#include "Collections/List.h"
#include "Object/PyObject.h"

namespace torchlight::Object {
class ListKlass : public Klass {
 public:
  explicit ListKlass() = default;
  static KlassPtr Self() {
    static KlassPtr instance = std::make_shared<ListKlass>();
    return instance;
  }
  PyObjPtr add(const PyObjPtr& lhs, const PyObjPtr& rhs) override;
  PyObjPtr repr(const PyObjPtr& obj) override;
  PyObjPtr getitem(const PyObjPtr& obj, const PyObjPtr& key) override;
  PyObjPtr setitem(
    const PyObjPtr& obj,
    const PyObjPtr& key,
    const PyObjPtr& value
  ) override;
  PyObjPtr eq(const PyObjPtr& lhs, const PyObjPtr& rhs) override;
  PyObjPtr len(const PyObjPtr& obj) override;
  PyObjPtr contains(const PyObjPtr& obj, const PyObjPtr& key) override;
  PyObjPtr construct(const PyObjPtr& type, const PyObjPtr& args) override;
  PyObjPtr iter(const PyObjPtr& obj) override;
  PyObjPtr _serialize_(const PyObjPtr& obj) override;
  static void Initialize();
};

PyObjPtr CreatePyList(Index capacity);

PyObjPtr CreatePyList(Collections::List<PyObjPtr> list);
class PyList;
using PyListPtr = std::shared_ptr<PyList>;
class PyList : public PyObject {
 private:
  Collections::List<PyObjPtr> value;

 public:
  explicit PyList(Collections::List<PyObjPtr> value)
    : PyObject(ListKlass::Self()), value(std::move(value)) {}

  void Append(PyObjPtr obj) { value.Push(std::move(obj)); }
  PyObjPtr Add(const PyObjPtr& obj) {
    return CreatePyList(value.Add(obj->as<PyList>()->value));
  }
  Index Length() const { return value.Size(); }
  bool Contains(const PyObjPtr& obj) const { return value.Contains(obj); }
  Index IndexOf(const PyObjPtr& obj) const { return value.IndexOf(obj); }
  PyObjPtr GetItem(Index index) const { return value[index]; }
  void SetItem(Index index, const PyObjPtr& obj) { value.Set(index, obj); }
  void SetList(Index start, Index stop, const PyObjPtr& obj) {
    auto list = obj->as<PyList>();
    for (Index i = start; i < stop; ++i) {
      value[i] = list->GetItem(i - start);
    }
  }
  PyObjPtr Prepend(const PyObjPtr& obj) {
    return CreatePyList({obj})->as<PyList>()->Add(shared_from_this());
  }
  void RemoveAt(Index index) { value.RemoveAt(index); }
};

PyObjPtr ListAppend(const PyObjPtr& args);

PyObjPtr ListIndex(const PyObjPtr& args);
}  // namespace torchlight::Object

#endif