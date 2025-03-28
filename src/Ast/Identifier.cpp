#include "Ast/Identifier.h"
#include <iostream>
#include "Ast/ClassDef.h"
#include "Ast/FuncDef.h"
#include "Ast/INode.h"
#include "Function/ObjectHelper.h"
#include "Object/Core/PyBoolean.h"
#include "Object/Core/PyNone.h"
#include "Object/Runtime/PyCode.h"

namespace torchlight::Ast {

Object::PyObjPtr IdentifierKlass::visit(
  const Object::PyObjPtr& obj,
  const Object::PyObjPtr& codeList
) {
  auto identifier = obj->as<Identifier>();
  auto code = GetCodeFromList(codeList, identifier);
  auto name = identifier->Name();
  auto scope = code->Scope();
  auto registry = IdentifierRegistry::UNREGISTERED;
  auto mode = identifier->Mode();
  if (scope == Object::Scope::GLOBAL) {
    bool found = false;
    if (code->Names()->Contains(name)) {
      registry = IdentifierRegistry::GLOBAL_NAME;
      found = true;
    }
    if (!found && identifier->Builtins()->Contains(name)) {
      registry = IdentifierRegistry::BUILTIN;
    }
  } else {
    auto context = identifier->Parent();
    INodePtr module = nullptr;
    if (context->is<ClassDef>()) {
      module = context->as<ClassDef>()->Parents()->GetItem(0)->as<INode>();
    }
    if (context->is<FuncDef>()) {
      module = context->as<FuncDef>()->Parents()->GetItem(0)->as<INode>();
    }
    auto moduleCode = GetCodeFromList(codeList, module);
    registry =
      GetIdentifierRegistry(name, code, moduleCode, identifier->Builtins());
  }
  if (mode == STOREORLOAD::STORE && registry == IdentifierRegistry::UNREGISTERED) {
    if (scope == Object::Scope::GLOBAL) {
      code->RegisterName(name);
      return Object::CreatePyNone();
    } else if (scope == Object::Scope::LOCAL) {
      code->RegisterVarName(name);
      return Object::CreatePyNone();
    }
  }
  if (mode == STOREORLOAD::STORE && registry == IdentifierRegistry::BUILTIN) {
    throw std::runtime_error(
      "Cannot store builtin variable" + name->ToCppString()
    );
  }
  if (mode == STOREORLOAD::STORE && registry == IdentifierRegistry::GLOBAL_NAME) {
    code->RegisterName(name);
    return Object::CreatePyNone();
  }
  if (mode == STOREORLOAD::STORE && registry == IdentifierRegistry::LOCAL_VARNAME) {
    code->RegisterVarName(name);
    return Object::CreatePyNone();
  }
  if (mode == STOREORLOAD::LOAD && registry == IdentifierRegistry::BUILTIN) {
    code->RegisterName(name);
    return Object::CreatePyNone();
  }
  if (mode == STOREORLOAD::LOAD && registry == IdentifierRegistry::GLOBAL_NAME) {
    code->RegisterName(name);
    return Object::CreatePyNone();
  }
  if (mode == STOREORLOAD::LOAD && registry == IdentifierRegistry::LOCAL_NAME) {
    code->RegisterName(name);
    return Object::CreatePyNone();
  }
  if (mode == STOREORLOAD::LOAD && registry == IdentifierRegistry::LOCAL_VARNAME) {
    code->RegisterVarName(name);
    return Object::CreatePyNone();
  }
  if (mode == STOREORLOAD::LOAD && registry == IdentifierRegistry::UNREGISTERED) {
    throw std::runtime_error(
      "NameError: name '" + name->ToCppString() + "' is not defined"
    );
  }
  throw std::runtime_error(
    "NameError: name '" + name->ToCppString() + "' is not defined"
  );
  return Object::CreatePyNone();
}

Object::PyObjPtr IdentifierKlass::emit(
  const Object::PyObjPtr& obj,
  const Object::PyObjPtr& codeList
) {
  auto identifier = obj->as<Identifier>();
  auto code = GetCodeFromList(codeList, identifier);
  auto name = identifier->Name();
  auto scope = code->Scope();
  auto mode = identifier->Mode();
  if (scope == Object::Scope::GLOBAL) {
    // 当前是GLOBAL
    if (mode == STOREORLOAD::STORE) {
      code->StoreName(name);
    }
    if (mode == STOREORLOAD::LOAD) {
      code->LoadName(name);
    }
    return Object::CreatePyNone();
  }

  if (scope == Object::Scope::LOCAL) {
    auto context = identifier->Parent();
    INodePtr module = nullptr;
    if (context->is<ClassDef>()) {
      module = context->as<ClassDef>()->Parents()->GetItem(0)->as<INode>();
    }
    if (context->is<FuncDef>()) {
      module = context->as<FuncDef>()->Parents()->GetItem(0)->as<INode>();
    }
    auto moduleCode = GetCodeFromList(codeList, module);
    auto registry =
      GetIdentifierRegistry(name, code, moduleCode, identifier->Builtins());

    if (registry == IdentifierRegistry::LOCAL_VARNAME &&
            mode == STOREORLOAD::STORE && code->VarNames()->Contains(name)) {
      code->StoreFast(name);
      return Object::CreatePyNone();
    }
    if (registry == IdentifierRegistry::LOCAL_NAME &&
            mode == STOREORLOAD::STORE && code->Names()->Contains(name)) {
      code->StoreName(name);
      return Object::CreatePyNone();
    }
    if (registry == IdentifierRegistry::GLOBAL_NAME &&
                mode == STOREORLOAD::STORE && code->Names()->Contains(name)) {
      code->StoreName(name);
      return Object::CreatePyNone();
    }
    if (registry == IdentifierRegistry::BUILTIN && mode == STOREORLOAD::LOAD) {
      code->LoadName(name);
      return Object::CreatePyNone();
    }
    if (registry == IdentifierRegistry::LOCAL_VARNAME &&
                mode == STOREORLOAD::LOAD && code->VarNames()->Contains(name)) {
      code->LoadFast(name);
      return Object::CreatePyNone();
    }
    if (registry == IdentifierRegistry::LOCAL_NAME &&
                        mode == STOREORLOAD::LOAD && code->Names()->Contains(name)) {
      code->LoadName(name);
      return Object::CreatePyNone();
    }
    if (registry == IdentifierRegistry::GLOBAL_NAME &&
                    mode == STOREORLOAD::LOAD && moduleCode->Names()->Contains(name)) {
      code->LoadName(name);
      return Object::CreatePyNone();
    }
    std::cout << "Registry: " << static_cast<int>(registry) << std::endl;
    std::cout << "Name: " << name->ToCppString() << std::endl;
    std::cout << "Builtins: " << std::flush;
    identifier->Builtins()->str()->as<Object::PyString>()->PrintLine();
    std::cout << "Scope: " << std::flush;
    Object::PrintCode(code);
    std::cout << "Module: " << std::flush;
    Object::PrintCode(
      codeList->as<Object::PyList>()->GetItem(0)->as<Object::PyCode>()
    );

    throw std::runtime_error(
      "NameError: name '" + name->ToCppString() + "' is not defined"
    );
  }
  return Object::CreatePyNone();
}

IdentifierRegistry GetIdentifierRegistry(
  const Object::PyStrPtr& name,
  const Object::PyCodePtr& current,
  const Object::PyCodePtr& global,
  const Object::PyListPtr& builtins
) {
  if (current->VarNames()->Contains(name)) {
    return IdentifierRegistry::
      LOCAL_VARNAME;  // 说明已经在local的varname里面注册了，说明是fast变量
  }
  if (current->Names()->Contains(name)) {
    return IdentifierRegistry::
      LOCAL_NAME;  // 说明已经在local的names里面注册了，说明是name变量
  }
  if (global->Names()->Contains(name)) {
    return IdentifierRegistry::
      GLOBAL_NAME;  // 说明已经在global的names里面注册了，说明是name变量
  }
  if (builtins->Contains(name)) {
    return IdentifierRegistry::BUILTIN;
  }
  return IdentifierRegistry::UNREGISTERED;
}

}  // namespace torchlight::Ast