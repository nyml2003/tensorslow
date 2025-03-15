#include "Ast/FuncDef.h"
#include "Ast/ClassDef.h"
#include "Ast/INode.h"
#include "Ast/Module.h"
#include "ByteCode/PyCode.h"
#include "Object/ObjectHelper.h"
#include "Object/PyNone.h"
#include "Object/PyObject.h"
#include "Tools/Tools.h"

namespace torchlight::Ast {

FuncDef::FuncDef(
  Object::PyStrPtr name,
  Object::PyListPtr parameters,
  Object::PyListPtr body,
  const INodePtr& parent
)
  : INode(FuncDefKlass::Self(), parent),
    name(std::move(name)),
    parameters(std::move(parameters)),
    body(std::move(body)),
    parents(Object::CreatePyList({})->as<Object::PyList>()),
    codeIndex(nullptr) {
  if (parent->is<Module>()) {
    parents = Object::CreatePyList({parent})->as<Object::PyList>();
  }
  if (parent->is<FuncDef>()) {
    parents = parent->as<FuncDef>()->Parents();
    parents->Append(parent);
  }
  if (parent->is<ClassDef>()) {
    parents = parent->as<ClassDef>()->Parents();
    parents->Append(parent);
  }
}

Object::PyObjPtr FuncDefKlass::visit(
  const Object::PyObjPtr& obj,
  const Object::PyObjPtr& codeList
) {
  auto funcDef = std::dynamic_pointer_cast<FuncDef>(obj);
  funcDef->SetCodeIndex(codeList->len());
  auto code = std::dynamic_pointer_cast<Object::PyCode>(
    Object::CreatePyCode(funcDef->Name())
  );
  code->SetScope(Object::Scope::LOCAL);
  Object::ForEach(
    funcDef->Parameters(),
    [&code](const Object::PyObjPtr& param, Index, const Object::PyObjPtr&) {
      code->RegisterVarName(param);
    }
  );
  code->RegisterConst(Object::CreatePyNone());
  codeList->as<Object::PyList>()->Append(code);
  auto parent = GetCodeFromList(codeList, funcDef->Parent());
  parent->RegisterName(funcDef->Name());
  Object::ForEach(
    funcDef->Body(),
    [&codeList](const Object::PyObjPtr& stmt, Index, const Object::PyObjPtr&) {
      auto stmtNode = std::dynamic_pointer_cast<INode>(stmt);
      stmtNode->visit(codeList);
    }
  );
  parent->RegisterConst(code);
  parent->RegisterConst(funcDef->Name());
  return Object::CreatePyNone();
}

Object::PyObjPtr FuncDefKlass::emit(
  const Object::PyObjPtr& obj,
  const Object::PyObjPtr& codeList
) {
  auto funcDef = std::dynamic_pointer_cast<FuncDef>(obj);
  auto selfCode = GetCodeFromList(codeList, funcDef);
  Object::ForEach(
    funcDef->Body(),
    [&codeList](const Object::PyObjPtr& stmt, Index, const Object::PyObjPtr&) {
      auto stmtNode = std::dynamic_pointer_cast<INode>(stmt);
      stmtNode->emit(codeList);
    }
  );
  if (selfCode->VarNames()->len()->ge(funcDef->Parameters()->len())) {
    selfCode->SetNLocals(selfCode->VarNames()->Length());
  } else {
    selfCode->SetNLocals(funcDef->Parameters()->Length());
  }
  selfCode->LoadConst(Object::CreatePyNone());
  selfCode->ReturnValue();
  auto parent = GetCodeFromList(codeList, funcDef->Parent());
  parent->LoadConst(selfCode);
  parent->LoadConst(funcDef->Name());
  parent->MakeFunction();
  parent->StoreName(funcDef->Name());
  if (ArgsHelper::Instance().Has("show_code")) {
    Object::PrintCode(selfCode);
  }
  return Object::CreatePyNone();
}

}  // namespace torchlight::Ast