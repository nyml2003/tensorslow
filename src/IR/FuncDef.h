#ifndef TORCHLIGHT_AST_FUNCDEF_H
#define TORCHLIGHT_AST_FUNCDEF_H

#include "Function/BuiltinFunction.h"
#include "IR/INode.h"

namespace torchlight::IR {

class FuncDefKlass : public INodeKlass {
 public:
  explicit FuncDefKlass() = default;

  static Object::KlassPtr Self() {
    static auto instance = std::make_shared<FuncDefKlass>();
    return instance;
  }

  void Initialize() override {
    if (this->isInitialized) {
      return;
    }
    InitKlass(Object::CreatePyString("ast_funcdef"), Self());
    this->isInitialized = true;
  }

  Object::PyObjPtr
  visit(const Object::PyObjPtr& obj, const Object::PyObjPtr& codeList) override;

  Object::PyObjPtr
  emit(const Object::PyObjPtr& obj, const Object::PyObjPtr& codeList) override;
};

class FuncDef : public INode {
 public:
  explicit FuncDef(
    Object::PyStrPtr name,
    Object::PyListPtr parameters,
    Object::PyListPtr body,
    const INodePtr& parent
  );

  [[nodiscard]] Object::PyStrPtr Name() const { return name; }

  [[nodiscard]] Object::PyListPtr Parameters() const { return parameters; }

  [[nodiscard]] Object::PyListPtr Body() const { return body; }

  [[nodiscard]] Object::PyListPtr Parents() const { return parents; }

  [[nodiscard]] Index CodeIndex() const { return codeIndex; }

  void SetParents(const Object::PyListPtr& _parents) { parents = _parents; }

  void SetCodeIndex(const Index codeIndex) { this->codeIndex = codeIndex; }

  void SetBody(const Object::PyListPtr& body) { this->body = body; }

 private:
  Object::PyStrPtr name;
  Object::PyListPtr body;
  Object::PyListPtr parameters;
  Object::PyListPtr
    parents;  // 保存整个调用链上的FuncDef或者Module所对应的PyCode对象
  Index codeIndex;  // 保存当前FuncDef对应的PyCode对象在codeList中的索引
};

inline INodePtr CreateFuncDef(
  const Object::PyStrPtr& name,
  const Object::PyListPtr& parameters,
  const Object::PyListPtr& body,
  const INodePtr& parent
) {
  return std::make_shared<FuncDef>(name, parameters, body, parent);
}
}  // namespace torchlight::IR

#endif