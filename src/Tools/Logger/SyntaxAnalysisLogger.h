#ifndef TENSORSLOW_SYNTAX_ANALYSIS_LOGGER_H
#define TENSORSLOW_SYNTAX_ANALYSIS_LOGGER_H


#include "Logger.h"

namespace tensorslow {

class SyntaxAnalysisLogger : public Logger {
 public:
  static SyntaxAnalysisLogger& getInstance() {
    static SyntaxAnalysisLogger instance;
    return instance;
  }

  void log(const std::string& msg) override {
    if (m_callback) {
      (*m_callback)(msg);
    }
  }

 private:
  SyntaxAnalysisLogger() = default;
};

}  // namespace tensorslow

#endif  // TENSORSLOW_SYNTAX_ANALYSIS_LOGGER_H