#include "Ast/Expression/List.h"
#include "Object/Core/PyNone.h"
#include "Object/Iterator/IteratorHelper.h"
namespace torchlight::Ast {
Object::PyObjPtr
ListKlass::emit(const Object::PyObjPtr& obj, const Object::PyObjPtr& codeList) {
  auto list = obj->as<List>();
  auto elements = list->Elements();
  Object::ForEach(
    elements,
    [&codeList](const Object::PyObjPtr& element, Index, const Object::PyObjPtr&) {
      element->as<INode>()->emit(codeList);
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
  auto list = obj->as<List>();
  auto elements = list->Elements();
  Object::ForEach(
    elements,
    [&codeList](const Object::PyObjPtr& element, Index, const Object::PyObjPtr&) {
      element->as<INode>()->visit(codeList);
    }
  );
  return Object::CreatePyNone();
}

}  // namespace torchlight::Ast