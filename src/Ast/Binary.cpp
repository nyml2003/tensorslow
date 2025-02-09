#include "Ast/Binary.h"
#include "ByteCode/PyCode.h"
#include "ByteCode/PyInst.h"
#include "Object/PyDictionary.h"
#include "Object/PyNone.h"
#include "Object/PyString.h"
#include "Object/PyType.h"

namespace torchlight::Ast {

Binary::Binary(
  Operator oprt,
  Ast::INodePtr left,
  Ast::INodePtr right,
  Ast::INodePtr parent
)
  : INode(BinaryKlass::Self(), std::move(parent)),
    oprt(oprt),
    left(std::move(left)),
    right(std::move(right)) {}

Ast::INodePtr Binary::Left() const {
  return left;
}

Ast::INodePtr Binary::Right() const {
  return right;
}

Binary::Operator Binary::Oprt() const {
  return oprt;
}

Ast::INodePtr CreateBinary(
  Binary::Operator oprt,
  Ast::INodePtr left,
  Ast::INodePtr right,
  Ast::INodePtr parent
) {
  return std::make_shared<Binary>(
    oprt, std::move(left), std::move(right), parent
  );
}

void BinaryKlass::Initialize() {
  SetName(Object::CreatePyString("Binary"));
  SetType(CreatePyType(Self()));
  SetAttributes(Object::CreatePyDict());
  Klass::Initialize();
}

Object::PyObjPtr
BinaryKlass::visit(Object::PyObjPtr obj, Object::PyObjPtr codeList) {
  auto binary = std::dynamic_pointer_cast<Binary>(obj);
  auto left = binary->Left();
  auto right = binary->Right();
  left->visit(codeList);
  right->visit(codeList);
  return Object::CreatePyNone();
}
Object::PyObjPtr
BinaryKlass::emit(Object::PyObjPtr obj, Object::PyObjPtr codeList) {
  auto binary = std::dynamic_pointer_cast<Binary>(obj);
  auto left = binary->Left();
  auto right = binary->Right();
  left->emit(codeList);
  right->emit(codeList);
  Object::PyObjPtr inst = nullptr;
  switch (binary->Oprt()) {
    case Binary::Operator::ADD:
      inst = Object::CreateBinaryAdd();
      break;
    case Binary::Operator::SUB:
      inst = Object::CreateBinarySubtract();
      break;
    case Binary::Operator::MUL:
      inst = Object::CreateBinaryMultiply();
      break;
    case Binary::Operator::MATMUL:
      inst = Object::CreateBinaryMatrixMultiply();
      break;
    default:
      break;
  }
  auto code = GetCodeFromList(codeList, binary);
  code->Instructions()->Append(inst);
  return Object::CreatePyNone();
}

BinaryKlass::BinaryKlass() = default;

Object::KlassPtr BinaryKlass::Self() {
  static Object::KlassPtr instance = std::make_shared<BinaryKlass>();
  return instance;
}

}  // namespace torchlight::Ast
