#include "Object/Container/PyDictionary.h"
#include "Function/ObjectHelper.h"
#include "Object/Container/PyList.h"
#include "Object/Core/PyBoolean.h"
#include "Object/Core/PyNone.h"
#include "Object/Core/PyObject.h"
#include "Object/Core/PyType.h"
#include "Object/Iterator/Iterator.h"
#include "Object/Iterator/IteratorHelper.h"
#include "Object/Number/PyInteger.h"
#include "Object/String/PyString.h"


namespace torchlight::Object {

PyObjPtr CreatePyDict() {
  return std::make_shared<PyDictionary>();
}

void PyDictionary::Put(const PyObjPtr& key, const PyObjPtr& value) {
  dict.insert_or_assign(key, value);
}

PyObjPtr PyDictionary::Get(const PyObjPtr& key) {
  return dict[key];
}

void PyDictionary::Remove(const PyObjPtr& key) {
  dict.erase(key);
}

bool PyDictionary::Contains(const PyObjPtr& key) {
  return dict.find(key) != dict.end();
}

PyObjPtr PyDictionary::GetItem(Index index) const {
  auto dictIterator = dict.begin();
  std::advance(dictIterator, index);
  auto entry = *dictIterator;
  return CreatePyList({entry.first, entry.second});
}

Index PyDictionary::Size() const {
  return dict.size();
}

void DictionaryKlass::Initialize() {
  LoadClass(CreatePyString("dict")->as<PyString>(), Self());
  ConfigureBasicAttributes(Self());
}

PyObjPtr DictionaryKlass::init(const PyObjPtr& klass, const PyObjPtr& args) {
  if (klass->as<PyType>()->Owner() != Self()) {
    throw std::runtime_error("PyDictionary::init(): klass is not a dict");
  }
  auto argList = args->as<PyList>();
  if (argList->Length() != 0) {
    throw std::runtime_error("PyDictionary::init(): args must be empty");
  }
  return CreatePyDict();
}

PyObjPtr DictionaryKlass::setitem(
  const PyObjPtr& obj,
  const PyObjPtr& key,
  const PyObjPtr& value
) {
  if (!obj->is<PyDictionary>()) {
    throw std::runtime_error("PyDictionary::setitem(): obj is not a dict");
  }
  auto dict = obj->as<PyDictionary>();
  dict->Put(key, value);
  return CreatePyNone();
}

PyObjPtr DictionaryKlass::getitem(const PyObjPtr& obj, const PyObjPtr& key) {
  if (!obj->is<PyDictionary>()) {
    throw std::runtime_error("PyDictionary::getitem(): obj is not a dict");
  }
  auto dict = obj->as<PyDictionary>();
  return dict->Get(key);
}

PyObjPtr DictionaryKlass::delitem(const PyObjPtr& obj, const PyObjPtr& key) {
  if (!obj->is<PyDictionary>()) {
    throw std::runtime_error("PyDictionary::delitem(): obj is not a dict");
  }
  auto dict = obj->as<PyDictionary>();
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
  auto dictItemReprList = Map(obj, [](const PyObjPtr& item) {
    auto key = item->as<PyList>()->GetItem(0);
    auto value = item->as<PyList>()->GetItem(1);
    return StringConcat(CreatePyList(
      {CreatePyString("(")->as<PyString>(), key->repr(),
       CreatePyString(": ")->as<PyString>(), value->repr(),
       CreatePyString(")")->as<PyString>()}
    ));
  });
  auto repr = CreatePyString(", ")->as<PyString>()->Join(dictItemReprList);
  return StringConcat(CreatePyList(
    {CreatePyString("{")->as<PyString>(), repr,
     CreatePyString("}")->as<PyString>()}
  ));
}

PyObjPtr DictionaryKlass::str(const PyObjPtr& obj) {
  if (!obj->is<PyDictionary>()) {
    throw std::runtime_error("PyDictionary::str(): obj is not a dict");
  }
  auto dictItemStrList = Map(obj, [](const PyObjPtr& item) {
    auto key = item->as<PyList>()->GetItem(0);
    auto value = item->as<PyList>()->GetItem(1);
    return StringConcat(CreatePyList(
      {CreatePyString("(")->as<PyString>(), key->str(),
       CreatePyString(": ")->as<PyString>(), value->str(),
       CreatePyString(")")->as<PyString>()}
    ));
  });
  auto repr = CreatePyString(", ")->as<PyString>()->Join(dictItemStrList);
  return StringConcat(CreatePyList(
    {CreatePyString("{")->as<PyString>(), repr,
     CreatePyString("}")->as<PyString>()}
  ));
}

PyObjPtr DictionaryKlass::contains(const PyObjPtr& obj, const PyObjPtr& key) {
  if (!obj->is<PyDictionary>()) {
    throw std::runtime_error("PyDictionary::contains(): obj is not a dict");
  }
  auto dict = obj->as<PyDictionary>();
  return CreatePyBoolean(dict->Contains(key));
}

bool KeyCompare(const PyObjPtr& lhs, const PyObjPtr& rhs) {
  auto leftHash = lhs->hash()->as<PyInteger>();
  auto rightHash = rhs->hash()->as<PyInteger>();
  return leftHash->LessThan(rightHash);
}

}  // namespace torchlight::Object