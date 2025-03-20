#include "ByteCode/PyCode.h"
#include "ByteCode/ByteCode.h"
#include "ByteCode/PyInst.h"
#include "Collections/BytesHelper.h"
#include "Object/Object.h"
#include "Object/ObjectHelper.h"
#include "Object/PyBoolean.h"
#include "Object/PyBytes.h"
#include "Object/PyInteger.h"
#include "Object/PyList.h"
#include "Object/PyObject.h"
#include "Object/PyString.h"

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
  if (!byteCodes->is<PyBytes>()) {
    throw std::runtime_error("byteCodes must be a bytes object");
  }
  byteCode = std::dynamic_pointer_cast<PyBytes>(byteCodes);
  if (!consts->is<PyList>()) {
    throw std::runtime_error("consts must be a list object");
  }
  this->consts = std::dynamic_pointer_cast<PyList>(consts);
  if (!names->is<PyList>()) {
    throw std::runtime_error("names must be a list object");
  }
  this->names = std::dynamic_pointer_cast<PyList>(names);
  if (!varNames->is<PyList>()) {
    throw std::runtime_error("varNames must be a list object");
  }
  this->varNames = std::dynamic_pointer_cast<PyList>(varNames);
  if (!name->is<PyString>()) {
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

PyObjPtr CodeKlass::eq(const PyObjPtr& lhs, const PyObjPtr& rhs) {
  if (!lhs->is<PyCode>() || !rhs->is<PyCode>()) {
    return CreatePyBoolean(false);
  }
  auto lhsc = lhs->as<PyCode>();
  auto rhsc = rhs->as<PyCode>();
  if (!IsTrue(lhsc->Name()->eq(rhsc->Name()))) {
    return CreatePyBoolean(false);
  }
  if (!IsTrue(lhsc->Consts()->eq(rhsc->Consts()))) {
    return CreatePyBoolean(false);
  }
  if (!IsTrue(lhsc->Names()->eq(rhsc->Names()))) {
    return CreatePyBoolean(false);
  }
  if (!IsTrue(lhsc->VarNames()->eq(rhsc->VarNames()))) {
    return CreatePyBoolean(false);
  }
  if (lhsc->NLocals() != rhsc->NLocals()) {
    return CreatePyBoolean(false);
  }
  if (!IsTrue(lhsc->Instructions()->eq(rhsc->Instructions()))) {
    return CreatePyBoolean(false);
  }
  return CreatePyBoolean(true);
}

PyObjPtr CodeKlass::repr(const PyObjPtr& self) {
  return StringConcat(CreatePyList(
    {CreatePyString("<code object at ")->as<PyString>(),
     Identity(CreatePyList({self}))->as<PyString>(), CreatePyString(">")->as<PyString>()}
  ));
}

PyObjPtr CodeKlass::_serialize_(const PyObjPtr& self) {
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
    DebugPrint(name);
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
  return instructions->Length();
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

void PyCode::LoadBuildClass() {
  instructions->Append(CreateLoadBuildClass());
}

void PyCode::StoreAttr(const PyObjPtr& obj) {
  auto index = IndexOfName(obj);
  instructions->Append(CreateStoreAttr(index));
}

void PyCode::Nop() {
  instructions->Append(CreateNop());
}

void PyCode::UnaryPositive() {
  instructions->Append(CreateUnaryPositive());
}

void PyCode::UnaryNegative() {
  instructions->Append(CreateUnaryNegative());
}

void PyCode::UnaryNot() {
  instructions->Append(CreateUnaryNot());
}

void PyCode::UnaryInvert() {
  instructions->Append(CreateUnaryInvert());
}

void PyCode::BinaryPower() {
  instructions->Append(CreateBinaryPower());
}

void PyCode::BinaryModulo() {
  instructions->Append(CreateBinaryModulo());
}

void PyCode::BinaryFloorDivide() {
  instructions->Append(CreateBinaryFloorDivide());
}

void PyCode::BinaryTrueDivide() {
  instructions->Append(CreateBinaryTrueDivide());
}

void PyCode::BinaryLShift() {
  instructions->Append(CreateBinaryLShift());
}

void PyCode::BinaryRShift() {
  instructions->Append(CreateBinaryRShift());
}

void PyCode::BinaryAnd() {
  instructions->Append(CreateBinaryAnd());
}

void PyCode::BinaryXor() {
  instructions->Append(CreateBinaryXor());
}

void PyCode::BinaryOr() {
  instructions->Append(CreateBinaryOr());
}

PyObjPtr CreatePyCode(const PyObjPtr& name) {
  auto byteCode = CreatePyBytes();
  auto consts = CreatePyList({});
  auto names = CreatePyList({});
  auto varNames = CreatePyList({});
  return std::make_shared<PyCode>(byteCode, consts, names, varNames, name, 0);
}

void PrintCode(const PyCodePtr& code) {
  auto codeObj = code->as<PyCode>();
  codeObj->str()->as<PyString>()->PrintLine();
  PyString::IncreaseIndent();
  CreatePyString("consts: ")->as<PyString>()->Print();
  codeObj->Consts()->str()->as<PyString>()->PrintLine(false);
  CreatePyString("names: ")->as<PyString>()->Print();
  codeObj->Names()->str()->as<PyString>()->PrintLine(false);
  CreatePyString("varNames: ")->as<PyString>()->Print();
  codeObj->VarNames()->str()->as<PyString>()->PrintLine(false);
  CreatePyString("instructions:")->as<PyString>()->PrintLine();
  PyString::IncreaseIndent();
  ForEach(
    codeObj->Instructions(),
    [](const PyObjPtr& inst, Index, const PyObjPtr&) {
      inst->str()->as<PyString>()->PrintLine();
    }
  );
  PyString::DecreaseIndent();
  CreatePyString("nLocals: ")->as<PyString>()->Print();
  CreatePyInteger(codeObj->NLocals())->str()->as<PyString>()->PrintLine(false);
  PyString::DecreaseIndent();
}

}  // namespace torchlight::Object