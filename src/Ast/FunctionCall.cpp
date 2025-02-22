#include "Ast/FunctionCall.h"
#include "Ast/INode.h"
#include "Object/ObjectHelper.h"
#include "Object/PyDictionary.h"
#include "Object/PyInteger.h"
#include "Object/PyNone.h"
#include "Object/PyString.h"
#include "Object/PyType.h"
namespace torchlight::Ast {

FunctionCall::FunctionCall(
  Object::PyObjPtr _func,
  Object::PyObjPtr _args,
  Ast::INodePtr parent
)
  : INode(FunctionCallKlass::Self(), std::move(parent)) {
  func = std::dynamic_pointer_cast<Ast::INode>(_func);
  args = std::dynamic_pointer_cast<Object::PyList>(_args);
}

Ast::INodePtr FunctionCall::Func() const {
  return func;
}

Object::PyListPtr FunctionCall::Args() const {
  return args;
}

Ast::INodePtr CreateFunctionCall(
  Object::PyObjPtr func,
  Object::PyObjPtr args,
  Ast::INodePtr parent
) {
  return std::make_shared<FunctionCall>(
    std::move(func), std::move(args), parent
  );
}

FunctionCallKlass::FunctionCallKlass() = default;

void FunctionCallKlass::Initialize() {
  SetName(Object::CreatePyString("FunctionCall"));
  SetType(CreatePyType(Self()));
  SetAttributes(Object::CreatePyDict());
  Klass::Initialize();
}

Object::PyObjPtr
FunctionCallKlass::emit(Object::PyObjPtr obj, Object::PyObjPtr codeList) {
  auto functionCall = std::dynamic_pointer_cast<FunctionCall>(obj);
  auto func = functionCall->Func();
  auto args = functionCall->Args();
  func->emit(codeList);
  Object::ForEach(
    std::dynamic_pointer_cast<Object::PyList>(args),
    [&codeList](const Object::PyObjPtr& arg, Index, const Object::PyObjPtr&) {
      auto argNode = std::dynamic_pointer_cast<INode>(arg);
      argNode->emit(codeList);
    }
  );
  auto code = GetCodeFromList(codeList, functionCall);
  code->CallFunction(ToU64(args->len()));
  return Object::CreatePyNone();
}

Object::PyObjPtr
FunctionCallKlass::visit(Object::PyObjPtr obj, Object::PyObjPtr codeList) {
  auto functionCall = std::dynamic_pointer_cast<FunctionCall>(obj);
  auto func = functionCall->Func();
  auto args = functionCall->Args();
  func->visit(codeList);
  Object::ForEach(
    std::dynamic_pointer_cast<Object::PyList>(args),
    [&codeList](const Object::PyObjPtr& arg, Index, const Object::PyObjPtr&) {
      auto argNode = std::dynamic_pointer_cast<INode>(arg);
      argNode->visit(codeList);
    }
  );
  return Object::CreatePyNone();
}

Object::KlassPtr FunctionCallKlass::Self() {
  static Object::KlassPtr instance = std::make_shared<FunctionCallKlass>();
  return instance;
}

}  // namespace torchlight::Ast