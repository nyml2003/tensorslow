#ifndef TENSORSLOW_AST_MAP_H
#define TENSORSLOW_AST_MAP_H

#include "IR/INode.h"

namespace tensorslow::IR {

class MapKlass : public INodeTrait, public Object::KlassBase<MapKlass> {
 public:
  MapKlass() = default;

  void Initialize() override {
    if (this->IsInitialized()) {
      return;
    }
    InitKlass(Object::CreatePyString("ast_map"), Self());
    this->SetInitialized();
  }

  Object::PyObjPtr
  visit(const Object::PyObjPtr& obj, const Object::PyObjPtr& codeList) override;

  Object::PyObjPtr
  emit(const Object::PyObjPtr& obj, const Object::PyObjPtr& codeList) override;

  Object::PyObjPtr print(const Object::PyObjPtr& obj) override;
};

class Map : public INode {
 public:
  explicit Map(
    Object::PyListPtr keys,
    Object::PyListPtr values,
    const INodePtr& parent
  )
    : INode(MapKlass::Self(), parent), keys(keys), values(values) {}

  Object::PyListPtr Keys() const { return keys; }
  Object::PyListPtr Values() const { return values; }

 private:
  Object::PyListPtr keys;
  Object::PyListPtr values;
};

using MapPtr = std::shared_ptr<Map>;

inline INodePtr CreateMap(
  const Object::PyListPtr& keys,
  const Object::PyListPtr& values,
  const INodePtr& parent
) {
  return std::make_shared<Map>(keys, values, parent);
}

}  // namespace tensorslow::IR

#endif