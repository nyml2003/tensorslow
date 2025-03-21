#ifndef TORCHLIGHT_AST_MODULE_H
#define TORCHLIGHT_AST_MODULE_H

#include "Ast/INode.h"
#include "Function/ObjectHelper.h"

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
  explicit Module(Object::PyListPtr body, Object::PyStrPtr name)
    : INode(ModuleKlass::Self(), nullptr),
      body(std::move(body)),
      name(std::move(name)) {}

  Object::PyListPtr Body() const { return body; }

  Object::PyStrPtr Name() const { return name; }

  [[nodiscard]] Index CodeIndex() const { return codeIndex; }

  void SetCodeIndex(const Index codeIndex) { this->codeIndex = codeIndex; }

  void SetBody(const Object::PyListPtr& body) { this->body = body; }

 private:
  Object::PyListPtr body;
  Object::PyStrPtr name;
  Index codeIndex{};  // 保存当前FuncDef对应的PyCode对象在codeList中的索引
};

using ModulePtr = std::shared_ptr<Module>;

inline INodePtr
CreateModule(const Object::PyListPtr& body, const Object::PyStrPtr& name) {
  return std::make_shared<Module>(body, name);
}

}  // namespace torchlight::Ast

#endif