#include "Object/Runtime/PyCode.h"
#include "ByteCode/ByteCode.h"
#include "Collections/String/BytesHelper.h"
#include "Function/BuiltinFunction.h"
#include "Object/Container/PyList.h"
#include "Object/Core/PyBoolean.h"
#include "Object/Core/PyObject.h"
#include "Object/Iterator/IteratorHelper.h"
#include "Object/Number/PyInteger.h"
#include "Object/Object.h"
#include "Object/Runtime/PyInst.h"
#include "Object/String/PyBytes.h"
#include "Object/String/PyString.h"
#include "Tools/Logger/VerboseLogger.h"

namespace tensorslow::Object {

PyCode::PyCode(
  PyBytesPtr byteCodes,
  PyListPtr consts,
  PyListPtr names,
  PyListPtr varNames,
  PyStrPtr name,
  Index nLocals
)
  : PyObject(CodeKlass::Self()),
    byteCode(std::move(byteCodes)),
    instructions(CreatePyList(0)->as<PyList>()),
    consts(std::move(consts)),
    names(std::move(names)),
    varNames(std::move(varNames)),
    name(std::move(name)),
    nLocals(nLocals) {}

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

Scope PyCode::GetScope() const {
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
  if (!lhs->is(CodeKlass::Self()) || !rhs->is(CodeKlass::Self())) {
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
     Function::Identity(CreatePyList({self}))->as<PyString>(),
     CreatePyString(">")->as<PyString>()}
  ));
}

PyObjPtr CodeKlass::_serialize_(const PyObjPtr& self) {
  if (!self->is(CodeKlass::Self())) {
    throw std::runtime_error("PyCode::_serialize_(): obj is not a code object");
  }
  auto code = self->as<PyCode>();
  Collections::StringBuilder result(Collections::Serialize(Literal::CODE));
  result.Append(code->Consts()->_serialize_()->as<PyBytes>()->Value());
  result.Append(code->Names()->_serialize_()->as<PyBytes>()->Value());
  result.Append(code->VarNames()->_serialize_()->as<PyBytes>()->Value());
  result.Append(code->Name()->_serialize_()->as<PyBytes>()->Value());
  result.Append(Collections::Serialize(code->NLocals()));
  result.Append(
    code->Instructions()->_serialize_()->_serialize_()->as<PyBytes>()->Value()
  );
  return CreatePyBytes(result.ToString());
}

Index PyCode::IndexOfConst(const PyObjPtr& obj) {
  if (!consts->Contains(obj)) {
    Function::DebugPrint(obj);
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
    Function::DebugPrint(name);
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

PyCodePtr CreatePyCode(const PyStrPtr& name) {
  auto byteCode = CreatePyString("")->as<PyBytes>();
  auto consts = CreatePyList()->as<PyList>();
  auto names = CreatePyList()->as<PyList>();
  auto varNames = CreatePyList()->as<PyList>();
  return std::make_shared<PyCode>(byteCode, consts, names, varNames, name, 0);
}

void PrintCode(const PyCodePtr& code) {
  auto codeObj = code->as<PyCode>();
  VerboseLogger::getInstance().log(codeObj->str()->as<PyString>()->ToCppString()
  );
  VerboseLogger::getInstance().log("\n");
  VerboseLogger::IncreaseIndent();

  VerboseLogger::getInstance().log("name: \n");
  VerboseLogger::getInstance().log(
    codeObj->Name()->str()->as<PyString>()->ToCppString()
  );
  VerboseLogger::getInstance().log("\n");

  VerboseLogger::getInstance().log("consts: \n");
  VerboseLogger::getInstance().log(
    codeObj->Consts()->str()->as<PyString>()->ToCppString()
  );
  VerboseLogger::getInstance().log("\n");

  VerboseLogger::getInstance().log("names: \n");
  VerboseLogger::getInstance().log(
    codeObj->Names()->str()->as<PyString>()->ToCppString()
  );
  VerboseLogger::getInstance().log("\n");

  VerboseLogger::getInstance().log("varNames: \n");
  VerboseLogger::getInstance().log(
    codeObj->VarNames()->str()->as<PyString>()->ToCppString()
  );
  VerboseLogger::getInstance().log("\n");

  VerboseLogger::getInstance().log("instructions:\n");
  VerboseLogger::IncreaseIndent();

  for (Index i = 0; i < codeObj->Instructions()->Length(); i++) {
    auto inst = codeObj->Instructions()->GetItem(i);
    std::string line = std::to_string(i) + ": " +
                       inst->str()->as<PyString>()->ToCppString() + "\n";
    VerboseLogger::getInstance().log(line);
  }

  VerboseLogger::DecreaseIndent();
  VerboseLogger::getInstance().log("nLocals: ");
  VerboseLogger::getInstance().log(std::to_string(codeObj->NLocals()) + "\n");

  VerboseLogger::DecreaseIndent();
}

}  // namespace tensorslow::Object