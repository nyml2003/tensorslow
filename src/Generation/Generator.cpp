#include "Generation/Generator.h"
#include "Ast/AssignStmt.h"
#include "Ast/ClassDef.h"
#include "Ast/Expression/Atom.h"
#include "Ast/Expression/Binary.h"
#include "Ast/Expression/FunctionCall.h"
#include "Ast/Expression/List.h"
#include "Ast/Expression/Slice.h"
#include "Ast/Expression/Unary.h"
#include "Ast/FuncDef.h"
#include "Ast/INode.h"
#include "Ast/Identifier.h"
#include "Ast/MemberAccess.h"
#include "Ast/Module.h"
#include "Ast/Statement/ExprStmt.h"
#include "Ast/Statement/ForStmt.h"
#include "Ast/Statement/IfStmt.h"
#include "Ast/Statement/PassStmt.h"
#include "Ast/Statement/ReturnStmt.h"
#include "Ast/Statement/WhileStmt.h"
#include "ByteCode/PyCode.h"
#include "Collections/IntegerHelper.h"
#include "Object/Object.h"
#include "Object/ObjectHelper.h"
#include "Object/PyBoolean.h"
#include "Object/PyFloat.h"
#include "Object/PyInteger.h"
#include "Object/PyList.h"
#include "Object/PyNone.h"
#include "Object/PyObject.h"
#include "Object/PyString.h"
#include "support/Any.h"

