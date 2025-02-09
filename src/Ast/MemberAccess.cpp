#include "Ast/MemberAccess.h"

#include "ByteCode/PyCode.h"
#include "Object/PyDictionary.h"
#include "Object/PyNone.h"
#include "Object/PyType.h"

namespace torchlight::Ast {

MemberAccess::MemberAccess(
  Ast::INodePtr obj,
  Object::PyObjPtr member,
  Ast::INodePtr parent
)
  : INode(MemberAccessKlass::Self(), std::move(parent)),
    obj(std::move(obj)),
    member(std::dynamic_pointer_cast<Object::PyString>(member)) {}

Ast::INodePtr MemberAccess::Obj() const {
  return obj;
}

Object::PyStrPtr MemberAccess::Member() const {
  return member;
}

MemberAccessKlass::MemberAccessKlass() = default;

void MemberAccessKlass::Initialize() {
  SetName(Object::CreatePyString("MemberAccess"));
  SetType(CreatePyType(Self()));
  SetAttributes(Object::CreatePyDict());
  Klass::Initialize();
}

Object::PyObjPtr
MemberAccessKlass::visit(Object::PyObjPtr obj, Object::PyObjPtr codeList) {
  auto memberAccess = std::dynamic_pointer_cast<MemberAccess>(obj);
  auto object = memberAccess->Obj();
  object->visit(codeList);
  auto member = memberAccess->Member();
  auto code = GetCodeFromList(codeList, memberAccess);
  code->RegisterName(member);
  return Object::CreatePyNone();
}

Object::PyObjPtr
MemberAccessKlass::emit(Object::PyObjPtr obj, Object::PyObjPtr codeList) {
  auto memberAccess = std::dynamic_pointer_cast<MemberAccess>(obj);
  auto object = memberAccess->Obj();
  object->emit(codeList);
  auto member = memberAccess->Member();
  auto code = GetCodeFromList(codeList, memberAccess);
  code->LoadAttr(member);
  return Object::CreatePyNone();
}

Object::KlassPtr MemberAccessKlass::Self() {
  static Object::KlassPtr instance = std::make_shared<MemberAccessKlass>();
  return instance;
}

Ast::INodePtr CreateMemberAccess(
  Ast::INodePtr obj,
  Object::PyObjPtr member,
  Ast::INodePtr parent
) {
  return std::make_shared<MemberAccess>(obj, member, parent);
}

}  // namespace torchlight::Ast
