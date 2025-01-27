#include "Python3ParserBase.h"

// Generated from /app/grammar/Python3Parser.g4 by ANTLR 4.9.2

#pragma once


#include "antlr4-runtime.h"
#include "Python3ParserVisitor.h"


/**
 * This class provides an empty implementation of Python3ParserVisitor, which can be
 * extended to create a visitor which only needs to handle a subset of the available methods.
 */
class  Python3ParserBaseVisitor : public Python3ParserVisitor {
public:

  virtual antlrcpp::Any visitSingle_input(Python3Parser::Single_inputContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitFile_input(Python3Parser::File_inputContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitEval_input(Python3Parser::Eval_inputContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitDecorator(Python3Parser::DecoratorContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitDecorators(Python3Parser::DecoratorsContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitDecorated(Python3Parser::DecoratedContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitAsync_funcdef(Python3Parser::Async_funcdefContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitFuncdef(Python3Parser::FuncdefContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitParameters(Python3Parser::ParametersContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitTypedargslist(Python3Parser::TypedargslistContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitTfpdef(Python3Parser::TfpdefContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitVarargslist(Python3Parser::VarargslistContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitVfpdef(Python3Parser::VfpdefContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitStmt(Python3Parser::StmtContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitSimple_stmts(Python3Parser::Simple_stmtsContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitSimple_stmt(Python3Parser::Simple_stmtContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitExpr_stmt(Python3Parser::Expr_stmtContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitAnnassign(Python3Parser::AnnassignContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitTestlist_star_expr(Python3Parser::Testlist_star_exprContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitAugassign(Python3Parser::AugassignContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitDel_stmt(Python3Parser::Del_stmtContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitPass_stmt(Python3Parser::Pass_stmtContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitFlow_stmt(Python3Parser::Flow_stmtContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitBreak_stmt(Python3Parser::Break_stmtContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitContinue_stmt(Python3Parser::Continue_stmtContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitReturn_stmt(Python3Parser::Return_stmtContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitYield_stmt(Python3Parser::Yield_stmtContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitRaise_stmt(Python3Parser::Raise_stmtContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitImport_stmt(Python3Parser::Import_stmtContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitImport_name(Python3Parser::Import_nameContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitImport_from(Python3Parser::Import_fromContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitImport_as_name(Python3Parser::Import_as_nameContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitDotted_as_name(Python3Parser::Dotted_as_nameContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitImport_as_names(Python3Parser::Import_as_namesContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitDotted_as_names(Python3Parser::Dotted_as_namesContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitDotted_name(Python3Parser::Dotted_nameContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitGlobal_stmt(Python3Parser::Global_stmtContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitNonlocal_stmt(Python3Parser::Nonlocal_stmtContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitAssert_stmt(Python3Parser::Assert_stmtContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitCompound_stmt(Python3Parser::Compound_stmtContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitAsync_stmt(Python3Parser::Async_stmtContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitIf_stmt(Python3Parser::If_stmtContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitWhile_stmt(Python3Parser::While_stmtContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitFor_stmt(Python3Parser::For_stmtContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitTry_stmt(Python3Parser::Try_stmtContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitWith_stmt(Python3Parser::With_stmtContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitWith_item(Python3Parser::With_itemContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitExcept_clause(Python3Parser::Except_clauseContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitBlock(Python3Parser::BlockContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitMatch_stmt(Python3Parser::Match_stmtContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitSubject_expr(Python3Parser::Subject_exprContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitStar_named_expressions(Python3Parser::Star_named_expressionsContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitStar_named_expression(Python3Parser::Star_named_expressionContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitCase_block(Python3Parser::Case_blockContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitGuard(Python3Parser::GuardContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitPatterns(Python3Parser::PatternsContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitPattern(Python3Parser::PatternContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitAs_pattern(Python3Parser::As_patternContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitOr_pattern(Python3Parser::Or_patternContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitClosed_pattern(Python3Parser::Closed_patternContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitLiteral_pattern(Python3Parser::Literal_patternContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitLiteral_expr(Python3Parser::Literal_exprContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitComplex_number(Python3Parser::Complex_numberContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitSigned_number(Python3Parser::Signed_numberContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitSigned_real_number(Python3Parser::Signed_real_numberContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitReal_number(Python3Parser::Real_numberContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitImaginary_number(Python3Parser::Imaginary_numberContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitCapture_pattern(Python3Parser::Capture_patternContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitPattern_capture_target(Python3Parser::Pattern_capture_targetContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitWildcard_pattern(Python3Parser::Wildcard_patternContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitValue_pattern(Python3Parser::Value_patternContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitAttr(Python3Parser::AttrContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitName_or_attr(Python3Parser::Name_or_attrContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitGroup_pattern(Python3Parser::Group_patternContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitSequence_pattern(Python3Parser::Sequence_patternContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitOpen_sequence_pattern(Python3Parser::Open_sequence_patternContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitMaybe_sequence_pattern(Python3Parser::Maybe_sequence_patternContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitMaybe_star_pattern(Python3Parser::Maybe_star_patternContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitStar_pattern(Python3Parser::Star_patternContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitMapping_pattern(Python3Parser::Mapping_patternContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitItems_pattern(Python3Parser::Items_patternContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitKey_value_pattern(Python3Parser::Key_value_patternContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitDouble_star_pattern(Python3Parser::Double_star_patternContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitClass_pattern(Python3Parser::Class_patternContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitPositional_patterns(Python3Parser::Positional_patternsContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitKeyword_patterns(Python3Parser::Keyword_patternsContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitKeyword_pattern(Python3Parser::Keyword_patternContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitTest(Python3Parser::TestContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitTest_nocond(Python3Parser::Test_nocondContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitLambdef(Python3Parser::LambdefContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitLambdef_nocond(Python3Parser::Lambdef_nocondContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitOr_test(Python3Parser::Or_testContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitAnd_test(Python3Parser::And_testContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitNot_test(Python3Parser::Not_testContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitComparison(Python3Parser::ComparisonContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitComp_op(Python3Parser::Comp_opContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitStar_expr(Python3Parser::Star_exprContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitExpr(Python3Parser::ExprContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitAtom_expr(Python3Parser::Atom_exprContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitAtom(Python3Parser::AtomContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitName(Python3Parser::NameContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitTestlist_comp(Python3Parser::Testlist_compContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitTrailer(Python3Parser::TrailerContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitSubscriptlist(Python3Parser::SubscriptlistContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitSubscript_(Python3Parser::Subscript_Context *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitSliceop(Python3Parser::SliceopContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitExprlist(Python3Parser::ExprlistContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitTestlist(Python3Parser::TestlistContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitDictorsetmaker(Python3Parser::DictorsetmakerContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitClassdef(Python3Parser::ClassdefContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitArglist(Python3Parser::ArglistContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitArgument(Python3Parser::ArgumentContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitComp_iter(Python3Parser::Comp_iterContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitComp_for(Python3Parser::Comp_forContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitComp_if(Python3Parser::Comp_ifContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitEncoding_decl(Python3Parser::Encoding_declContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitYield_expr(Python3Parser::Yield_exprContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitYield_arg(Python3Parser::Yield_argContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitStrings(Python3Parser::StringsContext *ctx) override {
    return visitChildren(ctx);
  }


};

