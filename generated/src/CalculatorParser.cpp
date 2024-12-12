
// Generated from /app/grammar/Calculator.g4 by ANTLR 4.9.2


#include "CalculatorListener.h"
#include "CalculatorVisitor.h"

#include "CalculatorParser.h"


using namespace antlrcpp;
using namespace antlr4;

CalculatorParser::CalculatorParser(TokenStream *input) : Parser(input) {
  _interpreter = new atn::ParserATNSimulator(this, _atn, _decisionToDFA, _sharedContextCache);
}

CalculatorParser::~CalculatorParser() {
  delete _interpreter;
}

std::string CalculatorParser::getGrammarFileName() const {
  return "Calculator.g4";
}

const std::vector<std::string>& CalculatorParser::getRuleNames() const {
  return _ruleNames;
}

dfa::Vocabulary& CalculatorParser::getVocabulary() const {
  return _vocabulary;
}


//----------------- ProgContext ------------------------------------------------------------------

CalculatorParser::ProgContext::ProgContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* CalculatorParser::ProgContext::EOF() {
  return getToken(CalculatorParser::EOF, 0);
}

std::vector<CalculatorParser::StatementContext *> CalculatorParser::ProgContext::statement() {
  return getRuleContexts<CalculatorParser::StatementContext>();
}

CalculatorParser::StatementContext* CalculatorParser::ProgContext::statement(size_t i) {
  return getRuleContext<CalculatorParser::StatementContext>(i);
}

std::vector<tree::TerminalNode *> CalculatorParser::ProgContext::NEWLINE() {
  return getTokens(CalculatorParser::NEWLINE);
}

tree::TerminalNode* CalculatorParser::ProgContext::NEWLINE(size_t i) {
  return getToken(CalculatorParser::NEWLINE, i);
}


size_t CalculatorParser::ProgContext::getRuleIndex() const {
  return CalculatorParser::RuleProg;
}

void CalculatorParser::ProgContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<CalculatorListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterProg(this);
}

void CalculatorParser::ProgContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<CalculatorListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitProg(this);
}


antlrcpp::Any CalculatorParser::ProgContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<CalculatorVisitor*>(visitor))
    return parserVisitor->visitProg(this);
  else
    return visitor->visitChildren(this);
}

CalculatorParser::ProgContext* CalculatorParser::prog() {
  ProgContext *_localctx = _tracker.createInstance<ProgContext>(_ctx, getState());
  enterRule(_localctx, 0, CalculatorParser::RuleProg);
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
    setState(20);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while (_la == CalculatorParser::FUNCTION_PRINT) {
      setState(12);
      statement();
      setState(14); 
      _errHandler->sync(this);
      _la = _input->LA(1);
      do {
        setState(13);
        match(CalculatorParser::NEWLINE);
        setState(16); 
        _errHandler->sync(this);
        _la = _input->LA(1);
      } while (_la == CalculatorParser::NEWLINE);
      setState(22);
      _errHandler->sync(this);
      _la = _input->LA(1);
    }
    setState(23);
    match(CalculatorParser::EOF);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- PrimaryExprContext ------------------------------------------------------------------

CalculatorParser::PrimaryExprContext::PrimaryExprContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

CalculatorParser::ExprContext* CalculatorParser::PrimaryExprContext::expr() {
  return getRuleContext<CalculatorParser::ExprContext>(0);
}

tree::TerminalNode* CalculatorParser::PrimaryExprContext::INT() {
  return getToken(CalculatorParser::INT, 0);
}

tree::TerminalNode* CalculatorParser::PrimaryExprContext::FLOAT() {
  return getToken(CalculatorParser::FLOAT, 0);
}


size_t CalculatorParser::PrimaryExprContext::getRuleIndex() const {
  return CalculatorParser::RulePrimaryExpr;
}

void CalculatorParser::PrimaryExprContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<CalculatorListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterPrimaryExpr(this);
}

void CalculatorParser::PrimaryExprContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<CalculatorListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitPrimaryExpr(this);
}


antlrcpp::Any CalculatorParser::PrimaryExprContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<CalculatorVisitor*>(visitor))
    return parserVisitor->visitPrimaryExpr(this);
  else
    return visitor->visitChildren(this);
}

