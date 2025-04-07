
#include "Ast/INode.h"
#include "Ast/ClassDef.h"
#include "Ast/FuncDef.h"
#include "Ast/Module.h"

namespace torchlight::Ast {
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

}  // namespace torchlight::Ast