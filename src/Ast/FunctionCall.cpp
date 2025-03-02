#include "Ast/FunctionCall.h"
#include "Ast/INode.h"
#include "Object/ObjectHelper.h"
#include "Object/PyNone.h"
namespace torchlight::Ast {

Object::PyObjPtr FunctionCallKlass::emit(
  const Object::PyObjPtr& obj,
  const Object::PyObjPtr& codeList
) {
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
  code->CallFunction(args->Length());
  return Object::CreatePyNone();
}

Object::PyObjPtr FunctionCallKlass::visit(
  const Object::PyObjPtr& obj,
  const Object::PyObjPtr& codeList
) {
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

}  // namespace torchlight::Ast