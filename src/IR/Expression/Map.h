#ifndef TORCHLIGHT_AST_MAP_H
#define TORCHLIGHT_AST_MAP_H

#include "Function/BuiltinFunction.h"
#include "IR/INode.h"

namespace torchlight::IR {

class MapKlass : public INodeKlass {
 public:
  MapKlass() = default;

  void Initialize() override {
    if (this->isInitialized) {
      return;
    }
    InitKlass(Object::CreatePyString("ast_map"), Self());
    this->isInitialized = true;
  }

  static Object::KlassPtr Self() {
    static auto instance = std::make_shared<MapKlass>();
    return instance;
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

}  // namespace torchlight::IR

#endif