#include "Ast/Identifier.h"
#include "ByteCode/PyCode.h"
#include "Object/PyBoolean.h"
#include "Object/PyNone.h"
#include "Object/PyString.h"

namespace torchlight::Ast {

Object::PyObjPtr IdentifierKlass::visit(
  const Object::PyObjPtr& obj,
  const Object::PyObjPtr& codeList
) {
  auto builtinStr = Object::CreatePyList(
    {Object::CreatePyString("print"),     Object::CreatePyString("matrix"),
     Object::CreatePyString("reshape"),   Object::CreatePyString("len"),
     Object::CreatePyString("zeros"),     Object::CreatePyString("diag"),
     Object::CreatePyString("eye"),       Object::CreatePyString("ones"),
     Object::CreatePyString("transpose"), Object::CreatePyString("__name__"),
     Object::CreatePyString("randint"),   Object::CreatePyString("sleep"),
     Object::CreatePyString("input"),     Object::CreatePyString("int"),
     Object::CreatePyString("float"),     Object::CreatePyString("str"),
     Object::CreatePyString("list"),      Object::CreatePyString("object"),
     Object::CreatePyString("type"),      Object::CreatePyString("dict")}
  );
  auto identifier = std::dynamic_pointer_cast<Identifier>(obj);
  auto code = GetCodeFromList(codeList, identifier);
  if (Object::IsTrue(builtinStr->contains(identifier->Name()))) {
    code->RegisterName(identifier->Name());
  }
  if (code->Scope() == Object::Scope::LOCAL) {
    auto module = identifier->Parent()->Parent();
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
    auto module = identifier->Parent()->Parent();
    auto moduleCode = GetCodeFromList(codeList, module);
    if (Object::IsTrue(moduleCode->Names()->contains(identifier->Name()))) {
      code->LoadGlobal(code->IndexOfName(identifier->Name()));
    } else if (Object::IsTrue(code->VarNames()->contains(identifier->Name()))) {
      code->LoadFast(code->IndexOfVarName(identifier->Name()));
    } else {
      code->LoadGlobal(code->IndexOfName(identifier->Name()));
    }
  }
  return Object::CreatePyNone();
}

}  // namespace torchlight::Ast