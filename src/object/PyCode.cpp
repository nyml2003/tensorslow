#include "Collections/BytesHelper.h"
#include "Collections/IntegerHelper.h"
#include "Collections/StringHelper.h"
#include "Object/ByteCode.h"
#include "Object/Klass.h"
#include "Object/PyBytes.h"
#include "Object/PyCode.h"
#include "Object/PyInteger.h"
#include "Object/PyList.h"
#include "Object/PyObject.h"
#include "Object/PyString.h"

#include <cstring>
#include <memory>
#include <stdexcept>

namespace torchlight::Object {

PyCode::PyCode(
  const PyObjPtr& byteCodes,
  const PyObjPtr& consts,
  const PyObjPtr& names,
  const PyObjPtr& varNames,
  const PyObjPtr& name,
  Index nLocals
)
  : PyObject(CodeKlass::Self()) {
  if (byteCodes->Klass() != BytesKlass::Self()) {
    throw std::runtime_error("byteCodes must be a bytes object");
  }
  byteCode = std::dynamic_pointer_cast<PyBytes>(byteCodes);
  if (consts->Klass() != ListKlass::Self()) {
    throw std::runtime_error("consts must be a list object");
  }
  this->consts = std::dynamic_pointer_cast<PyList>(consts);
  if (names->Klass() != ListKlass::Self()) {
    throw std::runtime_error("names must be a list object");
  }
  this->names = std::dynamic_pointer_cast<PyList>(names);
  if (varNames->Klass() != ListKlass::Self()) {
    throw std::runtime_error("varNames must be a list object");
  }
  this->varNames = std::dynamic_pointer_cast<PyList>(varNames);
  if (name->Klass() != StringKlass::Self()) {
    throw std::runtime_error("filename must be a string object");
  }
  this->name = std::dynamic_pointer_cast<PyString>(name);

  this->nLocals = nLocals;
}

PyListPtr PyCode::Instructions() {
  return instructions;
}

void PyCode::SetInstructions(const PyListPtr& insts) {
  instructions = insts;
}

PyBytesPtr PyCode::ByteCode() const {
  return byteCode;
}

PyListPtr PyCode::Consts() const {
  return consts;
}

PyListPtr PyCode::Names() const {
  return names;
}

PyStrPtr PyCode::Name() const {
  return name;
}

PyListPtr PyCode::VarNames() const {
  return varNames;
}

Index PyCode::NLocals() const {
  return nLocals;
}

CodeKlass::CodeKlass()
  : Object::Klass(Collections::CreateStringWithCString("code")) {}

Object::KlassPtr CodeKlass::Self() {
  static Object::KlassPtr instance = std::make_shared<CodeKlass>();
  return instance;
}

PyObjPtr CodeKlass::repr(PyObjPtr self) {
  if (self->Klass() != Self()) {
    throw std::runtime_error("PyCode::repr(): obj is not a code object");
  }
  auto code = std::dynamic_pointer_cast<PyCode>(self);
  PyObjPtr repr =
    CreatePyString(Collections::CreateStringWithCString("<code>\n"));
  repr =
    repr->add(CreatePyString(Collections::CreateStringWithCString("consts:\n"))
    );
  repr = repr->add(code->Consts()->repr());
  repr = repr->add(CreatePyString(Collections::CreateStringWithCString("\n")));
  repr =
    repr->add(CreatePyString(Collections::CreateStringWithCString("names:\n")));
  repr = repr->add(code->Names()->repr());
  repr = repr->add(CreatePyString(Collections::CreateStringWithCString("\n")));
  repr =
    repr->add(CreatePyString(Collections::CreateStringWithCString("varNames:\n")
    ));
  repr = repr->add(code->VarNames()->repr());
  repr = repr->add(CreatePyString(Collections::CreateStringWithCString("\n")));
  repr =
    repr->add(CreatePyString(Collections::CreateStringWithCString("name:\n")));
  repr = repr->add(code->Name()->repr());
  repr = repr->add(CreatePyString(Collections::CreateStringWithCString("\n")));
  repr =
    repr->add(CreatePyString(Collections::CreateStringWithCString("nLocals: "))
    );
  repr = repr->add(
    CreatePyInteger(Collections::CreateIntegerWithU64(code->NLocals()))->repr()
  );
  repr = repr->add(CreatePyString(Collections::CreateStringWithCString("\n")));
  return repr;
}

PyObjPtr CodeKlass::_serialize_(PyObjPtr self) {
  if (self->Klass() != Self()) {
    throw std::runtime_error("PyCode::_serialize_(): obj is not a code object");
  }
  auto code = std::dynamic_pointer_cast<PyCode>(self);
  PyObjPtr result =
    CreatePyBytes(Collections::Serialize(Literal::CODE))
      ->add(code->Consts()->_serialize_())
      ->add(code->Names()->_serialize_())
      ->add(code->VarNames()->_serialize_())
      ->add(code->Name()->_serialize_())
      ->add(CreatePyBytes(Collections::Serialize(code->NLocals())))
      ->add(code->ByteCode()->_serialize_());
  return result;
}

}  // namespace torchlight::Object