#include "Ast/Identifier.h"
#include "Ast/ClassDef.h"
#include "Ast/FuncDef.h"
#include "Ast/INode.h"
#include "ByteCode/PyCode.h"
#include "Object/ObjectHelper.h"
#include "Object/PyBoolean.h"
#include "Object/PyNone.h"
#include "Object/PyString.h"

namespace torchlight::Ast {

Object::PyObjPtr IdentifierKlass::visit(
  const Object::PyObjPtr& obj,
  const Object::PyObjPtr& codeList
) {
  auto builtinStr = Object::CreatePyList({
    Object::CreatePyString("print"),    Object::CreatePyString("reshape"),
    Object::CreatePyString("Matrix"),   Object::CreatePyString("len"),
    Object::CreatePyString("__name__"), Object::CreatePyString("randint"),
    Object::CreatePyString("sleep"),    Object::CreatePyString("input"),
    Object::CreatePyString("normal"),   Object::CreatePyString("shuffle"),
    Object::CreatePyString("next"),     Object::CreatePyString("int"),
    Object::CreatePyString("float"),    Object::CreatePyString("str"),
    Object::CreatePyString("list"),     Object::CreatePyString("object"),
    Object::CreatePyString("type"),     Object::CreatePyString("dict"),
    Object::CreatePyString("slice"),    Object::CreatePyString("repr"),
    Object::CreatePyString("bool"),
  });
  auto identifier = std::dynamic_pointer_cast<Identifier>(obj);
  auto code = GetCodeFromList(codeList, identifier);
  if (Object::IsTrue(builtinStr->contains(identifier->Name()))) {
    code->RegisterName(identifier->Name());
  }
  if (code->Scope() == Object::Scope::LOCAL) {
    INodePtr module = nullptr;
    auto scope = identifier->Parent();
    if (scope->is<ClassDef>()) {
      module = scope->as<ClassDef>()->Parents()->GetItem(0)->as<INode>();
    }
    if (scope->is<FuncDef>()) {
      module = scope->as<FuncDef>()->Parents()->GetItem(0)->as<INode>();
    }
    auto moduleCode = GetCodeFromList(codeList, module);
    if (Object::IsTrue(moduleCode->Names()->contains(identifier->Name()))) {
      code->RegisterName(identifier->Name());
    }
  }
  return Object::CreatePyNone();
}

Object::PyObjPtr IdentifierKlass::emit(
  const Object::PyObjPtr& obj,
  const Object::PyObjPtr& codeList
) {
  auto identifier = std::dynamic_pointer_cast<Identifier>(obj);
  auto code = GetCodeFromList(codeList, identifier);
  if (code->Scope() == Object::Scope::GLOBAL) {
    code->LoadName(identifier->Name());
  }
  if (code->Scope() == Object::Scope::LOCAL) {
    auto scope = identifier->Parent();
    INodePtr module = nullptr;
    if (scope->is<ClassDef>()) {
      module = scope->as<ClassDef>()->Parents()->GetItem(0)->as<INode>();
    }
    if (scope->is<FuncDef>()) {
      module = scope->as<FuncDef>()->Parents()->GetItem(0)->as<INode>();
    }
    auto moduleCode = GetCodeFromList(codeList, module);
    try {
      if (Object::IsTrue(code->VarNames()->contains(identifier->Name()))) {
        code->LoadFast(code->IndexOfVarName(identifier->Name()));
      } else if (Object::IsTrue(code->Names()->contains(identifier->Name()))) {
        code->LoadName(identifier->Name());
        // code->LoadGlobal(code->IndexOfName(identifier->Name()));
      } else if (Object::IsTrue(moduleCode->Names()->contains(identifier->Name()
                 ))) {
        code->LoadGlobal(moduleCode->IndexOfName(identifier->Name()));
      }
    } catch (const std::exception& e) {
      auto name = identifier->Name()->Value();
      Object::DebugPrint(moduleCode->Names());
      Object::DebugPrint(moduleCode->VarNames());
      Object::DebugPrint(code->Names());
      Object::DebugPrint(code->VarNames());
      throw(e);
    }
  }
  return Object::CreatePyNone();
}

}  // namespace torchlight::Ast