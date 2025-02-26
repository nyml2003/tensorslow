#include "Ast/Module.h"
#include "Ast/INode.h"
#include "ByteCode/PyCode.h"
#include "Object/ObjectHelper.h"
#include "Object/PyDictionary.h"
#include "Object/PyList.h"
#include "Object/PyNone.h"
#include "Object/PyObject.h"
#include "Object/PyString.h"
#include "Object/PyType.h"

namespace torchlight::Ast {

Module::Module(Object::PyObjPtr body, Object::PyObjPtr name)
  : INode(ModuleKlass::Self(), nullptr),
    body(std::dynamic_pointer_cast<Object::PyList>(body)),
    name(std::dynamic_pointer_cast<Object::PyString>(name)) {}

Object::PyListPtr Module::Body() const {
  return this->body;
}

Object::PyStrPtr Module::Name() const {
  return this->name;
}

Object::PyObjPtr Module::CodeIndex() const {
  return this->codeIndex;
}

void Module::SetCodeIndex(Object::PyObjPtr _codeIndex) {
  this->codeIndex = std::move(_codeIndex);
}

void Module::SetBody(Object::PyObjPtr _body) {
  this->body = std::dynamic_pointer_cast<Object::PyList>(_body);
}

Ast::INodePtr CreateModule(Object::PyObjPtr body, Object::PyObjPtr name) {
  return std::make_shared<Module>(body, name);
}

ModuleKlass::ModuleKlass() = default;

Object::KlassPtr ModuleKlass::Self() {
  static auto instance = std::make_shared<ModuleKlass>();
  return instance;
}

Object::PyObjPtr
ModuleKlass::visit(Object::PyObjPtr obj, Object::PyObjPtr codeList) {
  auto module = std::dynamic_pointer_cast<Module>(obj);
  module->SetCodeIndex(codeList->len());
  auto code = std::dynamic_pointer_cast<Object::PyCode>(
    Object::CreatePyCode(module->Name())
  );
  code->SetScope(Object::Scope::GLOBAL);
  code->RegisterConst(Object::CreatePyNone());
  Object::Invoke(codeList, Object::CreatePyString("append"), {code});
  Object::ForEach(
    module->Body(),
    [&codeList](const Object::PyObjPtr& stmt, Index, const Object::PyObjPtr&) {
      auto stmtNode = std::dynamic_pointer_cast<INode>(stmt);
      stmtNode->visit(codeList);
    }
  );
  
  return Object::CreatePyNone();
}

Object::PyObjPtr
ModuleKlass::emit(Object::PyObjPtr obj, Object::PyObjPtr codeList) {
  auto module = std::dynamic_pointer_cast<Module>(obj);
  Object::ForEach(
    module->Body(),
    [&codeList](const Object::PyObjPtr& stmt, Index, const Object::PyObjPtr&) {
      auto stmtNode = std::dynamic_pointer_cast<INode>(stmt);
      stmtNode->emit(codeList);
    }
  );
  auto selfCode = GetCodeFromList(codeList, module);
  selfCode->LoadConst(Object::CreatePyNone());
  selfCode->ReturnValue();
  return Object::CreatePyNone();
}

void ModuleKlass::Initialize() {
  SetName(Object::CreatePyString("module"));
  SetType(Object::CreatePyType(Self()));
  SetAttributes(Object::CreatePyDict());
  Object::Klass::Initialize();
}

}  // namespace torchlight::Ast