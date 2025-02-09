#include "Ast/Atom.h"
#include "Ast/INode.h"
#include "Object/PyDictionary.h"
#include "Object/PyNone.h"
#include "Object/PyObject.h"
#include "Object/PyString.h"
#include "Object/PyType.h"

namespace torchlight::Ast {

Atom::Atom(Object::PyObjPtr obj, Ast::INodePtr parent)
  : INode(AtomKlass::Self(), std::move(parent)), obj(std::move(obj)) {}

Object::PyObjPtr Atom::Obj() const {
  return obj;
}

AtomKlass::AtomKlass() = default;

void AtomKlass::Initialize() {
  SetName(Object::CreatePyString("Atom"));
  SetType(CreatePyType(Self()));
  SetAttributes(Object::CreatePyDict());
  Klass::Initialize();
}

Ast::INodePtr CreateAtom(Object::PyObjPtr obj, Ast::INodePtr parent) {
  return std::make_shared<Atom>(std::move(obj), std::move(parent));
}

Object::PyObjPtr
AtomKlass::emit(Object::PyObjPtr obj, Object::PyObjPtr codeList) {
  auto atom = std::dynamic_pointer_cast<Atom>(obj);
  auto code = GetCodeFromList(codeList, atom);
  auto object = atom->Obj();
  auto isNode = std::dynamic_pointer_cast<INode>(object);
  if (isNode == nullptr) {
    code->LoadConst(object);
    return Object::CreatePyNone();
  }
  throw std::runtime_error("AtomKlass::emit(): unsupported object type");
}

Object::PyObjPtr
AtomKlass::visit(Object::PyObjPtr obj, Object::PyObjPtr codeList) {
  auto atom = std::dynamic_pointer_cast<Atom>(obj);
  auto code = GetCodeFromList(codeList, atom);
  auto object = atom->Obj();
  auto isNode = std::dynamic_pointer_cast<INode>(object);
  if (isNode == nullptr) {
    code->RegisterConst(object);
    return Object::CreatePyNone();
  }
  throw std::runtime_error("AtomKlass::visit(): unsupported object type");
}

Object::KlassPtr AtomKlass::Self() {
  static Object::KlassPtr instance = std::make_shared<AtomKlass>();
  return instance;
}

}  // namespace torchlight::Ast