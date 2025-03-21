#include "Ast/Expression/FunctionCall.h"
#include "Object/PyNone.h"
namespace torchlight::Ast {

Object::PyObjPtr FunctionCallKlass::emit(
  const Object::PyObjPtr& obj,
  const Object::PyObjPtr& codeList
) {
  auto functionCall = obj->as<FunctionCall>();
  auto func = functionCall->Func();
  auto args = functionCall->Args();
  func->emit(codeList);
  Object::ForEach(
    args,
    [&codeList](const Object::PyObjPtr& arg, Index, const Object::PyObjPtr&) {
      arg->as<INode>()->emit(codeList);
    }
  );
  auto code = GetCodeFromList(codeList, functionCall);
  code->CallFunction(args->Length());
  return Object::CreatePyNone();
}

Object::PyObjPtr FunctionCallKlass::visit(
  const Object::PyObjPtr& obj,
  const Object::PyObjPtr& codeList
) {
  auto functionCall = obj->as<FunctionCall>();
  auto func = functionCall->Func();
  auto args = functionCall->Args();
  func->visit(codeList);
  Object::ForEach(
    args,
    [&codeList](const Object::PyObjPtr& arg, Index, const Object::PyObjPtr&) {
      arg->as<INode>()->visit(codeList);
    }
  );
  return Object::CreatePyNone();
}

}  // namespace torchlight::Ast