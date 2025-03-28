#ifndef TORCHLIGHT_AST_IDENTIFIER_H
#define TORCHLIGHT_AST_IDENTIFIER_H

#include "Ast/INode.h"
#include "Function/ObjectHelper.h"
#include "Object/String/PyString.h"

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
    : INode(IdentifierKlass::Self(), parent),
      name(_name->as<Object::PyString>()) {
    builtins = Object::CreatePyList({Object::CreatePyString("print"),
                                     Object::CreatePyString("reshape"),
                                     Object::CreatePyString("Reshape"),
                                     Object::CreatePyString("len"),
                                     Object::CreatePyString("__name__"),
                                     Object::CreatePyString("randint"),
                                     Object::CreatePyString("sleep"),
                                     Object::CreatePyString("input"),
                                     Object::CreatePyString("next"),
                                     Object::CreatePyString("int"),
                                     Object::CreatePyString("float"),
                                     Object::CreatePyString("str"),
                                     Object::CreatePyString("list"),
                                     Object::CreatePyString("object"),
                                     Object::CreatePyString("type"),
                                     Object::CreatePyString("dict"),
                                     Object::CreatePyString("slice"),
                                     Object::CreatePyString("repr"),
                                     Object::CreatePyString("bool"),
                                     Object::CreatePyString("Array"),
                                     Object::CreatePyString("Eye"),
                                     Object::CreatePyString("Zeros"),
                                     Object::CreatePyString("Ones"),
                                     Object::CreatePyString("Diag"),
                                     Object::CreatePyString("Transpose"),
                                     Object::CreatePyString("Shape"),
                                     Object::CreatePyString("Where"),
                                     Object::CreatePyString("Concatenate"),
                                     Object::CreatePyString("Ravel"),
                                     Object::CreatePyString("Normal"),
                                     Object::CreatePyString("Shuffle"),
                                     Object::CreatePyString("id"),
                                     Object::CreatePyString("iter")})
                 ->as<Object::PyList>();
  }

  [[nodiscard]] Object::PyStrPtr Name() const { return name; }
  void SetStoreMode() { mode = STOREORLOAD::STORE; }
  STOREORLOAD Mode() const { return mode; }
  [[nodiscard]] Object::PyListPtr Builtins() const { return builtins; }

 private:
  Object::PyStrPtr name;
  STOREORLOAD mode = STOREORLOAD::LOAD;
  Object::PyListPtr builtins;
};

using IdentifierPtr = std::shared_ptr<Identifier>;

inline INodePtr
CreateIdentifier(const Object::PyObjPtr& name, INodePtr parent) {
  return std::make_shared<Identifier>(name, parent);
}

enum class IdentifierRegistry {
  UNREGISTERED,
  LOCAL_VARNAME,
  LOCAL_NAME,
  GLOBAL_NAME,
  BUILTIN
};

IdentifierRegistry GetIdentifierRegistry(
  const Object::PyStrPtr& name,
  const Object::PyCodePtr& current,
  const Object::PyCodePtr& global,
  const Object::PyListPtr& builtins
);

}  // namespace torchlight::Ast

#endif