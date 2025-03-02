#include "Ast/ClassDef.h"
#include "Ast/INode.h"
#include "ByteCode/PyCode.h"
#include "Object/ObjectHelper.h"
#include "Object/PyNone.h"
#include "Object/PyObject.h"
#include "Object/PyString.h"
#include "Tools/Tools.h"

namespace torchlight::Ast {

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
    Object::DebugPrint(selfCode->repr());
  }
  return Object::CreatePyNone();
}

}  // namespace torchlight::Ast