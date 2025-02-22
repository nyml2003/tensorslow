#include "Object/Iterator.h"
#include "Object/PyDictionary.h"
#include "Object/PyList.h"
#include "Object/PyObject.h"
#include "Object/PyString.h"
#include "Object/PyType.h"

namespace torchlight::Object {

IterDone::IterDone() : PyObject(IterDoneKlass::Self()) {}

IterDoneKlass::IterDoneKlass() = default;

void IterDoneKlass::Initialize() {
  SetType(CreatePyType(Self()));
  SetName(CreatePyString("IterDone"));
  SetAttributes(CreatePyDict());
  Klass::Initialize();
}

KlassPtr IterDoneKlass::Self() {
  static KlassPtr self = std::make_shared<IterDoneKlass>();
  return self;
}

ListIterator::ListIterator(PyObjPtr list)
  : PyObject(ListIteratorKlass::Self()),
    list(std::dynamic_pointer_cast<PyList>(list)),
    index(0) {}

PyListPtr ListIterator::List() const {
  return list;
}

Index ListIterator::Index() const {
  return index;
}

ListIteratorKlass::ListIteratorKlass() = default;

void ListIteratorKlass::Initialize() {
  SetType(CreatePyType(Self()));
  SetName(CreatePyString("ListIterator"));
  SetAttributes(CreatePyDict());
  Klass::Initialize();
}

KlassPtr ListIteratorKlass::Self() {
  static KlassPtr self = std::make_shared<ListIteratorKlass>();
  return self;
}

PyObjPtr ListIteratorKlass::iter(PyObjPtr obj) {
  return obj;
}

PyObjPtr ListIteratorKlass::next(PyObjPtr obj) {
  auto iterator = std::dynamic_pointer_cast<ListIterator>(obj);
  auto list = iterator->List();
  if (iterator->Index() >= list->Length()) {
    return CreateIterDone();
  }
  auto value = list->GetItem(iterator->Index());
  iterator->Next();
  return value;
}

void ListIterator::Next() {
  index++;
}

PyObjPtr CreateListIterator(const PyObjPtr& list) {
  return std::make_shared<ListIterator>(list);
}

PyObjPtr CreateIterDone() {
  return std::make_shared<IterDone>();
}

}  // namespace torchlight::Object
