
// Generated from /app/grammar/Python3Parser.g4 by ANTLR 4.9.2


#include "Python3ParserListener.h"
#include "Python3ParserVisitor.h"

#include "Python3Parser.h"


using namespace antlrcpp;
using namespace antlr4;

Python3Parser::Python3Parser(TokenStream *input) : Python3ParserBase(input) {
  _interpreter = new atn::ParserATNSimulator(this, _atn, _decisionToDFA, _sharedContextCache);
}

Python3Parser::~Python3Parser() {
  delete _interpreter;
}

std::string Python3Parser::getGrammarFileName() const {
  return "Python3Parser.g4";
}

const std::vector<std::string>& Python3Parser::getRuleNames() const {
  return _ruleNames;
}

dfa::Vocabulary& Python3Parser::getVocabulary() const {
  return _vocabulary;
}


//----------------- Single_inputContext ------------------------------------------------------------------

Python3Parser::Single_inputContext::Single_inputContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* Python3Parser::Single_inputContext::NEWLINE() {
  return getToken(Python3Parser::NEWLINE, 0);
}

Python3Parser::Simple_stmtsContext* Python3Parser::Single_inputContext::simple_stmts() {
  return getRuleContext<Python3Parser::Simple_stmtsContext>(0);
}

Python3Parser::Compound_stmtContext* Python3Parser::Single_inputContext::compound_stmt() {
  return getRuleContext<Python3Parser::Compound_stmtContext>(0);
}


size_t Python3Parser::Single_inputContext::getRuleIndex() const {
  return Python3Parser::RuleSingle_input;
}

void Python3Parser::Single_inputContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<Python3ParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterSingle_input(this);
}

void Python3Parser::Single_inputContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<Python3ParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitSingle_input(this);
}


antlrcpp::Any Python3Parser::Single_inputContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<Python3ParserVisitor*>(visitor))
    return parserVisitor->visitSingle_input(this);
  else
    return visitor->visitChildren(this);
}

Python3Parser::Single_inputContext* Python3Parser::single_input() {
  Single_inputContext *_localctx = _tracker.createInstance<Single_inputContext>(_ctx, getState());
  enterRule(_localctx, 0, Python3Parser::RuleSingle_input);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    setState(243);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 0, _ctx)) {
    case 1: {
      enterOuterAlt(_localctx, 1);
      setState(238);
      match(Python3Parser::NEWLINE);
      break;
    }

    case 2: {
      enterOuterAlt(_localctx, 2);
      setState(239);
      simple_stmts();
      break;
    }

    case 3: {
      enterOuterAlt(_localctx, 3);
      setState(240);
      compound_stmt();
      setState(241);
      match(Python3Parser::NEWLINE);
      break;
    }

    default:
      break;
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- File_inputContext ------------------------------------------------------------------

Python3Parser::File_inputContext::File_inputContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* Python3Parser::File_inputContext::EOF() {
  return getToken(Python3Parser::EOF, 0);
}

std::vector<tree::TerminalNode *> Python3Parser::File_inputContext::NEWLINE() {
  return getTokens(Python3Parser::NEWLINE);
}

tree::TerminalNode* Python3Parser::File_inputContext::NEWLINE(size_t i) {
  return getToken(Python3Parser::NEWLINE, i);
}

std::vector<Python3Parser::StmtContext *> Python3Parser::File_inputContext::stmt() {
  return getRuleContexts<Python3Parser::StmtContext>();
}

Python3Parser::StmtContext* Python3Parser::File_inputContext::stmt(size_t i) {
  return getRuleContext<Python3Parser::StmtContext>(i);
}


size_t Python3Parser::File_inputContext::getRuleIndex() const {
  return Python3Parser::RuleFile_input;
}

void Python3Parser::File_inputContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<Python3ParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterFile_input(this);
}

void Python3Parser::File_inputContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<Python3ParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitFile_input(this);
}


antlrcpp::Any Python3Parser::File_inputContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<Python3ParserVisitor*>(visitor))
    return parserVisitor->visitFile_input(this);
  else
    return visitor->visitChildren(this);
}

Python3Parser::File_inputContext* Python3Parser::file_input() {
  File_inputContext *_localctx = _tracker.createInstance<File_inputContext>(_ctx, getState());
  enterRule(_localctx, 2, Python3Parser::RuleFile_input);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(249);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while ((((_la & ~ 0x3fULL) == 0) &&
      ((1ULL << _la) & ((1ULL << Python3Parser::STRING)
      | (1ULL << Python3Parser::NUMBER)
      | (1ULL << Python3Parser::ASSERT)
      | (1ULL << Python3Parser::ASYNC)
      | (1ULL << Python3Parser::AWAIT)
      | (1ULL << Python3Parser::BREAK)
      | (1ULL << Python3Parser::CLASS)
      | (1ULL << Python3Parser::CONTINUE)
      | (1ULL << Python3Parser::DEF)
      | (1ULL << Python3Parser::DEL)
      | (1ULL << Python3Parser::FALSE)
      | (1ULL << Python3Parser::FOR)
      | (1ULL << Python3Parser::FROM)
      | (1ULL << Python3Parser::GLOBAL)
      | (1ULL << Python3Parser::IF)
      | (1ULL << Python3Parser::IMPORT)
      | (1ULL << Python3Parser::LAMBDA)
      | (1ULL << Python3Parser::MATCH)
      | (1ULL << Python3Parser::NONE)
      | (1ULL << Python3Parser::NONLOCAL)
      | (1ULL << Python3Parser::NOT)
      | (1ULL << Python3Parser::PASS)
      | (1ULL << Python3Parser::RAISE)
      | (1ULL << Python3Parser::RETURN)
      | (1ULL << Python3Parser::TRUE)
      | (1ULL << Python3Parser::TRY)
      | (1ULL << Python3Parser::UNDERSCORE)
      | (1ULL << Python3Parser::WHILE)
      | (1ULL << Python3Parser::WITH)
      | (1ULL << Python3Parser::YIELD)
      | (1ULL << Python3Parser::NEWLINE)
      | (1ULL << Python3Parser::NAME)
      | (1ULL << Python3Parser::ELLIPSIS)
      | (1ULL << Python3Parser::STAR)
      | (1ULL << Python3Parser::OPEN_PAREN))) != 0) || ((((_la - 64) & ~ 0x3fULL) == 0) &&
      ((1ULL << (_la - 64)) & ((1ULL << (Python3Parser::OPEN_BRACK - 64))
      | (1ULL << (Python3Parser::ADD - 64))
      | (1ULL << (Python3Parser::MINUS - 64))
      | (1ULL << (Python3Parser::NOT_OP - 64))
      | (1ULL << (Python3Parser::OPEN_BRACE - 64))
      | (1ULL << (Python3Parser::AT - 64)))) != 0)) {
      setState(247);
      _errHandler->sync(this);
      switch (_input->LA(1)) {
        case Python3Parser::NEWLINE: {
          setState(245);
          match(Python3Parser::NEWLINE);
          break;
        }

        case Python3Parser::STRING:
        case Python3Parser::NUMBER:
        case Python3Parser::ASSERT:
        case Python3Parser::ASYNC:
        case Python3Parser::AWAIT:
        case Python3Parser::BREAK:
        case Python3Parser::CLASS:
        case Python3Parser::CONTINUE:
        case Python3Parser::DEF:
        case Python3Parser::DEL:
        case Python3Parser::FALSE:
        case Python3Parser::FOR:
        case Python3Parser::FROM:
        case Python3Parser::GLOBAL:
        case Python3Parser::IF:
        case Python3Parser::IMPORT:
        case Python3Parser::LAMBDA:
        case Python3Parser::MATCH:
        case Python3Parser::NONE:
        case Python3Parser::NONLOCAL:
        case Python3Parser::NOT:
        case Python3Parser::PASS:
        case Python3Parser::RAISE:
        case Python3Parser::RETURN:
        case Python3Parser::TRUE:
        case Python3Parser::TRY:
        case Python3Parser::UNDERSCORE:
        case Python3Parser::WHILE:
        case Python3Parser::WITH:
        case Python3Parser::YIELD:
        case Python3Parser::NAME:
        case Python3Parser::ELLIPSIS:
        case Python3Parser::STAR:
        case Python3Parser::OPEN_PAREN:
        case Python3Parser::OPEN_BRACK:
        case Python3Parser::ADD:
        case Python3Parser::MINUS:
        case Python3Parser::NOT_OP:
        case Python3Parser::OPEN_BRACE:
        case Python3Parser::AT: {
          setState(246);
          stmt();
          break;
        }

      default:
        throw NoViableAltException(this);
      }
      setState(251);
      _errHandler->sync(this);
      _la = _input->LA(1);
    }
    setState(252);
    match(Python3Parser::EOF);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- Eval_inputContext ------------------------------------------------------------------

Python3Parser::Eval_inputContext::Eval_inputContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

Python3Parser::TestlistContext* Python3Parser::Eval_inputContext::testlist() {
  return getRuleContext<Python3Parser::TestlistContext>(0);
}

tree::TerminalNode* Python3Parser::Eval_inputContext::EOF() {
  return getToken(Python3Parser::EOF, 0);
}

std::vector<tree::TerminalNode *> Python3Parser::Eval_inputContext::NEWLINE() {
  return getTokens(Python3Parser::NEWLINE);
}

tree::TerminalNode* Python3Parser::Eval_inputContext::NEWLINE(size_t i) {
  return getToken(Python3Parser::NEWLINE, i);
}


size_t Python3Parser::Eval_inputContext::getRuleIndex() const {
  return Python3Parser::RuleEval_input;
}

void Python3Parser::Eval_inputContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<Python3ParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterEval_input(this);
}

void Python3Parser::Eval_inputContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<Python3ParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitEval_input(this);
}


antlrcpp::Any Python3Parser::Eval_inputContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<Python3ParserVisitor*>(visitor))
    return parserVisitor->visitEval_input(this);
  else
    return visitor->visitChildren(this);
}

Python3Parser::Eval_inputContext* Python3Parser::eval_input() {
  Eval_inputContext *_localctx = _tracker.createInstance<Eval_inputContext>(_ctx, getState());
  enterRule(_localctx, 4, Python3Parser::RuleEval_input);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(254);
    testlist();
    setState(258);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while (_la == Python3Parser::NEWLINE) {
      setState(255);
      match(Python3Parser::NEWLINE);
      setState(260);
      _errHandler->sync(this);
      _la = _input->LA(1);
    }
    setState(261);
    match(Python3Parser::EOF);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- DecoratorContext ------------------------------------------------------------------

Python3Parser::DecoratorContext::DecoratorContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* Python3Parser::DecoratorContext::AT() {
  return getToken(Python3Parser::AT, 0);
}

Python3Parser::Dotted_nameContext* Python3Parser::DecoratorContext::dotted_name() {
  return getRuleContext<Python3Parser::Dotted_nameContext>(0);
}

tree::TerminalNode* Python3Parser::DecoratorContext::NEWLINE() {
  return getToken(Python3Parser::NEWLINE, 0);
}

tree::TerminalNode* Python3Parser::DecoratorContext::OPEN_PAREN() {
  return getToken(Python3Parser::OPEN_PAREN, 0);
}

tree::TerminalNode* Python3Parser::DecoratorContext::CLOSE_PAREN() {
  return getToken(Python3Parser::CLOSE_PAREN, 0);
}

Python3Parser::ArglistContext* Python3Parser::DecoratorContext::arglist() {
  return getRuleContext<Python3Parser::ArglistContext>(0);
}


size_t Python3Parser::DecoratorContext::getRuleIndex() const {
  return Python3Parser::RuleDecorator;
}

void Python3Parser::DecoratorContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<Python3ParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterDecorator(this);
}

void Python3Parser::DecoratorContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<Python3ParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitDecorator(this);
}


antlrcpp::Any Python3Parser::DecoratorContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<Python3ParserVisitor*>(visitor))
    return parserVisitor->visitDecorator(this);
  else
    return visitor->visitChildren(this);
}

Python3Parser::DecoratorContext* Python3Parser::decorator() {
  DecoratorContext *_localctx = _tracker.createInstance<DecoratorContext>(_ctx, getState());
  enterRule(_localctx, 6, Python3Parser::RuleDecorator);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(263);
    match(Python3Parser::AT);
    setState(264);
    dotted_name();
    setState(270);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == Python3Parser::OPEN_PAREN) {
      setState(265);
      match(Python3Parser::OPEN_PAREN);
      setState(267);
      _errHandler->sync(this);

      _la = _input->LA(1);
      if ((((_la & ~ 0x3fULL) == 0) &&
        ((1ULL << _la) & ((1ULL << Python3Parser::STRING)
        | (1ULL << Python3Parser::NUMBER)
        | (1ULL << Python3Parser::AWAIT)
        | (1ULL << Python3Parser::FALSE)
        | (1ULL << Python3Parser::LAMBDA)
        | (1ULL << Python3Parser::MATCH)
        | (1ULL << Python3Parser::NONE)
        | (1ULL << Python3Parser::NOT)
        | (1ULL << Python3Parser::TRUE)
        | (1ULL << Python3Parser::UNDERSCORE)
        | (1ULL << Python3Parser::NAME)
        | (1ULL << Python3Parser::ELLIPSIS)
        | (1ULL << Python3Parser::STAR)
        | (1ULL << Python3Parser::OPEN_PAREN)
        | (1ULL << Python3Parser::POWER))) != 0) || ((((_la - 64) & ~ 0x3fULL) == 0) &&
        ((1ULL << (_la - 64)) & ((1ULL << (Python3Parser::OPEN_BRACK - 64))
        | (1ULL << (Python3Parser::ADD - 64))
        | (1ULL << (Python3Parser::MINUS - 64))
        | (1ULL << (Python3Parser::NOT_OP - 64))
        | (1ULL << (Python3Parser::OPEN_BRACE - 64)))) != 0)) {
        setState(266);
        arglist();
      }
      setState(269);
      match(Python3Parser::CLOSE_PAREN);
    }
    setState(272);
    match(Python3Parser::NEWLINE);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- DecoratorsContext ------------------------------------------------------------------

Python3Parser::DecoratorsContext::DecoratorsContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

std::vector<Python3Parser::DecoratorContext *> Python3Parser::DecoratorsContext::decorator() {
  return getRuleContexts<Python3Parser::DecoratorContext>();
}

Python3Parser::DecoratorContext* Python3Parser::DecoratorsContext::decorator(size_t i) {
  return getRuleContext<Python3Parser::DecoratorContext>(i);
}


size_t Python3Parser::DecoratorsContext::getRuleIndex() const {
  return Python3Parser::RuleDecorators;
}

void Python3Parser::DecoratorsContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<Python3ParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterDecorators(this);
}

void Python3Parser::DecoratorsContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<Python3ParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitDecorators(this);
}


antlrcpp::Any Python3Parser::DecoratorsContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<Python3ParserVisitor*>(visitor))
    return parserVisitor->visitDecorators(this);
  else
    return visitor->visitChildren(this);
}

Python3Parser::DecoratorsContext* Python3Parser::decorators() {
  DecoratorsContext *_localctx = _tracker.createInstance<DecoratorsContext>(_ctx, getState());
  enterRule(_localctx, 8, Python3Parser::RuleDecorators);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(275); 
    _errHandler->sync(this);
    _la = _input->LA(1);
    do {
      setState(274);
      decorator();
      setState(277); 
      _errHandler->sync(this);
      _la = _input->LA(1);
    } while (_la == Python3Parser::AT);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- DecoratedContext ------------------------------------------------------------------

Python3Parser::DecoratedContext::DecoratedContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

Python3Parser::DecoratorsContext* Python3Parser::DecoratedContext::decorators() {
  return getRuleContext<Python3Parser::DecoratorsContext>(0);
}

Python3Parser::ClassdefContext* Python3Parser::DecoratedContext::classdef() {
  return getRuleContext<Python3Parser::ClassdefContext>(0);
}

Python3Parser::FuncdefContext* Python3Parser::DecoratedContext::funcdef() {
  return getRuleContext<Python3Parser::FuncdefContext>(0);
}

Python3Parser::Async_funcdefContext* Python3Parser::DecoratedContext::async_funcdef() {
  return getRuleContext<Python3Parser::Async_funcdefContext>(0);
}


size_t Python3Parser::DecoratedContext::getRuleIndex() const {
  return Python3Parser::RuleDecorated;
}

void Python3Parser::DecoratedContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<Python3ParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterDecorated(this);
}

void Python3Parser::DecoratedContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<Python3ParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitDecorated(this);
}


antlrcpp::Any Python3Parser::DecoratedContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<Python3ParserVisitor*>(visitor))
    return parserVisitor->visitDecorated(this);
  else
    return visitor->visitChildren(this);
}

Python3Parser::DecoratedContext* Python3Parser::decorated() {
  DecoratedContext *_localctx = _tracker.createInstance<DecoratedContext>(_ctx, getState());
  enterRule(_localctx, 10, Python3Parser::RuleDecorated);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(279);
    decorators();
    setState(283);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case Python3Parser::CLASS: {
        setState(280);
        classdef();
        break;
      }

      case Python3Parser::DEF: {
        setState(281);
        funcdef();
        break;
      }

      case Python3Parser::ASYNC: {
        setState(282);
        async_funcdef();
        break;
      }

    default:
      throw NoViableAltException(this);
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- Async_funcdefContext ------------------------------------------------------------------

Python3Parser::Async_funcdefContext::Async_funcdefContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* Python3Parser::Async_funcdefContext::ASYNC() {
  return getToken(Python3Parser::ASYNC, 0);
}

Python3Parser::FuncdefContext* Python3Parser::Async_funcdefContext::funcdef() {
  return getRuleContext<Python3Parser::FuncdefContext>(0);
}


size_t Python3Parser::Async_funcdefContext::getRuleIndex() const {
  return Python3Parser::RuleAsync_funcdef;
}

void Python3Parser::Async_funcdefContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<Python3ParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterAsync_funcdef(this);
}

void Python3Parser::Async_funcdefContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<Python3ParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitAsync_funcdef(this);
}


antlrcpp::Any Python3Parser::Async_funcdefContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<Python3ParserVisitor*>(visitor))
    return parserVisitor->visitAsync_funcdef(this);
  else
    return visitor->visitChildren(this);
}

Python3Parser::Async_funcdefContext* Python3Parser::async_funcdef() {
  Async_funcdefContext *_localctx = _tracker.createInstance<Async_funcdefContext>(_ctx, getState());
  enterRule(_localctx, 12, Python3Parser::RuleAsync_funcdef);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(285);
    match(Python3Parser::ASYNC);
    setState(286);
    funcdef();
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- FuncdefContext ------------------------------------------------------------------

Python3Parser::FuncdefContext::FuncdefContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* Python3Parser::FuncdefContext::DEF() {
  return getToken(Python3Parser::DEF, 0);
}

Python3Parser::NameContext* Python3Parser::FuncdefContext::name() {
  return getRuleContext<Python3Parser::NameContext>(0);
}

Python3Parser::ParametersContext* Python3Parser::FuncdefContext::parameters() {
  return getRuleContext<Python3Parser::ParametersContext>(0);
}

tree::TerminalNode* Python3Parser::FuncdefContext::COLON() {
  return getToken(Python3Parser::COLON, 0);
}

Python3Parser::BlockContext* Python3Parser::FuncdefContext::block() {
  return getRuleContext<Python3Parser::BlockContext>(0);
}

tree::TerminalNode* Python3Parser::FuncdefContext::ARROW() {
  return getToken(Python3Parser::ARROW, 0);
}

Python3Parser::TestContext* Python3Parser::FuncdefContext::test() {
  return getRuleContext<Python3Parser::TestContext>(0);
}


size_t Python3Parser::FuncdefContext::getRuleIndex() const {
  return Python3Parser::RuleFuncdef;
}

void Python3Parser::FuncdefContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<Python3ParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterFuncdef(this);
}

void Python3Parser::FuncdefContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<Python3ParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitFuncdef(this);
}


antlrcpp::Any Python3Parser::FuncdefContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<Python3ParserVisitor*>(visitor))
    return parserVisitor->visitFuncdef(this);
  else
    return visitor->visitChildren(this);
}

Python3Parser::FuncdefContext* Python3Parser::funcdef() {
  FuncdefContext *_localctx = _tracker.createInstance<FuncdefContext>(_ctx, getState());
  enterRule(_localctx, 14, Python3Parser::RuleFuncdef);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(288);
    match(Python3Parser::DEF);
    setState(289);
    name();
    setState(290);
    parameters();
    setState(293);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == Python3Parser::ARROW) {
      setState(291);
      match(Python3Parser::ARROW);
      setState(292);
      test();
    }
    setState(295);
    match(Python3Parser::COLON);
    setState(296);
    block();
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- ParametersContext ------------------------------------------------------------------

Python3Parser::ParametersContext::ParametersContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* Python3Parser::ParametersContext::OPEN_PAREN() {
  return getToken(Python3Parser::OPEN_PAREN, 0);
}

tree::TerminalNode* Python3Parser::ParametersContext::CLOSE_PAREN() {
  return getToken(Python3Parser::CLOSE_PAREN, 0);
}

Python3Parser::TypedargslistContext* Python3Parser::ParametersContext::typedargslist() {
  return getRuleContext<Python3Parser::TypedargslistContext>(0);
}


size_t Python3Parser::ParametersContext::getRuleIndex() const {
  return Python3Parser::RuleParameters;
}

void Python3Parser::ParametersContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<Python3ParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterParameters(this);
}

void Python3Parser::ParametersContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<Python3ParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitParameters(this);
}


antlrcpp::Any Python3Parser::ParametersContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<Python3ParserVisitor*>(visitor))
    return parserVisitor->visitParameters(this);
  else
    return visitor->visitChildren(this);
}

Python3Parser::ParametersContext* Python3Parser::parameters() {
  ParametersContext *_localctx = _tracker.createInstance<ParametersContext>(_ctx, getState());
  enterRule(_localctx, 16, Python3Parser::RuleParameters);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(298);
    match(Python3Parser::OPEN_PAREN);
    setState(300);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if ((((_la & ~ 0x3fULL) == 0) &&
      ((1ULL << _la) & ((1ULL << Python3Parser::MATCH)
      | (1ULL << Python3Parser::UNDERSCORE)
      | (1ULL << Python3Parser::NAME)
      | (1ULL << Python3Parser::STAR)
      | (1ULL << Python3Parser::POWER))) != 0)) {
      setState(299);
      typedargslist();
    }
    setState(302);
    match(Python3Parser::CLOSE_PAREN);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- TypedargslistContext ------------------------------------------------------------------

Python3Parser::TypedargslistContext::TypedargslistContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

std::vector<Python3Parser::TfpdefContext *> Python3Parser::TypedargslistContext::tfpdef() {
  return getRuleContexts<Python3Parser::TfpdefContext>();
}

Python3Parser::TfpdefContext* Python3Parser::TypedargslistContext::tfpdef(size_t i) {
  return getRuleContext<Python3Parser::TfpdefContext>(i);
}

tree::TerminalNode* Python3Parser::TypedargslistContext::STAR() {
  return getToken(Python3Parser::STAR, 0);
}

tree::TerminalNode* Python3Parser::TypedargslistContext::POWER() {
  return getToken(Python3Parser::POWER, 0);
}

std::vector<tree::TerminalNode *> Python3Parser::TypedargslistContext::ASSIGN() {
  return getTokens(Python3Parser::ASSIGN);
}

tree::TerminalNode* Python3Parser::TypedargslistContext::ASSIGN(size_t i) {
  return getToken(Python3Parser::ASSIGN, i);
}

std::vector<Python3Parser::TestContext *> Python3Parser::TypedargslistContext::test() {
  return getRuleContexts<Python3Parser::TestContext>();
}

Python3Parser::TestContext* Python3Parser::TypedargslistContext::test(size_t i) {
  return getRuleContext<Python3Parser::TestContext>(i);
}

std::vector<tree::TerminalNode *> Python3Parser::TypedargslistContext::COMMA() {
  return getTokens(Python3Parser::COMMA);
}

tree::TerminalNode* Python3Parser::TypedargslistContext::COMMA(size_t i) {
  return getToken(Python3Parser::COMMA, i);
}


size_t Python3Parser::TypedargslistContext::getRuleIndex() const {
  return Python3Parser::RuleTypedargslist;
}

void Python3Parser::TypedargslistContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<Python3ParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterTypedargslist(this);
}

void Python3Parser::TypedargslistContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<Python3ParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitTypedargslist(this);
}


antlrcpp::Any Python3Parser::TypedargslistContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<Python3ParserVisitor*>(visitor))
    return parserVisitor->visitTypedargslist(this);
  else
    return visitor->visitChildren(this);
}

Python3Parser::TypedargslistContext* Python3Parser::typedargslist() {
  TypedargslistContext *_localctx = _tracker.createInstance<TypedargslistContext>(_ctx, getState());
  enterRule(_localctx, 18, Python3Parser::RuleTypedargslist);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    size_t alt;
    enterOuterAlt(_localctx, 1);
    setState(385);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case Python3Parser::MATCH:
      case Python3Parser::UNDERSCORE:
      case Python3Parser::NAME: {
        setState(304);
        tfpdef();
        setState(307);
        _errHandler->sync(this);

        _la = _input->LA(1);
        if (_la == Python3Parser::ASSIGN) {
          setState(305);
          match(Python3Parser::ASSIGN);
          setState(306);
          test();
        }
        setState(317);
        _errHandler->sync(this);
        alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 12, _ctx);
        while (alt != 2 && alt != atn::ATN::INVALID_ALT_NUMBER) {
          if (alt == 1) {
            setState(309);
            match(Python3Parser::COMMA);
            setState(310);
            tfpdef();
            setState(313);
            _errHandler->sync(this);

            _la = _input->LA(1);
            if (_la == Python3Parser::ASSIGN) {
              setState(311);
              match(Python3Parser::ASSIGN);
              setState(312);
              test();
            } 
          }
          setState(319);
          _errHandler->sync(this);
          alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 12, _ctx);
        }
        setState(353);
        _errHandler->sync(this);

        _la = _input->LA(1);
        if (_la == Python3Parser::COMMA) {
          setState(320);
          match(Python3Parser::COMMA);
          setState(351);
          _errHandler->sync(this);
          switch (_input->LA(1)) {
            case Python3Parser::STAR: {
              setState(321);
              match(Python3Parser::STAR);
              setState(323);
              _errHandler->sync(this);

              _la = _input->LA(1);
              if ((((_la & ~ 0x3fULL) == 0) &&
                ((1ULL << _la) & ((1ULL << Python3Parser::MATCH)
                | (1ULL << Python3Parser::UNDERSCORE)
                | (1ULL << Python3Parser::NAME))) != 0)) {
                setState(322);
                tfpdef();
              }
              setState(333);
              _errHandler->sync(this);
              alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 15, _ctx);
              while (alt != 2 && alt != atn::ATN::INVALID_ALT_NUMBER) {
                if (alt == 1) {
                  setState(325);
                  match(Python3Parser::COMMA);
                  setState(326);
                  tfpdef();
                  setState(329);
                  _errHandler->sync(this);

                  _la = _input->LA(1);
                  if (_la == Python3Parser::ASSIGN) {
                    setState(327);
                    match(Python3Parser::ASSIGN);
                    setState(328);
                    test();
                  } 
                }
                setState(335);
                _errHandler->sync(this);
                alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 15, _ctx);
              }
              setState(344);
              _errHandler->sync(this);

              _la = _input->LA(1);
              if (_la == Python3Parser::COMMA) {
                setState(336);
                match(Python3Parser::COMMA);
                setState(342);
                _errHandler->sync(this);

                _la = _input->LA(1);
                if (_la == Python3Parser::POWER) {
                  setState(337);
                  match(Python3Parser::POWER);
                  setState(338);
                  tfpdef();
                  setState(340);
                  _errHandler->sync(this);

                  _la = _input->LA(1);
                  if (_la == Python3Parser::COMMA) {
                    setState(339);
                    match(Python3Parser::COMMA);
                  }
                }
              }
              break;
            }

            case Python3Parser::POWER: {
              setState(346);
              match(Python3Parser::POWER);
              setState(347);
              tfpdef();
              setState(349);
              _errHandler->sync(this);

              _la = _input->LA(1);
              if (_la == Python3Parser::COMMA) {
                setState(348);
                match(Python3Parser::COMMA);
              }
              break;
            }

            case Python3Parser::CLOSE_PAREN: {
              break;
            }

          default:
            break;
          }
        }
        break;
      }

      case Python3Parser::STAR: {
        setState(355);
        match(Python3Parser::STAR);
        setState(357);
        _errHandler->sync(this);

        _la = _input->LA(1);
        if ((((_la & ~ 0x3fULL) == 0) &&
          ((1ULL << _la) & ((1ULL << Python3Parser::MATCH)
          | (1ULL << Python3Parser::UNDERSCORE)
          | (1ULL << Python3Parser::NAME))) != 0)) {
          setState(356);
          tfpdef();
        }
        setState(367);
        _errHandler->sync(this);
        alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 24, _ctx);
        while (alt != 2 && alt != atn::ATN::INVALID_ALT_NUMBER) {
          if (alt == 1) {
            setState(359);
            match(Python3Parser::COMMA);
            setState(360);
            tfpdef();
            setState(363);
            _errHandler->sync(this);

            _la = _input->LA(1);
            if (_la == Python3Parser::ASSIGN) {
              setState(361);
              match(Python3Parser::ASSIGN);
              setState(362);
              test();
            } 
          }
          setState(369);
          _errHandler->sync(this);
          alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 24, _ctx);
        }
        setState(378);
        _errHandler->sync(this);

        _la = _input->LA(1);
        if (_la == Python3Parser::COMMA) {
          setState(370);
          match(Python3Parser::COMMA);
          setState(376);
          _errHandler->sync(this);

          _la = _input->LA(1);
          if (_la == Python3Parser::POWER) {
            setState(371);
            match(Python3Parser::POWER);
            setState(372);
            tfpdef();
            setState(374);
            _errHandler->sync(this);

            _la = _input->LA(1);
            if (_la == Python3Parser::COMMA) {
              setState(373);
              match(Python3Parser::COMMA);
            }
          }
        }
        break;
      }

      case Python3Parser::POWER: {
        setState(380);
        match(Python3Parser::POWER);
        setState(381);
        tfpdef();
        setState(383);
        _errHandler->sync(this);

        _la = _input->LA(1);
        if (_la == Python3Parser::COMMA) {
          setState(382);
          match(Python3Parser::COMMA);
        }
        break;
      }

    default:
      throw NoViableAltException(this);
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- TfpdefContext ------------------------------------------------------------------

Python3Parser::TfpdefContext::TfpdefContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

Python3Parser::NameContext* Python3Parser::TfpdefContext::name() {
  return getRuleContext<Python3Parser::NameContext>(0);
}

tree::TerminalNode* Python3Parser::TfpdefContext::COLON() {
  return getToken(Python3Parser::COLON, 0);
}

Python3Parser::TestContext* Python3Parser::TfpdefContext::test() {
  return getRuleContext<Python3Parser::TestContext>(0);
}


size_t Python3Parser::TfpdefContext::getRuleIndex() const {
  return Python3Parser::RuleTfpdef;
}

void Python3Parser::TfpdefContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<Python3ParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterTfpdef(this);
}

void Python3Parser::TfpdefContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<Python3ParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitTfpdef(this);
}


antlrcpp::Any Python3Parser::TfpdefContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<Python3ParserVisitor*>(visitor))
    return parserVisitor->visitTfpdef(this);
  else
    return visitor->visitChildren(this);
}

Python3Parser::TfpdefContext* Python3Parser::tfpdef() {
  TfpdefContext *_localctx = _tracker.createInstance<TfpdefContext>(_ctx, getState());
  enterRule(_localctx, 20, Python3Parser::RuleTfpdef);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(387);
    name();
    setState(390);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == Python3Parser::COLON) {
      setState(388);
      match(Python3Parser::COLON);
      setState(389);
      test();
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- VarargslistContext ------------------------------------------------------------------

Python3Parser::VarargslistContext::VarargslistContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

std::vector<Python3Parser::VfpdefContext *> Python3Parser::VarargslistContext::vfpdef() {
  return getRuleContexts<Python3Parser::VfpdefContext>();
}

Python3Parser::VfpdefContext* Python3Parser::VarargslistContext::vfpdef(size_t i) {
  return getRuleContext<Python3Parser::VfpdefContext>(i);
}

tree::TerminalNode* Python3Parser::VarargslistContext::STAR() {
  return getToken(Python3Parser::STAR, 0);
}

tree::TerminalNode* Python3Parser::VarargslistContext::POWER() {
  return getToken(Python3Parser::POWER, 0);
}

std::vector<tree::TerminalNode *> Python3Parser::VarargslistContext::ASSIGN() {
  return getTokens(Python3Parser::ASSIGN);
}

tree::TerminalNode* Python3Parser::VarargslistContext::ASSIGN(size_t i) {
  return getToken(Python3Parser::ASSIGN, i);
}

std::vector<Python3Parser::TestContext *> Python3Parser::VarargslistContext::test() {
  return getRuleContexts<Python3Parser::TestContext>();
}

Python3Parser::TestContext* Python3Parser::VarargslistContext::test(size_t i) {
  return getRuleContext<Python3Parser::TestContext>(i);
}

std::vector<tree::TerminalNode *> Python3Parser::VarargslistContext::COMMA() {
  return getTokens(Python3Parser::COMMA);
}

tree::TerminalNode* Python3Parser::VarargslistContext::COMMA(size_t i) {
  return getToken(Python3Parser::COMMA, i);
}


size_t Python3Parser::VarargslistContext::getRuleIndex() const {
  return Python3Parser::RuleVarargslist;
}

void Python3Parser::VarargslistContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<Python3ParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterVarargslist(this);
}

void Python3Parser::VarargslistContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<Python3ParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitVarargslist(this);
}


antlrcpp::Any Python3Parser::VarargslistContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<Python3ParserVisitor*>(visitor))
    return parserVisitor->visitVarargslist(this);
  else
    return visitor->visitChildren(this);
}

Python3Parser::VarargslistContext* Python3Parser::varargslist() {
  VarargslistContext *_localctx = _tracker.createInstance<VarargslistContext>(_ctx, getState());
  enterRule(_localctx, 22, Python3Parser::RuleVarargslist);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    size_t alt;
    enterOuterAlt(_localctx, 1);
    setState(473);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case Python3Parser::MATCH:
      case Python3Parser::UNDERSCORE:
      case Python3Parser::NAME: {
        setState(392);
        vfpdef();
        setState(395);
        _errHandler->sync(this);

        _la = _input->LA(1);
        if (_la == Python3Parser::ASSIGN) {
          setState(393);
          match(Python3Parser::ASSIGN);
          setState(394);
          test();
        }
        setState(405);
        _errHandler->sync(this);
        alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 33, _ctx);
        while (alt != 2 && alt != atn::ATN::INVALID_ALT_NUMBER) {
          if (alt == 1) {
            setState(397);
            match(Python3Parser::COMMA);
            setState(398);
            vfpdef();
            setState(401);
            _errHandler->sync(this);

            _la = _input->LA(1);
            if (_la == Python3Parser::ASSIGN) {
              setState(399);
              match(Python3Parser::ASSIGN);
              setState(400);
              test();
            } 
          }
          setState(407);
          _errHandler->sync(this);
          alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 33, _ctx);
        }
        setState(441);
        _errHandler->sync(this);

        _la = _input->LA(1);
        if (_la == Python3Parser::COMMA) {
          setState(408);
          match(Python3Parser::COMMA);
          setState(439);
          _errHandler->sync(this);
          switch (_input->LA(1)) {
            case Python3Parser::STAR: {
              setState(409);
              match(Python3Parser::STAR);
              setState(411);
              _errHandler->sync(this);

              _la = _input->LA(1);
              if ((((_la & ~ 0x3fULL) == 0) &&
                ((1ULL << _la) & ((1ULL << Python3Parser::MATCH)
                | (1ULL << Python3Parser::UNDERSCORE)
                | (1ULL << Python3Parser::NAME))) != 0)) {
                setState(410);
                vfpdef();
              }
              setState(421);
              _errHandler->sync(this);
              alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 36, _ctx);
              while (alt != 2 && alt != atn::ATN::INVALID_ALT_NUMBER) {
                if (alt == 1) {
                  setState(413);
                  match(Python3Parser::COMMA);
                  setState(414);
                  vfpdef();
                  setState(417);
                  _errHandler->sync(this);

                  _la = _input->LA(1);
                  if (_la == Python3Parser::ASSIGN) {
                    setState(415);
                    match(Python3Parser::ASSIGN);
                    setState(416);
                    test();
                  } 
                }
                setState(423);
                _errHandler->sync(this);
                alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 36, _ctx);
              }
              setState(432);
              _errHandler->sync(this);

              _la = _input->LA(1);
              if (_la == Python3Parser::COMMA) {
                setState(424);
                match(Python3Parser::COMMA);
                setState(430);
                _errHandler->sync(this);

                _la = _input->LA(1);
                if (_la == Python3Parser::POWER) {
                  setState(425);
                  match(Python3Parser::POWER);
                  setState(426);
                  vfpdef();
                  setState(428);
                  _errHandler->sync(this);

                  _la = _input->LA(1);
                  if (_la == Python3Parser::COMMA) {
                    setState(427);
                    match(Python3Parser::COMMA);
                  }
                }
              }
              break;
            }

            case Python3Parser::POWER: {
              setState(434);
              match(Python3Parser::POWER);
              setState(435);
              vfpdef();
              setState(437);
              _errHandler->sync(this);

              _la = _input->LA(1);
              if (_la == Python3Parser::COMMA) {
                setState(436);
                match(Python3Parser::COMMA);
              }
              break;
            }

            case Python3Parser::COLON: {
              break;
            }

          default:
            break;
          }
        }
        break;
      }

      case Python3Parser::STAR: {
        setState(443);
        match(Python3Parser::STAR);
        setState(445);
        _errHandler->sync(this);

        _la = _input->LA(1);
        if ((((_la & ~ 0x3fULL) == 0) &&
          ((1ULL << _la) & ((1ULL << Python3Parser::MATCH)
          | (1ULL << Python3Parser::UNDERSCORE)
          | (1ULL << Python3Parser::NAME))) != 0)) {
          setState(444);
          vfpdef();
        }
        setState(455);
        _errHandler->sync(this);
        alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 45, _ctx);
        while (alt != 2 && alt != atn::ATN::INVALID_ALT_NUMBER) {
          if (alt == 1) {
            setState(447);
            match(Python3Parser::COMMA);
            setState(448);
            vfpdef();
            setState(451);
            _errHandler->sync(this);

            _la = _input->LA(1);
            if (_la == Python3Parser::ASSIGN) {
              setState(449);
              match(Python3Parser::ASSIGN);
              setState(450);
              test();
            } 
          }
          setState(457);
          _errHandler->sync(this);
          alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 45, _ctx);
        }
        setState(466);
        _errHandler->sync(this);

        _la = _input->LA(1);
        if (_la == Python3Parser::COMMA) {
          setState(458);
          match(Python3Parser::COMMA);
          setState(464);
          _errHandler->sync(this);

          _la = _input->LA(1);
          if (_la == Python3Parser::POWER) {
            setState(459);
            match(Python3Parser::POWER);
            setState(460);
            vfpdef();
            setState(462);
            _errHandler->sync(this);

            _la = _input->LA(1);
            if (_la == Python3Parser::COMMA) {
              setState(461);
              match(Python3Parser::COMMA);
            }
          }
        }
        break;
      }

      case Python3Parser::POWER: {
        setState(468);
        match(Python3Parser::POWER);
        setState(469);
        vfpdef();
        setState(471);
        _errHandler->sync(this);

        _la = _input->LA(1);
        if (_la == Python3Parser::COMMA) {
          setState(470);
          match(Python3Parser::COMMA);
        }
        break;
      }

    default:
      throw NoViableAltException(this);
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- VfpdefContext ------------------------------------------------------------------

Python3Parser::VfpdefContext::VfpdefContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

Python3Parser::NameContext* Python3Parser::VfpdefContext::name() {
  return getRuleContext<Python3Parser::NameContext>(0);
}


size_t Python3Parser::VfpdefContext::getRuleIndex() const {
  return Python3Parser::RuleVfpdef;
}

void Python3Parser::VfpdefContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<Python3ParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterVfpdef(this);
}

void Python3Parser::VfpdefContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<Python3ParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitVfpdef(this);
}


antlrcpp::Any Python3Parser::VfpdefContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<Python3ParserVisitor*>(visitor))
    return parserVisitor->visitVfpdef(this);
  else
    return visitor->visitChildren(this);
}

Python3Parser::VfpdefContext* Python3Parser::vfpdef() {
  VfpdefContext *_localctx = _tracker.createInstance<VfpdefContext>(_ctx, getState());
  enterRule(_localctx, 24, Python3Parser::RuleVfpdef);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(475);
    name();
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- StmtContext ------------------------------------------------------------------

Python3Parser::StmtContext::StmtContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

Python3Parser::Simple_stmtsContext* Python3Parser::StmtContext::simple_stmts() {
  return getRuleContext<Python3Parser::Simple_stmtsContext>(0);
}

Python3Parser::Compound_stmtContext* Python3Parser::StmtContext::compound_stmt() {
  return getRuleContext<Python3Parser::Compound_stmtContext>(0);
}


size_t Python3Parser::StmtContext::getRuleIndex() const {
  return Python3Parser::RuleStmt;
}

void Python3Parser::StmtContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<Python3ParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterStmt(this);
}

void Python3Parser::StmtContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<Python3ParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitStmt(this);
}


antlrcpp::Any Python3Parser::StmtContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<Python3ParserVisitor*>(visitor))
    return parserVisitor->visitStmt(this);
  else
    return visitor->visitChildren(this);
}

Python3Parser::StmtContext* Python3Parser::stmt() {
  StmtContext *_localctx = _tracker.createInstance<StmtContext>(_ctx, getState());
  enterRule(_localctx, 26, Python3Parser::RuleStmt);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    setState(479);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 51, _ctx)) {
    case 1: {
      enterOuterAlt(_localctx, 1);
      setState(477);
      simple_stmts();
      break;
    }

    case 2: {
      enterOuterAlt(_localctx, 2);
      setState(478);
      compound_stmt();
      break;
    }

    default:
      break;
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- Simple_stmtsContext ------------------------------------------------------------------

Python3Parser::Simple_stmtsContext::Simple_stmtsContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

std::vector<Python3Parser::Simple_stmtContext *> Python3Parser::Simple_stmtsContext::simple_stmt() {
  return getRuleContexts<Python3Parser::Simple_stmtContext>();
}

Python3Parser::Simple_stmtContext* Python3Parser::Simple_stmtsContext::simple_stmt(size_t i) {
  return getRuleContext<Python3Parser::Simple_stmtContext>(i);
}

tree::TerminalNode* Python3Parser::Simple_stmtsContext::NEWLINE() {
  return getToken(Python3Parser::NEWLINE, 0);
}

std::vector<tree::TerminalNode *> Python3Parser::Simple_stmtsContext::SEMI_COLON() {
  return getTokens(Python3Parser::SEMI_COLON);
}

tree::TerminalNode* Python3Parser::Simple_stmtsContext::SEMI_COLON(size_t i) {
  return getToken(Python3Parser::SEMI_COLON, i);
}


size_t Python3Parser::Simple_stmtsContext::getRuleIndex() const {
  return Python3Parser::RuleSimple_stmts;
}

void Python3Parser::Simple_stmtsContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<Python3ParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterSimple_stmts(this);
}

void Python3Parser::Simple_stmtsContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<Python3ParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitSimple_stmts(this);
}


antlrcpp::Any Python3Parser::Simple_stmtsContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<Python3ParserVisitor*>(visitor))
    return parserVisitor->visitSimple_stmts(this);
  else
    return visitor->visitChildren(this);
}

Python3Parser::Simple_stmtsContext* Python3Parser::simple_stmts() {
  Simple_stmtsContext *_localctx = _tracker.createInstance<Simple_stmtsContext>(_ctx, getState());
  enterRule(_localctx, 28, Python3Parser::RuleSimple_stmts);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    size_t alt;
    enterOuterAlt(_localctx, 1);
    setState(481);
    simple_stmt();
    setState(486);
    _errHandler->sync(this);
    alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 52, _ctx);
    while (alt != 2 && alt != atn::ATN::INVALID_ALT_NUMBER) {
      if (alt == 1) {
        setState(482);
        match(Python3Parser::SEMI_COLON);
        setState(483);
        simple_stmt(); 
      }
      setState(488);
      _errHandler->sync(this);
      alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 52, _ctx);
    }
    setState(490);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == Python3Parser::SEMI_COLON) {
      setState(489);
      match(Python3Parser::SEMI_COLON);
    }
    setState(492);
    match(Python3Parser::NEWLINE);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- Simple_stmtContext ------------------------------------------------------------------

Python3Parser::Simple_stmtContext::Simple_stmtContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

Python3Parser::Expr_stmtContext* Python3Parser::Simple_stmtContext::expr_stmt() {
  return getRuleContext<Python3Parser::Expr_stmtContext>(0);
}

Python3Parser::Del_stmtContext* Python3Parser::Simple_stmtContext::del_stmt() {
  return getRuleContext<Python3Parser::Del_stmtContext>(0);
}

Python3Parser::Pass_stmtContext* Python3Parser::Simple_stmtContext::pass_stmt() {
  return getRuleContext<Python3Parser::Pass_stmtContext>(0);
}

Python3Parser::Flow_stmtContext* Python3Parser::Simple_stmtContext::flow_stmt() {
  return getRuleContext<Python3Parser::Flow_stmtContext>(0);
}

Python3Parser::Import_stmtContext* Python3Parser::Simple_stmtContext::import_stmt() {
  return getRuleContext<Python3Parser::Import_stmtContext>(0);
}

Python3Parser::Global_stmtContext* Python3Parser::Simple_stmtContext::global_stmt() {
  return getRuleContext<Python3Parser::Global_stmtContext>(0);
}

Python3Parser::Nonlocal_stmtContext* Python3Parser::Simple_stmtContext::nonlocal_stmt() {
  return getRuleContext<Python3Parser::Nonlocal_stmtContext>(0);
}

Python3Parser::Assert_stmtContext* Python3Parser::Simple_stmtContext::assert_stmt() {
  return getRuleContext<Python3Parser::Assert_stmtContext>(0);
}


size_t Python3Parser::Simple_stmtContext::getRuleIndex() const {
  return Python3Parser::RuleSimple_stmt;
}

void Python3Parser::Simple_stmtContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<Python3ParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterSimple_stmt(this);
}

void Python3Parser::Simple_stmtContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<Python3ParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitSimple_stmt(this);
}


antlrcpp::Any Python3Parser::Simple_stmtContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<Python3ParserVisitor*>(visitor))
    return parserVisitor->visitSimple_stmt(this);
  else
    return visitor->visitChildren(this);
}

Python3Parser::Simple_stmtContext* Python3Parser::simple_stmt() {
  Simple_stmtContext *_localctx = _tracker.createInstance<Simple_stmtContext>(_ctx, getState());
  enterRule(_localctx, 30, Python3Parser::RuleSimple_stmt);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(502);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case Python3Parser::STRING:
      case Python3Parser::NUMBER:
      case Python3Parser::AWAIT:
      case Python3Parser::FALSE:
      case Python3Parser::LAMBDA:
      case Python3Parser::MATCH:
      case Python3Parser::NONE:
      case Python3Parser::NOT:
      case Python3Parser::TRUE:
      case Python3Parser::UNDERSCORE:
      case Python3Parser::NAME:
      case Python3Parser::ELLIPSIS:
      case Python3Parser::STAR:
      case Python3Parser::OPEN_PAREN:
      case Python3Parser::OPEN_BRACK:
      case Python3Parser::ADD:
      case Python3Parser::MINUS:
      case Python3Parser::NOT_OP:
      case Python3Parser::OPEN_BRACE: {
        setState(494);
        expr_stmt();
        break;
      }

      case Python3Parser::DEL: {
        setState(495);
        del_stmt();
        break;
      }

      case Python3Parser::PASS: {
        setState(496);
        pass_stmt();
        break;
      }

      case Python3Parser::BREAK:
      case Python3Parser::CONTINUE:
      case Python3Parser::RAISE:
      case Python3Parser::RETURN:
      case Python3Parser::YIELD: {
        setState(497);
        flow_stmt();
        break;
      }

      case Python3Parser::FROM:
      case Python3Parser::IMPORT: {
        setState(498);
        import_stmt();
        break;
      }

      case Python3Parser::GLOBAL: {
        setState(499);
        global_stmt();
        break;
      }

      case Python3Parser::NONLOCAL: {
        setState(500);
        nonlocal_stmt();
        break;
      }

      case Python3Parser::ASSERT: {
        setState(501);
        assert_stmt();
        break;
      }

    default:
      throw NoViableAltException(this);
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- Expr_stmtContext ------------------------------------------------------------------

Python3Parser::Expr_stmtContext::Expr_stmtContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

std::vector<Python3Parser::Testlist_star_exprContext *> Python3Parser::Expr_stmtContext::testlist_star_expr() {
  return getRuleContexts<Python3Parser::Testlist_star_exprContext>();
}

Python3Parser::Testlist_star_exprContext* Python3Parser::Expr_stmtContext::testlist_star_expr(size_t i) {
  return getRuleContext<Python3Parser::Testlist_star_exprContext>(i);
}

Python3Parser::AnnassignContext* Python3Parser::Expr_stmtContext::annassign() {
  return getRuleContext<Python3Parser::AnnassignContext>(0);
}

Python3Parser::AugassignContext* Python3Parser::Expr_stmtContext::augassign() {
  return getRuleContext<Python3Parser::AugassignContext>(0);
}

std::vector<Python3Parser::Yield_exprContext *> Python3Parser::Expr_stmtContext::yield_expr() {
  return getRuleContexts<Python3Parser::Yield_exprContext>();
}

Python3Parser::Yield_exprContext* Python3Parser::Expr_stmtContext::yield_expr(size_t i) {
  return getRuleContext<Python3Parser::Yield_exprContext>(i);
}

Python3Parser::TestlistContext* Python3Parser::Expr_stmtContext::testlist() {
  return getRuleContext<Python3Parser::TestlistContext>(0);
}

std::vector<tree::TerminalNode *> Python3Parser::Expr_stmtContext::ASSIGN() {
  return getTokens(Python3Parser::ASSIGN);
}

tree::TerminalNode* Python3Parser::Expr_stmtContext::ASSIGN(size_t i) {
  return getToken(Python3Parser::ASSIGN, i);
}


size_t Python3Parser::Expr_stmtContext::getRuleIndex() const {
  return Python3Parser::RuleExpr_stmt;
}

void Python3Parser::Expr_stmtContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<Python3ParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterExpr_stmt(this);
}

void Python3Parser::Expr_stmtContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<Python3ParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitExpr_stmt(this);
}


antlrcpp::Any Python3Parser::Expr_stmtContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<Python3ParserVisitor*>(visitor))
    return parserVisitor->visitExpr_stmt(this);
  else
    return visitor->visitChildren(this);
}

Python3Parser::Expr_stmtContext* Python3Parser::expr_stmt() {
  Expr_stmtContext *_localctx = _tracker.createInstance<Expr_stmtContext>(_ctx, getState());
  enterRule(_localctx, 32, Python3Parser::RuleExpr_stmt);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(504);
    testlist_star_expr();
    setState(521);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case Python3Parser::COLON: {
        setState(505);
        annassign();
        break;
      }

      case Python3Parser::ADD_ASSIGN:
      case Python3Parser::SUB_ASSIGN:
      case Python3Parser::MULT_ASSIGN:
      case Python3Parser::AT_ASSIGN:
      case Python3Parser::DIV_ASSIGN:
      case Python3Parser::MOD_ASSIGN:
      case Python3Parser::AND_ASSIGN:
      case Python3Parser::OR_ASSIGN:
      case Python3Parser::XOR_ASSIGN:
      case Python3Parser::LEFT_SHIFT_ASSIGN:
      case Python3Parser::RIGHT_SHIFT_ASSIGN:
      case Python3Parser::POWER_ASSIGN:
      case Python3Parser::IDIV_ASSIGN: {
        setState(506);
        augassign();
        setState(509);
        _errHandler->sync(this);
        switch (_input->LA(1)) {
          case Python3Parser::YIELD: {
            setState(507);
            yield_expr();
            break;
          }

          case Python3Parser::STRING:
          case Python3Parser::NUMBER:
          case Python3Parser::AWAIT:
          case Python3Parser::FALSE:
          case Python3Parser::LAMBDA:
          case Python3Parser::MATCH:
          case Python3Parser::NONE:
          case Python3Parser::NOT:
          case Python3Parser::TRUE:
          case Python3Parser::UNDERSCORE:
          case Python3Parser::NAME:
          case Python3Parser::ELLIPSIS:
          case Python3Parser::OPEN_PAREN:
          case Python3Parser::OPEN_BRACK:
          case Python3Parser::ADD:
          case Python3Parser::MINUS:
          case Python3Parser::NOT_OP:
          case Python3Parser::OPEN_BRACE: {
            setState(508);
            testlist();
            break;
          }

        default:
          throw NoViableAltException(this);
        }
        break;
      }

      case Python3Parser::NEWLINE:
      case Python3Parser::SEMI_COLON:
      case Python3Parser::ASSIGN: {
        setState(518);
        _errHandler->sync(this);
        _la = _input->LA(1);
        while (_la == Python3Parser::ASSIGN) {
          setState(511);
          match(Python3Parser::ASSIGN);
          setState(514);
          _errHandler->sync(this);
          switch (_input->LA(1)) {
            case Python3Parser::YIELD: {
              setState(512);
              yield_expr();
              break;
            }

            case Python3Parser::STRING:
            case Python3Parser::NUMBER:
            case Python3Parser::AWAIT:
            case Python3Parser::FALSE:
            case Python3Parser::LAMBDA:
            case Python3Parser::MATCH:
            case Python3Parser::NONE:
            case Python3Parser::NOT:
            case Python3Parser::TRUE:
            case Python3Parser::UNDERSCORE:
            case Python3Parser::NAME:
            case Python3Parser::ELLIPSIS:
            case Python3Parser::STAR:
            case Python3Parser::OPEN_PAREN:
            case Python3Parser::OPEN_BRACK:
            case Python3Parser::ADD:
            case Python3Parser::MINUS:
            case Python3Parser::NOT_OP:
            case Python3Parser::OPEN_BRACE: {
              setState(513);
              testlist_star_expr();
              break;
            }

          default:
            throw NoViableAltException(this);
          }
          setState(520);
          _errHandler->sync(this);
          _la = _input->LA(1);
        }
        break;
      }

    default:
      throw NoViableAltException(this);
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- AnnassignContext ------------------------------------------------------------------

Python3Parser::AnnassignContext::AnnassignContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* Python3Parser::AnnassignContext::COLON() {
  return getToken(Python3Parser::COLON, 0);
}

std::vector<Python3Parser::TestContext *> Python3Parser::AnnassignContext::test() {
  return getRuleContexts<Python3Parser::TestContext>();
}

Python3Parser::TestContext* Python3Parser::AnnassignContext::test(size_t i) {
  return getRuleContext<Python3Parser::TestContext>(i);
}

tree::TerminalNode* Python3Parser::AnnassignContext::ASSIGN() {
  return getToken(Python3Parser::ASSIGN, 0);
}


size_t Python3Parser::AnnassignContext::getRuleIndex() const {
  return Python3Parser::RuleAnnassign;
}

void Python3Parser::AnnassignContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<Python3ParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterAnnassign(this);
}

void Python3Parser::AnnassignContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<Python3ParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitAnnassign(this);
}


antlrcpp::Any Python3Parser::AnnassignContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<Python3ParserVisitor*>(visitor))
    return parserVisitor->visitAnnassign(this);
  else
    return visitor->visitChildren(this);
}

Python3Parser::AnnassignContext* Python3Parser::annassign() {
  AnnassignContext *_localctx = _tracker.createInstance<AnnassignContext>(_ctx, getState());
  enterRule(_localctx, 34, Python3Parser::RuleAnnassign);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(523);
    match(Python3Parser::COLON);
    setState(524);
    test();
    setState(527);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == Python3Parser::ASSIGN) {
      setState(525);
      match(Python3Parser::ASSIGN);
      setState(526);
      test();
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- Testlist_star_exprContext ------------------------------------------------------------------

Python3Parser::Testlist_star_exprContext::Testlist_star_exprContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

std::vector<Python3Parser::TestContext *> Python3Parser::Testlist_star_exprContext::test() {
  return getRuleContexts<Python3Parser::TestContext>();
}

Python3Parser::TestContext* Python3Parser::Testlist_star_exprContext::test(size_t i) {
  return getRuleContext<Python3Parser::TestContext>(i);
}

std::vector<Python3Parser::Star_exprContext *> Python3Parser::Testlist_star_exprContext::star_expr() {
  return getRuleContexts<Python3Parser::Star_exprContext>();
}

Python3Parser::Star_exprContext* Python3Parser::Testlist_star_exprContext::star_expr(size_t i) {
  return getRuleContext<Python3Parser::Star_exprContext>(i);
}

std::vector<tree::TerminalNode *> Python3Parser::Testlist_star_exprContext::COMMA() {
  return getTokens(Python3Parser::COMMA);
}

tree::TerminalNode* Python3Parser::Testlist_star_exprContext::COMMA(size_t i) {
  return getToken(Python3Parser::COMMA, i);
}


size_t Python3Parser::Testlist_star_exprContext::getRuleIndex() const {
  return Python3Parser::RuleTestlist_star_expr;
}

void Python3Parser::Testlist_star_exprContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<Python3ParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterTestlist_star_expr(this);
}

void Python3Parser::Testlist_star_exprContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<Python3ParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitTestlist_star_expr(this);
}


antlrcpp::Any Python3Parser::Testlist_star_exprContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<Python3ParserVisitor*>(visitor))
    return parserVisitor->visitTestlist_star_expr(this);
  else
    return visitor->visitChildren(this);
}

Python3Parser::Testlist_star_exprContext* Python3Parser::testlist_star_expr() {
  Testlist_star_exprContext *_localctx = _tracker.createInstance<Testlist_star_exprContext>(_ctx, getState());
  enterRule(_localctx, 36, Python3Parser::RuleTestlist_star_expr);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    size_t alt;
    enterOuterAlt(_localctx, 1);
    setState(531);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case Python3Parser::STRING:
      case Python3Parser::NUMBER:
      case Python3Parser::AWAIT:
      case Python3Parser::FALSE:
      case Python3Parser::LAMBDA:
      case Python3Parser::MATCH:
      case Python3Parser::NONE:
      case Python3Parser::NOT:
      case Python3Parser::TRUE:
      case Python3Parser::UNDERSCORE:
      case Python3Parser::NAME:
      case Python3Parser::ELLIPSIS:
      case Python3Parser::OPEN_PAREN:
      case Python3Parser::OPEN_BRACK:
      case Python3Parser::ADD:
      case Python3Parser::MINUS:
      case Python3Parser::NOT_OP:
      case Python3Parser::OPEN_BRACE: {
        setState(529);
        test();
        break;
      }

      case Python3Parser::STAR: {
        setState(530);
        star_expr();
        break;
      }

    default:
      throw NoViableAltException(this);
    }
    setState(540);
    _errHandler->sync(this);
    alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 62, _ctx);
    while (alt != 2 && alt != atn::ATN::INVALID_ALT_NUMBER) {
      if (alt == 1) {
        setState(533);
        match(Python3Parser::COMMA);
        setState(536);
        _errHandler->sync(this);
        switch (_input->LA(1)) {
          case Python3Parser::STRING:
          case Python3Parser::NUMBER:
          case Python3Parser::AWAIT:
          case Python3Parser::FALSE:
          case Python3Parser::LAMBDA:
          case Python3Parser::MATCH:
          case Python3Parser::NONE:
          case Python3Parser::NOT:
          case Python3Parser::TRUE:
          case Python3Parser::UNDERSCORE:
          case Python3Parser::NAME:
          case Python3Parser::ELLIPSIS:
          case Python3Parser::OPEN_PAREN:
          case Python3Parser::OPEN_BRACK:
          case Python3Parser::ADD:
          case Python3Parser::MINUS:
          case Python3Parser::NOT_OP:
          case Python3Parser::OPEN_BRACE: {
            setState(534);
            test();
            break;
          }

          case Python3Parser::STAR: {
            setState(535);
            star_expr();
            break;
          }

        default:
          throw NoViableAltException(this);
        } 
      }
      setState(542);
      _errHandler->sync(this);
      alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 62, _ctx);
    }
    setState(544);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == Python3Parser::COMMA) {
      setState(543);
      match(Python3Parser::COMMA);
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- AugassignContext ------------------------------------------------------------------

Python3Parser::AugassignContext::AugassignContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* Python3Parser::AugassignContext::ADD_ASSIGN() {
  return getToken(Python3Parser::ADD_ASSIGN, 0);
}

tree::TerminalNode* Python3Parser::AugassignContext::SUB_ASSIGN() {
  return getToken(Python3Parser::SUB_ASSIGN, 0);
}

tree::TerminalNode* Python3Parser::AugassignContext::MULT_ASSIGN() {
  return getToken(Python3Parser::MULT_ASSIGN, 0);
}

tree::TerminalNode* Python3Parser::AugassignContext::AT_ASSIGN() {
  return getToken(Python3Parser::AT_ASSIGN, 0);
}

tree::TerminalNode* Python3Parser::AugassignContext::DIV_ASSIGN() {
  return getToken(Python3Parser::DIV_ASSIGN, 0);
}

tree::TerminalNode* Python3Parser::AugassignContext::MOD_ASSIGN() {
  return getToken(Python3Parser::MOD_ASSIGN, 0);
}

tree::TerminalNode* Python3Parser::AugassignContext::AND_ASSIGN() {
  return getToken(Python3Parser::AND_ASSIGN, 0);
}

tree::TerminalNode* Python3Parser::AugassignContext::OR_ASSIGN() {
  return getToken(Python3Parser::OR_ASSIGN, 0);
}

tree::TerminalNode* Python3Parser::AugassignContext::XOR_ASSIGN() {
  return getToken(Python3Parser::XOR_ASSIGN, 0);
}

tree::TerminalNode* Python3Parser::AugassignContext::LEFT_SHIFT_ASSIGN() {
  return getToken(Python3Parser::LEFT_SHIFT_ASSIGN, 0);
}

tree::TerminalNode* Python3Parser::AugassignContext::RIGHT_SHIFT_ASSIGN() {
  return getToken(Python3Parser::RIGHT_SHIFT_ASSIGN, 0);
}

tree::TerminalNode* Python3Parser::AugassignContext::POWER_ASSIGN() {
  return getToken(Python3Parser::POWER_ASSIGN, 0);
}

tree::TerminalNode* Python3Parser::AugassignContext::IDIV_ASSIGN() {
  return getToken(Python3Parser::IDIV_ASSIGN, 0);
}


size_t Python3Parser::AugassignContext::getRuleIndex() const {
  return Python3Parser::RuleAugassign;
}

void Python3Parser::AugassignContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<Python3ParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterAugassign(this);
}

void Python3Parser::AugassignContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<Python3ParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitAugassign(this);
}


antlrcpp::Any Python3Parser::AugassignContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<Python3ParserVisitor*>(visitor))
    return parserVisitor->visitAugassign(this);
  else
    return visitor->visitChildren(this);
}

Python3Parser::AugassignContext* Python3Parser::augassign() {
  AugassignContext *_localctx = _tracker.createInstance<AugassignContext>(_ctx, getState());
  enterRule(_localctx, 38, Python3Parser::RuleAugassign);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(546);
    _la = _input->LA(1);
    if (!(((((_la - 88) & ~ 0x3fULL) == 0) &&
      ((1ULL << (_la - 88)) & ((1ULL << (Python3Parser::ADD_ASSIGN - 88))
      | (1ULL << (Python3Parser::SUB_ASSIGN - 88))
      | (1ULL << (Python3Parser::MULT_ASSIGN - 88))
      | (1ULL << (Python3Parser::AT_ASSIGN - 88))
      | (1ULL << (Python3Parser::DIV_ASSIGN - 88))
      | (1ULL << (Python3Parser::MOD_ASSIGN - 88))
      | (1ULL << (Python3Parser::AND_ASSIGN - 88))
      | (1ULL << (Python3Parser::OR_ASSIGN - 88))
      | (1ULL << (Python3Parser::XOR_ASSIGN - 88))
      | (1ULL << (Python3Parser::LEFT_SHIFT_ASSIGN - 88))
      | (1ULL << (Python3Parser::RIGHT_SHIFT_ASSIGN - 88))
      | (1ULL << (Python3Parser::POWER_ASSIGN - 88))
      | (1ULL << (Python3Parser::IDIV_ASSIGN - 88)))) != 0))) {
    _errHandler->recoverInline(this);
    }
    else {
      _errHandler->reportMatch(this);
      consume();
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- Del_stmtContext ------------------------------------------------------------------

Python3Parser::Del_stmtContext::Del_stmtContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* Python3Parser::Del_stmtContext::DEL() {
  return getToken(Python3Parser::DEL, 0);
}

Python3Parser::ExprlistContext* Python3Parser::Del_stmtContext::exprlist() {
  return getRuleContext<Python3Parser::ExprlistContext>(0);
}


size_t Python3Parser::Del_stmtContext::getRuleIndex() const {
  return Python3Parser::RuleDel_stmt;
}

void Python3Parser::Del_stmtContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<Python3ParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterDel_stmt(this);
}

void Python3Parser::Del_stmtContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<Python3ParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitDel_stmt(this);
}


antlrcpp::Any Python3Parser::Del_stmtContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<Python3ParserVisitor*>(visitor))
    return parserVisitor->visitDel_stmt(this);
  else
    return visitor->visitChildren(this);
}

Python3Parser::Del_stmtContext* Python3Parser::del_stmt() {
  Del_stmtContext *_localctx = _tracker.createInstance<Del_stmtContext>(_ctx, getState());
  enterRule(_localctx, 40, Python3Parser::RuleDel_stmt);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(548);
    match(Python3Parser::DEL);
    setState(549);
    exprlist();
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- Pass_stmtContext ------------------------------------------------------------------

Python3Parser::Pass_stmtContext::Pass_stmtContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* Python3Parser::Pass_stmtContext::PASS() {
  return getToken(Python3Parser::PASS, 0);
}


size_t Python3Parser::Pass_stmtContext::getRuleIndex() const {
  return Python3Parser::RulePass_stmt;
}

void Python3Parser::Pass_stmtContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<Python3ParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterPass_stmt(this);
}

void Python3Parser::Pass_stmtContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<Python3ParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitPass_stmt(this);
}


antlrcpp::Any Python3Parser::Pass_stmtContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<Python3ParserVisitor*>(visitor))
    return parserVisitor->visitPass_stmt(this);
  else
    return visitor->visitChildren(this);
}

Python3Parser::Pass_stmtContext* Python3Parser::pass_stmt() {
  Pass_stmtContext *_localctx = _tracker.createInstance<Pass_stmtContext>(_ctx, getState());
  enterRule(_localctx, 42, Python3Parser::RulePass_stmt);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(551);
    match(Python3Parser::PASS);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- Flow_stmtContext ------------------------------------------------------------------

Python3Parser::Flow_stmtContext::Flow_stmtContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

Python3Parser::Break_stmtContext* Python3Parser::Flow_stmtContext::break_stmt() {
  return getRuleContext<Python3Parser::Break_stmtContext>(0);
}

Python3Parser::Continue_stmtContext* Python3Parser::Flow_stmtContext::continue_stmt() {
  return getRuleContext<Python3Parser::Continue_stmtContext>(0);
}

Python3Parser::Return_stmtContext* Python3Parser::Flow_stmtContext::return_stmt() {
  return getRuleContext<Python3Parser::Return_stmtContext>(0);
}

Python3Parser::Raise_stmtContext* Python3Parser::Flow_stmtContext::raise_stmt() {
  return getRuleContext<Python3Parser::Raise_stmtContext>(0);
}

Python3Parser::Yield_stmtContext* Python3Parser::Flow_stmtContext::yield_stmt() {
  return getRuleContext<Python3Parser::Yield_stmtContext>(0);
}


size_t Python3Parser::Flow_stmtContext::getRuleIndex() const {
  return Python3Parser::RuleFlow_stmt;
}

void Python3Parser::Flow_stmtContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<Python3ParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterFlow_stmt(this);
}

void Python3Parser::Flow_stmtContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<Python3ParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitFlow_stmt(this);
}


antlrcpp::Any Python3Parser::Flow_stmtContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<Python3ParserVisitor*>(visitor))
    return parserVisitor->visitFlow_stmt(this);
  else
    return visitor->visitChildren(this);
}

Python3Parser::Flow_stmtContext* Python3Parser::flow_stmt() {
  Flow_stmtContext *_localctx = _tracker.createInstance<Flow_stmtContext>(_ctx, getState());
  enterRule(_localctx, 44, Python3Parser::RuleFlow_stmt);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    setState(558);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case Python3Parser::BREAK: {
        enterOuterAlt(_localctx, 1);
        setState(553);
        break_stmt();
        break;
      }

      case Python3Parser::CONTINUE: {
        enterOuterAlt(_localctx, 2);
        setState(554);
        continue_stmt();
        break;
      }

      case Python3Parser::RETURN: {
        enterOuterAlt(_localctx, 3);
        setState(555);
        return_stmt();
        break;
      }

      case Python3Parser::RAISE: {
        enterOuterAlt(_localctx, 4);
        setState(556);
        raise_stmt();
        break;
      }

      case Python3Parser::YIELD: {
        enterOuterAlt(_localctx, 5);
        setState(557);
        yield_stmt();
        break;
      }

    default:
      throw NoViableAltException(this);
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- Break_stmtContext ------------------------------------------------------------------

Python3Parser::Break_stmtContext::Break_stmtContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* Python3Parser::Break_stmtContext::BREAK() {
  return getToken(Python3Parser::BREAK, 0);
}


size_t Python3Parser::Break_stmtContext::getRuleIndex() const {
  return Python3Parser::RuleBreak_stmt;
}

void Python3Parser::Break_stmtContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<Python3ParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterBreak_stmt(this);
}

void Python3Parser::Break_stmtContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<Python3ParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitBreak_stmt(this);
}


antlrcpp::Any Python3Parser::Break_stmtContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<Python3ParserVisitor*>(visitor))
    return parserVisitor->visitBreak_stmt(this);
  else
    return visitor->visitChildren(this);
}

Python3Parser::Break_stmtContext* Python3Parser::break_stmt() {
  Break_stmtContext *_localctx = _tracker.createInstance<Break_stmtContext>(_ctx, getState());
  enterRule(_localctx, 46, Python3Parser::RuleBreak_stmt);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(560);
    match(Python3Parser::BREAK);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- Continue_stmtContext ------------------------------------------------------------------

Python3Parser::Continue_stmtContext::Continue_stmtContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* Python3Parser::Continue_stmtContext::CONTINUE() {
  return getToken(Python3Parser::CONTINUE, 0);
}


size_t Python3Parser::Continue_stmtContext::getRuleIndex() const {
  return Python3Parser::RuleContinue_stmt;
}

void Python3Parser::Continue_stmtContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<Python3ParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterContinue_stmt(this);
}

void Python3Parser::Continue_stmtContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<Python3ParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitContinue_stmt(this);
}


antlrcpp::Any Python3Parser::Continue_stmtContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<Python3ParserVisitor*>(visitor))
    return parserVisitor->visitContinue_stmt(this);
  else
    return visitor->visitChildren(this);
}

Python3Parser::Continue_stmtContext* Python3Parser::continue_stmt() {
  Continue_stmtContext *_localctx = _tracker.createInstance<Continue_stmtContext>(_ctx, getState());
  enterRule(_localctx, 48, Python3Parser::RuleContinue_stmt);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(562);
    match(Python3Parser::CONTINUE);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- Return_stmtContext ------------------------------------------------------------------

Python3Parser::Return_stmtContext::Return_stmtContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* Python3Parser::Return_stmtContext::RETURN() {
  return getToken(Python3Parser::RETURN, 0);
}

Python3Parser::TestlistContext* Python3Parser::Return_stmtContext::testlist() {
  return getRuleContext<Python3Parser::TestlistContext>(0);
}


size_t Python3Parser::Return_stmtContext::getRuleIndex() const {
  return Python3Parser::RuleReturn_stmt;
}

void Python3Parser::Return_stmtContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<Python3ParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterReturn_stmt(this);
}

void Python3Parser::Return_stmtContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<Python3ParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitReturn_stmt(this);
}


antlrcpp::Any Python3Parser::Return_stmtContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<Python3ParserVisitor*>(visitor))
    return parserVisitor->visitReturn_stmt(this);
  else
    return visitor->visitChildren(this);
}

Python3Parser::Return_stmtContext* Python3Parser::return_stmt() {
  Return_stmtContext *_localctx = _tracker.createInstance<Return_stmtContext>(_ctx, getState());
  enterRule(_localctx, 50, Python3Parser::RuleReturn_stmt);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(564);
    match(Python3Parser::RETURN);
    setState(566);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if ((((_la & ~ 0x3fULL) == 0) &&
      ((1ULL << _la) & ((1ULL << Python3Parser::STRING)
      | (1ULL << Python3Parser::NUMBER)
      | (1ULL << Python3Parser::AWAIT)
      | (1ULL << Python3Parser::FALSE)
      | (1ULL << Python3Parser::LAMBDA)
      | (1ULL << Python3Parser::MATCH)
      | (1ULL << Python3Parser::NONE)
      | (1ULL << Python3Parser::NOT)
      | (1ULL << Python3Parser::TRUE)
      | (1ULL << Python3Parser::UNDERSCORE)
      | (1ULL << Python3Parser::NAME)
      | (1ULL << Python3Parser::ELLIPSIS)
      | (1ULL << Python3Parser::OPEN_PAREN))) != 0) || ((((_la - 64) & ~ 0x3fULL) == 0) &&
      ((1ULL << (_la - 64)) & ((1ULL << (Python3Parser::OPEN_BRACK - 64))
      | (1ULL << (Python3Parser::ADD - 64))
      | (1ULL << (Python3Parser::MINUS - 64))
      | (1ULL << (Python3Parser::NOT_OP - 64))
      | (1ULL << (Python3Parser::OPEN_BRACE - 64)))) != 0)) {
      setState(565);
      testlist();
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- Yield_stmtContext ------------------------------------------------------------------

Python3Parser::Yield_stmtContext::Yield_stmtContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

Python3Parser::Yield_exprContext* Python3Parser::Yield_stmtContext::yield_expr() {
  return getRuleContext<Python3Parser::Yield_exprContext>(0);
}


size_t Python3Parser::Yield_stmtContext::getRuleIndex() const {
  return Python3Parser::RuleYield_stmt;
}

void Python3Parser::Yield_stmtContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<Python3ParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterYield_stmt(this);
}

void Python3Parser::Yield_stmtContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<Python3ParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitYield_stmt(this);
}


antlrcpp::Any Python3Parser::Yield_stmtContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<Python3ParserVisitor*>(visitor))
    return parserVisitor->visitYield_stmt(this);
  else
    return visitor->visitChildren(this);
}

Python3Parser::Yield_stmtContext* Python3Parser::yield_stmt() {
  Yield_stmtContext *_localctx = _tracker.createInstance<Yield_stmtContext>(_ctx, getState());
  enterRule(_localctx, 52, Python3Parser::RuleYield_stmt);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(568);
    yield_expr();
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- Raise_stmtContext ------------------------------------------------------------------

Python3Parser::Raise_stmtContext::Raise_stmtContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* Python3Parser::Raise_stmtContext::RAISE() {
  return getToken(Python3Parser::RAISE, 0);
}

std::vector<Python3Parser::TestContext *> Python3Parser::Raise_stmtContext::test() {
  return getRuleContexts<Python3Parser::TestContext>();
}

Python3Parser::TestContext* Python3Parser::Raise_stmtContext::test(size_t i) {
  return getRuleContext<Python3Parser::TestContext>(i);
}

tree::TerminalNode* Python3Parser::Raise_stmtContext::FROM() {
  return getToken(Python3Parser::FROM, 0);
}


size_t Python3Parser::Raise_stmtContext::getRuleIndex() const {
  return Python3Parser::RuleRaise_stmt;
}

void Python3Parser::Raise_stmtContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<Python3ParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterRaise_stmt(this);
}

void Python3Parser::Raise_stmtContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<Python3ParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitRaise_stmt(this);
}


antlrcpp::Any Python3Parser::Raise_stmtContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<Python3ParserVisitor*>(visitor))
    return parserVisitor->visitRaise_stmt(this);
  else
    return visitor->visitChildren(this);
}

Python3Parser::Raise_stmtContext* Python3Parser::raise_stmt() {
  Raise_stmtContext *_localctx = _tracker.createInstance<Raise_stmtContext>(_ctx, getState());
  enterRule(_localctx, 54, Python3Parser::RuleRaise_stmt);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(570);
    match(Python3Parser::RAISE);
    setState(576);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if ((((_la & ~ 0x3fULL) == 0) &&
      ((1ULL << _la) & ((1ULL << Python3Parser::STRING)
      | (1ULL << Python3Parser::NUMBER)
      | (1ULL << Python3Parser::AWAIT)
      | (1ULL << Python3Parser::FALSE)
      | (1ULL << Python3Parser::LAMBDA)
      | (1ULL << Python3Parser::MATCH)
      | (1ULL << Python3Parser::NONE)
      | (1ULL << Python3Parser::NOT)
      | (1ULL << Python3Parser::TRUE)
      | (1ULL << Python3Parser::UNDERSCORE)
      | (1ULL << Python3Parser::NAME)
      | (1ULL << Python3Parser::ELLIPSIS)
      | (1ULL << Python3Parser::OPEN_PAREN))) != 0) || ((((_la - 64) & ~ 0x3fULL) == 0) &&
      ((1ULL << (_la - 64)) & ((1ULL << (Python3Parser::OPEN_BRACK - 64))
      | (1ULL << (Python3Parser::ADD - 64))
      | (1ULL << (Python3Parser::MINUS - 64))
      | (1ULL << (Python3Parser::NOT_OP - 64))
      | (1ULL << (Python3Parser::OPEN_BRACE - 64)))) != 0)) {
      setState(571);
      test();
      setState(574);
      _errHandler->sync(this);

      _la = _input->LA(1);
      if (_la == Python3Parser::FROM) {
        setState(572);
        match(Python3Parser::FROM);
        setState(573);
        test();
      }
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- Import_stmtContext ------------------------------------------------------------------

Python3Parser::Import_stmtContext::Import_stmtContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

Python3Parser::Import_nameContext* Python3Parser::Import_stmtContext::import_name() {
  return getRuleContext<Python3Parser::Import_nameContext>(0);
}

Python3Parser::Import_fromContext* Python3Parser::Import_stmtContext::import_from() {
  return getRuleContext<Python3Parser::Import_fromContext>(0);
}


size_t Python3Parser::Import_stmtContext::getRuleIndex() const {
  return Python3Parser::RuleImport_stmt;
}

void Python3Parser::Import_stmtContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<Python3ParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterImport_stmt(this);
}

void Python3Parser::Import_stmtContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<Python3ParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitImport_stmt(this);
}


antlrcpp::Any Python3Parser::Import_stmtContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<Python3ParserVisitor*>(visitor))
    return parserVisitor->visitImport_stmt(this);
  else
    return visitor->visitChildren(this);
}

Python3Parser::Import_stmtContext* Python3Parser::import_stmt() {
  Import_stmtContext *_localctx = _tracker.createInstance<Import_stmtContext>(_ctx, getState());
  enterRule(_localctx, 56, Python3Parser::RuleImport_stmt);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    setState(580);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case Python3Parser::IMPORT: {
        enterOuterAlt(_localctx, 1);
        setState(578);
        import_name();
        break;
      }

      case Python3Parser::FROM: {
        enterOuterAlt(_localctx, 2);
        setState(579);
        import_from();
        break;
      }

    default:
      throw NoViableAltException(this);
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- Import_nameContext ------------------------------------------------------------------

Python3Parser::Import_nameContext::Import_nameContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* Python3Parser::Import_nameContext::IMPORT() {
  return getToken(Python3Parser::IMPORT, 0);
}

Python3Parser::Dotted_as_namesContext* Python3Parser::Import_nameContext::dotted_as_names() {
  return getRuleContext<Python3Parser::Dotted_as_namesContext>(0);
}


size_t Python3Parser::Import_nameContext::getRuleIndex() const {
  return Python3Parser::RuleImport_name;
}

void Python3Parser::Import_nameContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<Python3ParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterImport_name(this);
}

void Python3Parser::Import_nameContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<Python3ParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitImport_name(this);
}


antlrcpp::Any Python3Parser::Import_nameContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<Python3ParserVisitor*>(visitor))
    return parserVisitor->visitImport_name(this);
  else
    return visitor->visitChildren(this);
}

Python3Parser::Import_nameContext* Python3Parser::import_name() {
  Import_nameContext *_localctx = _tracker.createInstance<Import_nameContext>(_ctx, getState());
  enterRule(_localctx, 58, Python3Parser::RuleImport_name);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(582);
    match(Python3Parser::IMPORT);
    setState(583);
    dotted_as_names();
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- Import_fromContext ------------------------------------------------------------------

Python3Parser::Import_fromContext::Import_fromContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* Python3Parser::Import_fromContext::FROM() {
  return getToken(Python3Parser::FROM, 0);
}

tree::TerminalNode* Python3Parser::Import_fromContext::IMPORT() {
  return getToken(Python3Parser::IMPORT, 0);
}

Python3Parser::Dotted_nameContext* Python3Parser::Import_fromContext::dotted_name() {
  return getRuleContext<Python3Parser::Dotted_nameContext>(0);
}

tree::TerminalNode* Python3Parser::Import_fromContext::STAR() {
  return getToken(Python3Parser::STAR, 0);
}

tree::TerminalNode* Python3Parser::Import_fromContext::OPEN_PAREN() {
  return getToken(Python3Parser::OPEN_PAREN, 0);
}

Python3Parser::Import_as_namesContext* Python3Parser::Import_fromContext::import_as_names() {
  return getRuleContext<Python3Parser::Import_as_namesContext>(0);
}

tree::TerminalNode* Python3Parser::Import_fromContext::CLOSE_PAREN() {
  return getToken(Python3Parser::CLOSE_PAREN, 0);
}

std::vector<tree::TerminalNode *> Python3Parser::Import_fromContext::DOT() {
  return getTokens(Python3Parser::DOT);
}

tree::TerminalNode* Python3Parser::Import_fromContext::DOT(size_t i) {
  return getToken(Python3Parser::DOT, i);
}

std::vector<tree::TerminalNode *> Python3Parser::Import_fromContext::ELLIPSIS() {
  return getTokens(Python3Parser::ELLIPSIS);
}

tree::TerminalNode* Python3Parser::Import_fromContext::ELLIPSIS(size_t i) {
  return getToken(Python3Parser::ELLIPSIS, i);
}


size_t Python3Parser::Import_fromContext::getRuleIndex() const {
  return Python3Parser::RuleImport_from;
}

void Python3Parser::Import_fromContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<Python3ParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterImport_from(this);
}

void Python3Parser::Import_fromContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<Python3ParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitImport_from(this);
}


antlrcpp::Any Python3Parser::Import_fromContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<Python3ParserVisitor*>(visitor))
    return parserVisitor->visitImport_from(this);
  else
    return visitor->visitChildren(this);
}

Python3Parser::Import_fromContext* Python3Parser::import_from() {
  Import_fromContext *_localctx = _tracker.createInstance<Import_fromContext>(_ctx, getState());
  enterRule(_localctx, 60, Python3Parser::RuleImport_from);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(585);
    match(Python3Parser::FROM);
    setState(598);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 71, _ctx)) {
    case 1: {
      setState(589);
      _errHandler->sync(this);
      _la = _input->LA(1);
      while (_la == Python3Parser::DOT

      || _la == Python3Parser::ELLIPSIS) {
        setState(586);
        _la = _input->LA(1);
        if (!(_la == Python3Parser::DOT

        || _la == Python3Parser::ELLIPSIS)) {
        _errHandler->recoverInline(this);
        }
        else {
          _errHandler->reportMatch(this);
          consume();
        }
        setState(591);
        _errHandler->sync(this);
        _la = _input->LA(1);
      }
      setState(592);
      dotted_name();
      break;
    }

    case 2: {
      setState(594); 
      _errHandler->sync(this);
      _la = _input->LA(1);
      do {
        setState(593);
        _la = _input->LA(1);
        if (!(_la == Python3Parser::DOT

        || _la == Python3Parser::ELLIPSIS)) {
        _errHandler->recoverInline(this);
        }
        else {
          _errHandler->reportMatch(this);
          consume();
        }
        setState(596); 
        _errHandler->sync(this);
        _la = _input->LA(1);
      } while (_la == Python3Parser::DOT

      || _la == Python3Parser::ELLIPSIS);
      break;
    }

    default:
      break;
    }
    setState(600);
    match(Python3Parser::IMPORT);
    setState(607);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case Python3Parser::STAR: {
        setState(601);
        match(Python3Parser::STAR);
        break;
      }

      case Python3Parser::OPEN_PAREN: {
        setState(602);
        match(Python3Parser::OPEN_PAREN);
        setState(603);
        import_as_names();
        setState(604);
        match(Python3Parser::CLOSE_PAREN);
        break;
      }

      case Python3Parser::MATCH:
      case Python3Parser::UNDERSCORE:
      case Python3Parser::NAME: {
        setState(606);
        import_as_names();
        break;
      }

    default:
      throw NoViableAltException(this);
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- Import_as_nameContext ------------------------------------------------------------------

Python3Parser::Import_as_nameContext::Import_as_nameContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

std::vector<Python3Parser::NameContext *> Python3Parser::Import_as_nameContext::name() {
  return getRuleContexts<Python3Parser::NameContext>();
}

Python3Parser::NameContext* Python3Parser::Import_as_nameContext::name(size_t i) {
  return getRuleContext<Python3Parser::NameContext>(i);
}

tree::TerminalNode* Python3Parser::Import_as_nameContext::AS() {
  return getToken(Python3Parser::AS, 0);
}


size_t Python3Parser::Import_as_nameContext::getRuleIndex() const {
  return Python3Parser::RuleImport_as_name;
}

void Python3Parser::Import_as_nameContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<Python3ParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterImport_as_name(this);
}

void Python3Parser::Import_as_nameContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<Python3ParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitImport_as_name(this);
}


antlrcpp::Any Python3Parser::Import_as_nameContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<Python3ParserVisitor*>(visitor))
    return parserVisitor->visitImport_as_name(this);
  else
    return visitor->visitChildren(this);
}

Python3Parser::Import_as_nameContext* Python3Parser::import_as_name() {
  Import_as_nameContext *_localctx = _tracker.createInstance<Import_as_nameContext>(_ctx, getState());
  enterRule(_localctx, 62, Python3Parser::RuleImport_as_name);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(609);
    name();
    setState(612);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == Python3Parser::AS) {
      setState(610);
      match(Python3Parser::AS);
      setState(611);
      name();
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- Dotted_as_nameContext ------------------------------------------------------------------

Python3Parser::Dotted_as_nameContext::Dotted_as_nameContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

Python3Parser::Dotted_nameContext* Python3Parser::Dotted_as_nameContext::dotted_name() {
  return getRuleContext<Python3Parser::Dotted_nameContext>(0);
}

tree::TerminalNode* Python3Parser::Dotted_as_nameContext::AS() {
  return getToken(Python3Parser::AS, 0);
}

Python3Parser::NameContext* Python3Parser::Dotted_as_nameContext::name() {
  return getRuleContext<Python3Parser::NameContext>(0);
}


size_t Python3Parser::Dotted_as_nameContext::getRuleIndex() const {
  return Python3Parser::RuleDotted_as_name;
}

void Python3Parser::Dotted_as_nameContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<Python3ParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterDotted_as_name(this);
}

void Python3Parser::Dotted_as_nameContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<Python3ParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitDotted_as_name(this);
}


antlrcpp::Any Python3Parser::Dotted_as_nameContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<Python3ParserVisitor*>(visitor))
    return parserVisitor->visitDotted_as_name(this);
  else
    return visitor->visitChildren(this);
}

Python3Parser::Dotted_as_nameContext* Python3Parser::dotted_as_name() {
  Dotted_as_nameContext *_localctx = _tracker.createInstance<Dotted_as_nameContext>(_ctx, getState());
  enterRule(_localctx, 64, Python3Parser::RuleDotted_as_name);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(614);
    dotted_name();
    setState(617);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == Python3Parser::AS) {
      setState(615);
      match(Python3Parser::AS);
      setState(616);
      name();
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- Import_as_namesContext ------------------------------------------------------------------

Python3Parser::Import_as_namesContext::Import_as_namesContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

std::vector<Python3Parser::Import_as_nameContext *> Python3Parser::Import_as_namesContext::import_as_name() {
  return getRuleContexts<Python3Parser::Import_as_nameContext>();
}

Python3Parser::Import_as_nameContext* Python3Parser::Import_as_namesContext::import_as_name(size_t i) {
  return getRuleContext<Python3Parser::Import_as_nameContext>(i);
}

std::vector<tree::TerminalNode *> Python3Parser::Import_as_namesContext::COMMA() {
  return getTokens(Python3Parser::COMMA);
}

tree::TerminalNode* Python3Parser::Import_as_namesContext::COMMA(size_t i) {
  return getToken(Python3Parser::COMMA, i);
}


size_t Python3Parser::Import_as_namesContext::getRuleIndex() const {
  return Python3Parser::RuleImport_as_names;
}

void Python3Parser::Import_as_namesContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<Python3ParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterImport_as_names(this);
}

void Python3Parser::Import_as_namesContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<Python3ParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitImport_as_names(this);
}


antlrcpp::Any Python3Parser::Import_as_namesContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<Python3ParserVisitor*>(visitor))
    return parserVisitor->visitImport_as_names(this);
  else
    return visitor->visitChildren(this);
}

Python3Parser::Import_as_namesContext* Python3Parser::import_as_names() {
  Import_as_namesContext *_localctx = _tracker.createInstance<Import_as_namesContext>(_ctx, getState());
  enterRule(_localctx, 66, Python3Parser::RuleImport_as_names);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    size_t alt;
    enterOuterAlt(_localctx, 1);
    setState(619);
    import_as_name();
    setState(624);
    _errHandler->sync(this);
    alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 75, _ctx);
    while (alt != 2 && alt != atn::ATN::INVALID_ALT_NUMBER) {
      if (alt == 1) {
        setState(620);
        match(Python3Parser::COMMA);
        setState(621);
        import_as_name(); 
      }
      setState(626);
      _errHandler->sync(this);
      alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 75, _ctx);
    }
    setState(628);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == Python3Parser::COMMA) {
      setState(627);
      match(Python3Parser::COMMA);
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- Dotted_as_namesContext ------------------------------------------------------------------

Python3Parser::Dotted_as_namesContext::Dotted_as_namesContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

std::vector<Python3Parser::Dotted_as_nameContext *> Python3Parser::Dotted_as_namesContext::dotted_as_name() {
  return getRuleContexts<Python3Parser::Dotted_as_nameContext>();
}

Python3Parser::Dotted_as_nameContext* Python3Parser::Dotted_as_namesContext::dotted_as_name(size_t i) {
  return getRuleContext<Python3Parser::Dotted_as_nameContext>(i);
}

std::vector<tree::TerminalNode *> Python3Parser::Dotted_as_namesContext::COMMA() {
  return getTokens(Python3Parser::COMMA);
}

tree::TerminalNode* Python3Parser::Dotted_as_namesContext::COMMA(size_t i) {
  return getToken(Python3Parser::COMMA, i);
}


size_t Python3Parser::Dotted_as_namesContext::getRuleIndex() const {
  return Python3Parser::RuleDotted_as_names;
}

void Python3Parser::Dotted_as_namesContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<Python3ParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterDotted_as_names(this);
}

void Python3Parser::Dotted_as_namesContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<Python3ParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitDotted_as_names(this);
}


antlrcpp::Any Python3Parser::Dotted_as_namesContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<Python3ParserVisitor*>(visitor))
    return parserVisitor->visitDotted_as_names(this);
  else
    return visitor->visitChildren(this);
}

Python3Parser::Dotted_as_namesContext* Python3Parser::dotted_as_names() {
  Dotted_as_namesContext *_localctx = _tracker.createInstance<Dotted_as_namesContext>(_ctx, getState());
  enterRule(_localctx, 68, Python3Parser::RuleDotted_as_names);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(630);
    dotted_as_name();
    setState(635);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while (_la == Python3Parser::COMMA) {
      setState(631);
      match(Python3Parser::COMMA);
      setState(632);
      dotted_as_name();
      setState(637);
      _errHandler->sync(this);
      _la = _input->LA(1);
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- Dotted_nameContext ------------------------------------------------------------------

Python3Parser::Dotted_nameContext::Dotted_nameContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

std::vector<Python3Parser::NameContext *> Python3Parser::Dotted_nameContext::name() {
  return getRuleContexts<Python3Parser::NameContext>();
}

Python3Parser::NameContext* Python3Parser::Dotted_nameContext::name(size_t i) {
  return getRuleContext<Python3Parser::NameContext>(i);
}

std::vector<tree::TerminalNode *> Python3Parser::Dotted_nameContext::DOT() {
  return getTokens(Python3Parser::DOT);
}

tree::TerminalNode* Python3Parser::Dotted_nameContext::DOT(size_t i) {
  return getToken(Python3Parser::DOT, i);
}


size_t Python3Parser::Dotted_nameContext::getRuleIndex() const {
  return Python3Parser::RuleDotted_name;
}

void Python3Parser::Dotted_nameContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<Python3ParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterDotted_name(this);
}

void Python3Parser::Dotted_nameContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<Python3ParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitDotted_name(this);
}


antlrcpp::Any Python3Parser::Dotted_nameContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<Python3ParserVisitor*>(visitor))
    return parserVisitor->visitDotted_name(this);
  else
    return visitor->visitChildren(this);
}

Python3Parser::Dotted_nameContext* Python3Parser::dotted_name() {
  Dotted_nameContext *_localctx = _tracker.createInstance<Dotted_nameContext>(_ctx, getState());
  enterRule(_localctx, 70, Python3Parser::RuleDotted_name);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(638);
    name();
    setState(643);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while (_la == Python3Parser::DOT) {
      setState(639);
      match(Python3Parser::DOT);
      setState(640);
      name();
      setState(645);
      _errHandler->sync(this);
      _la = _input->LA(1);
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- Global_stmtContext ------------------------------------------------------------------

Python3Parser::Global_stmtContext::Global_stmtContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* Python3Parser::Global_stmtContext::GLOBAL() {
  return getToken(Python3Parser::GLOBAL, 0);
}

std::vector<Python3Parser::NameContext *> Python3Parser::Global_stmtContext::name() {
  return getRuleContexts<Python3Parser::NameContext>();
}

Python3Parser::NameContext* Python3Parser::Global_stmtContext::name(size_t i) {
  return getRuleContext<Python3Parser::NameContext>(i);
}

std::vector<tree::TerminalNode *> Python3Parser::Global_stmtContext::COMMA() {
  return getTokens(Python3Parser::COMMA);
}

tree::TerminalNode* Python3Parser::Global_stmtContext::COMMA(size_t i) {
  return getToken(Python3Parser::COMMA, i);
}


size_t Python3Parser::Global_stmtContext::getRuleIndex() const {
  return Python3Parser::RuleGlobal_stmt;
}

void Python3Parser::Global_stmtContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<Python3ParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterGlobal_stmt(this);
}

void Python3Parser::Global_stmtContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<Python3ParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitGlobal_stmt(this);
}


antlrcpp::Any Python3Parser::Global_stmtContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<Python3ParserVisitor*>(visitor))
    return parserVisitor->visitGlobal_stmt(this);
  else
    return visitor->visitChildren(this);
}

Python3Parser::Global_stmtContext* Python3Parser::global_stmt() {
  Global_stmtContext *_localctx = _tracker.createInstance<Global_stmtContext>(_ctx, getState());
  enterRule(_localctx, 72, Python3Parser::RuleGlobal_stmt);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(646);
    match(Python3Parser::GLOBAL);
    setState(647);
    name();
    setState(652);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while (_la == Python3Parser::COMMA) {
      setState(648);
      match(Python3Parser::COMMA);
      setState(649);
      name();
      setState(654);
      _errHandler->sync(this);
      _la = _input->LA(1);
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- Nonlocal_stmtContext ------------------------------------------------------------------

Python3Parser::Nonlocal_stmtContext::Nonlocal_stmtContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* Python3Parser::Nonlocal_stmtContext::NONLOCAL() {
  return getToken(Python3Parser::NONLOCAL, 0);
}

std::vector<Python3Parser::NameContext *> Python3Parser::Nonlocal_stmtContext::name() {
  return getRuleContexts<Python3Parser::NameContext>();
}

Python3Parser::NameContext* Python3Parser::Nonlocal_stmtContext::name(size_t i) {
  return getRuleContext<Python3Parser::NameContext>(i);
}

std::vector<tree::TerminalNode *> Python3Parser::Nonlocal_stmtContext::COMMA() {
  return getTokens(Python3Parser::COMMA);
}

tree::TerminalNode* Python3Parser::Nonlocal_stmtContext::COMMA(size_t i) {
  return getToken(Python3Parser::COMMA, i);
}


size_t Python3Parser::Nonlocal_stmtContext::getRuleIndex() const {
  return Python3Parser::RuleNonlocal_stmt;
}

void Python3Parser::Nonlocal_stmtContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<Python3ParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterNonlocal_stmt(this);
}

void Python3Parser::Nonlocal_stmtContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<Python3ParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitNonlocal_stmt(this);
}


antlrcpp::Any Python3Parser::Nonlocal_stmtContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<Python3ParserVisitor*>(visitor))
    return parserVisitor->visitNonlocal_stmt(this);
  else
    return visitor->visitChildren(this);
}

Python3Parser::Nonlocal_stmtContext* Python3Parser::nonlocal_stmt() {
  Nonlocal_stmtContext *_localctx = _tracker.createInstance<Nonlocal_stmtContext>(_ctx, getState());
  enterRule(_localctx, 74, Python3Parser::RuleNonlocal_stmt);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(655);
    match(Python3Parser::NONLOCAL);
    setState(656);
    name();
    setState(661);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while (_la == Python3Parser::COMMA) {
      setState(657);
      match(Python3Parser::COMMA);
      setState(658);
      name();
      setState(663);
      _errHandler->sync(this);
      _la = _input->LA(1);
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- Assert_stmtContext ------------------------------------------------------------------

Python3Parser::Assert_stmtContext::Assert_stmtContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* Python3Parser::Assert_stmtContext::ASSERT() {
  return getToken(Python3Parser::ASSERT, 0);
}

std::vector<Python3Parser::TestContext *> Python3Parser::Assert_stmtContext::test() {
  return getRuleContexts<Python3Parser::TestContext>();
}

Python3Parser::TestContext* Python3Parser::Assert_stmtContext::test(size_t i) {
  return getRuleContext<Python3Parser::TestContext>(i);
}

tree::TerminalNode* Python3Parser::Assert_stmtContext::COMMA() {
  return getToken(Python3Parser::COMMA, 0);
}


size_t Python3Parser::Assert_stmtContext::getRuleIndex() const {
  return Python3Parser::RuleAssert_stmt;
}

void Python3Parser::Assert_stmtContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<Python3ParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterAssert_stmt(this);
}

void Python3Parser::Assert_stmtContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<Python3ParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitAssert_stmt(this);
}


antlrcpp::Any Python3Parser::Assert_stmtContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<Python3ParserVisitor*>(visitor))
    return parserVisitor->visitAssert_stmt(this);
  else
    return visitor->visitChildren(this);
}

Python3Parser::Assert_stmtContext* Python3Parser::assert_stmt() {
  Assert_stmtContext *_localctx = _tracker.createInstance<Assert_stmtContext>(_ctx, getState());
  enterRule(_localctx, 76, Python3Parser::RuleAssert_stmt);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(664);
    match(Python3Parser::ASSERT);
    setState(665);
    test();
    setState(668);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == Python3Parser::COMMA) {
      setState(666);
      match(Python3Parser::COMMA);
      setState(667);
      test();
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- Compound_stmtContext ------------------------------------------------------------------

Python3Parser::Compound_stmtContext::Compound_stmtContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

Python3Parser::If_stmtContext* Python3Parser::Compound_stmtContext::if_stmt() {
  return getRuleContext<Python3Parser::If_stmtContext>(0);
}

Python3Parser::While_stmtContext* Python3Parser::Compound_stmtContext::while_stmt() {
  return getRuleContext<Python3Parser::While_stmtContext>(0);
}

Python3Parser::For_stmtContext* Python3Parser::Compound_stmtContext::for_stmt() {
  return getRuleContext<Python3Parser::For_stmtContext>(0);
}

Python3Parser::Try_stmtContext* Python3Parser::Compound_stmtContext::try_stmt() {
  return getRuleContext<Python3Parser::Try_stmtContext>(0);
}

Python3Parser::With_stmtContext* Python3Parser::Compound_stmtContext::with_stmt() {
  return getRuleContext<Python3Parser::With_stmtContext>(0);
}

Python3Parser::FuncdefContext* Python3Parser::Compound_stmtContext::funcdef() {
  return getRuleContext<Python3Parser::FuncdefContext>(0);
}

Python3Parser::ClassdefContext* Python3Parser::Compound_stmtContext::classdef() {
  return getRuleContext<Python3Parser::ClassdefContext>(0);
}

Python3Parser::DecoratedContext* Python3Parser::Compound_stmtContext::decorated() {
  return getRuleContext<Python3Parser::DecoratedContext>(0);
}

Python3Parser::Async_stmtContext* Python3Parser::Compound_stmtContext::async_stmt() {
  return getRuleContext<Python3Parser::Async_stmtContext>(0);
}

Python3Parser::Match_stmtContext* Python3Parser::Compound_stmtContext::match_stmt() {
  return getRuleContext<Python3Parser::Match_stmtContext>(0);
}


size_t Python3Parser::Compound_stmtContext::getRuleIndex() const {
  return Python3Parser::RuleCompound_stmt;
}

void Python3Parser::Compound_stmtContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<Python3ParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterCompound_stmt(this);
}

void Python3Parser::Compound_stmtContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<Python3ParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitCompound_stmt(this);
}


antlrcpp::Any Python3Parser::Compound_stmtContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<Python3ParserVisitor*>(visitor))
    return parserVisitor->visitCompound_stmt(this);
  else
    return visitor->visitChildren(this);
}

Python3Parser::Compound_stmtContext* Python3Parser::compound_stmt() {
  Compound_stmtContext *_localctx = _tracker.createInstance<Compound_stmtContext>(_ctx, getState());
  enterRule(_localctx, 78, Python3Parser::RuleCompound_stmt);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    setState(680);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case Python3Parser::IF: {
        enterOuterAlt(_localctx, 1);
        setState(670);
        if_stmt();
        break;
      }

      case Python3Parser::WHILE: {
        enterOuterAlt(_localctx, 2);
        setState(671);
        while_stmt();
        break;
      }

      case Python3Parser::FOR: {
        enterOuterAlt(_localctx, 3);
        setState(672);
        for_stmt();
        break;
      }

      case Python3Parser::TRY: {
        enterOuterAlt(_localctx, 4);
        setState(673);
        try_stmt();
        break;
      }

      case Python3Parser::WITH: {
        enterOuterAlt(_localctx, 5);
        setState(674);
        with_stmt();
        break;
      }

      case Python3Parser::DEF: {
        enterOuterAlt(_localctx, 6);
        setState(675);
        funcdef();
        break;
      }

      case Python3Parser::CLASS: {
        enterOuterAlt(_localctx, 7);
        setState(676);
        classdef();
        break;
      }

      case Python3Parser::AT: {
        enterOuterAlt(_localctx, 8);
        setState(677);
        decorated();
        break;
      }

      case Python3Parser::ASYNC: {
        enterOuterAlt(_localctx, 9);
        setState(678);
        async_stmt();
        break;
      }

      case Python3Parser::MATCH: {
        enterOuterAlt(_localctx, 10);
        setState(679);
        match_stmt();
        break;
      }

    default:
      throw NoViableAltException(this);
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- Async_stmtContext ------------------------------------------------------------------

Python3Parser::Async_stmtContext::Async_stmtContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* Python3Parser::Async_stmtContext::ASYNC() {
  return getToken(Python3Parser::ASYNC, 0);
}

Python3Parser::FuncdefContext* Python3Parser::Async_stmtContext::funcdef() {
  return getRuleContext<Python3Parser::FuncdefContext>(0);
}

Python3Parser::With_stmtContext* Python3Parser::Async_stmtContext::with_stmt() {
  return getRuleContext<Python3Parser::With_stmtContext>(0);
}

Python3Parser::For_stmtContext* Python3Parser::Async_stmtContext::for_stmt() {
  return getRuleContext<Python3Parser::For_stmtContext>(0);
}


size_t Python3Parser::Async_stmtContext::getRuleIndex() const {
  return Python3Parser::RuleAsync_stmt;
}

void Python3Parser::Async_stmtContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<Python3ParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterAsync_stmt(this);
}

void Python3Parser::Async_stmtContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<Python3ParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitAsync_stmt(this);
}


antlrcpp::Any Python3Parser::Async_stmtContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<Python3ParserVisitor*>(visitor))
    return parserVisitor->visitAsync_stmt(this);
  else
    return visitor->visitChildren(this);
}

Python3Parser::Async_stmtContext* Python3Parser::async_stmt() {
  Async_stmtContext *_localctx = _tracker.createInstance<Async_stmtContext>(_ctx, getState());
  enterRule(_localctx, 80, Python3Parser::RuleAsync_stmt);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(682);
    match(Python3Parser::ASYNC);
    setState(686);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case Python3Parser::DEF: {
        setState(683);
        funcdef();
        break;
      }

      case Python3Parser::WITH: {
        setState(684);
        with_stmt();
        break;
      }

      case Python3Parser::FOR: {
        setState(685);
        for_stmt();
        break;
      }

    default:
      throw NoViableAltException(this);
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- If_stmtContext ------------------------------------------------------------------

Python3Parser::If_stmtContext::If_stmtContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* Python3Parser::If_stmtContext::IF() {
  return getToken(Python3Parser::IF, 0);
}

std::vector<Python3Parser::TestContext *> Python3Parser::If_stmtContext::test() {
  return getRuleContexts<Python3Parser::TestContext>();
}

Python3Parser::TestContext* Python3Parser::If_stmtContext::test(size_t i) {
  return getRuleContext<Python3Parser::TestContext>(i);
}

std::vector<tree::TerminalNode *> Python3Parser::If_stmtContext::COLON() {
  return getTokens(Python3Parser::COLON);
}

tree::TerminalNode* Python3Parser::If_stmtContext::COLON(size_t i) {
  return getToken(Python3Parser::COLON, i);
}

std::vector<Python3Parser::BlockContext *> Python3Parser::If_stmtContext::block() {
  return getRuleContexts<Python3Parser::BlockContext>();
}

Python3Parser::BlockContext* Python3Parser::If_stmtContext::block(size_t i) {
  return getRuleContext<Python3Parser::BlockContext>(i);
}

std::vector<tree::TerminalNode *> Python3Parser::If_stmtContext::ELIF() {
  return getTokens(Python3Parser::ELIF);
}

tree::TerminalNode* Python3Parser::If_stmtContext::ELIF(size_t i) {
  return getToken(Python3Parser::ELIF, i);
}

tree::TerminalNode* Python3Parser::If_stmtContext::ELSE() {
  return getToken(Python3Parser::ELSE, 0);
}


size_t Python3Parser::If_stmtContext::getRuleIndex() const {
  return Python3Parser::RuleIf_stmt;
}

void Python3Parser::If_stmtContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<Python3ParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterIf_stmt(this);
}

void Python3Parser::If_stmtContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<Python3ParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitIf_stmt(this);
}


antlrcpp::Any Python3Parser::If_stmtContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<Python3ParserVisitor*>(visitor))
    return parserVisitor->visitIf_stmt(this);
  else
    return visitor->visitChildren(this);
}

Python3Parser::If_stmtContext* Python3Parser::if_stmt() {
  If_stmtContext *_localctx = _tracker.createInstance<If_stmtContext>(_ctx, getState());
  enterRule(_localctx, 82, Python3Parser::RuleIf_stmt);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(688);
    match(Python3Parser::IF);
    setState(689);
    test();
    setState(690);
    match(Python3Parser::COLON);
    setState(691);
    block();
    setState(699);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while (_la == Python3Parser::ELIF) {
      setState(692);
      match(Python3Parser::ELIF);
      setState(693);
      test();
      setState(694);
      match(Python3Parser::COLON);
      setState(695);
      block();
      setState(701);
      _errHandler->sync(this);
      _la = _input->LA(1);
    }
    setState(705);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == Python3Parser::ELSE) {
      setState(702);
      match(Python3Parser::ELSE);
      setState(703);
      match(Python3Parser::COLON);
      setState(704);
      block();
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- While_stmtContext ------------------------------------------------------------------

Python3Parser::While_stmtContext::While_stmtContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* Python3Parser::While_stmtContext::WHILE() {
  return getToken(Python3Parser::WHILE, 0);
}

Python3Parser::TestContext* Python3Parser::While_stmtContext::test() {
  return getRuleContext<Python3Parser::TestContext>(0);
}

std::vector<tree::TerminalNode *> Python3Parser::While_stmtContext::COLON() {
  return getTokens(Python3Parser::COLON);
}

tree::TerminalNode* Python3Parser::While_stmtContext::COLON(size_t i) {
  return getToken(Python3Parser::COLON, i);
}

std::vector<Python3Parser::BlockContext *> Python3Parser::While_stmtContext::block() {
  return getRuleContexts<Python3Parser::BlockContext>();
}

Python3Parser::BlockContext* Python3Parser::While_stmtContext::block(size_t i) {
  return getRuleContext<Python3Parser::BlockContext>(i);
}

tree::TerminalNode* Python3Parser::While_stmtContext::ELSE() {
  return getToken(Python3Parser::ELSE, 0);
}


size_t Python3Parser::While_stmtContext::getRuleIndex() const {
  return Python3Parser::RuleWhile_stmt;
}

void Python3Parser::While_stmtContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<Python3ParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterWhile_stmt(this);
}

void Python3Parser::While_stmtContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<Python3ParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitWhile_stmt(this);
}


antlrcpp::Any Python3Parser::While_stmtContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<Python3ParserVisitor*>(visitor))
    return parserVisitor->visitWhile_stmt(this);
  else
    return visitor->visitChildren(this);
}

Python3Parser::While_stmtContext* Python3Parser::while_stmt() {
  While_stmtContext *_localctx = _tracker.createInstance<While_stmtContext>(_ctx, getState());
  enterRule(_localctx, 84, Python3Parser::RuleWhile_stmt);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(707);
    match(Python3Parser::WHILE);
    setState(708);
    test();
    setState(709);
    match(Python3Parser::COLON);
    setState(710);
    block();
    setState(714);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == Python3Parser::ELSE) {
      setState(711);
      match(Python3Parser::ELSE);
      setState(712);
      match(Python3Parser::COLON);
      setState(713);
      block();
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- For_stmtContext ------------------------------------------------------------------

Python3Parser::For_stmtContext::For_stmtContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* Python3Parser::For_stmtContext::FOR() {
  return getToken(Python3Parser::FOR, 0);
}

Python3Parser::ExprlistContext* Python3Parser::For_stmtContext::exprlist() {
  return getRuleContext<Python3Parser::ExprlistContext>(0);
}

tree::TerminalNode* Python3Parser::For_stmtContext::IN() {
  return getToken(Python3Parser::IN, 0);
}

Python3Parser::TestlistContext* Python3Parser::For_stmtContext::testlist() {
  return getRuleContext<Python3Parser::TestlistContext>(0);
}

std::vector<tree::TerminalNode *> Python3Parser::For_stmtContext::COLON() {
  return getTokens(Python3Parser::COLON);
}

tree::TerminalNode* Python3Parser::For_stmtContext::COLON(size_t i) {
  return getToken(Python3Parser::COLON, i);
}

std::vector<Python3Parser::BlockContext *> Python3Parser::For_stmtContext::block() {
  return getRuleContexts<Python3Parser::BlockContext>();
}

Python3Parser::BlockContext* Python3Parser::For_stmtContext::block(size_t i) {
  return getRuleContext<Python3Parser::BlockContext>(i);
}

tree::TerminalNode* Python3Parser::For_stmtContext::ELSE() {
  return getToken(Python3Parser::ELSE, 0);
}


size_t Python3Parser::For_stmtContext::getRuleIndex() const {
  return Python3Parser::RuleFor_stmt;
}

void Python3Parser::For_stmtContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<Python3ParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterFor_stmt(this);
}

void Python3Parser::For_stmtContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<Python3ParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitFor_stmt(this);
}


antlrcpp::Any Python3Parser::For_stmtContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<Python3ParserVisitor*>(visitor))
    return parserVisitor->visitFor_stmt(this);
  else
    return visitor->visitChildren(this);
}

Python3Parser::For_stmtContext* Python3Parser::for_stmt() {
  For_stmtContext *_localctx = _tracker.createInstance<For_stmtContext>(_ctx, getState());
  enterRule(_localctx, 86, Python3Parser::RuleFor_stmt);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(716);
    match(Python3Parser::FOR);
    setState(717);
    exprlist();
    setState(718);
    match(Python3Parser::IN);
    setState(719);
    testlist();
    setState(720);
    match(Python3Parser::COLON);
    setState(721);
    block();
    setState(725);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == Python3Parser::ELSE) {
      setState(722);
      match(Python3Parser::ELSE);
      setState(723);
      match(Python3Parser::COLON);
      setState(724);
      block();
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- Try_stmtContext ------------------------------------------------------------------

Python3Parser::Try_stmtContext::Try_stmtContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* Python3Parser::Try_stmtContext::TRY() {
  return getToken(Python3Parser::TRY, 0);
}

std::vector<tree::TerminalNode *> Python3Parser::Try_stmtContext::COLON() {
  return getTokens(Python3Parser::COLON);
}

tree::TerminalNode* Python3Parser::Try_stmtContext::COLON(size_t i) {
  return getToken(Python3Parser::COLON, i);
}

std::vector<Python3Parser::BlockContext *> Python3Parser::Try_stmtContext::block() {
  return getRuleContexts<Python3Parser::BlockContext>();
}

Python3Parser::BlockContext* Python3Parser::Try_stmtContext::block(size_t i) {
  return getRuleContext<Python3Parser::BlockContext>(i);
}

tree::TerminalNode* Python3Parser::Try_stmtContext::FINALLY() {
  return getToken(Python3Parser::FINALLY, 0);
}

std::vector<Python3Parser::Except_clauseContext *> Python3Parser::Try_stmtContext::except_clause() {
  return getRuleContexts<Python3Parser::Except_clauseContext>();
}

Python3Parser::Except_clauseContext* Python3Parser::Try_stmtContext::except_clause(size_t i) {
  return getRuleContext<Python3Parser::Except_clauseContext>(i);
}

tree::TerminalNode* Python3Parser::Try_stmtContext::ELSE() {
  return getToken(Python3Parser::ELSE, 0);
}


size_t Python3Parser::Try_stmtContext::getRuleIndex() const {
  return Python3Parser::RuleTry_stmt;
}

void Python3Parser::Try_stmtContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<Python3ParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterTry_stmt(this);
}

void Python3Parser::Try_stmtContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<Python3ParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitTry_stmt(this);
}


antlrcpp::Any Python3Parser::Try_stmtContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<Python3ParserVisitor*>(visitor))
    return parserVisitor->visitTry_stmt(this);
  else
    return visitor->visitChildren(this);
}

Python3Parser::Try_stmtContext* Python3Parser::try_stmt() {
  Try_stmtContext *_localctx = _tracker.createInstance<Try_stmtContext>(_ctx, getState());
  enterRule(_localctx, 88, Python3Parser::RuleTry_stmt);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(727);
    match(Python3Parser::TRY);
    setState(728);
    match(Python3Parser::COLON);
    setState(729);
    block();
    setState(751);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case Python3Parser::EXCEPT: {
        setState(734); 
        _errHandler->sync(this);
        _la = _input->LA(1);
        do {
          setState(730);
          except_clause();
          setState(731);
          match(Python3Parser::COLON);
          setState(732);
          block();
          setState(736); 
          _errHandler->sync(this);
          _la = _input->LA(1);
        } while (_la == Python3Parser::EXCEPT);
        setState(741);
        _errHandler->sync(this);

        _la = _input->LA(1);
        if (_la == Python3Parser::ELSE) {
          setState(738);
          match(Python3Parser::ELSE);
          setState(739);
          match(Python3Parser::COLON);
          setState(740);
          block();
        }
        setState(746);
        _errHandler->sync(this);

        _la = _input->LA(1);
        if (_la == Python3Parser::FINALLY) {
          setState(743);
          match(Python3Parser::FINALLY);
          setState(744);
          match(Python3Parser::COLON);
          setState(745);
          block();
        }
        break;
      }

      case Python3Parser::FINALLY: {
        setState(748);
        match(Python3Parser::FINALLY);
        setState(749);
        match(Python3Parser::COLON);
        setState(750);
        block();
        break;
      }

    default:
      throw NoViableAltException(this);
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- With_stmtContext ------------------------------------------------------------------

Python3Parser::With_stmtContext::With_stmtContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* Python3Parser::With_stmtContext::WITH() {
  return getToken(Python3Parser::WITH, 0);
}

std::vector<Python3Parser::With_itemContext *> Python3Parser::With_stmtContext::with_item() {
  return getRuleContexts<Python3Parser::With_itemContext>();
}

Python3Parser::With_itemContext* Python3Parser::With_stmtContext::with_item(size_t i) {
  return getRuleContext<Python3Parser::With_itemContext>(i);
}

tree::TerminalNode* Python3Parser::With_stmtContext::COLON() {
  return getToken(Python3Parser::COLON, 0);
}

Python3Parser::BlockContext* Python3Parser::With_stmtContext::block() {
  return getRuleContext<Python3Parser::BlockContext>(0);
}

std::vector<tree::TerminalNode *> Python3Parser::With_stmtContext::COMMA() {
  return getTokens(Python3Parser::COMMA);
}

tree::TerminalNode* Python3Parser::With_stmtContext::COMMA(size_t i) {
  return getToken(Python3Parser::COMMA, i);
}


size_t Python3Parser::With_stmtContext::getRuleIndex() const {
  return Python3Parser::RuleWith_stmt;
}

void Python3Parser::With_stmtContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<Python3ParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterWith_stmt(this);
}

void Python3Parser::With_stmtContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<Python3ParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitWith_stmt(this);
}


antlrcpp::Any Python3Parser::With_stmtContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<Python3ParserVisitor*>(visitor))
    return parserVisitor->visitWith_stmt(this);
  else
    return visitor->visitChildren(this);
}

Python3Parser::With_stmtContext* Python3Parser::with_stmt() {
  With_stmtContext *_localctx = _tracker.createInstance<With_stmtContext>(_ctx, getState());
  enterRule(_localctx, 90, Python3Parser::RuleWith_stmt);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(753);
    match(Python3Parser::WITH);
    setState(754);
    with_item();
    setState(759);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while (_la == Python3Parser::COMMA) {
      setState(755);
      match(Python3Parser::COMMA);
      setState(756);
      with_item();
      setState(761);
      _errHandler->sync(this);
      _la = _input->LA(1);
    }
    setState(762);
    match(Python3Parser::COLON);
    setState(763);
    block();
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- With_itemContext ------------------------------------------------------------------

Python3Parser::With_itemContext::With_itemContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

Python3Parser::TestContext* Python3Parser::With_itemContext::test() {
  return getRuleContext<Python3Parser::TestContext>(0);
}

tree::TerminalNode* Python3Parser::With_itemContext::AS() {
  return getToken(Python3Parser::AS, 0);
}

Python3Parser::ExprContext* Python3Parser::With_itemContext::expr() {
  return getRuleContext<Python3Parser::ExprContext>(0);
}


size_t Python3Parser::With_itemContext::getRuleIndex() const {
  return Python3Parser::RuleWith_item;
}

void Python3Parser::With_itemContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<Python3ParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterWith_item(this);
}

void Python3Parser::With_itemContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<Python3ParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitWith_item(this);
}


antlrcpp::Any Python3Parser::With_itemContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<Python3ParserVisitor*>(visitor))
    return parserVisitor->visitWith_item(this);
  else
    return visitor->visitChildren(this);
}

Python3Parser::With_itemContext* Python3Parser::with_item() {
  With_itemContext *_localctx = _tracker.createInstance<With_itemContext>(_ctx, getState());
  enterRule(_localctx, 92, Python3Parser::RuleWith_item);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(765);
    test();
    setState(768);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == Python3Parser::AS) {
      setState(766);
      match(Python3Parser::AS);
      setState(767);
      expr(0);
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- Except_clauseContext ------------------------------------------------------------------

Python3Parser::Except_clauseContext::Except_clauseContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* Python3Parser::Except_clauseContext::EXCEPT() {
  return getToken(Python3Parser::EXCEPT, 0);
}

Python3Parser::TestContext* Python3Parser::Except_clauseContext::test() {
  return getRuleContext<Python3Parser::TestContext>(0);
}

tree::TerminalNode* Python3Parser::Except_clauseContext::AS() {
  return getToken(Python3Parser::AS, 0);
}

Python3Parser::NameContext* Python3Parser::Except_clauseContext::name() {
  return getRuleContext<Python3Parser::NameContext>(0);
}


size_t Python3Parser::Except_clauseContext::getRuleIndex() const {
  return Python3Parser::RuleExcept_clause;
}

void Python3Parser::Except_clauseContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<Python3ParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterExcept_clause(this);
}

void Python3Parser::Except_clauseContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<Python3ParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitExcept_clause(this);
}


antlrcpp::Any Python3Parser::Except_clauseContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<Python3ParserVisitor*>(visitor))
    return parserVisitor->visitExcept_clause(this);
  else
    return visitor->visitChildren(this);
}

Python3Parser::Except_clauseContext* Python3Parser::except_clause() {
  Except_clauseContext *_localctx = _tracker.createInstance<Except_clauseContext>(_ctx, getState());
  enterRule(_localctx, 94, Python3Parser::RuleExcept_clause);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(770);
    match(Python3Parser::EXCEPT);
    setState(776);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if ((((_la & ~ 0x3fULL) == 0) &&
      ((1ULL << _la) & ((1ULL << Python3Parser::STRING)
      | (1ULL << Python3Parser::NUMBER)
      | (1ULL << Python3Parser::AWAIT)
      | (1ULL << Python3Parser::FALSE)
      | (1ULL << Python3Parser::LAMBDA)
      | (1ULL << Python3Parser::MATCH)
      | (1ULL << Python3Parser::NONE)
      | (1ULL << Python3Parser::NOT)
      | (1ULL << Python3Parser::TRUE)
      | (1ULL << Python3Parser::UNDERSCORE)
      | (1ULL << Python3Parser::NAME)
      | (1ULL << Python3Parser::ELLIPSIS)
      | (1ULL << Python3Parser::OPEN_PAREN))) != 0) || ((((_la - 64) & ~ 0x3fULL) == 0) &&
      ((1ULL << (_la - 64)) & ((1ULL << (Python3Parser::OPEN_BRACK - 64))
      | (1ULL << (Python3Parser::ADD - 64))
      | (1ULL << (Python3Parser::MINUS - 64))
      | (1ULL << (Python3Parser::NOT_OP - 64))
      | (1ULL << (Python3Parser::OPEN_BRACE - 64)))) != 0)) {
      setState(771);
      test();
      setState(774);
      _errHandler->sync(this);

      _la = _input->LA(1);
      if (_la == Python3Parser::AS) {
        setState(772);
        match(Python3Parser::AS);
        setState(773);
        name();
      }
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- BlockContext ------------------------------------------------------------------

Python3Parser::BlockContext::BlockContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

Python3Parser::Simple_stmtsContext* Python3Parser::BlockContext::simple_stmts() {
  return getRuleContext<Python3Parser::Simple_stmtsContext>(0);
}

tree::TerminalNode* Python3Parser::BlockContext::NEWLINE() {
  return getToken(Python3Parser::NEWLINE, 0);
}

tree::TerminalNode* Python3Parser::BlockContext::INDENT() {
  return getToken(Python3Parser::INDENT, 0);
}

tree::TerminalNode* Python3Parser::BlockContext::DEDENT() {
  return getToken(Python3Parser::DEDENT, 0);
}

std::vector<Python3Parser::StmtContext *> Python3Parser::BlockContext::stmt() {
  return getRuleContexts<Python3Parser::StmtContext>();
}

Python3Parser::StmtContext* Python3Parser::BlockContext::stmt(size_t i) {
  return getRuleContext<Python3Parser::StmtContext>(i);
}


size_t Python3Parser::BlockContext::getRuleIndex() const {
  return Python3Parser::RuleBlock;
}

void Python3Parser::BlockContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<Python3ParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterBlock(this);
}

void Python3Parser::BlockContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<Python3ParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitBlock(this);
}


antlrcpp::Any Python3Parser::BlockContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<Python3ParserVisitor*>(visitor))
    return parserVisitor->visitBlock(this);
  else
    return visitor->visitChildren(this);
}

Python3Parser::BlockContext* Python3Parser::block() {
  BlockContext *_localctx = _tracker.createInstance<BlockContext>(_ctx, getState());
  enterRule(_localctx, 96, Python3Parser::RuleBlock);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    setState(788);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case Python3Parser::STRING:
      case Python3Parser::NUMBER:
      case Python3Parser::ASSERT:
      case Python3Parser::AWAIT:
      case Python3Parser::BREAK:
      case Python3Parser::CONTINUE:
      case Python3Parser::DEL:
      case Python3Parser::FALSE:
      case Python3Parser::FROM:
      case Python3Parser::GLOBAL:
      case Python3Parser::IMPORT:
      case Python3Parser::LAMBDA:
      case Python3Parser::MATCH:
      case Python3Parser::NONE:
      case Python3Parser::NONLOCAL:
      case Python3Parser::NOT:
      case Python3Parser::PASS:
      case Python3Parser::RAISE:
      case Python3Parser::RETURN:
      case Python3Parser::TRUE:
      case Python3Parser::UNDERSCORE:
      case Python3Parser::YIELD:
      case Python3Parser::NAME:
      case Python3Parser::ELLIPSIS:
      case Python3Parser::STAR:
      case Python3Parser::OPEN_PAREN:
      case Python3Parser::OPEN_BRACK:
      case Python3Parser::ADD:
      case Python3Parser::MINUS:
      case Python3Parser::NOT_OP:
      case Python3Parser::OPEN_BRACE: {
        enterOuterAlt(_localctx, 1);
        setState(778);
        simple_stmts();
        break;
      }

      case Python3Parser::NEWLINE: {
        enterOuterAlt(_localctx, 2);
        setState(779);
        match(Python3Parser::NEWLINE);
        setState(780);
        match(Python3Parser::INDENT);
        setState(782); 
        _errHandler->sync(this);
        _la = _input->LA(1);
        do {
          setState(781);
          stmt();
          setState(784); 
          _errHandler->sync(this);
          _la = _input->LA(1);
        } while ((((_la & ~ 0x3fULL) == 0) &&
          ((1ULL << _la) & ((1ULL << Python3Parser::STRING)
          | (1ULL << Python3Parser::NUMBER)
          | (1ULL << Python3Parser::ASSERT)
          | (1ULL << Python3Parser::ASYNC)
          | (1ULL << Python3Parser::AWAIT)
          | (1ULL << Python3Parser::BREAK)
          | (1ULL << Python3Parser::CLASS)
          | (1ULL << Python3Parser::CONTINUE)
          | (1ULL << Python3Parser::DEF)
          | (1ULL << Python3Parser::DEL)
          | (1ULL << Python3Parser::FALSE)
          | (1ULL << Python3Parser::FOR)
          | (1ULL << Python3Parser::FROM)
          | (1ULL << Python3Parser::GLOBAL)
          | (1ULL << Python3Parser::IF)
          | (1ULL << Python3Parser::IMPORT)
          | (1ULL << Python3Parser::LAMBDA)
          | (1ULL << Python3Parser::MATCH)
          | (1ULL << Python3Parser::NONE)
          | (1ULL << Python3Parser::NONLOCAL)
          | (1ULL << Python3Parser::NOT)
          | (1ULL << Python3Parser::PASS)
          | (1ULL << Python3Parser::RAISE)
          | (1ULL << Python3Parser::RETURN)
          | (1ULL << Python3Parser::TRUE)
          | (1ULL << Python3Parser::TRY)
          | (1ULL << Python3Parser::UNDERSCORE)
          | (1ULL << Python3Parser::WHILE)
          | (1ULL << Python3Parser::WITH)
          | (1ULL << Python3Parser::YIELD)
          | (1ULL << Python3Parser::NAME)
          | (1ULL << Python3Parser::ELLIPSIS)
          | (1ULL << Python3Parser::STAR)
          | (1ULL << Python3Parser::OPEN_PAREN))) != 0) || ((((_la - 64) & ~ 0x3fULL) == 0) &&
          ((1ULL << (_la - 64)) & ((1ULL << (Python3Parser::OPEN_BRACK - 64))
          | (1ULL << (Python3Parser::ADD - 64))
          | (1ULL << (Python3Parser::MINUS - 64))
          | (1ULL << (Python3Parser::NOT_OP - 64))
          | (1ULL << (Python3Parser::OPEN_BRACE - 64))
          | (1ULL << (Python3Parser::AT - 64)))) != 0));
        setState(786);
        match(Python3Parser::DEDENT);
        break;
      }

    default:
      throw NoViableAltException(this);
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- Match_stmtContext ------------------------------------------------------------------

Python3Parser::Match_stmtContext::Match_stmtContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* Python3Parser::Match_stmtContext::MATCH() {
  return getToken(Python3Parser::MATCH, 0);
}

Python3Parser::Subject_exprContext* Python3Parser::Match_stmtContext::subject_expr() {
  return getRuleContext<Python3Parser::Subject_exprContext>(0);
}

tree::TerminalNode* Python3Parser::Match_stmtContext::COLON() {
  return getToken(Python3Parser::COLON, 0);
}

tree::TerminalNode* Python3Parser::Match_stmtContext::NEWLINE() {
  return getToken(Python3Parser::NEWLINE, 0);
}

tree::TerminalNode* Python3Parser::Match_stmtContext::INDENT() {
  return getToken(Python3Parser::INDENT, 0);
}

tree::TerminalNode* Python3Parser::Match_stmtContext::DEDENT() {
  return getToken(Python3Parser::DEDENT, 0);
}

std::vector<Python3Parser::Case_blockContext *> Python3Parser::Match_stmtContext::case_block() {
  return getRuleContexts<Python3Parser::Case_blockContext>();
}

Python3Parser::Case_blockContext* Python3Parser::Match_stmtContext::case_block(size_t i) {
  return getRuleContext<Python3Parser::Case_blockContext>(i);
}


size_t Python3Parser::Match_stmtContext::getRuleIndex() const {
  return Python3Parser::RuleMatch_stmt;
}

void Python3Parser::Match_stmtContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<Python3ParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterMatch_stmt(this);
}

void Python3Parser::Match_stmtContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<Python3ParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitMatch_stmt(this);
}


antlrcpp::Any Python3Parser::Match_stmtContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<Python3ParserVisitor*>(visitor))
    return parserVisitor->visitMatch_stmt(this);
  else
    return visitor->visitChildren(this);
}

Python3Parser::Match_stmtContext* Python3Parser::match_stmt() {
  Match_stmtContext *_localctx = _tracker.createInstance<Match_stmtContext>(_ctx, getState());
  enterRule(_localctx, 98, Python3Parser::RuleMatch_stmt);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(790);
    match(Python3Parser::MATCH);
    setState(791);
    subject_expr();
    setState(792);
    match(Python3Parser::COLON);
    setState(793);
    match(Python3Parser::NEWLINE);
    setState(794);
    match(Python3Parser::INDENT);
    setState(796); 
    _errHandler->sync(this);
    _la = _input->LA(1);
    do {
      setState(795);
      case_block();
      setState(798); 
      _errHandler->sync(this);
      _la = _input->LA(1);
    } while (_la == Python3Parser::CASE);
    setState(800);
    match(Python3Parser::DEDENT);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- Subject_exprContext ------------------------------------------------------------------

Python3Parser::Subject_exprContext::Subject_exprContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

Python3Parser::Star_named_expressionContext* Python3Parser::Subject_exprContext::star_named_expression() {
  return getRuleContext<Python3Parser::Star_named_expressionContext>(0);
}

tree::TerminalNode* Python3Parser::Subject_exprContext::COMMA() {
  return getToken(Python3Parser::COMMA, 0);
}

Python3Parser::Star_named_expressionsContext* Python3Parser::Subject_exprContext::star_named_expressions() {
  return getRuleContext<Python3Parser::Star_named_expressionsContext>(0);
}

Python3Parser::TestContext* Python3Parser::Subject_exprContext::test() {
  return getRuleContext<Python3Parser::TestContext>(0);
}


size_t Python3Parser::Subject_exprContext::getRuleIndex() const {
  return Python3Parser::RuleSubject_expr;
}

void Python3Parser::Subject_exprContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<Python3ParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterSubject_expr(this);
}

void Python3Parser::Subject_exprContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<Python3ParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitSubject_expr(this);
}


antlrcpp::Any Python3Parser::Subject_exprContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<Python3ParserVisitor*>(visitor))
    return parserVisitor->visitSubject_expr(this);
  else
    return visitor->visitChildren(this);
}

Python3Parser::Subject_exprContext* Python3Parser::subject_expr() {
  Subject_exprContext *_localctx = _tracker.createInstance<Subject_exprContext>(_ctx, getState());
  enterRule(_localctx, 100, Python3Parser::RuleSubject_expr);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    setState(808);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 100, _ctx)) {
    case 1: {
      enterOuterAlt(_localctx, 1);
      setState(802);
      star_named_expression();
      setState(803);
      match(Python3Parser::COMMA);
      setState(805);
      _errHandler->sync(this);

      _la = _input->LA(1);
      if (_la == Python3Parser::COMMA) {
        setState(804);
        star_named_expressions();
      }
      break;
    }

    case 2: {
      enterOuterAlt(_localctx, 2);
      setState(807);
      test();
      break;
    }

    default:
      break;
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- Star_named_expressionsContext ------------------------------------------------------------------

Python3Parser::Star_named_expressionsContext::Star_named_expressionsContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

std::vector<tree::TerminalNode *> Python3Parser::Star_named_expressionsContext::COMMA() {
  return getTokens(Python3Parser::COMMA);
}

tree::TerminalNode* Python3Parser::Star_named_expressionsContext::COMMA(size_t i) {
  return getToken(Python3Parser::COMMA, i);
}

std::vector<Python3Parser::Star_named_expressionContext *> Python3Parser::Star_named_expressionsContext::star_named_expression() {
  return getRuleContexts<Python3Parser::Star_named_expressionContext>();
}

Python3Parser::Star_named_expressionContext* Python3Parser::Star_named_expressionsContext::star_named_expression(size_t i) {
  return getRuleContext<Python3Parser::Star_named_expressionContext>(i);
}


size_t Python3Parser::Star_named_expressionsContext::getRuleIndex() const {
  return Python3Parser::RuleStar_named_expressions;
}

void Python3Parser::Star_named_expressionsContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<Python3ParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterStar_named_expressions(this);
}

void Python3Parser::Star_named_expressionsContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<Python3ParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitStar_named_expressions(this);
}


antlrcpp::Any Python3Parser::Star_named_expressionsContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<Python3ParserVisitor*>(visitor))
    return parserVisitor->visitStar_named_expressions(this);
  else
    return visitor->visitChildren(this);
}

Python3Parser::Star_named_expressionsContext* Python3Parser::star_named_expressions() {
  Star_named_expressionsContext *_localctx = _tracker.createInstance<Star_named_expressionsContext>(_ctx, getState());
  enterRule(_localctx, 102, Python3Parser::RuleStar_named_expressions);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(810);
    match(Python3Parser::COMMA);
    setState(812); 
    _errHandler->sync(this);
    _la = _input->LA(1);
    do {
      setState(811);
      star_named_expression();
      setState(814); 
      _errHandler->sync(this);
      _la = _input->LA(1);
    } while ((((_la & ~ 0x3fULL) == 0) &&
      ((1ULL << _la) & ((1ULL << Python3Parser::STRING)
      | (1ULL << Python3Parser::NUMBER)
      | (1ULL << Python3Parser::AWAIT)
      | (1ULL << Python3Parser::FALSE)
      | (1ULL << Python3Parser::LAMBDA)
      | (1ULL << Python3Parser::MATCH)
      | (1ULL << Python3Parser::NONE)
      | (1ULL << Python3Parser::NOT)
      | (1ULL << Python3Parser::TRUE)
      | (1ULL << Python3Parser::UNDERSCORE)
      | (1ULL << Python3Parser::NAME)
      | (1ULL << Python3Parser::ELLIPSIS)
      | (1ULL << Python3Parser::STAR)
      | (1ULL << Python3Parser::OPEN_PAREN))) != 0) || ((((_la - 64) & ~ 0x3fULL) == 0) &&
      ((1ULL << (_la - 64)) & ((1ULL << (Python3Parser::OPEN_BRACK - 64))
      | (1ULL << (Python3Parser::ADD - 64))
      | (1ULL << (Python3Parser::MINUS - 64))
      | (1ULL << (Python3Parser::NOT_OP - 64))
      | (1ULL << (Python3Parser::OPEN_BRACE - 64)))) != 0));
    setState(817);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == Python3Parser::COMMA) {
      setState(816);
      match(Python3Parser::COMMA);
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- Star_named_expressionContext ------------------------------------------------------------------

Python3Parser::Star_named_expressionContext::Star_named_expressionContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* Python3Parser::Star_named_expressionContext::STAR() {
  return getToken(Python3Parser::STAR, 0);
}

Python3Parser::ExprContext* Python3Parser::Star_named_expressionContext::expr() {
  return getRuleContext<Python3Parser::ExprContext>(0);
}

Python3Parser::TestContext* Python3Parser::Star_named_expressionContext::test() {
  return getRuleContext<Python3Parser::TestContext>(0);
}


size_t Python3Parser::Star_named_expressionContext::getRuleIndex() const {
  return Python3Parser::RuleStar_named_expression;
}

void Python3Parser::Star_named_expressionContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<Python3ParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterStar_named_expression(this);
}

void Python3Parser::Star_named_expressionContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<Python3ParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitStar_named_expression(this);
}


antlrcpp::Any Python3Parser::Star_named_expressionContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<Python3ParserVisitor*>(visitor))
    return parserVisitor->visitStar_named_expression(this);
  else
    return visitor->visitChildren(this);
}

Python3Parser::Star_named_expressionContext* Python3Parser::star_named_expression() {
  Star_named_expressionContext *_localctx = _tracker.createInstance<Star_named_expressionContext>(_ctx, getState());
  enterRule(_localctx, 104, Python3Parser::RuleStar_named_expression);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    setState(822);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case Python3Parser::STAR: {
        enterOuterAlt(_localctx, 1);
        setState(819);
        match(Python3Parser::STAR);
        setState(820);
        expr(0);
        break;
      }

      case Python3Parser::STRING:
      case Python3Parser::NUMBER:
      case Python3Parser::AWAIT:
      case Python3Parser::FALSE:
      case Python3Parser::LAMBDA:
      case Python3Parser::MATCH:
      case Python3Parser::NONE:
      case Python3Parser::NOT:
      case Python3Parser::TRUE:
      case Python3Parser::UNDERSCORE:
      case Python3Parser::NAME:
      case Python3Parser::ELLIPSIS:
      case Python3Parser::OPEN_PAREN:
      case Python3Parser::OPEN_BRACK:
      case Python3Parser::ADD:
      case Python3Parser::MINUS:
      case Python3Parser::NOT_OP:
      case Python3Parser::OPEN_BRACE: {
        enterOuterAlt(_localctx, 2);
        setState(821);
        test();
        break;
      }

    default:
      throw NoViableAltException(this);
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- Case_blockContext ------------------------------------------------------------------

Python3Parser::Case_blockContext::Case_blockContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* Python3Parser::Case_blockContext::CASE() {
  return getToken(Python3Parser::CASE, 0);
}

Python3Parser::PatternsContext* Python3Parser::Case_blockContext::patterns() {
  return getRuleContext<Python3Parser::PatternsContext>(0);
}

tree::TerminalNode* Python3Parser::Case_blockContext::COLON() {
  return getToken(Python3Parser::COLON, 0);
}

Python3Parser::BlockContext* Python3Parser::Case_blockContext::block() {
  return getRuleContext<Python3Parser::BlockContext>(0);
}

Python3Parser::GuardContext* Python3Parser::Case_blockContext::guard() {
  return getRuleContext<Python3Parser::GuardContext>(0);
}


size_t Python3Parser::Case_blockContext::getRuleIndex() const {
  return Python3Parser::RuleCase_block;
}

void Python3Parser::Case_blockContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<Python3ParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterCase_block(this);
}

void Python3Parser::Case_blockContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<Python3ParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitCase_block(this);
}


antlrcpp::Any Python3Parser::Case_blockContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<Python3ParserVisitor*>(visitor))
    return parserVisitor->visitCase_block(this);
  else
    return visitor->visitChildren(this);
}

Python3Parser::Case_blockContext* Python3Parser::case_block() {
  Case_blockContext *_localctx = _tracker.createInstance<Case_blockContext>(_ctx, getState());
  enterRule(_localctx, 106, Python3Parser::RuleCase_block);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(824);
    match(Python3Parser::CASE);
    setState(825);
    patterns();
    setState(827);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == Python3Parser::IF) {
      setState(826);
      guard();
    }
    setState(829);
    match(Python3Parser::COLON);
    setState(830);
    block();
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- GuardContext ------------------------------------------------------------------

Python3Parser::GuardContext::GuardContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* Python3Parser::GuardContext::IF() {
  return getToken(Python3Parser::IF, 0);
}

Python3Parser::TestContext* Python3Parser::GuardContext::test() {
  return getRuleContext<Python3Parser::TestContext>(0);
}


size_t Python3Parser::GuardContext::getRuleIndex() const {
  return Python3Parser::RuleGuard;
}

void Python3Parser::GuardContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<Python3ParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterGuard(this);
}

void Python3Parser::GuardContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<Python3ParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitGuard(this);
}


antlrcpp::Any Python3Parser::GuardContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<Python3ParserVisitor*>(visitor))
    return parserVisitor->visitGuard(this);
  else
    return visitor->visitChildren(this);
}

Python3Parser::GuardContext* Python3Parser::guard() {
  GuardContext *_localctx = _tracker.createInstance<GuardContext>(_ctx, getState());
  enterRule(_localctx, 108, Python3Parser::RuleGuard);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(832);
    match(Python3Parser::IF);
    setState(833);
    test();
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- PatternsContext ------------------------------------------------------------------

Python3Parser::PatternsContext::PatternsContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

Python3Parser::Open_sequence_patternContext* Python3Parser::PatternsContext::open_sequence_pattern() {
  return getRuleContext<Python3Parser::Open_sequence_patternContext>(0);
}

Python3Parser::PatternContext* Python3Parser::PatternsContext::pattern() {
  return getRuleContext<Python3Parser::PatternContext>(0);
}


size_t Python3Parser::PatternsContext::getRuleIndex() const {
  return Python3Parser::RulePatterns;
}

void Python3Parser::PatternsContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<Python3ParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterPatterns(this);
}

void Python3Parser::PatternsContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<Python3ParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitPatterns(this);
}


antlrcpp::Any Python3Parser::PatternsContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<Python3ParserVisitor*>(visitor))
    return parserVisitor->visitPatterns(this);
  else
    return visitor->visitChildren(this);
}

Python3Parser::PatternsContext* Python3Parser::patterns() {
  PatternsContext *_localctx = _tracker.createInstance<PatternsContext>(_ctx, getState());
  enterRule(_localctx, 110, Python3Parser::RulePatterns);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    setState(837);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 105, _ctx)) {
    case 1: {
      enterOuterAlt(_localctx, 1);
      setState(835);
      open_sequence_pattern();
      break;
    }

    case 2: {
      enterOuterAlt(_localctx, 2);
      setState(836);
      pattern();
      break;
    }

    default:
      break;
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- PatternContext ------------------------------------------------------------------

Python3Parser::PatternContext::PatternContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

Python3Parser::As_patternContext* Python3Parser::PatternContext::as_pattern() {
  return getRuleContext<Python3Parser::As_patternContext>(0);
}

Python3Parser::Or_patternContext* Python3Parser::PatternContext::or_pattern() {
  return getRuleContext<Python3Parser::Or_patternContext>(0);
}


size_t Python3Parser::PatternContext::getRuleIndex() const {
  return Python3Parser::RulePattern;
}

void Python3Parser::PatternContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<Python3ParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterPattern(this);
}

void Python3Parser::PatternContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<Python3ParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitPattern(this);
}


antlrcpp::Any Python3Parser::PatternContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<Python3ParserVisitor*>(visitor))
    return parserVisitor->visitPattern(this);
  else
    return visitor->visitChildren(this);
}

Python3Parser::PatternContext* Python3Parser::pattern() {
  PatternContext *_localctx = _tracker.createInstance<PatternContext>(_ctx, getState());
  enterRule(_localctx, 112, Python3Parser::RulePattern);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    setState(841);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 106, _ctx)) {
    case 1: {
      enterOuterAlt(_localctx, 1);
      setState(839);
      as_pattern();
      break;
    }

    case 2: {
      enterOuterAlt(_localctx, 2);
      setState(840);
      or_pattern();
      break;
    }

    default:
      break;
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- As_patternContext ------------------------------------------------------------------

Python3Parser::As_patternContext::As_patternContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

Python3Parser::Or_patternContext* Python3Parser::As_patternContext::or_pattern() {
  return getRuleContext<Python3Parser::Or_patternContext>(0);
}

tree::TerminalNode* Python3Parser::As_patternContext::AS() {
  return getToken(Python3Parser::AS, 0);
}

Python3Parser::Pattern_capture_targetContext* Python3Parser::As_patternContext::pattern_capture_target() {
  return getRuleContext<Python3Parser::Pattern_capture_targetContext>(0);
}


size_t Python3Parser::As_patternContext::getRuleIndex() const {
  return Python3Parser::RuleAs_pattern;
}

void Python3Parser::As_patternContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<Python3ParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterAs_pattern(this);
}

void Python3Parser::As_patternContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<Python3ParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitAs_pattern(this);
}


antlrcpp::Any Python3Parser::As_patternContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<Python3ParserVisitor*>(visitor))
    return parserVisitor->visitAs_pattern(this);
  else
    return visitor->visitChildren(this);
}

Python3Parser::As_patternContext* Python3Parser::as_pattern() {
  As_patternContext *_localctx = _tracker.createInstance<As_patternContext>(_ctx, getState());
  enterRule(_localctx, 114, Python3Parser::RuleAs_pattern);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(843);
    or_pattern();
    setState(844);
    match(Python3Parser::AS);
    setState(845);
    pattern_capture_target();
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- Or_patternContext ------------------------------------------------------------------

Python3Parser::Or_patternContext::Or_patternContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

std::vector<Python3Parser::Closed_patternContext *> Python3Parser::Or_patternContext::closed_pattern() {
  return getRuleContexts<Python3Parser::Closed_patternContext>();
}

Python3Parser::Closed_patternContext* Python3Parser::Or_patternContext::closed_pattern(size_t i) {
  return getRuleContext<Python3Parser::Closed_patternContext>(i);
}

std::vector<tree::TerminalNode *> Python3Parser::Or_patternContext::OR_OP() {
  return getTokens(Python3Parser::OR_OP);
}

tree::TerminalNode* Python3Parser::Or_patternContext::OR_OP(size_t i) {
  return getToken(Python3Parser::OR_OP, i);
}


size_t Python3Parser::Or_patternContext::getRuleIndex() const {
  return Python3Parser::RuleOr_pattern;
}

void Python3Parser::Or_patternContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<Python3ParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterOr_pattern(this);
}

void Python3Parser::Or_patternContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<Python3ParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitOr_pattern(this);
}


antlrcpp::Any Python3Parser::Or_patternContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<Python3ParserVisitor*>(visitor))
    return parserVisitor->visitOr_pattern(this);
  else
    return visitor->visitChildren(this);
}

Python3Parser::Or_patternContext* Python3Parser::or_pattern() {
  Or_patternContext *_localctx = _tracker.createInstance<Or_patternContext>(_ctx, getState());
  enterRule(_localctx, 116, Python3Parser::RuleOr_pattern);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(847);
    closed_pattern();
    setState(852);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while (_la == Python3Parser::OR_OP) {
      setState(848);
      match(Python3Parser::OR_OP);
      setState(849);
      closed_pattern();
      setState(854);
      _errHandler->sync(this);
      _la = _input->LA(1);
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- Closed_patternContext ------------------------------------------------------------------

Python3Parser::Closed_patternContext::Closed_patternContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

Python3Parser::Literal_patternContext* Python3Parser::Closed_patternContext::literal_pattern() {
  return getRuleContext<Python3Parser::Literal_patternContext>(0);
}

Python3Parser::Capture_patternContext* Python3Parser::Closed_patternContext::capture_pattern() {
  return getRuleContext<Python3Parser::Capture_patternContext>(0);
}

Python3Parser::Wildcard_patternContext* Python3Parser::Closed_patternContext::wildcard_pattern() {
  return getRuleContext<Python3Parser::Wildcard_patternContext>(0);
}

Python3Parser::Value_patternContext* Python3Parser::Closed_patternContext::value_pattern() {
  return getRuleContext<Python3Parser::Value_patternContext>(0);
}

Python3Parser::Group_patternContext* Python3Parser::Closed_patternContext::group_pattern() {
  return getRuleContext<Python3Parser::Group_patternContext>(0);
}

Python3Parser::Sequence_patternContext* Python3Parser::Closed_patternContext::sequence_pattern() {
  return getRuleContext<Python3Parser::Sequence_patternContext>(0);
}

Python3Parser::Mapping_patternContext* Python3Parser::Closed_patternContext::mapping_pattern() {
  return getRuleContext<Python3Parser::Mapping_patternContext>(0);
}

Python3Parser::Class_patternContext* Python3Parser::Closed_patternContext::class_pattern() {
  return getRuleContext<Python3Parser::Class_patternContext>(0);
}


size_t Python3Parser::Closed_patternContext::getRuleIndex() const {
  return Python3Parser::RuleClosed_pattern;
}

void Python3Parser::Closed_patternContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<Python3ParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterClosed_pattern(this);
}

void Python3Parser::Closed_patternContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<Python3ParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitClosed_pattern(this);
}


antlrcpp::Any Python3Parser::Closed_patternContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<Python3ParserVisitor*>(visitor))
    return parserVisitor->visitClosed_pattern(this);
  else
    return visitor->visitChildren(this);
}

Python3Parser::Closed_patternContext* Python3Parser::closed_pattern() {
  Closed_patternContext *_localctx = _tracker.createInstance<Closed_patternContext>(_ctx, getState());
  enterRule(_localctx, 118, Python3Parser::RuleClosed_pattern);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    setState(863);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 108, _ctx)) {
    case 1: {
      enterOuterAlt(_localctx, 1);
      setState(855);
      literal_pattern();
      break;
    }

    case 2: {
      enterOuterAlt(_localctx, 2);
      setState(856);
      capture_pattern();
      break;
    }

    case 3: {
      enterOuterAlt(_localctx, 3);
      setState(857);
      wildcard_pattern();
      break;
    }

    case 4: {
      enterOuterAlt(_localctx, 4);
      setState(858);
      value_pattern();
      break;
    }

    case 5: {
      enterOuterAlt(_localctx, 5);
      setState(859);
      group_pattern();
      break;
    }

    case 6: {
      enterOuterAlt(_localctx, 6);
      setState(860);
      sequence_pattern();
      break;
    }

    case 7: {
      enterOuterAlt(_localctx, 7);
      setState(861);
      mapping_pattern();
      break;
    }

    case 8: {
      enterOuterAlt(_localctx, 8);
      setState(862);
      class_pattern();
      break;
    }

    default:
      break;
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- Literal_patternContext ------------------------------------------------------------------

Python3Parser::Literal_patternContext::Literal_patternContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

Python3Parser::Signed_numberContext* Python3Parser::Literal_patternContext::signed_number() {
  return getRuleContext<Python3Parser::Signed_numberContext>(0);
}

Python3Parser::Complex_numberContext* Python3Parser::Literal_patternContext::complex_number() {
  return getRuleContext<Python3Parser::Complex_numberContext>(0);
}

Python3Parser::StringsContext* Python3Parser::Literal_patternContext::strings() {
  return getRuleContext<Python3Parser::StringsContext>(0);
}

tree::TerminalNode* Python3Parser::Literal_patternContext::NONE() {
  return getToken(Python3Parser::NONE, 0);
}

tree::TerminalNode* Python3Parser::Literal_patternContext::TRUE() {
  return getToken(Python3Parser::TRUE, 0);
}

tree::TerminalNode* Python3Parser::Literal_patternContext::FALSE() {
  return getToken(Python3Parser::FALSE, 0);
}


size_t Python3Parser::Literal_patternContext::getRuleIndex() const {
  return Python3Parser::RuleLiteral_pattern;
}

void Python3Parser::Literal_patternContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<Python3ParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterLiteral_pattern(this);
}

void Python3Parser::Literal_patternContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<Python3ParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitLiteral_pattern(this);
}


antlrcpp::Any Python3Parser::Literal_patternContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<Python3ParserVisitor*>(visitor))
    return parserVisitor->visitLiteral_pattern(this);
  else
    return visitor->visitChildren(this);
}

Python3Parser::Literal_patternContext* Python3Parser::literal_pattern() {
  Literal_patternContext *_localctx = _tracker.createInstance<Literal_patternContext>(_ctx, getState());
  enterRule(_localctx, 120, Python3Parser::RuleLiteral_pattern);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    setState(873);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 109, _ctx)) {
    case 1: {
      enterOuterAlt(_localctx, 1);
      setState(865);
      signed_number();
      setState(866);

      if (!( this->CannotBePlusMinus() )) throw FailedPredicateException(this, " this->CannotBePlusMinus() ");
      break;
    }

    case 2: {
      enterOuterAlt(_localctx, 2);
      setState(868);
      complex_number();
      break;
    }

    case 3: {
      enterOuterAlt(_localctx, 3);
      setState(869);
      strings();
      break;
    }

    case 4: {
      enterOuterAlt(_localctx, 4);
      setState(870);
      match(Python3Parser::NONE);
      break;
    }

    case 5: {
      enterOuterAlt(_localctx, 5);
      setState(871);
      match(Python3Parser::TRUE);
      break;
    }

    case 6: {
      enterOuterAlt(_localctx, 6);
      setState(872);
      match(Python3Parser::FALSE);
      break;
    }

    default:
      break;
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- Literal_exprContext ------------------------------------------------------------------

Python3Parser::Literal_exprContext::Literal_exprContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

Python3Parser::Signed_numberContext* Python3Parser::Literal_exprContext::signed_number() {
  return getRuleContext<Python3Parser::Signed_numberContext>(0);
}

Python3Parser::Complex_numberContext* Python3Parser::Literal_exprContext::complex_number() {
  return getRuleContext<Python3Parser::Complex_numberContext>(0);
}

Python3Parser::StringsContext* Python3Parser::Literal_exprContext::strings() {
  return getRuleContext<Python3Parser::StringsContext>(0);
}

tree::TerminalNode* Python3Parser::Literal_exprContext::NONE() {
  return getToken(Python3Parser::NONE, 0);
}

tree::TerminalNode* Python3Parser::Literal_exprContext::TRUE() {
  return getToken(Python3Parser::TRUE, 0);
}

tree::TerminalNode* Python3Parser::Literal_exprContext::FALSE() {
  return getToken(Python3Parser::FALSE, 0);
}


size_t Python3Parser::Literal_exprContext::getRuleIndex() const {
  return Python3Parser::RuleLiteral_expr;
}

void Python3Parser::Literal_exprContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<Python3ParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterLiteral_expr(this);
}

void Python3Parser::Literal_exprContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<Python3ParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitLiteral_expr(this);
}


antlrcpp::Any Python3Parser::Literal_exprContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<Python3ParserVisitor*>(visitor))
    return parserVisitor->visitLiteral_expr(this);
  else
    return visitor->visitChildren(this);
}

Python3Parser::Literal_exprContext* Python3Parser::literal_expr() {
  Literal_exprContext *_localctx = _tracker.createInstance<Literal_exprContext>(_ctx, getState());
  enterRule(_localctx, 122, Python3Parser::RuleLiteral_expr);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    setState(883);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 110, _ctx)) {
    case 1: {
      enterOuterAlt(_localctx, 1);
      setState(875);
      signed_number();
      setState(876);

      if (!( this->CannotBePlusMinus() )) throw FailedPredicateException(this, " this->CannotBePlusMinus() ");
      break;
    }

    case 2: {
      enterOuterAlt(_localctx, 2);
      setState(878);
      complex_number();
      break;
    }

    case 3: {
      enterOuterAlt(_localctx, 3);
      setState(879);
      strings();
      break;
    }

    case 4: {
      enterOuterAlt(_localctx, 4);
      setState(880);
      match(Python3Parser::NONE);
      break;
    }

    case 5: {
      enterOuterAlt(_localctx, 5);
      setState(881);
      match(Python3Parser::TRUE);
      break;
    }

    case 6: {
      enterOuterAlt(_localctx, 6);
      setState(882);
      match(Python3Parser::FALSE);
      break;
    }

    default:
      break;
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- Complex_numberContext ------------------------------------------------------------------

Python3Parser::Complex_numberContext::Complex_numberContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

Python3Parser::Signed_real_numberContext* Python3Parser::Complex_numberContext::signed_real_number() {
  return getRuleContext<Python3Parser::Signed_real_numberContext>(0);
}

tree::TerminalNode* Python3Parser::Complex_numberContext::ADD() {
  return getToken(Python3Parser::ADD, 0);
}

Python3Parser::Imaginary_numberContext* Python3Parser::Complex_numberContext::imaginary_number() {
  return getRuleContext<Python3Parser::Imaginary_numberContext>(0);
}

tree::TerminalNode* Python3Parser::Complex_numberContext::MINUS() {
  return getToken(Python3Parser::MINUS, 0);
}


size_t Python3Parser::Complex_numberContext::getRuleIndex() const {
  return Python3Parser::RuleComplex_number;
}

void Python3Parser::Complex_numberContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<Python3ParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterComplex_number(this);
}

void Python3Parser::Complex_numberContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<Python3ParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitComplex_number(this);
}


antlrcpp::Any Python3Parser::Complex_numberContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<Python3ParserVisitor*>(visitor))
    return parserVisitor->visitComplex_number(this);
  else
    return visitor->visitChildren(this);
}

Python3Parser::Complex_numberContext* Python3Parser::complex_number() {
  Complex_numberContext *_localctx = _tracker.createInstance<Complex_numberContext>(_ctx, getState());
  enterRule(_localctx, 124, Python3Parser::RuleComplex_number);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    setState(893);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 111, _ctx)) {
    case 1: {
      enterOuterAlt(_localctx, 1);
      setState(885);
      signed_real_number();
      setState(886);
      match(Python3Parser::ADD);
      setState(887);
      imaginary_number();
      break;
    }

    case 2: {
      enterOuterAlt(_localctx, 2);
      setState(889);
      signed_real_number();
      setState(890);
      match(Python3Parser::MINUS);
      setState(891);
      imaginary_number();
      break;
    }

    default:
      break;
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- Signed_numberContext ------------------------------------------------------------------

Python3Parser::Signed_numberContext::Signed_numberContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* Python3Parser::Signed_numberContext::NUMBER() {
  return getToken(Python3Parser::NUMBER, 0);
}

tree::TerminalNode* Python3Parser::Signed_numberContext::MINUS() {
  return getToken(Python3Parser::MINUS, 0);
}


size_t Python3Parser::Signed_numberContext::getRuleIndex() const {
  return Python3Parser::RuleSigned_number;
}

void Python3Parser::Signed_numberContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<Python3ParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterSigned_number(this);
}

void Python3Parser::Signed_numberContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<Python3ParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitSigned_number(this);
}


antlrcpp::Any Python3Parser::Signed_numberContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<Python3ParserVisitor*>(visitor))
    return parserVisitor->visitSigned_number(this);
  else
    return visitor->visitChildren(this);
}

Python3Parser::Signed_numberContext* Python3Parser::signed_number() {
  Signed_numberContext *_localctx = _tracker.createInstance<Signed_numberContext>(_ctx, getState());
  enterRule(_localctx, 126, Python3Parser::RuleSigned_number);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    setState(898);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case Python3Parser::NUMBER: {
        enterOuterAlt(_localctx, 1);
        setState(895);
        match(Python3Parser::NUMBER);
        break;
      }

      case Python3Parser::MINUS: {
        enterOuterAlt(_localctx, 2);
        setState(896);
        match(Python3Parser::MINUS);
        setState(897);
        match(Python3Parser::NUMBER);
        break;
      }

    default:
      throw NoViableAltException(this);
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- Signed_real_numberContext ------------------------------------------------------------------

Python3Parser::Signed_real_numberContext::Signed_real_numberContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

Python3Parser::Real_numberContext* Python3Parser::Signed_real_numberContext::real_number() {
  return getRuleContext<Python3Parser::Real_numberContext>(0);
}

tree::TerminalNode* Python3Parser::Signed_real_numberContext::MINUS() {
  return getToken(Python3Parser::MINUS, 0);
}


size_t Python3Parser::Signed_real_numberContext::getRuleIndex() const {
  return Python3Parser::RuleSigned_real_number;
}

void Python3Parser::Signed_real_numberContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<Python3ParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterSigned_real_number(this);
}

void Python3Parser::Signed_real_numberContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<Python3ParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitSigned_real_number(this);
}


antlrcpp::Any Python3Parser::Signed_real_numberContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<Python3ParserVisitor*>(visitor))
    return parserVisitor->visitSigned_real_number(this);
  else
    return visitor->visitChildren(this);
}

Python3Parser::Signed_real_numberContext* Python3Parser::signed_real_number() {
  Signed_real_numberContext *_localctx = _tracker.createInstance<Signed_real_numberContext>(_ctx, getState());
  enterRule(_localctx, 128, Python3Parser::RuleSigned_real_number);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    setState(903);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case Python3Parser::NUMBER: {
        enterOuterAlt(_localctx, 1);
        setState(900);
        real_number();
        break;
      }

      case Python3Parser::MINUS: {
        enterOuterAlt(_localctx, 2);
        setState(901);
        match(Python3Parser::MINUS);
        setState(902);
        real_number();
        break;
      }

    default:
      throw NoViableAltException(this);
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- Real_numberContext ------------------------------------------------------------------

Python3Parser::Real_numberContext::Real_numberContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* Python3Parser::Real_numberContext::NUMBER() {
  return getToken(Python3Parser::NUMBER, 0);
}


size_t Python3Parser::Real_numberContext::getRuleIndex() const {
  return Python3Parser::RuleReal_number;
}

void Python3Parser::Real_numberContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<Python3ParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterReal_number(this);
}

void Python3Parser::Real_numberContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<Python3ParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitReal_number(this);
}


antlrcpp::Any Python3Parser::Real_numberContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<Python3ParserVisitor*>(visitor))
    return parserVisitor->visitReal_number(this);
  else
    return visitor->visitChildren(this);
}

Python3Parser::Real_numberContext* Python3Parser::real_number() {
  Real_numberContext *_localctx = _tracker.createInstance<Real_numberContext>(_ctx, getState());
  enterRule(_localctx, 130, Python3Parser::RuleReal_number);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(905);
    match(Python3Parser::NUMBER);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- Imaginary_numberContext ------------------------------------------------------------------

Python3Parser::Imaginary_numberContext::Imaginary_numberContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* Python3Parser::Imaginary_numberContext::NUMBER() {
  return getToken(Python3Parser::NUMBER, 0);
}


size_t Python3Parser::Imaginary_numberContext::getRuleIndex() const {
  return Python3Parser::RuleImaginary_number;
}

void Python3Parser::Imaginary_numberContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<Python3ParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterImaginary_number(this);
}

void Python3Parser::Imaginary_numberContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<Python3ParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitImaginary_number(this);
}


antlrcpp::Any Python3Parser::Imaginary_numberContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<Python3ParserVisitor*>(visitor))
    return parserVisitor->visitImaginary_number(this);
  else
    return visitor->visitChildren(this);
}

Python3Parser::Imaginary_numberContext* Python3Parser::imaginary_number() {
  Imaginary_numberContext *_localctx = _tracker.createInstance<Imaginary_numberContext>(_ctx, getState());
  enterRule(_localctx, 132, Python3Parser::RuleImaginary_number);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(907);
    match(Python3Parser::NUMBER);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- Capture_patternContext ------------------------------------------------------------------

Python3Parser::Capture_patternContext::Capture_patternContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

Python3Parser::Pattern_capture_targetContext* Python3Parser::Capture_patternContext::pattern_capture_target() {
  return getRuleContext<Python3Parser::Pattern_capture_targetContext>(0);
}


size_t Python3Parser::Capture_patternContext::getRuleIndex() const {
  return Python3Parser::RuleCapture_pattern;
}

void Python3Parser::Capture_patternContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<Python3ParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterCapture_pattern(this);
}

void Python3Parser::Capture_patternContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<Python3ParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitCapture_pattern(this);
}


antlrcpp::Any Python3Parser::Capture_patternContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<Python3ParserVisitor*>(visitor))
    return parserVisitor->visitCapture_pattern(this);
  else
    return visitor->visitChildren(this);
}

Python3Parser::Capture_patternContext* Python3Parser::capture_pattern() {
  Capture_patternContext *_localctx = _tracker.createInstance<Capture_patternContext>(_ctx, getState());
  enterRule(_localctx, 134, Python3Parser::RuleCapture_pattern);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(909);
    pattern_capture_target();
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- Pattern_capture_targetContext ------------------------------------------------------------------

Python3Parser::Pattern_capture_targetContext::Pattern_capture_targetContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

Python3Parser::NameContext* Python3Parser::Pattern_capture_targetContext::name() {
  return getRuleContext<Python3Parser::NameContext>(0);
}


size_t Python3Parser::Pattern_capture_targetContext::getRuleIndex() const {
  return Python3Parser::RulePattern_capture_target;
}

void Python3Parser::Pattern_capture_targetContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<Python3ParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterPattern_capture_target(this);
}

void Python3Parser::Pattern_capture_targetContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<Python3ParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitPattern_capture_target(this);
}


antlrcpp::Any Python3Parser::Pattern_capture_targetContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<Python3ParserVisitor*>(visitor))
    return parserVisitor->visitPattern_capture_target(this);
  else
    return visitor->visitChildren(this);
}

Python3Parser::Pattern_capture_targetContext* Python3Parser::pattern_capture_target() {
  Pattern_capture_targetContext *_localctx = _tracker.createInstance<Pattern_capture_targetContext>(_ctx, getState());
  enterRule(_localctx, 136, Python3Parser::RulePattern_capture_target);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(911);
    name();
    setState(912);

    if (!( this->CannotBeDotLpEq() )) throw FailedPredicateException(this, " this->CannotBeDotLpEq() ");
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- Wildcard_patternContext ------------------------------------------------------------------

Python3Parser::Wildcard_patternContext::Wildcard_patternContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* Python3Parser::Wildcard_patternContext::UNDERSCORE() {
  return getToken(Python3Parser::UNDERSCORE, 0);
}


size_t Python3Parser::Wildcard_patternContext::getRuleIndex() const {
  return Python3Parser::RuleWildcard_pattern;
}

void Python3Parser::Wildcard_patternContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<Python3ParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterWildcard_pattern(this);
}

void Python3Parser::Wildcard_patternContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<Python3ParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitWildcard_pattern(this);
}


antlrcpp::Any Python3Parser::Wildcard_patternContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<Python3ParserVisitor*>(visitor))
    return parserVisitor->visitWildcard_pattern(this);
  else
    return visitor->visitChildren(this);
}

Python3Parser::Wildcard_patternContext* Python3Parser::wildcard_pattern() {
  Wildcard_patternContext *_localctx = _tracker.createInstance<Wildcard_patternContext>(_ctx, getState());
  enterRule(_localctx, 138, Python3Parser::RuleWildcard_pattern);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(914);
    match(Python3Parser::UNDERSCORE);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- Value_patternContext ------------------------------------------------------------------

Python3Parser::Value_patternContext::Value_patternContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

Python3Parser::AttrContext* Python3Parser::Value_patternContext::attr() {
  return getRuleContext<Python3Parser::AttrContext>(0);
}


size_t Python3Parser::Value_patternContext::getRuleIndex() const {
  return Python3Parser::RuleValue_pattern;
}

void Python3Parser::Value_patternContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<Python3ParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterValue_pattern(this);
}

void Python3Parser::Value_patternContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<Python3ParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitValue_pattern(this);
}


antlrcpp::Any Python3Parser::Value_patternContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<Python3ParserVisitor*>(visitor))
    return parserVisitor->visitValue_pattern(this);
  else
    return visitor->visitChildren(this);
}

Python3Parser::Value_patternContext* Python3Parser::value_pattern() {
  Value_patternContext *_localctx = _tracker.createInstance<Value_patternContext>(_ctx, getState());
  enterRule(_localctx, 140, Python3Parser::RuleValue_pattern);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(916);
    attr();
    setState(917);

    if (!( this->CannotBeDotLpEq() )) throw FailedPredicateException(this, " this->CannotBeDotLpEq() ");
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- AttrContext ------------------------------------------------------------------

Python3Parser::AttrContext::AttrContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

std::vector<Python3Parser::NameContext *> Python3Parser::AttrContext::name() {
  return getRuleContexts<Python3Parser::NameContext>();
}

Python3Parser::NameContext* Python3Parser::AttrContext::name(size_t i) {
  return getRuleContext<Python3Parser::NameContext>(i);
}

std::vector<tree::TerminalNode *> Python3Parser::AttrContext::DOT() {
  return getTokens(Python3Parser::DOT);
}

tree::TerminalNode* Python3Parser::AttrContext::DOT(size_t i) {
  return getToken(Python3Parser::DOT, i);
}


size_t Python3Parser::AttrContext::getRuleIndex() const {
  return Python3Parser::RuleAttr;
}

void Python3Parser::AttrContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<Python3ParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterAttr(this);
}

void Python3Parser::AttrContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<Python3ParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitAttr(this);
}


antlrcpp::Any Python3Parser::AttrContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<Python3ParserVisitor*>(visitor))
    return parserVisitor->visitAttr(this);
  else
    return visitor->visitChildren(this);
}

Python3Parser::AttrContext* Python3Parser::attr() {
  AttrContext *_localctx = _tracker.createInstance<AttrContext>(_ctx, getState());
  enterRule(_localctx, 142, Python3Parser::RuleAttr);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    size_t alt;
    enterOuterAlt(_localctx, 1);
    setState(919);
    name();
    setState(922); 
    _errHandler->sync(this);
    alt = 1;
    do {
      switch (alt) {
        case 1: {
              setState(920);
              match(Python3Parser::DOT);
              setState(921);
              name();
              break;
            }

      default:
        throw NoViableAltException(this);
      }
      setState(924); 
      _errHandler->sync(this);
      alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 114, _ctx);
    } while (alt != 2 && alt != atn::ATN::INVALID_ALT_NUMBER);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- Name_or_attrContext ------------------------------------------------------------------

Python3Parser::Name_or_attrContext::Name_or_attrContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

Python3Parser::AttrContext* Python3Parser::Name_or_attrContext::attr() {
  return getRuleContext<Python3Parser::AttrContext>(0);
}

Python3Parser::NameContext* Python3Parser::Name_or_attrContext::name() {
  return getRuleContext<Python3Parser::NameContext>(0);
}


size_t Python3Parser::Name_or_attrContext::getRuleIndex() const {
  return Python3Parser::RuleName_or_attr;
}

void Python3Parser::Name_or_attrContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<Python3ParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterName_or_attr(this);
}

void Python3Parser::Name_or_attrContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<Python3ParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitName_or_attr(this);
}


antlrcpp::Any Python3Parser::Name_or_attrContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<Python3ParserVisitor*>(visitor))
    return parserVisitor->visitName_or_attr(this);
  else
    return visitor->visitChildren(this);
}

Python3Parser::Name_or_attrContext* Python3Parser::name_or_attr() {
  Name_or_attrContext *_localctx = _tracker.createInstance<Name_or_attrContext>(_ctx, getState());
  enterRule(_localctx, 144, Python3Parser::RuleName_or_attr);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    setState(928);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 115, _ctx)) {
    case 1: {
      enterOuterAlt(_localctx, 1);
      setState(926);
      attr();
      break;
    }

    case 2: {
      enterOuterAlt(_localctx, 2);
      setState(927);
      name();
      break;
    }

    default:
      break;
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- Group_patternContext ------------------------------------------------------------------

Python3Parser::Group_patternContext::Group_patternContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* Python3Parser::Group_patternContext::OPEN_PAREN() {
  return getToken(Python3Parser::OPEN_PAREN, 0);
}

Python3Parser::PatternContext* Python3Parser::Group_patternContext::pattern() {
  return getRuleContext<Python3Parser::PatternContext>(0);
}

tree::TerminalNode* Python3Parser::Group_patternContext::CLOSE_PAREN() {
  return getToken(Python3Parser::CLOSE_PAREN, 0);
}


size_t Python3Parser::Group_patternContext::getRuleIndex() const {
  return Python3Parser::RuleGroup_pattern;
}

void Python3Parser::Group_patternContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<Python3ParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterGroup_pattern(this);
}

void Python3Parser::Group_patternContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<Python3ParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitGroup_pattern(this);
}


antlrcpp::Any Python3Parser::Group_patternContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<Python3ParserVisitor*>(visitor))
    return parserVisitor->visitGroup_pattern(this);
  else
    return visitor->visitChildren(this);
}

Python3Parser::Group_patternContext* Python3Parser::group_pattern() {
  Group_patternContext *_localctx = _tracker.createInstance<Group_patternContext>(_ctx, getState());
  enterRule(_localctx, 146, Python3Parser::RuleGroup_pattern);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(930);
    match(Python3Parser::OPEN_PAREN);
    setState(931);
    pattern();
    setState(932);
    match(Python3Parser::CLOSE_PAREN);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- Sequence_patternContext ------------------------------------------------------------------

Python3Parser::Sequence_patternContext::Sequence_patternContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* Python3Parser::Sequence_patternContext::OPEN_BRACK() {
  return getToken(Python3Parser::OPEN_BRACK, 0);
}

tree::TerminalNode* Python3Parser::Sequence_patternContext::CLOSE_BRACK() {
  return getToken(Python3Parser::CLOSE_BRACK, 0);
}

Python3Parser::Maybe_sequence_patternContext* Python3Parser::Sequence_patternContext::maybe_sequence_pattern() {
  return getRuleContext<Python3Parser::Maybe_sequence_patternContext>(0);
}

tree::TerminalNode* Python3Parser::Sequence_patternContext::OPEN_PAREN() {
  return getToken(Python3Parser::OPEN_PAREN, 0);
}

tree::TerminalNode* Python3Parser::Sequence_patternContext::CLOSE_PAREN() {
  return getToken(Python3Parser::CLOSE_PAREN, 0);
}

Python3Parser::Open_sequence_patternContext* Python3Parser::Sequence_patternContext::open_sequence_pattern() {
  return getRuleContext<Python3Parser::Open_sequence_patternContext>(0);
}


size_t Python3Parser::Sequence_patternContext::getRuleIndex() const {
  return Python3Parser::RuleSequence_pattern;
}

void Python3Parser::Sequence_patternContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<Python3ParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterSequence_pattern(this);
}

void Python3Parser::Sequence_patternContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<Python3ParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitSequence_pattern(this);
}


antlrcpp::Any Python3Parser::Sequence_patternContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<Python3ParserVisitor*>(visitor))
    return parserVisitor->visitSequence_pattern(this);
  else
    return visitor->visitChildren(this);
}

Python3Parser::Sequence_patternContext* Python3Parser::sequence_pattern() {
  Sequence_patternContext *_localctx = _tracker.createInstance<Sequence_patternContext>(_ctx, getState());
  enterRule(_localctx, 148, Python3Parser::RuleSequence_pattern);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    setState(944);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case Python3Parser::OPEN_BRACK: {
        enterOuterAlt(_localctx, 1);
        setState(934);
        match(Python3Parser::OPEN_BRACK);
        setState(936);
        _errHandler->sync(this);

        _la = _input->LA(1);
        if ((((_la & ~ 0x3fULL) == 0) &&
          ((1ULL << _la) & ((1ULL << Python3Parser::STRING)
          | (1ULL << Python3Parser::NUMBER)
          | (1ULL << Python3Parser::FALSE)
          | (1ULL << Python3Parser::MATCH)
          | (1ULL << Python3Parser::NONE)
          | (1ULL << Python3Parser::TRUE)
          | (1ULL << Python3Parser::UNDERSCORE)
          | (1ULL << Python3Parser::NAME)
          | (1ULL << Python3Parser::STAR)
          | (1ULL << Python3Parser::OPEN_PAREN))) != 0) || ((((_la - 64) & ~ 0x3fULL) == 0) &&
          ((1ULL << (_la - 64)) & ((1ULL << (Python3Parser::OPEN_BRACK - 64))
          | (1ULL << (Python3Parser::MINUS - 64))
          | (1ULL << (Python3Parser::OPEN_BRACE - 64)))) != 0)) {
          setState(935);
          maybe_sequence_pattern();
        }
        setState(938);
        match(Python3Parser::CLOSE_BRACK);
        break;
      }

      case Python3Parser::OPEN_PAREN: {
        enterOuterAlt(_localctx, 2);
        setState(939);
        match(Python3Parser::OPEN_PAREN);
        setState(941);
        _errHandler->sync(this);

        _la = _input->LA(1);
        if ((((_la & ~ 0x3fULL) == 0) &&
          ((1ULL << _la) & ((1ULL << Python3Parser::STRING)
          | (1ULL << Python3Parser::NUMBER)
          | (1ULL << Python3Parser::FALSE)
          | (1ULL << Python3Parser::MATCH)
          | (1ULL << Python3Parser::NONE)
          | (1ULL << Python3Parser::TRUE)
          | (1ULL << Python3Parser::UNDERSCORE)
          | (1ULL << Python3Parser::NAME)
          | (1ULL << Python3Parser::STAR)
          | (1ULL << Python3Parser::OPEN_PAREN))) != 0) || ((((_la - 64) & ~ 0x3fULL) == 0) &&
          ((1ULL << (_la - 64)) & ((1ULL << (Python3Parser::OPEN_BRACK - 64))
          | (1ULL << (Python3Parser::MINUS - 64))
          | (1ULL << (Python3Parser::OPEN_BRACE - 64)))) != 0)) {
          setState(940);
          open_sequence_pattern();
        }
        setState(943);
        match(Python3Parser::CLOSE_PAREN);
        break;
      }

    default:
      throw NoViableAltException(this);
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- Open_sequence_patternContext ------------------------------------------------------------------

Python3Parser::Open_sequence_patternContext::Open_sequence_patternContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

Python3Parser::Maybe_star_patternContext* Python3Parser::Open_sequence_patternContext::maybe_star_pattern() {
  return getRuleContext<Python3Parser::Maybe_star_patternContext>(0);
}

tree::TerminalNode* Python3Parser::Open_sequence_patternContext::COMMA() {
  return getToken(Python3Parser::COMMA, 0);
}

Python3Parser::Maybe_sequence_patternContext* Python3Parser::Open_sequence_patternContext::maybe_sequence_pattern() {
  return getRuleContext<Python3Parser::Maybe_sequence_patternContext>(0);
}


size_t Python3Parser::Open_sequence_patternContext::getRuleIndex() const {
  return Python3Parser::RuleOpen_sequence_pattern;
}

void Python3Parser::Open_sequence_patternContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<Python3ParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterOpen_sequence_pattern(this);
}

void Python3Parser::Open_sequence_patternContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<Python3ParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitOpen_sequence_pattern(this);
}


antlrcpp::Any Python3Parser::Open_sequence_patternContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<Python3ParserVisitor*>(visitor))
    return parserVisitor->visitOpen_sequence_pattern(this);
  else
    return visitor->visitChildren(this);
}

Python3Parser::Open_sequence_patternContext* Python3Parser::open_sequence_pattern() {
  Open_sequence_patternContext *_localctx = _tracker.createInstance<Open_sequence_patternContext>(_ctx, getState());
  enterRule(_localctx, 150, Python3Parser::RuleOpen_sequence_pattern);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(946);
    maybe_star_pattern();
    setState(947);
    match(Python3Parser::COMMA);
    setState(949);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if ((((_la & ~ 0x3fULL) == 0) &&
      ((1ULL << _la) & ((1ULL << Python3Parser::STRING)
      | (1ULL << Python3Parser::NUMBER)
      | (1ULL << Python3Parser::FALSE)
      | (1ULL << Python3Parser::MATCH)
      | (1ULL << Python3Parser::NONE)
      | (1ULL << Python3Parser::TRUE)
      | (1ULL << Python3Parser::UNDERSCORE)
      | (1ULL << Python3Parser::NAME)
      | (1ULL << Python3Parser::STAR)
      | (1ULL << Python3Parser::OPEN_PAREN))) != 0) || ((((_la - 64) & ~ 0x3fULL) == 0) &&
      ((1ULL << (_la - 64)) & ((1ULL << (Python3Parser::OPEN_BRACK - 64))
      | (1ULL << (Python3Parser::MINUS - 64))
      | (1ULL << (Python3Parser::OPEN_BRACE - 64)))) != 0)) {
      setState(948);
      maybe_sequence_pattern();
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- Maybe_sequence_patternContext ------------------------------------------------------------------

Python3Parser::Maybe_sequence_patternContext::Maybe_sequence_patternContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

std::vector<Python3Parser::Maybe_star_patternContext *> Python3Parser::Maybe_sequence_patternContext::maybe_star_pattern() {
  return getRuleContexts<Python3Parser::Maybe_star_patternContext>();
}

Python3Parser::Maybe_star_patternContext* Python3Parser::Maybe_sequence_patternContext::maybe_star_pattern(size_t i) {
  return getRuleContext<Python3Parser::Maybe_star_patternContext>(i);
}

std::vector<tree::TerminalNode *> Python3Parser::Maybe_sequence_patternContext::COMMA() {
  return getTokens(Python3Parser::COMMA);
}

tree::TerminalNode* Python3Parser::Maybe_sequence_patternContext::COMMA(size_t i) {
  return getToken(Python3Parser::COMMA, i);
}


size_t Python3Parser::Maybe_sequence_patternContext::getRuleIndex() const {
  return Python3Parser::RuleMaybe_sequence_pattern;
}

void Python3Parser::Maybe_sequence_patternContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<Python3ParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterMaybe_sequence_pattern(this);
}

void Python3Parser::Maybe_sequence_patternContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<Python3ParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitMaybe_sequence_pattern(this);
}


antlrcpp::Any Python3Parser::Maybe_sequence_patternContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<Python3ParserVisitor*>(visitor))
    return parserVisitor->visitMaybe_sequence_pattern(this);
  else
    return visitor->visitChildren(this);
}

Python3Parser::Maybe_sequence_patternContext* Python3Parser::maybe_sequence_pattern() {
  Maybe_sequence_patternContext *_localctx = _tracker.createInstance<Maybe_sequence_patternContext>(_ctx, getState());
  enterRule(_localctx, 152, Python3Parser::RuleMaybe_sequence_pattern);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    size_t alt;
    enterOuterAlt(_localctx, 1);
    setState(951);
    maybe_star_pattern();
    setState(956);
    _errHandler->sync(this);
    alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 120, _ctx);
    while (alt != 2 && alt != atn::ATN::INVALID_ALT_NUMBER) {
      if (alt == 1) {
        setState(952);
        match(Python3Parser::COMMA);
        setState(953);
        maybe_star_pattern(); 
      }
      setState(958);
      _errHandler->sync(this);
      alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 120, _ctx);
    }
    setState(960);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == Python3Parser::COMMA) {
      setState(959);
      match(Python3Parser::COMMA);
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- Maybe_star_patternContext ------------------------------------------------------------------

Python3Parser::Maybe_star_patternContext::Maybe_star_patternContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

Python3Parser::Star_patternContext* Python3Parser::Maybe_star_patternContext::star_pattern() {
  return getRuleContext<Python3Parser::Star_patternContext>(0);
}

Python3Parser::PatternContext* Python3Parser::Maybe_star_patternContext::pattern() {
  return getRuleContext<Python3Parser::PatternContext>(0);
}


size_t Python3Parser::Maybe_star_patternContext::getRuleIndex() const {
  return Python3Parser::RuleMaybe_star_pattern;
}

void Python3Parser::Maybe_star_patternContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<Python3ParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterMaybe_star_pattern(this);
}

void Python3Parser::Maybe_star_patternContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<Python3ParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitMaybe_star_pattern(this);
}


antlrcpp::Any Python3Parser::Maybe_star_patternContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<Python3ParserVisitor*>(visitor))
    return parserVisitor->visitMaybe_star_pattern(this);
  else
    return visitor->visitChildren(this);
}

Python3Parser::Maybe_star_patternContext* Python3Parser::maybe_star_pattern() {
  Maybe_star_patternContext *_localctx = _tracker.createInstance<Maybe_star_patternContext>(_ctx, getState());
  enterRule(_localctx, 154, Python3Parser::RuleMaybe_star_pattern);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    setState(964);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case Python3Parser::STAR: {
        enterOuterAlt(_localctx, 1);
        setState(962);
        star_pattern();
        break;
      }

      case Python3Parser::STRING:
      case Python3Parser::NUMBER:
      case Python3Parser::FALSE:
      case Python3Parser::MATCH:
      case Python3Parser::NONE:
      case Python3Parser::TRUE:
      case Python3Parser::UNDERSCORE:
      case Python3Parser::NAME:
      case Python3Parser::OPEN_PAREN:
      case Python3Parser::OPEN_BRACK:
      case Python3Parser::MINUS:
      case Python3Parser::OPEN_BRACE: {
        enterOuterAlt(_localctx, 2);
        setState(963);
        pattern();
        break;
      }

    default:
      throw NoViableAltException(this);
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- Star_patternContext ------------------------------------------------------------------

Python3Parser::Star_patternContext::Star_patternContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* Python3Parser::Star_patternContext::STAR() {
  return getToken(Python3Parser::STAR, 0);
}

Python3Parser::Pattern_capture_targetContext* Python3Parser::Star_patternContext::pattern_capture_target() {
  return getRuleContext<Python3Parser::Pattern_capture_targetContext>(0);
}

Python3Parser::Wildcard_patternContext* Python3Parser::Star_patternContext::wildcard_pattern() {
  return getRuleContext<Python3Parser::Wildcard_patternContext>(0);
}


size_t Python3Parser::Star_patternContext::getRuleIndex() const {
  return Python3Parser::RuleStar_pattern;
}

void Python3Parser::Star_patternContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<Python3ParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterStar_pattern(this);
}

void Python3Parser::Star_patternContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<Python3ParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitStar_pattern(this);
}


antlrcpp::Any Python3Parser::Star_patternContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<Python3ParserVisitor*>(visitor))
    return parserVisitor->visitStar_pattern(this);
  else
    return visitor->visitChildren(this);
}

Python3Parser::Star_patternContext* Python3Parser::star_pattern() {
  Star_patternContext *_localctx = _tracker.createInstance<Star_patternContext>(_ctx, getState());
  enterRule(_localctx, 156, Python3Parser::RuleStar_pattern);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    setState(970);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 123, _ctx)) {
    case 1: {
      enterOuterAlt(_localctx, 1);
      setState(966);
      match(Python3Parser::STAR);
      setState(967);
      pattern_capture_target();
      break;
    }

    case 2: {
      enterOuterAlt(_localctx, 2);
      setState(968);
      match(Python3Parser::STAR);
      setState(969);
      wildcard_pattern();
      break;
    }

    default:
      break;
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- Mapping_patternContext ------------------------------------------------------------------

Python3Parser::Mapping_patternContext::Mapping_patternContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* Python3Parser::Mapping_patternContext::OPEN_BRACE() {
  return getToken(Python3Parser::OPEN_BRACE, 0);
}

tree::TerminalNode* Python3Parser::Mapping_patternContext::CLOSE_BRACE() {
  return getToken(Python3Parser::CLOSE_BRACE, 0);
}

Python3Parser::Double_star_patternContext* Python3Parser::Mapping_patternContext::double_star_pattern() {
  return getRuleContext<Python3Parser::Double_star_patternContext>(0);
}

std::vector<tree::TerminalNode *> Python3Parser::Mapping_patternContext::COMMA() {
  return getTokens(Python3Parser::COMMA);
}

tree::TerminalNode* Python3Parser::Mapping_patternContext::COMMA(size_t i) {
  return getToken(Python3Parser::COMMA, i);
}

Python3Parser::Items_patternContext* Python3Parser::Mapping_patternContext::items_pattern() {
  return getRuleContext<Python3Parser::Items_patternContext>(0);
}


size_t Python3Parser::Mapping_patternContext::getRuleIndex() const {
  return Python3Parser::RuleMapping_pattern;
}

void Python3Parser::Mapping_patternContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<Python3ParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterMapping_pattern(this);
}

void Python3Parser::Mapping_patternContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<Python3ParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitMapping_pattern(this);
}


antlrcpp::Any Python3Parser::Mapping_patternContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<Python3ParserVisitor*>(visitor))
    return parserVisitor->visitMapping_pattern(this);
  else
    return visitor->visitChildren(this);
}

Python3Parser::Mapping_patternContext* Python3Parser::mapping_pattern() {
  Mapping_patternContext *_localctx = _tracker.createInstance<Mapping_patternContext>(_ctx, getState());
  enterRule(_localctx, 158, Python3Parser::RuleMapping_pattern);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    setState(997);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 127, _ctx)) {
    case 1: {
      enterOuterAlt(_localctx, 1);
      setState(972);
      match(Python3Parser::OPEN_BRACE);
      setState(973);
      match(Python3Parser::CLOSE_BRACE);
      break;
    }

    case 2: {
      enterOuterAlt(_localctx, 2);
      setState(974);
      match(Python3Parser::OPEN_BRACE);
      setState(975);
      double_star_pattern();
      setState(977);
      _errHandler->sync(this);

      _la = _input->LA(1);
      if (_la == Python3Parser::COMMA) {
        setState(976);
        match(Python3Parser::COMMA);
      }
      setState(979);
      match(Python3Parser::CLOSE_BRACE);
      break;
    }

    case 3: {
      enterOuterAlt(_localctx, 3);
      setState(981);
      match(Python3Parser::OPEN_BRACE);
      setState(982);
      items_pattern();
      setState(983);
      match(Python3Parser::COMMA);
      setState(984);
      double_star_pattern();
      setState(986);
      _errHandler->sync(this);

      _la = _input->LA(1);
      if (_la == Python3Parser::COMMA) {
        setState(985);
        match(Python3Parser::COMMA);
      }
      setState(988);
      match(Python3Parser::CLOSE_BRACE);
      break;
    }

    case 4: {
      enterOuterAlt(_localctx, 4);
      setState(990);
      match(Python3Parser::OPEN_BRACE);
      setState(991);
      items_pattern();
      setState(993);
      _errHandler->sync(this);

      _la = _input->LA(1);
      if (_la == Python3Parser::COMMA) {
        setState(992);
        match(Python3Parser::COMMA);
      }
      setState(995);
      match(Python3Parser::CLOSE_BRACE);
      break;
    }

    default:
      break;
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- Items_patternContext ------------------------------------------------------------------

Python3Parser::Items_patternContext::Items_patternContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

std::vector<Python3Parser::Key_value_patternContext *> Python3Parser::Items_patternContext::key_value_pattern() {
  return getRuleContexts<Python3Parser::Key_value_patternContext>();
}

Python3Parser::Key_value_patternContext* Python3Parser::Items_patternContext::key_value_pattern(size_t i) {
  return getRuleContext<Python3Parser::Key_value_patternContext>(i);
}

std::vector<tree::TerminalNode *> Python3Parser::Items_patternContext::COMMA() {
  return getTokens(Python3Parser::COMMA);
}

tree::TerminalNode* Python3Parser::Items_patternContext::COMMA(size_t i) {
  return getToken(Python3Parser::COMMA, i);
}


size_t Python3Parser::Items_patternContext::getRuleIndex() const {
  return Python3Parser::RuleItems_pattern;
}

void Python3Parser::Items_patternContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<Python3ParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterItems_pattern(this);
}

void Python3Parser::Items_patternContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<Python3ParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitItems_pattern(this);
}


antlrcpp::Any Python3Parser::Items_patternContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<Python3ParserVisitor*>(visitor))
    return parserVisitor->visitItems_pattern(this);
  else
    return visitor->visitChildren(this);
}

Python3Parser::Items_patternContext* Python3Parser::items_pattern() {
  Items_patternContext *_localctx = _tracker.createInstance<Items_patternContext>(_ctx, getState());
  enterRule(_localctx, 160, Python3Parser::RuleItems_pattern);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    size_t alt;
    enterOuterAlt(_localctx, 1);
    setState(999);
    key_value_pattern();
    setState(1004);
    _errHandler->sync(this);
    alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 128, _ctx);
    while (alt != 2 && alt != atn::ATN::INVALID_ALT_NUMBER) {
      if (alt == 1) {
        setState(1000);
        match(Python3Parser::COMMA);
        setState(1001);
        key_value_pattern(); 
      }
      setState(1006);
      _errHandler->sync(this);
      alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 128, _ctx);
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- Key_value_patternContext ------------------------------------------------------------------

Python3Parser::Key_value_patternContext::Key_value_patternContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* Python3Parser::Key_value_patternContext::COLON() {
  return getToken(Python3Parser::COLON, 0);
}

Python3Parser::PatternContext* Python3Parser::Key_value_patternContext::pattern() {
  return getRuleContext<Python3Parser::PatternContext>(0);
}

Python3Parser::Literal_exprContext* Python3Parser::Key_value_patternContext::literal_expr() {
  return getRuleContext<Python3Parser::Literal_exprContext>(0);
}

Python3Parser::AttrContext* Python3Parser::Key_value_patternContext::attr() {
  return getRuleContext<Python3Parser::AttrContext>(0);
}


size_t Python3Parser::Key_value_patternContext::getRuleIndex() const {
  return Python3Parser::RuleKey_value_pattern;
}

void Python3Parser::Key_value_patternContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<Python3ParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterKey_value_pattern(this);
}

void Python3Parser::Key_value_patternContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<Python3ParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitKey_value_pattern(this);
}


antlrcpp::Any Python3Parser::Key_value_patternContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<Python3ParserVisitor*>(visitor))
    return parserVisitor->visitKey_value_pattern(this);
  else
    return visitor->visitChildren(this);
}

Python3Parser::Key_value_patternContext* Python3Parser::key_value_pattern() {
  Key_value_patternContext *_localctx = _tracker.createInstance<Key_value_patternContext>(_ctx, getState());
  enterRule(_localctx, 162, Python3Parser::RuleKey_value_pattern);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(1009);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case Python3Parser::STRING:
      case Python3Parser::NUMBER:
      case Python3Parser::FALSE:
      case Python3Parser::NONE:
      case Python3Parser::TRUE:
      case Python3Parser::MINUS: {
        setState(1007);
        literal_expr();
        break;
      }

      case Python3Parser::MATCH:
      case Python3Parser::UNDERSCORE:
      case Python3Parser::NAME: {
        setState(1008);
        attr();
        break;
      }

    default:
      throw NoViableAltException(this);
    }
    setState(1011);
    match(Python3Parser::COLON);
    setState(1012);
    pattern();
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- Double_star_patternContext ------------------------------------------------------------------

Python3Parser::Double_star_patternContext::Double_star_patternContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* Python3Parser::Double_star_patternContext::POWER() {
  return getToken(Python3Parser::POWER, 0);
}

Python3Parser::Pattern_capture_targetContext* Python3Parser::Double_star_patternContext::pattern_capture_target() {
  return getRuleContext<Python3Parser::Pattern_capture_targetContext>(0);
}


size_t Python3Parser::Double_star_patternContext::getRuleIndex() const {
  return Python3Parser::RuleDouble_star_pattern;
}

void Python3Parser::Double_star_patternContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<Python3ParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterDouble_star_pattern(this);
}

void Python3Parser::Double_star_patternContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<Python3ParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitDouble_star_pattern(this);
}


antlrcpp::Any Python3Parser::Double_star_patternContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<Python3ParserVisitor*>(visitor))
    return parserVisitor->visitDouble_star_pattern(this);
  else
    return visitor->visitChildren(this);
}

Python3Parser::Double_star_patternContext* Python3Parser::double_star_pattern() {
  Double_star_patternContext *_localctx = _tracker.createInstance<Double_star_patternContext>(_ctx, getState());
  enterRule(_localctx, 164, Python3Parser::RuleDouble_star_pattern);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(1014);
    match(Python3Parser::POWER);
    setState(1015);
    pattern_capture_target();
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- Class_patternContext ------------------------------------------------------------------

Python3Parser::Class_patternContext::Class_patternContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

Python3Parser::Name_or_attrContext* Python3Parser::Class_patternContext::name_or_attr() {
  return getRuleContext<Python3Parser::Name_or_attrContext>(0);
}

tree::TerminalNode* Python3Parser::Class_patternContext::OPEN_PAREN() {
  return getToken(Python3Parser::OPEN_PAREN, 0);
}

tree::TerminalNode* Python3Parser::Class_patternContext::CLOSE_PAREN() {
  return getToken(Python3Parser::CLOSE_PAREN, 0);
}

Python3Parser::Positional_patternsContext* Python3Parser::Class_patternContext::positional_patterns() {
  return getRuleContext<Python3Parser::Positional_patternsContext>(0);
}

std::vector<tree::TerminalNode *> Python3Parser::Class_patternContext::COMMA() {
  return getTokens(Python3Parser::COMMA);
}

tree::TerminalNode* Python3Parser::Class_patternContext::COMMA(size_t i) {
  return getToken(Python3Parser::COMMA, i);
}

Python3Parser::Keyword_patternsContext* Python3Parser::Class_patternContext::keyword_patterns() {
  return getRuleContext<Python3Parser::Keyword_patternsContext>(0);
}


size_t Python3Parser::Class_patternContext::getRuleIndex() const {
  return Python3Parser::RuleClass_pattern;
}

void Python3Parser::Class_patternContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<Python3ParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterClass_pattern(this);
}

void Python3Parser::Class_patternContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<Python3ParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitClass_pattern(this);
}


antlrcpp::Any Python3Parser::Class_patternContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<Python3ParserVisitor*>(visitor))
    return parserVisitor->visitClass_pattern(this);
  else
    return visitor->visitChildren(this);
}

Python3Parser::Class_patternContext* Python3Parser::class_pattern() {
  Class_patternContext *_localctx = _tracker.createInstance<Class_patternContext>(_ctx, getState());
  enterRule(_localctx, 166, Python3Parser::RuleClass_pattern);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    setState(1047);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 133, _ctx)) {
    case 1: {
      enterOuterAlt(_localctx, 1);
      setState(1017);
      name_or_attr();
      setState(1018);
      match(Python3Parser::OPEN_PAREN);
      setState(1019);
      match(Python3Parser::CLOSE_PAREN);
      break;
    }

    case 2: {
      enterOuterAlt(_localctx, 2);
      setState(1021);
      name_or_attr();
      setState(1022);
      match(Python3Parser::OPEN_PAREN);
      setState(1023);
      positional_patterns();
      setState(1025);
      _errHandler->sync(this);

      _la = _input->LA(1);
      if (_la == Python3Parser::COMMA) {
        setState(1024);
        match(Python3Parser::COMMA);
      }
      setState(1027);
      match(Python3Parser::CLOSE_PAREN);
      break;
    }

    case 3: {
      enterOuterAlt(_localctx, 3);
      setState(1029);
      name_or_attr();
      setState(1030);
      match(Python3Parser::OPEN_PAREN);
      setState(1031);
      keyword_patterns();
      setState(1033);
      _errHandler->sync(this);

      _la = _input->LA(1);
      if (_la == Python3Parser::COMMA) {
        setState(1032);
        match(Python3Parser::COMMA);
      }
      setState(1035);
      match(Python3Parser::CLOSE_PAREN);
      break;
    }

    case 4: {
      enterOuterAlt(_localctx, 4);
      setState(1037);
      name_or_attr();
      setState(1038);
      match(Python3Parser::OPEN_PAREN);
      setState(1039);
      positional_patterns();
      setState(1040);
      match(Python3Parser::COMMA);
      setState(1041);
      keyword_patterns();
      setState(1043);
      _errHandler->sync(this);

      _la = _input->LA(1);
      if (_la == Python3Parser::COMMA) {
        setState(1042);
        match(Python3Parser::COMMA);
      }
      setState(1045);
      match(Python3Parser::CLOSE_PAREN);
      break;
    }

    default:
      break;
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- Positional_patternsContext ------------------------------------------------------------------

Python3Parser::Positional_patternsContext::Positional_patternsContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

std::vector<Python3Parser::PatternContext *> Python3Parser::Positional_patternsContext::pattern() {
  return getRuleContexts<Python3Parser::PatternContext>();
}

Python3Parser::PatternContext* Python3Parser::Positional_patternsContext::pattern(size_t i) {
  return getRuleContext<Python3Parser::PatternContext>(i);
}

std::vector<tree::TerminalNode *> Python3Parser::Positional_patternsContext::COMMA() {
  return getTokens(Python3Parser::COMMA);
}

tree::TerminalNode* Python3Parser::Positional_patternsContext::COMMA(size_t i) {
  return getToken(Python3Parser::COMMA, i);
}


size_t Python3Parser::Positional_patternsContext::getRuleIndex() const {
  return Python3Parser::RulePositional_patterns;
}

void Python3Parser::Positional_patternsContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<Python3ParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterPositional_patterns(this);
}

void Python3Parser::Positional_patternsContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<Python3ParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitPositional_patterns(this);
}


antlrcpp::Any Python3Parser::Positional_patternsContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<Python3ParserVisitor*>(visitor))
    return parserVisitor->visitPositional_patterns(this);
  else
    return visitor->visitChildren(this);
}

Python3Parser::Positional_patternsContext* Python3Parser::positional_patterns() {
  Positional_patternsContext *_localctx = _tracker.createInstance<Positional_patternsContext>(_ctx, getState());
  enterRule(_localctx, 168, Python3Parser::RulePositional_patterns);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    size_t alt;
    enterOuterAlt(_localctx, 1);
    setState(1049);
    pattern();
    setState(1054);
    _errHandler->sync(this);
    alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 134, _ctx);
    while (alt != 2 && alt != atn::ATN::INVALID_ALT_NUMBER) {
      if (alt == 1) {
        setState(1050);
        match(Python3Parser::COMMA);
        setState(1051);
        pattern(); 
      }
      setState(1056);
      _errHandler->sync(this);
      alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 134, _ctx);
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- Keyword_patternsContext ------------------------------------------------------------------

Python3Parser::Keyword_patternsContext::Keyword_patternsContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

std::vector<Python3Parser::Keyword_patternContext *> Python3Parser::Keyword_patternsContext::keyword_pattern() {
  return getRuleContexts<Python3Parser::Keyword_patternContext>();
}

Python3Parser::Keyword_patternContext* Python3Parser::Keyword_patternsContext::keyword_pattern(size_t i) {
  return getRuleContext<Python3Parser::Keyword_patternContext>(i);
}

std::vector<tree::TerminalNode *> Python3Parser::Keyword_patternsContext::COMMA() {
  return getTokens(Python3Parser::COMMA);
}

tree::TerminalNode* Python3Parser::Keyword_patternsContext::COMMA(size_t i) {
  return getToken(Python3Parser::COMMA, i);
}


size_t Python3Parser::Keyword_patternsContext::getRuleIndex() const {
  return Python3Parser::RuleKeyword_patterns;
}

void Python3Parser::Keyword_patternsContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<Python3ParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterKeyword_patterns(this);
}

void Python3Parser::Keyword_patternsContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<Python3ParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitKeyword_patterns(this);
}


antlrcpp::Any Python3Parser::Keyword_patternsContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<Python3ParserVisitor*>(visitor))
    return parserVisitor->visitKeyword_patterns(this);
  else
    return visitor->visitChildren(this);
}

Python3Parser::Keyword_patternsContext* Python3Parser::keyword_patterns() {
  Keyword_patternsContext *_localctx = _tracker.createInstance<Keyword_patternsContext>(_ctx, getState());
  enterRule(_localctx, 170, Python3Parser::RuleKeyword_patterns);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    size_t alt;
    enterOuterAlt(_localctx, 1);
    setState(1057);
    keyword_pattern();
    setState(1062);
    _errHandler->sync(this);
    alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 135, _ctx);
    while (alt != 2 && alt != atn::ATN::INVALID_ALT_NUMBER) {
      if (alt == 1) {
        setState(1058);
        match(Python3Parser::COMMA);
        setState(1059);
        keyword_pattern(); 
      }
      setState(1064);
      _errHandler->sync(this);
      alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 135, _ctx);
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- Keyword_patternContext ------------------------------------------------------------------

Python3Parser::Keyword_patternContext::Keyword_patternContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

Python3Parser::NameContext* Python3Parser::Keyword_patternContext::name() {
  return getRuleContext<Python3Parser::NameContext>(0);
}

tree::TerminalNode* Python3Parser::Keyword_patternContext::ASSIGN() {
  return getToken(Python3Parser::ASSIGN, 0);
}

Python3Parser::PatternContext* Python3Parser::Keyword_patternContext::pattern() {
  return getRuleContext<Python3Parser::PatternContext>(0);
}


size_t Python3Parser::Keyword_patternContext::getRuleIndex() const {
  return Python3Parser::RuleKeyword_pattern;
}

void Python3Parser::Keyword_patternContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<Python3ParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterKeyword_pattern(this);
}

void Python3Parser::Keyword_patternContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<Python3ParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitKeyword_pattern(this);
}


antlrcpp::Any Python3Parser::Keyword_patternContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<Python3ParserVisitor*>(visitor))
    return parserVisitor->visitKeyword_pattern(this);
  else
    return visitor->visitChildren(this);
}

Python3Parser::Keyword_patternContext* Python3Parser::keyword_pattern() {
  Keyword_patternContext *_localctx = _tracker.createInstance<Keyword_patternContext>(_ctx, getState());
  enterRule(_localctx, 172, Python3Parser::RuleKeyword_pattern);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(1065);
    name();
    setState(1066);
    match(Python3Parser::ASSIGN);
    setState(1067);
    pattern();
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- TestContext ------------------------------------------------------------------

Python3Parser::TestContext::TestContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

std::vector<Python3Parser::Or_testContext *> Python3Parser::TestContext::or_test() {
  return getRuleContexts<Python3Parser::Or_testContext>();
}

Python3Parser::Or_testContext* Python3Parser::TestContext::or_test(size_t i) {
  return getRuleContext<Python3Parser::Or_testContext>(i);
}

tree::TerminalNode* Python3Parser::TestContext::IF() {
  return getToken(Python3Parser::IF, 0);
}

tree::TerminalNode* Python3Parser::TestContext::ELSE() {
  return getToken(Python3Parser::ELSE, 0);
}

Python3Parser::TestContext* Python3Parser::TestContext::test() {
  return getRuleContext<Python3Parser::TestContext>(0);
}

Python3Parser::LambdefContext* Python3Parser::TestContext::lambdef() {
  return getRuleContext<Python3Parser::LambdefContext>(0);
}


size_t Python3Parser::TestContext::getRuleIndex() const {
  return Python3Parser::RuleTest;
}

void Python3Parser::TestContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<Python3ParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterTest(this);
}

void Python3Parser::TestContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<Python3ParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitTest(this);
}


antlrcpp::Any Python3Parser::TestContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<Python3ParserVisitor*>(visitor))
    return parserVisitor->visitTest(this);
  else
    return visitor->visitChildren(this);
}

Python3Parser::TestContext* Python3Parser::test() {
  TestContext *_localctx = _tracker.createInstance<TestContext>(_ctx, getState());
  enterRule(_localctx, 174, Python3Parser::RuleTest);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    setState(1078);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case Python3Parser::STRING:
      case Python3Parser::NUMBER:
      case Python3Parser::AWAIT:
      case Python3Parser::FALSE:
      case Python3Parser::MATCH:
      case Python3Parser::NONE:
      case Python3Parser::NOT:
      case Python3Parser::TRUE:
      case Python3Parser::UNDERSCORE:
      case Python3Parser::NAME:
      case Python3Parser::ELLIPSIS:
      case Python3Parser::OPEN_PAREN:
      case Python3Parser::OPEN_BRACK:
      case Python3Parser::ADD:
      case Python3Parser::MINUS:
      case Python3Parser::NOT_OP:
      case Python3Parser::OPEN_BRACE: {
        enterOuterAlt(_localctx, 1);
        setState(1069);
        or_test();
        setState(1075);
        _errHandler->sync(this);

        _la = _input->LA(1);
        if (_la == Python3Parser::IF) {
          setState(1070);
          match(Python3Parser::IF);
          setState(1071);
          or_test();
          setState(1072);
          match(Python3Parser::ELSE);
          setState(1073);
          test();
        }
        break;
      }

      case Python3Parser::LAMBDA: {
        enterOuterAlt(_localctx, 2);
        setState(1077);
        lambdef();
        break;
      }

    default:
      throw NoViableAltException(this);
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- Test_nocondContext ------------------------------------------------------------------

Python3Parser::Test_nocondContext::Test_nocondContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

Python3Parser::Or_testContext* Python3Parser::Test_nocondContext::or_test() {
  return getRuleContext<Python3Parser::Or_testContext>(0);
}

Python3Parser::Lambdef_nocondContext* Python3Parser::Test_nocondContext::lambdef_nocond() {
  return getRuleContext<Python3Parser::Lambdef_nocondContext>(0);
}


size_t Python3Parser::Test_nocondContext::getRuleIndex() const {
  return Python3Parser::RuleTest_nocond;
}

void Python3Parser::Test_nocondContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<Python3ParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterTest_nocond(this);
}

void Python3Parser::Test_nocondContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<Python3ParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitTest_nocond(this);
}


antlrcpp::Any Python3Parser::Test_nocondContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<Python3ParserVisitor*>(visitor))
    return parserVisitor->visitTest_nocond(this);
  else
    return visitor->visitChildren(this);
}

Python3Parser::Test_nocondContext* Python3Parser::test_nocond() {
  Test_nocondContext *_localctx = _tracker.createInstance<Test_nocondContext>(_ctx, getState());
  enterRule(_localctx, 176, Python3Parser::RuleTest_nocond);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    setState(1082);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case Python3Parser::STRING:
      case Python3Parser::NUMBER:
      case Python3Parser::AWAIT:
      case Python3Parser::FALSE:
      case Python3Parser::MATCH:
      case Python3Parser::NONE:
      case Python3Parser::NOT:
      case Python3Parser::TRUE:
      case Python3Parser::UNDERSCORE:
      case Python3Parser::NAME:
      case Python3Parser::ELLIPSIS:
      case Python3Parser::OPEN_PAREN:
      case Python3Parser::OPEN_BRACK:
      case Python3Parser::ADD:
      case Python3Parser::MINUS:
      case Python3Parser::NOT_OP:
      case Python3Parser::OPEN_BRACE: {
        enterOuterAlt(_localctx, 1);
        setState(1080);
        or_test();
        break;
      }

      case Python3Parser::LAMBDA: {
        enterOuterAlt(_localctx, 2);
        setState(1081);
        lambdef_nocond();
        break;
      }

    default:
      throw NoViableAltException(this);
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- LambdefContext ------------------------------------------------------------------

Python3Parser::LambdefContext::LambdefContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* Python3Parser::LambdefContext::LAMBDA() {
  return getToken(Python3Parser::LAMBDA, 0);
}

tree::TerminalNode* Python3Parser::LambdefContext::COLON() {
  return getToken(Python3Parser::COLON, 0);
}

Python3Parser::TestContext* Python3Parser::LambdefContext::test() {
  return getRuleContext<Python3Parser::TestContext>(0);
}

Python3Parser::VarargslistContext* Python3Parser::LambdefContext::varargslist() {
  return getRuleContext<Python3Parser::VarargslistContext>(0);
}


size_t Python3Parser::LambdefContext::getRuleIndex() const {
  return Python3Parser::RuleLambdef;
}

void Python3Parser::LambdefContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<Python3ParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterLambdef(this);
}

void Python3Parser::LambdefContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<Python3ParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitLambdef(this);
}


antlrcpp::Any Python3Parser::LambdefContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<Python3ParserVisitor*>(visitor))
    return parserVisitor->visitLambdef(this);
  else
    return visitor->visitChildren(this);
}

Python3Parser::LambdefContext* Python3Parser::lambdef() {
  LambdefContext *_localctx = _tracker.createInstance<LambdefContext>(_ctx, getState());
  enterRule(_localctx, 178, Python3Parser::RuleLambdef);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(1084);
    match(Python3Parser::LAMBDA);
    setState(1086);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if ((((_la & ~ 0x3fULL) == 0) &&
      ((1ULL << _la) & ((1ULL << Python3Parser::MATCH)
      | (1ULL << Python3Parser::UNDERSCORE)
      | (1ULL << Python3Parser::NAME)
      | (1ULL << Python3Parser::STAR)
      | (1ULL << Python3Parser::POWER))) != 0)) {
      setState(1085);
      varargslist();
    }
    setState(1088);
    match(Python3Parser::COLON);
    setState(1089);
    test();
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- Lambdef_nocondContext ------------------------------------------------------------------

Python3Parser::Lambdef_nocondContext::Lambdef_nocondContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* Python3Parser::Lambdef_nocondContext::LAMBDA() {
  return getToken(Python3Parser::LAMBDA, 0);
}

tree::TerminalNode* Python3Parser::Lambdef_nocondContext::COLON() {
  return getToken(Python3Parser::COLON, 0);
}

Python3Parser::Test_nocondContext* Python3Parser::Lambdef_nocondContext::test_nocond() {
  return getRuleContext<Python3Parser::Test_nocondContext>(0);
}

Python3Parser::VarargslistContext* Python3Parser::Lambdef_nocondContext::varargslist() {
  return getRuleContext<Python3Parser::VarargslistContext>(0);
}


size_t Python3Parser::Lambdef_nocondContext::getRuleIndex() const {
  return Python3Parser::RuleLambdef_nocond;
}

void Python3Parser::Lambdef_nocondContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<Python3ParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterLambdef_nocond(this);
}

void Python3Parser::Lambdef_nocondContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<Python3ParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitLambdef_nocond(this);
}


antlrcpp::Any Python3Parser::Lambdef_nocondContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<Python3ParserVisitor*>(visitor))
    return parserVisitor->visitLambdef_nocond(this);
  else
    return visitor->visitChildren(this);
}

Python3Parser::Lambdef_nocondContext* Python3Parser::lambdef_nocond() {
  Lambdef_nocondContext *_localctx = _tracker.createInstance<Lambdef_nocondContext>(_ctx, getState());
  enterRule(_localctx, 180, Python3Parser::RuleLambdef_nocond);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(1091);
    match(Python3Parser::LAMBDA);
    setState(1093);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if ((((_la & ~ 0x3fULL) == 0) &&
      ((1ULL << _la) & ((1ULL << Python3Parser::MATCH)
      | (1ULL << Python3Parser::UNDERSCORE)
      | (1ULL << Python3Parser::NAME)
      | (1ULL << Python3Parser::STAR)
      | (1ULL << Python3Parser::POWER))) != 0)) {
      setState(1092);
      varargslist();
    }
    setState(1095);
    match(Python3Parser::COLON);
    setState(1096);
    test_nocond();
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- Or_testContext ------------------------------------------------------------------

Python3Parser::Or_testContext::Or_testContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

std::vector<Python3Parser::And_testContext *> Python3Parser::Or_testContext::and_test() {
  return getRuleContexts<Python3Parser::And_testContext>();
}

Python3Parser::And_testContext* Python3Parser::Or_testContext::and_test(size_t i) {
  return getRuleContext<Python3Parser::And_testContext>(i);
}

std::vector<tree::TerminalNode *> Python3Parser::Or_testContext::OR() {
  return getTokens(Python3Parser::OR);
}

tree::TerminalNode* Python3Parser::Or_testContext::OR(size_t i) {
  return getToken(Python3Parser::OR, i);
}


size_t Python3Parser::Or_testContext::getRuleIndex() const {
  return Python3Parser::RuleOr_test;
}

void Python3Parser::Or_testContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<Python3ParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterOr_test(this);
}

void Python3Parser::Or_testContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<Python3ParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitOr_test(this);
}


antlrcpp::Any Python3Parser::Or_testContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<Python3ParserVisitor*>(visitor))
    return parserVisitor->visitOr_test(this);
  else
    return visitor->visitChildren(this);
}

Python3Parser::Or_testContext* Python3Parser::or_test() {
  Or_testContext *_localctx = _tracker.createInstance<Or_testContext>(_ctx, getState());
  enterRule(_localctx, 182, Python3Parser::RuleOr_test);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(1098);
    and_test();
    setState(1103);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while (_la == Python3Parser::OR) {
      setState(1099);
      match(Python3Parser::OR);
      setState(1100);
      and_test();
      setState(1105);
      _errHandler->sync(this);
      _la = _input->LA(1);
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- And_testContext ------------------------------------------------------------------

Python3Parser::And_testContext::And_testContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

std::vector<Python3Parser::Not_testContext *> Python3Parser::And_testContext::not_test() {
  return getRuleContexts<Python3Parser::Not_testContext>();
}

Python3Parser::Not_testContext* Python3Parser::And_testContext::not_test(size_t i) {
  return getRuleContext<Python3Parser::Not_testContext>(i);
}

std::vector<tree::TerminalNode *> Python3Parser::And_testContext::AND() {
  return getTokens(Python3Parser::AND);
}

tree::TerminalNode* Python3Parser::And_testContext::AND(size_t i) {
  return getToken(Python3Parser::AND, i);
}


size_t Python3Parser::And_testContext::getRuleIndex() const {
  return Python3Parser::RuleAnd_test;
}

void Python3Parser::And_testContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<Python3ParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterAnd_test(this);
}

void Python3Parser::And_testContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<Python3ParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitAnd_test(this);
}


antlrcpp::Any Python3Parser::And_testContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<Python3ParserVisitor*>(visitor))
    return parserVisitor->visitAnd_test(this);
  else
    return visitor->visitChildren(this);
}

Python3Parser::And_testContext* Python3Parser::and_test() {
  And_testContext *_localctx = _tracker.createInstance<And_testContext>(_ctx, getState());
  enterRule(_localctx, 184, Python3Parser::RuleAnd_test);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(1106);
    not_test();
    setState(1111);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while (_la == Python3Parser::AND) {
      setState(1107);
      match(Python3Parser::AND);
      setState(1108);
      not_test();
      setState(1113);
      _errHandler->sync(this);
      _la = _input->LA(1);
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- Not_testContext ------------------------------------------------------------------

Python3Parser::Not_testContext::Not_testContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* Python3Parser::Not_testContext::NOT() {
  return getToken(Python3Parser::NOT, 0);
}

Python3Parser::Not_testContext* Python3Parser::Not_testContext::not_test() {
  return getRuleContext<Python3Parser::Not_testContext>(0);
}

Python3Parser::ComparisonContext* Python3Parser::Not_testContext::comparison() {
  return getRuleContext<Python3Parser::ComparisonContext>(0);
}


size_t Python3Parser::Not_testContext::getRuleIndex() const {
  return Python3Parser::RuleNot_test;
}

void Python3Parser::Not_testContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<Python3ParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterNot_test(this);
}

void Python3Parser::Not_testContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<Python3ParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitNot_test(this);
}


antlrcpp::Any Python3Parser::Not_testContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<Python3ParserVisitor*>(visitor))
    return parserVisitor->visitNot_test(this);
  else
    return visitor->visitChildren(this);
}

Python3Parser::Not_testContext* Python3Parser::not_test() {
  Not_testContext *_localctx = _tracker.createInstance<Not_testContext>(_ctx, getState());
  enterRule(_localctx, 186, Python3Parser::RuleNot_test);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    setState(1117);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case Python3Parser::NOT: {
        enterOuterAlt(_localctx, 1);
        setState(1114);
        match(Python3Parser::NOT);
        setState(1115);
        not_test();
        break;
      }

      case Python3Parser::STRING:
      case Python3Parser::NUMBER:
      case Python3Parser::AWAIT:
      case Python3Parser::FALSE:
      case Python3Parser::MATCH:
      case Python3Parser::NONE:
      case Python3Parser::TRUE:
      case Python3Parser::UNDERSCORE:
      case Python3Parser::NAME:
      case Python3Parser::ELLIPSIS:
      case Python3Parser::OPEN_PAREN:
      case Python3Parser::OPEN_BRACK:
      case Python3Parser::ADD:
      case Python3Parser::MINUS:
      case Python3Parser::NOT_OP:
      case Python3Parser::OPEN_BRACE: {
        enterOuterAlt(_localctx, 2);
        setState(1116);
        comparison();
        break;
      }

    default:
      throw NoViableAltException(this);
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- ComparisonContext ------------------------------------------------------------------

Python3Parser::ComparisonContext::ComparisonContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

std::vector<Python3Parser::ExprContext *> Python3Parser::ComparisonContext::expr() {
  return getRuleContexts<Python3Parser::ExprContext>();
}

Python3Parser::ExprContext* Python3Parser::ComparisonContext::expr(size_t i) {
  return getRuleContext<Python3Parser::ExprContext>(i);
}

std::vector<Python3Parser::Comp_opContext *> Python3Parser::ComparisonContext::comp_op() {
  return getRuleContexts<Python3Parser::Comp_opContext>();
}

Python3Parser::Comp_opContext* Python3Parser::ComparisonContext::comp_op(size_t i) {
  return getRuleContext<Python3Parser::Comp_opContext>(i);
}


size_t Python3Parser::ComparisonContext::getRuleIndex() const {
  return Python3Parser::RuleComparison;
}

void Python3Parser::ComparisonContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<Python3ParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterComparison(this);
}

void Python3Parser::ComparisonContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<Python3ParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitComparison(this);
}


antlrcpp::Any Python3Parser::ComparisonContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<Python3ParserVisitor*>(visitor))
    return parserVisitor->visitComparison(this);
  else
    return visitor->visitChildren(this);
}

Python3Parser::ComparisonContext* Python3Parser::comparison() {
  ComparisonContext *_localctx = _tracker.createInstance<ComparisonContext>(_ctx, getState());
  enterRule(_localctx, 188, Python3Parser::RuleComparison);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    size_t alt;
    enterOuterAlt(_localctx, 1);
    setState(1119);
    expr(0);
    setState(1125);
    _errHandler->sync(this);
    alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 144, _ctx);
    while (alt != 2 && alt != atn::ATN::INVALID_ALT_NUMBER) {
      if (alt == 1) {
        setState(1120);
        comp_op();
        setState(1121);
        expr(0); 
      }
      setState(1127);
      _errHandler->sync(this);
      alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 144, _ctx);
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- Comp_opContext ------------------------------------------------------------------

Python3Parser::Comp_opContext::Comp_opContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* Python3Parser::Comp_opContext::LESS_THAN() {
  return getToken(Python3Parser::LESS_THAN, 0);
}

tree::TerminalNode* Python3Parser::Comp_opContext::GREATER_THAN() {
  return getToken(Python3Parser::GREATER_THAN, 0);
}

tree::TerminalNode* Python3Parser::Comp_opContext::EQUALS() {
  return getToken(Python3Parser::EQUALS, 0);
}

tree::TerminalNode* Python3Parser::Comp_opContext::GT_EQ() {
  return getToken(Python3Parser::GT_EQ, 0);
}

tree::TerminalNode* Python3Parser::Comp_opContext::LT_EQ() {
  return getToken(Python3Parser::LT_EQ, 0);
}

tree::TerminalNode* Python3Parser::Comp_opContext::NOT_EQ_1() {
  return getToken(Python3Parser::NOT_EQ_1, 0);
}

tree::TerminalNode* Python3Parser::Comp_opContext::NOT_EQ_2() {
  return getToken(Python3Parser::NOT_EQ_2, 0);
}

tree::TerminalNode* Python3Parser::Comp_opContext::IN() {
  return getToken(Python3Parser::IN, 0);
}

tree::TerminalNode* Python3Parser::Comp_opContext::NOT() {
  return getToken(Python3Parser::NOT, 0);
}

tree::TerminalNode* Python3Parser::Comp_opContext::IS() {
  return getToken(Python3Parser::IS, 0);
}


size_t Python3Parser::Comp_opContext::getRuleIndex() const {
  return Python3Parser::RuleComp_op;
}

void Python3Parser::Comp_opContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<Python3ParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterComp_op(this);
}

void Python3Parser::Comp_opContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<Python3ParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitComp_op(this);
}


antlrcpp::Any Python3Parser::Comp_opContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<Python3ParserVisitor*>(visitor))
    return parserVisitor->visitComp_op(this);
  else
    return visitor->visitChildren(this);
}

Python3Parser::Comp_opContext* Python3Parser::comp_op() {
  Comp_opContext *_localctx = _tracker.createInstance<Comp_opContext>(_ctx, getState());
  enterRule(_localctx, 190, Python3Parser::RuleComp_op);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    setState(1141);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 145, _ctx)) {
    case 1: {
      enterOuterAlt(_localctx, 1);
      setState(1128);
      match(Python3Parser::LESS_THAN);
      break;
    }

    case 2: {
      enterOuterAlt(_localctx, 2);
      setState(1129);
      match(Python3Parser::GREATER_THAN);
      break;
    }

    case 3: {
      enterOuterAlt(_localctx, 3);
      setState(1130);
      match(Python3Parser::EQUALS);
      break;
    }

    case 4: {
      enterOuterAlt(_localctx, 4);
      setState(1131);
      match(Python3Parser::GT_EQ);
      break;
    }

    case 5: {
      enterOuterAlt(_localctx, 5);
      setState(1132);
      match(Python3Parser::LT_EQ);
      break;
    }

    case 6: {
      enterOuterAlt(_localctx, 6);
      setState(1133);
      match(Python3Parser::NOT_EQ_1);
      break;
    }

    case 7: {
      enterOuterAlt(_localctx, 7);
      setState(1134);
      match(Python3Parser::NOT_EQ_2);
      break;
    }

    case 8: {
      enterOuterAlt(_localctx, 8);
      setState(1135);
      match(Python3Parser::IN);
      break;
    }

    case 9: {
      enterOuterAlt(_localctx, 9);
      setState(1136);
      match(Python3Parser::NOT);
      setState(1137);
      match(Python3Parser::IN);
      break;
    }

    case 10: {
      enterOuterAlt(_localctx, 10);
      setState(1138);
      match(Python3Parser::IS);
      break;
    }

    case 11: {
      enterOuterAlt(_localctx, 11);
      setState(1139);
      match(Python3Parser::IS);
      setState(1140);
      match(Python3Parser::NOT);
      break;
    }

    default:
      break;
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- Star_exprContext ------------------------------------------------------------------

Python3Parser::Star_exprContext::Star_exprContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* Python3Parser::Star_exprContext::STAR() {
  return getToken(Python3Parser::STAR, 0);
}

Python3Parser::ExprContext* Python3Parser::Star_exprContext::expr() {
  return getRuleContext<Python3Parser::ExprContext>(0);
}


size_t Python3Parser::Star_exprContext::getRuleIndex() const {
  return Python3Parser::RuleStar_expr;
}

void Python3Parser::Star_exprContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<Python3ParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterStar_expr(this);
}

void Python3Parser::Star_exprContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<Python3ParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitStar_expr(this);
}


antlrcpp::Any Python3Parser::Star_exprContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<Python3ParserVisitor*>(visitor))
    return parserVisitor->visitStar_expr(this);
  else
    return visitor->visitChildren(this);
}

Python3Parser::Star_exprContext* Python3Parser::star_expr() {
  Star_exprContext *_localctx = _tracker.createInstance<Star_exprContext>(_ctx, getState());
  enterRule(_localctx, 192, Python3Parser::RuleStar_expr);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(1143);
    match(Python3Parser::STAR);
    setState(1144);
    expr(0);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- ExprContext ------------------------------------------------------------------

Python3Parser::ExprContext::ExprContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

Python3Parser::Atom_exprContext* Python3Parser::ExprContext::atom_expr() {
  return getRuleContext<Python3Parser::Atom_exprContext>(0);
}

std::vector<Python3Parser::ExprContext *> Python3Parser::ExprContext::expr() {
  return getRuleContexts<Python3Parser::ExprContext>();
}

Python3Parser::ExprContext* Python3Parser::ExprContext::expr(size_t i) {
  return getRuleContext<Python3Parser::ExprContext>(i);
}

std::vector<tree::TerminalNode *> Python3Parser::ExprContext::ADD() {
  return getTokens(Python3Parser::ADD);
}

tree::TerminalNode* Python3Parser::ExprContext::ADD(size_t i) {
  return getToken(Python3Parser::ADD, i);
}

std::vector<tree::TerminalNode *> Python3Parser::ExprContext::MINUS() {
  return getTokens(Python3Parser::MINUS);
}

tree::TerminalNode* Python3Parser::ExprContext::MINUS(size_t i) {
  return getToken(Python3Parser::MINUS, i);
}

std::vector<tree::TerminalNode *> Python3Parser::ExprContext::NOT_OP() {
  return getTokens(Python3Parser::NOT_OP);
}

tree::TerminalNode* Python3Parser::ExprContext::NOT_OP(size_t i) {
  return getToken(Python3Parser::NOT_OP, i);
}

tree::TerminalNode* Python3Parser::ExprContext::POWER() {
  return getToken(Python3Parser::POWER, 0);
}

tree::TerminalNode* Python3Parser::ExprContext::STAR() {
  return getToken(Python3Parser::STAR, 0);
}

tree::TerminalNode* Python3Parser::ExprContext::AT() {
  return getToken(Python3Parser::AT, 0);
}

tree::TerminalNode* Python3Parser::ExprContext::DIV() {
  return getToken(Python3Parser::DIV, 0);
}

tree::TerminalNode* Python3Parser::ExprContext::MOD() {
  return getToken(Python3Parser::MOD, 0);
}

tree::TerminalNode* Python3Parser::ExprContext::IDIV() {
  return getToken(Python3Parser::IDIV, 0);
}

tree::TerminalNode* Python3Parser::ExprContext::LEFT_SHIFT() {
  return getToken(Python3Parser::LEFT_SHIFT, 0);
}

tree::TerminalNode* Python3Parser::ExprContext::RIGHT_SHIFT() {
  return getToken(Python3Parser::RIGHT_SHIFT, 0);
}

tree::TerminalNode* Python3Parser::ExprContext::AND_OP() {
  return getToken(Python3Parser::AND_OP, 0);
}

tree::TerminalNode* Python3Parser::ExprContext::XOR() {
  return getToken(Python3Parser::XOR, 0);
}

tree::TerminalNode* Python3Parser::ExprContext::OR_OP() {
  return getToken(Python3Parser::OR_OP, 0);
}


size_t Python3Parser::ExprContext::getRuleIndex() const {
  return Python3Parser::RuleExpr;
}

void Python3Parser::ExprContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<Python3ParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterExpr(this);
}

void Python3Parser::ExprContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<Python3ParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitExpr(this);
}


antlrcpp::Any Python3Parser::ExprContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<Python3ParserVisitor*>(visitor))
    return parserVisitor->visitExpr(this);
  else
    return visitor->visitChildren(this);
}


Python3Parser::ExprContext* Python3Parser::expr() {
   return expr(0);
}

Python3Parser::ExprContext* Python3Parser::expr(int precedence) {
  ParserRuleContext *parentContext = _ctx;
  size_t parentState = getState();
  Python3Parser::ExprContext *_localctx = _tracker.createInstance<ExprContext>(_ctx, parentState);
  Python3Parser::ExprContext *previousContext = _localctx;
  (void)previousContext; // Silence compiler, in case the context is not used by generated code.
  size_t startState = 194;
  enterRecursionRule(_localctx, 194, Python3Parser::RuleExpr, precedence);

    size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    unrollRecursionContexts(parentContext);
  });
  try {
    size_t alt;
    enterOuterAlt(_localctx, 1);
    setState(1154);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case Python3Parser::STRING:
      case Python3Parser::NUMBER:
      case Python3Parser::AWAIT:
      case Python3Parser::FALSE:
      case Python3Parser::MATCH:
      case Python3Parser::NONE:
      case Python3Parser::TRUE:
      case Python3Parser::UNDERSCORE:
      case Python3Parser::NAME:
      case Python3Parser::ELLIPSIS:
      case Python3Parser::OPEN_PAREN:
      case Python3Parser::OPEN_BRACK:
      case Python3Parser::OPEN_BRACE: {
        setState(1147);
        atom_expr();
        break;
      }

      case Python3Parser::ADD:
      case Python3Parser::MINUS:
      case Python3Parser::NOT_OP: {
        setState(1149); 
        _errHandler->sync(this);
        alt = 1;
        do {
          switch (alt) {
            case 1: {
                  setState(1148);
                  _la = _input->LA(1);
                  if (!(((((_la - 71) & ~ 0x3fULL) == 0) &&
                    ((1ULL << (_la - 71)) & ((1ULL << (Python3Parser::ADD - 71))
                    | (1ULL << (Python3Parser::MINUS - 71))
                    | (1ULL << (Python3Parser::NOT_OP - 71)))) != 0))) {
                  _errHandler->recoverInline(this);
                  }
                  else {
                    _errHandler->reportMatch(this);
                    consume();
                  }
                  break;
                }

          default:
            throw NoViableAltException(this);
          }
          setState(1151); 
          _errHandler->sync(this);
          alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 146, _ctx);
        } while (alt != 2 && alt != atn::ATN::INVALID_ALT_NUMBER);
        setState(1153);
        expr(7);
        break;
      }

    default:
      throw NoViableAltException(this);
    }
    _ctx->stop = _input->LT(-1);
    setState(1179);
    _errHandler->sync(this);
    alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 149, _ctx);
    while (alt != 2 && alt != atn::ATN::INVALID_ALT_NUMBER) {
      if (alt == 1) {
        if (!_parseListeners.empty())
          triggerExitRuleEvent();
        previousContext = _localctx;
        setState(1177);
        _errHandler->sync(this);
        switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 148, _ctx)) {
        case 1: {
          _localctx = _tracker.createInstance<ExprContext>(parentContext, parentState);
          pushNewRecursionContext(_localctx, startState, RuleExpr);
          setState(1156);

          if (!(precpred(_ctx, 8))) throw FailedPredicateException(this, "precpred(_ctx, 8)");
          setState(1157);
          match(Python3Parser::POWER);
          setState(1158);
          expr(9);
          break;
        }

        case 2: {
          _localctx = _tracker.createInstance<ExprContext>(parentContext, parentState);
          pushNewRecursionContext(_localctx, startState, RuleExpr);
          setState(1159);

          if (!(precpred(_ctx, 6))) throw FailedPredicateException(this, "precpred(_ctx, 6)");
          setState(1160);
          _la = _input->LA(1);
          if (!(((((_la - 56) & ~ 0x3fULL) == 0) &&
            ((1ULL << (_la - 56)) & ((1ULL << (Python3Parser::STAR - 56))
            | (1ULL << (Python3Parser::DIV - 56))
            | (1ULL << (Python3Parser::MOD - 56))
            | (1ULL << (Python3Parser::IDIV - 56))
            | (1ULL << (Python3Parser::AT - 56)))) != 0))) {
          _errHandler->recoverInline(this);
          }
          else {
            _errHandler->reportMatch(this);
            consume();
          }
          setState(1161);
          expr(7);
          break;
        }

        case 3: {
          _localctx = _tracker.createInstance<ExprContext>(parentContext, parentState);
          pushNewRecursionContext(_localctx, startState, RuleExpr);
          setState(1162);

          if (!(precpred(_ctx, 5))) throw FailedPredicateException(this, "precpred(_ctx, 5)");
          setState(1163);
          _la = _input->LA(1);
          if (!(_la == Python3Parser::ADD

          || _la == Python3Parser::MINUS)) {
          _errHandler->recoverInline(this);
          }
          else {
            _errHandler->reportMatch(this);
            consume();
          }
          setState(1164);
          expr(6);
          break;
        }

        case 4: {
          _localctx = _tracker.createInstance<ExprContext>(parentContext, parentState);
          pushNewRecursionContext(_localctx, startState, RuleExpr);
          setState(1165);

          if (!(precpred(_ctx, 4))) throw FailedPredicateException(this, "precpred(_ctx, 4)");
          setState(1166);
          _la = _input->LA(1);
          if (!(_la == Python3Parser::LEFT_SHIFT

          || _la == Python3Parser::RIGHT_SHIFT)) {
          _errHandler->recoverInline(this);
          }
          else {
            _errHandler->reportMatch(this);
            consume();
          }
          setState(1167);
          expr(5);
          break;
        }

        case 5: {
          _localctx = _tracker.createInstance<ExprContext>(parentContext, parentState);
          pushNewRecursionContext(_localctx, startState, RuleExpr);
          setState(1168);

          if (!(precpred(_ctx, 3))) throw FailedPredicateException(this, "precpred(_ctx, 3)");
          setState(1169);
          match(Python3Parser::AND_OP);
          setState(1170);
          expr(4);
          break;
        }

        case 6: {
          _localctx = _tracker.createInstance<ExprContext>(parentContext, parentState);
          pushNewRecursionContext(_localctx, startState, RuleExpr);
          setState(1171);

          if (!(precpred(_ctx, 2))) throw FailedPredicateException(this, "precpred(_ctx, 2)");
          setState(1172);
          match(Python3Parser::XOR);
          setState(1173);
          expr(3);
          break;
        }

        case 7: {
          _localctx = _tracker.createInstance<ExprContext>(parentContext, parentState);
          pushNewRecursionContext(_localctx, startState, RuleExpr);
          setState(1174);

          if (!(precpred(_ctx, 1))) throw FailedPredicateException(this, "precpred(_ctx, 1)");
          setState(1175);
          match(Python3Parser::OR_OP);
          setState(1176);
          expr(2);
          break;
        }

        default:
          break;
        } 
      }
      setState(1181);
      _errHandler->sync(this);
      alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 149, _ctx);
    }
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }
  return _localctx;
}

//----------------- Atom_exprContext ------------------------------------------------------------------

Python3Parser::Atom_exprContext::Atom_exprContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

Python3Parser::AtomContext* Python3Parser::Atom_exprContext::atom() {
  return getRuleContext<Python3Parser::AtomContext>(0);
}

tree::TerminalNode* Python3Parser::Atom_exprContext::AWAIT() {
  return getToken(Python3Parser::AWAIT, 0);
}

std::vector<Python3Parser::TrailerContext *> Python3Parser::Atom_exprContext::trailer() {
  return getRuleContexts<Python3Parser::TrailerContext>();
}

Python3Parser::TrailerContext* Python3Parser::Atom_exprContext::trailer(size_t i) {
  return getRuleContext<Python3Parser::TrailerContext>(i);
}


size_t Python3Parser::Atom_exprContext::getRuleIndex() const {
  return Python3Parser::RuleAtom_expr;
}

void Python3Parser::Atom_exprContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<Python3ParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterAtom_expr(this);
}

void Python3Parser::Atom_exprContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<Python3ParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitAtom_expr(this);
}


antlrcpp::Any Python3Parser::Atom_exprContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<Python3ParserVisitor*>(visitor))
    return parserVisitor->visitAtom_expr(this);
  else
    return visitor->visitChildren(this);
}

Python3Parser::Atom_exprContext* Python3Parser::atom_expr() {
  Atom_exprContext *_localctx = _tracker.createInstance<Atom_exprContext>(_ctx, getState());
  enterRule(_localctx, 196, Python3Parser::RuleAtom_expr);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    size_t alt;
    enterOuterAlt(_localctx, 1);
    setState(1183);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == Python3Parser::AWAIT) {
      setState(1182);
      match(Python3Parser::AWAIT);
    }
    setState(1185);
    atom();
    setState(1189);
    _errHandler->sync(this);
    alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 151, _ctx);
    while (alt != 2 && alt != atn::ATN::INVALID_ALT_NUMBER) {
      if (alt == 1) {
        setState(1186);
        trailer(); 
      }
      setState(1191);
      _errHandler->sync(this);
      alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 151, _ctx);
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- AtomContext ------------------------------------------------------------------

Python3Parser::AtomContext::AtomContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* Python3Parser::AtomContext::OPEN_PAREN() {
  return getToken(Python3Parser::OPEN_PAREN, 0);
}

tree::TerminalNode* Python3Parser::AtomContext::CLOSE_PAREN() {
  return getToken(Python3Parser::CLOSE_PAREN, 0);
}

Python3Parser::Yield_exprContext* Python3Parser::AtomContext::yield_expr() {
  return getRuleContext<Python3Parser::Yield_exprContext>(0);
}

Python3Parser::Testlist_compContext* Python3Parser::AtomContext::testlist_comp() {
  return getRuleContext<Python3Parser::Testlist_compContext>(0);
}

tree::TerminalNode* Python3Parser::AtomContext::OPEN_BRACK() {
  return getToken(Python3Parser::OPEN_BRACK, 0);
}

tree::TerminalNode* Python3Parser::AtomContext::CLOSE_BRACK() {
  return getToken(Python3Parser::CLOSE_BRACK, 0);
}

tree::TerminalNode* Python3Parser::AtomContext::OPEN_BRACE() {
  return getToken(Python3Parser::OPEN_BRACE, 0);
}

tree::TerminalNode* Python3Parser::AtomContext::CLOSE_BRACE() {
  return getToken(Python3Parser::CLOSE_BRACE, 0);
}

Python3Parser::DictorsetmakerContext* Python3Parser::AtomContext::dictorsetmaker() {
  return getRuleContext<Python3Parser::DictorsetmakerContext>(0);
}

Python3Parser::NameContext* Python3Parser::AtomContext::name() {
  return getRuleContext<Python3Parser::NameContext>(0);
}

tree::TerminalNode* Python3Parser::AtomContext::NUMBER() {
  return getToken(Python3Parser::NUMBER, 0);
}

std::vector<tree::TerminalNode *> Python3Parser::AtomContext::STRING() {
  return getTokens(Python3Parser::STRING);
}

tree::TerminalNode* Python3Parser::AtomContext::STRING(size_t i) {
  return getToken(Python3Parser::STRING, i);
}

tree::TerminalNode* Python3Parser::AtomContext::ELLIPSIS() {
  return getToken(Python3Parser::ELLIPSIS, 0);
}

tree::TerminalNode* Python3Parser::AtomContext::NONE() {
  return getToken(Python3Parser::NONE, 0);
}

tree::TerminalNode* Python3Parser::AtomContext::TRUE() {
  return getToken(Python3Parser::TRUE, 0);
}

tree::TerminalNode* Python3Parser::AtomContext::FALSE() {
  return getToken(Python3Parser::FALSE, 0);
}


size_t Python3Parser::AtomContext::getRuleIndex() const {
  return Python3Parser::RuleAtom;
}

void Python3Parser::AtomContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<Python3ParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterAtom(this);
}

void Python3Parser::AtomContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<Python3ParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitAtom(this);
}


antlrcpp::Any Python3Parser::AtomContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<Python3ParserVisitor*>(visitor))
    return parserVisitor->visitAtom(this);
  else
    return visitor->visitChildren(this);
}

Python3Parser::AtomContext* Python3Parser::atom() {
  AtomContext *_localctx = _tracker.createInstance<AtomContext>(_ctx, getState());
  enterRule(_localctx, 198, Python3Parser::RuleAtom);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    size_t alt;
    setState(1219);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case Python3Parser::OPEN_PAREN: {
        enterOuterAlt(_localctx, 1);
        setState(1192);
        match(Python3Parser::OPEN_PAREN);
        setState(1195);
        _errHandler->sync(this);
        switch (_input->LA(1)) {
          case Python3Parser::YIELD: {
            setState(1193);
            yield_expr();
            break;
          }

          case Python3Parser::STRING:
          case Python3Parser::NUMBER:
          case Python3Parser::AWAIT:
          case Python3Parser::FALSE:
          case Python3Parser::LAMBDA:
          case Python3Parser::MATCH:
          case Python3Parser::NONE:
          case Python3Parser::NOT:
          case Python3Parser::TRUE:
          case Python3Parser::UNDERSCORE:
          case Python3Parser::NAME:
          case Python3Parser::ELLIPSIS:
          case Python3Parser::STAR:
          case Python3Parser::OPEN_PAREN:
          case Python3Parser::OPEN_BRACK:
          case Python3Parser::ADD:
          case Python3Parser::MINUS:
          case Python3Parser::NOT_OP:
          case Python3Parser::OPEN_BRACE: {
            setState(1194);
            testlist_comp();
            break;
          }

          case Python3Parser::CLOSE_PAREN: {
            break;
          }

        default:
          break;
        }
        setState(1197);
        match(Python3Parser::CLOSE_PAREN);
        break;
      }

      case Python3Parser::OPEN_BRACK: {
        enterOuterAlt(_localctx, 2);
        setState(1198);
        match(Python3Parser::OPEN_BRACK);
        setState(1200);
        _errHandler->sync(this);

        _la = _input->LA(1);
        if ((((_la & ~ 0x3fULL) == 0) &&
          ((1ULL << _la) & ((1ULL << Python3Parser::STRING)
          | (1ULL << Python3Parser::NUMBER)
          | (1ULL << Python3Parser::AWAIT)
          | (1ULL << Python3Parser::FALSE)
          | (1ULL << Python3Parser::LAMBDA)
          | (1ULL << Python3Parser::MATCH)
          | (1ULL << Python3Parser::NONE)
          | (1ULL << Python3Parser::NOT)
          | (1ULL << Python3Parser::TRUE)
          | (1ULL << Python3Parser::UNDERSCORE)
          | (1ULL << Python3Parser::NAME)
          | (1ULL << Python3Parser::ELLIPSIS)
          | (1ULL << Python3Parser::STAR)
          | (1ULL << Python3Parser::OPEN_PAREN))) != 0) || ((((_la - 64) & ~ 0x3fULL) == 0) &&
          ((1ULL << (_la - 64)) & ((1ULL << (Python3Parser::OPEN_BRACK - 64))
          | (1ULL << (Python3Parser::ADD - 64))
          | (1ULL << (Python3Parser::MINUS - 64))
          | (1ULL << (Python3Parser::NOT_OP - 64))
          | (1ULL << (Python3Parser::OPEN_BRACE - 64)))) != 0)) {
          setState(1199);
          testlist_comp();
        }
        setState(1202);
        match(Python3Parser::CLOSE_BRACK);
        break;
      }

      case Python3Parser::OPEN_BRACE: {
        enterOuterAlt(_localctx, 3);
        setState(1203);
        match(Python3Parser::OPEN_BRACE);
        setState(1205);
        _errHandler->sync(this);

        _la = _input->LA(1);
        if ((((_la & ~ 0x3fULL) == 0) &&
          ((1ULL << _la) & ((1ULL << Python3Parser::STRING)
          | (1ULL << Python3Parser::NUMBER)
          | (1ULL << Python3Parser::AWAIT)
          | (1ULL << Python3Parser::FALSE)
          | (1ULL << Python3Parser::LAMBDA)
          | (1ULL << Python3Parser::MATCH)
          | (1ULL << Python3Parser::NONE)
          | (1ULL << Python3Parser::NOT)
          | (1ULL << Python3Parser::TRUE)
          | (1ULL << Python3Parser::UNDERSCORE)
          | (1ULL << Python3Parser::NAME)
          | (1ULL << Python3Parser::ELLIPSIS)
          | (1ULL << Python3Parser::STAR)
          | (1ULL << Python3Parser::OPEN_PAREN)
          | (1ULL << Python3Parser::POWER))) != 0) || ((((_la - 64) & ~ 0x3fULL) == 0) &&
          ((1ULL << (_la - 64)) & ((1ULL << (Python3Parser::OPEN_BRACK - 64))
          | (1ULL << (Python3Parser::ADD - 64))
          | (1ULL << (Python3Parser::MINUS - 64))
          | (1ULL << (Python3Parser::NOT_OP - 64))
          | (1ULL << (Python3Parser::OPEN_BRACE - 64)))) != 0)) {
          setState(1204);
          dictorsetmaker();
        }
        setState(1207);
        match(Python3Parser::CLOSE_BRACE);
        break;
      }

      case Python3Parser::MATCH:
      case Python3Parser::UNDERSCORE:
      case Python3Parser::NAME: {
        enterOuterAlt(_localctx, 4);
        setState(1208);
        name();
        break;
      }

      case Python3Parser::NUMBER: {
        enterOuterAlt(_localctx, 5);
        setState(1209);
        match(Python3Parser::NUMBER);
        break;
      }

      case Python3Parser::STRING: {
        enterOuterAlt(_localctx, 6);
        setState(1211); 
        _errHandler->sync(this);
        alt = 1;
        do {
          switch (alt) {
            case 1: {
                  setState(1210);
                  match(Python3Parser::STRING);
                  break;
                }

          default:
            throw NoViableAltException(this);
          }
          setState(1213); 
          _errHandler->sync(this);
          alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 155, _ctx);
        } while (alt != 2 && alt != atn::ATN::INVALID_ALT_NUMBER);
        break;
      }

      case Python3Parser::ELLIPSIS: {
        enterOuterAlt(_localctx, 7);
        setState(1215);
        match(Python3Parser::ELLIPSIS);
        break;
      }

      case Python3Parser::NONE: {
        enterOuterAlt(_localctx, 8);
        setState(1216);
        match(Python3Parser::NONE);
        break;
      }

      case Python3Parser::TRUE: {
        enterOuterAlt(_localctx, 9);
        setState(1217);
        match(Python3Parser::TRUE);
        break;
      }

      case Python3Parser::FALSE: {
        enterOuterAlt(_localctx, 10);
        setState(1218);
        match(Python3Parser::FALSE);
        break;
      }

    default:
      throw NoViableAltException(this);
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- NameContext ------------------------------------------------------------------

Python3Parser::NameContext::NameContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* Python3Parser::NameContext::NAME() {
  return getToken(Python3Parser::NAME, 0);
}

tree::TerminalNode* Python3Parser::NameContext::UNDERSCORE() {
  return getToken(Python3Parser::UNDERSCORE, 0);
}

tree::TerminalNode* Python3Parser::NameContext::MATCH() {
  return getToken(Python3Parser::MATCH, 0);
}


size_t Python3Parser::NameContext::getRuleIndex() const {
  return Python3Parser::RuleName;
}

void Python3Parser::NameContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<Python3ParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterName(this);
}

void Python3Parser::NameContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<Python3ParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitName(this);
}


antlrcpp::Any Python3Parser::NameContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<Python3ParserVisitor*>(visitor))
    return parserVisitor->visitName(this);
  else
    return visitor->visitChildren(this);
}

Python3Parser::NameContext* Python3Parser::name() {
  NameContext *_localctx = _tracker.createInstance<NameContext>(_ctx, getState());
  enterRule(_localctx, 200, Python3Parser::RuleName);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(1221);
    _la = _input->LA(1);
    if (!((((_la & ~ 0x3fULL) == 0) &&
      ((1ULL << _la) & ((1ULL << Python3Parser::MATCH)
      | (1ULL << Python3Parser::UNDERSCORE)
      | (1ULL << Python3Parser::NAME))) != 0))) {
    _errHandler->recoverInline(this);
    }
    else {
      _errHandler->reportMatch(this);
      consume();
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- Testlist_compContext ------------------------------------------------------------------

Python3Parser::Testlist_compContext::Testlist_compContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

std::vector<Python3Parser::TestContext *> Python3Parser::Testlist_compContext::test() {
  return getRuleContexts<Python3Parser::TestContext>();
}

Python3Parser::TestContext* Python3Parser::Testlist_compContext::test(size_t i) {
  return getRuleContext<Python3Parser::TestContext>(i);
}

std::vector<Python3Parser::Star_exprContext *> Python3Parser::Testlist_compContext::star_expr() {
  return getRuleContexts<Python3Parser::Star_exprContext>();
}

Python3Parser::Star_exprContext* Python3Parser::Testlist_compContext::star_expr(size_t i) {
  return getRuleContext<Python3Parser::Star_exprContext>(i);
}

Python3Parser::Comp_forContext* Python3Parser::Testlist_compContext::comp_for() {
  return getRuleContext<Python3Parser::Comp_forContext>(0);
}

std::vector<tree::TerminalNode *> Python3Parser::Testlist_compContext::COMMA() {
  return getTokens(Python3Parser::COMMA);
}

tree::TerminalNode* Python3Parser::Testlist_compContext::COMMA(size_t i) {
  return getToken(Python3Parser::COMMA, i);
}


size_t Python3Parser::Testlist_compContext::getRuleIndex() const {
  return Python3Parser::RuleTestlist_comp;
}

void Python3Parser::Testlist_compContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<Python3ParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterTestlist_comp(this);
}

void Python3Parser::Testlist_compContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<Python3ParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitTestlist_comp(this);
}


antlrcpp::Any Python3Parser::Testlist_compContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<Python3ParserVisitor*>(visitor))
    return parserVisitor->visitTestlist_comp(this);
  else
    return visitor->visitChildren(this);
}

Python3Parser::Testlist_compContext* Python3Parser::testlist_comp() {
  Testlist_compContext *_localctx = _tracker.createInstance<Testlist_compContext>(_ctx, getState());
  enterRule(_localctx, 202, Python3Parser::RuleTestlist_comp);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    size_t alt;
    enterOuterAlt(_localctx, 1);
    setState(1225);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case Python3Parser::STRING:
      case Python3Parser::NUMBER:
      case Python3Parser::AWAIT:
      case Python3Parser::FALSE:
      case Python3Parser::LAMBDA:
      case Python3Parser::MATCH:
      case Python3Parser::NONE:
      case Python3Parser::NOT:
      case Python3Parser::TRUE:
      case Python3Parser::UNDERSCORE:
      case Python3Parser::NAME:
      case Python3Parser::ELLIPSIS:
      case Python3Parser::OPEN_PAREN:
      case Python3Parser::OPEN_BRACK:
      case Python3Parser::ADD:
      case Python3Parser::MINUS:
      case Python3Parser::NOT_OP:
      case Python3Parser::OPEN_BRACE: {
        setState(1223);
        test();
        break;
      }

      case Python3Parser::STAR: {
        setState(1224);
        star_expr();
        break;
      }

    default:
      throw NoViableAltException(this);
    }
    setState(1241);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case Python3Parser::ASYNC:
      case Python3Parser::FOR: {
        setState(1227);
        comp_for();
        break;
      }

      case Python3Parser::CLOSE_PAREN:
      case Python3Parser::COMMA:
      case Python3Parser::CLOSE_BRACK: {
        setState(1235);
        _errHandler->sync(this);
        alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 159, _ctx);
        while (alt != 2 && alt != atn::ATN::INVALID_ALT_NUMBER) {
          if (alt == 1) {
            setState(1228);
            match(Python3Parser::COMMA);
            setState(1231);
            _errHandler->sync(this);
            switch (_input->LA(1)) {
              case Python3Parser::STRING:
              case Python3Parser::NUMBER:
              case Python3Parser::AWAIT:
              case Python3Parser::FALSE:
              case Python3Parser::LAMBDA:
              case Python3Parser::MATCH:
              case Python3Parser::NONE:
              case Python3Parser::NOT:
              case Python3Parser::TRUE:
              case Python3Parser::UNDERSCORE:
              case Python3Parser::NAME:
              case Python3Parser::ELLIPSIS:
              case Python3Parser::OPEN_PAREN:
              case Python3Parser::OPEN_BRACK:
              case Python3Parser::ADD:
              case Python3Parser::MINUS:
              case Python3Parser::NOT_OP:
              case Python3Parser::OPEN_BRACE: {
                setState(1229);
                test();
                break;
              }

              case Python3Parser::STAR: {
                setState(1230);
                star_expr();
                break;
              }

            default:
              throw NoViableAltException(this);
            } 
          }
          setState(1237);
          _errHandler->sync(this);
          alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 159, _ctx);
        }
        setState(1239);
        _errHandler->sync(this);

        _la = _input->LA(1);
        if (_la == Python3Parser::COMMA) {
          setState(1238);
          match(Python3Parser::COMMA);
        }
        break;
      }

    default:
      throw NoViableAltException(this);
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- TrailerContext ------------------------------------------------------------------

Python3Parser::TrailerContext::TrailerContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* Python3Parser::TrailerContext::OPEN_PAREN() {
  return getToken(Python3Parser::OPEN_PAREN, 0);
}

tree::TerminalNode* Python3Parser::TrailerContext::CLOSE_PAREN() {
  return getToken(Python3Parser::CLOSE_PAREN, 0);
}

Python3Parser::ArglistContext* Python3Parser::TrailerContext::arglist() {
  return getRuleContext<Python3Parser::ArglistContext>(0);
}

tree::TerminalNode* Python3Parser::TrailerContext::OPEN_BRACK() {
  return getToken(Python3Parser::OPEN_BRACK, 0);
}

Python3Parser::SubscriptlistContext* Python3Parser::TrailerContext::subscriptlist() {
  return getRuleContext<Python3Parser::SubscriptlistContext>(0);
}

tree::TerminalNode* Python3Parser::TrailerContext::CLOSE_BRACK() {
  return getToken(Python3Parser::CLOSE_BRACK, 0);
}

tree::TerminalNode* Python3Parser::TrailerContext::DOT() {
  return getToken(Python3Parser::DOT, 0);
}

Python3Parser::NameContext* Python3Parser::TrailerContext::name() {
  return getRuleContext<Python3Parser::NameContext>(0);
}


size_t Python3Parser::TrailerContext::getRuleIndex() const {
  return Python3Parser::RuleTrailer;
}

void Python3Parser::TrailerContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<Python3ParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterTrailer(this);
}

void Python3Parser::TrailerContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<Python3ParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitTrailer(this);
}


antlrcpp::Any Python3Parser::TrailerContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<Python3ParserVisitor*>(visitor))
    return parserVisitor->visitTrailer(this);
  else
    return visitor->visitChildren(this);
}

Python3Parser::TrailerContext* Python3Parser::trailer() {
  TrailerContext *_localctx = _tracker.createInstance<TrailerContext>(_ctx, getState());
  enterRule(_localctx, 204, Python3Parser::RuleTrailer);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    setState(1254);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case Python3Parser::OPEN_PAREN: {
        enterOuterAlt(_localctx, 1);
        setState(1243);
        match(Python3Parser::OPEN_PAREN);
        setState(1245);
        _errHandler->sync(this);

        _la = _input->LA(1);
        if ((((_la & ~ 0x3fULL) == 0) &&
          ((1ULL << _la) & ((1ULL << Python3Parser::STRING)
          | (1ULL << Python3Parser::NUMBER)
          | (1ULL << Python3Parser::AWAIT)
          | (1ULL << Python3Parser::FALSE)
          | (1ULL << Python3Parser::LAMBDA)
          | (1ULL << Python3Parser::MATCH)
          | (1ULL << Python3Parser::NONE)
          | (1ULL << Python3Parser::NOT)
          | (1ULL << Python3Parser::TRUE)
          | (1ULL << Python3Parser::UNDERSCORE)
          | (1ULL << Python3Parser::NAME)
          | (1ULL << Python3Parser::ELLIPSIS)
          | (1ULL << Python3Parser::STAR)
          | (1ULL << Python3Parser::OPEN_PAREN)
          | (1ULL << Python3Parser::POWER))) != 0) || ((((_la - 64) & ~ 0x3fULL) == 0) &&
          ((1ULL << (_la - 64)) & ((1ULL << (Python3Parser::OPEN_BRACK - 64))
          | (1ULL << (Python3Parser::ADD - 64))
          | (1ULL << (Python3Parser::MINUS - 64))
          | (1ULL << (Python3Parser::NOT_OP - 64))
          | (1ULL << (Python3Parser::OPEN_BRACE - 64)))) != 0)) {
          setState(1244);
          arglist();
        }
        setState(1247);
        match(Python3Parser::CLOSE_PAREN);
        break;
      }

      case Python3Parser::OPEN_BRACK: {
        enterOuterAlt(_localctx, 2);
        setState(1248);
        match(Python3Parser::OPEN_BRACK);
        setState(1249);
        subscriptlist();
        setState(1250);
        match(Python3Parser::CLOSE_BRACK);
        break;
      }

      case Python3Parser::DOT: {
        enterOuterAlt(_localctx, 3);
        setState(1252);
        match(Python3Parser::DOT);
        setState(1253);
        name();
        break;
      }

    default:
      throw NoViableAltException(this);
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- SubscriptlistContext ------------------------------------------------------------------

Python3Parser::SubscriptlistContext::SubscriptlistContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

std::vector<Python3Parser::Subscript_Context *> Python3Parser::SubscriptlistContext::subscript_() {
  return getRuleContexts<Python3Parser::Subscript_Context>();
}

Python3Parser::Subscript_Context* Python3Parser::SubscriptlistContext::subscript_(size_t i) {
  return getRuleContext<Python3Parser::Subscript_Context>(i);
}

std::vector<tree::TerminalNode *> Python3Parser::SubscriptlistContext::COMMA() {
  return getTokens(Python3Parser::COMMA);
}

tree::TerminalNode* Python3Parser::SubscriptlistContext::COMMA(size_t i) {
  return getToken(Python3Parser::COMMA, i);
}


size_t Python3Parser::SubscriptlistContext::getRuleIndex() const {
  return Python3Parser::RuleSubscriptlist;
}

void Python3Parser::SubscriptlistContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<Python3ParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterSubscriptlist(this);
}

void Python3Parser::SubscriptlistContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<Python3ParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitSubscriptlist(this);
}


antlrcpp::Any Python3Parser::SubscriptlistContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<Python3ParserVisitor*>(visitor))
    return parserVisitor->visitSubscriptlist(this);
  else
    return visitor->visitChildren(this);
}

Python3Parser::SubscriptlistContext* Python3Parser::subscriptlist() {
  SubscriptlistContext *_localctx = _tracker.createInstance<SubscriptlistContext>(_ctx, getState());
  enterRule(_localctx, 206, Python3Parser::RuleSubscriptlist);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    size_t alt;
    enterOuterAlt(_localctx, 1);
    setState(1256);
    subscript_();
    setState(1261);
    _errHandler->sync(this);
    alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 164, _ctx);
    while (alt != 2 && alt != atn::ATN::INVALID_ALT_NUMBER) {
      if (alt == 1) {
        setState(1257);
        match(Python3Parser::COMMA);
        setState(1258);
        subscript_(); 
      }
      setState(1263);
      _errHandler->sync(this);
      alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 164, _ctx);
    }
    setState(1265);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == Python3Parser::COMMA) {
      setState(1264);
      match(Python3Parser::COMMA);
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- Subscript_Context ------------------------------------------------------------------

Python3Parser::Subscript_Context::Subscript_Context(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

std::vector<Python3Parser::TestContext *> Python3Parser::Subscript_Context::test() {
  return getRuleContexts<Python3Parser::TestContext>();
}

Python3Parser::TestContext* Python3Parser::Subscript_Context::test(size_t i) {
  return getRuleContext<Python3Parser::TestContext>(i);
}

tree::TerminalNode* Python3Parser::Subscript_Context::COLON() {
  return getToken(Python3Parser::COLON, 0);
}

Python3Parser::SliceopContext* Python3Parser::Subscript_Context::sliceop() {
  return getRuleContext<Python3Parser::SliceopContext>(0);
}


size_t Python3Parser::Subscript_Context::getRuleIndex() const {
  return Python3Parser::RuleSubscript_;
}

void Python3Parser::Subscript_Context::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<Python3ParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterSubscript_(this);
}

void Python3Parser::Subscript_Context::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<Python3ParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitSubscript_(this);
}


antlrcpp::Any Python3Parser::Subscript_Context::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<Python3ParserVisitor*>(visitor))
    return parserVisitor->visitSubscript_(this);
  else
    return visitor->visitChildren(this);
}

Python3Parser::Subscript_Context* Python3Parser::subscript_() {
  Subscript_Context *_localctx = _tracker.createInstance<Subscript_Context>(_ctx, getState());
  enterRule(_localctx, 208, Python3Parser::RuleSubscript_);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    setState(1278);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 169, _ctx)) {
    case 1: {
      enterOuterAlt(_localctx, 1);
      setState(1267);
      test();
      break;
    }

    case 2: {
      enterOuterAlt(_localctx, 2);
      setState(1269);
      _errHandler->sync(this);

      _la = _input->LA(1);
      if ((((_la & ~ 0x3fULL) == 0) &&
        ((1ULL << _la) & ((1ULL << Python3Parser::STRING)
        | (1ULL << Python3Parser::NUMBER)
        | (1ULL << Python3Parser::AWAIT)
        | (1ULL << Python3Parser::FALSE)
        | (1ULL << Python3Parser::LAMBDA)
        | (1ULL << Python3Parser::MATCH)
        | (1ULL << Python3Parser::NONE)
        | (1ULL << Python3Parser::NOT)
        | (1ULL << Python3Parser::TRUE)
        | (1ULL << Python3Parser::UNDERSCORE)
        | (1ULL << Python3Parser::NAME)
        | (1ULL << Python3Parser::ELLIPSIS)
        | (1ULL << Python3Parser::OPEN_PAREN))) != 0) || ((((_la - 64) & ~ 0x3fULL) == 0) &&
        ((1ULL << (_la - 64)) & ((1ULL << (Python3Parser::OPEN_BRACK - 64))
        | (1ULL << (Python3Parser::ADD - 64))
        | (1ULL << (Python3Parser::MINUS - 64))
        | (1ULL << (Python3Parser::NOT_OP - 64))
        | (1ULL << (Python3Parser::OPEN_BRACE - 64)))) != 0)) {
        setState(1268);
        test();
      }
      setState(1271);
      match(Python3Parser::COLON);
      setState(1273);
      _errHandler->sync(this);

      _la = _input->LA(1);
      if ((((_la & ~ 0x3fULL) == 0) &&
        ((1ULL << _la) & ((1ULL << Python3Parser::STRING)
        | (1ULL << Python3Parser::NUMBER)
        | (1ULL << Python3Parser::AWAIT)
        | (1ULL << Python3Parser::FALSE)
        | (1ULL << Python3Parser::LAMBDA)
        | (1ULL << Python3Parser::MATCH)
        | (1ULL << Python3Parser::NONE)
        | (1ULL << Python3Parser::NOT)
        | (1ULL << Python3Parser::TRUE)
        | (1ULL << Python3Parser::UNDERSCORE)
        | (1ULL << Python3Parser::NAME)
        | (1ULL << Python3Parser::ELLIPSIS)
        | (1ULL << Python3Parser::OPEN_PAREN))) != 0) || ((((_la - 64) & ~ 0x3fULL) == 0) &&
        ((1ULL << (_la - 64)) & ((1ULL << (Python3Parser::OPEN_BRACK - 64))
        | (1ULL << (Python3Parser::ADD - 64))
        | (1ULL << (Python3Parser::MINUS - 64))
        | (1ULL << (Python3Parser::NOT_OP - 64))
        | (1ULL << (Python3Parser::OPEN_BRACE - 64)))) != 0)) {
        setState(1272);
        test();
      }
      setState(1276);
      _errHandler->sync(this);

      _la = _input->LA(1);
      if (_la == Python3Parser::COLON) {
        setState(1275);
        sliceop();
      }
      break;
    }

    default:
      break;
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- SliceopContext ------------------------------------------------------------------

Python3Parser::SliceopContext::SliceopContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* Python3Parser::SliceopContext::COLON() {
  return getToken(Python3Parser::COLON, 0);
}

Python3Parser::TestContext* Python3Parser::SliceopContext::test() {
  return getRuleContext<Python3Parser::TestContext>(0);
}


size_t Python3Parser::SliceopContext::getRuleIndex() const {
  return Python3Parser::RuleSliceop;
}

void Python3Parser::SliceopContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<Python3ParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterSliceop(this);
}

void Python3Parser::SliceopContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<Python3ParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitSliceop(this);
}


antlrcpp::Any Python3Parser::SliceopContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<Python3ParserVisitor*>(visitor))
    return parserVisitor->visitSliceop(this);
  else
    return visitor->visitChildren(this);
}

Python3Parser::SliceopContext* Python3Parser::sliceop() {
  SliceopContext *_localctx = _tracker.createInstance<SliceopContext>(_ctx, getState());
  enterRule(_localctx, 210, Python3Parser::RuleSliceop);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(1280);
    match(Python3Parser::COLON);
    setState(1282);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if ((((_la & ~ 0x3fULL) == 0) &&
      ((1ULL << _la) & ((1ULL << Python3Parser::STRING)
      | (1ULL << Python3Parser::NUMBER)
      | (1ULL << Python3Parser::AWAIT)
      | (1ULL << Python3Parser::FALSE)
      | (1ULL << Python3Parser::LAMBDA)
      | (1ULL << Python3Parser::MATCH)
      | (1ULL << Python3Parser::NONE)
      | (1ULL << Python3Parser::NOT)
      | (1ULL << Python3Parser::TRUE)
      | (1ULL << Python3Parser::UNDERSCORE)
      | (1ULL << Python3Parser::NAME)
      | (1ULL << Python3Parser::ELLIPSIS)
      | (1ULL << Python3Parser::OPEN_PAREN))) != 0) || ((((_la - 64) & ~ 0x3fULL) == 0) &&
      ((1ULL << (_la - 64)) & ((1ULL << (Python3Parser::OPEN_BRACK - 64))
      | (1ULL << (Python3Parser::ADD - 64))
      | (1ULL << (Python3Parser::MINUS - 64))
      | (1ULL << (Python3Parser::NOT_OP - 64))
      | (1ULL << (Python3Parser::OPEN_BRACE - 64)))) != 0)) {
      setState(1281);
      test();
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- ExprlistContext ------------------------------------------------------------------

Python3Parser::ExprlistContext::ExprlistContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

std::vector<Python3Parser::ExprContext *> Python3Parser::ExprlistContext::expr() {
  return getRuleContexts<Python3Parser::ExprContext>();
}

Python3Parser::ExprContext* Python3Parser::ExprlistContext::expr(size_t i) {
  return getRuleContext<Python3Parser::ExprContext>(i);
}

std::vector<Python3Parser::Star_exprContext *> Python3Parser::ExprlistContext::star_expr() {
  return getRuleContexts<Python3Parser::Star_exprContext>();
}

Python3Parser::Star_exprContext* Python3Parser::ExprlistContext::star_expr(size_t i) {
  return getRuleContext<Python3Parser::Star_exprContext>(i);
}

std::vector<tree::TerminalNode *> Python3Parser::ExprlistContext::COMMA() {
  return getTokens(Python3Parser::COMMA);
}

tree::TerminalNode* Python3Parser::ExprlistContext::COMMA(size_t i) {
  return getToken(Python3Parser::COMMA, i);
}


size_t Python3Parser::ExprlistContext::getRuleIndex() const {
  return Python3Parser::RuleExprlist;
}

void Python3Parser::ExprlistContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<Python3ParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterExprlist(this);
}

void Python3Parser::ExprlistContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<Python3ParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitExprlist(this);
}


antlrcpp::Any Python3Parser::ExprlistContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<Python3ParserVisitor*>(visitor))
    return parserVisitor->visitExprlist(this);
  else
    return visitor->visitChildren(this);
}

Python3Parser::ExprlistContext* Python3Parser::exprlist() {
  ExprlistContext *_localctx = _tracker.createInstance<ExprlistContext>(_ctx, getState());
  enterRule(_localctx, 212, Python3Parser::RuleExprlist);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    size_t alt;
    enterOuterAlt(_localctx, 1);
    setState(1286);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case Python3Parser::STRING:
      case Python3Parser::NUMBER:
      case Python3Parser::AWAIT:
      case Python3Parser::FALSE:
      case Python3Parser::MATCH:
      case Python3Parser::NONE:
      case Python3Parser::TRUE:
      case Python3Parser::UNDERSCORE:
      case Python3Parser::NAME:
      case Python3Parser::ELLIPSIS:
      case Python3Parser::OPEN_PAREN:
      case Python3Parser::OPEN_BRACK:
      case Python3Parser::ADD:
      case Python3Parser::MINUS:
      case Python3Parser::NOT_OP:
      case Python3Parser::OPEN_BRACE: {
        setState(1284);
        expr(0);
        break;
      }

      case Python3Parser::STAR: {
        setState(1285);
        star_expr();
        break;
      }

    default:
      throw NoViableAltException(this);
    }
    setState(1295);
    _errHandler->sync(this);
    alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 173, _ctx);
    while (alt != 2 && alt != atn::ATN::INVALID_ALT_NUMBER) {
      if (alt == 1) {
        setState(1288);
        match(Python3Parser::COMMA);
        setState(1291);
        _errHandler->sync(this);
        switch (_input->LA(1)) {
          case Python3Parser::STRING:
          case Python3Parser::NUMBER:
          case Python3Parser::AWAIT:
          case Python3Parser::FALSE:
          case Python3Parser::MATCH:
          case Python3Parser::NONE:
          case Python3Parser::TRUE:
          case Python3Parser::UNDERSCORE:
          case Python3Parser::NAME:
          case Python3Parser::ELLIPSIS:
          case Python3Parser::OPEN_PAREN:
          case Python3Parser::OPEN_BRACK:
          case Python3Parser::ADD:
          case Python3Parser::MINUS:
          case Python3Parser::NOT_OP:
          case Python3Parser::OPEN_BRACE: {
            setState(1289);
            expr(0);
            break;
          }

          case Python3Parser::STAR: {
            setState(1290);
            star_expr();
            break;
          }

        default:
          throw NoViableAltException(this);
        } 
      }
      setState(1297);
      _errHandler->sync(this);
      alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 173, _ctx);
    }
    setState(1299);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == Python3Parser::COMMA) {
      setState(1298);
      match(Python3Parser::COMMA);
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- TestlistContext ------------------------------------------------------------------

Python3Parser::TestlistContext::TestlistContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

std::vector<Python3Parser::TestContext *> Python3Parser::TestlistContext::test() {
  return getRuleContexts<Python3Parser::TestContext>();
}

Python3Parser::TestContext* Python3Parser::TestlistContext::test(size_t i) {
  return getRuleContext<Python3Parser::TestContext>(i);
}

std::vector<tree::TerminalNode *> Python3Parser::TestlistContext::COMMA() {
  return getTokens(Python3Parser::COMMA);
}

tree::TerminalNode* Python3Parser::TestlistContext::COMMA(size_t i) {
  return getToken(Python3Parser::COMMA, i);
}


size_t Python3Parser::TestlistContext::getRuleIndex() const {
  return Python3Parser::RuleTestlist;
}

void Python3Parser::TestlistContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<Python3ParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterTestlist(this);
}

void Python3Parser::TestlistContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<Python3ParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitTestlist(this);
}


antlrcpp::Any Python3Parser::TestlistContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<Python3ParserVisitor*>(visitor))
    return parserVisitor->visitTestlist(this);
  else
    return visitor->visitChildren(this);
}

Python3Parser::TestlistContext* Python3Parser::testlist() {
  TestlistContext *_localctx = _tracker.createInstance<TestlistContext>(_ctx, getState());
  enterRule(_localctx, 214, Python3Parser::RuleTestlist);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    size_t alt;
    enterOuterAlt(_localctx, 1);
    setState(1301);
    test();
    setState(1306);
    _errHandler->sync(this);
    alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 175, _ctx);
    while (alt != 2 && alt != atn::ATN::INVALID_ALT_NUMBER) {
      if (alt == 1) {
        setState(1302);
        match(Python3Parser::COMMA);
        setState(1303);
        test(); 
      }
      setState(1308);
      _errHandler->sync(this);
      alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 175, _ctx);
    }
    setState(1310);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == Python3Parser::COMMA) {
      setState(1309);
      match(Python3Parser::COMMA);
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- DictorsetmakerContext ------------------------------------------------------------------

Python3Parser::DictorsetmakerContext::DictorsetmakerContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

std::vector<Python3Parser::TestContext *> Python3Parser::DictorsetmakerContext::test() {
  return getRuleContexts<Python3Parser::TestContext>();
}

Python3Parser::TestContext* Python3Parser::DictorsetmakerContext::test(size_t i) {
  return getRuleContext<Python3Parser::TestContext>(i);
}

std::vector<tree::TerminalNode *> Python3Parser::DictorsetmakerContext::COLON() {
  return getTokens(Python3Parser::COLON);
}

tree::TerminalNode* Python3Parser::DictorsetmakerContext::COLON(size_t i) {
  return getToken(Python3Parser::COLON, i);
}

std::vector<tree::TerminalNode *> Python3Parser::DictorsetmakerContext::POWER() {
  return getTokens(Python3Parser::POWER);
}

tree::TerminalNode* Python3Parser::DictorsetmakerContext::POWER(size_t i) {
  return getToken(Python3Parser::POWER, i);
}

std::vector<Python3Parser::ExprContext *> Python3Parser::DictorsetmakerContext::expr() {
  return getRuleContexts<Python3Parser::ExprContext>();
}

Python3Parser::ExprContext* Python3Parser::DictorsetmakerContext::expr(size_t i) {
  return getRuleContext<Python3Parser::ExprContext>(i);
}

Python3Parser::Comp_forContext* Python3Parser::DictorsetmakerContext::comp_for() {
  return getRuleContext<Python3Parser::Comp_forContext>(0);
}

std::vector<Python3Parser::Star_exprContext *> Python3Parser::DictorsetmakerContext::star_expr() {
  return getRuleContexts<Python3Parser::Star_exprContext>();
}

Python3Parser::Star_exprContext* Python3Parser::DictorsetmakerContext::star_expr(size_t i) {
  return getRuleContext<Python3Parser::Star_exprContext>(i);
}

std::vector<tree::TerminalNode *> Python3Parser::DictorsetmakerContext::COMMA() {
  return getTokens(Python3Parser::COMMA);
}

tree::TerminalNode* Python3Parser::DictorsetmakerContext::COMMA(size_t i) {
  return getToken(Python3Parser::COMMA, i);
}


size_t Python3Parser::DictorsetmakerContext::getRuleIndex() const {
  return Python3Parser::RuleDictorsetmaker;
}

void Python3Parser::DictorsetmakerContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<Python3ParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterDictorsetmaker(this);
}

void Python3Parser::DictorsetmakerContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<Python3ParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitDictorsetmaker(this);
}


antlrcpp::Any Python3Parser::DictorsetmakerContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<Python3ParserVisitor*>(visitor))
    return parserVisitor->visitDictorsetmaker(this);
  else
    return visitor->visitChildren(this);
}

Python3Parser::DictorsetmakerContext* Python3Parser::dictorsetmaker() {
  DictorsetmakerContext *_localctx = _tracker.createInstance<DictorsetmakerContext>(_ctx, getState());
  enterRule(_localctx, 216, Python3Parser::RuleDictorsetmaker);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    size_t alt;
    enterOuterAlt(_localctx, 1);
    setState(1360);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 187, _ctx)) {
    case 1: {
      setState(1318);
      _errHandler->sync(this);
      switch (_input->LA(1)) {
        case Python3Parser::STRING:
        case Python3Parser::NUMBER:
        case Python3Parser::AWAIT:
        case Python3Parser::FALSE:
        case Python3Parser::LAMBDA:
        case Python3Parser::MATCH:
        case Python3Parser::NONE:
        case Python3Parser::NOT:
        case Python3Parser::TRUE:
        case Python3Parser::UNDERSCORE:
        case Python3Parser::NAME:
        case Python3Parser::ELLIPSIS:
        case Python3Parser::OPEN_PAREN:
        case Python3Parser::OPEN_BRACK:
        case Python3Parser::ADD:
        case Python3Parser::MINUS:
        case Python3Parser::NOT_OP:
        case Python3Parser::OPEN_BRACE: {
          setState(1312);
          test();
          setState(1313);
          match(Python3Parser::COLON);
          setState(1314);
          test();
          break;
        }

        case Python3Parser::POWER: {
          setState(1316);
          match(Python3Parser::POWER);
          setState(1317);
          expr(0);
          break;
        }

      default:
        throw NoViableAltException(this);
      }
      setState(1338);
      _errHandler->sync(this);
      switch (_input->LA(1)) {
        case Python3Parser::ASYNC:
        case Python3Parser::FOR: {
          setState(1320);
          comp_for();
          break;
        }

        case Python3Parser::COMMA:
        case Python3Parser::CLOSE_BRACE: {
          setState(1332);
          _errHandler->sync(this);
          alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 179, _ctx);
          while (alt != 2 && alt != atn::ATN::INVALID_ALT_NUMBER) {
            if (alt == 1) {
              setState(1321);
              match(Python3Parser::COMMA);
              setState(1328);
              _errHandler->sync(this);
              switch (_input->LA(1)) {
                case Python3Parser::STRING:
                case Python3Parser::NUMBER:
                case Python3Parser::AWAIT:
                case Python3Parser::FALSE:
                case Python3Parser::LAMBDA:
                case Python3Parser::MATCH:
                case Python3Parser::NONE:
                case Python3Parser::NOT:
                case Python3Parser::TRUE:
                case Python3Parser::UNDERSCORE:
                case Python3Parser::NAME:
                case Python3Parser::ELLIPSIS:
                case Python3Parser::OPEN_PAREN:
                case Python3Parser::OPEN_BRACK:
                case Python3Parser::ADD:
                case Python3Parser::MINUS:
                case Python3Parser::NOT_OP:
                case Python3Parser::OPEN_BRACE: {
                  setState(1322);
                  test();
                  setState(1323);
                  match(Python3Parser::COLON);
                  setState(1324);
                  test();
                  break;
                }

                case Python3Parser::POWER: {
                  setState(1326);
                  match(Python3Parser::POWER);
                  setState(1327);
                  expr(0);
                  break;
                }

              default:
                throw NoViableAltException(this);
              } 
            }
            setState(1334);
            _errHandler->sync(this);
            alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 179, _ctx);
          }
          setState(1336);
          _errHandler->sync(this);

          _la = _input->LA(1);
          if (_la == Python3Parser::COMMA) {
            setState(1335);
            match(Python3Parser::COMMA);
          }
          break;
        }

      default:
        throw NoViableAltException(this);
      }
      break;
    }

    case 2: {
      setState(1342);
      _errHandler->sync(this);
      switch (_input->LA(1)) {
        case Python3Parser::STRING:
        case Python3Parser::NUMBER:
        case Python3Parser::AWAIT:
        case Python3Parser::FALSE:
        case Python3Parser::LAMBDA:
        case Python3Parser::MATCH:
        case Python3Parser::NONE:
        case Python3Parser::NOT:
        case Python3Parser::TRUE:
        case Python3Parser::UNDERSCORE:
        case Python3Parser::NAME:
        case Python3Parser::ELLIPSIS:
        case Python3Parser::OPEN_PAREN:
        case Python3Parser::OPEN_BRACK:
        case Python3Parser::ADD:
        case Python3Parser::MINUS:
        case Python3Parser::NOT_OP:
        case Python3Parser::OPEN_BRACE: {
          setState(1340);
          test();
          break;
        }

        case Python3Parser::STAR: {
          setState(1341);
          star_expr();
          break;
        }

      default:
        throw NoViableAltException(this);
      }
      setState(1358);
      _errHandler->sync(this);
      switch (_input->LA(1)) {
        case Python3Parser::ASYNC:
        case Python3Parser::FOR: {
          setState(1344);
          comp_for();
          break;
        }

        case Python3Parser::COMMA:
        case Python3Parser::CLOSE_BRACE: {
          setState(1352);
          _errHandler->sync(this);
          alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 184, _ctx);
          while (alt != 2 && alt != atn::ATN::INVALID_ALT_NUMBER) {
            if (alt == 1) {
              setState(1345);
              match(Python3Parser::COMMA);
              setState(1348);
              _errHandler->sync(this);
              switch (_input->LA(1)) {
                case Python3Parser::STRING:
                case Python3Parser::NUMBER:
                case Python3Parser::AWAIT:
                case Python3Parser::FALSE:
                case Python3Parser::LAMBDA:
                case Python3Parser::MATCH:
                case Python3Parser::NONE:
                case Python3Parser::NOT:
                case Python3Parser::TRUE:
                case Python3Parser::UNDERSCORE:
                case Python3Parser::NAME:
                case Python3Parser::ELLIPSIS:
                case Python3Parser::OPEN_PAREN:
                case Python3Parser::OPEN_BRACK:
                case Python3Parser::ADD:
                case Python3Parser::MINUS:
                case Python3Parser::NOT_OP:
                case Python3Parser::OPEN_BRACE: {
                  setState(1346);
                  test();
                  break;
                }

                case Python3Parser::STAR: {
                  setState(1347);
                  star_expr();
                  break;
                }

              default:
                throw NoViableAltException(this);
              } 
            }
            setState(1354);
            _errHandler->sync(this);
            alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 184, _ctx);
          }
          setState(1356);
          _errHandler->sync(this);

          _la = _input->LA(1);
          if (_la == Python3Parser::COMMA) {
            setState(1355);
            match(Python3Parser::COMMA);
          }
          break;
        }

      default:
        throw NoViableAltException(this);
      }
      break;
    }

    default:
      break;
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- ClassdefContext ------------------------------------------------------------------

Python3Parser::ClassdefContext::ClassdefContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* Python3Parser::ClassdefContext::CLASS() {
  return getToken(Python3Parser::CLASS, 0);
}

Python3Parser::NameContext* Python3Parser::ClassdefContext::name() {
  return getRuleContext<Python3Parser::NameContext>(0);
}

tree::TerminalNode* Python3Parser::ClassdefContext::COLON() {
  return getToken(Python3Parser::COLON, 0);
}

Python3Parser::BlockContext* Python3Parser::ClassdefContext::block() {
  return getRuleContext<Python3Parser::BlockContext>(0);
}

tree::TerminalNode* Python3Parser::ClassdefContext::OPEN_PAREN() {
  return getToken(Python3Parser::OPEN_PAREN, 0);
}

tree::TerminalNode* Python3Parser::ClassdefContext::CLOSE_PAREN() {
  return getToken(Python3Parser::CLOSE_PAREN, 0);
}

Python3Parser::ArglistContext* Python3Parser::ClassdefContext::arglist() {
  return getRuleContext<Python3Parser::ArglistContext>(0);
}


size_t Python3Parser::ClassdefContext::getRuleIndex() const {
  return Python3Parser::RuleClassdef;
}

void Python3Parser::ClassdefContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<Python3ParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterClassdef(this);
}

void Python3Parser::ClassdefContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<Python3ParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitClassdef(this);
}


antlrcpp::Any Python3Parser::ClassdefContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<Python3ParserVisitor*>(visitor))
    return parserVisitor->visitClassdef(this);
  else
    return visitor->visitChildren(this);
}

Python3Parser::ClassdefContext* Python3Parser::classdef() {
  ClassdefContext *_localctx = _tracker.createInstance<ClassdefContext>(_ctx, getState());
  enterRule(_localctx, 218, Python3Parser::RuleClassdef);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(1362);
    match(Python3Parser::CLASS);
    setState(1363);
    name();
    setState(1369);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == Python3Parser::OPEN_PAREN) {
      setState(1364);
      match(Python3Parser::OPEN_PAREN);
      setState(1366);
      _errHandler->sync(this);

      _la = _input->LA(1);
      if ((((_la & ~ 0x3fULL) == 0) &&
        ((1ULL << _la) & ((1ULL << Python3Parser::STRING)
        | (1ULL << Python3Parser::NUMBER)
        | (1ULL << Python3Parser::AWAIT)
        | (1ULL << Python3Parser::FALSE)
        | (1ULL << Python3Parser::LAMBDA)
        | (1ULL << Python3Parser::MATCH)
        | (1ULL << Python3Parser::NONE)
        | (1ULL << Python3Parser::NOT)
        | (1ULL << Python3Parser::TRUE)
        | (1ULL << Python3Parser::UNDERSCORE)
        | (1ULL << Python3Parser::NAME)
        | (1ULL << Python3Parser::ELLIPSIS)
        | (1ULL << Python3Parser::STAR)
        | (1ULL << Python3Parser::OPEN_PAREN)
        | (1ULL << Python3Parser::POWER))) != 0) || ((((_la - 64) & ~ 0x3fULL) == 0) &&
        ((1ULL << (_la - 64)) & ((1ULL << (Python3Parser::OPEN_BRACK - 64))
        | (1ULL << (Python3Parser::ADD - 64))
        | (1ULL << (Python3Parser::MINUS - 64))
        | (1ULL << (Python3Parser::NOT_OP - 64))
        | (1ULL << (Python3Parser::OPEN_BRACE - 64)))) != 0)) {
        setState(1365);
        arglist();
      }
      setState(1368);
      match(Python3Parser::CLOSE_PAREN);
    }
    setState(1371);
    match(Python3Parser::COLON);
    setState(1372);
    block();
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- ArglistContext ------------------------------------------------------------------

Python3Parser::ArglistContext::ArglistContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

std::vector<Python3Parser::ArgumentContext *> Python3Parser::ArglistContext::argument() {
  return getRuleContexts<Python3Parser::ArgumentContext>();
}

Python3Parser::ArgumentContext* Python3Parser::ArglistContext::argument(size_t i) {
  return getRuleContext<Python3Parser::ArgumentContext>(i);
}

std::vector<tree::TerminalNode *> Python3Parser::ArglistContext::COMMA() {
  return getTokens(Python3Parser::COMMA);
}

tree::TerminalNode* Python3Parser::ArglistContext::COMMA(size_t i) {
  return getToken(Python3Parser::COMMA, i);
}


size_t Python3Parser::ArglistContext::getRuleIndex() const {
  return Python3Parser::RuleArglist;
}

void Python3Parser::ArglistContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<Python3ParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterArglist(this);
}

void Python3Parser::ArglistContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<Python3ParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitArglist(this);
}


antlrcpp::Any Python3Parser::ArglistContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<Python3ParserVisitor*>(visitor))
    return parserVisitor->visitArglist(this);
  else
    return visitor->visitChildren(this);
}

Python3Parser::ArglistContext* Python3Parser::arglist() {
  ArglistContext *_localctx = _tracker.createInstance<ArglistContext>(_ctx, getState());
  enterRule(_localctx, 220, Python3Parser::RuleArglist);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    size_t alt;
    enterOuterAlt(_localctx, 1);
    setState(1374);
    argument();
    setState(1379);
    _errHandler->sync(this);
    alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 190, _ctx);
    while (alt != 2 && alt != atn::ATN::INVALID_ALT_NUMBER) {
      if (alt == 1) {
        setState(1375);
        match(Python3Parser::COMMA);
        setState(1376);
        argument(); 
      }
      setState(1381);
      _errHandler->sync(this);
      alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 190, _ctx);
    }
    setState(1383);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == Python3Parser::COMMA) {
      setState(1382);
      match(Python3Parser::COMMA);
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- ArgumentContext ------------------------------------------------------------------

Python3Parser::ArgumentContext::ArgumentContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

std::vector<Python3Parser::TestContext *> Python3Parser::ArgumentContext::test() {
  return getRuleContexts<Python3Parser::TestContext>();
}

Python3Parser::TestContext* Python3Parser::ArgumentContext::test(size_t i) {
  return getRuleContext<Python3Parser::TestContext>(i);
}

tree::TerminalNode* Python3Parser::ArgumentContext::ASSIGN() {
  return getToken(Python3Parser::ASSIGN, 0);
}

tree::TerminalNode* Python3Parser::ArgumentContext::POWER() {
  return getToken(Python3Parser::POWER, 0);
}

tree::TerminalNode* Python3Parser::ArgumentContext::STAR() {
  return getToken(Python3Parser::STAR, 0);
}

Python3Parser::Comp_forContext* Python3Parser::ArgumentContext::comp_for() {
  return getRuleContext<Python3Parser::Comp_forContext>(0);
}


size_t Python3Parser::ArgumentContext::getRuleIndex() const {
  return Python3Parser::RuleArgument;
}

void Python3Parser::ArgumentContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<Python3ParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterArgument(this);
}

void Python3Parser::ArgumentContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<Python3ParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitArgument(this);
}


antlrcpp::Any Python3Parser::ArgumentContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<Python3ParserVisitor*>(visitor))
    return parserVisitor->visitArgument(this);
  else
    return visitor->visitChildren(this);
}

Python3Parser::ArgumentContext* Python3Parser::argument() {
  ArgumentContext *_localctx = _tracker.createInstance<ArgumentContext>(_ctx, getState());
  enterRule(_localctx, 222, Python3Parser::RuleArgument);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(1397);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 193, _ctx)) {
    case 1: {
      setState(1385);
      test();
      setState(1387);
      _errHandler->sync(this);

      _la = _input->LA(1);
      if (_la == Python3Parser::ASYNC

      || _la == Python3Parser::FOR) {
        setState(1386);
        comp_for();
      }
      break;
    }

    case 2: {
      setState(1389);
      test();
      setState(1390);
      match(Python3Parser::ASSIGN);
      setState(1391);
      test();
      break;
    }

    case 3: {
      setState(1393);
      match(Python3Parser::POWER);
      setState(1394);
      test();
      break;
    }

    case 4: {
      setState(1395);
      match(Python3Parser::STAR);
      setState(1396);
      test();
      break;
    }

    default:
      break;
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- Comp_iterContext ------------------------------------------------------------------

Python3Parser::Comp_iterContext::Comp_iterContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

Python3Parser::Comp_forContext* Python3Parser::Comp_iterContext::comp_for() {
  return getRuleContext<Python3Parser::Comp_forContext>(0);
}

Python3Parser::Comp_ifContext* Python3Parser::Comp_iterContext::comp_if() {
  return getRuleContext<Python3Parser::Comp_ifContext>(0);
}


size_t Python3Parser::Comp_iterContext::getRuleIndex() const {
  return Python3Parser::RuleComp_iter;
}

void Python3Parser::Comp_iterContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<Python3ParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterComp_iter(this);
}

void Python3Parser::Comp_iterContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<Python3ParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitComp_iter(this);
}


antlrcpp::Any Python3Parser::Comp_iterContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<Python3ParserVisitor*>(visitor))
    return parserVisitor->visitComp_iter(this);
  else
    return visitor->visitChildren(this);
}

Python3Parser::Comp_iterContext* Python3Parser::comp_iter() {
  Comp_iterContext *_localctx = _tracker.createInstance<Comp_iterContext>(_ctx, getState());
  enterRule(_localctx, 224, Python3Parser::RuleComp_iter);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    setState(1401);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case Python3Parser::ASYNC:
      case Python3Parser::FOR: {
        enterOuterAlt(_localctx, 1);
        setState(1399);
        comp_for();
        break;
      }

      case Python3Parser::IF: {
        enterOuterAlt(_localctx, 2);
        setState(1400);
        comp_if();
        break;
      }

    default:
      throw NoViableAltException(this);
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- Comp_forContext ------------------------------------------------------------------

Python3Parser::Comp_forContext::Comp_forContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* Python3Parser::Comp_forContext::FOR() {
  return getToken(Python3Parser::FOR, 0);
}

Python3Parser::ExprlistContext* Python3Parser::Comp_forContext::exprlist() {
  return getRuleContext<Python3Parser::ExprlistContext>(0);
}

tree::TerminalNode* Python3Parser::Comp_forContext::IN() {
  return getToken(Python3Parser::IN, 0);
}

Python3Parser::Or_testContext* Python3Parser::Comp_forContext::or_test() {
  return getRuleContext<Python3Parser::Or_testContext>(0);
}

tree::TerminalNode* Python3Parser::Comp_forContext::ASYNC() {
  return getToken(Python3Parser::ASYNC, 0);
}

Python3Parser::Comp_iterContext* Python3Parser::Comp_forContext::comp_iter() {
  return getRuleContext<Python3Parser::Comp_iterContext>(0);
}


size_t Python3Parser::Comp_forContext::getRuleIndex() const {
  return Python3Parser::RuleComp_for;
}

void Python3Parser::Comp_forContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<Python3ParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterComp_for(this);
}

void Python3Parser::Comp_forContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<Python3ParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitComp_for(this);
}


antlrcpp::Any Python3Parser::Comp_forContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<Python3ParserVisitor*>(visitor))
    return parserVisitor->visitComp_for(this);
  else
    return visitor->visitChildren(this);
}

Python3Parser::Comp_forContext* Python3Parser::comp_for() {
  Comp_forContext *_localctx = _tracker.createInstance<Comp_forContext>(_ctx, getState());
  enterRule(_localctx, 226, Python3Parser::RuleComp_for);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(1404);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == Python3Parser::ASYNC) {
      setState(1403);
      match(Python3Parser::ASYNC);
    }
    setState(1406);
    match(Python3Parser::FOR);
    setState(1407);
    exprlist();
    setState(1408);
    match(Python3Parser::IN);
    setState(1409);
    or_test();
    setState(1411);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if ((((_la & ~ 0x3fULL) == 0) &&
      ((1ULL << _la) & ((1ULL << Python3Parser::ASYNC)
      | (1ULL << Python3Parser::FOR)
      | (1ULL << Python3Parser::IF))) != 0)) {
      setState(1410);
      comp_iter();
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- Comp_ifContext ------------------------------------------------------------------

Python3Parser::Comp_ifContext::Comp_ifContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* Python3Parser::Comp_ifContext::IF() {
  return getToken(Python3Parser::IF, 0);
}

Python3Parser::Test_nocondContext* Python3Parser::Comp_ifContext::test_nocond() {
  return getRuleContext<Python3Parser::Test_nocondContext>(0);
}

Python3Parser::Comp_iterContext* Python3Parser::Comp_ifContext::comp_iter() {
  return getRuleContext<Python3Parser::Comp_iterContext>(0);
}


size_t Python3Parser::Comp_ifContext::getRuleIndex() const {
  return Python3Parser::RuleComp_if;
}

void Python3Parser::Comp_ifContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<Python3ParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterComp_if(this);
}

void Python3Parser::Comp_ifContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<Python3ParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitComp_if(this);
}


antlrcpp::Any Python3Parser::Comp_ifContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<Python3ParserVisitor*>(visitor))
    return parserVisitor->visitComp_if(this);
  else
    return visitor->visitChildren(this);
}

Python3Parser::Comp_ifContext* Python3Parser::comp_if() {
  Comp_ifContext *_localctx = _tracker.createInstance<Comp_ifContext>(_ctx, getState());
  enterRule(_localctx, 228, Python3Parser::RuleComp_if);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(1413);
    match(Python3Parser::IF);
    setState(1414);
    test_nocond();
    setState(1416);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if ((((_la & ~ 0x3fULL) == 0) &&
      ((1ULL << _la) & ((1ULL << Python3Parser::ASYNC)
      | (1ULL << Python3Parser::FOR)
      | (1ULL << Python3Parser::IF))) != 0)) {
      setState(1415);
      comp_iter();
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- Encoding_declContext ------------------------------------------------------------------

Python3Parser::Encoding_declContext::Encoding_declContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

Python3Parser::NameContext* Python3Parser::Encoding_declContext::name() {
  return getRuleContext<Python3Parser::NameContext>(0);
}


size_t Python3Parser::Encoding_declContext::getRuleIndex() const {
  return Python3Parser::RuleEncoding_decl;
}

void Python3Parser::Encoding_declContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<Python3ParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterEncoding_decl(this);
}

void Python3Parser::Encoding_declContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<Python3ParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitEncoding_decl(this);
}


antlrcpp::Any Python3Parser::Encoding_declContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<Python3ParserVisitor*>(visitor))
    return parserVisitor->visitEncoding_decl(this);
  else
    return visitor->visitChildren(this);
}

Python3Parser::Encoding_declContext* Python3Parser::encoding_decl() {
  Encoding_declContext *_localctx = _tracker.createInstance<Encoding_declContext>(_ctx, getState());
  enterRule(_localctx, 230, Python3Parser::RuleEncoding_decl);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(1418);
    name();
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- Yield_exprContext ------------------------------------------------------------------

Python3Parser::Yield_exprContext::Yield_exprContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* Python3Parser::Yield_exprContext::YIELD() {
  return getToken(Python3Parser::YIELD, 0);
}

Python3Parser::Yield_argContext* Python3Parser::Yield_exprContext::yield_arg() {
  return getRuleContext<Python3Parser::Yield_argContext>(0);
}


size_t Python3Parser::Yield_exprContext::getRuleIndex() const {
  return Python3Parser::RuleYield_expr;
}

void Python3Parser::Yield_exprContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<Python3ParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterYield_expr(this);
}

void Python3Parser::Yield_exprContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<Python3ParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitYield_expr(this);
}


antlrcpp::Any Python3Parser::Yield_exprContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<Python3ParserVisitor*>(visitor))
    return parserVisitor->visitYield_expr(this);
  else
    return visitor->visitChildren(this);
}

Python3Parser::Yield_exprContext* Python3Parser::yield_expr() {
  Yield_exprContext *_localctx = _tracker.createInstance<Yield_exprContext>(_ctx, getState());
  enterRule(_localctx, 232, Python3Parser::RuleYield_expr);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(1420);
    match(Python3Parser::YIELD);
    setState(1422);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if ((((_la & ~ 0x3fULL) == 0) &&
      ((1ULL << _la) & ((1ULL << Python3Parser::STRING)
      | (1ULL << Python3Parser::NUMBER)
      | (1ULL << Python3Parser::AWAIT)
      | (1ULL << Python3Parser::FALSE)
      | (1ULL << Python3Parser::FROM)
      | (1ULL << Python3Parser::LAMBDA)
      | (1ULL << Python3Parser::MATCH)
      | (1ULL << Python3Parser::NONE)
      | (1ULL << Python3Parser::NOT)
      | (1ULL << Python3Parser::TRUE)
      | (1ULL << Python3Parser::UNDERSCORE)
      | (1ULL << Python3Parser::NAME)
      | (1ULL << Python3Parser::ELLIPSIS)
      | (1ULL << Python3Parser::OPEN_PAREN))) != 0) || ((((_la - 64) & ~ 0x3fULL) == 0) &&
      ((1ULL << (_la - 64)) & ((1ULL << (Python3Parser::OPEN_BRACK - 64))
      | (1ULL << (Python3Parser::ADD - 64))
      | (1ULL << (Python3Parser::MINUS - 64))
      | (1ULL << (Python3Parser::NOT_OP - 64))
      | (1ULL << (Python3Parser::OPEN_BRACE - 64)))) != 0)) {
      setState(1421);
      yield_arg();
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- Yield_argContext ------------------------------------------------------------------

Python3Parser::Yield_argContext::Yield_argContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* Python3Parser::Yield_argContext::FROM() {
  return getToken(Python3Parser::FROM, 0);
}

Python3Parser::TestContext* Python3Parser::Yield_argContext::test() {
  return getRuleContext<Python3Parser::TestContext>(0);
}

Python3Parser::TestlistContext* Python3Parser::Yield_argContext::testlist() {
  return getRuleContext<Python3Parser::TestlistContext>(0);
}


size_t Python3Parser::Yield_argContext::getRuleIndex() const {
  return Python3Parser::RuleYield_arg;
}

void Python3Parser::Yield_argContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<Python3ParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterYield_arg(this);
}

void Python3Parser::Yield_argContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<Python3ParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitYield_arg(this);
}


antlrcpp::Any Python3Parser::Yield_argContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<Python3ParserVisitor*>(visitor))
    return parserVisitor->visitYield_arg(this);
  else
    return visitor->visitChildren(this);
}

Python3Parser::Yield_argContext* Python3Parser::yield_arg() {
  Yield_argContext *_localctx = _tracker.createInstance<Yield_argContext>(_ctx, getState());
  enterRule(_localctx, 234, Python3Parser::RuleYield_arg);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    setState(1427);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case Python3Parser::FROM: {
        enterOuterAlt(_localctx, 1);
        setState(1424);
        match(Python3Parser::FROM);
        setState(1425);
        test();
        break;
      }

      case Python3Parser::STRING:
      case Python3Parser::NUMBER:
      case Python3Parser::AWAIT:
      case Python3Parser::FALSE:
      case Python3Parser::LAMBDA:
      case Python3Parser::MATCH:
      case Python3Parser::NONE:
      case Python3Parser::NOT:
      case Python3Parser::TRUE:
      case Python3Parser::UNDERSCORE:
      case Python3Parser::NAME:
      case Python3Parser::ELLIPSIS:
      case Python3Parser::OPEN_PAREN:
      case Python3Parser::OPEN_BRACK:
      case Python3Parser::ADD:
      case Python3Parser::MINUS:
      case Python3Parser::NOT_OP:
      case Python3Parser::OPEN_BRACE: {
        enterOuterAlt(_localctx, 2);
        setState(1426);
        testlist();
        break;
      }

    default:
      throw NoViableAltException(this);
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- StringsContext ------------------------------------------------------------------

Python3Parser::StringsContext::StringsContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

std::vector<tree::TerminalNode *> Python3Parser::StringsContext::STRING() {
  return getTokens(Python3Parser::STRING);
}

tree::TerminalNode* Python3Parser::StringsContext::STRING(size_t i) {
  return getToken(Python3Parser::STRING, i);
}


size_t Python3Parser::StringsContext::getRuleIndex() const {
  return Python3Parser::RuleStrings;
}

void Python3Parser::StringsContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<Python3ParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterStrings(this);
}

void Python3Parser::StringsContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<Python3ParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitStrings(this);
}


antlrcpp::Any Python3Parser::StringsContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<Python3ParserVisitor*>(visitor))
    return parserVisitor->visitStrings(this);
  else
    return visitor->visitChildren(this);
}

Python3Parser::StringsContext* Python3Parser::strings() {
  StringsContext *_localctx = _tracker.createInstance<StringsContext>(_ctx, getState());
  enterRule(_localctx, 236, Python3Parser::RuleStrings);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(1430); 
    _errHandler->sync(this);
    _la = _input->LA(1);
    do {
      setState(1429);
      match(Python3Parser::STRING);
      setState(1432); 
      _errHandler->sync(this);
      _la = _input->LA(1);
    } while (_la == Python3Parser::STRING);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

bool Python3Parser::sempred(RuleContext *context, size_t ruleIndex, size_t predicateIndex) {
  switch (ruleIndex) {
    case 60: return literal_patternSempred(dynamic_cast<Literal_patternContext *>(context), predicateIndex);
    case 61: return literal_exprSempred(dynamic_cast<Literal_exprContext *>(context), predicateIndex);
    case 68: return pattern_capture_targetSempred(dynamic_cast<Pattern_capture_targetContext *>(context), predicateIndex);
    case 70: return value_patternSempred(dynamic_cast<Value_patternContext *>(context), predicateIndex);
    case 97: return exprSempred(dynamic_cast<ExprContext *>(context), predicateIndex);

  default:
    break;
  }
  return true;
}

bool Python3Parser::literal_patternSempred(Literal_patternContext *_localctx, size_t predicateIndex) {
  switch (predicateIndex) {
    case 0: return  this->CannotBePlusMinus() ;

  default:
    break;
  }
  return true;
}

bool Python3Parser::literal_exprSempred(Literal_exprContext *_localctx, size_t predicateIndex) {
  switch (predicateIndex) {
    case 1: return  this->CannotBePlusMinus() ;

  default:
    break;
  }
  return true;
}

bool Python3Parser::pattern_capture_targetSempred(Pattern_capture_targetContext *_localctx, size_t predicateIndex) {
  switch (predicateIndex) {
    case 2: return  this->CannotBeDotLpEq() ;

  default:
    break;
  }
  return true;
}

bool Python3Parser::value_patternSempred(Value_patternContext *_localctx, size_t predicateIndex) {
  switch (predicateIndex) {
    case 3: return  this->CannotBeDotLpEq() ;

  default:
    break;
  }
  return true;
}

bool Python3Parser::exprSempred(ExprContext *_localctx, size_t predicateIndex) {
  switch (predicateIndex) {
    case 4: return precpred(_ctx, 8);
    case 5: return precpred(_ctx, 6);
    case 6: return precpred(_ctx, 5);
    case 7: return precpred(_ctx, 4);
    case 8: return precpred(_ctx, 3);
    case 9: return precpred(_ctx, 2);
    case 10: return precpred(_ctx, 1);

  default:
    break;
  }
  return true;
}

// Static vars and initialization.
std::vector<dfa::DFA> Python3Parser::_decisionToDFA;
atn::PredictionContextCache Python3Parser::_sharedContextCache;

// We own the ATN which in turn owns the ATN states.
atn::ATN Python3Parser::_atn;
std::vector<uint16_t> Python3Parser::_serializedATN;

std::vector<std::string> Python3Parser::_ruleNames = {
  "single_input", "file_input", "eval_input", "decorator", "decorators", 
  "decorated", "async_funcdef", "funcdef", "parameters", "typedargslist", 
  "tfpdef", "varargslist", "vfpdef", "stmt", "simple_stmts", "simple_stmt", 
  "expr_stmt", "annassign", "testlist_star_expr", "augassign", "del_stmt", 
  "pass_stmt", "flow_stmt", "break_stmt", "continue_stmt", "return_stmt", 
  "yield_stmt", "raise_stmt", "import_stmt", "import_name", "import_from", 
  "import_as_name", "dotted_as_name", "import_as_names", "dotted_as_names", 
  "dotted_name", "global_stmt", "nonlocal_stmt", "assert_stmt", "compound_stmt", 
  "async_stmt", "if_stmt", "while_stmt", "for_stmt", "try_stmt", "with_stmt", 
  "with_item", "except_clause", "block", "match_stmt", "subject_expr", "star_named_expressions", 
  "star_named_expression", "case_block", "guard", "patterns", "pattern", 
  "as_pattern", "or_pattern", "closed_pattern", "literal_pattern", "literal_expr", 
  "complex_number", "signed_number", "signed_real_number", "real_number", 
  "imaginary_number", "capture_pattern", "pattern_capture_target", "wildcard_pattern", 
  "value_pattern", "attr", "name_or_attr", "group_pattern", "sequence_pattern", 
  "open_sequence_pattern", "maybe_sequence_pattern", "maybe_star_pattern", 
  "star_pattern", "mapping_pattern", "items_pattern", "key_value_pattern", 
  "double_star_pattern", "class_pattern", "positional_patterns", "keyword_patterns", 
  "keyword_pattern", "test", "test_nocond", "lambdef", "lambdef_nocond", 
  "or_test", "and_test", "not_test", "comparison", "comp_op", "star_expr", 
  "expr", "atom_expr", "atom", "name", "testlist_comp", "trailer", "subscriptlist", 
  "subscript_", "sliceop", "exprlist", "testlist", "dictorsetmaker", "classdef", 
  "arglist", "argument", "comp_iter", "comp_for", "comp_if", "encoding_decl", 
  "yield_expr", "yield_arg", "strings"
};

std::vector<std::string> Python3Parser::_literalNames = {
  "", "", "", "", "", "", "'and'", "'as'", "'assert'", "'async'", "'await'", 
  "'break'", "'case'", "'class'", "'continue'", "'def'", "'del'", "'elif'", 
  "'else'", "'except'", "'False'", "'finally'", "'for'", "'from'", "'global'", 
  "'if'", "'import'", "'in'", "'is'", "'lambda'", "'match'", "'None'", "'nonlocal'", 
  "'not'", "'or'", "'pass'", "'raise'", "'return'", "'True'", "'try'", "'_'", 
  "'while'", "'with'", "'yield'", "", "", "", "", "", "", "", "", "", "", 
  "'.'", "'...'", "'*'", "'('", "')'", "','", "':'", "';'", "'**'", "'='", 
  "'['", "']'", "'|'", "'^'", "'&'", "'<<'", "'>>'", "'+'", "'-'", "'/'", 
  "'%'", "'//'", "'~'", "'{'", "'}'", "'<'", "'>'", "'=='", "'>='", "'<='", 
  "'<>'", "'!='", "'@'", "'->'", "'+='", "'-='", "'*='", "'@='", "'/='", 
  "'%='", "'&='", "'|='", "'^='", "'<<='", "'>>='", "'**='", "'//='"
};

std::vector<std::string> Python3Parser::_symbolicNames = {
  "", "INDENT", "DEDENT", "STRING", "NUMBER", "INTEGER", "AND", "AS", "ASSERT", 
  "ASYNC", "AWAIT", "BREAK", "CASE", "CLASS", "CONTINUE", "DEF", "DEL", 
  "ELIF", "ELSE", "EXCEPT", "FALSE", "FINALLY", "FOR", "FROM", "GLOBAL", 
  "IF", "IMPORT", "IN", "IS", "LAMBDA", "MATCH", "NONE", "NONLOCAL", "NOT", 
  "OR", "PASS", "RAISE", "RETURN", "TRUE", "TRY", "UNDERSCORE", "WHILE", 
  "WITH", "YIELD", "NEWLINE", "NAME", "STRING_LITERAL", "BYTES_LITERAL", 
  "DECIMAL_INTEGER", "OCT_INTEGER", "HEX_INTEGER", "BIN_INTEGER", "FLOAT_NUMBER", 
  "IMAG_NUMBER", "DOT", "ELLIPSIS", "STAR", "OPEN_PAREN", "CLOSE_PAREN", 
  "COMMA", "COLON", "SEMI_COLON", "POWER", "ASSIGN", "OPEN_BRACK", "CLOSE_BRACK", 
  "OR_OP", "XOR", "AND_OP", "LEFT_SHIFT", "RIGHT_SHIFT", "ADD", "MINUS", 
  "DIV", "MOD", "IDIV", "NOT_OP", "OPEN_BRACE", "CLOSE_BRACE", "LESS_THAN", 
  "GREATER_THAN", "EQUALS", "GT_EQ", "LT_EQ", "NOT_EQ_1", "NOT_EQ_2", "AT", 
  "ARROW", "ADD_ASSIGN", "SUB_ASSIGN", "MULT_ASSIGN", "AT_ASSIGN", "DIV_ASSIGN", 
  "MOD_ASSIGN", "AND_ASSIGN", "OR_ASSIGN", "XOR_ASSIGN", "LEFT_SHIFT_ASSIGN", 
  "RIGHT_SHIFT_ASSIGN", "POWER_ASSIGN", "IDIV_ASSIGN", "SKIP_", "UNKNOWN_CHAR"
};

dfa::Vocabulary Python3Parser::_vocabulary(_literalNames, _symbolicNames);

std::vector<std::string> Python3Parser::_tokenNames;

Python3Parser::Initializer::Initializer() {
	for (size_t i = 0; i < _symbolicNames.size(); ++i) {
		std::string name = _vocabulary.getLiteralName(i);
		if (name.empty()) {
			name = _vocabulary.getSymbolicName(i);
		}

		if (name.empty()) {
			_tokenNames.push_back("<INVALID>");
		} else {
      _tokenNames.push_back(name);
    }
	}

  static const uint16_t serializedATNSegment0[] = {
    0x3, 0x608b, 0xa72a, 0x8133, 0xb9ed, 0x417c, 0x3be7, 0x7786, 0x5964, 
       0x3, 0x68, 0x59d, 0x4, 0x2, 0x9, 0x2, 0x4, 0x3, 0x9, 0x3, 0x4, 0x4, 
       0x9, 0x4, 0x4, 0x5, 0x9, 0x5, 0x4, 0x6, 0x9, 0x6, 0x4, 0x7, 0x9, 
       0x7, 0x4, 0x8, 0x9, 0x8, 0x4, 0x9, 0x9, 0x9, 0x4, 0xa, 0x9, 0xa, 
       0x4, 0xb, 0x9, 0xb, 0x4, 0xc, 0x9, 0xc, 0x4, 0xd, 0x9, 0xd, 0x4, 
       0xe, 0x9, 0xe, 0x4, 0xf, 0x9, 0xf, 0x4, 0x10, 0x9, 0x10, 0x4, 0x11, 
       0x9, 0x11, 0x4, 0x12, 0x9, 0x12, 0x4, 0x13, 0x9, 0x13, 0x4, 0x14, 
       0x9, 0x14, 0x4, 0x15, 0x9, 0x15, 0x4, 0x16, 0x9, 0x16, 0x4, 0x17, 
       0x9, 0x17, 0x4, 0x18, 0x9, 0x18, 0x4, 0x19, 0x9, 0x19, 0x4, 0x1a, 
       0x9, 0x1a, 0x4, 0x1b, 0x9, 0x1b, 0x4, 0x1c, 0x9, 0x1c, 0x4, 0x1d, 
       0x9, 0x1d, 0x4, 0x1e, 0x9, 0x1e, 0x4, 0x1f, 0x9, 0x1f, 0x4, 0x20, 
       0x9, 0x20, 0x4, 0x21, 0x9, 0x21, 0x4, 0x22, 0x9, 0x22, 0x4, 0x23, 
       0x9, 0x23, 0x4, 0x24, 0x9, 0x24, 0x4, 0x25, 0x9, 0x25, 0x4, 0x26, 
       0x9, 0x26, 0x4, 0x27, 0x9, 0x27, 0x4, 0x28, 0x9, 0x28, 0x4, 0x29, 
       0x9, 0x29, 0x4, 0x2a, 0x9, 0x2a, 0x4, 0x2b, 0x9, 0x2b, 0x4, 0x2c, 
       0x9, 0x2c, 0x4, 0x2d, 0x9, 0x2d, 0x4, 0x2e, 0x9, 0x2e, 0x4, 0x2f, 
       0x9, 0x2f, 0x4, 0x30, 0x9, 0x30, 0x4, 0x31, 0x9, 0x31, 0x4, 0x32, 
       0x9, 0x32, 0x4, 0x33, 0x9, 0x33, 0x4, 0x34, 0x9, 0x34, 0x4, 0x35, 
       0x9, 0x35, 0x4, 0x36, 0x9, 0x36, 0x4, 0x37, 0x9, 0x37, 0x4, 0x38, 
       0x9, 0x38, 0x4, 0x39, 0x9, 0x39, 0x4, 0x3a, 0x9, 0x3a, 0x4, 0x3b, 
       0x9, 0x3b, 0x4, 0x3c, 0x9, 0x3c, 0x4, 0x3d, 0x9, 0x3d, 0x4, 0x3e, 
       0x9, 0x3e, 0x4, 0x3f, 0x9, 0x3f, 0x4, 0x40, 0x9, 0x40, 0x4, 0x41, 
       0x9, 0x41, 0x4, 0x42, 0x9, 0x42, 0x4, 0x43, 0x9, 0x43, 0x4, 0x44, 
       0x9, 0x44, 0x4, 0x45, 0x9, 0x45, 0x4, 0x46, 0x9, 0x46, 0x4, 0x47, 
       0x9, 0x47, 0x4, 0x48, 0x9, 0x48, 0x4, 0x49, 0x9, 0x49, 0x4, 0x4a, 
       0x9, 0x4a, 0x4, 0x4b, 0x9, 0x4b, 0x4, 0x4c, 0x9, 0x4c, 0x4, 0x4d, 
       0x9, 0x4d, 0x4, 0x4e, 0x9, 0x4e, 0x4, 0x4f, 0x9, 0x4f, 0x4, 0x50, 
       0x9, 0x50, 0x4, 0x51, 0x9, 0x51, 0x4, 0x52, 0x9, 0x52, 0x4, 0x53, 
       0x9, 0x53, 0x4, 0x54, 0x9, 0x54, 0x4, 0x55, 0x9, 0x55, 0x4, 0x56, 
       0x9, 0x56, 0x4, 0x57, 0x9, 0x57, 0x4, 0x58, 0x9, 0x58, 0x4, 0x59, 
       0x9, 0x59, 0x4, 0x5a, 0x9, 0x5a, 0x4, 0x5b, 0x9, 0x5b, 0x4, 0x5c, 
       0x9, 0x5c, 0x4, 0x5d, 0x9, 0x5d, 0x4, 0x5e, 0x9, 0x5e, 0x4, 0x5f, 
       0x9, 0x5f, 0x4, 0x60, 0x9, 0x60, 0x4, 0x61, 0x9, 0x61, 0x4, 0x62, 
       0x9, 0x62, 0x4, 0x63, 0x9, 0x63, 0x4, 0x64, 0x9, 0x64, 0x4, 0x65, 
       0x9, 0x65, 0x4, 0x66, 0x9, 0x66, 0x4, 0x67, 0x9, 0x67, 0x4, 0x68, 
       0x9, 0x68, 0x4, 0x69, 0x9, 0x69, 0x4, 0x6a, 0x9, 0x6a, 0x4, 0x6b, 
       0x9, 0x6b, 0x4, 0x6c, 0x9, 0x6c, 0x4, 0x6d, 0x9, 0x6d, 0x4, 0x6e, 
       0x9, 0x6e, 0x4, 0x6f, 0x9, 0x6f, 0x4, 0x70, 0x9, 0x70, 0x4, 0x71, 
       0x9, 0x71, 0x4, 0x72, 0x9, 0x72, 0x4, 0x73, 0x9, 0x73, 0x4, 0x74, 
       0x9, 0x74, 0x4, 0x75, 0x9, 0x75, 0x4, 0x76, 0x9, 0x76, 0x4, 0x77, 
       0x9, 0x77, 0x4, 0x78, 0x9, 0x78, 0x3, 0x2, 0x3, 0x2, 0x3, 0x2, 0x3, 
       0x2, 0x3, 0x2, 0x5, 0x2, 0xf6, 0xa, 0x2, 0x3, 0x3, 0x3, 0x3, 0x7, 
       0x3, 0xfa, 0xa, 0x3, 0xc, 0x3, 0xe, 0x3, 0xfd, 0xb, 0x3, 0x3, 0x3, 
       0x3, 0x3, 0x3, 0x4, 0x3, 0x4, 0x7, 0x4, 0x103, 0xa, 0x4, 0xc, 0x4, 
       0xe, 0x4, 0x106, 0xb, 0x4, 0x3, 0x4, 0x3, 0x4, 0x3, 0x5, 0x3, 0x5, 
       0x3, 0x5, 0x3, 0x5, 0x5, 0x5, 0x10e, 0xa, 0x5, 0x3, 0x5, 0x5, 0x5, 
       0x111, 0xa, 0x5, 0x3, 0x5, 0x3, 0x5, 0x3, 0x6, 0x6, 0x6, 0x116, 0xa, 
       0x6, 0xd, 0x6, 0xe, 0x6, 0x117, 0x3, 0x7, 0x3, 0x7, 0x3, 0x7, 0x3, 
       0x7, 0x5, 0x7, 0x11e, 0xa, 0x7, 0x3, 0x8, 0x3, 0x8, 0x3, 0x8, 0x3, 
       0x9, 0x3, 0x9, 0x3, 0x9, 0x3, 0x9, 0x3, 0x9, 0x5, 0x9, 0x128, 0xa, 
       0x9, 0x3, 0x9, 0x3, 0x9, 0x3, 0x9, 0x3, 0xa, 0x3, 0xa, 0x5, 0xa, 
       0x12f, 0xa, 0xa, 0x3, 0xa, 0x3, 0xa, 0x3, 0xb, 0x3, 0xb, 0x3, 0xb, 
       0x5, 0xb, 0x136, 0xa, 0xb, 0x3, 0xb, 0x3, 0xb, 0x3, 0xb, 0x3, 0xb, 
       0x5, 0xb, 0x13c, 0xa, 0xb, 0x7, 0xb, 0x13e, 0xa, 0xb, 0xc, 0xb, 0xe, 
       0xb, 0x141, 0xb, 0xb, 0x3, 0xb, 0x3, 0xb, 0x3, 0xb, 0x5, 0xb, 0x146, 
       0xa, 0xb, 0x3, 0xb, 0x3, 0xb, 0x3, 0xb, 0x3, 0xb, 0x5, 0xb, 0x14c, 
       0xa, 0xb, 0x7, 0xb, 0x14e, 0xa, 0xb, 0xc, 0xb, 0xe, 0xb, 0x151, 0xb, 
       0xb, 0x3, 0xb, 0x3, 0xb, 0x3, 0xb, 0x3, 0xb, 0x5, 0xb, 0x157, 0xa, 
       0xb, 0x5, 0xb, 0x159, 0xa, 0xb, 0x5, 0xb, 0x15b, 0xa, 0xb, 0x3, 0xb, 
       0x3, 0xb, 0x3, 0xb, 0x5, 0xb, 0x160, 0xa, 0xb, 0x5, 0xb, 0x162, 0xa, 
       0xb, 0x5, 0xb, 0x164, 0xa, 0xb, 0x3, 0xb, 0x3, 0xb, 0x5, 0xb, 0x168, 
       0xa, 0xb, 0x3, 0xb, 0x3, 0xb, 0x3, 0xb, 0x3, 0xb, 0x5, 0xb, 0x16e, 
       0xa, 0xb, 0x7, 0xb, 0x170, 0xa, 0xb, 0xc, 0xb, 0xe, 0xb, 0x173, 0xb, 
       0xb, 0x3, 0xb, 0x3, 0xb, 0x3, 0xb, 0x3, 0xb, 0x5, 0xb, 0x179, 0xa, 
       0xb, 0x5, 0xb, 0x17b, 0xa, 0xb, 0x5, 0xb, 0x17d, 0xa, 0xb, 0x3, 0xb, 
       0x3, 0xb, 0x3, 0xb, 0x5, 0xb, 0x182, 0xa, 0xb, 0x5, 0xb, 0x184, 0xa, 
       0xb, 0x3, 0xc, 0x3, 0xc, 0x3, 0xc, 0x5, 0xc, 0x189, 0xa, 0xc, 0x3, 
       0xd, 0x3, 0xd, 0x3, 0xd, 0x5, 0xd, 0x18e, 0xa, 0xd, 0x3, 0xd, 0x3, 
       0xd, 0x3, 0xd, 0x3, 0xd, 0x5, 0xd, 0x194, 0xa, 0xd, 0x7, 0xd, 0x196, 
       0xa, 0xd, 0xc, 0xd, 0xe, 0xd, 0x199, 0xb, 0xd, 0x3, 0xd, 0x3, 0xd, 
       0x3, 0xd, 0x5, 0xd, 0x19e, 0xa, 0xd, 0x3, 0xd, 0x3, 0xd, 0x3, 0xd, 
       0x3, 0xd, 0x5, 0xd, 0x1a4, 0xa, 0xd, 0x7, 0xd, 0x1a6, 0xa, 0xd, 0xc, 
       0xd, 0xe, 0xd, 0x1a9, 0xb, 0xd, 0x3, 0xd, 0x3, 0xd, 0x3, 0xd, 0x3, 
       0xd, 0x5, 0xd, 0x1af, 0xa, 0xd, 0x5, 0xd, 0x1b1, 0xa, 0xd, 0x5, 0xd, 
       0x1b3, 0xa, 0xd, 0x3, 0xd, 0x3, 0xd, 0x3, 0xd, 0x5, 0xd, 0x1b8, 0xa, 
       0xd, 0x5, 0xd, 0x1ba, 0xa, 0xd, 0x5, 0xd, 0x1bc, 0xa, 0xd, 0x3, 0xd, 
       0x3, 0xd, 0x5, 0xd, 0x1c0, 0xa, 0xd, 0x3, 0xd, 0x3, 0xd, 0x3, 0xd, 
       0x3, 0xd, 0x5, 0xd, 0x1c6, 0xa, 0xd, 0x7, 0xd, 0x1c8, 0xa, 0xd, 0xc, 
       0xd, 0xe, 0xd, 0x1cb, 0xb, 0xd, 0x3, 0xd, 0x3, 0xd, 0x3, 0xd, 0x3, 
       0xd, 0x5, 0xd, 0x1d1, 0xa, 0xd, 0x5, 0xd, 0x1d3, 0xa, 0xd, 0x5, 0xd, 
       0x1d5, 0xa, 0xd, 0x3, 0xd, 0x3, 0xd, 0x3, 0xd, 0x5, 0xd, 0x1da, 0xa, 
       0xd, 0x5, 0xd, 0x1dc, 0xa, 0xd, 0x3, 0xe, 0x3, 0xe, 0x3, 0xf, 0x3, 
       0xf, 0x5, 0xf, 0x1e2, 0xa, 0xf, 0x3, 0x10, 0x3, 0x10, 0x3, 0x10, 
       0x7, 0x10, 0x1e7, 0xa, 0x10, 0xc, 0x10, 0xe, 0x10, 0x1ea, 0xb, 0x10, 
       0x3, 0x10, 0x5, 0x10, 0x1ed, 0xa, 0x10, 0x3, 0x10, 0x3, 0x10, 0x3, 
       0x11, 0x3, 0x11, 0x3, 0x11, 0x3, 0x11, 0x3, 0x11, 0x3, 0x11, 0x3, 
       0x11, 0x3, 0x11, 0x5, 0x11, 0x1f9, 0xa, 0x11, 0x3, 0x12, 0x3, 0x12, 
       0x3, 0x12, 0x3, 0x12, 0x3, 0x12, 0x5, 0x12, 0x200, 0xa, 0x12, 0x3, 
       0x12, 0x3, 0x12, 0x3, 0x12, 0x5, 0x12, 0x205, 0xa, 0x12, 0x7, 0x12, 
       0x207, 0xa, 0x12, 0xc, 0x12, 0xe, 0x12, 0x20a, 0xb, 0x12, 0x5, 0x12, 
       0x20c, 0xa, 0x12, 0x3, 0x13, 0x3, 0x13, 0x3, 0x13, 0x3, 0x13, 0x5, 
       0x13, 0x212, 0xa, 0x13, 0x3, 0x14, 0x3, 0x14, 0x5, 0x14, 0x216, 0xa, 
       0x14, 0x3, 0x14, 0x3, 0x14, 0x3, 0x14, 0x5, 0x14, 0x21b, 0xa, 0x14, 
       0x7, 0x14, 0x21d, 0xa, 0x14, 0xc, 0x14, 0xe, 0x14, 0x220, 0xb, 0x14, 
       0x3, 0x14, 0x5, 0x14, 0x223, 0xa, 0x14, 0x3, 0x15, 0x3, 0x15, 0x3, 
       0x16, 0x3, 0x16, 0x3, 0x16, 0x3, 0x17, 0x3, 0x17, 0x3, 0x18, 0x3, 
       0x18, 0x3, 0x18, 0x3, 0x18, 0x3, 0x18, 0x5, 0x18, 0x231, 0xa, 0x18, 
       0x3, 0x19, 0x3, 0x19, 0x3, 0x1a, 0x3, 0x1a, 0x3, 0x1b, 0x3, 0x1b, 
       0x5, 0x1b, 0x239, 0xa, 0x1b, 0x3, 0x1c, 0x3, 0x1c, 0x3, 0x1d, 0x3, 
       0x1d, 0x3, 0x1d, 0x3, 0x1d, 0x5, 0x1d, 0x241, 0xa, 0x1d, 0x5, 0x1d, 
       0x243, 0xa, 0x1d, 0x3, 0x1e, 0x3, 0x1e, 0x5, 0x1e, 0x247, 0xa, 0x1e, 
       0x3, 0x1f, 0x3, 0x1f, 0x3, 0x1f, 0x3, 0x20, 0x3, 0x20, 0x7, 0x20, 
       0x24e, 0xa, 0x20, 0xc, 0x20, 0xe, 0x20, 0x251, 0xb, 0x20, 0x3, 0x20, 
       0x3, 0x20, 0x6, 0x20, 0x255, 0xa, 0x20, 0xd, 0x20, 0xe, 0x20, 0x256, 
       0x5, 0x20, 0x259, 0xa, 0x20, 0x3, 0x20, 0x3, 0x20, 0x3, 0x20, 0x3, 
       0x20, 0x3, 0x20, 0x3, 0x20, 0x3, 0x20, 0x5, 0x20, 0x262, 0xa, 0x20, 
       0x3, 0x21, 0x3, 0x21, 0x3, 0x21, 0x5, 0x21, 0x267, 0xa, 0x21, 0x3, 
       0x22, 0x3, 0x22, 0x3, 0x22, 0x5, 0x22, 0x26c, 0xa, 0x22, 0x3, 0x23, 
       0x3, 0x23, 0x3, 0x23, 0x7, 0x23, 0x271, 0xa, 0x23, 0xc, 0x23, 0xe, 
       0x23, 0x274, 0xb, 0x23, 0x3, 0x23, 0x5, 0x23, 0x277, 0xa, 0x23, 0x3, 
       0x24, 0x3, 0x24, 0x3, 0x24, 0x7, 0x24, 0x27c, 0xa, 0x24, 0xc, 0x24, 
       0xe, 0x24, 0x27f, 0xb, 0x24, 0x3, 0x25, 0x3, 0x25, 0x3, 0x25, 0x7, 
       0x25, 0x284, 0xa, 0x25, 0xc, 0x25, 0xe, 0x25, 0x287, 0xb, 0x25, 0x3, 
       0x26, 0x3, 0x26, 0x3, 0x26, 0x3, 0x26, 0x7, 0x26, 0x28d, 0xa, 0x26, 
       0xc, 0x26, 0xe, 0x26, 0x290, 0xb, 0x26, 0x3, 0x27, 0x3, 0x27, 0x3, 
       0x27, 0x3, 0x27, 0x7, 0x27, 0x296, 0xa, 0x27, 0xc, 0x27, 0xe, 0x27, 
       0x299, 0xb, 0x27, 0x3, 0x28, 0x3, 0x28, 0x3, 0x28, 0x3, 0x28, 0x5, 
       0x28, 0x29f, 0xa, 0x28, 0x3, 0x29, 0x3, 0x29, 0x3, 0x29, 0x3, 0x29, 
       0x3, 0x29, 0x3, 0x29, 0x3, 0x29, 0x3, 0x29, 0x3, 0x29, 0x3, 0x29, 
       0x5, 0x29, 0x2ab, 0xa, 0x29, 0x3, 0x2a, 0x3, 0x2a, 0x3, 0x2a, 0x3, 
       0x2a, 0x5, 0x2a, 0x2b1, 0xa, 0x2a, 0x3, 0x2b, 0x3, 0x2b, 0x3, 0x2b, 
       0x3, 0x2b, 0x3, 0x2b, 0x3, 0x2b, 0x3, 0x2b, 0x3, 0x2b, 0x3, 0x2b, 
       0x7, 0x2b, 0x2bc, 0xa, 0x2b, 0xc, 0x2b, 0xe, 0x2b, 0x2bf, 0xb, 0x2b, 
       0x3, 0x2b, 0x3, 0x2b, 0x3, 0x2b, 0x5, 0x2b, 0x2c4, 0xa, 0x2b, 0x3, 
       0x2c, 0x3, 0x2c, 0x3, 0x2c, 0x3, 0x2c, 0x3, 0x2c, 0x3, 0x2c, 0x3, 
       0x2c, 0x5, 0x2c, 0x2cd, 0xa, 0x2c, 0x3, 0x2d, 0x3, 0x2d, 0x3, 0x2d, 
       0x3, 0x2d, 0x3, 0x2d, 0x3, 0x2d, 0x3, 0x2d, 0x3, 0x2d, 0x3, 0x2d, 
       0x5, 0x2d, 0x2d8, 0xa, 0x2d, 0x3, 0x2e, 0x3, 0x2e, 0x3, 0x2e, 0x3, 
       0x2e, 0x3, 0x2e, 0x3, 0x2e, 0x3, 0x2e, 0x6, 0x2e, 0x2e1, 0xa, 0x2e, 
       0xd, 0x2e, 0xe, 0x2e, 0x2e2, 0x3, 0x2e, 0x3, 0x2e, 0x3, 0x2e, 0x5, 
       0x2e, 0x2e8, 0xa, 0x2e, 0x3, 0x2e, 0x3, 0x2e, 0x3, 0x2e, 0x5, 0x2e, 
       0x2ed, 0xa, 0x2e, 0x3, 0x2e, 0x3, 0x2e, 0x3, 0x2e, 0x5, 0x2e, 0x2f2, 
       0xa, 0x2e, 0x3, 0x2f, 0x3, 0x2f, 0x3, 0x2f, 0x3, 0x2f, 0x7, 0x2f, 
       0x2f8, 0xa, 0x2f, 0xc, 0x2f, 0xe, 0x2f, 0x2fb, 0xb, 0x2f, 0x3, 0x2f, 
       0x3, 0x2f, 0x3, 0x2f, 0x3, 0x30, 0x3, 0x30, 0x3, 0x30, 0x5, 0x30, 
       0x303, 0xa, 0x30, 0x3, 0x31, 0x3, 0x31, 0x3, 0x31, 0x3, 0x31, 0x5, 
       0x31, 0x309, 0xa, 0x31, 0x5, 0x31, 0x30b, 0xa, 0x31, 0x3, 0x32, 0x3, 
       0x32, 0x3, 0x32, 0x3, 0x32, 0x6, 0x32, 0x311, 0xa, 0x32, 0xd, 0x32, 
       0xe, 0x32, 0x312, 0x3, 0x32, 0x3, 0x32, 0x5, 0x32, 0x317, 0xa, 0x32, 
       0x3, 0x33, 0x3, 0x33, 0x3, 0x33, 0x3, 0x33, 0x3, 0x33, 0x3, 0x33, 
       0x6, 0x33, 0x31f, 0xa, 0x33, 0xd, 0x33, 0xe, 0x33, 0x320, 0x3, 0x33, 
       0x3, 0x33, 0x3, 0x34, 0x3, 0x34, 0x3, 0x34, 0x5, 0x34, 0x328, 0xa, 
       0x34, 0x3, 0x34, 0x5, 0x34, 0x32b, 0xa, 0x34, 0x3, 0x35, 0x3, 0x35, 
       0x6, 0x35, 0x32f, 0xa, 0x35, 0xd, 0x35, 0xe, 0x35, 0x330, 0x3, 0x35, 
       0x5, 0x35, 0x334, 0xa, 0x35, 0x3, 0x36, 0x3, 0x36, 0x3, 0x36, 0x5, 
       0x36, 0x339, 0xa, 0x36, 0x3, 0x37, 0x3, 0x37, 0x3, 0x37, 0x5, 0x37, 
       0x33e, 0xa, 0x37, 0x3, 0x37, 0x3, 0x37, 0x3, 0x37, 0x3, 0x38, 0x3, 
       0x38, 0x3, 0x38, 0x3, 0x39, 0x3, 0x39, 0x5, 0x39, 0x348, 0xa, 0x39, 
       0x3, 0x3a, 0x3, 0x3a, 0x5, 0x3a, 0x34c, 0xa, 0x3a, 0x3, 0x3b, 0x3, 
       0x3b, 0x3, 0x3b, 0x3, 0x3b, 0x3, 0x3c, 0x3, 0x3c, 0x3, 0x3c, 0x7, 
       0x3c, 0x355, 0xa, 0x3c, 0xc, 0x3c, 0xe, 0x3c, 0x358, 0xb, 0x3c, 0x3, 
       0x3d, 0x3, 0x3d, 0x3, 0x3d, 0x3, 0x3d, 0x3, 0x3d, 0x3, 0x3d, 0x3, 
       0x3d, 0x3, 0x3d, 0x5, 0x3d, 0x362, 0xa, 0x3d, 0x3, 0x3e, 0x3, 0x3e, 
       0x3, 0x3e, 0x3, 0x3e, 0x3, 0x3e, 0x3, 0x3e, 0x3, 0x3e, 0x3, 0x3e, 
       0x5, 0x3e, 0x36c, 0xa, 0x3e, 0x3, 0x3f, 0x3, 0x3f, 0x3, 0x3f, 0x3, 
       0x3f, 0x3, 0x3f, 0x3, 0x3f, 0x3, 0x3f, 0x3, 0x3f, 0x5, 0x3f, 0x376, 
       0xa, 0x3f, 0x3, 0x40, 0x3, 0x40, 0x3, 0x40, 0x3, 0x40, 0x3, 0x40, 
       0x3, 0x40, 0x3, 0x40, 0x3, 0x40, 0x5, 0x40, 0x380, 0xa, 0x40, 0x3, 
       0x41, 0x3, 0x41, 0x3, 0x41, 0x5, 0x41, 0x385, 0xa, 0x41, 0x3, 0x42, 
       0x3, 0x42, 0x3, 0x42, 0x5, 0x42, 0x38a, 0xa, 0x42, 0x3, 0x43, 0x3, 
       0x43, 0x3, 0x44, 0x3, 0x44, 0x3, 0x45, 0x3, 0x45, 0x3, 0x46, 0x3, 
       0x46, 0x3, 0x46, 0x3, 0x47, 0x3, 0x47, 0x3, 0x48, 0x3, 0x48, 0x3, 
       0x48, 0x3, 0x49, 0x3, 0x49, 0x3, 0x49, 0x6, 0x49, 0x39d, 0xa, 0x49, 
       0xd, 0x49, 0xe, 0x49, 0x39e, 0x3, 0x4a, 0x3, 0x4a, 0x5, 0x4a, 0x3a3, 
       0xa, 0x4a, 0x3, 0x4b, 0x3, 0x4b, 0x3, 0x4b, 0x3, 0x4b, 0x3, 0x4c, 
       0x3, 0x4c, 0x5, 0x4c, 0x3ab, 0xa, 0x4c, 0x3, 0x4c, 0x3, 0x4c, 0x3, 
       0x4c, 0x5, 0x4c, 0x3b0, 0xa, 0x4c, 0x3, 0x4c, 0x5, 0x4c, 0x3b3, 0xa, 
       0x4c, 0x3, 0x4d, 0x3, 0x4d, 0x3, 0x4d, 0x5, 0x4d, 0x3b8, 0xa, 0x4d, 
       0x3, 0x4e, 0x3, 0x4e, 0x3, 0x4e, 0x7, 0x4e, 0x3bd, 0xa, 0x4e, 0xc, 
       0x4e, 0xe, 0x4e, 0x3c0, 0xb, 0x4e, 0x3, 0x4e, 0x5, 0x4e, 0x3c3, 0xa, 
       0x4e, 0x3, 0x4f, 0x3, 0x4f, 0x5, 0x4f, 0x3c7, 0xa, 0x4f, 0x3, 0x50, 
       0x3, 0x50, 0x3, 0x50, 0x3, 0x50, 0x5, 0x50, 0x3cd, 0xa, 0x50, 0x3, 
       0x51, 0x3, 0x51, 0x3, 0x51, 0x3, 0x51, 0x3, 0x51, 0x5, 0x51, 0x3d4, 
       0xa, 0x51, 0x3, 0x51, 0x3, 0x51, 0x3, 0x51, 0x3, 0x51, 0x3, 0x51, 
       0x3, 0x51, 0x3, 0x51, 0x5, 0x51, 0x3dd, 0xa, 0x51, 0x3, 0x51, 0x3, 
       0x51, 0x3, 0x51, 0x3, 0x51, 0x3, 0x51, 0x5, 0x51, 0x3e4, 0xa, 0x51, 
       0x3, 0x51, 0x3, 0x51, 0x5, 0x51, 0x3e8, 0xa, 0x51, 0x3, 0x52, 0x3, 
       0x52, 0x3, 0x52, 0x7, 0x52, 0x3ed, 0xa, 0x52, 0xc, 0x52, 0xe, 0x52, 
       0x3f0, 0xb, 0x52, 0x3, 0x53, 0x3, 0x53, 0x5, 0x53, 0x3f4, 0xa, 0x53, 
       0x3, 0x53, 0x3, 0x53, 0x3, 0x53, 0x3, 0x54, 0x3, 0x54, 0x3, 0x54, 
       0x3, 0x55, 0x3, 0x55, 0x3, 0x55, 0x3, 0x55, 0x3, 0x55, 0x3, 0x55, 
       0x3, 0x55, 0x3, 0x55, 0x5, 0x55, 0x404, 0xa, 0x55, 0x3, 0x55, 0x3, 
       0x55, 0x3, 0x55, 0x3, 0x55, 0x3, 0x55, 0x3, 0x55, 0x5, 0x55, 0x40c, 
       0xa, 0x55, 0x3, 0x55, 0x3, 0x55, 0x3, 0x55, 0x3, 0x55, 0x3, 0x55, 
       0x3, 0x55, 0x3, 0x55, 0x3, 0x55, 0x5, 0x55, 0x416, 0xa, 0x55, 0x3, 
       0x55, 0x3, 0x55, 0x5, 0x55, 0x41a, 0xa, 0x55, 0x3, 0x56, 0x3, 0x56, 
       0x3, 0x56, 0x7, 0x56, 0x41f, 0xa, 0x56, 0xc, 0x56, 0xe, 0x56, 0x422, 
       0xb, 0x56, 0x3, 0x57, 0x3, 0x57, 0x3, 0x57, 0x7, 0x57, 0x427, 0xa, 
       0x57, 0xc, 0x57, 0xe, 0x57, 0x42a, 0xb, 0x57, 0x3, 0x58, 0x3, 0x58, 
       0x3, 0x58, 0x3, 0x58, 0x3, 0x59, 0x3, 0x59, 0x3, 0x59, 0x3, 0x59, 
       0x3, 0x59, 0x3, 0x59, 0x5, 0x59, 0x436, 0xa, 0x59, 0x3, 0x59, 0x5, 
       0x59, 0x439, 0xa, 0x59, 0x3, 0x5a, 0x3, 0x5a, 0x5, 0x5a, 0x43d, 0xa, 
       0x5a, 0x3, 0x5b, 0x3, 0x5b, 0x5, 0x5b, 0x441, 0xa, 0x5b, 0x3, 0x5b, 
       0x3, 0x5b, 0x3, 0x5b, 0x3, 0x5c, 0x3, 0x5c, 0x5, 0x5c, 0x448, 0xa, 
       0x5c, 0x3, 0x5c, 0x3, 0x5c, 0x3, 0x5c, 0x3, 0x5d, 0x3, 0x5d, 0x3, 
       0x5d, 0x7, 0x5d, 0x450, 0xa, 0x5d, 0xc, 0x5d, 0xe, 0x5d, 0x453, 0xb, 
       0x5d, 0x3, 0x5e, 0x3, 0x5e, 0x3, 0x5e, 0x7, 0x5e, 0x458, 0xa, 0x5e, 
       0xc, 0x5e, 0xe, 0x5e, 0x45b, 0xb, 0x5e, 0x3, 0x5f, 0x3, 0x5f, 0x3, 
       0x5f, 0x5, 0x5f, 0x460, 0xa, 0x5f, 0x3, 0x60, 0x3, 0x60, 0x3, 0x60, 
       0x3, 0x60, 0x7, 0x60, 0x466, 0xa, 0x60, 0xc, 0x60, 0xe, 0x60, 0x469, 
       0xb, 0x60, 0x3, 0x61, 0x3, 0x61, 0x3, 0x61, 0x3, 0x61, 0x3, 0x61, 
       0x3, 0x61, 0x3, 0x61, 0x3, 0x61, 0x3, 0x61, 0x3, 0x61, 0x3, 0x61, 
       0x3, 0x61, 0x3, 0x61, 0x5, 0x61, 0x478, 0xa, 0x61, 0x3, 0x62, 0x3, 
       0x62, 0x3, 0x62, 0x3, 0x63, 0x3, 0x63, 0x3, 0x63, 0x6, 0x63, 0x480, 
       0xa, 0x63, 0xd, 0x63, 0xe, 0x63, 0x481, 0x3, 0x63, 0x5, 0x63, 0x485, 
       0xa, 0x63, 0x3, 0x63, 0x3, 0x63, 0x3, 0x63, 0x3, 0x63, 0x3, 0x63, 
       0x3, 0x63, 0x3, 0x63, 0x3, 0x63, 0x3, 0x63, 0x3, 0x63, 0x3, 0x63, 
       0x3, 0x63, 0x3, 0x63, 0x3, 0x63, 0x3, 0x63, 0x3, 0x63, 0x3, 0x63, 
       0x3, 0x63, 0x3, 0x63, 0x3, 0x63, 0x3, 0x63, 0x7, 0x63, 0x49c, 0xa, 
       0x63, 0xc, 0x63, 0xe, 0x63, 0x49f, 0xb, 0x63, 0x3, 0x64, 0x5, 0x64, 
       0x4a2, 0xa, 0x64, 0x3, 0x64, 0x3, 0x64, 0x7, 0x64, 0x4a6, 0xa, 0x64, 
       0xc, 0x64, 0xe, 0x64, 0x4a9, 0xb, 0x64, 0x3, 0x65, 0x3, 0x65, 0x3, 
       0x65, 0x5, 0x65, 0x4ae, 0xa, 0x65, 0x3, 0x65, 0x3, 0x65, 0x3, 0x65, 
       0x5, 0x65, 0x4b3, 0xa, 0x65, 0x3, 0x65, 0x3, 0x65, 0x3, 0x65, 0x5, 
       0x65, 0x4b8, 0xa, 0x65, 0x3, 0x65, 0x3, 0x65, 0x3, 0x65, 0x3, 0x65, 
       0x6, 0x65, 0x4be, 0xa, 0x65, 0xd, 0x65, 0xe, 0x65, 0x4bf, 0x3, 0x65, 
       0x3, 0x65, 0x3, 0x65, 0x3, 0x65, 0x5, 0x65, 0x4c6, 0xa, 0x65, 0x3, 
       0x66, 0x3, 0x66, 0x3, 0x67, 0x3, 0x67, 0x5, 0x67, 0x4cc, 0xa, 0x67, 
       0x3, 0x67, 0x3, 0x67, 0x3, 0x67, 0x3, 0x67, 0x5, 0x67, 0x4d2, 0xa, 
       0x67, 0x7, 0x67, 0x4d4, 0xa, 0x67, 0xc, 0x67, 0xe, 0x67, 0x4d7, 0xb, 
       0x67, 0x3, 0x67, 0x5, 0x67, 0x4da, 0xa, 0x67, 0x5, 0x67, 0x4dc, 0xa, 
       0x67, 0x3, 0x68, 0x3, 0x68, 0x5, 0x68, 0x4e0, 0xa, 0x68, 0x3, 0x68, 
       0x3, 0x68, 0x3, 0x68, 0x3, 0x68, 0x3, 0x68, 0x3, 0x68, 0x3, 0x68, 
       0x5, 0x68, 0x4e9, 0xa, 0x68, 0x3, 0x69, 0x3, 0x69, 0x3, 0x69, 0x7, 
       0x69, 0x4ee, 0xa, 0x69, 0xc, 0x69, 0xe, 0x69, 0x4f1, 0xb, 0x69, 0x3, 
       0x69, 0x5, 0x69, 0x4f4, 0xa, 0x69, 0x3, 0x6a, 0x3, 0x6a, 0x5, 0x6a, 
       0x4f8, 0xa, 0x6a, 0x3, 0x6a, 0x3, 0x6a, 0x5, 0x6a, 0x4fc, 0xa, 0x6a, 
       0x3, 0x6a, 0x5, 0x6a, 0x4ff, 0xa, 0x6a, 0x5, 0x6a, 0x501, 0xa, 0x6a, 
       0x3, 0x6b, 0x3, 0x6b, 0x5, 0x6b, 0x505, 0xa, 0x6b, 0x3, 0x6c, 0x3, 
       0x6c, 0x5, 0x6c, 0x509, 0xa, 0x6c, 0x3, 0x6c, 0x3, 0x6c, 0x3, 0x6c, 
       0x5, 0x6c, 0x50e, 0xa, 0x6c, 0x7, 0x6c, 0x510, 0xa, 0x6c, 0xc, 0x6c, 
       0xe, 0x6c, 0x513, 0xb, 0x6c, 0x3, 0x6c, 0x5, 0x6c, 0x516, 0xa, 0x6c, 
       0x3, 0x6d, 0x3, 0x6d, 0x3, 0x6d, 0x7, 0x6d, 0x51b, 0xa, 0x6d, 0xc, 
       0x6d, 0xe, 0x6d, 0x51e, 0xb, 0x6d, 0x3, 0x6d, 0x5, 0x6d, 0x521, 0xa, 
       0x6d, 0x3, 0x6e, 0x3, 0x6e, 0x3, 0x6e, 0x3, 0x6e, 0x3, 0x6e, 0x3, 
       0x6e, 0x5, 0x6e, 0x529, 0xa, 0x6e, 0x3, 0x6e, 0x3, 0x6e, 0x3, 0x6e, 
       0x3, 0x6e, 0x3, 0x6e, 0x3, 0x6e, 0x3, 0x6e, 0x3, 0x6e, 0x5, 0x6e, 
       0x533, 0xa, 0x6e, 0x7, 0x6e, 0x535, 0xa, 0x6e, 0xc, 0x6e, 0xe, 0x6e, 
       0x538, 0xb, 0x6e, 0x3, 0x6e, 0x5, 0x6e, 0x53b, 0xa, 0x6e, 0x5, 0x6e, 
       0x53d, 0xa, 0x6e, 0x3, 0x6e, 0x3, 0x6e, 0x5, 0x6e, 0x541, 0xa, 0x6e, 
       0x3, 0x6e, 0x3, 0x6e, 0x3, 0x6e, 0x3, 0x6e, 0x5, 0x6e, 0x547, 0xa, 
       0x6e, 0x7, 0x6e, 0x549, 0xa, 0x6e, 0xc, 0x6e, 0xe, 0x6e, 0x54c, 0xb, 
       0x6e, 0x3, 0x6e, 0x5, 0x6e, 0x54f, 0xa, 0x6e, 0x5, 0x6e, 0x551, 0xa, 
       0x6e, 0x5, 0x6e, 0x553, 0xa, 0x6e, 0x3, 0x6f, 0x3, 0x6f, 0x3, 0x6f, 
       0x3, 0x6f, 0x5, 0x6f, 0x559, 0xa, 0x6f, 0x3, 0x6f, 0x5, 0x6f, 0x55c, 
       0xa, 0x6f, 0x3, 0x6f, 0x3, 0x6f, 0x3, 0x6f, 0x3, 0x70, 0x3, 0x70, 
       0x3, 0x70, 0x7, 0x70, 0x564, 0xa, 0x70, 0xc, 0x70, 0xe, 0x70, 0x567, 
       0xb, 0x70, 0x3, 0x70, 0x5, 0x70, 0x56a, 0xa, 0x70, 0x3, 0x71, 0x3, 
       0x71, 0x5, 0x71, 0x56e, 0xa, 0x71, 0x3, 0x71, 0x3, 0x71, 0x3, 0x71, 
       0x3, 0x71, 0x3, 0x71, 0x3, 0x71, 0x3, 0x71, 0x3, 0x71, 0x5, 0x71, 
       0x578, 0xa, 0x71, 0x3, 0x72, 0x3, 0x72, 0x5, 0x72, 0x57c, 0xa, 0x72, 
       0x3, 0x73, 0x5, 0x73, 0x57f, 0xa, 0x73, 0x3, 0x73, 0x3, 0x73, 0x3, 
       0x73, 0x3, 0x73, 0x3, 0x73, 0x5, 0x73, 0x586, 0xa, 0x73, 0x3, 0x74, 
       0x3, 0x74, 0x3, 0x74, 0x5, 0x74, 0x58b, 0xa, 0x74, 0x3, 0x75, 0x3, 
       0x75, 0x3, 0x76, 0x3, 0x76, 0x5, 0x76, 0x591, 0xa, 0x76, 0x3, 0x77, 
       0x3, 0x77, 0x3, 0x77, 0x5, 0x77, 0x596, 0xa, 0x77, 0x3, 0x78, 0x6, 
       0x78, 0x599, 0xa, 0x78, 0xd, 0x78, 0xe, 0x78, 0x59a, 0x3, 0x78, 0x2, 
       0x3, 0xc4, 0x79, 0x2, 0x4, 0x6, 0x8, 0xa, 0xc, 0xe, 0x10, 0x12, 0x14, 
       0x16, 0x18, 0x1a, 0x1c, 0x1e, 0x20, 0x22, 0x24, 0x26, 0x28, 0x2a, 
       0x2c, 0x2e, 0x30, 0x32, 0x34, 0x36, 0x38, 0x3a, 0x3c, 0x3e, 0x40, 
       0x42, 0x44, 0x46, 0x48, 0x4a, 0x4c, 0x4e, 0x50, 0x52, 0x54, 0x56, 
       0x58, 0x5a, 0x5c, 0x5e, 0x60, 0x62, 0x64, 0x66, 0x68, 0x6a, 0x6c, 
       0x6e, 0x70, 0x72, 0x74, 0x76, 0x78, 0x7a, 0x7c, 0x7e, 0x80, 0x82, 
       0x84, 0x86, 0x88, 0x8a, 0x8c, 0x8e, 0x90, 0x92, 0x94, 0x96, 0x98, 
       0x9a, 0x9c, 0x9e, 0xa0, 0xa2, 0xa4, 0xa6, 0xa8, 0xaa, 0xac, 0xae, 
       0xb0, 0xb2, 0xb4, 0xb6, 0xb8, 0xba, 0xbc, 0xbe, 0xc0, 0xc2, 0xc4, 
       0xc6, 0xc8, 0xca, 0xcc, 0xce, 0xd0, 0xd2, 0xd4, 0xd6, 0xd8, 0xda, 
       0xdc, 0xde, 0xe0, 0xe2, 0xe4, 0xe6, 0xe8, 0xea, 0xec, 0xee, 0x2, 
       0x9, 0x3, 0x2, 0x5a, 0x66, 0x3, 0x2, 0x38, 0x39, 0x4, 0x2, 0x49, 
       0x4a, 0x4e, 0x4e, 0x5, 0x2, 0x3a, 0x3a, 0x4b, 0x4d, 0x58, 0x58, 0x3, 
       0x2, 0x49, 0x4a, 0x3, 0x2, 0x47, 0x48, 0x5, 0x2, 0x20, 0x20, 0x2a, 
       0x2a, 0x2f, 0x2f, 0x2, 0x634, 0x2, 0xf5, 0x3, 0x2, 0x2, 0x2, 0x4, 
       0xfb, 0x3, 0x2, 0x2, 0x2, 0x6, 0x100, 0x3, 0x2, 0x2, 0x2, 0x8, 0x109, 
       0x3, 0x2, 0x2, 0x2, 0xa, 0x115, 0x3, 0x2, 0x2, 0x2, 0xc, 0x119, 0x3, 
       0x2, 0x2, 0x2, 0xe, 0x11f, 0x3, 0x2, 0x2, 0x2, 0x10, 0x122, 0x3, 
       0x2, 0x2, 0x2, 0x12, 0x12c, 0x3, 0x2, 0x2, 0x2, 0x14, 0x183, 0x3, 
       0x2, 0x2, 0x2, 0x16, 0x185, 0x3, 0x2, 0x2, 0x2, 0x18, 0x1db, 0x3, 
       0x2, 0x2, 0x2, 0x1a, 0x1dd, 0x3, 0x2, 0x2, 0x2, 0x1c, 0x1e1, 0x3, 
       0x2, 0x2, 0x2, 0x1e, 0x1e3, 0x3, 0x2, 0x2, 0x2, 0x20, 0x1f8, 0x3, 
       0x2, 0x2, 0x2, 0x22, 0x1fa, 0x3, 0x2, 0x2, 0x2, 0x24, 0x20d, 0x3, 
       0x2, 0x2, 0x2, 0x26, 0x215, 0x3, 0x2, 0x2, 0x2, 0x28, 0x224, 0x3, 
       0x2, 0x2, 0x2, 0x2a, 0x226, 0x3, 0x2, 0x2, 0x2, 0x2c, 0x229, 0x3, 
       0x2, 0x2, 0x2, 0x2e, 0x230, 0x3, 0x2, 0x2, 0x2, 0x30, 0x232, 0x3, 
       0x2, 0x2, 0x2, 0x32, 0x234, 0x3, 0x2, 0x2, 0x2, 0x34, 0x236, 0x3, 
       0x2, 0x2, 0x2, 0x36, 0x23a, 0x3, 0x2, 0x2, 0x2, 0x38, 0x23c, 0x3, 
       0x2, 0x2, 0x2, 0x3a, 0x246, 0x3, 0x2, 0x2, 0x2, 0x3c, 0x248, 0x3, 
       0x2, 0x2, 0x2, 0x3e, 0x24b, 0x3, 0x2, 0x2, 0x2, 0x40, 0x263, 0x3, 
       0x2, 0x2, 0x2, 0x42, 0x268, 0x3, 0x2, 0x2, 0x2, 0x44, 0x26d, 0x3, 
       0x2, 0x2, 0x2, 0x46, 0x278, 0x3, 0x2, 0x2, 0x2, 0x48, 0x280, 0x3, 
       0x2, 0x2, 0x2, 0x4a, 0x288, 0x3, 0x2, 0x2, 0x2, 0x4c, 0x291, 0x3, 
       0x2, 0x2, 0x2, 0x4e, 0x29a, 0x3, 0x2, 0x2, 0x2, 0x50, 0x2aa, 0x3, 
       0x2, 0x2, 0x2, 0x52, 0x2ac, 0x3, 0x2, 0x2, 0x2, 0x54, 0x2b2, 0x3, 
       0x2, 0x2, 0x2, 0x56, 0x2c5, 0x3, 0x2, 0x2, 0x2, 0x58, 0x2ce, 0x3, 
       0x2, 0x2, 0x2, 0x5a, 0x2d9, 0x3, 0x2, 0x2, 0x2, 0x5c, 0x2f3, 0x3, 
       0x2, 0x2, 0x2, 0x5e, 0x2ff, 0x3, 0x2, 0x2, 0x2, 0x60, 0x304, 0x3, 
       0x2, 0x2, 0x2, 0x62, 0x316, 0x3, 0x2, 0x2, 0x2, 0x64, 0x318, 0x3, 
       0x2, 0x2, 0x2, 0x66, 0x32a, 0x3, 0x2, 0x2, 0x2, 0x68, 0x32c, 0x3, 
       0x2, 0x2, 0x2, 0x6a, 0x338, 0x3, 0x2, 0x2, 0x2, 0x6c, 0x33a, 0x3, 
       0x2, 0x2, 0x2, 0x6e, 0x342, 0x3, 0x2, 0x2, 0x2, 0x70, 0x347, 0x3, 
       0x2, 0x2, 0x2, 0x72, 0x34b, 0x3, 0x2, 0x2, 0x2, 0x74, 0x34d, 0x3, 
       0x2, 0x2, 0x2, 0x76, 0x351, 0x3, 0x2, 0x2, 0x2, 0x78, 0x361, 0x3, 
       0x2, 0x2, 0x2, 0x7a, 0x36b, 0x3, 0x2, 0x2, 0x2, 0x7c, 0x375, 0x3, 
       0x2, 0x2, 0x2, 0x7e, 0x37f, 0x3, 0x2, 0x2, 0x2, 0x80, 0x384, 0x3, 
       0x2, 0x2, 0x2, 0x82, 0x389, 0x3, 0x2, 0x2, 0x2, 0x84, 0x38b, 0x3, 
       0x2, 0x2, 0x2, 0x86, 0x38d, 0x3, 0x2, 0x2, 0x2, 0x88, 0x38f, 0x3, 
       0x2, 0x2, 0x2, 0x8a, 0x391, 0x3, 0x2, 0x2, 0x2, 0x8c, 0x394, 0x3, 
       0x2, 0x2, 0x2, 0x8e, 0x396, 0x3, 0x2, 0x2, 0x2, 0x90, 0x399, 0x3, 
       0x2, 0x2, 0x2, 0x92, 0x3a2, 0x3, 0x2, 0x2, 0x2, 0x94, 0x3a4, 0x3, 
       0x2, 0x2, 0x2, 0x96, 0x3b2, 0x3, 0x2, 0x2, 0x2, 0x98, 0x3b4, 0x3, 
       0x2, 0x2, 0x2, 0x9a, 0x3b9, 0x3, 0x2, 0x2, 0x2, 0x9c, 0x3c6, 0x3, 
       0x2, 0x2, 0x2, 0x9e, 0x3cc, 0x3, 0x2, 0x2, 0x2, 0xa0, 0x3e7, 0x3, 
       0x2, 0x2, 0x2, 0xa2, 0x3e9, 0x3, 0x2, 0x2, 0x2, 0xa4, 0x3f3, 0x3, 
       0x2, 0x2, 0x2, 0xa6, 0x3f8, 0x3, 0x2, 0x2, 0x2, 0xa8, 0x419, 0x3, 
       0x2, 0x2, 0x2, 0xaa, 0x41b, 0x3, 0x2, 0x2, 0x2, 0xac, 0x423, 0x3, 
       0x2, 0x2, 0x2, 0xae, 0x42b, 0x3, 0x2, 0x2, 0x2, 0xb0, 0x438, 0x3, 
       0x2, 0x2, 0x2, 0xb2, 0x43c, 0x3, 0x2, 0x2, 0x2, 0xb4, 0x43e, 0x3, 
       0x2, 0x2, 0x2, 0xb6, 0x445, 0x3, 0x2, 0x2, 0x2, 0xb8, 0x44c, 0x3, 
       0x2, 0x2, 0x2, 0xba, 0x454, 0x3, 0x2, 0x2, 0x2, 0xbc, 0x45f, 0x3, 
       0x2, 0x2, 0x2, 0xbe, 0x461, 0x3, 0x2, 0x2, 0x2, 0xc0, 0x477, 0x3, 
       0x2, 0x2, 0x2, 0xc2, 0x479, 0x3, 0x2, 0x2, 0x2, 0xc4, 0x484, 0x3, 
       0x2, 0x2, 0x2, 0xc6, 0x4a1, 0x3, 0x2, 0x2, 0x2, 0xc8, 0x4c5, 0x3, 
       0x2, 0x2, 0x2, 0xca, 0x4c7, 0x3, 0x2, 0x2, 0x2, 0xcc, 0x4cb, 0x3, 
       0x2, 0x2, 0x2, 0xce, 0x4e8, 0x3, 0x2, 0x2, 0x2, 0xd0, 0x4ea, 0x3, 
       0x2, 0x2, 0x2, 0xd2, 0x500, 0x3, 0x2, 0x2, 0x2, 0xd4, 0x502, 0x3, 
       0x2, 0x2, 0x2, 0xd6, 0x508, 0x3, 0x2, 0x2, 0x2, 0xd8, 0x517, 0x3, 
       0x2, 0x2, 0x2, 0xda, 0x552, 0x3, 0x2, 0x2, 0x2, 0xdc, 0x554, 0x3, 
       0x2, 0x2, 0x2, 0xde, 0x560, 0x3, 0x2, 0x2, 0x2, 0xe0, 0x577, 0x3, 
       0x2, 0x2, 0x2, 0xe2, 0x57b, 0x3, 0x2, 0x2, 0x2, 0xe4, 0x57e, 0x3, 
       0x2, 0x2, 0x2, 0xe6, 0x587, 0x3, 0x2, 0x2, 0x2, 0xe8, 0x58c, 0x3, 
       0x2, 0x2, 0x2, 0xea, 0x58e, 0x3, 0x2, 0x2, 0x2, 0xec, 0x595, 0x3, 
       0x2, 0x2, 0x2, 0xee, 0x598, 0x3, 0x2, 0x2, 0x2, 0xf0, 0xf6, 0x7, 
       0x2e, 0x2, 0x2, 0xf1, 0xf6, 0x5, 0x1e, 0x10, 0x2, 0xf2, 0xf3, 0x5, 
       0x50, 0x29, 0x2, 0xf3, 0xf4, 0x7, 0x2e, 0x2, 0x2, 0xf4, 0xf6, 0x3, 
       0x2, 0x2, 0x2, 0xf5, 0xf0, 0x3, 0x2, 0x2, 0x2, 0xf5, 0xf1, 0x3, 0x2, 
       0x2, 0x2, 0xf5, 0xf2, 0x3, 0x2, 0x2, 0x2, 0xf6, 0x3, 0x3, 0x2, 0x2, 
       0x2, 0xf7, 0xfa, 0x7, 0x2e, 0x2, 0x2, 0xf8, 0xfa, 0x5, 0x1c, 0xf, 
       0x2, 0xf9, 0xf7, 0x3, 0x2, 0x2, 0x2, 0xf9, 0xf8, 0x3, 0x2, 0x2, 0x2, 
       0xfa, 0xfd, 0x3, 0x2, 0x2, 0x2, 0xfb, 0xf9, 0x3, 0x2, 0x2, 0x2, 0xfb, 
       0xfc, 0x3, 0x2, 0x2, 0x2, 0xfc, 0xfe, 0x3, 0x2, 0x2, 0x2, 0xfd, 0xfb, 
       0x3, 0x2, 0x2, 0x2, 0xfe, 0xff, 0x7, 0x2, 0x2, 0x3, 0xff, 0x5, 0x3, 
       0x2, 0x2, 0x2, 0x100, 0x104, 0x5, 0xd8, 0x6d, 0x2, 0x101, 0x103, 
       0x7, 0x2e, 0x2, 0x2, 0x102, 0x101, 0x3, 0x2, 0x2, 0x2, 0x103, 0x106, 
       0x3, 0x2, 0x2, 0x2, 0x104, 0x102, 0x3, 0x2, 0x2, 0x2, 0x104, 0x105, 
       0x3, 0x2, 0x2, 0x2, 0x105, 0x107, 0x3, 0x2, 0x2, 0x2, 0x106, 0x104, 
       0x3, 0x2, 0x2, 0x2, 0x107, 0x108, 0x7, 0x2, 0x2, 0x3, 0x108, 0x7, 
       0x3, 0x2, 0x2, 0x2, 0x109, 0x10a, 0x7, 0x58, 0x2, 0x2, 0x10a, 0x110, 
       0x5, 0x48, 0x25, 0x2, 0x10b, 0x10d, 0x7, 0x3b, 0x2, 0x2, 0x10c, 0x10e, 
       0x5, 0xde, 0x70, 0x2, 0x10d, 0x10c, 0x3, 0x2, 0x2, 0x2, 0x10d, 0x10e, 
       0x3, 0x2, 0x2, 0x2, 0x10e, 0x10f, 0x3, 0x2, 0x2, 0x2, 0x10f, 0x111, 
       0x7, 0x3c, 0x2, 0x2, 0x110, 0x10b, 0x3, 0x2, 0x2, 0x2, 0x110, 0x111, 
       0x3, 0x2, 0x2, 0x2, 0x111, 0x112, 0x3, 0x2, 0x2, 0x2, 0x112, 0x113, 
       0x7, 0x2e, 0x2, 0x2, 0x113, 0x9, 0x3, 0x2, 0x2, 0x2, 0x114, 0x116, 
       0x5, 0x8, 0x5, 0x2, 0x115, 0x114, 0x3, 0x2, 0x2, 0x2, 0x116, 0x117, 
       0x3, 0x2, 0x2, 0x2, 0x117, 0x115, 0x3, 0x2, 0x2, 0x2, 0x117, 0x118, 
       0x3, 0x2, 0x2, 0x2, 0x118, 0xb, 0x3, 0x2, 0x2, 0x2, 0x119, 0x11d, 
       0x5, 0xa, 0x6, 0x2, 0x11a, 0x11e, 0x5, 0xdc, 0x6f, 0x2, 0x11b, 0x11e, 
       0x5, 0x10, 0x9, 0x2, 0x11c, 0x11e, 0x5, 0xe, 0x8, 0x2, 0x11d, 0x11a, 
       0x3, 0x2, 0x2, 0x2, 0x11d, 0x11b, 0x3, 0x2, 0x2, 0x2, 0x11d, 0x11c, 
       0x3, 0x2, 0x2, 0x2, 0x11e, 0xd, 0x3, 0x2, 0x2, 0x2, 0x11f, 0x120, 
       0x7, 0xb, 0x2, 0x2, 0x120, 0x121, 0x5, 0x10, 0x9, 0x2, 0x121, 0xf, 
       0x3, 0x2, 0x2, 0x2, 0x122, 0x123, 0x7, 0x11, 0x2, 0x2, 0x123, 0x124, 
       0x5, 0xca, 0x66, 0x2, 0x124, 0x127, 0x5, 0x12, 0xa, 0x2, 0x125, 0x126, 
       0x7, 0x59, 0x2, 0x2, 0x126, 0x128, 0x5, 0xb0, 0x59, 0x2, 0x127, 0x125, 
       0x3, 0x2, 0x2, 0x2, 0x127, 0x128, 0x3, 0x2, 0x2, 0x2, 0x128, 0x129, 
       0x3, 0x2, 0x2, 0x2, 0x129, 0x12a, 0x7, 0x3e, 0x2, 0x2, 0x12a, 0x12b, 
       0x5, 0x62, 0x32, 0x2, 0x12b, 0x11, 0x3, 0x2, 0x2, 0x2, 0x12c, 0x12e, 
       0x7, 0x3b, 0x2, 0x2, 0x12d, 0x12f, 0x5, 0x14, 0xb, 0x2, 0x12e, 0x12d, 
       0x3, 0x2, 0x2, 0x2, 0x12e, 0x12f, 0x3, 0x2, 0x2, 0x2, 0x12f, 0x130, 
       0x3, 0x2, 0x2, 0x2, 0x130, 0x131, 0x7, 0x3c, 0x2, 0x2, 0x131, 0x13, 
       0x3, 0x2, 0x2, 0x2, 0x132, 0x135, 0x5, 0x16, 0xc, 0x2, 0x133, 0x134, 
       0x7, 0x41, 0x2, 0x2, 0x134, 0x136, 0x5, 0xb0, 0x59, 0x2, 0x135, 0x133, 
       0x3, 0x2, 0x2, 0x2, 0x135, 0x136, 0x3, 0x2, 0x2, 0x2, 0x136, 0x13f, 
       0x3, 0x2, 0x2, 0x2, 0x137, 0x138, 0x7, 0x3d, 0x2, 0x2, 0x138, 0x13b, 
       0x5, 0x16, 0xc, 0x2, 0x139, 0x13a, 0x7, 0x41, 0x2, 0x2, 0x13a, 0x13c, 
       0x5, 0xb0, 0x59, 0x2, 0x13b, 0x139, 0x3, 0x2, 0x2, 0x2, 0x13b, 0x13c, 
       0x3, 0x2, 0x2, 0x2, 0x13c, 0x13e, 0x3, 0x2, 0x2, 0x2, 0x13d, 0x137, 
       0x3, 0x2, 0x2, 0x2, 0x13e, 0x141, 0x3, 0x2, 0x2, 0x2, 0x13f, 0x13d, 
       0x3, 0x2, 0x2, 0x2, 0x13f, 0x140, 0x3, 0x2, 0x2, 0x2, 0x140, 0x163, 
       0x3, 0x2, 0x2, 0x2, 0x141, 0x13f, 0x3, 0x2, 0x2, 0x2, 0x142, 0x161, 
       0x7, 0x3d, 0x2, 0x2, 0x143, 0x145, 0x7, 0x3a, 0x2, 0x2, 0x144, 0x146, 
       0x5, 0x16, 0xc, 0x2, 0x145, 0x144, 0x3, 0x2, 0x2, 0x2, 0x145, 0x146, 
       0x3, 0x2, 0x2, 0x2, 0x146, 0x14f, 0x3, 0x2, 0x2, 0x2, 0x147, 0x148, 
       0x7, 0x3d, 0x2, 0x2, 0x148, 0x14b, 0x5, 0x16, 0xc, 0x2, 0x149, 0x14a, 
       0x7, 0x41, 0x2, 0x2, 0x14a, 0x14c, 0x5, 0xb0, 0x59, 0x2, 0x14b, 0x149, 
       0x3, 0x2, 0x2, 0x2, 0x14b, 0x14c, 0x3, 0x2, 0x2, 0x2, 0x14c, 0x14e, 
       0x3, 0x2, 0x2, 0x2, 0x14d, 0x147, 0x3, 0x2, 0x2, 0x2, 0x14e, 0x151, 
       0x3, 0x2, 0x2, 0x2, 0x14f, 0x14d, 0x3, 0x2, 0x2, 0x2, 0x14f, 0x150, 
       0x3, 0x2, 0x2, 0x2, 0x150, 0x15a, 0x3, 0x2, 0x2, 0x2, 0x151, 0x14f, 
       0x3, 0x2, 0x2, 0x2, 0x152, 0x158, 0x7, 0x3d, 0x2, 0x2, 0x153, 0x154, 
       0x7, 0x40, 0x2, 0x2, 0x154, 0x156, 0x5, 0x16, 0xc, 0x2, 0x155, 0x157, 
       0x7, 0x3d, 0x2, 0x2, 0x156, 0x155, 0x3, 0x2, 0x2, 0x2, 0x156, 0x157, 
       0x3, 0x2, 0x2, 0x2, 0x157, 0x159, 0x3, 0x2, 0x2, 0x2, 0x158, 0x153, 
       0x3, 0x2, 0x2, 0x2, 0x158, 0x159, 0x3, 0x2, 0x2, 0x2, 0x159, 0x15b, 
       0x3, 0x2, 0x2, 0x2, 0x15a, 0x152, 0x3, 0x2, 0x2, 0x2, 0x15a, 0x15b, 
       0x3, 0x2, 0x2, 0x2, 0x15b, 0x162, 0x3, 0x2, 0x2, 0x2, 0x15c, 0x15d, 
       0x7, 0x40, 0x2, 0x2, 0x15d, 0x15f, 0x5, 0x16, 0xc, 0x2, 0x15e, 0x160, 
       0x7, 0x3d, 0x2, 0x2, 0x15f, 0x15e, 0x3, 0x2, 0x2, 0x2, 0x15f, 0x160, 
       0x3, 0x2, 0x2, 0x2, 0x160, 0x162, 0x3, 0x2, 0x2, 0x2, 0x161, 0x143, 
       0x3, 0x2, 0x2, 0x2, 0x161, 0x15c, 0x3, 0x2, 0x2, 0x2, 0x161, 0x162, 
       0x3, 0x2, 0x2, 0x2, 0x162, 0x164, 0x3, 0x2, 0x2, 0x2, 0x163, 0x142, 
       0x3, 0x2, 0x2, 0x2, 0x163, 0x164, 0x3, 0x2, 0x2, 0x2, 0x164, 0x184, 
       0x3, 0x2, 0x2, 0x2, 0x165, 0x167, 0x7, 0x3a, 0x2, 0x2, 0x166, 0x168, 
       0x5, 0x16, 0xc, 0x2, 0x167, 0x166, 0x3, 0x2, 0x2, 0x2, 0x167, 0x168, 
       0x3, 0x2, 0x2, 0x2, 0x168, 0x171, 0x3, 0x2, 0x2, 0x2, 0x169, 0x16a, 
       0x7, 0x3d, 0x2, 0x2, 0x16a, 0x16d, 0x5, 0x16, 0xc, 0x2, 0x16b, 0x16c, 
       0x7, 0x41, 0x2, 0x2, 0x16c, 0x16e, 0x5, 0xb0, 0x59, 0x2, 0x16d, 0x16b, 
       0x3, 0x2, 0x2, 0x2, 0x16d, 0x16e, 0x3, 0x2, 0x2, 0x2, 0x16e, 0x170, 
       0x3, 0x2, 0x2, 0x2, 0x16f, 0x169, 0x3, 0x2, 0x2, 0x2, 0x170, 0x173, 
       0x3, 0x2, 0x2, 0x2, 0x171, 0x16f, 0x3, 0x2, 0x2, 0x2, 0x171, 0x172, 
       0x3, 0x2, 0x2, 0x2, 0x172, 0x17c, 0x3, 0x2, 0x2, 0x2, 0x173, 0x171, 
       0x3, 0x2, 0x2, 0x2, 0x174, 0x17a, 0x7, 0x3d, 0x2, 0x2, 0x175, 0x176, 
       0x7, 0x40, 0x2, 0x2, 0x176, 0x178, 0x5, 0x16, 0xc, 0x2, 0x177, 0x179, 
       0x7, 0x3d, 0x2, 0x2, 0x178, 0x177, 0x3, 0x2, 0x2, 0x2, 0x178, 0x179, 
       0x3, 0x2, 0x2, 0x2, 0x179, 0x17b, 0x3, 0x2, 0x2, 0x2, 0x17a, 0x175, 
       0x3, 0x2, 0x2, 0x2, 0x17a, 0x17b, 0x3, 0x2, 0x2, 0x2, 0x17b, 0x17d, 
       0x3, 0x2, 0x2, 0x2, 0x17c, 0x174, 0x3, 0x2, 0x2, 0x2, 0x17c, 0x17d, 
       0x3, 0x2, 0x2, 0x2, 0x17d, 0x184, 0x3, 0x2, 0x2, 0x2, 0x17e, 0x17f, 
       0x7, 0x40, 0x2, 0x2, 0x17f, 0x181, 0x5, 0x16, 0xc, 0x2, 0x180, 0x182, 
       0x7, 0x3d, 0x2, 0x2, 0x181, 0x180, 0x3, 0x2, 0x2, 0x2, 0x181, 0x182, 
       0x3, 0x2, 0x2, 0x2, 0x182, 0x184, 0x3, 0x2, 0x2, 0x2, 0x183, 0x132, 
       0x3, 0x2, 0x2, 0x2, 0x183, 0x165, 0x3, 0x2, 0x2, 0x2, 0x183, 0x17e, 
       0x3, 0x2, 0x2, 0x2, 0x184, 0x15, 0x3, 0x2, 0x2, 0x2, 0x185, 0x188, 
       0x5, 0xca, 0x66, 0x2, 0x186, 0x187, 0x7, 0x3e, 0x2, 0x2, 0x187, 0x189, 
       0x5, 0xb0, 0x59, 0x2, 0x188, 0x186, 0x3, 0x2, 0x2, 0x2, 0x188, 0x189, 
       0x3, 0x2, 0x2, 0x2, 0x189, 0x17, 0x3, 0x2, 0x2, 0x2, 0x18a, 0x18d, 
       0x5, 0x1a, 0xe, 0x2, 0x18b, 0x18c, 0x7, 0x41, 0x2, 0x2, 0x18c, 0x18e, 
       0x5, 0xb0, 0x59, 0x2, 0x18d, 0x18b, 0x3, 0x2, 0x2, 0x2, 0x18d, 0x18e, 
       0x3, 0x2, 0x2, 0x2, 0x18e, 0x197, 0x3, 0x2, 0x2, 0x2, 0x18f, 0x190, 
       0x7, 0x3d, 0x2, 0x2, 0x190, 0x193, 0x5, 0x1a, 0xe, 0x2, 0x191, 0x192, 
       0x7, 0x41, 0x2, 0x2, 0x192, 0x194, 0x5, 0xb0, 0x59, 0x2, 0x193, 0x191, 
       0x3, 0x2, 0x2, 0x2, 0x193, 0x194, 0x3, 0x2, 0x2, 0x2, 0x194, 0x196, 
       0x3, 0x2, 0x2, 0x2, 0x195, 0x18f, 0x3, 0x2, 0x2, 0x2, 0x196, 0x199, 
       0x3, 0x2, 0x2, 0x2, 0x197, 0x195, 0x3, 0x2, 0x2, 0x2, 0x197, 0x198, 
       0x3, 0x2, 0x2, 0x2, 0x198, 0x1bb, 0x3, 0x2, 0x2, 0x2, 0x199, 0x197, 
       0x3, 0x2, 0x2, 0x2, 0x19a, 0x1b9, 0x7, 0x3d, 0x2, 0x2, 0x19b, 0x19d, 
       0x7, 0x3a, 0x2, 0x2, 0x19c, 0x19e, 0x5, 0x1a, 0xe, 0x2, 0x19d, 0x19c, 
       0x3, 0x2, 0x2, 0x2, 0x19d, 0x19e, 0x3, 0x2, 0x2, 0x2, 0x19e, 0x1a7, 
       0x3, 0x2, 0x2, 0x2, 0x19f, 0x1a0, 0x7, 0x3d, 0x2, 0x2, 0x1a0, 0x1a3, 
       0x5, 0x1a, 0xe, 0x2, 0x1a1, 0x1a2, 0x7, 0x41, 0x2, 0x2, 0x1a2, 0x1a4, 
       0x5, 0xb0, 0x59, 0x2, 0x1a3, 0x1a1, 0x3, 0x2, 0x2, 0x2, 0x1a3, 0x1a4, 
       0x3, 0x2, 0x2, 0x2, 0x1a4, 0x1a6, 0x3, 0x2, 0x2, 0x2, 0x1a5, 0x19f, 
       0x3, 0x2, 0x2, 0x2, 0x1a6, 0x1a9, 0x3, 0x2, 0x2, 0x2, 0x1a7, 0x1a5, 
       0x3, 0x2, 0x2, 0x2, 0x1a7, 0x1a8, 0x3, 0x2, 0x2, 0x2, 0x1a8, 0x1b2, 
       0x3, 0x2, 0x2, 0x2, 0x1a9, 0x1a7, 0x3, 0x2, 0x2, 0x2, 0x1aa, 0x1b0, 
       0x7, 0x3d, 0x2, 0x2, 0x1ab, 0x1ac, 0x7, 0x40, 0x2, 0x2, 0x1ac, 0x1ae, 
       0x5, 0x1a, 0xe, 0x2, 0x1ad, 0x1af, 0x7, 0x3d, 0x2, 0x2, 0x1ae, 0x1ad, 
       0x3, 0x2, 0x2, 0x2, 0x1ae, 0x1af, 0x3, 0x2, 0x2, 0x2, 0x1af, 0x1b1, 
       0x3, 0x2, 0x2, 0x2, 0x1b0, 0x1ab, 0x3, 0x2, 0x2, 0x2, 0x1b0, 0x1b1, 
       0x3, 0x2, 0x2, 0x2, 0x1b1, 0x1b3, 0x3, 0x2, 0x2, 0x2, 0x1b2, 0x1aa, 
       0x3, 0x2, 0x2, 0x2, 0x1b2, 0x1b3, 0x3, 0x2, 0x2, 0x2, 0x1b3, 0x1ba, 
       0x3, 0x2, 0x2, 0x2, 0x1b4, 0x1b5, 0x7, 0x40, 0x2, 0x2, 0x1b5, 0x1b7, 
       0x5, 0x1a, 0xe, 0x2, 0x1b6, 0x1b8, 0x7, 0x3d, 0x2, 0x2, 0x1b7, 0x1b6, 
       0x3, 0x2, 0x2, 0x2, 0x1b7, 0x1b8, 0x3, 0x2, 0x2, 0x2, 0x1b8, 0x1ba, 
       0x3, 0x2, 0x2, 0x2, 0x1b9, 0x19b, 0x3, 0x2, 0x2, 0x2, 0x1b9, 0x1b4, 
       0x3, 0x2, 0x2, 0x2, 0x1b9, 0x1ba, 0x3, 0x2, 0x2, 0x2, 0x1ba, 0x1bc, 
       0x3, 0x2, 0x2, 0x2, 0x1bb, 0x19a, 0x3, 0x2, 0x2, 0x2, 0x1bb, 0x1bc, 
       0x3, 0x2, 0x2, 0x2, 0x1bc, 0x1dc, 0x3, 0x2, 0x2, 0x2, 0x1bd, 0x1bf, 
       0x7, 0x3a, 0x2, 0x2, 0x1be, 0x1c0, 0x5, 0x1a, 0xe, 0x2, 0x1bf, 0x1be, 
       0x3, 0x2, 0x2, 0x2, 0x1bf, 0x1c0, 0x3, 0x2, 0x2, 0x2, 0x1c0, 0x1c9, 
       0x3, 0x2, 0x2, 0x2, 0x1c1, 0x1c2, 0x7, 0x3d, 0x2, 0x2, 0x1c2, 0x1c5, 
       0x5, 0x1a, 0xe, 0x2, 0x1c3, 0x1c4, 0x7, 0x41, 0x2, 0x2, 0x1c4, 0x1c6, 
       0x5, 0xb0, 0x59, 0x2, 0x1c5, 0x1c3, 0x3, 0x2, 0x2, 0x2, 0x1c5, 0x1c6, 
       0x3, 0x2, 0x2, 0x2, 0x1c6, 0x1c8, 0x3, 0x2, 0x2, 0x2, 0x1c7, 0x1c1, 
       0x3, 0x2, 0x2, 0x2, 0x1c8, 0x1cb, 0x3, 0x2, 0x2, 0x2, 0x1c9, 0x1c7, 
       0x3, 0x2, 0x2, 0x2, 0x1c9, 0x1ca, 0x3, 0x2, 0x2, 0x2, 0x1ca, 0x1d4, 
       0x3, 0x2, 0x2, 0x2, 0x1cb, 0x1c9, 0x3, 0x2, 0x2, 0x2, 0x1cc, 0x1d2, 
       0x7, 0x3d, 0x2, 0x2, 0x1cd, 0x1ce, 0x7, 0x40, 0x2, 0x2, 0x1ce, 0x1d0, 
       0x5, 0x1a, 0xe, 0x2, 0x1cf, 0x1d1, 0x7, 0x3d, 0x2, 0x2, 0x1d0, 0x1cf, 
       0x3, 0x2, 0x2, 0x2, 0x1d0, 0x1d1, 0x3, 0x2, 0x2, 0x2, 0x1d1, 0x1d3, 
       0x3, 0x2, 0x2, 0x2, 0x1d2, 0x1cd, 0x3, 0x2, 0x2, 0x2, 0x1d2, 0x1d3, 
       0x3, 0x2, 0x2, 0x2, 0x1d3, 0x1d5, 0x3, 0x2, 0x2, 0x2, 0x1d4, 0x1cc, 
       0x3, 0x2, 0x2, 0x2, 0x1d4, 0x1d5, 0x3, 0x2, 0x2, 0x2, 0x1d5, 0x1dc, 
       0x3, 0x2, 0x2, 0x2, 0x1d6, 0x1d7, 0x7, 0x40, 0x2, 0x2, 0x1d7, 0x1d9, 
       0x5, 0x1a, 0xe, 0x2, 0x1d8, 0x1da, 0x7, 0x3d, 0x2, 0x2, 0x1d9, 0x1d8, 
       0x3, 0x2, 0x2, 0x2, 0x1d9, 0x1da, 0x3, 0x2, 0x2, 0x2, 0x1da, 0x1dc, 
       0x3, 0x2, 0x2, 0x2, 0x1db, 0x18a, 0x3, 0x2, 0x2, 0x2, 0x1db, 0x1bd, 
       0x3, 0x2, 0x2, 0x2, 0x1db, 0x1d6, 0x3, 0x2, 0x2, 0x2, 0x1dc, 0x19, 
       0x3, 0x2, 0x2, 0x2, 0x1dd, 0x1de, 0x5, 0xca, 0x66, 0x2, 0x1de, 0x1b, 
       0x3, 0x2, 0x2, 0x2, 0x1df, 0x1e2, 0x5, 0x1e, 0x10, 0x2, 0x1e0, 0x1e2, 
       0x5, 0x50, 0x29, 0x2, 0x1e1, 0x1df, 0x3, 0x2, 0x2, 0x2, 0x1e1, 0x1e0, 
       0x3, 0x2, 0x2, 0x2, 0x1e2, 0x1d, 0x3, 0x2, 0x2, 0x2, 0x1e3, 0x1e8, 
       0x5, 0x20, 0x11, 0x2, 0x1e4, 0x1e5, 0x7, 0x3f, 0x2, 0x2, 0x1e5, 0x1e7, 
       0x5, 0x20, 0x11, 0x2, 0x1e6, 0x1e4, 0x3, 0x2, 0x2, 0x2, 0x1e7, 0x1ea, 
       0x3, 0x2, 0x2, 0x2, 0x1e8, 0x1e6, 0x3, 0x2, 0x2, 0x2, 0x1e8, 0x1e9, 
       0x3, 0x2, 0x2, 0x2, 0x1e9, 0x1ec, 0x3, 0x2, 0x2, 0x2, 0x1ea, 0x1e8, 
       0x3, 0x2, 0x2, 0x2, 0x1eb, 0x1ed, 0x7, 0x3f, 0x2, 0x2, 0x1ec, 0x1eb, 
       0x3, 0x2, 0x2, 0x2, 0x1ec, 0x1ed, 0x3, 0x2, 0x2, 0x2, 0x1ed, 0x1ee, 
       0x3, 0x2, 0x2, 0x2, 0x1ee, 0x1ef, 0x7, 0x2e, 0x2, 0x2, 0x1ef, 0x1f, 
       0x3, 0x2, 0x2, 0x2, 0x1f0, 0x1f9, 0x5, 0x22, 0x12, 0x2, 0x1f1, 0x1f9, 
       0x5, 0x2a, 0x16, 0x2, 0x1f2, 0x1f9, 0x5, 0x2c, 0x17, 0x2, 0x1f3, 
       0x1f9, 0x5, 0x2e, 0x18, 0x2, 0x1f4, 0x1f9, 0x5, 0x3a, 0x1e, 0x2, 
       0x1f5, 0x1f9, 0x5, 0x4a, 0x26, 0x2, 0x1f6, 0x1f9, 0x5, 0x4c, 0x27, 
       0x2, 0x1f7, 0x1f9, 0x5, 0x4e, 0x28, 0x2, 0x1f8, 0x1f0, 0x3, 0x2, 
       0x2, 0x2, 0x1f8, 0x1f1, 0x3, 0x2, 0x2, 0x2, 0x1f8, 0x1f2, 0x3, 0x2, 
       0x2, 0x2, 0x1f8, 0x1f3, 0x3, 0x2, 0x2, 0x2, 0x1f8, 0x1f4, 0x3, 0x2, 
       0x2, 0x2, 0x1f8, 0x1f5, 0x3, 0x2, 0x2, 0x2, 0x1f8, 0x1f6, 0x3, 0x2, 
       0x2, 0x2, 0x1f8, 0x1f7, 0x3, 0x2, 0x2, 0x2, 0x1f9, 0x21, 0x3, 0x2, 
       0x2, 0x2, 0x1fa, 0x20b, 0x5, 0x26, 0x14, 0x2, 0x1fb, 0x20c, 0x5, 
       0x24, 0x13, 0x2, 0x1fc, 0x1ff, 0x5, 0x28, 0x15, 0x2, 0x1fd, 0x200, 
       0x5, 0xea, 0x76, 0x2, 0x1fe, 0x200, 0x5, 0xd8, 0x6d, 0x2, 0x1ff, 
       0x1fd, 0x3, 0x2, 0x2, 0x2, 0x1ff, 0x1fe, 0x3, 0x2, 0x2, 0x2, 0x200, 
       0x20c, 0x3, 0x2, 0x2, 0x2, 0x201, 0x204, 0x7, 0x41, 0x2, 0x2, 0x202, 
       0x205, 0x5, 0xea, 0x76, 0x2, 0x203, 0x205, 0x5, 0x26, 0x14, 0x2, 
       0x204, 0x202, 0x3, 0x2, 0x2, 0x2, 0x204, 0x203, 0x3, 0x2, 0x2, 0x2, 
       0x205, 0x207, 0x3, 0x2, 0x2, 0x2, 0x206, 0x201, 0x3, 0x2, 0x2, 0x2, 
       0x207, 0x20a, 0x3, 0x2, 0x2, 0x2, 0x208, 0x206, 0x3, 0x2, 0x2, 0x2, 
       0x208, 0x209, 0x3, 0x2, 0x2, 0x2, 0x209, 0x20c, 0x3, 0x2, 0x2, 0x2, 
       0x20a, 0x208, 0x3, 0x2, 0x2, 0x2, 0x20b, 0x1fb, 0x3, 0x2, 0x2, 0x2, 
       0x20b, 0x1fc, 0x3, 0x2, 0x2, 0x2, 0x20b, 0x208, 0x3, 0x2, 0x2, 0x2, 
       0x20c, 0x23, 0x3, 0x2, 0x2, 0x2, 0x20d, 0x20e, 0x7, 0x3e, 0x2, 0x2, 
       0x20e, 0x211, 0x5, 0xb0, 0x59, 0x2, 0x20f, 0x210, 0x7, 0x41, 0x2, 
       0x2, 0x210, 0x212, 0x5, 0xb0, 0x59, 0x2, 0x211, 0x20f, 0x3, 0x2, 
       0x2, 0x2, 0x211, 0x212, 0x3, 0x2, 0x2, 0x2, 0x212, 0x25, 0x3, 0x2, 
       0x2, 0x2, 0x213, 0x216, 0x5, 0xb0, 0x59, 0x2, 0x214, 0x216, 0x5, 
       0xc2, 0x62, 0x2, 0x215, 0x213, 0x3, 0x2, 0x2, 0x2, 0x215, 0x214, 
       0x3, 0x2, 0x2, 0x2, 0x216, 0x21e, 0x3, 0x2, 0x2, 0x2, 0x217, 0x21a, 
       0x7, 0x3d, 0x2, 0x2, 0x218, 0x21b, 0x5, 0xb0, 0x59, 0x2, 0x219, 0x21b, 
       0x5, 0xc2, 0x62, 0x2, 0x21a, 0x218, 0x3, 0x2, 0x2, 0x2, 0x21a, 0x219, 
       0x3, 0x2, 0x2, 0x2, 0x21b, 0x21d, 0x3, 0x2, 0x2, 0x2, 0x21c, 0x217, 
       0x3, 0x2, 0x2, 0x2, 0x21d, 0x220, 0x3, 0x2, 0x2, 0x2, 0x21e, 0x21c, 
       0x3, 0x2, 0x2, 0x2, 0x21e, 0x21f, 0x3, 0x2, 0x2, 0x2, 0x21f, 0x222, 
       0x3, 0x2, 0x2, 0x2, 0x220, 0x21e, 0x3, 0x2, 0x2, 0x2, 0x221, 0x223, 
       0x7, 0x3d, 0x2, 0x2, 0x222, 0x221, 0x3, 0x2, 0x2, 0x2, 0x222, 0x223, 
       0x3, 0x2, 0x2, 0x2, 0x223, 0x27, 0x3, 0x2, 0x2, 0x2, 0x224, 0x225, 
       0x9, 0x2, 0x2, 0x2, 0x225, 0x29, 0x3, 0x2, 0x2, 0x2, 0x226, 0x227, 
       0x7, 0x12, 0x2, 0x2, 0x227, 0x228, 0x5, 0xd6, 0x6c, 0x2, 0x228, 0x2b, 
       0x3, 0x2, 0x2, 0x2, 0x229, 0x22a, 0x7, 0x25, 0x2, 0x2, 0x22a, 0x2d, 
       0x3, 0x2, 0x2, 0x2, 0x22b, 0x231, 0x5, 0x30, 0x19, 0x2, 0x22c, 0x231, 
       0x5, 0x32, 0x1a, 0x2, 0x22d, 0x231, 0x5, 0x34, 0x1b, 0x2, 0x22e, 
       0x231, 0x5, 0x38, 0x1d, 0x2, 0x22f, 0x231, 0x5, 0x36, 0x1c, 0x2, 
       0x230, 0x22b, 0x3, 0x2, 0x2, 0x2, 0x230, 0x22c, 0x3, 0x2, 0x2, 0x2, 
       0x230, 0x22d, 0x3, 0x2, 0x2, 0x2, 0x230, 0x22e, 0x3, 0x2, 0x2, 0x2, 
       0x230, 0x22f, 0x3, 0x2, 0x2, 0x2, 0x231, 0x2f, 0x3, 0x2, 0x2, 0x2, 
       0x232, 0x233, 0x7, 0xd, 0x2, 0x2, 0x233, 0x31, 0x3, 0x2, 0x2, 0x2, 
       0x234, 0x235, 0x7, 0x10, 0x2, 0x2, 0x235, 0x33, 0x3, 0x2, 0x2, 0x2, 
       0x236, 0x238, 0x7, 0x27, 0x2, 0x2, 0x237, 0x239, 0x5, 0xd8, 0x6d, 
       0x2, 0x238, 0x237, 0x3, 0x2, 0x2, 0x2, 0x238, 0x239, 0x3, 0x2, 0x2, 
       0x2, 0x239, 0x35, 0x3, 0x2, 0x2, 0x2, 0x23a, 0x23b, 0x5, 0xea, 0x76, 
       0x2, 0x23b, 0x37, 0x3, 0x2, 0x2, 0x2, 0x23c, 0x242, 0x7, 0x26, 0x2, 
       0x2, 0x23d, 0x240, 0x5, 0xb0, 0x59, 0x2, 0x23e, 0x23f, 0x7, 0x19, 
       0x2, 0x2, 0x23f, 0x241, 0x5, 0xb0, 0x59, 0x2, 0x240, 0x23e, 0x3, 
       0x2, 0x2, 0x2, 0x240, 0x241, 0x3, 0x2, 0x2, 0x2, 0x241, 0x243, 0x3, 
       0x2, 0x2, 0x2, 0x242, 0x23d, 0x3, 0x2, 0x2, 0x2, 0x242, 0x243, 0x3, 
       0x2, 0x2, 0x2, 0x243, 0x39, 0x3, 0x2, 0x2, 0x2, 0x244, 0x247, 0x5, 
       0x3c, 0x1f, 0x2, 0x245, 0x247, 0x5, 0x3e, 0x20, 0x2, 0x246, 0x244, 
       0x3, 0x2, 0x2, 0x2, 0x246, 0x245, 0x3, 0x2, 0x2, 0x2, 0x247, 0x3b, 
       0x3, 0x2, 0x2, 0x2, 0x248, 0x249, 0x7, 0x1c, 0x2, 0x2, 0x249, 0x24a, 
       0x5, 0x46, 0x24, 0x2, 0x24a, 0x3d, 0x3, 0x2, 0x2, 0x2, 0x24b, 0x258, 
       0x7, 0x19, 0x2, 0x2, 0x24c, 0x24e, 0x9, 0x3, 0x2, 0x2, 0x24d, 0x24c, 
       0x3, 0x2, 0x2, 0x2, 0x24e, 0x251, 0x3, 0x2, 0x2, 0x2, 0x24f, 0x24d, 
       0x3, 0x2, 0x2, 0x2, 0x24f, 0x250, 0x3, 0x2, 0x2, 0x2, 0x250, 0x252, 
       0x3, 0x2, 0x2, 0x2, 0x251, 0x24f, 0x3, 0x2, 0x2, 0x2, 0x252, 0x259, 
       0x5, 0x48, 0x25, 0x2, 0x253, 0x255, 0x9, 0x3, 0x2, 0x2, 0x254, 0x253, 
       0x3, 0x2, 0x2, 0x2, 0x255, 0x256, 0x3, 0x2, 0x2, 0x2, 0x256, 0x254, 
       0x3, 0x2, 0x2, 0x2, 0x256, 0x257, 0x3, 0x2, 0x2, 0x2, 0x257, 0x259, 
       0x3, 0x2, 0x2, 0x2, 0x258, 0x24f, 0x3, 0x2, 0x2, 0x2, 0x258, 0x254, 
       0x3, 0x2, 0x2, 0x2, 0x259, 0x25a, 0x3, 0x2, 0x2, 0x2, 0x25a, 0x261, 
       0x7, 0x1c, 0x2, 0x2, 0x25b, 0x262, 0x7, 0x3a, 0x2, 0x2, 0x25c, 0x25d, 
       0x7, 0x3b, 0x2, 0x2, 0x25d, 0x25e, 0x5, 0x44, 0x23, 0x2, 0x25e, 0x25f, 
       0x7, 0x3c, 0x2, 0x2, 0x25f, 0x262, 0x3, 0x2, 0x2, 0x2, 0x260, 0x262, 
       0x5, 0x44, 0x23, 0x2, 0x261, 0x25b, 0x3, 0x2, 0x2, 0x2, 0x261, 0x25c, 
       0x3, 0x2, 0x2, 0x2, 0x261, 0x260, 0x3, 0x2, 0x2, 0x2, 0x262, 0x3f, 
       0x3, 0x2, 0x2, 0x2, 0x263, 0x266, 0x5, 0xca, 0x66, 0x2, 0x264, 0x265, 
       0x7, 0x9, 0x2, 0x2, 0x265, 0x267, 0x5, 0xca, 0x66, 0x2, 0x266, 0x264, 
       0x3, 0x2, 0x2, 0x2, 0x266, 0x267, 0x3, 0x2, 0x2, 0x2, 0x267, 0x41, 
       0x3, 0x2, 0x2, 0x2, 0x268, 0x26b, 0x5, 0x48, 0x25, 0x2, 0x269, 0x26a, 
       0x7, 0x9, 0x2, 0x2, 0x26a, 0x26c, 0x5, 0xca, 0x66, 0x2, 0x26b, 0x269, 
       0x3, 0x2, 0x2, 0x2, 0x26b, 0x26c, 0x3, 0x2, 0x2, 0x2, 0x26c, 0x43, 
       0x3, 0x2, 0x2, 0x2, 0x26d, 0x272, 0x5, 0x40, 0x21, 0x2, 0x26e, 0x26f, 
       0x7, 0x3d, 0x2, 0x2, 0x26f, 0x271, 0x5, 0x40, 0x21, 0x2, 0x270, 0x26e, 
       0x3, 0x2, 0x2, 0x2, 0x271, 0x274, 0x3, 0x2, 0x2, 0x2, 0x272, 0x270, 
       0x3, 0x2, 0x2, 0x2, 0x272, 0x273, 0x3, 0x2, 0x2, 0x2, 0x273, 0x276, 
       0x3, 0x2, 0x2, 0x2, 0x274, 0x272, 0x3, 0x2, 0x2, 0x2, 0x275, 0x277, 
       0x7, 0x3d, 0x2, 0x2, 0x276, 0x275, 0x3, 0x2, 0x2, 0x2, 0x276, 0x277, 
       0x3, 0x2, 0x2, 0x2, 0x277, 0x45, 0x3, 0x2, 0x2, 0x2, 0x278, 0x27d, 
       0x5, 0x42, 0x22, 0x2, 0x279, 0x27a, 0x7, 0x3d, 0x2, 0x2, 0x27a, 0x27c, 
       0x5, 0x42, 0x22, 0x2, 0x27b, 0x279, 0x3, 0x2, 0x2, 0x2, 0x27c, 0x27f, 
       0x3, 0x2, 0x2, 0x2, 0x27d, 0x27b, 0x3, 0x2, 0x2, 0x2, 0x27d, 0x27e, 
       0x3, 0x2, 0x2, 0x2, 0x27e, 0x47, 0x3, 0x2, 0x2, 0x2, 0x27f, 0x27d, 
       0x3, 0x2, 0x2, 0x2, 0x280, 0x285, 0x5, 0xca, 0x66, 0x2, 0x281, 0x282, 
       0x7, 0x38, 0x2, 0x2, 0x282, 0x284, 0x5, 0xca, 0x66, 0x2, 0x283, 0x281, 
       0x3, 0x2, 0x2, 0x2, 0x284, 0x287, 0x3, 0x2, 0x2, 0x2, 0x285, 0x283, 
       0x3, 0x2, 0x2, 0x2, 0x285, 0x286, 0x3, 0x2, 0x2, 0x2, 0x286, 0x49, 
       0x3, 0x2, 0x2, 0x2, 0x287, 0x285, 0x3, 0x2, 0x2, 0x2, 0x288, 0x289, 
       0x7, 0x1a, 0x2, 0x2, 0x289, 0x28e, 0x5, 0xca, 0x66, 0x2, 0x28a, 0x28b, 
       0x7, 0x3d, 0x2, 0x2, 0x28b, 0x28d, 0x5, 0xca, 0x66, 0x2, 0x28c, 0x28a, 
       0x3, 0x2, 0x2, 0x2, 0x28d, 0x290, 0x3, 0x2, 0x2, 0x2, 0x28e, 0x28c, 
       0x3, 0x2, 0x2, 0x2, 0x28e, 0x28f, 0x3, 0x2, 0x2, 0x2, 0x28f, 0x4b, 
       0x3, 0x2, 0x2, 0x2, 0x290, 0x28e, 0x3, 0x2, 0x2, 0x2, 0x291, 0x292, 
       0x7, 0x22, 0x2, 0x2, 0x292, 0x297, 0x5, 0xca, 0x66, 0x2, 0x293, 0x294, 
       0x7, 0x3d, 0x2, 0x2, 0x294, 0x296, 0x5, 0xca, 0x66, 0x2, 0x295, 0x293, 
       0x3, 0x2, 0x2, 0x2, 0x296, 0x299, 0x3, 0x2, 0x2, 0x2, 0x297, 0x295, 
       0x3, 0x2, 0x2, 0x2, 0x297, 0x298, 0x3, 0x2, 0x2, 0x2, 0x298, 0x4d, 
       0x3, 0x2, 0x2, 0x2, 0x299, 0x297, 0x3, 0x2, 0x2, 0x2, 0x29a, 0x29b, 
       0x7, 0xa, 0x2, 0x2, 0x29b, 0x29e, 0x5, 0xb0, 0x59, 0x2, 0x29c, 0x29d, 
       0x7, 0x3d, 0x2, 0x2, 0x29d, 0x29f, 0x5, 0xb0, 0x59, 0x2, 0x29e, 0x29c, 
       0x3, 0x2, 0x2, 0x2, 0x29e, 0x29f, 0x3, 0x2, 0x2, 0x2, 0x29f, 0x4f, 
       0x3, 0x2, 0x2, 0x2, 0x2a0, 0x2ab, 0x5, 0x54, 0x2b, 0x2, 0x2a1, 0x2ab, 
       0x5, 0x56, 0x2c, 0x2, 0x2a2, 0x2ab, 0x5, 0x58, 0x2d, 0x2, 0x2a3, 
       0x2ab, 0x5, 0x5a, 0x2e, 0x2, 0x2a4, 0x2ab, 0x5, 0x5c, 0x2f, 0x2, 
       0x2a5, 0x2ab, 0x5, 0x10, 0x9, 0x2, 0x2a6, 0x2ab, 0x5, 0xdc, 0x6f, 
       0x2, 0x2a7, 0x2ab, 0x5, 0xc, 0x7, 0x2, 0x2a8, 0x2ab, 0x5, 0x52, 0x2a, 
       0x2, 0x2a9, 0x2ab, 0x5, 0x64, 0x33, 0x2, 0x2aa, 0x2a0, 0x3, 0x2, 
       0x2, 0x2, 0x2aa, 0x2a1, 0x3, 0x2, 0x2, 0x2, 0x2aa, 0x2a2, 0x3, 0x2, 
       0x2, 0x2, 0x2aa, 0x2a3, 0x3, 0x2, 0x2, 0x2, 0x2aa, 0x2a4, 0x3, 0x2, 
       0x2, 0x2, 0x2aa, 0x2a5, 0x3, 0x2, 0x2, 0x2, 0x2aa, 0x2a6, 0x3, 0x2, 
       0x2, 0x2, 0x2aa, 0x2a7, 0x3, 0x2, 0x2, 0x2, 0x2aa, 0x2a8, 0x3, 0x2, 
       0x2, 0x2, 0x2aa, 0x2a9, 0x3, 0x2, 0x2, 0x2, 0x2ab, 0x51, 0x3, 0x2, 
       0x2, 0x2, 0x2ac, 0x2b0, 0x7, 0xb, 0x2, 0x2, 0x2ad, 0x2b1, 0x5, 0x10, 
       0x9, 0x2, 0x2ae, 0x2b1, 0x5, 0x5c, 0x2f, 0x2, 0x2af, 0x2b1, 0x5, 
       0x58, 0x2d, 0x2, 0x2b0, 0x2ad, 0x3, 0x2, 0x2, 0x2, 0x2b0, 0x2ae, 
       0x3, 0x2, 0x2, 0x2, 0x2b0, 0x2af, 0x3, 0x2, 0x2, 0x2, 0x2b1, 0x53, 
       0x3, 0x2, 0x2, 0x2, 0x2b2, 0x2b3, 0x7, 0x1b, 0x2, 0x2, 0x2b3, 0x2b4, 
       0x5, 0xb0, 0x59, 0x2, 0x2b4, 0x2b5, 0x7, 0x3e, 0x2, 0x2, 0x2b5, 0x2bd, 
       0x5, 0x62, 0x32, 0x2, 0x2b6, 0x2b7, 0x7, 0x13, 0x2, 0x2, 0x2b7, 0x2b8, 
       0x5, 0xb0, 0x59, 0x2, 0x2b8, 0x2b9, 0x7, 0x3e, 0x2, 0x2, 0x2b9, 0x2ba, 
       0x5, 0x62, 0x32, 0x2, 0x2ba, 0x2bc, 0x3, 0x2, 0x2, 0x2, 0x2bb, 0x2b6, 
       0x3, 0x2, 0x2, 0x2, 0x2bc, 0x2bf, 0x3, 0x2, 0x2, 0x2, 0x2bd, 0x2bb, 
       0x3, 0x2, 0x2, 0x2, 0x2bd, 0x2be, 0x3, 0x2, 0x2, 0x2, 0x2be, 0x2c3, 
       0x3, 0x2, 0x2, 0x2, 0x2bf, 0x2bd, 0x3, 0x2, 0x2, 0x2, 0x2c0, 0x2c1, 
       0x7, 0x14, 0x2, 0x2, 0x2c1, 0x2c2, 0x7, 0x3e, 0x2, 0x2, 0x2c2, 0x2c4, 
       0x5, 0x62, 0x32, 0x2, 0x2c3, 0x2c0, 0x3, 0x2, 0x2, 0x2, 0x2c3, 0x2c4, 
       0x3, 0x2, 0x2, 0x2, 0x2c4, 0x55, 0x3, 0x2, 0x2, 0x2, 0x2c5, 0x2c6, 
       0x7, 0x2b, 0x2, 0x2, 0x2c6, 0x2c7, 0x5, 0xb0, 0x59, 0x2, 0x2c7, 0x2c8, 
       0x7, 0x3e, 0x2, 0x2, 0x2c8, 0x2cc, 0x5, 0x62, 0x32, 0x2, 0x2c9, 0x2ca, 
       0x7, 0x14, 0x2, 0x2, 0x2ca, 0x2cb, 0x7, 0x3e, 0x2, 0x2, 0x2cb, 0x2cd, 
       0x5, 0x62, 0x32, 0x2, 0x2cc, 0x2c9, 0x3, 0x2, 0x2, 0x2, 0x2cc, 0x2cd, 
       0x3, 0x2, 0x2, 0x2, 0x2cd, 0x57, 0x3, 0x2, 0x2, 0x2, 0x2ce, 0x2cf, 
       0x7, 0x18, 0x2, 0x2, 0x2cf, 0x2d0, 0x5, 0xd6, 0x6c, 0x2, 0x2d0, 0x2d1, 
       0x7, 0x1d, 0x2, 0x2, 0x2d1, 0x2d2, 0x5, 0xd8, 0x6d, 0x2, 0x2d2, 0x2d3, 
       0x7, 0x3e, 0x2, 0x2, 0x2d3, 0x2d7, 0x5, 0x62, 0x32, 0x2, 0x2d4, 0x2d5, 
       0x7, 0x14, 0x2, 0x2, 0x2d5, 0x2d6, 0x7, 0x3e, 0x2, 0x2, 0x2d6, 0x2d8, 
       0x5, 0x62, 0x32, 0x2, 0x2d7, 0x2d4, 0x3, 0x2, 0x2, 0x2, 0x2d7, 0x2d8, 
       0x3, 0x2, 0x2, 0x2, 0x2d8, 0x59, 0x3, 0x2, 0x2, 0x2, 0x2d9, 0x2da, 
       0x7, 0x29, 0x2, 0x2, 0x2da, 0x2db, 0x7, 0x3e, 0x2, 0x2, 0x2db, 0x2f1, 
       0x5, 0x62, 0x32, 0x2, 0x2dc, 0x2dd, 0x5, 0x60, 0x31, 0x2, 0x2dd, 
       0x2de, 0x7, 0x3e, 0x2, 0x2, 0x2de, 0x2df, 0x5, 0x62, 0x32, 0x2, 0x2df, 
       0x2e1, 0x3, 0x2, 0x2, 0x2, 0x2e0, 0x2dc, 0x3, 0x2, 0x2, 0x2, 0x2e1, 
       0x2e2, 0x3, 0x2, 0x2, 0x2, 0x2e2, 0x2e0, 0x3, 0x2, 0x2, 0x2, 0x2e2, 
       0x2e3, 0x3, 0x2, 0x2, 0x2, 0x2e3, 0x2e7, 0x3, 0x2, 0x2, 0x2, 0x2e4, 
       0x2e5, 0x7, 0x14, 0x2, 0x2, 0x2e5, 0x2e6, 0x7, 0x3e, 0x2, 0x2, 0x2e6, 
       0x2e8, 0x5, 0x62, 0x32, 0x2, 0x2e7, 0x2e4, 0x3, 0x2, 0x2, 0x2, 0x2e7, 
       0x2e8, 0x3, 0x2, 0x2, 0x2, 0x2e8, 0x2ec, 0x3, 0x2, 0x2, 0x2, 0x2e9, 
       0x2ea, 0x7, 0x17, 0x2, 0x2, 0x2ea, 0x2eb, 0x7, 0x3e, 0x2, 0x2, 0x2eb, 
       0x2ed, 0x5, 0x62, 0x32, 0x2, 0x2ec, 0x2e9, 0x3, 0x2, 0x2, 0x2, 0x2ec, 
       0x2ed, 0x3, 0x2, 0x2, 0x2, 0x2ed, 0x2f2, 0x3, 0x2, 0x2, 0x2, 0x2ee, 
       0x2ef, 0x7, 0x17, 0x2, 0x2, 0x2ef, 0x2f0, 0x7, 0x3e, 0x2, 0x2, 0x2f0, 
       0x2f2, 0x5, 0x62, 0x32, 0x2, 0x2f1, 0x2e0, 0x3, 0x2, 0x2, 0x2, 0x2f1, 
       0x2ee, 0x3, 0x2, 0x2, 0x2, 0x2f2, 0x5b, 0x3, 0x2, 0x2, 0x2, 0x2f3, 
       0x2f4, 0x7, 0x2c, 0x2, 0x2, 0x2f4, 0x2f9, 0x5, 0x5e, 0x30, 0x2, 0x2f5, 
       0x2f6, 0x7, 0x3d, 0x2, 0x2, 0x2f6, 0x2f8, 0x5, 0x5e, 0x30, 0x2, 0x2f7, 
       0x2f5, 0x3, 0x2, 0x2, 0x2, 0x2f8, 0x2fb, 0x3, 0x2, 0x2, 0x2, 0x2f9, 
       0x2f7, 0x3, 0x2, 0x2, 0x2, 0x2f9, 0x2fa, 0x3, 0x2, 0x2, 0x2, 0x2fa, 
       0x2fc, 0x3, 0x2, 0x2, 0x2, 0x2fb, 0x2f9, 0x3, 0x2, 0x2, 0x2, 0x2fc, 
       0x2fd, 0x7, 0x3e, 0x2, 0x2, 0x2fd, 0x2fe, 0x5, 0x62, 0x32, 0x2, 0x2fe, 
       0x5d, 0x3, 0x2, 0x2, 0x2, 0x2ff, 0x302, 0x5, 0xb0, 0x59, 0x2, 0x300, 
       0x301, 0x7, 0x9, 0x2, 0x2, 0x301, 0x303, 0x5, 0xc4, 0x63, 0x2, 0x302, 
       0x300, 0x3, 0x2, 0x2, 0x2, 0x302, 0x303, 0x3, 0x2, 0x2, 0x2, 0x303, 
       0x5f, 0x3, 0x2, 0x2, 0x2, 0x304, 0x30a, 0x7, 0x15, 0x2, 0x2, 0x305, 
       0x308, 0x5, 0xb0, 0x59, 0x2, 0x306, 0x307, 0x7, 0x9, 0x2, 0x2, 0x307, 
       0x309, 0x5, 0xca, 0x66, 0x2, 0x308, 0x306, 0x3, 0x2, 0x2, 0x2, 0x308, 
       0x309, 0x3, 0x2, 0x2, 0x2, 0x309, 0x30b, 0x3, 0x2, 0x2, 0x2, 0x30a, 
       0x305, 0x3, 0x2, 0x2, 0x2, 0x30a, 0x30b, 0x3, 0x2, 0x2, 0x2, 0x30b, 
       0x61, 0x3, 0x2, 0x2, 0x2, 0x30c, 0x317, 0x5, 0x1e, 0x10, 0x2, 0x30d, 
       0x30e, 0x7, 0x2e, 0x2, 0x2, 0x30e, 0x310, 0x7, 0x3, 0x2, 0x2, 0x30f, 
       0x311, 0x5, 0x1c, 0xf, 0x2, 0x310, 0x30f, 0x3, 0x2, 0x2, 0x2, 0x311, 
       0x312, 0x3, 0x2, 0x2, 0x2, 0x312, 0x310, 0x3, 0x2, 0x2, 0x2, 0x312, 
       0x313, 0x3, 0x2, 0x2, 0x2, 0x313, 0x314, 0x3, 0x2, 0x2, 0x2, 0x314, 
       0x315, 0x7, 0x4, 0x2, 0x2, 0x315, 0x317, 0x3, 0x2, 0x2, 0x2, 0x316, 
       0x30c, 0x3, 0x2, 0x2, 0x2, 0x316, 0x30d, 0x3, 0x2, 0x2, 0x2, 0x317, 
       0x63, 0x3, 0x2, 0x2, 0x2, 0x318, 0x319, 0x7, 0x20, 0x2, 0x2, 0x319, 
       0x31a, 0x5, 0x66, 0x34, 0x2, 0x31a, 0x31b, 0x7, 0x3e, 0x2, 0x2, 0x31b, 
       0x31c, 0x7, 0x2e, 0x2, 0x2, 0x31c, 0x31e, 0x7, 0x3, 0x2, 0x2, 0x31d, 
       0x31f, 0x5, 0x6c, 0x37, 0x2, 0x31e, 0x31d, 0x3, 0x2, 0x2, 0x2, 0x31f, 
       0x320, 0x3, 0x2, 0x2, 0x2, 0x320, 0x31e, 0x3, 0x2, 0x2, 0x2, 0x320, 
       0x321, 0x3, 0x2, 0x2, 0x2, 0x321, 0x322, 0x3, 0x2, 0x2, 0x2, 0x322, 
       0x323, 0x7, 0x4, 0x2, 0x2, 0x323, 0x65, 0x3, 0x2, 0x2, 0x2, 0x324, 
       0x325, 0x5, 0x6a, 0x36, 0x2, 0x325, 0x327, 0x7, 0x3d, 0x2, 0x2, 0x326, 
       0x328, 0x5, 0x68, 0x35, 0x2, 0x327, 0x326, 0x3, 0x2, 0x2, 0x2, 0x327, 
       0x328, 0x3, 0x2, 0x2, 0x2, 0x328, 0x32b, 0x3, 0x2, 0x2, 0x2, 0x329, 
       0x32b, 0x5, 0xb0, 0x59, 0x2, 0x32a, 0x324, 0x3, 0x2, 0x2, 0x2, 0x32a, 
       0x329, 0x3, 0x2, 0x2, 0x2, 0x32b, 0x67, 0x3, 0x2, 0x2, 0x2, 0x32c, 
       0x32e, 0x7, 0x3d, 0x2, 0x2, 0x32d, 0x32f, 0x5, 0x6a, 0x36, 0x2, 0x32e, 
       0x32d, 0x3, 0x2, 0x2, 0x2, 0x32f, 0x330, 0x3, 0x2, 0x2, 0x2, 0x330, 
       0x32e, 0x3, 0x2, 0x2, 0x2, 0x330, 0x331, 0x3, 0x2, 0x2, 0x2, 0x331, 
       0x333, 0x3, 0x2, 0x2, 0x2, 0x332, 0x334, 0x7, 0x3d, 0x2, 0x2, 0x333, 
       0x332, 0x3, 0x2, 0x2, 0x2, 0x333, 0x334, 0x3, 0x2, 0x2, 0x2, 0x334, 
       0x69, 0x3, 0x2, 0x2, 0x2, 0x335, 0x336, 0x7, 0x3a, 0x2, 0x2, 0x336, 
       0x339, 0x5, 0xc4, 0x63, 0x2, 0x337, 0x339, 0x5, 0xb0, 0x59, 0x2, 
       0x338, 0x335, 0x3, 0x2, 0x2, 0x2, 0x338, 0x337, 0x3, 0x2, 0x2, 0x2, 
       0x339, 0x6b, 0x3, 0x2, 0x2, 0x2, 0x33a, 0x33b, 0x7, 0xe, 0x2, 0x2, 
       0x33b, 0x33d, 0x5, 0x70, 0x39, 0x2, 0x33c, 0x33e, 0x5, 0x6e, 0x38, 
       0x2, 0x33d, 0x33c, 0x3, 0x2, 0x2, 0x2, 0x33d, 0x33e, 0x3, 0x2, 0x2, 
       0x2, 0x33e, 0x33f, 0x3, 0x2, 0x2, 0x2, 0x33f, 0x340, 0x7, 0x3e, 0x2, 
       0x2, 0x340, 0x341, 0x5, 0x62, 0x32, 0x2, 0x341, 0x6d, 0x3, 0x2, 0x2, 
       0x2, 0x342, 0x343, 0x7, 0x1b, 0x2, 0x2, 0x343, 0x344, 0x5, 0xb0, 
       0x59, 0x2, 0x344, 0x6f, 0x3, 0x2, 0x2, 0x2, 0x345, 0x348, 0x5, 0x98, 
       0x4d, 0x2, 0x346, 0x348, 0x5, 0x72, 0x3a, 0x2, 0x347, 0x345, 0x3, 
       0x2, 0x2, 0x2, 0x347, 0x346, 0x3, 0x2, 0x2, 0x2, 0x348, 0x71, 0x3, 
       0x2, 0x2, 0x2, 0x349, 0x34c, 0x5, 0x74, 0x3b, 0x2, 0x34a, 0x34c, 
       0x5, 0x76, 0x3c, 0x2, 0x34b, 0x349, 0x3, 0x2, 0x2, 0x2, 0x34b, 0x34a, 
       0x3, 0x2, 0x2, 0x2, 0x34c, 0x73, 0x3, 0x2, 0x2, 0x2, 0x34d, 0x34e, 
       0x5, 0x76, 0x3c, 0x2, 0x34e, 0x34f, 0x7, 0x9, 0x2, 0x2, 0x34f, 0x350, 
       0x5, 0x8a, 0x46, 0x2, 0x350, 0x75, 0x3, 0x2, 0x2, 0x2, 0x351, 0x356, 
       0x5, 0x78, 0x3d, 0x2, 0x352, 0x353, 0x7, 0x44, 0x2, 0x2, 0x353, 0x355, 
       0x5, 0x78, 0x3d, 0x2, 0x354, 0x352, 0x3, 0x2, 0x2, 0x2, 0x355, 0x358, 
       0x3, 0x2, 0x2, 0x2, 0x356, 0x354, 0x3, 0x2, 0x2, 0x2, 0x356, 0x357, 
       0x3, 0x2, 0x2, 0x2, 0x357, 0x77, 0x3, 0x2, 0x2, 0x2, 0x358, 0x356, 
       0x3, 0x2, 0x2, 0x2, 0x359, 0x362, 0x5, 0x7a, 0x3e, 0x2, 0x35a, 0x362, 
       0x5, 0x88, 0x45, 0x2, 0x35b, 0x362, 0x5, 0x8c, 0x47, 0x2, 0x35c, 
       0x362, 0x5, 0x8e, 0x48, 0x2, 0x35d, 0x362, 0x5, 0x94, 0x4b, 0x2, 
       0x35e, 0x362, 0x5, 0x96, 0x4c, 0x2, 0x35f, 0x362, 0x5, 0xa0, 0x51, 
       0x2, 0x360, 0x362, 0x5, 0xa8, 0x55, 0x2, 0x361, 0x359, 0x3, 0x2, 
       0x2, 0x2, 0x361, 0x35a, 0x3, 0x2, 0x2, 0x2, 0x361, 0x35b, 0x3, 0x2, 
       0x2, 0x2, 0x361, 0x35c, 0x3, 0x2, 0x2, 0x2, 0x361, 0x35d, 0x3, 0x2, 
       0x2, 0x2, 0x361, 0x35e, 0x3, 0x2, 0x2, 0x2, 0x361, 0x35f, 0x3, 0x2, 
       0x2, 0x2, 0x361, 0x360, 0x3, 0x2, 0x2, 0x2, 0x362, 0x79, 0x3, 0x2, 
       0x2, 0x2, 0x363, 0x364, 0x5, 0x80, 0x41, 0x2, 0x364, 0x365, 0x6, 
       0x3e, 0x2, 0x2, 0x365, 0x36c, 0x3, 0x2, 0x2, 0x2, 0x366, 0x36c, 0x5, 
       0x7e, 0x40, 0x2, 0x367, 0x36c, 0x5, 0xee, 0x78, 0x2, 0x368, 0x36c, 
       0x7, 0x21, 0x2, 0x2, 0x369, 0x36c, 0x7, 0x28, 0x2, 0x2, 0x36a, 0x36c, 
       0x7, 0x16, 0x2, 0x2, 0x36b, 0x363, 0x3, 0x2, 0x2, 0x2, 0x36b, 0x366, 
       0x3, 0x2, 0x2, 0x2, 0x36b, 0x367, 0x3, 0x2, 0x2, 0x2, 0x36b, 0x368, 
       0x3, 0x2, 0x2, 0x2, 0x36b, 0x369, 0x3, 0x2, 0x2, 0x2, 0x36b, 0x36a, 
       0x3, 0x2, 0x2, 0x2, 0x36c, 0x7b, 0x3, 0x2, 0x2, 0x2, 0x36d, 0x36e, 
       0x5, 0x80, 0x41, 0x2, 0x36e, 0x36f, 0x6, 0x3f, 0x3, 0x2, 0x36f, 0x376, 
       0x3, 0x2, 0x2, 0x2, 0x370, 0x376, 0x5, 0x7e, 0x40, 0x2, 0x371, 0x376, 
       0x5, 0xee, 0x78, 0x2, 0x372, 0x376, 0x7, 0x21, 0x2, 0x2, 0x373, 0x376, 
       0x7, 0x28, 0x2, 0x2, 0x374, 0x376, 0x7, 0x16, 0x2, 0x2, 0x375, 0x36d, 
       0x3, 0x2, 0x2, 0x2, 0x375, 0x370, 0x3, 0x2, 0x2, 0x2, 0x375, 0x371, 
       0x3, 0x2, 0x2, 0x2, 0x375, 0x372, 0x3, 0x2, 0x2, 0x2, 0x375, 0x373, 
       0x3, 0x2, 0x2, 0x2, 0x375, 0x374, 0x3, 0x2, 0x2, 0x2, 0x376, 0x7d, 
       0x3, 0x2, 0x2, 0x2, 0x377, 0x378, 0x5, 0x82, 0x42, 0x2, 0x378, 0x379, 
       0x7, 0x49, 0x2, 0x2, 0x379, 0x37a, 0x5, 0x86, 0x44, 0x2, 0x37a, 0x380, 
       0x3, 0x2, 0x2, 0x2, 0x37b, 0x37c, 0x5, 0x82, 0x42, 0x2, 0x37c, 0x37d, 
       0x7, 0x4a, 0x2, 0x2, 0x37d, 0x37e, 0x5, 0x86, 0x44, 0x2, 0x37e, 0x380, 
       0x3, 0x2, 0x2, 0x2, 0x37f, 0x377, 0x3, 0x2, 0x2, 0x2, 0x37f, 0x37b, 
       0x3, 0x2, 0x2, 0x2, 0x380, 0x7f, 0x3, 0x2, 0x2, 0x2, 0x381, 0x385, 
       0x7, 0x6, 0x2, 0x2, 0x382, 0x383, 0x7, 0x4a, 0x2, 0x2, 0x383, 0x385, 
       0x7, 0x6, 0x2, 0x2, 0x384, 0x381, 0x3, 0x2, 0x2, 0x2, 0x384, 0x382, 
       0x3, 0x2, 0x2, 0x2, 0x385, 0x81, 0x3, 0x2, 0x2, 0x2, 0x386, 0x38a, 
       0x5, 0x84, 0x43, 0x2, 0x387, 0x388, 0x7, 0x4a, 0x2, 0x2, 0x388, 0x38a, 
       0x5, 0x84, 0x43, 0x2, 0x389, 0x386, 0x3, 0x2, 0x2, 0x2, 0x389, 0x387, 
       0x3, 0x2, 0x2, 0x2, 0x38a, 0x83, 0x3, 0x2, 0x2, 0x2, 0x38b, 0x38c, 
       0x7, 0x6, 0x2, 0x2, 0x38c, 0x85, 0x3, 0x2, 0x2, 0x2, 0x38d, 0x38e, 
       0x7, 0x6, 0x2, 0x2, 0x38e, 0x87, 0x3, 0x2, 0x2, 0x2, 0x38f, 0x390, 
       0x5, 0x8a, 0x46, 0x2, 0x390, 0x89, 0x3, 0x2, 0x2, 0x2, 0x391, 0x392, 
       0x5, 0xca, 0x66, 0x2, 0x392, 0x393, 0x6, 0x46, 0x4, 0x2, 0x393, 0x8b, 
       0x3, 0x2, 0x2, 0x2, 0x394, 0x395, 0x7, 0x2a, 0x2, 0x2, 0x395, 0x8d, 
       0x3, 0x2, 0x2, 0x2, 0x396, 0x397, 0x5, 0x90, 0x49, 0x2, 0x397, 0x398, 
       0x6, 0x48, 0x5, 0x2, 0x398, 0x8f, 0x3, 0x2, 0x2, 0x2, 0x399, 0x39c, 
       0x5, 0xca, 0x66, 0x2, 0x39a, 0x39b, 0x7, 0x38, 0x2, 0x2, 0x39b, 0x39d, 
       0x5, 0xca, 0x66, 0x2, 0x39c, 0x39a, 0x3, 0x2, 0x2, 0x2, 0x39d, 0x39e, 
       0x3, 0x2, 0x2, 0x2, 0x39e, 0x39c, 0x3, 0x2, 0x2, 0x2, 0x39e, 0x39f, 
       0x3, 0x2, 0x2, 0x2, 0x39f, 0x91, 0x3, 0x2, 0x2, 0x2, 0x3a0, 0x3a3, 
       0x5, 0x90, 0x49, 0x2, 0x3a1, 0x3a3, 0x5, 0xca, 0x66, 0x2, 0x3a2, 
       0x3a0, 0x3, 0x2, 0x2, 0x2, 0x3a2, 0x3a1, 0x3, 0x2, 0x2, 0x2, 0x3a3, 
       0x93, 0x3, 0x2, 0x2, 0x2, 0x3a4, 0x3a5, 0x7, 0x3b, 0x2, 0x2, 0x3a5, 
       0x3a6, 0x5, 0x72, 0x3a, 0x2, 0x3a6, 0x3a7, 0x7, 0x3c, 0x2, 0x2, 0x3a7, 
       0x95, 0x3, 0x2, 0x2, 0x2, 0x3a8, 0x3aa, 0x7, 0x42, 0x2, 0x2, 0x3a9, 
       0x3ab, 0x5, 0x9a, 0x4e, 0x2, 0x3aa, 0x3a9, 0x3, 0x2, 0x2, 0x2, 0x3aa, 
       0x3ab, 0x3, 0x2, 0x2, 0x2, 0x3ab, 0x3ac, 0x3, 0x2, 0x2, 0x2, 0x3ac, 
       0x3b3, 0x7, 0x43, 0x2, 0x2, 0x3ad, 0x3af, 0x7, 0x3b, 0x2, 0x2, 0x3ae, 
       0x3b0, 0x5, 0x98, 0x4d, 0x2, 0x3af, 0x3ae, 0x3, 0x2, 0x2, 0x2, 0x3af, 
       0x3b0, 0x3, 0x2, 0x2, 0x2, 0x3b0, 0x3b1, 0x3, 0x2, 0x2, 0x2, 0x3b1, 
       0x3b3, 0x7, 0x3c, 0x2, 0x2, 0x3b2, 0x3a8, 0x3, 0x2, 0x2, 0x2, 0x3b2, 
       0x3ad, 0x3, 0x2, 0x2, 0x2, 0x3b3, 0x97, 0x3, 0x2, 0x2, 0x2, 0x3b4, 
       0x3b5, 0x5, 0x9c, 0x4f, 0x2, 0x3b5, 0x3b7, 0x7, 0x3d, 0x2, 0x2, 0x3b6, 
       0x3b8, 0x5, 0x9a, 0x4e, 0x2, 0x3b7, 0x3b6, 0x3, 0x2, 0x2, 0x2, 0x3b7, 
       0x3b8, 0x3, 0x2, 0x2, 0x2, 0x3b8, 0x99, 0x3, 0x2, 0x2, 0x2, 0x3b9, 
       0x3be, 0x5, 0x9c, 0x4f, 0x2, 0x3ba, 0x3bb, 0x7, 0x3d, 0x2, 0x2, 0x3bb, 
       0x3bd, 0x5, 0x9c, 0x4f, 0x2, 0x3bc, 0x3ba, 0x3, 0x2, 0x2, 0x2, 0x3bd, 
       0x3c0, 0x3, 0x2, 0x2, 0x2, 0x3be, 0x3bc, 0x3, 0x2, 0x2, 0x2, 0x3be, 
       0x3bf, 0x3, 0x2, 0x2, 0x2, 0x3bf, 0x3c2, 0x3, 0x2, 0x2, 0x2, 0x3c0, 
       0x3be, 0x3, 0x2, 0x2, 0x2, 0x3c1, 0x3c3, 0x7, 0x3d, 0x2, 0x2, 0x3c2, 
       0x3c1, 0x3, 0x2, 0x2, 0x2, 0x3c2, 0x3c3, 0x3, 0x2, 0x2, 0x2, 0x3c3, 
       0x9b, 0x3, 0x2, 0x2, 0x2, 0x3c4, 0x3c7, 0x5, 0x9e, 0x50, 0x2, 0x3c5, 
       0x3c7, 0x5, 0x72, 0x3a, 0x2, 0x3c6, 0x3c4, 0x3, 0x2, 0x2, 0x2, 0x3c6, 
       0x3c5, 0x3, 0x2, 0x2, 0x2, 0x3c7, 0x9d, 0x3, 0x2, 0x2, 0x2, 0x3c8, 
       0x3c9, 0x7, 0x3a, 0x2, 0x2, 0x3c9, 0x3cd, 0x5, 0x8a, 0x46, 0x2, 0x3ca, 
       0x3cb, 0x7, 0x3a, 0x2, 0x2, 0x3cb, 0x3cd, 0x5, 0x8c, 0x47, 0x2, 0x3cc, 
       0x3c8, 0x3, 0x2, 0x2, 0x2, 0x3cc, 0x3ca, 0x3, 0x2, 0x2, 0x2, 0x3cd, 
       0x9f, 0x3, 0x2, 0x2, 0x2, 0x3ce, 0x3cf, 0x7, 0x4f, 0x2, 0x2, 0x3cf, 
       0x3e8, 0x7, 0x50, 0x2, 0x2, 0x3d0, 0x3d1, 0x7, 0x4f, 0x2, 0x2, 0x3d1, 
       0x3d3, 0x5, 0xa6, 0x54, 0x2, 0x3d2, 0x3d4, 0x7, 0x3d, 0x2, 0x2, 0x3d3, 
       0x3d2, 0x3, 0x2, 0x2, 0x2, 0x3d3, 0x3d4, 0x3, 0x2, 0x2, 0x2, 0x3d4, 
       0x3d5, 0x3, 0x2, 0x2, 0x2, 0x3d5, 0x3d6, 0x7, 0x50, 0x2, 0x2, 0x3d6, 
       0x3e8, 0x3, 0x2, 0x2, 0x2, 0x3d7, 0x3d8, 0x7, 0x4f, 0x2, 0x2, 0x3d8, 
       0x3d9, 0x5, 0xa2, 0x52, 0x2, 0x3d9, 0x3da, 0x7, 0x3d, 0x2, 0x2, 0x3da, 
       0x3dc, 0x5, 0xa6, 0x54, 0x2, 0x3db, 0x3dd, 0x7, 0x3d, 0x2, 0x2, 0x3dc, 
       0x3db, 0x3, 0x2, 0x2, 0x2, 0x3dc, 0x3dd, 0x3, 0x2, 0x2, 0x2, 0x3dd, 
       0x3de, 0x3, 0x2, 0x2, 0x2, 0x3de, 0x3df, 0x7, 0x50, 0x2, 0x2, 0x3df, 
       0x3e8, 0x3, 0x2, 0x2, 0x2, 0x3e0, 0x3e1, 0x7, 0x4f, 0x2, 0x2, 0x3e1, 
       0x3e3, 0x5, 0xa2, 0x52, 0x2, 0x3e2, 0x3e4, 0x7, 0x3d, 0x2, 0x2, 0x3e3, 
       0x3e2, 0x3, 0x2, 0x2, 0x2, 0x3e3, 0x3e4, 0x3, 0x2, 0x2, 0x2, 0x3e4, 
       0x3e5, 0x3, 0x2, 0x2, 0x2, 0x3e5, 0x3e6, 0x7, 0x50, 0x2, 0x2, 0x3e6, 
       0x3e8, 0x3, 0x2, 0x2, 0x2, 0x3e7, 0x3ce, 0x3, 0x2, 0x2, 0x2, 0x3e7, 
       0x3d0, 0x3, 0x2, 0x2, 0x2, 0x3e7, 0x3d7, 0x3, 0x2, 0x2, 0x2, 0x3e7, 
       0x3e0, 0x3, 0x2, 0x2, 0x2, 0x3e8, 0xa1, 0x3, 0x2, 0x2, 0x2, 0x3e9, 
       0x3ee, 0x5, 0xa4, 0x53, 0x2, 0x3ea, 0x3eb, 0x7, 0x3d, 0x2, 0x2, 0x3eb, 
       0x3ed, 0x5, 0xa4, 0x53, 0x2, 0x3ec, 0x3ea, 0x3, 0x2, 0x2, 0x2, 0x3ed, 
       0x3f0, 0x3, 0x2, 0x2, 0x2, 0x3ee, 0x3ec, 0x3, 0x2, 0x2, 0x2, 0x3ee, 
       0x3ef, 0x3, 0x2, 0x2, 0x2, 0x3ef, 0xa3, 0x3, 0x2, 0x2, 0x2, 0x3f0, 
       0x3ee, 0x3, 0x2, 0x2, 0x2, 0x3f1, 0x3f4, 0x5, 0x7c, 0x3f, 0x2, 0x3f2, 
       0x3f4, 0x5, 0x90, 0x49, 0x2, 0x3f3, 0x3f1, 0x3, 0x2, 0x2, 0x2, 0x3f3, 
       0x3f2, 0x3, 0x2, 0x2, 0x2, 0x3f4, 0x3f5, 0x3, 0x2, 0x2, 0x2, 0x3f5, 
       0x3f6, 0x7, 0x3e, 0x2, 0x2, 0x3f6, 0x3f7, 0x5, 0x72, 0x3a, 0x2, 0x3f7, 
       0xa5, 0x3, 0x2, 0x2, 0x2, 0x3f8, 0x3f9, 0x7, 0x40, 0x2, 0x2, 0x3f9, 
       0x3fa, 0x5, 0x8a, 0x46, 0x2, 0x3fa, 0xa7, 0x3, 0x2, 0x2, 0x2, 0x3fb, 
       0x3fc, 0x5, 0x92, 0x4a, 0x2, 0x3fc, 0x3fd, 0x7, 0x3b, 0x2, 0x2, 0x3fd, 
       0x3fe, 0x7, 0x3c, 0x2, 0x2, 0x3fe, 0x41a, 0x3, 0x2, 0x2, 0x2, 0x3ff, 
       0x400, 0x5, 0x92, 0x4a, 0x2, 0x400, 0x401, 0x7, 0x3b, 0x2, 0x2, 0x401, 
       0x403, 0x5, 0xaa, 0x56, 0x2, 0x402, 0x404, 0x7, 0x3d, 0x2, 0x2, 0x403, 
       0x402, 0x3, 0x2, 0x2, 0x2, 0x403, 0x404, 0x3, 0x2, 0x2, 0x2, 0x404, 
       0x405, 0x3, 0x2, 0x2, 0x2, 0x405, 0x406, 0x7, 0x3c, 0x2, 0x2, 0x406, 
       0x41a, 0x3, 0x2, 0x2, 0x2, 0x407, 0x408, 0x5, 0x92, 0x4a, 0x2, 0x408, 
       0x409, 0x7, 0x3b, 0x2, 0x2, 0x409, 0x40b, 0x5, 0xac, 0x57, 0x2, 0x40a, 
       0x40c, 0x7, 0x3d, 0x2, 0x2, 0x40b, 0x40a, 0x3, 0x2, 0x2, 0x2, 0x40b, 
       0x40c, 0x3, 0x2, 0x2, 0x2, 0x40c, 0x40d, 0x3, 0x2, 0x2, 0x2, 0x40d, 
       0x40e, 0x7, 0x3c, 0x2, 0x2, 0x40e, 0x41a, 0x3, 0x2, 0x2, 0x2, 0x40f, 
       0x410, 0x5, 0x92, 0x4a, 0x2, 0x410, 0x411, 0x7, 0x3b, 0x2, 0x2, 0x411, 
       0x412, 0x5, 0xaa, 0x56, 0x2, 0x412, 0x413, 0x7, 0x3d, 0x2, 0x2, 0x413, 
       0x415, 0x5, 0xac, 0x57, 0x2, 0x414, 0x416, 0x7, 0x3d, 0x2, 0x2, 0x415, 
       0x414, 0x3, 0x2, 0x2, 0x2, 0x415, 0x416, 0x3, 0x2, 0x2, 0x2, 0x416, 
       0x417, 0x3, 0x2, 0x2, 0x2, 0x417, 0x418, 0x7, 0x3c, 0x2, 0x2, 0x418, 
       0x41a, 0x3, 0x2, 0x2, 0x2, 0x419, 0x3fb, 0x3, 0x2, 0x2, 0x2, 0x419, 
       0x3ff, 0x3, 0x2, 0x2, 0x2, 0x419, 0x407, 0x3, 0x2, 0x2, 0x2, 0x419, 
       0x40f, 0x3, 0x2, 0x2, 0x2, 0x41a, 0xa9, 0x3, 0x2, 0x2, 0x2, 0x41b, 
       0x420, 0x5, 0x72, 0x3a, 0x2, 0x41c, 0x41d, 0x7, 0x3d, 0x2, 0x2, 0x41d, 
       0x41f, 0x5, 0x72, 0x3a, 0x2, 0x41e, 0x41c, 0x3, 0x2, 0x2, 0x2, 0x41f, 
       0x422, 0x3, 0x2, 0x2, 0x2, 0x420, 0x41e, 0x3, 0x2, 0x2, 0x2, 0x420, 
       0x421, 0x3, 0x2, 0x2, 0x2, 0x421, 0xab, 0x3, 0x2, 0x2, 0x2, 0x422, 
       0x420, 0x3, 0x2, 0x2, 0x2, 0x423, 0x428, 0x5, 0xae, 0x58, 0x2, 0x424, 
       0x425, 0x7, 0x3d, 0x2, 0x2, 0x425, 0x427, 0x5, 0xae, 0x58, 0x2, 0x426, 
       0x424, 0x3, 0x2, 0x2, 0x2, 0x427, 0x42a, 0x3, 0x2, 0x2, 0x2, 0x428, 
       0x426, 0x3, 0x2, 0x2, 0x2, 0x428, 0x429, 0x3, 0x2, 0x2, 0x2, 0x429, 
       0xad, 0x3, 0x2, 0x2, 0x2, 0x42a, 0x428, 0x3, 0x2, 0x2, 0x2, 0x42b, 
       0x42c, 0x5, 0xca, 0x66, 0x2, 0x42c, 0x42d, 0x7, 0x41, 0x2, 0x2, 0x42d, 
       0x42e, 0x5, 0x72, 0x3a, 0x2, 0x42e, 0xaf, 0x3, 0x2, 0x2, 0x2, 0x42f, 
       0x435, 0x5, 0xb8, 0x5d, 0x2, 0x430, 0x431, 0x7, 0x1b, 0x2, 0x2, 0x431, 
       0x432, 0x5, 0xb8, 0x5d, 0x2, 0x432, 0x433, 0x7, 0x14, 0x2, 0x2, 0x433, 
       0x434, 0x5, 0xb0, 0x59, 0x2, 0x434, 0x436, 0x3, 0x2, 0x2, 0x2, 0x435, 
       0x430, 0x3, 0x2, 0x2, 0x2, 0x435, 0x436, 0x3, 0x2, 0x2, 0x2, 0x436, 
       0x439, 0x3, 0x2, 0x2, 0x2, 0x437, 0x439, 0x5, 0xb4, 0x5b, 0x2, 0x438, 
       0x42f, 0x3, 0x2, 0x2, 0x2, 0x438, 0x437, 0x3, 0x2, 0x2, 0x2, 0x439, 
       0xb1, 0x3, 0x2, 0x2, 0x2, 0x43a, 0x43d, 0x5, 0xb8, 0x5d, 0x2, 0x43b, 
       0x43d, 0x5, 0xb6, 0x5c, 0x2, 0x43c, 0x43a, 0x3, 0x2, 0x2, 0x2, 0x43c, 
       0x43b, 0x3, 0x2, 0x2, 0x2, 0x43d, 0xb3, 0x3, 0x2, 0x2, 0x2, 0x43e, 
       0x440, 0x7, 0x1f, 0x2, 0x2, 0x43f, 0x441, 0x5, 0x18, 0xd, 0x2, 0x440, 
       0x43f, 0x3, 0x2, 0x2, 0x2, 0x440, 0x441, 0x3, 0x2, 0x2, 0x2, 0x441, 
       0x442, 0x3, 0x2, 0x2, 0x2, 0x442, 0x443, 0x7, 0x3e, 0x2, 0x2, 0x443, 
       0x444, 0x5, 0xb0, 0x59, 0x2, 0x444, 0xb5, 0x3, 0x2, 0x2, 0x2, 0x445, 
       0x447, 0x7, 0x1f, 0x2, 0x2, 0x446, 0x448, 0x5, 0x18, 0xd, 0x2, 0x447, 
       0x446, 0x3, 0x2, 0x2, 0x2, 0x447, 0x448, 0x3, 0x2, 0x2, 0x2, 0x448, 
       0x449, 0x3, 0x2, 0x2, 0x2, 0x449, 0x44a, 0x7, 0x3e, 0x2, 0x2, 0x44a, 
       0x44b, 0x5, 0xb2, 0x5a, 0x2, 0x44b, 0xb7, 0x3, 0x2, 0x2, 0x2, 0x44c, 
       0x451, 0x5, 0xba, 0x5e, 0x2, 0x44d, 0x44e, 0x7, 0x24, 0x2, 0x2, 0x44e, 
       0x450, 0x5, 0xba, 0x5e, 0x2, 0x44f, 0x44d, 0x3, 0x2, 0x2, 0x2, 0x450, 
       0x453, 0x3, 0x2, 0x2, 0x2, 0x451, 0x44f, 0x3, 0x2, 0x2, 0x2, 0x451, 
       0x452, 0x3, 0x2, 0x2, 0x2, 0x452, 0xb9, 0x3, 0x2, 0x2, 0x2, 0x453, 
       0x451, 0x3, 0x2, 0x2, 0x2, 0x454, 0x459, 0x5, 0xbc, 0x5f, 0x2, 0x455, 
       0x456, 0x7, 0x8, 0x2, 0x2, 0x456, 0x458, 0x5, 0xbc, 0x5f, 0x2, 0x457, 
       0x455, 0x3, 0x2, 0x2, 0x2, 0x458, 0x45b, 0x3, 0x2, 0x2, 0x2, 0x459, 
       0x457, 0x3, 0x2, 0x2, 0x2, 0x459, 0x45a, 0x3, 0x2, 0x2, 0x2, 0x45a, 
       0xbb, 0x3, 0x2, 0x2, 0x2, 0x45b, 0x459, 0x3, 0x2, 0x2, 0x2, 0x45c, 
       0x45d, 0x7, 0x23, 0x2, 0x2, 0x45d, 0x460, 0x5, 0xbc, 0x5f, 0x2, 0x45e, 
       0x460, 0x5, 0xbe, 0x60, 0x2, 0x45f, 0x45c, 0x3, 0x2, 0x2, 0x2, 0x45f, 
       0x45e, 0x3, 0x2, 0x2, 0x2, 0x460, 0xbd, 0x3, 0x2, 0x2, 0x2, 0x461, 
       0x467, 0x5, 0xc4, 0x63, 0x2, 0x462, 0x463, 0x5, 0xc0, 0x61, 0x2, 
       0x463, 0x464, 0x5, 0xc4, 0x63, 0x2, 0x464, 0x466, 0x3, 0x2, 0x2, 
       0x2, 0x465, 0x462, 0x3, 0x2, 0x2, 0x2, 0x466, 0x469, 0x3, 0x2, 0x2, 
       0x2, 0x467, 0x465, 0x3, 0x2, 0x2, 0x2, 0x467, 0x468, 0x3, 0x2, 0x2, 
       0x2, 0x468, 0xbf, 0x3, 0x2, 0x2, 0x2, 0x469, 0x467, 0x3, 0x2, 0x2, 
       0x2, 0x46a, 0x478, 0x7, 0x51, 0x2, 0x2, 0x46b, 0x478, 0x7, 0x52, 
       0x2, 0x2, 0x46c, 0x478, 0x7, 0x53, 0x2, 0x2, 0x46d, 0x478, 0x7, 0x54, 
       0x2, 0x2, 0x46e, 0x478, 0x7, 0x55, 0x2, 0x2, 0x46f, 0x478, 0x7, 0x56, 
       0x2, 0x2, 0x470, 0x478, 0x7, 0x57, 0x2, 0x2, 0x471, 0x478, 0x7, 0x1d, 
       0x2, 0x2, 0x472, 0x473, 0x7, 0x23, 0x2, 0x2, 0x473, 0x478, 0x7, 0x1d, 
       0x2, 0x2, 0x474, 0x478, 0x7, 0x1e, 0x2, 0x2, 0x475, 0x476, 0x7, 0x1e, 
       0x2, 0x2, 0x476, 0x478, 0x7, 0x23, 0x2, 0x2, 0x477, 0x46a, 0x3, 0x2, 
       0x2, 0x2, 0x477, 0x46b, 0x3, 0x2, 0x2, 0x2, 0x477, 0x46c, 0x3, 0x2, 
       0x2, 0x2, 0x477, 0x46d, 0x3, 0x2, 0x2, 0x2, 0x477, 0x46e, 0x3, 0x2, 
       0x2, 0x2, 0x477, 0x46f, 0x3, 0x2, 0x2, 0x2, 0x477, 0x470, 0x3, 0x2, 
       0x2, 0x2, 0x477, 0x471, 0x3, 0x2, 0x2, 0x2, 0x477, 0x472, 0x3, 0x2, 
       0x2, 0x2, 0x477, 0x474, 0x3, 0x2, 0x2, 0x2, 0x477, 0x475, 0x3, 0x2, 
       0x2, 0x2, 0x478, 0xc1, 0x3, 0x2, 0x2, 0x2, 0x479, 0x47a, 0x7, 0x3a, 
       0x2, 0x2, 0x47a, 0x47b, 0x5, 0xc4, 0x63, 0x2, 0x47b, 0xc3, 0x3, 0x2, 
       0x2, 0x2, 0x47c, 0x47d, 0x8, 0x63, 0x1, 0x2, 0x47d, 0x485, 0x5, 0xc6, 
       0x64, 0x2, 0x47e, 0x480, 0x9, 0x4, 0x2, 0x2, 0x47f, 0x47e, 0x3, 0x2, 
       0x2, 0x2, 0x480, 0x481, 0x3, 0x2, 0x2, 0x2, 0x481, 0x47f, 0x3, 0x2, 
       0x2, 0x2, 0x481, 0x482, 0x3, 0x2, 0x2, 0x2, 0x482, 0x483, 0x3, 0x2, 
       0x2, 0x2, 0x483, 0x485, 0x5, 0xc4, 0x63, 0x9, 0x484, 0x47c, 0x3, 
       0x2, 0x2, 0x2, 0x484, 0x47f, 0x3, 0x2, 0x2, 0x2, 0x485, 0x49d, 0x3, 
       0x2, 0x2, 0x2, 0x486, 0x487, 0xc, 0xa, 0x2, 0x2, 0x487, 0x488, 0x7, 
       0x40, 0x2, 0x2, 0x488, 0x49c, 0x5, 0xc4, 0x63, 0xb, 0x489, 0x48a, 
       0xc, 0x8, 0x2, 0x2, 0x48a, 0x48b, 0x9, 0x5, 0x2, 0x2, 0x48b, 0x49c, 
       0x5, 0xc4, 0x63, 0x9, 0x48c, 0x48d, 0xc, 0x7, 0x2, 0x2, 0x48d, 0x48e, 
       0x9, 0x6, 0x2, 0x2, 0x48e, 0x49c, 0x5, 0xc4, 0x63, 0x8, 0x48f, 0x490, 
       0xc, 0x6, 0x2, 0x2, 0x490, 0x491, 0x9, 0x7, 0x2, 0x2, 0x491, 0x49c, 
       0x5, 0xc4, 0x63, 0x7, 0x492, 0x493, 0xc, 0x5, 0x2, 0x2, 0x493, 0x494, 
       0x7, 0x46, 0x2, 0x2, 0x494, 0x49c, 0x5, 0xc4, 0x63, 0x6, 0x495, 0x496, 
       0xc, 0x4, 0x2, 0x2, 0x496, 0x497, 0x7, 0x45, 0x2, 0x2, 0x497, 0x49c, 
       0x5, 0xc4, 0x63, 0x5, 0x498, 0x499, 0xc, 0x3, 0x2, 0x2, 0x499, 0x49a, 
       0x7, 0x44, 0x2, 0x2, 0x49a, 0x49c, 0x5, 0xc4, 0x63, 0x4, 0x49b, 0x486, 
       0x3, 0x2, 0x2, 0x2, 0x49b, 0x489, 0x3, 0x2, 0x2, 0x2, 0x49b, 0x48c, 
       0x3, 0x2, 0x2, 0x2, 0x49b, 0x48f, 0x3, 0x2, 0x2, 0x2, 0x49b, 0x492, 
       0x3, 0x2, 0x2, 0x2, 0x49b, 0x495, 0x3, 0x2, 0x2, 0x2, 0x49b, 0x498, 
       0x3, 0x2, 0x2, 0x2, 0x49c, 0x49f, 0x3, 0x2, 0x2, 0x2, 0x49d, 0x49b, 
       0x3, 0x2, 0x2, 0x2, 0x49d, 0x49e, 0x3, 0x2, 0x2, 0x2, 0x49e, 0xc5, 
       0x3, 0x2, 0x2, 0x2, 0x49f, 0x49d, 0x3, 0x2, 0x2, 0x2, 0x4a0, 0x4a2, 
       0x7, 0xc, 0x2, 0x2, 0x4a1, 0x4a0, 0x3, 0x2, 0x2, 0x2, 0x4a1, 0x4a2, 
       0x3, 0x2, 0x2, 0x2, 0x4a2, 0x4a3, 0x3, 0x2, 0x2, 0x2, 0x4a3, 0x4a7, 
       0x5, 0xc8, 0x65, 0x2, 0x4a4, 0x4a6, 0x5, 0xce, 0x68, 0x2, 0x4a5, 
       0x4a4, 0x3, 0x2, 0x2, 0x2, 0x4a6, 0x4a9, 0x3, 0x2, 0x2, 0x2, 0x4a7, 
       0x4a5, 0x3, 0x2, 0x2, 0x2, 0x4a7, 0x4a8, 0x3, 0x2, 0x2, 0x2, 0x4a8, 
       0xc7, 0x3, 0x2, 0x2, 0x2, 0x4a9, 0x4a7, 0x3, 0x2, 0x2, 0x2, 0x4aa, 
       0x4ad, 0x7, 0x3b, 0x2, 0x2, 0x4ab, 0x4ae, 0x5, 0xea, 0x76, 0x2, 0x4ac, 
       0x4ae, 0x5, 0xcc, 0x67, 0x2, 0x4ad, 0x4ab, 0x3, 0x2, 0x2, 0x2, 0x4ad, 
       0x4ac, 0x3, 0x2, 0x2, 0x2, 0x4ad, 0x4ae, 0x3, 0x2, 0x2, 0x2, 0x4ae, 
       0x4af, 0x3, 0x2, 0x2, 0x2, 0x4af, 0x4c6, 0x7, 0x3c, 0x2, 0x2, 0x4b0, 
       0x4b2, 0x7, 0x42, 0x2, 0x2, 0x4b1, 0x4b3, 0x5, 0xcc, 0x67, 0x2, 0x4b2, 
       0x4b1, 0x3, 0x2, 0x2, 0x2, 0x4b2, 0x4b3, 0x3, 0x2, 0x2, 0x2, 0x4b3, 
       0x4b4, 0x3, 0x2, 0x2, 0x2, 0x4b4, 0x4c6, 0x7, 0x43, 0x2, 0x2, 0x4b5, 
       0x4b7, 0x7, 0x4f, 0x2, 0x2, 0x4b6, 0x4b8, 0x5, 0xda, 0x6e, 0x2, 0x4b7, 
       0x4b6, 0x3, 0x2, 0x2, 0x2, 0x4b7, 0x4b8, 0x3, 0x2, 0x2, 0x2, 0x4b8, 
       0x4b9, 0x3, 0x2, 0x2, 0x2, 0x4b9, 0x4c6, 0x7, 0x50, 0x2, 0x2, 0x4ba, 
       0x4c6, 0x5, 0xca, 0x66, 0x2, 0x4bb, 0x4c6, 0x7, 0x6, 0x2, 0x2, 0x4bc, 
       0x4be, 0x7, 0x5, 0x2, 0x2, 0x4bd, 0x4bc, 0x3, 0x2, 0x2, 0x2, 0x4be, 
       0x4bf, 0x3, 0x2, 0x2, 0x2, 0x4bf, 0x4bd, 0x3, 0x2, 0x2, 0x2, 0x4bf, 
       0x4c0, 0x3, 0x2, 0x2, 0x2, 0x4c0, 0x4c6, 0x3, 0x2, 0x2, 0x2, 0x4c1, 
       0x4c6, 0x7, 0x39, 0x2, 0x2, 0x4c2, 0x4c6, 0x7, 0x21, 0x2, 0x2, 0x4c3, 
       0x4c6, 0x7, 0x28, 0x2, 0x2, 0x4c4, 0x4c6, 0x7, 0x16, 0x2, 0x2, 0x4c5, 
       0x4aa, 0x3, 0x2, 0x2, 0x2, 0x4c5, 0x4b0, 0x3, 0x2, 0x2, 0x2, 0x4c5, 
       0x4b5, 0x3, 0x2, 0x2, 0x2, 0x4c5, 0x4ba, 0x3, 0x2, 0x2, 0x2, 0x4c5, 
       0x4bb, 0x3, 0x2, 0x2, 0x2, 0x4c5, 0x4bd, 0x3, 0x2, 0x2, 0x2, 0x4c5, 
       0x4c1, 0x3, 0x2, 0x2, 0x2, 0x4c5, 0x4c2, 0x3, 0x2, 0x2, 0x2, 0x4c5, 
       0x4c3, 0x3, 0x2, 0x2, 0x2, 0x4c5, 0x4c4, 0x3, 0x2, 0x2, 0x2, 0x4c6, 
       0xc9, 0x3, 0x2, 0x2, 0x2, 0x4c7, 0x4c8, 0x9, 0x8, 0x2, 0x2, 0x4c8, 
       0xcb, 0x3, 0x2, 0x2, 0x2, 0x4c9, 0x4cc, 0x5, 0xb0, 0x59, 0x2, 0x4ca, 
       0x4cc, 0x5, 0xc2, 0x62, 0x2, 0x4cb, 0x4c9, 0x3, 0x2, 0x2, 0x2, 0x4cb, 
       0x4ca, 0x3, 0x2, 0x2, 0x2, 0x4cc, 0x4db, 0x3, 0x2, 0x2, 0x2, 0x4cd, 
       0x4dc, 0x5, 0xe4, 0x73, 0x2, 0x4ce, 0x4d1, 0x7, 0x3d, 0x2, 0x2, 0x4cf, 
       0x4d2, 0x5, 0xb0, 0x59, 0x2, 0x4d0, 0x4d2, 0x5, 0xc2, 0x62, 0x2, 
       0x4d1, 0x4cf, 0x3, 0x2, 0x2, 0x2, 0x4d1, 0x4d0, 0x3, 0x2, 0x2, 0x2, 
       0x4d2, 0x4d4, 0x3, 0x2, 0x2, 0x2, 0x4d3, 0x4ce, 0x3, 0x2, 0x2, 0x2, 
       0x4d4, 0x4d7, 0x3, 0x2, 0x2, 0x2, 0x4d5, 0x4d3, 0x3, 0x2, 0x2, 0x2, 
       0x4d5, 0x4d6, 0x3, 0x2, 0x2, 0x2, 0x4d6, 0x4d9, 0x3, 0x2, 0x2, 0x2, 
       0x4d7, 0x4d5, 0x3, 0x2, 0x2, 0x2, 0x4d8, 0x4da, 0x7, 0x3d, 0x2, 0x2, 
       0x4d9, 0x4d8, 0x3, 0x2, 0x2, 0x2, 0x4d9, 0x4da, 0x3, 0x2, 0x2, 0x2, 
       0x4da, 0x4dc, 0x3, 0x2, 0x2, 0x2, 0x4db, 0x4cd, 0x3, 0x2, 0x2, 0x2, 
       0x4db, 0x4d5, 0x3, 0x2, 0x2, 0x2, 0x4dc, 0xcd, 0x3, 0x2, 0x2, 0x2, 
       0x4dd, 0x4df, 0x7, 0x3b, 0x2, 0x2, 0x4de, 0x4e0, 0x5, 0xde, 0x70, 
       0x2, 0x4df, 0x4de, 0x3, 0x2, 0x2, 0x2, 0x4df, 0x4e0, 0x3, 0x2, 0x2, 
       0x2, 0x4e0, 0x4e1, 0x3, 0x2, 0x2, 0x2, 0x4e1, 0x4e9, 0x7, 0x3c, 0x2, 
       0x2, 0x4e2, 0x4e3, 0x7, 0x42, 0x2, 0x2, 0x4e3, 0x4e4, 0x5, 0xd0, 
       0x69, 0x2, 0x4e4, 0x4e5, 0x7, 0x43, 0x2, 0x2, 0x4e5, 0x4e9, 0x3, 
       0x2, 0x2, 0x2, 0x4e6, 0x4e7, 0x7, 0x38, 0x2, 0x2, 0x4e7, 0x4e9, 0x5, 
       0xca, 0x66, 0x2, 0x4e8, 0x4dd, 0x3, 0x2, 0x2, 0x2, 0x4e8, 0x4e2, 
       0x3, 0x2, 0x2, 0x2, 0x4e8, 0x4e6, 0x3, 0x2, 0x2, 0x2, 0x4e9, 0xcf, 
       0x3, 0x2, 0x2, 0x2, 0x4ea, 0x4ef, 0x5, 0xd2, 0x6a, 0x2, 0x4eb, 0x4ec, 
       0x7, 0x3d, 0x2, 0x2, 0x4ec, 0x4ee, 0x5, 0xd2, 0x6a, 0x2, 0x4ed, 0x4eb, 
       0x3, 0x2, 0x2, 0x2, 0x4ee, 0x4f1, 0x3, 0x2, 0x2, 0x2, 0x4ef, 0x4ed, 
       0x3, 0x2, 0x2, 0x2, 0x4ef, 0x4f0, 0x3, 0x2, 0x2, 0x2, 0x4f0, 0x4f3, 
       0x3, 0x2, 0x2, 0x2, 0x4f1, 0x4ef, 0x3, 0x2, 0x2, 0x2, 0x4f2, 0x4f4, 
       0x7, 0x3d, 0x2, 0x2, 0x4f3, 0x4f2, 0x3, 0x2, 0x2, 0x2, 0x4f3, 0x4f4, 
       0x3, 0x2, 0x2, 0x2, 0x4f4, 0xd1, 0x3, 0x2, 0x2, 0x2, 0x4f5, 0x501, 
       0x5, 0xb0, 0x59, 0x2, 0x4f6, 0x4f8, 0x5, 0xb0, 0x59, 0x2, 0x4f7, 
       0x4f6, 0x3, 0x2, 0x2, 0x2, 0x4f7, 0x4f8, 0x3, 0x2, 0x2, 0x2, 0x4f8, 
       0x4f9, 0x3, 0x2, 0x2, 0x2, 0x4f9, 0x4fb, 0x7, 0x3e, 0x2, 0x2, 0x4fa, 
       0x4fc, 0x5, 0xb0, 0x59, 0x2, 0x4fb, 0x4fa, 0x3, 0x2, 0x2, 0x2, 0x4fb, 
       0x4fc, 0x3, 0x2, 0x2, 0x2, 0x4fc, 0x4fe, 0x3, 0x2, 0x2, 0x2, 0x4fd, 
       0x4ff, 0x5, 0xd4, 0x6b, 0x2, 0x4fe, 0x4fd, 0x3, 0x2, 0x2, 0x2, 0x4fe, 
       0x4ff, 0x3, 0x2, 0x2, 0x2, 0x4ff, 0x501, 0x3, 0x2, 0x2, 0x2, 0x500, 
       0x4f5, 0x3, 0x2, 0x2, 0x2, 0x500, 0x4f7, 0x3, 0x2, 0x2, 0x2, 0x501, 
       0xd3, 0x3, 0x2, 0x2, 0x2, 0x502, 0x504, 0x7, 0x3e, 0x2, 0x2, 0x503, 
       0x505, 0x5, 0xb0, 0x59, 0x2, 0x504, 0x503, 0x3, 0x2, 0x2, 0x2, 0x504, 
       0x505, 0x3, 0x2, 0x2, 0x2, 0x505, 0xd5, 0x3, 0x2, 0x2, 0x2, 0x506, 
       0x509, 0x5, 0xc4, 0x63, 0x2, 0x507, 0x509, 0x5, 0xc2, 0x62, 0x2, 
       0x508, 0x506, 0x3, 0x2, 0x2, 0x2, 0x508, 0x507, 0x3, 0x2, 0x2, 0x2, 
       0x509, 0x511, 0x3, 0x2, 0x2, 0x2, 0x50a, 0x50d, 0x7, 0x3d, 0x2, 0x2, 
       0x50b, 0x50e, 0x5, 0xc4, 0x63, 0x2, 0x50c, 0x50e, 0x5, 0xc2, 0x62, 
       0x2, 0x50d, 0x50b, 0x3, 0x2, 0x2, 0x2, 0x50d, 0x50c, 0x3, 0x2, 0x2, 
       0x2, 0x50e, 0x510, 0x3, 0x2, 0x2, 0x2, 0x50f, 0x50a, 0x3, 0x2, 0x2, 
       0x2, 0x510, 0x513, 0x3, 0x2, 0x2, 0x2, 0x511, 0x50f, 0x3, 0x2, 0x2, 
       0x2, 0x511, 0x512, 0x3, 0x2, 0x2, 0x2, 0x512, 0x515, 0x3, 0x2, 0x2, 
       0x2, 0x513, 0x511, 0x3, 0x2, 0x2, 0x2, 0x514, 0x516, 0x7, 0x3d, 0x2, 
       0x2, 0x515, 0x514, 0x3, 0x2, 0x2, 0x2, 0x515, 0x516, 0x3, 0x2, 0x2, 
       0x2, 0x516, 0xd7, 0x3, 0x2, 0x2, 0x2, 0x517, 0x51c, 0x5, 0xb0, 0x59, 
       0x2, 0x518, 0x519, 0x7, 0x3d, 0x2, 0x2, 0x519, 0x51b, 0x5, 0xb0, 
       0x59, 0x2, 0x51a, 0x518, 0x3, 0x2, 0x2, 0x2, 0x51b, 0x51e, 0x3, 0x2, 
       0x2, 0x2, 0x51c, 0x51a, 0x3, 0x2, 0x2, 0x2, 0x51c, 0x51d, 0x3, 0x2, 
       0x2, 0x2, 0x51d, 0x520, 0x3, 0x2, 0x2, 0x2, 0x51e, 0x51c, 0x3, 0x2, 
       0x2, 0x2, 0x51f, 0x521, 0x7, 0x3d, 0x2, 0x2, 0x520, 0x51f, 0x3, 0x2, 
       0x2, 0x2, 0x520, 0x521, 0x3, 0x2, 0x2, 0x2, 0x521, 0xd9, 0x3, 0x2, 
       0x2, 0x2, 0x522, 0x523, 0x5, 0xb0, 0x59, 0x2, 0x523, 0x524, 0x7, 
       0x3e, 0x2, 0x2, 0x524, 0x525, 0x5, 0xb0, 0x59, 0x2, 0x525, 0x529, 
       0x3, 0x2, 0x2, 0x2, 0x526, 0x527, 0x7, 0x40, 0x2, 0x2, 0x527, 0x529, 
       0x5, 0xc4, 0x63, 0x2, 0x528, 0x522, 0x3, 0x2, 0x2, 0x2, 0x528, 0x526, 
       0x3, 0x2, 0x2, 0x2, 0x529, 0x53c, 0x3, 0x2, 0x2, 0x2, 0x52a, 0x53d, 
       0x5, 0xe4, 0x73, 0x2, 0x52b, 0x532, 0x7, 0x3d, 0x2, 0x2, 0x52c, 0x52d, 
       0x5, 0xb0, 0x59, 0x2, 0x52d, 0x52e, 0x7, 0x3e, 0x2, 0x2, 0x52e, 0x52f, 
       0x5, 0xb0, 0x59, 0x2, 0x52f, 0x533, 0x3, 0x2, 0x2, 0x2, 0x530, 0x531, 
       0x7, 0x40, 0x2, 0x2, 0x531, 0x533, 0x5, 0xc4, 0x63, 0x2, 0x532, 0x52c, 
       0x3, 0x2, 0x2, 0x2, 0x532, 0x530, 0x3, 0x2, 0x2, 0x2, 0x533, 0x535, 
       0x3, 0x2, 0x2, 0x2, 0x534, 0x52b, 0x3, 0x2, 0x2, 0x2, 0x535, 0x538, 
       0x3, 0x2, 0x2, 0x2, 0x536, 0x534, 0x3, 0x2, 0x2, 0x2, 0x536, 0x537, 
       0x3, 0x2, 0x2, 0x2, 0x537, 0x53a, 0x3, 0x2, 0x2, 0x2, 0x538, 0x536, 
       0x3, 0x2, 0x2, 0x2, 0x539, 0x53b, 0x7, 0x3d, 0x2, 0x2, 0x53a, 0x539, 
       0x3, 0x2, 0x2, 0x2, 0x53a, 0x53b, 0x3, 0x2, 0x2, 0x2, 0x53b, 0x53d, 
       0x3, 0x2, 0x2, 0x2, 0x53c, 0x52a, 0x3, 0x2, 0x2, 0x2, 0x53c, 0x536, 
       0x3, 0x2, 0x2, 0x2, 0x53d, 0x553, 0x3, 0x2, 0x2, 0x2, 0x53e, 0x541, 
       0x5, 0xb0, 0x59, 0x2, 0x53f, 0x541, 0x5, 0xc2, 0x62, 0x2, 0x540, 
       0x53e, 0x3, 0x2, 0x2, 0x2, 0x540, 0x53f, 0x3, 0x2, 0x2, 0x2, 0x541, 
       0x550, 0x3, 0x2, 0x2, 0x2, 0x542, 0x551, 0x5, 0xe4, 0x73, 0x2, 0x543, 
       0x546, 0x7, 0x3d, 0x2, 0x2, 0x544, 0x547, 0x5, 0xb0, 0x59, 0x2, 0x545, 
       0x547, 0x5, 0xc2, 0x62, 0x2, 0x546, 0x544, 0x3, 0x2, 0x2, 0x2, 0x546, 
       0x545, 0x3, 0x2, 0x2, 0x2, 0x547, 0x549, 0x3, 0x2, 0x2, 0x2, 0x548, 
       0x543, 0x3, 0x2, 0x2, 0x2, 0x549, 0x54c, 0x3, 0x2, 0x2, 0x2, 0x54a, 
       0x548, 0x3, 0x2, 0x2, 0x2, 0x54a, 0x54b, 0x3, 0x2, 0x2, 0x2, 0x54b, 
       0x54e, 0x3, 0x2, 0x2, 0x2, 0x54c, 0x54a, 0x3, 0x2, 0x2, 0x2, 0x54d, 
       0x54f, 0x7, 0x3d, 0x2, 0x2, 0x54e, 0x54d, 0x3, 0x2, 0x2, 0x2, 0x54e, 
       0x54f, 0x3, 0x2, 0x2, 0x2, 0x54f, 0x551, 0x3, 0x2, 0x2, 0x2, 0x550, 
       0x542, 0x3, 0x2, 0x2, 0x2, 0x550, 0x54a, 0x3, 0x2, 0x2, 0x2, 0x551, 
       0x553, 0x3, 0x2, 0x2, 0x2, 0x552, 0x528, 0x3, 0x2, 0x2, 0x2, 0x552, 
       0x540, 0x3, 0x2, 0x2, 0x2, 0x553, 0xdb, 0x3, 0x2, 0x2, 0x2, 0x554, 
       0x555, 0x7, 0xf, 0x2, 0x2, 0x555, 0x55b, 0x5, 0xca, 0x66, 0x2, 0x556, 
       0x558, 0x7, 0x3b, 0x2, 0x2, 0x557, 0x559, 0x5, 0xde, 0x70, 0x2, 0x558, 
       0x557, 0x3, 0x2, 0x2, 0x2, 0x558, 0x559, 0x3, 0x2, 0x2, 0x2, 0x559, 
       0x55a, 0x3, 0x2, 0x2, 0x2, 0x55a, 0x55c, 0x7, 0x3c, 0x2, 0x2, 0x55b, 
       0x556, 0x3, 0x2, 0x2, 0x2, 0x55b, 0x55c, 0x3, 0x2, 0x2, 0x2, 0x55c, 
       0x55d, 0x3, 0x2, 0x2, 0x2, 0x55d, 0x55e, 0x7, 0x3e, 0x2, 0x2, 0x55e, 
       0x55f, 0x5, 0x62, 0x32, 0x2, 0x55f, 0xdd, 0x3, 0x2, 0x2, 0x2, 0x560, 
       0x565, 0x5, 0xe0, 0x71, 0x2, 0x561, 0x562, 0x7, 0x3d, 0x2, 0x2, 0x562, 
       0x564, 0x5, 0xe0, 0x71, 0x2, 0x563, 0x561, 0x3, 0x2, 0x2, 0x2, 0x564, 
       0x567, 0x3, 0x2, 0x2, 0x2, 0x565, 0x563, 0x3, 0x2, 0x2, 0x2, 0x565, 
       0x566, 0x3, 0x2, 0x2, 0x2, 0x566, 0x569, 0x3, 0x2, 0x2, 0x2, 0x567, 
       0x565, 0x3, 0x2, 0x2, 0x2, 0x568, 0x56a, 0x7, 0x3d, 0x2, 0x2, 0x569, 
       0x568, 0x3, 0x2, 0x2, 0x2, 0x569, 0x56a, 0x3, 0x2, 0x2, 0x2, 0x56a, 
       0xdf, 0x3, 0x2, 0x2, 0x2, 0x56b, 0x56d, 0x5, 0xb0, 0x59, 0x2, 0x56c, 
       0x56e, 0x5, 0xe4, 0x73, 0x2, 0x56d, 0x56c, 0x3, 0x2, 0x2, 0x2, 0x56d, 
       0x56e, 0x3, 0x2, 0x2, 0x2, 0x56e, 0x578, 0x3, 0x2, 0x2, 0x2, 0x56f, 
       0x570, 0x5, 0xb0, 0x59, 0x2, 0x570, 0x571, 0x7, 0x41, 0x2, 0x2, 0x571, 
       0x572, 0x5, 0xb0, 0x59, 0x2, 0x572, 0x578, 0x3, 0x2, 0x2, 0x2, 0x573, 
       0x574, 0x7, 0x40, 0x2, 0x2, 0x574, 0x578, 0x5, 0xb0, 0x59, 0x2, 0x575, 
       0x576, 0x7, 0x3a, 0x2, 0x2, 0x576, 0x578, 0x5, 0xb0, 0x59, 0x2, 0x577, 
       0x56b, 0x3, 0x2, 0x2, 0x2, 0x577, 0x56f, 0x3, 0x2, 0x2, 0x2, 0x577, 
       0x573, 0x3, 0x2, 0x2, 0x2, 0x577, 0x575, 0x3, 0x2, 0x2, 0x2, 0x578, 
       0xe1, 0x3, 0x2, 0x2, 0x2, 0x579, 0x57c, 0x5, 0xe4, 0x73, 0x2, 0x57a, 
       0x57c, 0x5, 0xe6, 0x74, 0x2, 0x57b, 0x579, 0x3, 0x2, 0x2, 0x2, 0x57b, 
       0x57a, 0x3, 0x2, 0x2, 0x2, 0x57c, 0xe3, 0x3, 0x2, 0x2, 0x2, 0x57d, 
       0x57f, 0x7, 0xb, 0x2, 0x2, 0x57e, 0x57d, 0x3, 0x2, 0x2, 0x2, 0x57e, 
       0x57f, 0x3, 0x2, 0x2, 0x2, 0x57f, 0x580, 0x3, 0x2, 0x2, 0x2, 0x580, 
       0x581, 0x7, 0x18, 0x2, 0x2, 0x581, 0x582, 0x5, 0xd6, 0x6c, 0x2, 0x582, 
       0x583, 0x7, 0x1d, 0x2, 0x2, 0x583, 0x585, 0x5, 0xb8, 0x5d, 0x2, 0x584, 
       0x586, 0x5, 0xe2, 0x72, 0x2, 0x585, 0x584, 0x3, 0x2, 0x2, 0x2, 0x585, 
       0x586, 0x3, 0x2, 0x2, 0x2, 0x586, 0xe5, 0x3, 0x2, 0x2, 0x2, 0x587, 
       0x588, 0x7, 0x1b, 0x2, 0x2, 0x588, 0x58a, 0x5, 0xb2, 0x5a, 0x2, 0x589, 
       0x58b, 0x5, 0xe2, 0x72, 0x2, 0x58a, 0x589, 0x3, 0x2, 0x2, 0x2, 0x58a, 
       0x58b, 0x3, 0x2, 0x2, 0x2, 0x58b, 0xe7, 0x3, 0x2, 0x2, 0x2, 0x58c, 
       0x58d, 0x5, 0xca, 0x66, 0x2, 0x58d, 0xe9, 0x3, 0x2, 0x2, 0x2, 0x58e, 
       0x590, 0x7, 0x2d, 0x2, 0x2, 0x58f, 0x591, 0x5, 0xec, 0x77, 0x2, 0x590, 
       0x58f, 0x3, 0x2, 0x2, 0x2, 0x590, 0x591, 0x3, 0x2, 0x2, 0x2, 0x591, 
       0xeb, 0x3, 0x2, 0x2, 0x2, 0x592, 0x593, 0x7, 0x19, 0x2, 0x2, 0x593, 
       0x596, 0x5, 0xb0, 0x59, 0x2, 0x594, 0x596, 0x5, 0xd8, 0x6d, 0x2, 
       0x595, 0x592, 0x3, 0x2, 0x2, 0x2, 0x595, 0x594, 0x3, 0x2, 0x2, 0x2, 
       0x596, 0xed, 0x3, 0x2, 0x2, 0x2, 0x597, 0x599, 0x7, 0x5, 0x2, 0x2, 
       0x598, 0x597, 0x3, 0x2, 0x2, 0x2, 0x599, 0x59a, 0x3, 0x2, 0x2, 0x2, 
       0x59a, 0x598, 0x3, 0x2, 0x2, 0x2, 0x59a, 0x59b, 0x3, 0x2, 0x2, 0x2, 
       0x59b, 0xef, 0x3, 0x2, 0x2, 0x2, 0xcb, 0xf5, 0xf9, 0xfb, 0x104, 0x10d, 
       0x110, 0x117, 0x11d, 0x127, 0x12e, 0x135, 0x13b, 0x13f, 0x145, 0x14b, 
       0x14f, 0x156, 0x158, 0x15a, 0x15f, 0x161, 0x163, 0x167, 0x16d, 0x171, 
       0x178, 0x17a, 0x17c, 0x181, 0x183, 0x188, 0x18d, 0x193, 0x197, 0x19d, 
       0x1a3, 0x1a7, 0x1ae, 0x1b0, 0x1b2, 0x1b7, 0x1b9, 0x1bb, 0x1bf, 0x1c5, 
       0x1c9, 0x1d0, 0x1d2, 0x1d4, 0x1d9, 0x1db, 0x1e1, 0x1e8, 0x1ec, 0x1f8, 
       0x1ff, 0x204, 0x208, 0x20b, 0x211, 0x215, 0x21a, 0x21e, 0x222, 0x230, 
       0x238, 0x240, 0x242, 0x246, 0x24f, 0x256, 0x258, 0x261, 0x266, 0x26b, 
       0x272, 0x276, 0x27d, 0x285, 0x28e, 0x297, 0x29e, 0x2aa, 0x2b0, 0x2bd, 
       0x2c3, 0x2cc, 0x2d7, 0x2e2, 0x2e7, 0x2ec, 0x2f1, 0x2f9, 0x302, 0x308, 
       0x30a, 0x312, 0x316, 0x320, 0x327, 0x32a, 0x330, 0x333, 0x338, 0x33d, 
       0x347, 0x34b, 0x356, 0x361, 0x36b, 0x375, 0x37f, 0x384, 0x389, 0x39e, 
       0x3a2, 0x3aa, 0x3af, 0x3b2, 0x3b7, 0x3be, 0x3c2, 0x3c6, 0x3cc, 0x3d3, 
       0x3dc, 0x3e3, 0x3e7, 0x3ee, 0x3f3, 0x403, 0x40b, 0x415, 0x419, 0x420, 
       0x428, 0x435, 0x438, 0x43c, 0x440, 0x447, 0x451, 0x459, 0x45f, 0x467, 
       0x477, 0x481, 0x484, 0x49b, 0x49d, 0x4a1, 0x4a7, 0x4ad, 0x4b2, 0x4b7, 
       0x4bf, 0x4c5, 0x4cb, 0x4d1, 0x4d5, 0x4d9, 0x4db, 0x4df, 0x4e8, 0x4ef, 
       0x4f3, 0x4f7, 0x4fb, 0x4fe, 0x500, 0x504, 0x508, 0x50d, 0x511, 0x515, 
       0x51c, 0x520, 0x528, 0x532, 0x536, 0x53a, 0x53c, 0x540, 0x546, 0x54a, 
       0x54e, 0x550, 0x552, 0x558, 0x55b, 0x565, 0x569, 0x56d, 0x577, 0x57b, 
       0x57e, 0x585, 0x58a, 0x590, 0x595, 0x59a, 
  };

  _serializedATN.insert(_serializedATN.end(), serializedATNSegment0,
    serializedATNSegment0 + sizeof(serializedATNSegment0) / sizeof(serializedATNSegment0[0]));


  atn::ATNDeserializer deserializer;
  _atn = deserializer.deserialize(_serializedATN);

  size_t count = _atn.getNumberOfDecisions();
  _decisionToDFA.reserve(count);
  for (size_t i = 0; i < count; i++) { 
    _decisionToDFA.emplace_back(_atn.getDecisionState(i), i);
  }
}

Python3Parser::Initializer Python3Parser::_init;
