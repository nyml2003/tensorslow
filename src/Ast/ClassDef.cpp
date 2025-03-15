#include "Ast/ClassDef.h"
#include "Ast/FuncDef.h"
#include "Ast/INode.h"
#include "Ast/Module.h"
#include "ByteCode/PyCode.h"
#include "Object/ObjectHelper.h"
#include "Object/PyNone.h"
#include "Object/PyObject.h"
#include "Object/PyString.h"
#include "Tools/Tools.h"

namespace torchlight::Ast {

ClassDef::ClassDef(
  Object::PyStrPtr name,
  INodePtr bases,
  const INodePtr& parent
)
  : INode(ClassDefKlass::Self(), parent),
    name(std::move(name)),
    bases(std::move(bases)),
    body(Object::CreatePyList({})->as<Object::PyList>()),
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

Object::PyObjPtr ClassDefKlass::visit(
  const Object::PyObjPtr& obj,
  const Object::PyObjPtr& codeList
) {
  auto classDef = std::dynamic_pointer_cast<ClassDef>(obj);
  classDef->SetCodeIndex(codeList->len());
  auto code = std::dynamic_pointer_cast<Object::PyCode>(
    Object::CreatePyCode(classDef->Name())
  );
  code->RegisterName(Object::CreatePyString("__name__"));
  code->RegisterName(Object::CreatePyString("__module__"));
  code->RegisterName(Object::CreatePyString("__qualname__"));
  code->RegisterConst(classDef->Name());
  code->SetScope(Object::Scope::GLOBAL);
  codeList->as<Object::PyList>()->Append(code);
  classDef->Bases()->visit(codeList);
  auto parent = GetCodeFromList(codeList, classDef->Parent());
  parent->RegisterName(classDef->Name());
  Object::ForEach(
    classDef->Body(),
    [&codeList](const Object::PyObjPtr& stmt, Index, const Object::PyObjPtr&) {
      auto stmtNode = std::dynamic_pointer_cast<INode>(stmt);
      stmtNode->visit(codeList);
    }
  );
  code->RegisterConst(Object::CreatePyNone());
  parent->RegisterConst(code);
  parent->RegisterConst(classDef->Name());
  return Object::CreatePyNone();
}

Object::PyObjPtr ClassDefKlass::emit(
  const Object::PyObjPtr& obj,
  const Object::PyObjPtr& codeList
) {
  auto classDef = std::dynamic_pointer_cast<ClassDef>(obj);
  auto selfCode = GetCodeFromList(codeList, classDef);
  selfCode->LoadName(Object::CreatePyString("__name__"));
  selfCode->StoreName(Object::CreatePyString("__module__"));
  selfCode->LoadConst(classDef->Name());
  selfCode->StoreName(Object::CreatePyString("__qualname__"));
  Object::ForEach(
    classDef->Body(),
    [&codeList](const Object::PyObjPtr& stmt, Index, const Object::PyObjPtr&) {
      auto stmtNode = std::dynamic_pointer_cast<INode>(stmt);
      stmtNode->emit(codeList);
    }
  );
  selfCode->LoadConst(Object::CreatePyNone());
  selfCode->ReturnValue();
  auto parent = GetCodeFromList(codeList, classDef->Parent());
  parent->LoadBuildClass();
  parent->LoadConst(selfCode);
  parent->LoadConst(classDef->Name());
  parent->MakeFunction();
  parent->LoadConst(classDef->Name());
  classDef->Bases()->emit(codeList);
  parent->CallFunction(3);
  parent->StoreName(classDef->Name());
  if (ArgsHelper::Instance().Has("show_code")) {
    Object::PrintCode(selfCode);
  }
  return Object::CreatePyNone();
}

}  // namespace torchlight::Ast