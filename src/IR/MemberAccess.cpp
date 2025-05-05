#include "IR/MemberAccess.h"
#include "Object/Core/PyNone.h"

namespace tensorslow::IR {

Object::PyObjPtr MemberAccessKlass::visit(
  const Object::PyObjPtr& obj,
  const Object::PyObjPtr& codeList
) {
  auto memberAccess = obj->as<MemberAccess>();
  auto object = memberAccess->Obj();
  object->visit(codeList);
  auto member = memberAccess->Member();
  auto code = GetCodeFromList(codeList, memberAccess);
  code->RegisterName(member);
  return Object::CreatePyNone();
}

Object::PyObjPtr MemberAccessKlass::emit(
  const Object::PyObjPtr& obj,
  const Object::PyObjPtr& codeList
) {
  auto memberAccess = obj->as<MemberAccess>();
  auto object = memberAccess->Obj();
  object->emit(codeList);
  auto member = memberAccess->Member();
  auto code = GetCodeFromList(codeList, memberAccess);
  if (memberAccess->Mode() == STOREORLOAD::STORE) {
    code->StoreAttr(member);
  }
  if (memberAccess->Mode() == STOREORLOAD::LOAD) {
    code->LoadAttr(member);
  }
  return Object::CreatePyNone();
}

Object::PyObjPtr MemberAccessKlass::print(const Object::PyObjPtr& obj) {
  auto memberAccess = obj->as<MemberAccess>();
  auto object = memberAccess->Obj();
  auto member = memberAccess->Member();
  PrintNode(memberAccess, Object::CreatePyString("MemberAccess"));
  object->print();
  PrintEdge(memberAccess, object, Object::CreatePyString("object"));
  PrintEdge(memberAccess, member, Object::CreatePyString("member"));
  return Object::CreatePyNone();
}

}  // namespace tensorslow::IR
