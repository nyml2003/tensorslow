#include "Ast/Expression/Map.h"
#include "Object/Core/PyNone.h"
#include "Object/Iterator/IteratorHelper.h"
namespace torchlight::Ast {
Object::PyObjPtr
MapKlass::emit(const Object::PyObjPtr& obj, const Object::PyObjPtr& codeList) {
  auto map = obj->as<Ast::Map>();
  auto keys = map->Keys();
  auto values = map->Values();
  Index size = keys->Length();
  auto code = GetCodeFromList(codeList, map);
  for (Index i = size - 1; ~i; --i) {
    keys->GetItem(i)->as<INode>()->emit(codeList);
    values->GetItem(i)->as<INode>()->emit(codeList);
  }
  code->BuildMap(size);
  return Object::CreatePyNone();
}

Object::PyObjPtr
MapKlass::visit(const Object::PyObjPtr& obj, const Object::PyObjPtr& codeList) {
  auto map = obj->as<Ast::Map>();
  auto keys = map->Keys();
  auto values = map->Values();
  Object::ForEach(
    keys,
    [&codeList](const Object::PyObjPtr& element, Index, const Object::PyObjPtr&) {
      element->as<INode>()->visit(codeList);
    }
  );
  Object::ForEach(
    values,
    [&codeList](const Object::PyObjPtr& element, Index, const Object::PyObjPtr&) {
      element->as<INode>()->visit(codeList);
    }
  );
  return Object::CreatePyNone();
}

}  // namespace torchlight::Ast