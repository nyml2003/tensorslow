
// Generated from /app/grammar/Python3Parser.g4 by ANTLR 4.9.2

#pragma once


#include "antlr4-runtime.h"
#include "Python3Parser.h"



/**
 * This class defines an abstract visitor for a parse tree
 * produced by Python3Parser.
 */
class  Python3ParserVisitor : public antlr4::tree::AbstractParseTreeVisitor {
public:

  /**
   * Visit parse trees produced by Python3Parser.
   */
    virtual antlrcpp::Any visitSingle_input(Python3Parser::Single_inputContext *context) = 0;

    virtual antlrcpp::Any visitFile_input(Python3Parser::File_inputContext *context) = 0;

    virtual antlrcpp::Any visitEval_input(Python3Parser::Eval_inputContext *context) = 0;

    virtual antlrcpp::Any visitDecorator(Python3Parser::DecoratorContext *context) = 0;

    virtual antlrcpp::Any visitDecorators(Python3Parser::DecoratorsContext *context) = 0;

    virtual antlrcpp::Any visitDecorated(Python3Parser::DecoratedContext *context) = 0;

    virtual antlrcpp::Any visitAsync_funcdef(Python3Parser::Async_funcdefContext *context) = 0;

    virtual antlrcpp::Any visitFuncdef(Python3Parser::FuncdefContext *context) = 0;

    virtual antlrcpp::Any visitParameters(Python3Parser::ParametersContext *context) = 0;

    virtual antlrcpp::Any visitTypedargslist(Python3Parser::TypedargslistContext *context) = 0;

    virtual antlrcpp::Any visitTfpdef(Python3Parser::TfpdefContext *context) = 0;

    virtual antlrcpp::Any visitVarargslist(Python3Parser::VarargslistContext *context) = 0;

    virtual antlrcpp::Any visitVfpdef(Python3Parser::VfpdefContext *context) = 0;

    virtual antlrcpp::Any visitStmt(Python3Parser::StmtContext *context) = 0;

    virtual antlrcpp::Any visitSimple_stmts(Python3Parser::Simple_stmtsContext *context) = 0;

    virtual antlrcpp::Any visitSimple_stmt(Python3Parser::Simple_stmtContext *context) = 0;

    virtual antlrcpp::Any visitExpr_stmt(Python3Parser::Expr_stmtContext *context) = 0;

    virtual antlrcpp::Any visitAnnassign(Python3Parser::AnnassignContext *context) = 0;

    virtual antlrcpp::Any visitTestlist_star_expr(Python3Parser::Testlist_star_exprContext *context) = 0;

    virtual antlrcpp::Any visitAugassign(Python3Parser::AugassignContext *context) = 0;

    virtual antlrcpp::Any visitDel_stmt(Python3Parser::Del_stmtContext *context) = 0;

    virtual antlrcpp::Any visitPass_stmt(Python3Parser::Pass_stmtContext *context) = 0;

    virtual antlrcpp::Any visitFlow_stmt(Python3Parser::Flow_stmtContext *context) = 0;

    virtual antlrcpp::Any visitBreak_stmt(Python3Parser::Break_stmtContext *context) = 0;

    virtual antlrcpp::Any visitContinue_stmt(Python3Parser::Continue_stmtContext *context) = 0;

    virtual antlrcpp::Any visitReturn_stmt(Python3Parser::Return_stmtContext *context) = 0;

    virtual antlrcpp::Any visitYield_stmt(Python3Parser::Yield_stmtContext *context) = 0;

    virtual antlrcpp::Any visitRaise_stmt(Python3Parser::Raise_stmtContext *context) = 0;

    virtual antlrcpp::Any visitImport_stmt(Python3Parser::Import_stmtContext *context) = 0;

    virtual antlrcpp::Any visitImport_name(Python3Parser::Import_nameContext *context) = 0;

    virtual antlrcpp::Any visitImport_from(Python3Parser::Import_fromContext *context) = 0;

    virtual antlrcpp::Any visitImport_as_name(Python3Parser::Import_as_nameContext *context) = 0;

    virtual antlrcpp::Any visitDotted_as_name(Python3Parser::Dotted_as_nameContext *context) = 0;

    virtual antlrcpp::Any visitImport_as_names(Python3Parser::Import_as_namesContext *context) = 0;

    virtual antlrcpp::Any visitDotted_as_names(Python3Parser::Dotted_as_namesContext *context) = 0;

    virtual antlrcpp::Any visitDotted_name(Python3Parser::Dotted_nameContext *context) = 0;

    virtual antlrcpp::Any visitGlobal_stmt(Python3Parser::Global_stmtContext *context) = 0;

