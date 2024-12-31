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

namespace torchlight::object {
using collections::ToString;

PyCode::PyCode(
  const PyObjPtr& byteCodes,
  const PyObjPtr& consts,
  const PyObjPtr& names,
  const PyObjPtr& varNames,
  const PyObjPtr& filename
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
  if (filename->Klass() != StringKlass::Self()) {
    throw std::runtime_error("filename must be a string object");
  }
  this->filename = std::dynamic_pointer_cast<PyString>(filename);
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

PyStrPtr PyCode::Filename() const {
  return filename;
}

PyListPtr PyCode::VarNames() const {
  return varNames;
}

CodeKlass::CodeKlass()
  : object::Klass(collections::CreateStringWithCString("code")) {}

object::KlassPtr CodeKlass::Self() {
  static object::KlassPtr instance = std::make_shared<CodeKlass>();
  return instance;
}

PyObjPtr CodeKlass::repr(PyObjPtr self) {
  if (self->Klass() != Self()) {
    return nullptr;
  }
  auto code = std::dynamic_pointer_cast<PyCode>(self);
  String result = collections::CreateStringWithCString("<code object ");
  result.InplaceConcat(code->Filename()->Value());
  result.InplaceConcat(collections::CreateStringWithCString(" at "));
  result.InplaceConcat(String(ToString(reinterpret_cast<uint64_t>(self.get())))
  );
  result.InplaceConcat(collections::CreateStringWithCString(">"));
  PyObjPtr s = std::make_shared<PyString>(result);
  s = s->add(std::make_shared<PyString>(
    collections::CreateStringWithCString("\nConsts:\n")
  ));
  s = s->add(code->Consts()->repr());
  s = s->add(std::make_shared<PyString>(
    collections::CreateStringWithCString("\nNames:\n")
  ));
  s = s->add(code->Names()->repr());
  s = s->add(std::make_shared<PyString>(
    collections::CreateStringWithCString("\nVarNames:\n")
  ));
  s = s->add(code->VarNames()->repr());
  return s;
}

PyObjPtr CodeKlass::_serialize_(PyObjPtr self) {
  if (self->Klass() != Self()) {
    return nullptr;
  }
  auto code = std::dynamic_pointer_cast<PyCode>(self);
  PyObjPtr result =
    std::make_shared<PyBytes>(collections::CreateBytesWithCString(""));
  result = result->add(code->Filename()->_serialize_());
  result = result->add(code->Consts()->_serialize_());
  result = result->add(code->Names()->_serialize_());
  result = result->add(code->VarNames()->_serialize_());
  result = result->add(code->ByteCode()->_serialize_());
  return result;
}

}  // namespace torchlight::object