#include "Ast/Module.h"
#include "Ast/INode.h"
#include "ByteCode/PyCode.h"
#include "Object/ObjectHelper.h"
#include "Object/PyNone.h"
#include "Object/PyObject.h"
#include "Object/PyString.h"

namespace torchlight::Ast {

Object::PyObjPtr ModuleKlass::visit(
  const Object::PyObjPtr& obj,
  const Object::PyObjPtr& codeList
) {
  auto module = std::dynamic_pointer_cast<Module>(obj);
  module->SetCodeIndex(codeList->len());
  auto code = std::dynamic_pointer_cast<Object::PyCode>(
    Object::CreatePyCode(module->Name())
  );
  code->SetScope(Object::Scope::GLOBAL);
  codeList->as<Object::PyList>()->Append(code);
  Object::ForEach(
    module->Body(),
    [&codeList](const Object::PyObjPtr& stmt, Index, const Object::PyObjPtr&) {
      auto stmtNode = std::dynamic_pointer_cast<INode>(stmt);
      stmtNode->visit(codeList);
    }
  );
  code->RegisterConst(Object::CreatePyNone());
  return Object::CreatePyNone();
}

Object::PyObjPtr ModuleKlass::emit(
  const Object::PyObjPtr& obj,
  const Object::PyObjPtr& codeList
) {
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

}  // namespace torchlight::Ast