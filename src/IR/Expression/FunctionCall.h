#ifndef TENSORSLOW_AST_FUNCTIONCALL_H
#define TENSORSLOW_AST_FUNCTIONCALL_H

#include "Function/BuiltinFunction.h"
#include "IR/INode.h"

namespace tensorslow::IR {

class FunctionCallKlass : public INodeKlass {
 public:
  FunctionCallKlass() = default;

  void Initialize() override {
    if (this->isInitialized) {
      return;
    }
    InitKlass(Object::CreatePyString("ast_functioncall"), Self());
    this->isInitialized = true;
  }

  static Object::KlassPtr Self() {
    static auto instance = std::make_shared<FunctionCallKlass>();
    return instance;
  }

  Object::PyObjPtr
  visit(const Object::PyObjPtr& obj, const Object::PyObjPtr& codeList) override;

  Object::PyObjPtr
  emit(const Object::PyObjPtr& obj, const Object::PyObjPtr& codeList) override;

  Object::PyObjPtr print(const Object::PyObjPtr& obj) override;
};

class FunctionCall : public INode {
 public:
  FunctionCall(INodePtr func, Object::PyListPtr args, INodePtr parent)
    : INode(FunctionCallKlass::Self(), std::move(parent)),
      func(std::move(func)),
      args(std::move(args)) {}

  [[nodiscard]] INodePtr Func() const { return func; }

  [[nodiscard]] Object::PyListPtr Args() const { return args; }

 private:
  INodePtr func;
  Object::PyListPtr args;
};

using FunctionCallPtr = std::shared_ptr<FunctionCall>;

inline INodePtr CreateFunctionCall(
  const INodePtr& func,
  const Object::PyListPtr& args,
  const INodePtr& parent
) {
  return std::make_shared<FunctionCall>(func, args, parent);
}

}  // namespace tensorslow::IR

#endif
