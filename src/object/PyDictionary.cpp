
#include "Collections/Iterator.h"
#include "Collections/StringHelper.h"
#include "Object/PyDictionary.h"
#include "Object/PyList.h"
#include "Object/PyNone.h"
#include "Object/PyObject.h"
#include "Object/PyString.h"

namespace torchlight::Object {

PyDictionary::PyDictionary(Collections::Map<PyObjPtr, PyObjPtr> dict)
  : PyObject(DictionaryKlass::Self()), dict(std::move(dict)) {}

PyDictPtr CreatePyDict() {
  return std::make_shared<PyDictionary>(Collections::Map<PyObjPtr, PyObjPtr>());
}

DictionaryKlass::DictionaryKlass()
  : Klass(Collections::CreateStringWithCString("dict")) {}

KlassPtr DictionaryKlass::Self() {
  static KlassPtr self = std::make_shared<DictionaryKlass>();
  return self;
}

PyObjPtr DictionaryKlass::setitem(PyObjPtr obj, PyObjPtr key, PyObjPtr value) {
  if (obj->Klass() != Self()) {
    throw std::runtime_error("PyDictionary::setitem(): obj is not a dict");
  }
  auto dict = std::dynamic_pointer_cast<PyDictionary>(obj);
  dict->Value().Put(std::move(key), std::move(value));
  obj = dict;
  return CreatePyNone();
}

PyObjPtr DictionaryKlass::getitem(PyObjPtr obj, PyObjPtr key) {
  if (obj->Klass() != Self()) {
    throw std::runtime_error("PyDictionary::getitem(): obj is not a dict");
  }
  auto dict = std::dynamic_pointer_cast<PyDictionary>(obj);
  return dict->Value().Get(key);
}

PyObjPtr DictionaryKlass::delitem(PyObjPtr obj, PyObjPtr key) {
  if (obj->Klass() != Self()) {
    throw std::runtime_error("PyDictionary::delitem(): obj is not a dict");
  }
  auto dict = std::dynamic_pointer_cast<PyDictionary>(obj);
  dict->Value().Remove(key);
  return obj;
}

Collections::Map<PyObjPtr, PyObjPtr>& PyDictionary::Value() {
  return dict;
}

PyObjPtr DictionaryKlass::repr(PyObjPtr obj) {
  if (obj->Klass() != Self()) {
    throw std::runtime_error("PyDictionary::repr(): obj is not a dict");
  }
  auto dict = std::dynamic_pointer_cast<PyDictionary>(obj);
  PyObjPtr result = CreatePyString(Collections::CreateStringWithCString("{"));
  PyListPtr entrites = CreatePyList(0);
  for (auto it =
         Collections::Iterator<Collections::MapEntry<PyObjPtr, PyObjPtr>>::
           Begin(dict->Value().Entries());
       !it.End(); it.Next()) {
    auto key = it.Get().Key()->repr();
    auto value = it.Get().Value()->repr();
    entrites->Append(
      CreatePyString(Collections::CreateStringWithCString("  "))
        ->add(key)
        ->add(CreatePyString(Collections::CreateStringWithCString(": ")))
        ->add(value)
    );
  }
  result = result->add(
    entrites->Join(CreatePyString(Collections::CreateStringWithCString("\n")))
  );
  result =
    result->add(CreatePyString(Collections::CreateStringWithCString("}")));
  return result;
}
}  // namespace torchlight::Object