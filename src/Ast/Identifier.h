#ifndef TORCHLIGHT_AST_IDENTIFIER_H
#define TORCHLIGHT_AST_IDENTIFIER_H

#include "Ast/INode.h"

namespace torchlight::Ast {

class IdentifierKlass : public INodeKlass {
 public:
  IdentifierKlass() = default;

  static Object::KlassPtr Self() {
    static auto instance = std::make_shared<IdentifierKlass>();
    Object::LoadClass(
      Object::CreatePyString("Identifier")->as<Object::PyString>(), instance
    );
    Object::ConfigureBasicAttributes(instance);
    return instance;
  }

  Object::PyObjPtr
  visit(const Object::PyObjPtr& obj, const Object::PyObjPtr& codeList) override;
  Object::PyObjPtr
  emit(const Object::PyObjPtr& obj, const Object::PyObjPtr& codeList) override;
};

class Identifier : public INode {
 public:
  explicit Identifier(const Object::PyObjPtr& _name, const INodePtr& parent)
    : INode(IdentifierKlass::Self(), std::move(parent)),
      name(_name->as<Object::PyString>()) {}

  [[nodiscard]] Object::PyStrPtr Name() const { return name; }

 private:
  Object::PyStrPtr name;
};

using IdentifierPtr = std::shared_ptr<Identifier>;

inline INodePtr
CreateIdentifier(const Object::PyObjPtr& name, INodePtr parent) {
  return std::make_shared<Identifier>(name, parent);
}
}  // namespace torchlight::Ast

#endif