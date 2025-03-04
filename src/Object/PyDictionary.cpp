#include "Object/PyDictionary.h"
#include "Object/Iterator.h"
#include "Object/PyBoolean.h"
#include "Object/PyList.h"
#include "Object/PyNone.h"
#include "Object/PyObject.h"
#include "Object/PyString.h"
#include "Object/PyType.h"
namespace torchlight::Object {

PyObjPtr CreatePyDict() {
  return std::make_shared<PyDictionary>(Collections::Map<PyObjPtr, PyObjPtr>());
}

PyObjPtr CreatePyDict(Collections::Map<PyObjPtr, PyObjPtr> dict) {
  return std::make_shared<PyDictionary>(std::move(dict));
}

void PyDictionary::Put(const PyObjPtr& key, const PyObjPtr& value) {
  dict.Put(key, value);
}

PyObjPtr PyDictionary::Get(const PyObjPtr& key) {
  return dict.Get(key);
}

void PyDictionary::Remove(const PyObjPtr& key) {
  dict.Remove(key);
}

bool PyDictionary::Contains(const PyObjPtr& key) {
  return dict.Contains(key);
}

PyObjPtr PyDictionary::GetItem(Index index) const {
  auto entry = dict.Entries().Get(index);
  return CreatePyList({entry.Key(), entry.Value()});
}

Index PyDictionary::Size() const{
  return dict.Size();
}

void DictionaryKlass::Initialize() {
  LoadClass(CreatePyString("dict")->as<PyString>(), Self());
  ConfigureBasicAttributes(Self());
}

PyObjPtr
DictionaryKlass::construct(const PyObjPtr& klass, const PyObjPtr& args) {
  if (klass->as<PyType>()->Owner() != Self()) {
    throw std::runtime_error("PyDictionary::construct(): klass is not a dict");
  }
  auto argList = args->as<PyList>();
  if (argList->Length() != 0) {
    throw std::runtime_error("PyDictionary::construct(): args must be empty");
  }
  return CreatePyDict();
}

PyObjPtr DictionaryKlass::setitem(
  const PyObjPtr& obj,
  const PyObjPtr& key,
  const PyObjPtr& value
) {
  if (obj->Klass() != Self()) {
    throw std::runtime_error("PyDictionary::setitem(): obj is not a dict");
  }
  auto dict = std::dynamic_pointer_cast<PyDictionary>(obj);
  dict->Put(key, value);
  return CreatePyNone();
}

PyObjPtr DictionaryKlass::getitem(const PyObjPtr& obj, const PyObjPtr& key) {
  if (obj->Klass() != Self()) {
    throw std::runtime_error("PyDictionary::getitem(): obj is not a dict");
  }
  auto dict = std::dynamic_pointer_cast<PyDictionary>(obj);
  return dict->Get(key);
}

PyObjPtr DictionaryKlass::delitem(const PyObjPtr& obj, const PyObjPtr& key) {
  if (obj->Klass() != Self()) {
    throw std::runtime_error("PyDictionary::delitem(): obj is not a dict");
  }
  auto dict = std::dynamic_pointer_cast<PyDictionary>(obj);
  dict->Remove(key);
  return obj;
}

PyObjPtr DictionaryKlass::iter(const PyObjPtr& obj) {
  if (!obj->is<PyDictionary>()) {
    throw std::runtime_error("PyDictionary::iter(): obj is not a dict");
  }
  return CreateDictItemIterator(obj);
}

PyObjPtr DictionaryKlass::repr(const PyObjPtr& obj) {
  if (!obj->is<PyDictionary>()) {
    throw std::runtime_error("PyDictionary::repr(): obj is not a dict");
  }
  auto repr = CreatePyString(", ")->as<PyString>()->Join(obj);
  return StringConcat(CreatePyList(
    {CreatePyString("{")->as<PyString>(), repr,
     CreatePyString("}")->as<PyString>()}
  ));
}

PyObjPtr DictionaryKlass::contains(const PyObjPtr& obj, const PyObjPtr& key) {
  if (obj->Klass() != Self()) {
    throw std::runtime_error("PyDictionary::contains(): obj is not a dict");
  }
  auto dict = std::dynamic_pointer_cast<PyDictionary>(obj);
  return CreatePyBoolean(dict->Contains(key));
}

}  // namespace torchlight::Object