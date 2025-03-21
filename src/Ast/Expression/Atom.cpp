#include "Ast/Expression/Atom.h"
#include "Object/PyNone.h"
#include "Object/PyObject.h"

namespace torchlight::Ast {

Object::PyObjPtr
AtomKlass::emit(const Object::PyObjPtr& obj, const Object::PyObjPtr& codeList) {
  auto atom = obj->as<Atom>();
  auto code = GetCodeFromList(codeList, atom);
  auto object = atom->Obj();
  if (!object->is<INode>()) {
    code->LoadConst(object);
    return Object::CreatePyNone();
  }
  throw std::runtime_error("AtomKlass::emit(): unsupported object type");
}

Object::PyObjPtr AtomKlass::visit(
  const Object::PyObjPtr& obj,
  const Object::PyObjPtr& codeList
) {
  auto atom = obj->as<Atom>();
  auto code = GetCodeFromList(codeList, atom);
  auto object = atom->Obj();
  if (!object->is<INode>()) {
    code->RegisterConst(object);
    return Object::CreatePyNone();
  }
  throw std::runtime_error("AtomKlass::visit(): unsupported object type");
}

}  // namespace torchlight::Ast