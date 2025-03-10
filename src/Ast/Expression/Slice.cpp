#include "Ast/Expression/Slice.h"
#include "Object/PyNone.h"

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
      auto elementNode = std::dynamic_pointer_cast<INode>(element);
      elementNode->emit(codeList);
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
    std::dynamic_pointer_cast<Object::PyList>(elements),
    [&codeList](const Object::PyObjPtr& element, Index, const Object::PyObjPtr&) {
      auto elementNode = std::dynamic_pointer_cast<INode>(element);
      elementNode->visit(codeList);
    }
  );
  return Object::CreatePyNone();
}

}  // namespace torchlight::Ast