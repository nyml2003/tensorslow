#include "Ast/Module.h"
#include "Ast/INode.h"
#include "ByteCode/PyCode.h"
#include "Object/ObjectHelper.h"
#include "Object/PyList.h"
#include "Object/PyNone.h"
#include "Object/PyObject.h"

namespace torchlight::Ast {

Object::PyObjPtr ModuleKlass::visit(
  const Object::PyObjPtr& obj,
  const Object::PyObjPtr& codeList
) {
  auto module = obj->as<Module>();
  module->SetCodeIndex(codeList->as<Object::PyList>()->Length());
  auto code = Object::CreatePyCode(module->Name())->as<Object::PyCode>();
  code->SetScope(Object::Scope::GLOBAL);
  codeList->as<Object::PyList>()->Append(code);
  Object::ForEach(
    module->Body(),
    [&codeList](const Object::PyObjPtr& stmt, Index, const Object::PyObjPtr&) {
      stmt->as<INode>()->visit(codeList);
    }
  );
  code->RegisterConst(Object::CreatePyNone());
  return Object::CreatePyNone();
}

Object::PyObjPtr ModuleKlass::emit(
  const Object::PyObjPtr& obj,
  const Object::PyObjPtr& codeList
) {
  auto module = obj->as<Module>();
  Object::ForEach(
    module->Body(),
    [&codeList](const Object::PyObjPtr& stmt, Index, const Object::PyObjPtr&) {
      stmt->as<INode>()->emit(codeList);
    }
  );
  auto selfCode = GetCodeFromList(codeList, module);
  selfCode->LoadConst(Object::CreatePyNone());
  selfCode->ReturnValue();
  return Object::CreatePyNone();
}

}  // namespace torchlight::Ast