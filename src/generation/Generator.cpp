

#include "generation/Generator.h"

#include "ByteCode/PyCode.h"
#include "ByteCode/PyInst.h"
#include "Collections/IntegerHelper.h"
#include "Collections/Iterator.h"
#include "Common.h"
#include "Generation/Expression.h"
#include "Object/Common.h"
#include "Object/ObjectHelper.h"
#include "Object/PyBoolean.h"
#include "Object/PyInteger.h"
#include "Object/PyList.h"
#include "Object/PyNone.h"
#include "Object/PyObject.h"
#include "Object/PyString.h"
#include "support/Any.h"

#include <utility>
#include <variant>

namespace torchlight::Generation {

Generator::Generator(Object::PyObjPtr filename)
  : filename(std::move(filename)) {
  consts = Object::CreatePyList({Object::CreatePyNone()});
  names = Object::CreatePyList({});
  instructions = Object::CreatePyList({});
}

Object::PyObjPtr Generator::Generate() {
  Index nLocals = 0;
  Object::DebugPrint(instructions);
  return std::make_shared<Object::PyCode>(
    instructions->_serialize_(), consts, names, Object::CreatePyList({}),
    filename, nLocals
  );
}

antlrcpp::Any Generator::visitFile_input(Python3Parser::File_inputContext* ctx
) {
  visitChildren(ctx);
  return nullptr;
}

antlrcpp::Any Generator::visitTestlist_comp(
  Python3Parser::Testlist_compContext* ctx
) {
  auto testlist = ctx->test();
  Collections::List<Expr> tests(static_cast<uint64_t>(testlist.size()));
  for (auto& test : testlist) {
    tests.Push(visitTest(test).as<Expr>());
  }
  return CreateList(tests);
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
    auto testlist_comp = visitTestlist_comp(ctx->testlist_comp()).as<Expr>();
    if (std::holds_alternative<List>(testlist_comp->kind)) {
      auto list = std::get<List>(testlist_comp->kind);
      return CreateAtomList(list);
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
    return CreateIdentifier(Object::CreatePyString(ctx->name()->getText().c_str(
    )));
    // visitName(ctx->name());
  } else if (ctx->NUMBER() != nullptr) {
    // 情况 5: NUMBER
    return CreateAtom(Object::CreatePyInteger(
      Collections::CreateIntegerWithCString(ctx->NUMBER()->getText().c_str())
    ));
  } else if (!ctx->STRING().empty()) {
    // 情况 6: STRING+
    Object::PyObjPtr str = Object::CreatePyString("");
    for (auto* string : ctx->STRING()) {
      auto rawString = string->getText();
      rawString = rawString.substr(1, rawString.size() - 2);
      str = str->add(Object::CreatePyString(rawString));
    }
    return CreateAtom(str);
  } else if (ctx->ELLIPSIS() != nullptr) {
    // 情况 7: '...'
    std::cout << "atom: '...'" << std::endl;
  } else if (ctx->NONE() != nullptr) {
    // 情况 8: 'None'
    return CreateAtom(Object::CreatePyNone());
  } else if (ctx->TRUE() != nullptr) {
    // 情况 9: 'True'
    return CreateAtom(Object::CreatePyBoolean(true));
  } else if (ctx->FALSE() != nullptr) {
    // 情况 10: 'False'
    return CreateAtom(Object::CreatePyBoolean(false));
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
    return isStar  ? CreateBinary(BinaryOperator::MUL, left, right)
           : isAt  ? CreateBinary(BinaryOperator::MATMUL, left, right)
           : isDiv ? CreateBinary(BinaryOperator::DIV, left, right)
           : isMod ? CreateBinary(BinaryOperator::MOD, left, right)
                   : CreateBinary(BinaryOperator::FLOOR_DIV, left, right);
  } else if (ctx->expr().size() == 2 &&
             (ctx->ADD().size() == 1 || ctx->MINUS().size() == 1)) {
    // 情况 5: expr ('+' | '-') expr
    bool isAdd = (ctx->ADD().size() == 1);
    bool isMinus = (ctx->MINUS().size() == 1);
    auto left = visitExpr(ctx->expr(0));
    auto right = visitExpr(ctx->expr(1));
    return isAdd ? CreateBinary(BinaryOperator::ADD, left, right)
                 : CreateBinary(BinaryOperator::SUB, left, right);
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
    return visitAnnassign(ctx->annassign());
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
    auto rvalue =
      visitTestlist_star_expr(ctx->testlist_star_expr(1)).as<Expr>();
    // Atom Binary Unary
    CodegenExpr(rvalue, consts, names, instructions);
    auto lvalue =
      visitTestlist_star_expr(ctx->testlist_star_expr(0)).as<Expr>();
    auto identifier = std::get<Identifier>(lvalue->kind);
    StoreName(identifier.name, names, instructions);
    // 遍历所有赋值右侧的表达式
    // for (auto* exprIt : ctx->testlist_star_expr()) {
    //   auto expr = visitTestlist_star_expr(exprIt).as<Object::PyObjPtr>();
    // }
  }

  // 处理只有 testlist_star_expr 的情况
  if (ctx->ASSIGN().empty()) {
    auto expr_stmt =
      visitTestlist_star_expr(ctx->testlist_star_expr(0)).as<Expr>();
    auto call = std::get<FunctionCall>(expr_stmt->kind);
    auto args = call.arguments;
    CodegenFunctionCall(call, consts, names, instructions);
    return nullptr;
  }

  return nullptr;
}

antlrcpp::Any Generator::visitArglist(Python3Parser::ArglistContext* ctx) {
  auto arglist = ctx->argument();
  Collections::List<Expr> args(static_cast<uint64_t>(arglist.size()));
  for (auto& arg : arglist) {
    args.Push(visitArgument(arg).as<Expr>());
  }
  return CreateList(args);
}

antlrcpp::Any Generator::visitArgument(Python3Parser::ArgumentContext* ctx) {
  return visitTest(ctx->test(0));
}

antlrcpp::Any Generator::visitTrailer(Python3Parser::TrailerContext* ctx) {
  if (ctx->OPEN_PAREN() != nullptr) {
    if (ctx->arglist() != nullptr) {
      return visitArglist(ctx->arglist());
    }
    return CreateList(Collections::List<Expr>({}));
  } else if (ctx->OPEN_BRACK() != nullptr) {
    // 情况 2: '[' subscriptlist ']'
    std::cout << "trailer: '[' subscriptlist ']'" << std::endl;
    // if (ctx->subscriptlist() != nullptr) {
    //   visitSubscriptlist(ctx->subscriptlist());
    // }
  } else if (ctx->DOT() != nullptr) {
    return CreateIdentifier(
      Object::CreatePyString(ctx->name()->NAME()->getText().c_str())
    );
  } else {
    // 其他情况
    std::cout << "trailer: Unknown type" << std::endl;
  }
  return nullptr;
}

antlrcpp::Any Generator::visitAtom_expr(Python3Parser::Atom_exprContext* ctx) {
  if (ctx->trailer().empty()) {
    if (ctx->atom() != nullptr) {
      return visitAtom(ctx->atom());
    }
    return nullptr;
  }
  auto atom = visitAtom(ctx->atom()).as<Expr>();
  auto identifier = std::get<Identifier>(atom->kind);
  Collections::List<Expr> trailer(static_cast<uint64_t>(ctx->trailer().size()));
  for (auto* trailerIt : ctx->trailer()) {
    trailer.Push(visitTrailer(trailerIt).as<Expr>());
  }
  Expr result = atom;
  for (auto it = Collections::Iterator<Expr>::Begin(trailer); !it.End();
       it.Next()) {
    if (std::holds_alternative<List>(it.Get()->kind)) {
      result = CreateFunctionCall(result, std::get<List>(it.Get()->kind));
    } else if (std::holds_alternative<Identifier>(it.Get()->kind)) {
      result = CreateMemberAccess(result, std::get<Identifier>(it.Get()->kind));
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
  return visitExpr(ctx->expr(0));
}

void LoadConst(
  const Object::PyObjPtr& obj,
  const Object::PyObjPtr& consts,
  const Object::PyObjPtr& instructions
) {
  auto index = IndexOfConst(obj, consts);

  Object::Invoke(
    instructions, Object::CreatePyString("append"),
    {Object::CreateLoadConst(Object::ToU64(index))}
  );
}

void LoadName(
  const Object::PyObjPtr& name,
  const Object::PyObjPtr& names,
  const Object::PyObjPtr& instructions
) {
  auto index = IndexOfName(name, names);

  Object::Invoke(
    instructions, Object::CreatePyString("append"),
    {Object::CreateLoadName(Object::ToU64(index))}
  );
}

void StoreName(
  const Object::PyObjPtr& name,
  const Object::PyObjPtr& names,
  const Object::PyObjPtr& instructions
) {
  auto index = IndexOfName(name, names);

  Object::Invoke(
    instructions, Object::CreatePyString("append"),
    {Object::CreateStoreName(Object::ToU64(index))}
  );
}

void CallFunction(Index argumentSize, const Object::PyObjPtr& instructions) {
  Object::Invoke(
    instructions, Object::CreatePyString("append"),
    {Object::CreateCallFunction(argumentSize)}
  );
}

Object::PyObjPtr
IndexOfConst(const Object::PyObjPtr& obj, const Object::PyObjPtr& consts) {
  if (!Object::IsTrue(consts->contains(obj))) {
    Object::Invoke(consts, Object::CreatePyString("append"), {obj});
  }
  return Object::Invoke(consts, Object::CreatePyString("index"), {obj});
}

Object::PyObjPtr
IndexOfName(const Object::PyObjPtr& name, const Object::PyObjPtr& names) {
  if (!Object::IsTrue(names->contains(name))) {
    Object::Invoke(names, Object::CreatePyString("append"), {name});
  }
  return Object::Invoke(names, Object::CreatePyString("index"), {name});
}

void CodegenList(
  const List& list,
  const Object::PyObjPtr& consts,
  const Object::PyObjPtr& names,
  const Object::PyObjPtr& instructions
) {
  for (auto it = Collections::Iterator<Expr>::Begin(list.elements); !it.End();
       it.Next()) {
    CodegenExpr(it.Get(), consts, names, instructions);
  }
}

void CodegenIdentifier(
  const Identifier& identifier,
  const Object::PyObjPtr& names,
  const Object::PyObjPtr& instructions
) {
  LoadName(identifier.name, names, instructions);
}

void CodegenFunctionCall(
  const FunctionCall& call,
  const Object::PyObjPtr& consts,
  const Object::PyObjPtr& names,
  const Object::PyObjPtr& instructions
) {
  CodegenExpr(call.functionName, consts, names, instructions);
  CodegenList(call.arguments, consts, names, instructions);
  CallFunction(call.arguments.elements.Size(), instructions);
}

void CodegenUnary(
  const Unary& unary,
  const Object::PyObjPtr& consts,
  const Object::PyObjPtr& names,
  const Object::PyObjPtr& instructions
) {
  std::cout << "Unary: " << std::endl;
}

void CodegenBinary(
  const Binary& binary,
  const Object::PyObjPtr& consts,
  const Object::PyObjPtr& names,
  const Object::PyObjPtr& instructions
) {
  CodegenExpr(binary.left, consts, names, instructions);
  CodegenExpr(binary.right, consts, names, instructions);
  Object::PyInstPtr inst = nullptr;
  switch (binary.oprt) {
    case BinaryOperator::ADD:
      inst = Object::CreateBinaryAdd();
      break;
    case BinaryOperator::SUB:
      inst = Object::CreateBinarySubtract();
      break;
    case BinaryOperator::MUL:
      inst = Object::CreateBinaryMultiply();
      break;
    default:
      break;
  }
  Object::Invoke(instructions, Object::CreatePyString("append"), {inst});
}

void CodegenAtom(
  const Atom& atom,
  const Object::PyObjPtr& consts,
  const Object::PyObjPtr& instructions
) {
  LoadConst(atom.obj, consts, instructions);
}

void CodegenExpr(
  const Expr& expr,
  const Object::PyObjPtr& consts,
  const Object::PyObjPtr& names,
  const Object::PyObjPtr& instructions
) {
  std::visit(
    overload{
      [consts, names, instructions](const Atom& atom) {
        CodegenAtom(atom, consts, instructions);
      },
      [consts, names, instructions](const Binary& binary) {
        CodegenBinary(binary, consts, names, instructions);
      },
      [consts, names, instructions](const Unary& unary) {
        CodegenUnary(unary, consts, names, instructions);
      },
      [consts, names, instructions](const FunctionCall& call) {
        CodegenFunctionCall(call, consts, names, instructions);
      },
      [consts, names, instructions](const Identifier& identifier) {
        CodegenIdentifier(identifier, names, instructions);
      },
      [consts, names, instructions](const List& list) {
        CodegenList(list, consts, names, instructions);
      },
      [consts, names, instructions](const MemberAccess& memberAccess) {
        CodegenMemberAccess(memberAccess, consts, names, instructions);
      },
      [consts, names, instructions](const AtomList& atomList) {
        CodegenAtomList(atomList, consts, names, instructions);
      },
    },
    expr->kind
  );
}

void CodegenMemberAccess(
  const MemberAccess& memberAccess,
  const Object::PyObjPtr& consts,
  const Object::PyObjPtr& names,
  const Object::PyObjPtr& instructions
) {
  CodegenExpr(memberAccess.object, consts, names, instructions);
  LoadAttr(memberAccess.attribute.name, names, instructions);
}

void LoadAttr(
  const Object::PyObjPtr& attribute,
  const Object::PyObjPtr& names,
  const Object::PyObjPtr& instructions
) {
  auto index = IndexOfName(attribute, names);
  Object::Invoke(
    instructions, Object::CreatePyString("append"),
    {Object::CreateLoadAttr(Object::ToU64(index))}
  );
}

void BuildList(Index size, const Object::PyObjPtr& instructions) {
  Object::Invoke(
    instructions, Object::CreatePyString("append"),
    {Object::CreateBuildList(size)}
  );
}

void CodegenAtomList(
  const AtomList& atomList,
  const Object::PyObjPtr& consts,
  const Object::PyObjPtr& names,
  const Object::PyObjPtr& instructions
) {
  for (auto it = Collections::Iterator<Expr>::Begin(atomList.elements);
       !it.End(); it.Next()) {
    CodegenExpr(it.Get(), consts, names, instructions);
  }
  BuildList(atomList.elements.Size(), instructions);
}

}  // namespace torchlight::Generation