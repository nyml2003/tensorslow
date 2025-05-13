#include "Object/Iterator/Iterator.h"
#include "Object/Container/PyList.h"
#include "Object/Number/PyInteger.h"
#include "Object/Object.h"
#include "Object/String/PyString.h"

namespace tensorslow::Object {

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

PyObjPtr ListIteratorKlass::repr(const PyObjPtr& obj) {
  auto iterator = obj->as<ListIterator>();
  return StringConcat(CreatePyList(
    {CreatePyString("<list_iterator object of "), iterator->List()->str(),
     CreatePyString(" index: "),
     CreatePyInteger(iterator->CurrentIndex())->str(), CreatePyString(">")}
  ));
}

PyObjPtr ListReverseIteratorKlass::next(const PyObjPtr& obj) {
  auto iterator = obj->as<ListReverseIterator>();
  auto list = iterator->List();
  if (!~(iterator->CurrentIndex())) {
    return CreateIterDone();
  }
  auto value = list->GetItem(iterator->CurrentIndex());
  iterator->Next();
  return value;
}

PyObjPtr ListReverseIteratorKlass::repr(const PyObjPtr& obj) {
  auto iterator = obj->as<ListReverseIterator>();
  return StringConcat(CreatePyList(
    {CreatePyString("<list_reversed_iterator object of "),
     iterator->List()->str(), CreatePyString(" index: "),
     CreatePyInteger(iterator->CurrentIndex())->str(), CreatePyString(">")}
  ));
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
    {value->GetItem(0)->str(), CreatePyString(": ")->as<PyString>(),
     value->GetItem(1)->str()}
  ));
  return result;
}

}  // namespace tensorslow::Object
