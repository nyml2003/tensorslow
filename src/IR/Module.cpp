#include "IR/Module.h"
#include "Function/BuiltinFunction.h"
#include "IR/INode.h"
#include "Object/Container/PyList.h"
#include "Object/Core/PyNone.h"
#include "Object/Core/PyObject.h"
#include "Object/Iterator/IteratorHelper.h"
#include "Object/Runtime/PyCode.h"
namespace tensorslow::IR {

Object::PyObjPtr ModuleKlass::visit(
  const Object::PyObjPtr& obj,
  const Object::PyObjPtr& codeList
) {
  auto module = obj->as<Module>();
  module->SetCodeIndex(codeList->as<Object::PyList>()->Length());
  auto code = Object::CreatePyCode(module->Name());
  code->SetScope(Object::Scope::GLOBAL);
  codeList->as<Object::PyList>()->Append(code);
  Object::ForEach(module->Body(), [&codeList](const Object::PyObjPtr& stmt) {
    stmt->as<INode>()->visit(codeList);
  });
  code->RegisterConst(Object::CreatePyNone());
  return Object::CreatePyNone();
}

Object::PyObjPtr ModuleKlass::emit(
  const Object::PyObjPtr& obj,
  const Object::PyObjPtr& codeList
) {
  auto module = obj->as<Module>();
  Object::ForEach(module->Body(), [&codeList](const Object::PyObjPtr& stmt) {
    stmt->as<INode>()->emit(codeList);
  });
  auto selfCode = GetCodeFromList(codeList, module);
  selfCode->LoadConst(Object::CreatePyNone());
  selfCode->ReturnValue();
  return Object::CreatePyNone();
}

Object::PyObjPtr ModuleKlass::print(const Object::PyObjPtr& obj) {
  auto module = obj->as<Module>();
  PrintNode(
    module,
    Object::StringConcat(
      Object::CreatePyList({Object::CreatePyString("Module "), module->Name()})
    )
      ->as<Object::PyString>()
  );
  Object::ForEach(module->Body(), [&module](const Object::PyObjPtr& stmt) {
    stmt->as<INode>()->print();
    PrintEdge(module, stmt);
  });
  return Object::CreatePyNone();
}

}  // namespace tensorslow::IR