    virtual antlrcpp::Any visitNonlocal_stmt(Python3Parser::Nonlocal_stmtContext *context) = 0;

    virtual antlrcpp::Any visitAssert_stmt(Python3Parser::Assert_stmtContext *context) = 0;

    virtual antlrcpp::Any visitCompound_stmt(Python3Parser::Compound_stmtContext *context) = 0;

    virtual antlrcpp::Any visitAsync_stmt(Python3Parser::Async_stmtContext *context) = 0;

    virtual antlrcpp::Any visitIf_stmt(Python3Parser::If_stmtContext *context) = 0;

    virtual antlrcpp::Any visitWhile_stmt(Python3Parser::While_stmtContext *context) = 0;

    virtual antlrcpp::Any visitFor_stmt(Python3Parser::For_stmtContext *context) = 0;

    virtual antlrcpp::Any visitTry_stmt(Python3Parser::Try_stmtContext *context) = 0;

    virtual antlrcpp::Any visitWith_stmt(Python3Parser::With_stmtContext *context) = 0;

    virtual antlrcpp::Any visitWith_item(Python3Parser::With_itemContext *context) = 0;

    virtual antlrcpp::Any visitExcept_clause(Python3Parser::Except_clauseContext *context) = 0;

    virtual antlrcpp::Any visitBlock(Python3Parser::BlockContext *context) = 0;

    virtual antlrcpp::Any visitMatch_stmt(Python3Parser::Match_stmtContext *context) = 0;

    virtual antlrcpp::Any visitSubject_expr(Python3Parser::Subject_exprContext *context) = 0;

    virtual antlrcpp::Any visitStar_named_expressions(Python3Parser::Star_named_expressionsContext *context) = 0;

    virtual antlrcpp::Any visitStar_named_expression(Python3Parser::Star_named_expressionContext *context) = 0;

    virtual antlrcpp::Any visitCase_block(Python3Parser::Case_blockContext *context) = 0;

    virtual antlrcpp::Any visitGuard(Python3Parser::GuardContext *context) = 0;

    virtual antlrcpp::Any visitPatterns(Python3Parser::PatternsContext *context) = 0;

    virtual antlrcpp::Any visitPattern(Python3Parser::PatternContext *context) = 0;

    virtual antlrcpp::Any visitAs_pattern(Python3Parser::As_patternContext *context) = 0;

    virtual antlrcpp::Any visitOr_pattern(Python3Parser::Or_patternContext *context) = 0;

    virtual antlrcpp::Any visitClosed_pattern(Python3Parser::Closed_patternContext *context) = 0;

    virtual antlrcpp::Any visitLiteral_pattern(Python3Parser::Literal_patternContext *context) = 0;

    virtual antlrcpp::Any visitLiteral_expr(Python3Parser::Literal_exprContext *context) = 0;

    virtual antlrcpp::Any visitComplex_number(Python3Parser::Complex_numberContext *context) = 0;

    virtual antlrcpp::Any visitSigned_number(Python3Parser::Signed_numberContext *context) = 0;

    virtual antlrcpp::Any visitSigned_real_number(Python3Parser::Signed_real_numberContext *context) = 0;

    virtual antlrcpp::Any visitReal_number(Python3Parser::Real_numberContext *context) = 0;

    virtual antlrcpp::Any visitImaginary_number(Python3Parser::Imaginary_numberContext *context) = 0;

    virtual antlrcpp::Any visitCapture_pattern(Python3Parser::Capture_patternContext *context) = 0;

    virtual antlrcpp::Any visitPattern_capture_target(Python3Parser::Pattern_capture_targetContext *context) = 0;

    virtual antlrcpp::Any visitWildcard_pattern(Python3Parser::Wildcard_patternContext *context) = 0;

    virtual antlrcpp::Any visitValue_pattern(Python3Parser::Value_patternContext *context) = 0;

    virtual antlrcpp::Any visitAttr(Python3Parser::AttrContext *context) = 0;

    virtual antlrcpp::Any visitName_or_attr(Python3Parser::Name_or_attrContext *context) = 0;

    virtual antlrcpp::Any visitGroup_pattern(Python3Parser::Group_patternContext *context) = 0;

    virtual antlrcpp::Any visitSequence_pattern(Python3Parser::Sequence_patternContext *context) = 0;

    virtual antlrcpp::Any visitOpen_sequence_pattern(Python3Parser::Open_sequence_patternContext *context) = 0;

    virtual antlrcpp::Any visitMaybe_sequence_pattern(Python3Parser::Maybe_sequence_patternContext *context) = 0;

