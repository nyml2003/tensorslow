#ifndef TENSORSLOW_OBJECT_ITERATOR_H
#define TENSORSLOW_OBJECT_ITERATOR_H

#include "Function/BuiltinFunction.h"
#include "Object/Container/PyDictionary.h"
#include "Object/Container/PyList.h"
#include "Object/Core/CoreHelper.h"
#include "Object/Object.h"
#include "Object/String/PyString.h"
namespace tensorslow::Object {

class IterDoneKlass : public Klass {
 public:
  explicit IterDoneKlass() = default;
  static KlassPtr Self() {
    static KlassPtr instance = std::make_shared<IterDoneKlass>();
    return instance;
  }

  void Initialize() override {
    if (this->isInitialized) {
      return;
    }
    LoadClass(CreatePyString("StopIteration")->as<PyString>(), Self());
    ConfigureBasicAttributes(Self());
    this->isInitialized = true;
  }
};

class IterDone : public PyObject {
 public:
  explicit IterDone() : PyObject(IterDoneKlass::Self()) {}
};

class ListIteratorKlass : public Klass {
 public:
  explicit ListIteratorKlass() = default;
  static KlassPtr Self() {
    static KlassPtr instance = std::make_shared<ListIteratorKlass>();
    return instance;
  }
  PyObjPtr iter(const PyObjPtr& obj) override { return obj; }
  PyObjPtr next(const PyObjPtr& obj) override;
  PyObjPtr str(const PyObjPtr& obj) override { return repr(obj); }
  PyObjPtr repr(const PyObjPtr& obj) override;

  void Initialize() override {
    if (this->isInitialized) {
      return;
    }
    LoadClass(CreatePyString("ListIterator")->as<PyString>(), Self());
    ConfigureBasicAttributes(Self());
    this->isInitialized = true;
  }
};

class ListReverseIteratorKlass : public Klass {
 public:
  explicit ListReverseIteratorKlass() = default;
  static KlassPtr Self() {
    static KlassPtr instance = std::make_shared<ListReverseIteratorKlass>();
    return instance;
  }

  PyObjPtr iter(const PyObjPtr& obj) override { return obj; }
  PyObjPtr next(const PyObjPtr& obj) override;
  PyObjPtr str(const PyObjPtr& obj) override { return repr(obj); }
  PyObjPtr repr(const PyObjPtr& obj) override;

  void Initialize() override {
    if (this->isInitialized) {
      return;
    }
    LoadClass(CreatePyString("ListReverseIterator")->as<PyString>(), Self());
    ConfigureBasicAttributes(Self());
    this->isInitialized = true;
  }
};

inline PyObjPtr CreateIterDone() {
  return std::make_shared<IterDone>();
}

class ListIterator : public PyObject {
 private:
  PyListPtr list;
  Index index{};

 public:
  explicit ListIterator(const PyObjPtr& list)
    : PyObject(ListIteratorKlass::Self()) {
    this->list = list->as<PyList>();
  }
  [[nodiscard]] PyListPtr List() const { return list; }
  [[nodiscard]] Index CurrentIndex() const { return index; }
  void Next() { index++; }
};

inline PyObjPtr CreateListIterator(const PyObjPtr& list) {
  return std::make_shared<ListIterator>(list);
}

class ListReverseIterator : public PyObject {
 private:
  PyListPtr list;
  Index index{};

 public:
  explicit ListReverseIterator(const PyObjPtr& list)
    : PyObject(ListReverseIteratorKlass::Self()) {
    this->list = list->as<PyList>();
    index = this->list->Length() - 1;
  }
  [[nodiscard]] PyListPtr List() const { return list; }
  [[nodiscard]] Index CurrentIndex() const { return index; }
  void Next() { index--; }
};

class StringIteratorKlass : public Klass {
 public:
  explicit StringIteratorKlass() = default;
  static KlassPtr Self() {
    static KlassPtr instance = std::make_shared<StringIteratorKlass>();
    return instance;
  }
  void Initialize() override {
    if (this->isInitialized) {
      return;
    }
    LoadClass(CreatePyString("StringIterator")->as<PyString>(), Self());
    ConfigureBasicAttributes(Self());
    this->isInitialized = true;
  }
  PyObjPtr iter(const PyObjPtr& obj) override { return obj; }
  PyObjPtr next(const PyObjPtr& obj) override;
  PyObjPtr str(const PyObjPtr& obj) override;
};

inline PyObjPtr CreateListReverseIterator(const PyObjPtr& list) {
  return std::make_shared<ListReverseIterator>(list);
}

class StringIterator : public PyObject {
 private:
  PyStrPtr string;
  Index index{};

 public:
  explicit StringIterator(const PyObjPtr& string)
    : PyObject(StringIteratorKlass::Self()) {
    this->string = string->as<PyString>();
  }
  [[nodiscard]] PyStrPtr String() const { return string; }
  [[nodiscard]] Index CurrentIndex() const { return index; }
  void Next() { index++; }
};

inline PyObjPtr CreateStringIterator(const PyObjPtr& string) {
  return std::make_shared<StringIterator>(string);
}

class DictItemIteratorKlass : public Klass {
 public:
  explicit DictItemIteratorKlass() = default;
  static KlassPtr Self() {
    static KlassPtr instance = std::make_shared<DictItemIteratorKlass>();
    return instance;
  }
  void Initialize() override {
    if (this->isInitialized) {
      return;
    }
    LoadClass(CreatePyString("DictItemIterator")->as<PyString>(), Self());
    ConfigureBasicAttributes(Self());
    this->isInitialized = true;
  }
  PyObjPtr iter(const PyObjPtr& obj) override { return obj; }
  PyObjPtr next(const PyObjPtr& obj) override;
  PyObjPtr str(const PyObjPtr& obj) override;
};

class DictItemIterator : public PyObject {
 private:
  PyDictPtr dict;
  Index index{};

 public:
  explicit DictItemIterator(PyDictPtr dict)
    : PyObject(DictItemIteratorKlass::Self()), dict(std::move(dict)) {}
  [[nodiscard]] PyDictPtr Dict() const { return dict; }
  [[nodiscard]] Index CurrentIndex() const { return index; }
  void Next() { index++; }
};

inline PyObjPtr CreateDictItemIterator(const PyDictPtr& dict) {
  return std::make_shared<DictItemIterator>(dict);
}

}  // namespace tensorslow::Object

#endif