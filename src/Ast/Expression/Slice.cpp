#include "Ast/Expression/Slice.h"
#include "Object/Core/PyNone.h"
#include "Object/Iterator/IteratorHelper.h"
namespace torchlight::Ast {
Object::PyObjPtr SliceKlass::emit(
  const Object::PyObjPtr& obj,
  const Object::PyObjPtr& codeList
) {
  auto list = obj->as<Ast::Slice>();
  auto elements = list->Elements();
  Object::ForEach(
    elements,
    [&codeList](const Object::PyObjPtr& element, Index, const Object::PyObjPtr&) {
      element->as<INode>()->emit(codeList);
    }
  );
  auto code = GetCodeFromList(codeList, list);
  code->BuildSlice();
  return Object::CreatePyNone();
}

Object::PyObjPtr SliceKlass::visit(
  const Object::PyObjPtr& obj,
  const Object::PyObjPtr& codeList
) {
  auto list = obj->as<Ast::Slice>();
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