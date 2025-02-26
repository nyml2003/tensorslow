#include "Ast/ClassDef.h"
#include <memory>
#include "Ast/INode.h"
#include "ByteCode/PyCode.h"

#include "Object/ObjectHelper.h"
#include "Object/PyDictionary.h"
#include "Object/PyInteger.h"
#include "Object/PyNone.h"
#include "Object/PyObject.h"
#include "Object/PyString.h"
#include "Object/PyType.h"
#include "Tools/Tools.h"

namespace torchlight::Ast {

ClassDef::ClassDef(
  const Object::PyObjPtr& _name,
  const Object::PyObjPtr& _bases,
  const Ast::INodePtr& parent
)
  : INode(ClassDefKlass::Self(), parent) {
  name = std::dynamic_pointer_cast<Object::PyString>(_name);
  bases = std::dynamic_pointer_cast<Object::PyList>(_bases);
  body = nullptr;
  parents = Object::CreatePyNone();
  codeIndex = Object::CreatePyNone();
}

Object::PyStrPtr ClassDef::Name() const {
  return name;
}

Object::PyListPtr ClassDef::Bases() const {
  return bases;
}

Object::PyListPtr ClassDef::Body() const {
  return body;
}
Object::PyObjPtr ClassDef::Parents() const {
  return parents;
}

Object::PyObjPtr ClassDef::CodeIndex() const {
  return codeIndex;
}

void ClassDef::SetCodeIndex(const Object::PyObjPtr& _codeIndex) {
  codeIndex = std::dynamic_pointer_cast<Object::PyInteger>(_codeIndex);
}

void ClassDef::SetBody(const Object::PyObjPtr& _body) {
  body = std::dynamic_pointer_cast<Object::PyList>(_body);
}

Ast::INodePtr CreateClassDef(
  const Object::PyObjPtr& _name,
  const Object::PyObjPtr& _bases,
  const Ast::INodePtr& parent
) {
  return std::make_shared<ClassDef>(_name, _bases, parent);
}

void ClassDefKlass::Initialize() {
  SetName(Object::CreatePyString("ClassDef"));
  SetType(CreatePyType(Self()));
  SetAttributes(Object::CreatePyDict());
  Klass::Initialize();
}

ClassDefKlass::ClassDefKlass() = default;

Object::PyObjPtr
ClassDefKlass::visit(Object::PyObjPtr obj, Object::PyObjPtr codeList) {
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
  Object::Invoke(codeList, Object::CreatePyString("append"), {code});
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

Object::PyObjPtr
ClassDefKlass::emit(Object::PyObjPtr obj, Object::PyObjPtr codeList) {
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
  parent->CallFunction(2);
  parent->StoreName(classDef->Name());
  if (ArgsHelper::Instance().Has("show_code")) {
    Object::DebugPrint(selfCode->str());
  }
  return Object::CreatePyNone();
}

Object::KlassPtr ClassDefKlass::Self() {
  static Object::KlassPtr instance = std::make_shared<ClassDefKlass>();
  return instance;
}

}  // namespace torchlight::Ast