CalculatorParser::PrimaryExprContext* CalculatorParser::primaryExpr() {
  PrimaryExprContext *_localctx = _tracker.createInstance<PrimaryExprContext>(_ctx, getState());
  enterRule(_localctx, 2, CalculatorParser::RulePrimaryExpr);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    setState(31);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case CalculatorParser::T__0: {
        enterOuterAlt(_localctx, 1);
        setState(25);
        match(CalculatorParser::T__0);
        setState(26);
        expr();
        setState(27);
        match(CalculatorParser::T__1);
        break;
      }

      case CalculatorParser::INT: {
        enterOuterAlt(_localctx, 2);
        setState(29);
        match(CalculatorParser::INT);
        break;
      }

      case CalculatorParser::FLOAT: {
        enterOuterAlt(_localctx, 3);
        setState(30);
        match(CalculatorParser::FLOAT);
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

//----------------- MulDivExprContext ------------------------------------------------------------------

CalculatorParser::MulDivExprContext::MulDivExprContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

CalculatorParser::PrimaryExprContext* CalculatorParser::MulDivExprContext::primaryExpr() {
  return getRuleContext<CalculatorParser::PrimaryExprContext>(0);
}

CalculatorParser::MulDivExprContext* CalculatorParser::MulDivExprContext::mulDivExpr() {
  return getRuleContext<CalculatorParser::MulDivExprContext>(0);
}


size_t CalculatorParser::MulDivExprContext::getRuleIndex() const {
  return CalculatorParser::RuleMulDivExpr;
}

void CalculatorParser::MulDivExprContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<CalculatorListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterMulDivExpr(this);
}

void CalculatorParser::MulDivExprContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<CalculatorListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitMulDivExpr(this);
}


antlrcpp::Any CalculatorParser::MulDivExprContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<CalculatorVisitor*>(visitor))
    return parserVisitor->visitMulDivExpr(this);
  else
    return visitor->visitChildren(this);
}


CalculatorParser::MulDivExprContext* CalculatorParser::mulDivExpr() {
   return mulDivExpr(0);
}

CalculatorParser::MulDivExprContext* CalculatorParser::mulDivExpr(int precedence) {
  ParserRuleContext *parentContext = _ctx;
  size_t parentState = getState();
  CalculatorParser::MulDivExprContext *_localctx = _tracker.createInstance<MulDivExprContext>(_ctx, parentState);
  CalculatorParser::MulDivExprContext *previousContext = _localctx;
  (void)previousContext; // Silence compiler, in case the context is not used by generated code.
  size_t startState = 4;
  enterRecursionRule(_localctx, 4, CalculatorParser::RuleMulDivExpr, precedence);

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
    setState(34);
    primaryExpr();
    _ctx->stop = _input->LT(-1);
    setState(41);
    _errHandler->sync(this);
    alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 3, _ctx);
    while (alt != 2 && alt != atn::ATN::INVALID_ALT_NUMBER) {
      if (alt == 1) {
        if (!_parseListeners.empty())
          triggerExitRuleEvent();
        previousContext = _localctx;
        _localctx = _tracker.createInstance<MulDivExprContext>(parentContext, parentState);
        pushNewRecursionContext(_localctx, startState, RuleMulDivExpr);
        setState(36);

        if (!(precpred(_ctx, 1))) throw FailedPredicateException(this, "precpred(_ctx, 1)");
        setState(37);
        dynamic_cast<MulDivExprContext *>(_localctx)->op = _input->LT(1);
        _la = _input->LA(1);
        if (!(_la == CalculatorParser::T__2

        || _la == CalculatorParser::T__3)) {
          dynamic_cast<MulDivExprContext *>(_localctx)->op = _errHandler->recoverInline(this);
        }
        else {
          _errHandler->reportMatch(this);
          consume();
        }
        setState(38);
        primaryExpr(); 
      }
      setState(43);
      _errHandler->sync(this);
      alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 3, _ctx);
    }
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }
  return _localctx;
}

//----------------- AddSubExprContext ------------------------------------------------------------------

CalculatorParser::AddSubExprContext::AddSubExprContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

CalculatorParser::MulDivExprContext* CalculatorParser::AddSubExprContext::mulDivExpr() {
  return getRuleContext<CalculatorParser::MulDivExprContext>(0);
}

CalculatorParser::AddSubExprContext* CalculatorParser::AddSubExprContext::addSubExpr() {
  return getRuleContext<CalculatorParser::AddSubExprContext>(0);
}


size_t CalculatorParser::AddSubExprContext::getRuleIndex() const {
  return CalculatorParser::RuleAddSubExpr;
}

void CalculatorParser::AddSubExprContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<CalculatorListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterAddSubExpr(this);
}

void CalculatorParser::AddSubExprContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<CalculatorListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitAddSubExpr(this);
}


