#include "object/PyCode.h"
#include "collections/impl/Bytes.h"
#include "collections/impl/String.h"
#include "object/ByteCode.h"
#include "object/Klass.h"
#include "object/PyBytes.h"
#include "object/PyList.h"
#include "object/PyObject.h"
#include "object/PyString.h"

#include <cstring>
#include <memory>
#include <stdexcept>

namespace torchlight::object {
using collections::CreateStringWithCString;
using collections::ToString;

PyCode::PyCode(
  const PyObjPtr& byteCodes,
  const PyObjPtr& consts,
  const PyObjPtr& names,
  const PyObjPtr& varNames,
  const PyObjPtr& name,
  collections::Index nLocals
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

collections::Index PyCode::NLocals() const {
  return nLocals;
}

CodeKlass::CodeKlass() : object::Klass(CreateStringWithCString("code")) {}

object::KlassPtr CodeKlass::Self() {
  static object::KlassPtr instance = std::make_shared<CodeKlass>();
  return instance;
}

PyObjPtr CodeKlass::repr(PyObjPtr self) {
  if (self->Klass() != Self()) {
    return nullptr;
  }
  auto code = std::dynamic_pointer_cast<PyCode>(self);
  PyObjPtr s = std::make_shared<PyString>(
    CreateStringWithCString("<code object ")
      .Concat(code->Name()->Value())
      .Concat(CreateStringWithCString(" at "))
      .Concat(ToString(reinterpret_cast<uint64_t>(self.get())))
      .Concat(CreateStringWithCString(">"))
  );
  return s;
}

PyObjPtr CodeKlass::_serialize_(PyObjPtr self) {
  if (self->Klass() != Self()) {
    return nullptr;
  }
  auto code = std::dynamic_pointer_cast<PyCode>(self);
  PyObjPtr result =
    std::make_shared<PyBytes>(Serialize(Literal::CODE))
      ->add(code->Consts()->_serialize_())
      ->add(code->Names()->_serialize_())
      ->add(code->VarNames()->_serialize_())
      ->add(code->Name()->_serialize_())
      ->add(std::make_shared<PyBytes>(collections::Serialize(code->NLocals())))
      ->add(code->ByteCode()->_serialize_());
  return result;
}

}  // namespace torchlight::object