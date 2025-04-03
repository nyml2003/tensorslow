#ifndef TORCHLIGHT_OBJECT_PYLIST_H
#define TORCHLIGHT_OBJECT_PYLIST_H

#include "Collections/List.h"
#include "Object/Core/PyObject.h"
#include "Object/Object.h"
#include "Object/PySlice.h"

namespace torchlight::Object {
class ListKlass : public Klass {
 public:
  explicit ListKlass() = default;
  static KlassPtr Self() {
    static KlassPtr instance = std::make_shared<ListKlass>();
    return instance;
  }
  PyObjPtr add(const PyObjPtr& lhs, const PyObjPtr& rhs) override;
  PyObjPtr mul(const PyObjPtr& lhs, const PyObjPtr& rhs) override;
  PyObjPtr str(const PyObjPtr& obj) override;
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
  PyObjPtr init(const PyObjPtr& type, const PyObjPtr& args) override;
  PyObjPtr iter(const PyObjPtr& obj) override;
  PyObjPtr boolean(const PyObjPtr& obj) override;
  PyObjPtr reversed(const PyObjPtr& obj) override;
  PyObjPtr _serialize_(const PyObjPtr& obj) override;
  void Initialize() override;
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

  void Shuffle() { value.Shuffle(); }
  void Append(PyObjPtr obj) { value.Push(std::move(obj)); }
  PyObjPtr Add(const PyObjPtr& obj) {
    return CreatePyList(value.Add(obj->as<PyList>()->value));
  }
  Index Length() const { return value.Size(); }
  bool Contains(const PyObjPtr& obj) const { return value.Contains(obj); }
  Index IndexOf(const PyObjPtr& obj) const { return value.IndexOf(obj); }
  PyObjPtr GetItem(Index index) const { return value[index]; }
  PyObjPtr GetSlice(const PySlicePtr& slice) const;
  void SetItem(Index index, const PyObjPtr& obj) { value.Set(index, obj); }
  PyObjPtr Prepend(const PyObjPtr& obj) {
    return CreatePyList({obj})->as<PyList>()->Add(shared_from_this());
  }
  void RemoveAt(Index index) { value.RemoveAt(index); }
  void InsertAndReplace(Index start, Index end, const PyListPtr& list) {
    value.InsertAndReplace(start, end, list->value);
  }
  void Pop(Index index) { value.RemoveAt(index); }
  void Clear() { value.Clear(); }
  void Reverse() { value.Reverse(); }
  PyListPtr Copy() { return CreatePyList(value.Copy())->as<PyList>(); }
  void Insert(Index index, const PyObjPtr& obj) { value.Insert(index, obj); };
};

PyObjPtr ListIndex(const PyObjPtr& args);

PyObjPtr ListAppend(const PyObjPtr& args);

PyObjPtr ListExtend(const PyObjPtr& args);

PyObjPtr ListCount(const PyObjPtr& args);

PyObjPtr ListPop(const PyObjPtr& args);

PyObjPtr ListInsert(const PyObjPtr& args);

PyObjPtr ListRemove(const PyObjPtr& args);

PyObjPtr ListReverse(const PyObjPtr& args);

PyObjPtr ListClear(const PyObjPtr& args);

PyObjPtr ListCopy(const PyObjPtr& args);

PyListPtr CreatePyListFromIterable(const PyObjPtr& iterator);
}  // namespace torchlight::Object

#endif