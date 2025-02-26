
#include "Ast/INode.h"
#include "Ast/ClassDef.h"
#include "Ast/FuncDef.h"
#include "Ast/Module.h"

namespace torchlight::Ast {

INode::INode(Object::KlassPtr klass, Ast::INodePtr parent)
  : Object::PyObject(std::move(klass)), parent(std::move(parent)) {}

Ast::INodePtr INode::Parent() const {
  return parent;
}

INodeKlass::INodeKlass() = default;

Object::KlassPtr INodeKlass::Self() {
  static Object::KlassPtr instance = std::make_shared<INodeKlass>();
  return instance;
}

Object::PyObjPtr
INodeKlass::visit(Object::PyObjPtr obj, Object::PyObjPtr codeList) {
  throw std::runtime_error("INodeKlass::visit() not implemented");
}

Object::PyObjPtr INode::visit(Object::PyObjPtr codeList) {
  return std::dynamic_pointer_cast<INodeKlass>(Klass())->visit(
    shared_from_this(), codeList
  );
}

Object::PyObjPtr
INodeKlass::emit(Object::PyObjPtr obj, Object::PyObjPtr codeList) {
  throw std::runtime_error("INodeKlass::emit() not implemented");
}

Object::PyObjPtr INode::emit(Object::PyObjPtr codeList) {
  return std::dynamic_pointer_cast<INodeKlass>(Klass())->emit(
    shared_from_this(), codeList
  );
}

Object::PyCodePtr
GetCodeFromList(Object::PyObjPtr codeList, Ast::INodePtr node) {
  auto IsModule = std::dynamic_pointer_cast<Module>(node);
  auto IsFuncDef = std::dynamic_pointer_cast<FuncDef>(node);
  auto IsClassDef = std::dynamic_pointer_cast<ClassDef>(node);
  if (IsModule != nullptr) {
    return std::dynamic_pointer_cast<Object::PyCode>(
      codeList->getitem(IsModule->CodeIndex())
    );
  }
  if (IsFuncDef != nullptr) {
    return std::dynamic_pointer_cast<Object::PyCode>(
      codeList->getitem(IsFuncDef->CodeIndex())
    );
  }
  if (IsClassDef != nullptr) {
    return std::dynamic_pointer_cast<Object::PyCode>(
      codeList->getitem(IsClassDef->CodeIndex())
    );
  }
  return GetCodeFromList(codeList, node->Parent());
}

}  // namespace torchlight::Ast