#ifndef TORCHLIGHT_AST_MODULE_H
#define TORCHLIGHT_AST_MODULE_H

#include "Ast/INode.h"
#include "Object/ObjectHelper.h"

namespace torchlight::Ast {

class ModuleKlass : public INodeKlass {
 public:
  explicit ModuleKlass() = default;

  static Object::KlassPtr Self() {
    static auto instance = std::make_shared<ModuleKlass>();
    Object::LoadClass(
      Object::CreatePyString("Module")->as<Object::PyString>(), instance
    );
    Object::ConfigureBasicAttributes(instance);
    return instance;
  }
  Object::PyObjPtr
  visit(const Object::PyObjPtr& obj, const Object::PyObjPtr& codeList) override;

  Object::PyObjPtr
  emit(const Object::PyObjPtr& obj, const Object::PyObjPtr& codeList) override;
};

class Module : public INode {
 public:
  explicit Module(const Object::PyObjPtr& body, const Object::PyObjPtr& name)
    : INode(ModuleKlass::Self(), nullptr),
      body(body->as<Object::PyList>()),
      name(name->as<Object::PyString>()) {}

  Object::PyListPtr Body() const { return body; }

  Object::PyStrPtr Name() const { return name; }

  [[nodiscard]] Object::PyObjPtr CodeIndex() const { return codeIndex; }

  void SetCodeIndex(const Object::PyObjPtr& _codeIndex) {
    codeIndex = _codeIndex;
  }

  void SetBody(const Object::PyObjPtr& _body) {
    body = _body->as<Object::PyList>();
  }

 private:
  Object::PyListPtr body;
  Object::PyStrPtr name;
  Object::PyObjPtr
    codeIndex;  // 保存当前FuncDef对应的PyCode对象在codeList中的索引
};

using ModulePtr = std::shared_ptr<Module>;

inline INodePtr
CreateModule(const Object::PyObjPtr& body, const Object::PyObjPtr& name) {
  return std::make_shared<Module>(body, name);
}

}  // namespace torchlight::Ast

#endif