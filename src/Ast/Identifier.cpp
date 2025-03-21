#include "Ast/Identifier.h"
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
  // 如果当前变量是内置变量, 注册到names
  if (identifier->Builtins()->Contains(name)) {
    code->RegisterName(name);
    return Object::CreatePyNone();
  }
  // 如果当前变量在module内，注册到names
  if (code->Scope() == Object::Scope::GLOBAL) {
    code->RegisterName(name);
    return Object::CreatePyNone();
  }
  // 如果当前变量在类定义和函数定义内，注册需要分类讨论
  if (code->Scope() == Object::Scope::LOCAL) {
    if (identifier->Mode() == STOREORLOAD::STORE) {
      // 当前是STORE模式，一定是varName，当前不支持global, nolocal, 闭包
      if (!code->VarNames()->Contains(name)) {
        code->RegisterVarName(name);
      }
      return Object::CreatePyNone();
    }
    if (identifier->Mode() == STOREORLOAD::LOAD) {
      // 当前是LOAD模式，注册到name吧，可能是外部变量
      if (code->VarNames()->Contains(name)) {
        return Object::CreatePyNone();
      }
      if (code->Names()->Contains(name)) {
        return Object::CreatePyNone();
      }
      // 获取module, 一般是parents的第一个
      auto scope = identifier->Parent();
      INodePtr module = nullptr;
      if (scope->is<ClassDef>()) {
        module = scope->as<ClassDef>()->Parents()->GetItem(0)->as<INode>();
      }
      if (scope->is<FuncDef>()) {
        module = scope->as<FuncDef>()->Parents()->GetItem(0)->as<INode>();
      }
      auto moduleCode = GetCodeFromList(codeList, module);
      if (!moduleCode->Names()->Contains(name)) {
        throw std::runtime_error(
          "NameError: name '" + name->ToCppString() + "' is not defined"
        );
      }
      // 说明module内有这个名字，注册到code的names
      if (!code->Names()->Contains(name)) {
        code->RegisterName(name);
      }
    }
  }
  return Object::CreatePyNone();
}

Object::PyObjPtr IdentifierKlass::emit(
  const Object::PyObjPtr& obj,
  const Object::PyObjPtr& codeList
) {
  auto identifier = obj->as<Identifier>();
  auto code = GetCodeFromList(codeList, identifier);
  auto name = identifier->Name();
  if (code->Scope() == Object::Scope::GLOBAL) {
    // 当前是GLOBAL
    if (identifier->Mode() == STOREORLOAD::STORE) {
      code->StoreName(name);
    }
    if (identifier->Mode() == STOREORLOAD::LOAD) {
      code->LoadName(name);
    }
    return Object::CreatePyNone();
  }
  if (code->Scope() == Object::Scope::LOCAL) {
    auto scope = identifier->Parent();
    // 获取module, 一般是parents的第一个
    INodePtr module = nullptr;
    if (scope->is<ClassDef>()) {
      module = scope->as<ClassDef>()->Parents()->GetItem(0)->as<INode>();
    }
    if (scope->is<FuncDef>()) {
      module = scope->as<FuncDef>()->Parents()->GetItem(0)->as<INode>();
    }
    auto moduleCode = GetCodeFromList(codeList, module);
    auto name = identifier->Name();
    try {
      if (identifier->Builtins()->Contains(name)) {
        if (identifier->Mode() == STOREORLOAD::STORE) {
          throw std::runtime_error("Cannot store global variable");
        }
        if (identifier->Mode() == STOREORLOAD::LOAD) {
          code->LoadGlobal(name);
          return Object::CreatePyNone();
        }
      }
      // LEGB
      if (Object::IsTrue(code->VarNames()->contains(name))) {
        // 如果是varname
        if (identifier->Mode() == STOREORLOAD::STORE) {
          code->StoreFast(name);
        }
        if (identifier->Mode() == STOREORLOAD::LOAD) {
          code->LoadFast(name);
        }
        return Object::CreatePyNone();
      }
      if (Object::IsTrue(moduleCode->Names()->contains(name))) {
        // 如果是module
        if (identifier->Mode() == STOREORLOAD::STORE) {
          throw std::runtime_error("Cannot store global variable");
        }
        if (identifier->Mode() == STOREORLOAD::LOAD) {
          code->LoadGlobal(name);
        }
        return Object::CreatePyNone();
      }
      if (Object::IsTrue(code->Names()->contains(name))) {
        // 如果是names
        if (identifier->Mode() == STOREORLOAD::STORE) {
          code->StoreName(name);
        }
        if (identifier->Mode() == STOREORLOAD::LOAD) {
          code->LoadName(name);
        }
        return Object::CreatePyNone();
      }

    } catch (const std::exception& e) {
      auto name = identifier->Name();
      Function::DebugPrint(name);
      Function::DebugPrint(moduleCode->Names());
      Function::DebugPrint(moduleCode->VarNames());
      Function::DebugPrint(code->Names());
      Function::DebugPrint(code->VarNames());
      throw(e);
    }
  }
  return Object::CreatePyNone();
}

}  // namespace torchlight::Ast