    virtual antlrcpp::Any visitMaybe_star_pattern(Python3Parser::Maybe_star_patternContext *context) = 0;

    virtual antlrcpp::Any visitStar_pattern(Python3Parser::Star_patternContext *context) = 0;

    virtual antlrcpp::Any visitMapping_pattern(Python3Parser::Mapping_patternContext *context) = 0;

    virtual antlrcpp::Any visitItems_pattern(Python3Parser::Items_patternContext *context) = 0;

    virtual antlrcpp::Any visitKey_value_pattern(Python3Parser::Key_value_patternContext *context) = 0;

    virtual antlrcpp::Any visitDouble_star_pattern(Python3Parser::Double_star_patternContext *context) = 0;

    virtual antlrcpp::Any visitClass_pattern(Python3Parser::Class_patternContext *context) = 0;

    virtual antlrcpp::Any visitPositional_patterns(Python3Parser::Positional_patternsContext *context) = 0;

    virtual antlrcpp::Any visitKeyword_patterns(Python3Parser::Keyword_patternsContext *context) = 0;

    virtual antlrcpp::Any visitKeyword_pattern(Python3Parser::Keyword_patternContext *context) = 0;

    virtual antlrcpp::Any visitTest(Python3Parser::TestContext *context) = 0;

    virtual antlrcpp::Any visitTest_nocond(Python3Parser::Test_nocondContext *context) = 0;

    virtual antlrcpp::Any visitLambdef(Python3Parser::LambdefContext *context) = 0;

    virtual antlrcpp::Any visitLambdef_nocond(Python3Parser::Lambdef_nocondContext *context) = 0;

    virtual antlrcpp::Any visitOr_test(Python3Parser::Or_testContext *context) = 0;

    virtual antlrcpp::Any visitAnd_test(Python3Parser::And_testContext *context) = 0;

    virtual antlrcpp::Any visitNot_test(Python3Parser::Not_testContext *context) = 0;

    virtual antlrcpp::Any visitComparison(Python3Parser::ComparisonContext *context) = 0;

    virtual antlrcpp::Any visitComp_op(Python3Parser::Comp_opContext *context) = 0;

    virtual antlrcpp::Any visitStar_expr(Python3Parser::Star_exprContext *context) = 0;

    virtual antlrcpp::Any visitExpr(Python3Parser::ExprContext *context) = 0;

    virtual antlrcpp::Any visitAtom_expr(Python3Parser::Atom_exprContext *context) = 0;

    virtual antlrcpp::Any visitAtom(Python3Parser::AtomContext *context) = 0;

    virtual antlrcpp::Any visitName(Python3Parser::NameContext *context) = 0;

    virtual antlrcpp::Any visitTestlist_comp(Python3Parser::Testlist_compContext *context) = 0;

    virtual antlrcpp::Any visitTrailer(Python3Parser::TrailerContext *context) = 0;

    virtual antlrcpp::Any visitSubscriptlist(Python3Parser::SubscriptlistContext *context) = 0;

    virtual antlrcpp::Any visitSubscript_(Python3Parser::Subscript_Context *context) = 0;

    virtual antlrcpp::Any visitSliceop(Python3Parser::SliceopContext *context) = 0;

    virtual antlrcpp::Any visitExprlist(Python3Parser::ExprlistContext *context) = 0;

    virtual antlrcpp::Any visitTestlist(Python3Parser::TestlistContext *context) = 0;

    virtual antlrcpp::Any visitDictorsetmaker(Python3Parser::DictorsetmakerContext *context) = 0;

    virtual antlrcpp::Any visitClassdef(Python3Parser::ClassdefContext *context) = 0;

    virtual antlrcpp::Any visitArglist(Python3Parser::ArglistContext *context) = 0;

    virtual antlrcpp::Any visitArgument(Python3Parser::ArgumentContext *context) = 0;

    virtual antlrcpp::Any visitComp_iter(Python3Parser::Comp_iterContext *context) = 0;

    virtual antlrcpp::Any visitComp_for(Python3Parser::Comp_forContext *context) = 0;

    virtual antlrcpp::Any visitComp_if(Python3Parser::Comp_ifContext *context) = 0;

    virtual antlrcpp::Any visitEncoding_decl(Python3Parser::Encoding_declContext *context) = 0;

    virtual antlrcpp::Any visitYield_expr(Python3Parser::Yield_exprContext *context) = 0;

    virtual antlrcpp::Any visitYield_arg(Python3Parser::Yield_argContext *context) = 0;

    virtual antlrcpp::Any visitStrings(Python3Parser::StringsContext *context) = 0;


};

