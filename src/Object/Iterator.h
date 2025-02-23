#ifndef TORCHLIGHT_OBJECT_ITERATOR_H
#define TORCHLIGHT_OBJECT_ITERATOR_H
#include "Common.h"
#include "Object/Klass.h"
#include "Object/PyObject.h"

namespace torchlight::Object {

class IterDone : public PyObject {
 private:
 public:
  explicit IterDone();
};

class IterDoneKlass : public Klass {
 public:
  explicit IterDoneKlass();
  static KlassPtr Self();
  void Initialize() override;
};

class ListIterator : public PyObject {
 private:
  PyListPtr list;
  Index index;

 public:
  explicit ListIterator(const PyObjPtr& list);
  [[nodiscard]] PyListPtr List() const;
  [[nodiscard]] Index Index() const;
  void Next();
};

class ListIteratorKlass : public Klass {
 public:
  explicit ListIteratorKlass();
  static KlassPtr Self();
  void Initialize() override;
  PyObjPtr iter(const PyObjPtr& obj) override;
  PyObjPtr next(const PyObjPtr& obj) override;
  PyObjPtr str(const PyObjPtr& obj) override;
};

PyObjPtr CreateListIterator(const PyObjPtr& list);
PyObjPtr CreateIterDone();

}  // namespace torchlight::Object

#endif