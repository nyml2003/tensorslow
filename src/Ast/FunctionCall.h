#ifndef TORCHLIGHT_AST_FUNCTIONCALL_H
#define TORCHLIGHT_AST_FUNCTIONCALL_H

#include "Ast/INode.h"

namespace torchlight::Ast {

class FunctionCall : public INode {
 public:
  FunctionCall(
    Object::PyObjPtr _func,
    Object::PyObjPtr _args,
    Ast::INodePtr parent
  );

  [[nodiscard]] Ast::INodePtr Func() const;

  [[nodiscard]] Object::PyListPtr Args() const;

 private:
  Ast::INodePtr func;
  Object::PyListPtr args;
};

class FunctionCallKlass : public INodeKlass {
 public:
  FunctionCallKlass();

  static Object::KlassPtr Self();

  Object::PyObjPtr visit(Object::PyObjPtr obj, Object::PyObjPtr codeList)
    override;

  Object::PyObjPtr emit(Object::PyObjPtr obj, Object::PyObjPtr codeList)
    override;

  void Initialize() override;
};

using FunctionCallPtr = std::shared_ptr<FunctionCall>;

Ast::INodePtr CreateFunctionCall(
  Object::PyObjPtr func,
  Object::PyObjPtr args,
  Ast::INodePtr parent
);

}  // namespace torchlight::Ast

#endif