antlrcpp::Any CalculatorParser::AddSubExprContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<CalculatorVisitor*>(visitor))
    return parserVisitor->visitAddSubExpr(this);
  else
    return visitor->visitChildren(this);
}


CalculatorParser::AddSubExprContext* CalculatorParser::addSubExpr() {
   return addSubExpr(0);
}

CalculatorParser::AddSubExprContext* CalculatorParser::addSubExpr(int precedence) {
  ParserRuleContext *parentContext = _ctx;
  size_t parentState = getState();
  CalculatorParser::AddSubExprContext *_localctx = _tracker.createInstance<AddSubExprContext>(_ctx, parentState);
  CalculatorParser::AddSubExprContext *previousContext = _localctx;
  (void)previousContext; // Silence compiler, in case the context is not used by generated code.
  size_t startState = 6;
  enterRecursionRule(_localctx, 6, CalculatorParser::RuleAddSubExpr, precedence);

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
    setState(45);
    mulDivExpr(0);
    _ctx->stop = _input->LT(-1);
    setState(52);
    _errHandler->sync(this);
    alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 4, _ctx);
    while (alt != 2 && alt != atn::ATN::INVALID_ALT_NUMBER) {
      if (alt == 1) {
        if (!_parseListeners.empty())
          triggerExitRuleEvent();
        previousContext = _localctx;
        _localctx = _tracker.createInstance<AddSubExprContext>(parentContext, parentState);
        pushNewRecursionContext(_localctx, startState, RuleAddSubExpr);
        setState(47);

        if (!(precpred(_ctx, 1))) throw FailedPredicateException(this, "precpred(_ctx, 1)");
        setState(48);
        dynamic_cast<AddSubExprContext *>(_localctx)->op = _input->LT(1);
        _la = _input->LA(1);
        if (!(_la == CalculatorParser::T__4

        || _la == CalculatorParser::T__5)) {
          dynamic_cast<AddSubExprContext *>(_localctx)->op = _errHandler->recoverInline(this);
        }
        else {
          _errHandler->reportMatch(this);
          consume();
        }
        setState(49);
        mulDivExpr(0); 
      }
      setState(54);
      _errHandler->sync(this);
      alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 4, _ctx);
    }
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }
  return _localctx;
}

//----------------- ExprContext ------------------------------------------------------------------

CalculatorParser::ExprContext::ExprContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

CalculatorParser::AddSubExprContext* CalculatorParser::ExprContext::addSubExpr() {
  return getRuleContext<CalculatorParser::AddSubExprContext>(0);
}


size_t CalculatorParser::ExprContext::getRuleIndex() const {
  return CalculatorParser::RuleExpr;
}

void CalculatorParser::ExprContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<CalculatorListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterExpr(this);
}

void CalculatorParser::ExprContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<CalculatorListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitExpr(this);
}


antlrcpp::Any CalculatorParser::ExprContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<CalculatorVisitor*>(visitor))
    return parserVisitor->visitExpr(this);
  else
    return visitor->visitChildren(this);
}

CalculatorParser::ExprContext* CalculatorParser::expr() {
  ExprContext *_localctx = _tracker.createInstance<ExprContext>(_ctx, getState());
  enterRule(_localctx, 8, CalculatorParser::RuleExpr);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(55);
    addSubExpr(0);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- StatementContext ------------------------------------------------------------------

CalculatorParser::StatementContext::StatementContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* CalculatorParser::StatementContext::FUNCTION_PRINT() {
  return getToken(CalculatorParser::FUNCTION_PRINT, 0);
}

CalculatorParser::ExprContext* CalculatorParser::StatementContext::expr() {
  return getRuleContext<CalculatorParser::ExprContext>(0);
}


size_t CalculatorParser::StatementContext::getRuleIndex() const {
  return CalculatorParser::RuleStatement;
}

void CalculatorParser::StatementContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<CalculatorListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterStatement(this);
}

void CalculatorParser::StatementContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<CalculatorListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitStatement(this);
}


antlrcpp::Any CalculatorParser::StatementContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<CalculatorVisitor*>(visitor))
    return parserVisitor->visitStatement(this);
  else
    return visitor->visitChildren(this);
}

