#include "Object/PyString.h"
#include "ByteCode/ByteCode.h"
#include "Collections/BytesHelper.h"
#include "Collections/StringHelper.h"
#include "Function/PyNativeFunction.h"
#include "Object/PyBoolean.h"
#include "Object/PyBytes.h"
#include "Object/PyDictionary.h"
#include "Object/PyInteger.h"
#include "Object/PyList.h"
#include "Object/PyObject.h"
#include "Object/PyType.h"

namespace torchlight::Object {

PyString::PyString(Collections::String value)
  : PyObject(StringKlass::Self()), value(std::move(value)) {}

Collections::String PyString::Value() const {
  return value;
}

StringKlass::StringKlass() = default;

void StringKlass::Initialize() {
  SetType(CreatePyType(Self()));
  SetName(CreatePyString("str"));
  Collections::Map<PyObjPtr, PyObjPtr> methods;
  methods.Put(CreatePyString("upper"), CreatePyNativeFunction(Upper));
  methods.Put(CreatePyString("startswith"), CreatePyNativeFunction(StartsWith));
  SetAttributes(CreatePyDict(methods));
  Klass::Initialize();
}

KlassPtr StringKlass::Self() {
  static KlassPtr instance = std::make_shared<StringKlass>();
  return instance;
}

PyObjPtr CreatePyString(Collections::String value) {
  return std::make_shared<PyString>(value);
}

PyObjPtr CreatePyString(const char* value) {
  return CreatePyString(Collections::CreateStringWithCString(value));
}

PyObjPtr CreatePyString(const std::string& value) {
  return CreatePyString(Collections::CreateStringWithCString(value.c_str()));
}

PyObjPtr StringKlass::add(PyObjPtr lhs, PyObjPtr rhs) {
  if (lhs->Klass() != StringKlass::Self()) {
    throw std::runtime_error("lhs is not a string");
  }
  if (rhs->Klass() != StringKlass::Self()) {
    throw std::runtime_error("rhs is not a string");
  }
  auto left = std::dynamic_pointer_cast<PyString>(lhs);
  auto right = std::dynamic_pointer_cast<PyString>(rhs);
  return CreatePyString(left->Value().Add(right->Value()));
}

PyObjPtr StringKlass::repr(PyObjPtr obj) {
  if (obj->Klass() != StringKlass::Self()) {
    throw std::runtime_error("obj is not a string");
  }
  return CreatePyString(Collections::CreateStringWithCString("\"")
                          .Add(std::dynamic_pointer_cast<PyString>(obj)->Value()
                          )
                          .Add(Collections::CreateStringWithCString("\"")));
}

PyObjPtr StringKlass::str(PyObjPtr obj) {
  if (obj->Klass() != StringKlass::Self()) {
    throw std::runtime_error("obj is not a string");
  }
  return obj;
}

PyObjPtr StringKlass::eq(PyObjPtr lhs, PyObjPtr rhs) {
  if (lhs->Klass() != Self()) {
    throw std::runtime_error("lhs is not a string");
  }
  if (rhs->Klass() != Self()) {
    throw std::runtime_error("rhs is not a string");
  }
  auto left = std::dynamic_pointer_cast<PyString>(lhs);
  auto right = std::dynamic_pointer_cast<PyString>(rhs);
  return CreatePyBoolean(left->Value() == right->Value());
}

PyObjPtr StringKlass::_serialize_(PyObjPtr obj) {
  if (obj->Klass() != Self()) {
    throw std::runtime_error("str does not support serialization");
  }
  auto string = std::dynamic_pointer_cast<PyString>(obj);
  return CreatePyBytes(Collections::Serialize(Literal::STRING)
                         .Add(Collections::Serialize(string->Value())));
}

PyObjPtr Upper(PyObjPtr args) {
  if (args->Klass() != ListKlass::Self()) {
    throw std::runtime_error("Upper() argument must be a list");
  }
  if (args->len() != CreatePyInteger(1)) {
    throw std::runtime_error("Upper() argument must be a list with one element"
    );
  }
  auto value = args->getitem(CreatePyInteger(0));
  if (value->Klass() != StringKlass::Self()) {
    throw std::runtime_error("Upper() argument must be a string");
  }
  auto str = std::dynamic_pointer_cast<PyString>(value);
  return CreatePyString(str->Value().Upper());
}

PyObjPtr StartsWith(PyObjPtr args) {
  if (args->Klass() != ListKlass::Self()) {
    throw std::runtime_error("StartsWith() argument must be a list");
  }
  if (args->len() != CreatePyInteger(2)) {
    throw std::runtime_error(
      "StartsWith() argument must be a list with two elements"
    );
  }
  auto value = args->getitem(CreatePyInteger(0));
  if (value->Klass() != StringKlass::Self()) {
    throw std::runtime_error("StartsWith() argument must be a string");
  }
  auto str = std::dynamic_pointer_cast<PyString>(value);
  auto prefix = args->getitem(CreatePyInteger(1));
  if (prefix->Klass() != StringKlass::Self()) {
    throw std::runtime_error("StartsWith() argument must be a string");
  }
  return CreatePyBoolean(str->Value().StartsWith(
    std::dynamic_pointer_cast<PyString>(prefix)->Value()
  ));
}

}  // namespace torchlight::Object