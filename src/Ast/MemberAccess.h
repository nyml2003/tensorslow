#ifndef TORCHLIGHT_AST_MEMBERACCESS_H
#define TORCHLIGHT_AST_MEMBERACCESS_H

#include "Ast/INode.h"

namespace torchlight::Ast {

class MemberAccessKlass : public INodeKlass {
 public:
  MemberAccessKlass() = default;

  static Object::KlassPtr Self() {
    static auto instance = std::make_shared<MemberAccessKlass>();
    Object::LoadClass(
      Object::CreatePyString("MemberAccess")->as<Object::PyString>(), instance
    );
    Object::ConfigureBasicAttributes(instance);
    return instance;
  }

  Object::PyObjPtr
  visit(const Object::PyObjPtr& obj, const Object::PyObjPtr& codeList) override;

  Object::PyObjPtr
  emit(const Object::PyObjPtr& obj, const Object::PyObjPtr& codeList) override;
};

class MemberAccess : public INode {
 public:
  MemberAccess(
    INodePtr obj,
    const Object::PyObjPtr& member,
    const INodePtr& parent
  )
    : INode(MemberAccessKlass::Self(), parent),
      obj(std::move(obj)),
      member(member->as<Object::PyString>()) {}

  [[nodiscard]] INodePtr Obj() const { return obj; }

  [[nodiscard]] Object::PyStrPtr Member() const { return member; }

 private:
  INodePtr obj;
  Object::PyStrPtr member;
};

using MemberAccessPtr = std::shared_ptr<MemberAccess>;

inline INodePtr CreateMemberAccess(
  const INodePtr& obj,
  const Object::PyObjPtr& member,
  const INodePtr& parent
) {
  return std::make_shared<MemberAccess>(obj, member, parent);
}

}  // namespace torchlight::Ast

#endif