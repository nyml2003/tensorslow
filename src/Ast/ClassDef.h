#ifndef TORCHLIGHT_AST_CLASSDEF_H
#define TORCHLIGHT_AST_CLASSDEF_H

#include "Ast/INode.h"

namespace torchlight::Ast {

class ClassDef : public INode {
 public:
  explicit ClassDef(
    const Object::PyObjPtr& _name,
    const Object::PyObjPtr& _bases,
    const Ast::INodePtr& parent
  );

  [[nodiscard]] Object::PyStrPtr Name() const;

  [[nodiscard]] Object::PyListPtr Bases() const;

  [[nodiscard]] Object::PyListPtr Body() const;

  [[nodiscard]] Object::PyObjPtr Parents() const;

  [[nodiscard]] Object::PyObjPtr CodeIndex() const;

  void SetCodeIndex(const Object::PyObjPtr& _codeIndex);

  void SetBody(const Object::PyObjPtr& _body);

 private:
  Object::PyStrPtr name;    // 类名
  Object::PyListPtr body;   // 类的主体
  Object::PyListPtr bases;  // 保存当前ClassDef的基类
  Object::PyObjPtr
    parents;  // 保存整个调用链上的ClassDef,Module和FuncDef所对应的PyCode对象
  Object::PyObjPtr
    codeIndex;  // 保存当前ClassDef对应的PyCode对象在codeList中的索引
};

Ast::INodePtr CreateClassDef(
  const Object::PyObjPtr& _name,
  const Object::PyObjPtr& _bases,
  const Ast::INodePtr& parent
);

class ClassDefKlass : public INodeKlass {
 public:
  explicit ClassDefKlass();

  static Object::KlassPtr Self();

  Object::PyObjPtr visit(Object::PyObjPtr obj, Object::PyObjPtr codeList)
    override;

  Object::PyObjPtr emit(Object::PyObjPtr obj, Object::PyObjPtr codeList)
    override;

  void Initialize() override;
};

}  // namespace torchlight::Ast

#endif