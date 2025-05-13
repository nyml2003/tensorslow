#ifndef TENSORSLOW_SYNTAX_ANALYSIS_LOGGER_H
#define TENSORSLOW_SYNTAX_ANALYSIS_LOGGER_H

#include <memory>
#include <mutex>
#include <string>
#include "ConsoleLogger.h"
#include "Logger.h"

namespace tensorslow {

class SyntaxAnalysisLogger : public Logger {
 public:
  static SyntaxAnalysisLogger& getInstance() {
    static SyntaxAnalysisLogger instance;
    return instance;
  }

  void log(const std::string& msg) override {
    std::lock_guard<std::mutex> lock(m_mutex);
    if (m_callback) {
      (*m_callback)(msg);
    }
  }
  SyntaxAnalysisLogger(const SyntaxAnalysisLogger&) = delete;
  SyntaxAnalysisLogger& operator=(const SyntaxAnalysisLogger&) = delete;

 private:
  SyntaxAnalysisLogger() = default;
};

}  // namespace tensorslow

#endif  // TENSORSLOW_SYNTAX_ANALYSIS_LOGGER_H