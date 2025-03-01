#ifndef TORCHLIGHT_AST_ATOM_H
#define TORCHLIGHT_AST_ATOM_H

#include <utility>

#include "Ast/INode.h"

namespace torchlight::Ast {

class AtomKlass : public INodeKlass {
 public:
  explicit AtomKlass() = default;

  static Object::KlassPtr Self() {
    static auto instance = std::make_shared<AtomKlass>();
    LoadClass(Object::CreatePyString("Atom")->as<Object::PyString>(), instance);
    ConfigureBasicAttributes(instance);
    return instance;
  }

  Object::PyObjPtr
  visit(const Object::PyObjPtr& obj, const Object::PyObjPtr& codeList) override;

  Object::PyObjPtr
  emit(const Object::PyObjPtr& obj, const Object::PyObjPtr& codeList) override;
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

}  // namespace torchlight::Ast

#endif