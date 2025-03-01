#include "Object/Iterator.h"
#include "Object/Object.h"
#include "Object/PyInteger.h"
#include "Object/PyList.h"
#include "Object/PyString.h"

namespace torchlight::Object {

PyObjPtr ListIteratorKlass::next(const PyObjPtr& obj) {
  auto iterator = obj->as<ListIterator>();
  auto list = iterator->List();
  if (iterator->CurrentIndex() >= list->Length()) {
    return CreateIterDone();
  }
  auto value = list->GetItem(iterator->CurrentIndex());
  iterator->Next();
  return value;
}

PyObjPtr ListIteratorKlass::str(const PyObjPtr& obj) {
  auto iterator = std::dynamic_pointer_cast<ListIterator>(obj);
  return iterator->List()->GetItem(iterator->CurrentIndex())->str();
}

PyObjPtr StringIteratorKlass::next(const PyObjPtr& obj) {
  auto iterator = obj->as<StringIterator>();
  auto string = iterator->String();
  if (iterator->CurrentIndex() >= string->Length()) {
    return CreateIterDone();
  }
  auto value = string->GetItem(iterator->CurrentIndex());
  iterator->Next();
  return value;
}

PyObjPtr StringIteratorKlass::str(const PyObjPtr& obj) {
  auto iterator = obj->as<StringIterator>();
  return iterator->String()->GetItem(iterator->CurrentIndex())->str();
}

PyObjPtr DictItemIteratorKlass::next(const PyObjPtr& obj) {
  auto iterator = obj->as<DictItemIterator>();
  auto dict = iterator->Dict();
  if (iterator->CurrentIndex() >= dict->Size()) {
    return CreateIterDone();
  }
  auto value = dict->GetItem(iterator->CurrentIndex());
  iterator->Next();
  return value;
}

PyObjPtr DictItemIteratorKlass::str(const PyObjPtr& obj) {
  auto iterator = obj->as<DictItemIterator>();
  auto dict = iterator->Dict();
  auto value = dict->GetItem(iterator->CurrentIndex())->as<PyList>();
  auto result = StringConcat(CreatePyList(
    {value->GetItem(0)->str(), CreatePyString(": "), value->GetItem(1)->str()}
  ));
  return result;
}

// StringIterator::StringIterator(const PyObjPtr& string)
//   : PyObject(StringIteratorKlass::Self()),
//     string(std::dynamic_pointer_cast<PyString>(string)),
//     index(0) {}

// PyStrPtr StringIterator::String() const {
//   return string;
// }

// Index StringIterator::Index() const {
//   return index;
// }

// StringIteratorKlass::StringIteratorKlass() = default;

// void StringIteratorKlass::Initialize() {
//   SetType(CreatePyType(Self()));
//   SetName(CreatePyString("StringIterator"));
//   SetAttributes(CreatePyDict());
//   Klass::Initialize();
// }

// KlassPtr StringIteratorKlass::Self() {
//   static KlassPtr self = std::make_shared<StringIteratorKlass>();
//   return self;
// }

// PyObjPtr StringIteratorKlass::iter(const PyObjPtr& obj) {
//   return obj;
// }

// PyObjPtr StringIteratorKlass::next(const

//                                    PyObjPtr& obj) {
//   auto iterator = std::dynamic_pointer_cast<StringIterator>(obj);
//   auto string = iterator->String();
//   if (iterator->Index() >= string->Length()) {
//     return CreateIterDone();
//   }
//   auto value = string->GetItem(iterator->Index());
//   iterator->Next();
//   return value;
// }

}  // namespace torchlight::Object
