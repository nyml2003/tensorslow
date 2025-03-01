#ifndef TORCHLIGHT_AST_FUNCTIONCALL_H
#define TORCHLIGHT_AST_FUNCTIONCALL_H

#include "Ast/INode.h"

namespace torchlight::Ast {

class FunctionCallKlass : public INodeKlass {
 public:
  FunctionCallKlass() = default;

  static Object::KlassPtr Self() {
    static auto instance = std::make_shared<FunctionCallKlass>();
    Object::LoadClass(
      Object::CreatePyString("FunctionCall")->as<Object::PyString>(), instance
    );
    Object::ConfigureBasicAttributes(instance);
    return instance;
  }

  Object::PyObjPtr
  visit(const Object::PyObjPtr& obj, const Object::PyObjPtr& codeList) override;

  Object::PyObjPtr
  emit(const Object::PyObjPtr& obj, const Object::PyObjPtr& codeList) override;
};

class FunctionCall : public INode {
 public:
  FunctionCall(
    const Object::PyObjPtr& _func,
    const Object::PyObjPtr& _args,
    INodePtr parent
  )
    : INode(FunctionCallKlass::Self(), std::move(parent)),
      func(_func->as<INode>()),
      args(_args->as<Object::PyList>()) {}

  [[nodiscard]] INodePtr Func() const { return func; }

  [[nodiscard]] Object::PyListPtr Args() const { return args; }

 private:
  INodePtr func;
  Object::PyListPtr args;
};

using FunctionCallPtr = std::shared_ptr<FunctionCall>;

inline INodePtr CreateFunctionCall(
  const Object::PyObjPtr& func,
  const Object::PyObjPtr& args,
  INodePtr parent
) {
  return std::make_shared<FunctionCall>(func, args, std::move(parent));
}

}  // namespace torchlight::Ast

#endif
