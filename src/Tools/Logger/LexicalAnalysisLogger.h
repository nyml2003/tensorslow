#ifndef TENSORSLOW_LEXICAL_ANALYSIS_LOGGER_H
#define TENSORSLOW_LEXICAL_ANALYSIS_LOGGER_H
#include "ConsoleLogger.h"
namespace tensorslow {
class LexicalAnalysisLogger : public Logger {
 public:
  static LexicalAnalysisLogger& getInstance() {
    static LexicalAnalysisLogger instance;
    return instance;
  }

  void log(const std::string& msg) override {
    std::lock_guard<std::mutex> lock(m_mutex);
    if (m_callback) {
      (*m_callback)(msg);
    }
  }
  LexicalAnalysisLogger(const LexicalAnalysisLogger&) = delete;
  LexicalAnalysisLogger& operator=(const LexicalAnalysisLogger&) = delete;

 private:
  LexicalAnalysisLogger() = default;
};
}  // namespace tensorslow

#endif  // TENSORSLOW_LEXICAL_ANALYSIS_LOGGER_H
