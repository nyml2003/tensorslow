#include "IR/Statement/PassStmt.h"

namespace torchlight::IR {

Object::PyObjPtr PassStmtKlass::emit(
  const Object::PyObjPtr& obj,
  const Object::PyObjPtr& codeList
) {
  auto stmt = obj->as<PassStmt>();
  auto code = GetCodeFromList(codeList, stmt);
  code->Nop();
  return Object::CreatePyNone();
}

}  // namespace torchlight::IR