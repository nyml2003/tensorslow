#ifndef TORCHLIGHT_AST_FUNCDEF_H
#define TORCHLIGHT_AST_FUNCDEF_H

#include <utility>

#include "Ast/INode.h"

namespace torchlight::Ast {

class FuncDefKlass : public INodeKlass {
 public:
  explicit FuncDefKlass() = default;

  static Object::KlassPtr Self() {
    static auto instance = std::make_shared<FuncDefKlass>();
    LoadClass(
      Object::CreatePyString("FuncDef")->as<Object::PyString>(), instance
    );
    ConfigureBasicAttributes(instance);
    return instance;
  }

  Object::PyObjPtr
  visit(const Object::PyObjPtr& obj, const Object::PyObjPtr& codeList) override;

  Object::PyObjPtr
  emit(const Object::PyObjPtr& obj, const Object::PyObjPtr& codeList) override;
};

class FuncDef : public INode {
 public:
  explicit FuncDef(
    const Object::PyObjPtr& _name,
    const Object::PyObjPtr& _parameters,
    const Object::PyObjPtr& _body,
    INodePtr parent
  )
    : INode(FuncDefKlass::Self(), std::move(parent)),
      name(_name->as<Object::PyString>()),
      parameters(_parameters->as<Object::PyList>()),
      body(_body->as<Object::PyList>()) {}

  [[nodiscard]] Object::PyStrPtr Name() const { return name; }

  [[nodiscard]] Object::PyListPtr Parameters() const { return parameters; }

  [[nodiscard]] Object::PyListPtr Body() const { return body; }

  [[nodiscard]] Object::PyObjPtr Parents() const { return parents; }

  [[nodiscard]] Object::PyObjPtr CodeIndex() const { return codeIndex; }

  void SetParents(const Object::PyObjPtr& _parents) { parents = _parents; }

  void SetCodeIndex(const Object::PyObjPtr& _codeIndex) {
    codeIndex = _codeIndex;
  }

  void SetBody(const Object::PyObjPtr& _body) {
    body = _body->as<Object::PyList>();
  }

 private:
  Object::PyStrPtr name;
  Object::PyListPtr body;
  Object::PyListPtr parameters;
  Object::PyObjPtr
    parents;  // 保存整个调用链上的FuncDef或者Module所对应的PyCode对象
  Object::PyObjPtr
    codeIndex;  // 保存当前FuncDef对应的PyCode对象在codeList中的索引
};

inline INodePtr CreateFuncDef(
  Object::PyObjPtr _name,
  Object::PyObjPtr _parameters,
  Object::PyObjPtr _body,
  INodePtr parent
) {
  return std::make_shared<FuncDef>(
    std::move(_name), std::move(_parameters), std::move(_body),
    std::move(parent)
  );
}
}  // namespace torchlight::Ast

#endif