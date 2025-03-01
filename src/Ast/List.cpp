#include "Ast/List.h"
#include "Ast/INode.h"
#include "Object/ObjectHelper.h"
#include "Object/PyNone.h"

namespace torchlight::Ast {
Object::PyObjPtr
ListKlass::emit(const Object::PyObjPtr& obj, const Object::PyObjPtr& codeList) {
  auto list = std::dynamic_pointer_cast<List>(obj);
  auto elements = list->Elements();
  Object::ForEach(
    std::dynamic_pointer_cast<Object::PyList>(elements),
    [&codeList](const Object::PyObjPtr& element, Index, const Object::PyObjPtr&) {
      auto elementNode = std::dynamic_pointer_cast<INode>(element);
      elementNode->emit(codeList);
    }
  );
  auto code = GetCodeFromList(codeList, list);
  code->BuildList(elements->Length());
  return Object::CreatePyNone();
}

Object::PyObjPtr ListKlass::visit(
  const Object::PyObjPtr& obj,
  const Object::PyObjPtr& codeList
) {
  auto list = std::dynamic_pointer_cast<List>(obj);
  auto elements = list->Elements();
  Object::ForEach(
    std::dynamic_pointer_cast<Object::PyList>(elements),
    [&codeList](const Object::PyObjPtr& element, Index, const Object::PyObjPtr&) {
      auto elementNode = std::dynamic_pointer_cast<INode>(element);
      elementNode->visit(codeList);
    }
  );
  return Object::CreatePyNone();
}

}  // namespace torchlight::Ast