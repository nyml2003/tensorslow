
#include "IR/INode.h"
#include "IR/ClassDef.h"
#include "IR/FuncDef.h"
#include "IR/Module.h"

namespace tensorslow::IR {
Object::PyCodePtr
GetCodeFromList(const Object::PyObjPtr& codeList, const INodePtr& node) {
  if (node->is(ModuleKlass::Self())) {
    return codeList->as<Object::PyList>()
      ->GetItem(node->as<Module>()->CodeIndex())
      ->as<Object::PyCode>();
  }
  if (node->is(FuncDefKlass::Self())) {
    return codeList->as<Object::PyList>()
      ->GetItem(node->as<FuncDef>()->CodeIndex())
      ->as<Object::PyCode>();
  }
  if (node->is(ClassDefKlass::Self())) {
    return codeList->as<Object::PyList>()
      ->GetItem(node->as<ClassDef>()->CodeIndex())
      ->as<Object::PyCode>();
  }
  return GetCodeFromList(codeList, node->Parent());
}
void PrintNode(const Object::PyObjPtr& node, const Object::PyStrPtr& text) {
  Function::Identity(Object::CreatePyList({node}))
    ->str()
    ->as<Object::PyString>()
    ->Print();
  Object::CreatePyString("[")->Print();
  text->Print();
  Object::CreatePyString("]\n")->Print();
}

void PrintEdge(
  const Object::PyObjPtr& parent,
  const Object::PyObjPtr& child,
  const Object::PyStrPtr& text
) {
  Function::Identity(Object::CreatePyList({parent}))
    ->str()
    ->as<Object::PyString>()
    ->Print();
  if (text == nullptr) {
    Object::CreatePyString("--->")->Print();
  } else {
    Object::StringConcat(Object::CreatePyList(
                           {Object::CreatePyString("--"), text,
                            Object::CreatePyString("-->")}
                         ))
      ->as<Object::PyString>()
      ->Print();
  }
  Function::Identity(Object::CreatePyList({child}))
    ->str()
    ->as<Object::PyString>()
    ->Print();
  Object::CreatePyString("")->PrintLine();
}

}  // namespace tensorslow::IR