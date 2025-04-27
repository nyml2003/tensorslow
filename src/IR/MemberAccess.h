#ifndef TORCHLIGHT_AST_MEMBERACCESS_H
#define TORCHLIGHT_AST_MEMBERACCESS_H

#include "Function/BuiltinFunction.h"
#include "IR/INode.h"

namespace torchlight::IR {

class MemberAccessKlass : public INodeKlass {
 public:
  MemberAccessKlass() = default;

  static Object::KlassPtr Self() {
    static auto instance = std::make_shared<MemberAccessKlass>();
    return instance;
  }

  void Initialize() override {
    if (this->isInitialized) {
      return;
    }
    InitKlass(Object::CreatePyString("ast_memberaccess"), Self());
    this->isInitialized = true;
  }

  Object::PyObjPtr
  visit(const Object::PyObjPtr& obj, const Object::PyObjPtr& codeList) override;

  Object::PyObjPtr
  emit(const Object::PyObjPtr& obj, const Object::PyObjPtr& codeList) override;

  Object::PyObjPtr print(const Object::PyObjPtr& obj) override;
};

class MemberAccess : public INode {
 public:
  MemberAccess(INodePtr obj, Object::PyStrPtr member, const INodePtr& parent)
    : INode(MemberAccessKlass::Self(), parent),
      obj(std::move(obj)),
      member(std::move(member)) {}

  [[nodiscard]] INodePtr Obj() const { return obj; }

  [[nodiscard]] Object::PyStrPtr Member() const { return member; }

  [[nodiscard]] STOREORLOAD Mode() const { return mode; }

  void SetStoreMode() { mode = STOREORLOAD::STORE; }

 private:
  INodePtr obj;
  Object::PyStrPtr member;
  STOREORLOAD mode = STOREORLOAD::LOAD;
};

using MemberAccessPtr = std::shared_ptr<MemberAccess>;

inline INodePtr CreateMemberAccess(
  const INodePtr& obj,
  const Object::PyStrPtr& member,
  const INodePtr& parent
) {
  return std::make_shared<MemberAccess>(obj, member, parent);
}

}  // namespace torchlight::IR

#endif