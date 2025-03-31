#ifndef TORCHLIGHT_AST_HELPER_H
#define TORCHLIGHT_AST_HELPER_H

#include "Ast/AssignStmt.h"
#include "Ast/ClassDef.h"
#include "Ast/Expression/Atom.h"
#include "Ast/Expression/Binary.h"
#include "Ast/Expression/FunctionCall.h"
#include "Ast/Expression/List.h"
#include "Ast/Expression/Map.h"
#include "Ast/Expression/Slice.h"
#include "Ast/Expression/Unary.h"
#include "Ast/FuncDef.h"
#include "Ast/Identifier.h"
#include "Ast/MemberAccess.h"
#include "Ast/Module.h"
#include "Ast/Statement/ExprStmt.h"
#include "Ast/Statement/ForStmt.h"
#include "Ast/Statement/IfStmt.h"
#include "Ast/Statement/PassStmt.h"
#include "Ast/Statement/ReturnStmt.h"
#include "Ast/Statement/WhileStmt.h"
#include "Ast/Statement/YieldStmt.h"

namespace torchlight::Ast {

inline void RegisterAstKlass() {
  AtomKlass::Self()->Initialize();
  BinaryKlass::Self()->Initialize();
  FunctionCallKlass::Self()->Initialize();
  ListKlass::Self()->Initialize();
  MapKlass::Self()->Initialize();
  SliceKlass::Self()->Initialize();
  UnaryKlass::Self()->Initialize();
  ExprStmtKlass::Self()->Initialize();
  ForStmtKlass::Self()->Initialize();
  IfStmtKlass::Self()->Initialize();
  PassStmtKlass::Self()->Initialize();
  ReturnStmtKlass::Self()->Initialize();
  WhileStmtKlass::Self()->Initialize();
  YieldStmtKlass::Self()->Initialize();
  AssignStmtKlass::Self()->Initialize();
  ClassDefKlass::Self()->Initialize();
  FuncDefKlass::Self()->Initialize();
  IdentifierKlass::Self()->Initialize();
  MemberAccessKlass::Self()->Initialize();
  ModuleKlass::Self()->Initialize();
}

}  // namespace torchlight::Ast

#endif