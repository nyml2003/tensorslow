#include "Ast/AstHelper.h"
#include "Ast/AssignStmt.h"
#include "Ast/Atom.h"
#include "Ast/Binary.h"
#include "Ast/ExprStmt.h"
#include "Ast/FuncDef.h"
#include "Ast/FunctionCall.h"
#include "Ast/Identifier.h"
#include "Ast/IfStmt.h"
#include "Ast/List.h"
#include "Ast/MemberAccess.h"
#include "Ast/Module.h"
#include "Ast/ReturnStmt.h"
#include "Ast/WhileStmt.h"

namespace torchlight::Ast {

void AstKlassLoad() {
  Ast::ModuleKlass::Self()->Initialize();
  Ast::FuncDefKlass::Self()->Initialize();
  Ast::ExprStmtKlass::Self()->Initialize();
  Ast::AssignStmtKlass::Self()->Initialize();
  Ast::AtomKlass::Self()->Initialize();
  Ast::BinaryKlass::Self()->Initialize();
  Ast::FunctionCallKlass::Self()->Initialize();
  Ast::IdentifierKlass::Self()->Initialize();
  Ast::ListKlass::Self()->Initialize();
  Ast::MemberAccessKlass::Self()->Initialize();
  Ast::ReturnStmtKlass::Self()->Initialize();
  Ast::IfStmtKlass::Self()->Initialize();
  Ast::WhileStmtKlass::Self()->Initialize();
}

}  // namespace torchlight::Ast