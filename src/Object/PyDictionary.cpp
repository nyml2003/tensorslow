#include "Object/PyDictionary.h"
#include "Collections/Iterator.h"
#include "Object/PyBoolean.h"
#include "Object/PyInteger.h"
#include "Object/PyList.h"
#include "Object/PyNone.h"
#include "Object/PyObject.h"
#include "Object/PyString.h"
#include "Object/PyType.h"

namespace torchlight::Object {

PyDictionary::PyDictionary(Collections::Map<PyObjPtr, PyObjPtr> dict)
  : PyObject(DictionaryKlass::Self()), dict(std::move(dict)) {}

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

DictionaryKlass::DictionaryKlass() = default;

void DictionaryKlass::Initialize() {
  SetType(CreatePyType(Self()));
  SetName(CreatePyString("dict"));
  SetAttributes(CreatePyDict());
  Klass::Initialize();
}

KlassPtr DictionaryKlass::Self() {
  static KlassPtr self = std::make_shared<DictionaryKlass>();
  return self;
}

PyObjPtr
DictionaryKlass::allocateInstance(const PyObjPtr& klass, const PyObjPtr& args) {
  if (Self()->Type() != klass) {
    throw std::runtime_error(
      "PyDictionary::allocateInstance(): klass is not a dict"
    );
  }
  if (args->len() != CreatePyInteger(0)) {
    throw std::runtime_error(
      "PyDictionary::allocateInstance(): args must be empty"
    );
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

Collections::Map<PyObjPtr, PyObjPtr>& PyDictionary::Value() {
  return dict;
}

PyObjPtr DictionaryKlass::repr(const PyObjPtr& obj) {
  if (obj->Klass() != Self()) {
    throw std::runtime_error("PyDictionary::repr(): obj is not a dict");
  }
  auto dict = std::dynamic_pointer_cast<PyDictionary>(obj);
  auto entriesRaw = dict->Value().Entries();
  auto entriesObj = CreatePyList(entriesRaw.Size());
  for (auto it = Collections::Iterator<
         Collections::MapEntry<PyObjPtr, PyObjPtr>>::Begin(entriesRaw);
       !it.End(); it.Next()) {
    auto key = it.Get().Key()->repr();
    auto value = it.Get().Value()->repr();
    entriesObj->setitem(
      CreatePyInteger(it.GetCurrentIndex()),
      key->add(CreatePyString(": "))->add(value)
    );
  }
  return CreatePyString("{")
    ->add(Join(CreatePyList({entriesObj, CreatePyString(", ")})))
    ->add(CreatePyString("}"));
}

PyObjPtr DictionaryKlass::contains(const PyObjPtr& obj, const PyObjPtr& key) {
  if (obj->Klass() != Self()) {
    throw std::runtime_error("PyDictionary::contains(): obj is not a dict");
  }
  auto dict = std::dynamic_pointer_cast<PyDictionary>(obj);
  return CreatePyBoolean(dict->Contains(key));
}

}  // namespace torchlight::Object