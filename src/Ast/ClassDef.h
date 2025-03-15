#ifndef TORCHLIGHT_AST_CLASSDEF_H
#define TORCHLIGHT_AST_CLASSDEF_H

#include "Ast/INode.h"
#include "Object/ObjectHelper.h"

namespace torchlight::Ast {

class ClassDefKlass : public INodeKlass {
 public:
  static Object::KlassPtr Self() {
    static auto instance = std::make_shared<ClassDefKlass>();
    LoadClass(
      Object::CreatePyString("ClassDef")->as<Object::PyString>(), instance
    );
    ConfigureBasicAttributes(instance);
    return instance;
  }

  Object::PyObjPtr
  visit(const Object::PyObjPtr& obj, const Object::PyObjPtr& codeList) override;

  Object::PyObjPtr
  emit(const Object::PyObjPtr& obj, const Object::PyObjPtr& codeList) override;
};

class ClassDef : public INode {
 public:
  explicit ClassDef(
    Object::PyStrPtr name,
    INodePtr bases,
    const INodePtr& parent
  );

  [[nodiscard]] Object::PyStrPtr Name() const { return name; }

  [[nodiscard]] INodePtr Bases() const { return bases; }

  [[nodiscard]] Object::PyListPtr Body() const { return body; }

  [[nodiscard]] Object::PyListPtr Parents() const { return parents; }

  [[nodiscard]] Object::PyObjPtr CodeIndex() const { return codeIndex; }

  void SetCodeIndex(const Object::PyObjPtr& _codeIndex) {
    codeIndex = _codeIndex;
  }

  void SetBody(const Object::PyObjPtr& _body) {
    body = _body->as<Object::PyList>();
  }

 private:
  Object::PyStrPtr name;   // 类名
  Object::PyListPtr body;  // 类的主体
  INodePtr bases;  // 保存当前ClassDef的基类, 是一个Identifier对象的列表
  Object::PyListPtr
    parents;  // 保存整个调用链上的ClassDef,Module和FuncDef所对应的PyCode对象
  Object::PyObjPtr
    codeIndex;  // 保存当前ClassDef对应的PyCode对象在codeList中的索引
};

inline INodePtr CreateClassDef(
  const Object::PyStrPtr& name,
  const INodePtr& bases,
  const INodePtr& parent
) {
  return std::make_shared<ClassDef>(name, bases, parent);
}

}  // namespace torchlight::Ast

#endif