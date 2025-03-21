#include "Ast/ClassDef.h"
#include "Ast/FuncDef.h"
#include "Ast/INode.h"
#include "Ast/Module.h"
#include "Function/ObjectHelper.h"
#include "Object/Core/PyNone.h"
#include "Object/Core/PyObject.h"
#include "Object/Iterator/IteratorHelper.h"
#include "Object/Runtime/PyCode.h"
#include "Object/String/PyString.h"
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
    codeIndex(0) {
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
  auto classDef = obj->as<ClassDef>();
  classDef->SetCodeIndex(codeList->as<Object::PyList>()->Length());
  auto code = Object::CreatePyCode(classDef->Name())->as<Object::PyCode>();
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
      stmt->as<INode>()->visit(codeList);
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
  auto classDef = obj->as<ClassDef>();
  auto selfCode = GetCodeFromList(codeList, classDef);
  selfCode->LoadName(Object::CreatePyString("__name__"));
  selfCode->StoreName(Object::CreatePyString("__module__"));
  selfCode->LoadConst(classDef->Name());
  selfCode->StoreName(Object::CreatePyString("__qualname__"));
  Object::ForEach(
    classDef->Body(),
    [&codeList](const Object::PyObjPtr& stmt, Index, const Object::PyObjPtr&) {
      stmt->as<INode>()->emit(codeList);
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