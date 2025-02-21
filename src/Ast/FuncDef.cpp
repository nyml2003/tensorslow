#include "Ast/FuncDef.h"
#include <memory>
#include "Ast/INode.h"
#include "ByteCode/PyCode.h"
#include "Collections/Iterator.h"
#include "Object/Common.h"
#include "Object/ObjectHelper.h"
#include "Object/PyDictionary.h"
#include "Object/PyInteger.h"
#include "Object/PyNone.h"
#include "Object/PyObject.h"
#include "Object/PyString.h"
#include "Object/PyType.h"
#include "Tools/Tools.h"

namespace torchlight::Ast {

FuncDef::FuncDef(
  Object::PyObjPtr _name,
  Object::PyObjPtr _parameters,
  Object::PyObjPtr _body,
  Ast::INodePtr parent
)
  : INode(FuncDefKlass::Self(), std::move(parent)) {
  name = std::dynamic_pointer_cast<Object::PyString>(_name);
  parameters = std::dynamic_pointer_cast<Object::PyList>(_parameters);
  body = std::dynamic_pointer_cast<Object::PyList>(_body);
  parents = Object::CreatePyNone();
  codeIndex = Object::CreatePyNone();
}

Object::PyStrPtr FuncDef::Name() const {
  return name;
}

Object::PyListPtr FuncDef::Parameters() const {
  return parameters;
}

Object::PyListPtr FuncDef::Body() const {
  return body;
}
Object::PyObjPtr FuncDef::Parents() const {
  return parents;
}

Object::PyObjPtr FuncDef::CodeIndex() const {
  return codeIndex;
}

void FuncDef::SetParents(Object::PyObjPtr _parents) {
  parents = std::dynamic_pointer_cast<Object::PyList>(_parents);
}

void FuncDef::SetCodeIndex(Object::PyObjPtr _codeIndex) {
  codeIndex = std::dynamic_pointer_cast<Object::PyInteger>(_codeIndex);
}

void FuncDef::SetBody(Object::PyObjPtr _body) {
  body = std::dynamic_pointer_cast<Object::PyList>(_body);
}

Ast::INodePtr CreateFuncDef(
  Object::PyObjPtr _name,
  Object::PyObjPtr _parameters,
  Object::PyObjPtr _body,
  Ast::INodePtr parent
) {
  return std::make_shared<FuncDef>(_name, _parameters, _body, parent);
}

void FuncDefKlass::Initialize() {
  SetName(Object::CreatePyString("FuncDef"));
  SetType(CreatePyType(Self()));
  SetAttributes(Object::CreatePyDict());
  Klass::Initialize();
}

FuncDefKlass::FuncDefKlass() = default;

Object::PyObjPtr
FuncDefKlass::visit(Object::PyObjPtr obj, Object::PyObjPtr codeList) {
  auto funcDef = std::dynamic_pointer_cast<FuncDef>(obj);
  funcDef->SetCodeIndex(codeList->len());
  auto code = std::dynamic_pointer_cast<Object::PyCode>(
    Object::CreatePyCode(funcDef->Name())
  );
  code->SetScope(Object::Scope::LOCAL);
  auto params = funcDef->Parameters()->Value();
  for (Index i = 0; i < params.Size(); i++) {
    code->RegisterVarName(params[i]);
  }
  Object::Invoke(codeList, Object::CreatePyString("append"), {code});
  auto parent = GetCodeFromList(codeList, funcDef->Parent());
  parent->RegisterName(funcDef->Name());
  Collections::List<Object::PyObjPtr> stmts = funcDef->Body()->Value();
  for (auto stmt = Collections::Iterator<Object::PyObjPtr>::Begin(stmts);
       !stmt.End(); stmt.Next()) {
    auto stmtNode = std::dynamic_pointer_cast<INode>(stmt.Get());
    stmtNode->visit(codeList);
  }

  parent->RegisterConst(code);
  parent->RegisterConst(funcDef->Name());
  return Object::CreatePyNone();
}

Object::PyObjPtr
FuncDefKlass::emit(Object::PyObjPtr obj, Object::PyObjPtr codeList) {
  auto funcDef = std::dynamic_pointer_cast<FuncDef>(obj);
  Collections::List<Object::PyObjPtr> stmts = funcDef->Body()->Value();
  auto selfCode = GetCodeFromList(codeList, funcDef);
  for (auto stmt = Collections::Iterator<Object::PyObjPtr>::Begin(stmts);
       !stmt.End(); stmt.Next()) {
    auto stmtNode = std::dynamic_pointer_cast<INode>(stmt.Get());
    stmtNode->emit(codeList);
  }
  if (selfCode->VarNames()->len()->ge(funcDef->Parameters()->len())) {
    selfCode->SetNLocals(Object::ToU64(selfCode->VarNames()->len()));
  } else {
    selfCode->SetNLocals(Object::ToU64(funcDef->Parameters()->len()));
  }
  auto parent = GetCodeFromList(codeList, funcDef->Parent());

  parent->LoadConst(selfCode);
  parent->LoadConst(funcDef->Name());
  parent->MakeFunction();
  parent->StoreName(funcDef->Name());
  if (ArgsHelper::Instance().Has("show_code_object")) {
    Object::DebugPrint(selfCode->repr());
  }

  return Object::CreatePyNone();
}

Object::KlassPtr FuncDefKlass::Self() {
  static Object::KlassPtr instance = std::make_shared<FuncDefKlass>();
  return instance;
}

}  // namespace torchlight::Ast