#include "Ast/Identifier.h"
#include "ByteCode/PyCode.h"
#include "Object/PyBoolean.h"
#include "Object/PyDictionary.h"
#include "Object/PyNone.h"
#include "Object/PyString.h"
#include "Object/PyType.h"

namespace torchlight::Ast {

Identifier::Identifier(Object::PyObjPtr _name, Ast::INodePtr parent)
  : INode(IdentifierKlass::Self(), std::move(parent)),
    name(std::dynamic_pointer_cast<Object::PyString>(_name)) {}

Object::PyStrPtr Identifier::Name() const {
  return name;
}

IdentifierKlass::IdentifierKlass() = default;

void IdentifierKlass::Initialize() {
  SetName(Object::CreatePyString("Identifier"));
  SetType(CreatePyType(Self()));
  SetAttributes(Object::CreatePyDict());
  Klass::Initialize();
}

Ast::INodePtr CreateIdentifier(Object::PyObjPtr name, Ast::INodePtr parent) {
  return std::make_shared<Identifier>(name, parent);
}

Object::PyObjPtr
IdentifierKlass::visit(Object::PyObjPtr obj, Object::PyObjPtr codeList) {
  auto builtinStr = Object::CreatePyList(
    {Object::CreatePyString("print"), Object::CreatePyString("matrix"),
     Object::CreatePyString("reshape"), Object::CreatePyString("len"),
     Object::CreatePyString("__name__"), Object::CreatePyString("randint"),
     Object::CreatePyString("sleep"), Object::CreatePyString("input")}
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

Object::PyObjPtr
IdentifierKlass::emit(Object::PyObjPtr obj, Object::PyObjPtr codeList) {
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

Object::KlassPtr IdentifierKlass::Self() {
  static Object::KlassPtr instance = std::make_shared<IdentifierKlass>();
  return instance;
}

}  // namespace torchlight::Ast