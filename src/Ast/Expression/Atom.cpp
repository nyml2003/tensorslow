#include "Ast/Expression/Atom.h"
#include "Object/PyNone.h"
#include "Object/PyObject.h"

namespace torchlight::Ast {

Object::PyObjPtr
AtomKlass::emit(const Object::PyObjPtr& obj, const Object::PyObjPtr& codeList) {
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

Object::PyObjPtr AtomKlass::visit(
  const Object::PyObjPtr& obj,
  const Object::PyObjPtr& codeList
) {
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

}  // namespace torchlight::Ast