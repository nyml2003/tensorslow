#ifndef TENSORSLOW_AST_ATOM_H
#define TENSORSLOW_AST_ATOM_H

#include "Function/BuiltinFunction.h"
#include "IR/INode.h"

namespace tensorslow::IR {

class AtomKlass : public INodeKlass {
 public:
  explicit AtomKlass() = default;

  void Initialize() override {
    if (this->isInitialized) {
      return;
    }
    InitKlass(Object::CreatePyString("ast_atom"), Self());
    this->isInitialized = true;
  }

  static Object::KlassPtr Self() {
    static auto instance = std::make_shared<AtomKlass>();
    return instance;
  }

  Object::PyObjPtr
  visit(const Object::PyObjPtr& obj, const Object::PyObjPtr& codeList) override;

  Object::PyObjPtr
  emit(const Object::PyObjPtr& obj, const Object::PyObjPtr& codeList) override;

  Object::PyObjPtr print(const Object::PyObjPtr& obj) override;
};

// True False None Integer Float String字面量，不包含dict, list, tuple
class Atom : public INode {
 public:
  explicit Atom(Object::PyObjPtr obj, const INodePtr& parent)
    : INode(AtomKlass::Self(), parent), obj(std::move(obj)) {}

  [[nodiscard]] Object::PyObjPtr Obj() const { return obj; }

 private:
  Object::PyObjPtr obj;
};

inline INodePtr CreateAtom(Object::PyObjPtr obj, INodePtr parent) {
  return std::make_shared<Atom>(std::move(obj), std::move(parent));
}

}  // namespace tensorslow::IR

#endif