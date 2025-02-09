#ifndef TORCHLIGHT_AST_FUNCDEF_H
#define TORCHLIGHT_AST_FUNCDEF_H

#include "Ast/INode.h"

namespace torchlight::Ast {

class FuncDef : public INode {
 public:
  explicit FuncDef(
    Object::PyObjPtr _name,
    Object::PyObjPtr _parameters,
    Object::PyObjPtr _body,
    Ast::INodePtr parent
  );

  [[nodiscard]] Object::PyStrPtr Name() const;

  [[nodiscard]] Object::PyListPtr Parameters() const;

  [[nodiscard]] Object::PyListPtr Body() const;

  [[nodiscard]] Object::PyObjPtr Parents() const;

  [[nodiscard]] Object::PyObjPtr CodeIndex() const;

  void SetParents(Object::PyObjPtr _parents);

  void SetCodeIndex(Object::PyObjPtr _codeIndex);

  void SetBody(Object::PyObjPtr _body); 

 private:
  Object::PyStrPtr name;
  Object::PyListPtr body;
  Object::PyListPtr parameters;
  Object::PyObjPtr
    parents;  // 保存整个调用链上的FuncDef或者Module所对应的PyCode对象
  Object::PyObjPtr
    codeIndex;  // 保存当前FuncDef对应的PyCode对象在codeList中的索引
};

Ast::INodePtr CreateFuncDef(
  Object::PyObjPtr _name,
  Object::PyObjPtr _parameters,
  Object::PyObjPtr _body,
  Ast::INodePtr parent
);
class FuncDefKlass : public INodeKlass {
 public:
  explicit FuncDefKlass();

  static Object::KlassPtr Self();

  Object::PyObjPtr visit(Object::PyObjPtr obj, Object::PyObjPtr codeList)
    override;

  Object::PyObjPtr emit(Object::PyObjPtr obj, Object::PyObjPtr codeList)
    override;

  void Initialize() override;
};

}  // namespace torchlight::Ast

#endif