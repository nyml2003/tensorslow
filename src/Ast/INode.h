#ifndef TORCHLIGHT_AST_AST_NODE_BASE_H
#define TORCHLIGHT_AST_AST_NODE_BASE_H

#include "ByteCode/PyCode.h"

#include "Object/Klass.h"
#include "Object/PyObject.h"
namespace torchlight::Ast {

class INodeKlass : public Object::Klass {
 public:
  explicit INodeKlass();

  static Object::KlassPtr Self();

  virtual Object::PyObjPtr
  visit(Object::PyObjPtr obj, Object::PyObjPtr codeList);

  virtual Object::PyObjPtr
  emit(Object::PyObjPtr obj, Object::PyObjPtr codeList);
};

class INode;

using INodePtr = std::shared_ptr<INode>;

class INode : public Object::PyObject {
 public:
  explicit INode(Object::KlassPtr klass, Ast::INodePtr parent);

  [[nodiscard]] Ast::INodePtr Parent() const;

  /**
   * @brief
   * 遍历AST树，在当前INode节点所属的PyCode对象中注册常量表(consts)，变量表(names)
   */
  virtual Object::PyObjPtr visit(Object::PyObjPtr codeList);

  /**
   * @brief
   * 遍历AST树，在当前INode节点所属的PyCode对象中生成字节码
   */
  virtual Object::PyObjPtr emit(Object::PyObjPtr codeList);

 private:
  Ast::INodePtr parent;  // 保存父结点在codeList中的索引
};

Object::PyCodePtr
GetCodeFromList(Object::PyObjPtr codeList, Ast::INodePtr node);

}  // namespace torchlight::Ast

#endif