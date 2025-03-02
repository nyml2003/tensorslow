#include "Ast/PassStmt.h"

namespace torchlight::Ast {

Object::PyObjPtr PassStmtKlass::emit(
  const Object::PyObjPtr& obj,
  const Object::PyObjPtr& codeList
) {
  auto stmt = std::dynamic_pointer_cast<PassStmt>(obj);
  auto code = GetCodeFromList(codeList, stmt);
  code->Nop();
  return Object::CreatePyNone();
}

}  // namespace torchlight::Ast