CalculatorParser::StatementContext* CalculatorParser::statement() {
  StatementContext *_localctx = _tracker.createInstance<StatementContext>(_ctx, getState());
  enterRule(_localctx, 10, CalculatorParser::RuleStatement);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(57);
    match(CalculatorParser::FUNCTION_PRINT);
    setState(58);
    match(CalculatorParser::T__0);
    setState(59);
    expr();
    setState(60);
    match(CalculatorParser::T__1);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

bool CalculatorParser::sempred(RuleContext *context, size_t ruleIndex, size_t predicateIndex) {
  switch (ruleIndex) {
    case 2: return mulDivExprSempred(dynamic_cast<MulDivExprContext *>(context), predicateIndex);
    case 3: return addSubExprSempred(dynamic_cast<AddSubExprContext *>(context), predicateIndex);

  default:
    break;
  }
  return true;
}

bool CalculatorParser::mulDivExprSempred(MulDivExprContext *_localctx, size_t predicateIndex) {
  switch (predicateIndex) {
    case 0: return precpred(_ctx, 1);

  default:
    break;
  }
  return true;
}

bool CalculatorParser::addSubExprSempred(AddSubExprContext *_localctx, size_t predicateIndex) {
  switch (predicateIndex) {
    case 1: return precpred(_ctx, 1);

  default:
    break;
  }
  return true;
}

// Static vars and initialization.
std::vector<dfa::DFA> CalculatorParser::_decisionToDFA;
atn::PredictionContextCache CalculatorParser::_sharedContextCache;

// We own the ATN which in turn owns the ATN states.
atn::ATN CalculatorParser::_atn;
std::vector<uint16_t> CalculatorParser::_serializedATN;

std::vector<std::string> CalculatorParser::_ruleNames = {
  "prog", "primaryExpr", "mulDivExpr", "addSubExpr", "expr", "statement"
};

std::vector<std::string> CalculatorParser::_literalNames = {
  "", "'('", "')'", "'*'", "'/'", "'+'", "'-'", "", "", "'print'"
};

std::vector<std::string> CalculatorParser::_symbolicNames = {
  "", "", "", "", "", "", "", "INT", "FLOAT", "FUNCTION_PRINT", "NEWLINE", 
  "WS"
};

dfa::Vocabulary CalculatorParser::_vocabulary(_literalNames, _symbolicNames);

std::vector<std::string> CalculatorParser::_tokenNames;

CalculatorParser::Initializer::Initializer() {
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
       0x3, 0xd, 0x41, 0x4, 0x2, 0x9, 0x2, 0x4, 0x3, 0x9, 0x3, 0x4, 0x4, 
       0x9, 0x4, 0x4, 0x5, 0x9, 0x5, 0x4, 0x6, 0x9, 0x6, 0x4, 0x7, 0x9, 
       0x7, 0x3, 0x2, 0x3, 0x2, 0x6, 0x2, 0x11, 0xa, 0x2, 0xd, 0x2, 0xe, 
       0x2, 0x12, 0x7, 0x2, 0x15, 0xa, 0x2, 0xc, 0x2, 0xe, 0x2, 0x18, 0xb, 
       0x2, 0x3, 0x2, 0x3, 0x2, 0x3, 0x3, 0x3, 0x3, 0x3, 0x3, 0x3, 0x3, 
       0x3, 0x3, 0x3, 0x3, 0x5, 0x3, 0x22, 0xa, 0x3, 0x3, 0x4, 0x3, 0x4, 
       0x3, 0x4, 0x3, 0x4, 0x3, 0x4, 0x3, 0x4, 0x7, 0x4, 0x2a, 0xa, 0x4, 
       0xc, 0x4, 0xe, 0x4, 0x2d, 0xb, 0x4, 0x3, 0x5, 0x3, 0x5, 0x3, 0x5, 
       0x3, 0x5, 0x3, 0x5, 0x3, 0x5, 0x7, 0x5, 0x35, 0xa, 0x5, 0xc, 0x5, 
       0xe, 0x5, 0x38, 0xb, 0x5, 0x3, 0x6, 0x3, 0x6, 0x3, 0x7, 0x3, 0x7, 
       0x3, 0x7, 0x3, 0x7, 0x3, 0x7, 0x3, 0x7, 0x2, 0x4, 0x6, 0x8, 0x8, 
       0x2, 0x4, 0x6, 0x8, 0xa, 0xc, 0x2, 0x4, 0x3, 0x2, 0x5, 0x6, 0x3, 
       0x2, 0x7, 0x8, 0x2, 0x40, 0x2, 0x16, 0x3, 0x2, 0x2, 0x2, 0x4, 0x21, 
       0x3, 0x2, 0x2, 0x2, 0x6, 0x23, 0x3, 0x2, 0x2, 0x2, 0x8, 0x2e, 0x3, 
       0x2, 0x2, 0x2, 0xa, 0x39, 0x3, 0x2, 0x2, 0x2, 0xc, 0x3b, 0x3, 0x2, 
       0x2, 0x2, 0xe, 0x10, 0x5, 0xc, 0x7, 0x2, 0xf, 0x11, 0x7, 0xc, 0x2, 
       0x2, 0x10, 0xf, 0x3, 0x2, 0x2, 0x2, 0x11, 0x12, 0x3, 0x2, 0x2, 0x2, 
       0x12, 0x10, 0x3, 0x2, 0x2, 0x2, 0x12, 0x13, 0x3, 0x2, 0x2, 0x2, 0x13, 
       0x15, 0x3, 0x2, 0x2, 0x2, 0x14, 0xe, 0x3, 0x2, 0x2, 0x2, 0x15, 0x18, 
       0x3, 0x2, 0x2, 0x2, 0x16, 0x14, 0x3, 0x2, 0x2, 0x2, 0x16, 0x17, 0x3, 
       0x2, 0x2, 0x2, 0x17, 0x19, 0x3, 0x2, 0x2, 0x2, 0x18, 0x16, 0x3, 0x2, 
       0x2, 0x2, 0x19, 0x1a, 0x7, 0x2, 0x2, 0x3, 0x1a, 0x3, 0x3, 0x2, 0x2, 
       0x2, 0x1b, 0x1c, 0x7, 0x3, 0x2, 0x2, 0x1c, 0x1d, 0x5, 0xa, 0x6, 0x2, 
       0x1d, 0x1e, 0x7, 0x4, 0x2, 0x2, 0x1e, 0x22, 0x3, 0x2, 0x2, 0x2, 0x1f, 
       0x22, 0x7, 0x9, 0x2, 0x2, 0x20, 0x22, 0x7, 0xa, 0x2, 0x2, 0x21, 0x1b, 
       0x3, 0x2, 0x2, 0x2, 0x21, 0x1f, 0x3, 0x2, 0x2, 0x2, 0x21, 0x20, 0x3, 
       0x2, 0x2, 0x2, 0x22, 0x5, 0x3, 0x2, 0x2, 0x2, 0x23, 0x24, 0x8, 0x4, 
       0x1, 0x2, 0x24, 0x25, 0x5, 0x4, 0x3, 0x2, 0x25, 0x2b, 0x3, 0x2, 0x2, 
       0x2, 0x26, 0x27, 0xc, 0x3, 0x2, 0x2, 0x27, 0x28, 0x9, 0x2, 0x2, 0x2, 
       0x28, 0x2a, 0x5, 0x4, 0x3, 0x2, 0x29, 0x26, 0x3, 0x2, 0x2, 0x2, 0x2a, 
       0x2d, 0x3, 0x2, 0x2, 0x2, 0x2b, 0x29, 0x3, 0x2, 0x2, 0x2, 0x2b, 0x2c, 
       0x3, 0x2, 0x2, 0x2, 0x2c, 0x7, 0x3, 0x2, 0x2, 0x2, 0x2d, 0x2b, 0x3, 
       0x2, 0x2, 0x2, 0x2e, 0x2f, 0x8, 0x5, 0x1, 0x2, 0x2f, 0x30, 0x5, 0x6, 
       0x4, 0x2, 0x30, 0x36, 0x3, 0x2, 0x2, 0x2, 0x31, 0x32, 0xc, 0x3, 0x2, 
       0x2, 0x32, 0x33, 0x9, 0x3, 0x2, 0x2, 0x33, 0x35, 0x5, 0x6, 0x4, 0x2, 
       0x34, 0x31, 0x3, 0x2, 0x2, 0x2, 0x35, 0x38, 0x3, 0x2, 0x2, 0x2, 0x36, 
       0x34, 0x3, 0x2, 0x2, 0x2, 0x36, 0x37, 0x3, 0x2, 0x2, 0x2, 0x37, 0x9, 
       0x3, 0x2, 0x2, 0x2, 0x38, 0x36, 0x3, 0x2, 0x2, 0x2, 0x39, 0x3a, 0x5, 
       0x8, 0x5, 0x2, 0x3a, 0xb, 0x3, 0x2, 0x2, 0x2, 0x3b, 0x3c, 0x7, 0xb, 
       0x2, 0x2, 0x3c, 0x3d, 0x7, 0x3, 0x2, 0x2, 0x3d, 0x3e, 0x5, 0xa, 0x6, 
       0x2, 0x3e, 0x3f, 0x7, 0x4, 0x2, 0x2, 0x3f, 0xd, 0x3, 0x2, 0x2, 0x2, 
       0x7, 0x12, 0x16, 0x21, 0x2b, 0x36, 
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

CalculatorParser::Initializer CalculatorParser::_init;
