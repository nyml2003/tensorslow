
#include "Ast/INode.h"
#include "Ast/ClassDef.h"
#include "Ast/FuncDef.h"
#include "Ast/Module.h"

namespace torchlight::Ast {
Object::PyCodePtr GetCodeFromList(Object::PyObjPtr codeList, INodePtr node) {
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