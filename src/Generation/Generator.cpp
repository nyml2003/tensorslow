#include "Generation/Generator.h"

#include "Ast/AssignStmt.h"
#include "Ast/Atom.h"
#include "Ast/Binary.h"
#include "Ast/ClassDef.h"
#include "Ast/ExprStmt.h"
#include "Ast/ForStmt.h"
#include "Ast/FuncDef.h"
#include "Ast/FunctionCall.h"
#include "Ast/INode.h"
#include "Ast/Identifier.h"
#include "Ast/IfStmt.h"
#include "Ast/List.h"
#include "Ast/MemberAccess.h"
#include "Ast/Module.h"
#include "Ast/ReturnStmt.h"
#include "Ast/WhileStmt.h"
#include "ByteCode/PyCode.h"
#include "Collections/IntegerHelper.h"
#include "Object/ObjectHelper.h"
#include "Object/PyBoolean.h"
#include "Object/PyFloat.h"
#include "Object/PyInteger.h"
#include "Object/PyList.h"
#include "Object/PyNone.h"
#include "Object/PyObject.h"
#include "Object/PyString.h"
#include "support/Any.h"

#include <memory>

namespace torchlight::Generation {

Generator::Generator(Object::PyObjPtr filename) {
  context = Ast::CreateModule(Object::CreatePyList({}), filename);
  codeList =
    std::dynamic_pointer_cast<Object::PyList>(Object::CreatePyList({}));
}

void Generator::Visit() {
  context->visit(codeList);
}

void Generator::Emit() {
  context->emit(codeList);
}

[[nodiscard]] Object::PyCodePtr Generator::Code() const {
  return Ast::GetCodeFromList(codeList, context);
}

antlrcpp::Any Generator::visitStmt(Python3Parser::StmtContext* ctx) {
  if (ctx->simple_stmts()) {
    return visitSimple_stmts(ctx->simple_stmts()).as<Object::PyObjPtr>();
  } else if (ctx->compound_stmt()) {
    return visitCompound_stmt(ctx->compound_stmt()).as<Ast::INodePtr>();
  }
  return nullptr;
}

antlrcpp::Any Generator::visitFile_input(Python3Parser::File_inputContext* ctx
) {
  auto stmts = ctx->stmt();
  Collections::List<Object::PyObjPtr> statements(
    static_cast<uint64_t>(stmts.size())
  );
  for (auto* it : stmts) {
    auto stmt = visitStmt(it);
    if (stmt.is<Object::PyObjPtr>()) {
      Object::ForEach(
        std::dynamic_pointer_cast<Object::PyList>(stmt.as<Object::PyObjPtr>()),
        [&statements](const Object::PyObjPtr& stmt, Index, const Object::PyObjPtr&) {
          statements.Push(stmt);
        }
      );
    } else {
      statements.Push(stmt.as<Ast::INodePtr>());
    }
  }
  auto IsModule = std::dynamic_pointer_cast<Ast::Module>(context);
  if (IsModule != nullptr) {
    IsModule->SetBody(Object::CreatePyList(statements));
    return nullptr;
  }
  auto IsFuncDef = std::dynamic_pointer_cast<Ast::FuncDef>(context);
  if (IsFuncDef != nullptr) {
    IsFuncDef->SetBody(Object::CreatePyList(statements));
    return nullptr;
  }
  std::cerr << "visitFile_input: Unknown context type" << std::endl;
  return nullptr;
}

antlrcpp::Any Generator::visitTestlist_comp(
  Python3Parser::Testlist_compContext* ctx
) {
  auto testlist = ctx->test();
  Collections::List<Object::PyObjPtr> tests(static_cast<uint64_t>(testlist.size(
  )));
  for (auto* it : testlist) {
    auto test = visitTest(it).as<Ast::INodePtr>();
    tests.Push(test);
  }
  return Object::CreatePyList(tests);
}

antlrcpp::Any Generator::visitAtom(Python3Parser::AtomContext* ctx) {
  if (ctx->OPEN_PAREN() != nullptr) {
    // 情况 1: '(' (yield_expr | testlist_comp)? ')'
    std::cout << "atom: '(' (yield_expr | testlist_comp)? ')'" << std::endl;
    // if (ctx->yield_expr()) {
    //   //visitYield_expr(ctx->yield_expr());
    // } else if (ctx->testlist_comp()) {
    //   //visitTestlist_comp(ctx->testlist_comp());
    // }
  } else if (ctx->OPEN_BRACK() != nullptr) {
    // 情况 2: '[' testlist_comp? ']'
    if (ctx->testlist_comp() == nullptr) {
      return Ast::CreateList(Object::CreatePyList({}), context);
    }
    auto testlist_comp =
      visitTestlist_comp(ctx->testlist_comp()).as<Object::PyObjPtr>();
    if (testlist_comp->Klass() == Object::ListKlass::Self()) {
      return Ast::CreateList(testlist_comp, context);
    }
    std::cerr << "visitAtom: testlist_comp is not a List" << std::endl;

  } else if (ctx->OPEN_BRACE() != nullptr) {
    // 情况 3: '{' dictorsetmaker? '}'
    std::cout << "atom: '{' dictorsetmaker? '}'" << std::endl;
    // if (ctx->dictorsetmaker()) {
    //   visitDictorsetmaker(ctx->dictorsetmaker());
    // }
  } else if (ctx->name() != nullptr) {
    // 情况 4: name
    return Ast::CreateIdentifier(
      Object::CreatePyString(ctx->name()->getText().c_str()), context
    );
    // visitName(ctx->name());
  } else if (ctx->NUMBER() != nullptr) {
    // 情况 5: NUMBER
    std::string numberText = ctx->NUMBER()->getText();

    // 检查字符串中是否包含小数点
    if (numberText.find('.') != std::string::npos) {
      // 情况 5.1: Float
      return Ast::CreateAtom(
        Object::CreatePyFloat(std::stod(numberText)), context
      );
    }
    // 情况 5.2: Integer
    return Ast::CreateAtom(
      Object::CreatePyInteger(
        Collections::CreateIntegerWithCString(numberText.c_str())
      ),
      context
    );

  } else if (!ctx->STRING().empty()) {
    // 情况 6: STRING+
    Object::PyObjPtr str = Object::CreatePyString("");
    for (auto* string : ctx->STRING()) {
      auto rawString = string->getText();
      rawString = rawString.substr(1, rawString.size() - 2);
      str = str->add(Object::CreatePyString(rawString));
    }
    return Ast::CreateAtom(str, context);
  } else if (ctx->ELLIPSIS() != nullptr) {
    // 情况 7: '...'
    std::cout << "atom: '...'" << std::endl;
  } else if (ctx->NONE() != nullptr) {
    // 情况 8: 'None'
    return Ast::CreateAtom(Object::CreatePyNone(), context);
  } else if (ctx->TRUE() != nullptr) {
    // 情况 9: 'True'
    return Ast::CreateAtom(Object::CreatePyBoolean(true), context);
  } else if (ctx->FALSE() != nullptr) {
    // 情况 10: 'False'
    return Ast::CreateAtom(Object::CreatePyBoolean(false), context);
  } else {
    // 其他情况
    std::cout << "atom: Unknown type" << std::endl;
  }
  return nullptr;
}

antlrcpp::Any Generator::visitExpr(Python3Parser::ExprContext* ctx) {
  if (ctx->atom_expr() != nullptr) {
    // 情况 1: atom_expr
    return visitAtom_expr(ctx->atom_expr());
  }
  if (ctx->expr().size() == 2 && ctx->POWER() != nullptr) {
    // 情况 2: expr '**' expr
    std::cout << "expr '**' expr" << std::endl;
    visitExpr(ctx->expr(0));
    visitExpr(ctx->expr(1));
  } else if ((ctx->expr().size() == 1) &&
             (!ctx->ADD().empty() || !ctx->MINUS().empty() ||
              !ctx->NOT_OP().empty())) {
    // 情况 3: ('+' | '-' | '~')+ expr
    std::cout << "('+' | '-' | '~')+ expr" << std::endl;
    visitExpr(ctx->expr(0));
  } else if (ctx->expr().size() ==
               2 &&  // 情况 4: expr ('*' | '@' | '/' | '%' | '//') expr
             (ctx->STAR() != nullptr || ctx->AT() != nullptr ||
              ctx->DIV() != nullptr || ctx->MOD() != nullptr ||
              ctx->IDIV() != nullptr)) {
    bool isStar = (ctx->STAR() != nullptr);
    bool isAt = (ctx->AT() != nullptr);
    bool isDiv = (ctx->DIV() != nullptr);
    bool isMod = (ctx->MOD() != nullptr);
    bool isIdiv = (ctx->IDIV() != nullptr);
    auto left = visitExpr(ctx->expr(0));
    auto right = visitExpr(ctx->expr(1));
    return isStar
             ? CreateBinary(Ast::Binary::Operator::MUL, left, right, context)
           : isAt
             ? CreateBinary(Ast::Binary::Operator::MATMUL, left, right, context)
           : isDiv
             ? CreateBinary(Ast::Binary::Operator::DIV, left, right, context)
           : isMod
             ? CreateBinary(Ast::Binary::Operator::MOD, left, right, context)
             : CreateBinary(
                 Ast::Binary::Operator::FLOOR_DIV, left, right, context
               );
  } else if (ctx->expr().size() == 2 &&
             (ctx->ADD().size() == 1 || ctx->MINUS().size() == 1)) {
    // 情况 5: expr ('+' | '-') expr
    bool isAdd = (ctx->ADD().size() == 1);
    bool isMinus = (ctx->MINUS().size() == 1);
    auto left = visitExpr(ctx->expr(0));
    auto right = visitExpr(ctx->expr(1));
    return isAdd
             ? CreateBinary(Ast::Binary::Operator::ADD, left, right, context)
             : CreateBinary(Ast::Binary::Operator::SUB, left, right, context);
  } else if (ctx->expr().size() == 2 &&
             (ctx->LEFT_SHIFT() != nullptr || ctx->RIGHT_SHIFT() != nullptr)) {
    // 情况 6: expr ('<<' | '>>') expr
    std::cout << "expr ('<<' | '>>') expr" << std::endl;
    visitExpr(ctx->expr(0));
    visitExpr(ctx->expr(1));
  } else if (ctx->expr().size() == 2 && ctx->AND_OP() != nullptr) {
    // 情况 7: expr '&' expr
    std::cout << "expr '&' expr" << std::endl;
    visitExpr(ctx->expr(0));
    visitExpr(ctx->expr(1));
  } else if (ctx->expr().size() == 2 && ctx->XOR() != nullptr) {
    // 情况 8: expr '^' expr
    std::cout << "expr '^' expr" << std::endl;
    visitExpr(ctx->expr(0));
    visitExpr(ctx->expr(1));
  } else if (ctx->expr().size() == 2 && ctx->OR_OP() != nullptr) {
    // 情况 9: expr '|' expr
    std::cout << "expr '|' expr" << std::endl;
    visitExpr(ctx->expr(0));
    visitExpr(ctx->expr(1));
  } else {
    // 其他情况
    std::cout << "Unknown expression type" << std::endl;
  }
  return nullptr;
}

antlrcpp::Any Generator::visitExpr_stmt(Python3Parser::Expr_stmtContext* ctx) {
  // 处理类型注解赋值 (annassign)
  if (ctx->annassign() != nullptr) {
    std::cout << "Annotation assignment" << std::endl;
    // return visitAnnassign(ctx->annassign());
    return nullptr;
  }

  // 处理增强赋值 (augassign)
  if (ctx->augassign() != nullptr) {
    std::cout << "Augmented assignment" << std::endl;
    visitAugassign(ctx->augassign());

    // 处理右侧的 yield_expr 或 testlist
    if (!ctx->yield_expr().empty()) {
      return nullptr;
    }
    if (ctx->testlist() != nullptr) {
      return nullptr;
    }
  }

  // 处理普通赋值或多重赋值
  if (!ctx->ASSIGN().empty()) {
    auto source =
      visitTestlist_star_expr(ctx->testlist_star_expr(1)).as<Ast::INodePtr>();
    auto target =
      visitTestlist_star_expr(ctx->testlist_star_expr(0)).as<Ast::INodePtr>();
    return Ast::CreateAssignStmt(target, source, context);
    // 遍历所有赋值右侧的表达式
    // for (auto* exprIt : ctx->testlist_star_expr()) {
    //   auto expr = visitTestlist_star_expr(exprIt).as<Object::PyObjPtr>();
    // }
  }

  // 处理只有 testlist_star_expr 的情况
  if (ctx->ASSIGN().empty()) {
    return Ast::CreateExprStmt(
      visitTestlist_star_expr(ctx->testlist_star_expr(0)), context
    );
  }

  return nullptr;
}

antlrcpp::Any Generator::visitArglist(Python3Parser::ArglistContext* ctx) {
  auto arglist = ctx->argument();
  Collections::List<Object::PyObjPtr> args(static_cast<uint64_t>(arglist.size())
  );
  for (auto* it : arglist) {
    args.Push(visitArgument(it).as<Ast::INodePtr>());
  }
  return Object::CreatePyList(args);
}

antlrcpp::Any Generator::visitArgument(Python3Parser::ArgumentContext* ctx) {
  return visitTest(ctx->test(0));
}

antlrcpp::Any Generator::visitTrailer(Python3Parser::TrailerContext* ctx) {
  if (ctx->OPEN_PAREN() != nullptr) {
    if (ctx->arglist() != nullptr) {
      return visitArglist(ctx->arglist());
    }
    return Object::CreatePyList({});
  } else if (ctx->OPEN_BRACK() != nullptr) {
    return visitSubscriptlist(ctx->subscriptlist());
  } else if (ctx->DOT() != nullptr) {
    throw std::runtime_error("visitTrailer: DOT is handled by visitAtom_expr");
  } else {
    // 其他情况
    std::cout << "trailer: Unknown type" << std::endl;
  }
  return nullptr;
}

antlrcpp::Any Generator::visitAtom_expr(Python3Parser::Atom_exprContext* ctx) {
  if (ctx->trailer().empty()) {
    if (ctx->atom() != nullptr) {
      return visitAtom(ctx->atom()).as<Ast::INodePtr>();
    }
    return nullptr;
  }
  auto identifier = visitAtom(ctx->atom()).as<Ast::INodePtr>();
  auto result = identifier;
  auto trailers = ctx->trailer();
  for (auto& trailer : trailers) {
    if (trailer->OPEN_PAREN() != nullptr) {  // '('
      auto args = visitTrailer(trailer).as<Object::PyObjPtr>();
      result = Ast::CreateFunctionCall(result, args, context);
    } else if (trailer->OPEN_BRACK() != nullptr) {  // '['
      auto args = visitTrailer(trailer);
      result =
        Ast::CreateBinary(Ast::Binary::Operator::SUBSCR, result, args, context);
    } else if (trailer->DOT() != nullptr) {  // '.'
      auto args = Object::CreatePyString(trailer->name()->getText().c_str());
      result = Ast::CreateMemberAccess(result, args, context);
    }
  }
  return result;
}

antlrcpp::Any Generator::visitTestlist_star_expr(
  Python3Parser::Testlist_star_exprContext* ctx
) {
  return visitTest(ctx->test(0));
}

antlrcpp::Any Generator::visitTest(Python3Parser::TestContext* ctx) {
  return visitOr_test(ctx->or_test(0));
}

antlrcpp::Any Generator::visitOr_test(Python3Parser::Or_testContext* ctx) {
  return visitAnd_test(ctx->and_test(0));
}

antlrcpp::Any Generator::visitAnd_test(Python3Parser::And_testContext* ctx) {
  return visitNot_test(ctx->not_test(0));
}

antlrcpp::Any Generator::visitNot_test(Python3Parser::Not_testContext* ctx) {
  if (ctx->comparison() != nullptr) {
    return visitComparison(ctx->comparison());
  }
  return nullptr;
}

antlrcpp::Any Generator::visitComparison(Python3Parser::ComparisonContext* ctx
) {
  if (ctx->comp_op().empty()) {
    return visitExpr(ctx->expr(0));
  }
  auto left = visitExpr(ctx->expr(0));
  auto right = visitExpr(ctx->expr(1));
  if (ctx->comp_op(0)->GT_EQ() != nullptr) {
    return CreateBinary(Ast::Binary::Operator::GE, left, right, context);
  }
  if (ctx->comp_op(0)->LT_EQ() != nullptr) {
    return CreateBinary(Ast::Binary::Operator::LE, left, right, context);
  }
  if (ctx->comp_op(0)->EQUALS() != nullptr) {
    return CreateBinary(Ast::Binary::Operator::EQ, left, right, context);
  }
  if ((ctx->comp_op(0)->NOT_EQ_1() != nullptr) ||
      (ctx->comp_op(0)->NOT_EQ_2() != nullptr)) {
    return CreateBinary(Ast::Binary::Operator::NE, left, right, context);
  }
  if (ctx->comp_op(0)->LESS_THAN() != nullptr) {
    return CreateBinary(Ast::Binary::Operator::LT, left, right, context);
  }
  if (ctx->comp_op(0)->GREATER_THAN() != nullptr) {
    return CreateBinary(Ast::Binary::Operator::GT, left, right, context);
  }
  if (ctx->comp_op(0)->getText() == "in") {
    return CreateBinary(Ast::Binary::Operator::IN, left, right, context);
  }
  if (ctx->comp_op(0)->getText() == "notin") {
    return CreateBinary(Ast::Binary::Operator::NOT_IN, left, right, context);
  }
  if (ctx->comp_op(0)->getText() == "is") {
    return CreateBinary(Ast::Binary::Operator::IS, left, right, context);
  }
  if (ctx->comp_op(0)->getText() == "isnot") {
    return CreateBinary(Ast::Binary::Operator::IS_NOT, left, right, context);
  }
  return nullptr;
}

antlrcpp::Any Generator::visitCompound_stmt(
  Python3Parser::Compound_stmtContext* ctx
) {
  // 1. 如果是 if_stmt
  if (ctx->if_stmt()) {
    return visitIf_stmt(ctx->if_stmt());
  }
  // 2. 如果是 while_stmt
  else if (ctx->while_stmt()) {
    return visitWhile_stmt(ctx->while_stmt());
  }
  // 3. 如果是 for_stmt
  else if (ctx->for_stmt()) {
    return visitFor_stmt(ctx->for_stmt());
  }
  // 4. 如果是 try_stmt
  else if (ctx->try_stmt()) {
    return visitTry_stmt(ctx->try_stmt());
  }
  // 5. 如果是 with_stmt
  else if (ctx->with_stmt()) {
    return visitWith_stmt(ctx->with_stmt());
  }
  // 6. 如果是 funcdef
  else if (ctx->funcdef()) {
    return visitFuncdef(ctx->funcdef()).as<Ast::INodePtr>();
  }
  // 7. 如果是 classdef
  else if (ctx->classdef()) {
    return visitClassdef(ctx->classdef()).as<Ast::INodePtr>();
  }
  // 8. 如果是 decorated
  else if (ctx->decorated()) {
    return visitDecorated(ctx->decorated());
  }
  // 9. 如果是 async_stmt
  else if (ctx->async_stmt()) {
    return visitAsync_stmt(ctx->async_stmt());
  }
  // 10. 如果是 match_stmt
  else if (ctx->match_stmt()) {
    return visitMatch_stmt(ctx->match_stmt());
  }
  // 其他情况（不应该出现）
  else {
    std::cerr << "visitCompound_stmt: Unknown compound statement type"
              << std::endl;
    return nullptr;
  }
}

antlrcpp::Any Generator::visitFuncdef(Python3Parser::FuncdefContext* ctx) {
  // 1. 获取函数名
  auto funcName = Object::CreatePyString(ctx->name()->getText().c_str());
  // 2. 获取函数参数列表
  auto parameters = visitParameters(ctx->parameters()).as<Object::PyObjPtr>();
  // 3. 获取函数体

  // 4. 创建函数对象
  auto funcDef = std::dynamic_pointer_cast<Ast::FuncDef>(
    Ast::CreateFuncDef(funcName, parameters, Object::CreatePyList({}), context)
  );
  auto oldContext = context;
  context = funcDef;
  auto body = visitBlock(ctx->block()).as<Object::PyObjPtr>();
  funcDef->SetBody(body);
  context = oldContext;
  return std::dynamic_pointer_cast<Ast::INode>(funcDef);
}

antlrcpp::Any Generator::visitBlock(Python3Parser::BlockContext* ctx) {
  auto statements = ctx->stmt();
  if (!statements.empty()) {
    Collections::List<Object::PyObjPtr> stmts(
      static_cast<uint64_t>(statements.size())
    );
    for (auto* it : statements) {
      auto stmt = visitStmt(it);
      if (stmt.is<Object::PyObjPtr>()) {
        Object::ForEach(
          std::dynamic_pointer_cast<Object::PyList>(stmt.as<Object::PyObjPtr>()
          ),
          [&stmts](const Object::PyObjPtr& stmt, Index, const Object::PyObjPtr&) {
            stmts.Push(stmt);
          }
        );
      } else {
        stmts.Push(stmt.as<Ast::INodePtr>());
      }
    }
    return Object::CreatePyList(stmts);
  }
  auto* simple_stmts = ctx->simple_stmts();
  if (simple_stmts != nullptr) {
    return visitSimple_stmts(simple_stmts);
  }
  return nullptr;
}

antlrcpp::Any Generator::visitSimple_stmts(
  Python3Parser::Simple_stmtsContext* ctx
) {
  auto simple_stmt = ctx->simple_stmt();
  if (!simple_stmt.empty()) {
    Collections::List<Object::PyObjPtr> stmts(
      static_cast<uint64_t>(simple_stmt.size())
    );
    for (auto* it : simple_stmt) {
      stmts.Push(visitSimple_stmt(it).as<Ast::INodePtr>());
    }
    return Object::CreatePyList(stmts);
  }
  return nullptr;
}

antlrcpp::Any Generator::visitReturn_stmt(Python3Parser::Return_stmtContext* ctx
) {
  return Ast::CreateReturnStmt(visitTestlist(ctx->testlist()), context);
}

antlrcpp::Any Generator::visitTestlist(Python3Parser::TestlistContext* ctx) {
  return visitTest(ctx->test(0));
}

antlrcpp::Any Generator::visitParameters(Python3Parser::ParametersContext* ctx
) {
  if (ctx->typedargslist() != nullptr) {
    return visitTypedargslist(ctx->typedargslist());
  }
  return Object::CreatePyList({});
}

antlrcpp::Any Generator::visitTypedargslist(
  Python3Parser::TypedargslistContext* ctx
) {
  auto tfpdef = ctx->tfpdef();
  Collections::List<Object::PyObjPtr> args(static_cast<uint64_t>(tfpdef.size())
  );
  for (auto* it : tfpdef) {
    args.Push(Object::CreatePyString(it->getText().c_str()));
  }
  return Object::CreatePyList(args);
}

antlrcpp::Any Generator::visitTfpdef(Python3Parser::TfpdefContext* ctx) {
  return Object::CreatePyString(ctx->getText().c_str());
}

antlrcpp::Any Generator::visitIf_stmt(Python3Parser::If_stmtContext* ctx) {
  auto condition = visitTest(ctx->test(0)).as<Ast::INodePtr>();
  auto thenStmts = visitBlock(ctx->block(0)).as<Object::PyObjPtr>();
  auto ifStmt = Ast::CreateIfStmt(condition, thenStmts, context);
  return ifStmt;
}

antlrcpp::Any Generator::visitWhile_stmt(Python3Parser::While_stmtContext* ctx
) {
  auto condition = visitTest(ctx->test()).as<Ast::INodePtr>();
  auto body = visitBlock(ctx->block(0)).as<Object::PyObjPtr>();
  return Ast::CreateWhileStmt(condition, body, context);
}

antlrcpp::Any Generator::visitSubscriptlist(
  Python3Parser::SubscriptlistContext* ctx
) {
  if (ctx->subscript_().size() == 1) {
    return visitSubscript_(ctx->subscript_(0));
  }
  Collections::List<Object::PyObjPtr> subscripts(
    static_cast<uint64_t>(ctx->subscript_().size())
  );
  for (auto* it : ctx->subscript_()) {
    subscripts.Push(visitSubscript_(it).as<Object::PyObjPtr>());
  }
  return Ast::CreateAtom(Object::CreatePyList(subscripts), context);
}

antlrcpp::Any Generator::visitSubscript_(Python3Parser::Subscript_Context* ctx
) {
  if (ctx->test().size() == 1) {
    return visitTest(ctx->test(0));
  }
  return nullptr;
}

antlrcpp::Any Generator::visitFor_stmt(Python3Parser::For_stmtContext* ctx) {
  auto target = visitExprlist(ctx->exprlist()).as<Ast::INodePtr>();
  auto iter = visitTestlist(ctx->testlist()).as<Ast::INodePtr>();
  auto body = visitBlock(ctx->block(0)).as<Object::PyObjPtr>();
  return Ast::CreateForStmt(target, iter, body, context);
}

antlrcpp::Any Generator::visitExprlist(Python3Parser::ExprlistContext* ctx) {
  return visitExpr(ctx->expr(0));
}

antlrcpp::Any Generator::visitClassdef(Python3Parser::ClassdefContext* ctx) {
  auto className = Object::CreatePyString(ctx->name()->getText().c_str());
  auto bases = Object::CreatePyList({});
  auto classDef = std::dynamic_pointer_cast<Ast::ClassDef>(
    Ast::CreateClassDef(className, bases, context)
  );
  auto oldContext = context;
  context = classDef;
  auto body = visitBlock(ctx->block()).as<Object::PyObjPtr>();
  classDef->SetBody(body);
  context = oldContext;
  return std::dynamic_pointer_cast<Ast::INode>(classDef);
}

}  // namespace torchlight::Generation