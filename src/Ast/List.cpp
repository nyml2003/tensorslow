#include "Ast/List.h"
#include "Ast/INode.h"
#include "Collections/Iterator.h"
#include "Object/ObjectHelper.h"
#include "Object/PyDictionary.h"
#include "Object/PyNone.h"
#include "Object/PyString.h"
#include "Object/PyType.h"

namespace torchlight::Ast {

List::List(Object::PyObjPtr elements, Ast::INodePtr parent)
  : INode(ListKlass::Self(), std::move(parent)) {
  this->elements = std::dynamic_pointer_cast<Object::PyList>(elements);
}

Object::PyListPtr List::Elements() const {
  return elements;
}

ListKlass::ListKlass() = default;

void ListKlass::Initialize() {
  SetName(Object::CreatePyString("List"));
  SetType(CreatePyType(Self()));
  SetAttributes(Object::CreatePyDict());
  Klass::Initialize();
}

Ast::INodePtr CreateList(Object::PyObjPtr elements, Ast::INodePtr parent) {
  return std::make_shared<List>(std::move(elements), std::move(parent));
}

Object::PyObjPtr
ListKlass::emit(Object::PyObjPtr obj, Object::PyObjPtr codeList) {
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

Object::PyObjPtr
ListKlass::visit(Object::PyObjPtr obj, Object::PyObjPtr codeList) {
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

Object::KlassPtr ListKlass::Self() {
  static Object::KlassPtr instance = std::make_shared<ListKlass>();
  return instance;
}

}  // namespace torchlight::Ast