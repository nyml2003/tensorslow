#include "ByteCode/PyCode.h"
#include "ByteCode/ByteCode.h"
#include "ByteCode/PyInst.h"
#include "Collections/BytesHelper.h"
#include "Collections/IntegerHelper.h"
#include "Collections/StringHelper.h"
#include "Object/Klass.h"
#include "Object/PyBytes.h"
#include "Object/PyDictionary.h"
#include "Object/PyInteger.h"
#include "Object/PyList.h"
#include "Object/PyObject.h"
#include "Object/PyString.h"
#include "Object/PyType.h"

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
  auto insts = CreatePyList({});
  instructions = std::dynamic_pointer_cast<PyList>(insts);
  this->nLocals = nLocals;
}

PyListPtr PyCode::Instructions() {
  return instructions;
}

void PyCode::SetInstructions(const PyListPtr& insts) {
  instructions = insts;
}

void PyCode::SetByteCode(const PyBytesPtr& byteCodes) {
  byteCode = byteCodes;
}

void PyCode::SetNLocals(Index nLocals) {
  this->nLocals = nLocals;
}

void PyCode::SetScope(enum Scope scope) {
  this->scope = scope;
}

Scope PyCode::Scope() const {
  return scope;
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

CodeKlass::CodeKlass() = default;

void CodeKlass::Initialize() {
  SetType(CreatePyType(Self()));
  SetName(CreatePyString("code"));
  SetAttributes(CreatePyDict());
  Klass::Initialize();
}

KlassPtr CodeKlass::Self() {
  static KlassPtr instance = std::make_shared<CodeKlass>();
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
  repr = repr->add(
    CreatePyString(Collections::CreateStringWithCString("instructions:\n"))
  );
  repr = repr->add(code->Instructions()->repr());
  repr = repr->add(CreatePyString(Collections::CreateStringWithCString("\n")));
  repr =
    repr->add(CreatePyString(Collections::CreateStringWithCString("nLocals: "))
    );
  repr = repr->add(
    CreatePyInteger(Collections::CreateIntegerWithU64(code->NLocals()))->repr()
  );
  repr =
    repr->add(CreatePyString(Collections::CreateStringWithCString("\n</code>\n")
    ));
  return repr;
}

PyObjPtr CodeKlass::str(PyObjPtr self) {
  // 返回内存地址
  return CreatePyString(Collections::CreateStringWithCString("<code object "))
    ->add(std::dynamic_pointer_cast<PyCode>(self)->Name())
    ->add(CreatePyString(Collections::CreateStringWithCString(" at ")))
    ->add(CreatePyString(Collections::CreateStringWithCString(
      std::to_string(reinterpret_cast<uint64_t>(self.get())).c_str()
    )))
    ->add(CreatePyString(Collections::CreateStringWithCString(">")));
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
      ->add(code->Instructions()->_serialize_()->_serialize_());
  return result;
}

Index PyCode::IndexOfConst(const PyObjPtr& obj) {
  if (!consts->Contains(obj)) {
    DebugPrint(obj);
    throw std::runtime_error("PyCode::IndexOfConst(): obj not found");
  }
  return consts->IndexOf(obj);
}

void PyCode::RegisterConst(const PyObjPtr& obj) {
  if (!consts->Contains(obj)) {
    consts->Append(obj);
  }
}

Index PyCode::IndexOfName(const PyObjPtr& name) {
  if (!names->Contains(name)) {
    throw std::runtime_error("PyCode::IndexOfName(): name not found");
  }
  return names->IndexOf(name);
}

void PyCode::RegisterName(const PyObjPtr& name) {
  if (!names->Contains(name)) {
    names->Append(name);
  }
}

Index PyCode::IndexOfVarName(const PyObjPtr& name) {
  if (!varNames->Contains(name)) {
    throw std::runtime_error("PyCode::IndexOfVarName(): name not found");
  }
  return varNames->IndexOf(name);
}

void PyCode::RegisterVarName(const PyObjPtr& name) {
  if (!varNames->Contains(name)) {
    varNames->Append(name);
  }
}

void PyCode::LoadConst(const PyObjPtr& obj) {
  auto index = IndexOfConst(obj);
  instructions->Append(CreateLoadConst(index));
}

void PyCode::LoadName(const PyObjPtr& obj) {
  auto index = IndexOfName(obj);
  instructions->Append(CreateLoadName(index));
}

void PyCode::StoreName(const PyObjPtr& obj) {
  auto index = IndexOfName(obj);
  instructions->Append(CreateStoreName(index));
}

void PyCode::LoadAttr(const PyObjPtr& obj) {
  auto index = IndexOfName(obj);
  instructions->Append(CreateLoadAttr(index));
}

void PyCode::LoadGlobal(Index index) {
  if (index == 5) {
    ;
  }
  instructions->Append(CreateLoadGlobal(index));
}

void PyCode::LoadFast(Index index) {
  instructions->Append(CreateLoadFast(index));
}

void PyCode::StoreFast(const PyObjPtr& obj) {
  auto index = IndexOfVarName(obj);
  instructions->Append(CreateStoreFast(index));
}

void PyCode::BuildList(Index size) {
  instructions->Append(CreateBuildList(size));
}

void PyCode::CallFunction(Index nArgs) {
  instructions->Append(CreateCallFunction(nArgs));
}

void PyCode::MakeFunction() {
  instructions->Append(CreateMakeFunction());
}

void PyCode::ReturnValue() {
  instructions->Append(CreateReturnValue());
}

Index PyCode::PopJumpIfFalse() {
  instructions->Append(CreatePopJumpIfFalse(0));
  return ToU64(instructions->len());
}

void PyCode::JumpAbsolute(Index index) {
  instructions->Append(CreateJumpAbsolute(index));
}

void PyCode::PopTop() {
  instructions->Append(CreatePopTop());
}

void PyCode::StoreSubscr() {
  instructions->Append(CreateStoreSubscr());
}

void PyCode::GetIter() {
  instructions->Append(CreateGetIter());
}

Index PyCode::ForIter(Index index) {
  instructions->Append(CreateForIter(index));
  return instructions->Length();
}

PyObjPtr CreatePyCode(const PyObjPtr& name) {
  auto byteCode = CreatePyBytes();
  auto consts = CreatePyList({});
  auto names = CreatePyList({});
  auto varNames = CreatePyList({});
  return std::make_shared<PyCode>(byteCode, consts, names, varNames, name, 0);
}

}  // namespace torchlight::Object