namespace torchlight::Generation {

Generator::Generator(const Object::PyObjPtr& filename) {
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
  if (ctx->simple_stmts() != nullptr) {
    return visitSimple_stmts(ctx->simple_stmts()).as<Object::PyObjPtr>();
  }
  if (ctx->compound_stmt() != nullptr) {
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
  for (auto* stmtItertor : stmts) {
    auto stmt = visitStmt(stmtItertor);
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
  for (auto* test : testlist) {
    tests.Push(visitTest(test).as<Ast::INodePtr>());
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
    return visitAtom_expr(ctx->atom_expr());
  }
  auto exprs = ctx->expr();
  if (exprs.size() == 1) {
    auto operand = visitExpr(ctx->expr(0)).as<Ast::INodePtr>();
    if (ctx->ADD().size() == 1) {
      return Ast::CreateUnary(Ast::Unary::Operator::PLUS, operand, context);
    }
    if (ctx->MINUS().size() == 1) {
      return Ast::CreateUnary(Ast::Unary::Operator::MINUS, operand, context);
    }
    if (ctx->NOT_OP().size() == 1) {
      return Ast::CreateUnary(Ast::Unary::Operator::INVERT, operand, context);
    }
  }
  if (exprs.size() == 2) {
    auto left = visitExpr(ctx->expr(0)).as<Ast::INodePtr>();
    auto right = visitExpr(ctx->expr(1)).as<Ast::INodePtr>();
    if (ctx->STAR() != nullptr) {
      return Ast::CreateBinary(
        Ast::Binary::Operator::MUL, left, right, context
      );
    }
    if (ctx->POWER() != nullptr) {
      return Ast::CreateBinary(
        Ast::Binary::Operator::POWER, left, right, context
      );
    }
    if (ctx->AT() != nullptr) {
      return Ast::CreateBinary(
        Ast::Binary::Operator::MATMUL, left, right, context
      );
    }
    if (ctx->DIV() != nullptr) {
      return Ast::CreateBinary(
        Ast::Binary::Operator::DIV, left, right, context
      );
    }
    if (ctx->MOD() != nullptr) {
      return Ast::CreateBinary(
        Ast::Binary::Operator::MOD, left, right, context
      );
    }
    if (ctx->IDIV() != nullptr) {
      return Ast::CreateBinary(
        Ast::Binary::Operator::FLOOR_DIV, left, right, context
      );
    }
    if (ctx->ADD().size() == 1) {
      return Ast::CreateBinary(
        Ast::Binary::Operator::ADD, left, right, context
      );
    }
    if (ctx->MINUS().size() == 1) {
      return Ast::CreateBinary(
        Ast::Binary::Operator::SUB, left, right, context
      );
    }
    if (ctx->LEFT_SHIFT() != nullptr) {
      return Ast::CreateBinary(
        Ast::Binary::Operator::LSHIFT, left, right, context
      );
    }
    if (ctx->RIGHT_SHIFT() != nullptr) {
      return Ast::CreateBinary(
        Ast::Binary::Operator::RSHIFT, left, right, context
      );
    }
    if (ctx->AND_OP() != nullptr) {
      return Ast::CreateBinary(
        Ast::Binary::Operator::AND, left, right, context
      );
    }
    if (ctx->XOR() != nullptr) {
      return Ast::CreateBinary(
        Ast::Binary::Operator::XOR, left, right, context
      );
    }
    if (ctx->OR_OP() != nullptr) {
      return Ast::CreateBinary(Ast::Binary::Operator::OR, left, right, context);
    }
  }
  throw std::runtime_error("Unknown expression type");
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
    auto target =
      visitTestlist_star_expr(ctx->testlist_star_expr(0)).as<Ast::INodePtr>();
    auto source = visitTestlist(ctx->testlist()).as<Ast::INodePtr>();
    if (ctx->augassign()->ADD_ASSIGN() != nullptr) {
      return Ast::CreateAssignStmt(
        target,
        Ast::CreateBinary(Ast::Binary::Operator::ADD, target, source, context),
        context
      );
    }
    if (ctx->augassign()->SUB_ASSIGN() != nullptr) {
      return Ast::CreateAssignStmt(
        target,
        Ast::CreateBinary(Ast::Binary::Operator::SUB, target, source, context),
        context
      );
    }
    if (ctx->augassign()->MULT_ASSIGN() != nullptr) {
      return Ast::CreateAssignStmt(
        target,
        Ast::CreateBinary(Ast::Binary::Operator::MUL, target, source, context),
        context
      );
    }
    if (ctx->augassign()->AT_ASSIGN() != nullptr) {
      return Ast::CreateAssignStmt(
        target,
        Ast::CreateBinary(
          Ast::Binary::Operator::MATMUL, target, source, context
        ),
        context
      );
    }
    if (ctx->augassign()->DIV_ASSIGN() != nullptr) {
      return Ast::CreateAssignStmt(
        target,
        Ast::CreateBinary(Ast::Binary::Operator::DIV, target, source, context),
        context
      );
    }
    if (ctx->augassign()->MOD_ASSIGN() != nullptr) {
      return Ast::CreateAssignStmt(
        target,
        Ast::CreateBinary(Ast::Binary::Operator::MOD, target, source, context),
        context
      );
    }
    if (ctx->augassign()->AND_ASSIGN() != nullptr) {
      return Ast::CreateAssignStmt(
        target,
        Ast::CreateBinary(Ast::Binary::Operator::AND, target, source, context),
        context
      );
    }
    if (ctx->augassign()->OR_ASSIGN() != nullptr) {
      return Ast::CreateAssignStmt(
        target,
        Ast::CreateBinary(Ast::Binary::Operator::OR, target, source, context),
        context
      );
    }
    if (ctx->augassign()->XOR_ASSIGN() != nullptr) {
      return Ast::CreateAssignStmt(
        target,
        Ast::CreateBinary(Ast::Binary::Operator::XOR, target, source, context),
        context
      );
    }
    if (ctx->augassign()->LEFT_SHIFT_ASSIGN() != nullptr) {
      return Ast::CreateAssignStmt(
        target,
        Ast::CreateBinary(
          Ast::Binary::Operator::LSHIFT, target, source, context
        ),
        context
      );
    }
    if (ctx->augassign()->RIGHT_SHIFT_ASSIGN() != nullptr) {
      return Ast::CreateAssignStmt(
        target,
        Ast::CreateBinary(
          Ast::Binary::Operator::RSHIFT, target, source, context
        ),
        context
      );
    }
    if (ctx->augassign()->POWER_ASSIGN() != nullptr) {
      return Ast::CreateAssignStmt(
        target,
        Ast::CreateBinary(
          Ast::Binary::Operator::POWER, target, source, context
        ),
        context
      );
    }
    if (ctx->augassign()->IDIV_ASSIGN() != nullptr) {
      return Ast::CreateAssignStmt(
        target,
        Ast::CreateBinary(
          Ast::Binary::Operator::FLOOR_DIV, target, source, context
        ),
        context
      );
    }
  }

  // 处理普通赋值或多重赋值
  if (!ctx->ASSIGN().empty()) {
    auto source =
      visitTestlist_star_expr(ctx->testlist_star_expr(1)).as<Ast::INodePtr>();
    auto target =
      visitTestlist_star_expr(ctx->testlist_star_expr(0)).as<Ast::INodePtr>();
    return Ast::CreateAssignStmt(target, source, context);
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
  if (ctx->argument().empty()) {
    return Object::CreatePyList({})->as<Object::PyList>();
  }
  auto arglist = ctx->argument();
  Collections::List<Object::PyObjPtr> args(static_cast<uint64_t>(arglist.size())
  );
  for (auto* arg : arglist) {
    args.Push(visitArgument(arg).as<Ast::INodePtr>());
  }
  return Object::CreatePyList(args)->as<Object::PyList>();
}

antlrcpp::Any Generator::visitArgument(Python3Parser::ArgumentContext* ctx) {
  return visitTest(ctx->test(0));
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
      if (trailer->arglist() == nullptr) {
        result = Ast::CreateFunctionCall(
          result, Object::CreatePyList({})->as<Object::PyList>(), context
        );
      } else {
        auto args = visitArglist(trailer->arglist()).as<Object::PyListPtr>();
        result = Ast::CreateFunctionCall(result, args, context);
      }
    } else if (trailer->OPEN_BRACK() != nullptr) {  // '['
      auto args = visitSubscriptlist(trailer->subscriptlist());
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
  auto andTests = ctx->and_test();
  auto left = visitAnd_test(andTests[0]);
  if (andTests.size() == 1) {
    return left;
  }
  Ast::INodePtr right = nullptr;
  for (Index i = 1; i < andTests.size(); ++i) {
    right = visitAnd_test(andTests[i]);
    left = Ast::CreateBinary(Ast::Binary::Operator::OR, left, right, context);
  }
  return left;
}

antlrcpp::Any Generator::visitAnd_test(Python3Parser::And_testContext* ctx) {
  auto notTests = ctx->not_test();
  auto left = visitNot_test(notTests[0]);
  if (notTests.size() == 1) {
    return left;
  }
  Ast::INodePtr right = nullptr;
  for (Index i = 1; i < notTests.size(); ++i) {
    right = visitNot_test(notTests[i]);
    left = Ast::CreateBinary(Ast::Binary::Operator::AND, left, right, context);
  }
  return left;
}

antlrcpp::Any Generator::visitNot_test(Python3Parser::Not_testContext* ctx) {
  if (ctx->comparison() != nullptr) {
    return visitComparison(ctx->comparison());
  }
  if (ctx->NOT() != nullptr) {
    auto operand = visitNot_test(ctx->not_test()).as<Ast::INodePtr>();
    return Ast::CreateUnary(Ast::Unary::Operator::NOT, operand, context);
  }
  throw std::runtime_error("visitNot_test: Unknown type");
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
  if (ctx->if_stmt() != nullptr) {
    return visitIf_stmt(ctx->if_stmt());
  }
  // 2. 如果是 while_stmt
  if (ctx->while_stmt() != nullptr) {
    return visitWhile_stmt(ctx->while_stmt());
  }
  // 3. 如果是 for_stmt
  if (ctx->for_stmt() != nullptr) {
    return visitFor_stmt(ctx->for_stmt());
  }
  // 4. 如果是 try_stmt
  if (ctx->try_stmt() != nullptr) {
    return visitTry_stmt(ctx->try_stmt());
  }
  // 5. 如果是 with_stmt
  if (ctx->with_stmt() != nullptr) {
    return visitWith_stmt(ctx->with_stmt());
  }
  // 6. 如果是 funcdef
  if (ctx->funcdef() != nullptr) {
    return visitFuncdef(ctx->funcdef()).as<Ast::INodePtr>();
  }
  // 7. 如果是 classdef
  if (ctx->classdef() != nullptr) {
    return visitClassdef(ctx->classdef()).as<Ast::INodePtr>();
  }
  // 8. 如果是 decorated
  if (ctx->decorated() != nullptr) {
    return visitDecorated(ctx->decorated());
  }
  // 9. 如果是 async_stmt
  if (ctx->async_stmt() != nullptr) {
    return visitAsync_stmt(ctx->async_stmt());
  }
  // 10. 如果是 match_stmt
  if (ctx->match_stmt() != nullptr) {
    return visitMatch_stmt(ctx->match_stmt());
  }
  // 其他情况（不应该出现）

  std::cerr << "visitCompound_stmt: Unknown compound statement type"
            << std::endl;
  return nullptr;
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
    for (auto* statement : statements) {
      auto stmt = visitStmt(statement);
      if (stmt.is<Object::PyObjPtr>()) {
        Object::ForEach(
          stmt.as<Object::PyObjPtr>()->as<Object::PyList>(),
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
    for (auto* stmt : simple_stmt) {
      stmts.Push(visitSimple_stmt(stmt).as<Ast::INodePtr>());
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
  for (auto* def : tfpdef) {
    args.Push(Object::CreatePyString(def->getText().c_str()));
  }
  return Object::CreatePyList(args);
}

antlrcpp::Any Generator::visitTfpdef(Python3Parser::TfpdefContext* ctx) {
  return Object::CreatePyString(ctx->getText().c_str());
}

antlrcpp::Any Generator::visitIf_stmt(Python3Parser::If_stmtContext* ctx) {
  auto condition = visitTest(ctx->test(0)).as<Ast::INodePtr>();
  auto thenStmts =
    visitBlock(ctx->block(0)).as<Object::PyObjPtr>()->as<Object::PyList>();
  Object::PyListPtr elseStmts = Object::CreatePyList({})->as<Object::PyList>();
  Object::PyListPtr elseIfStmts =
    Object::CreatePyList({})->as<Object::PyList>();
  Object::PyListPtr elseIfConditions =
    Object::CreatePyList({})->as<Object::PyList>();
  size_t elseifCount = ctx->ELIF().size();
  bool hasElse = ctx->ELSE() != nullptr;
  if (elseifCount > 0) {
    for (size_t i = 0; i < elseifCount; ++i) {
      auto elseIfCondition = visitTest(ctx->test(i + 1)).as<Ast::INodePtr>();
      elseIfConditions->Append(elseIfCondition);
      auto block = visitBlock(ctx->block(i + 1))
                     .as<Object::PyObjPtr>()
                     ->as<Object::PyList>();
      elseIfStmts->Append(block);
    }
  }
  if (hasElse) {
    elseStmts = visitBlock(ctx->block(elseifCount + 1))
                  .as<Object::PyObjPtr>()
                  ->as<Object::PyList>();
  }

  auto ifStmt = Ast::CreateIfStmt(
    condition, thenStmts, elseStmts, elseIfStmts, elseIfConditions, context
  );
  return ifStmt;
}

antlrcpp::Any Generator::visitWhile_stmt(Python3Parser::While_stmtContext* ctx
) {
  auto condition = visitTest(ctx->test()).as<Ast::INodePtr>();
  auto body = visitBlock(ctx->block(0)).as<Object::PyObjPtr>();
  return Ast::CreateWhileStmt(condition, body, context);
}

// 返回一个INodePtr
antlrcpp::Any Generator::visitSubscriptlist(
  Python3Parser::SubscriptlistContext* ctx
) {
  if (ctx->subscript_().size() == 1) {
    return visitSubscript_(ctx->subscript_(0)).as<Ast::INodePtr>();
  }
  Collections::List<Object::PyObjPtr> subscripts(
    static_cast<uint64_t>(ctx->subscript_().size())
  );
  for (auto* subscript : ctx->subscript_()) {
    subscripts.Push(visitSubscript_(subscript));
  }
  return Ast::CreateList(Object::CreatePyList(subscripts), context);
}

antlrcpp::Any Generator::visitSubscript_(Python3Parser::Subscript_Context* ctx
) {
  if (ctx->COLON() == nullptr) {
    return visitTest(ctx->test(0)).as<Ast::INodePtr>();
  }
  auto none = Ast::CreateAtom(Object::CreatePyNone(), context);
  auto step = none;
  if (ctx->sliceop() != nullptr) {
    step = visitTest(ctx->sliceop()->test()).as<Ast::INodePtr>();
  }
  // 存在冒号
  // 如果只有一个test
  // 判断是左边界还是右边界
  if (ctx->test().size() == 1) {
    auto* test = ctx->test(0);
    auto* colon = ctx->COLON();
    auto value = visitTest(test).as<Ast::INodePtr>();
    if (colon->getSymbol()->getTokenIndex() <
        test->getStart()->getTokenIndex()) {
      return Ast::CreateSlice(
        Object::CreatePyList({none, value, step})->as<Object::PyList>(), context
      );
    }
    return Ast::CreateSlice(
      Object::CreatePyList({value, none, step})->as<Object::PyList>(), context
    );
  }
  if (ctx->test().size() == 2) {
    auto start = visitTest(ctx->test(0)).as<Ast::INodePtr>();
    auto stop = visitTest(ctx->test(1)).as<Ast::INodePtr>();
    return Ast::CreateSlice(
      Object::CreatePyList({start, stop, step})->as<Object::PyList>(), context
    );
  }
  return Ast::CreateSlice(
    Object::CreatePyList({none, none, step})->as<Object::PyList>(), context
  );

  std::cerr << "visitSubscript_: Unknown type" << std::endl;
  std::cout << ctx->getText() << std::endl;
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

  auto bases = Object::CreatePyList({})->as<Object::PyList>();
  if (ctx->arglist() != nullptr) {
    bases = visitArglist(ctx->arglist()).as<Object::PyListPtr>();
  }
  if (bases->Length() == 0) {
    bases->Append(
      Ast::CreateIdentifier(Object::CreatePyString("object"), context)
    );
  }
  auto classDef = std::dynamic_pointer_cast<Ast::ClassDef>(
    Ast::CreateClassDef(className, Ast::CreateList(bases, context), context)
  );
  auto oldContext = context;
  context = classDef;
  auto body = visitBlock(ctx->block()).as<Object::PyObjPtr>();
  classDef->SetBody(body);
  context = oldContext;
  return std::dynamic_pointer_cast<Ast::INode>(classDef);
}

antlrcpp::Any
Generator::visitPass_stmt(Python3Parser::Pass_stmtContext* /*ctx*/) {
  return Ast::CreatePassStmt(context);
}

}  // namespace torchlight::Generation