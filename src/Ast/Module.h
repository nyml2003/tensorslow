#ifndef TORCHLIGHT_AST_MODULE_H
#define TORCHLIGHT_AST_MODULE_H

#include "Ast/INode.h"

namespace torchlight::Ast {

class Module : public INode {
 public:
  explicit Module(Object::PyObjPtr body, Object::PyObjPtr name);

  Object::PyListPtr Body() const;

  Object::PyStrPtr Name() const;

  [[nodiscard]] Object::PyObjPtr CodeIndex() const;

  void SetCodeIndex(Object::PyObjPtr _codeIndex);

  void SetBody(Object::PyObjPtr _body);

 private:
  Object::PyListPtr body;
  Object::PyStrPtr name;
  Object::PyObjPtr
    codeIndex;  // 保存当前FuncDef对应的PyCode对象在codeList中的索引
};

using ModulePtr = std::shared_ptr<Module>;

Ast::INodePtr CreateModule(Object::PyObjPtr body, Object::PyObjPtr name);

class ModuleKlass : public INodeKlass {
 public:
  explicit ModuleKlass();

  static Object::KlassPtr Self();

  Object::PyObjPtr visit(Object::PyObjPtr obj, Object::PyObjPtr codeList)
    override;

  Object::PyObjPtr emit(Object::PyObjPtr obj, Object::PyObjPtr codeList)
    override;

  void Initialize() override;
};

}  // namespace torchlight::Ast

#endif