#ifndef TENSORSLOW_INTERMEDIATE_CODE_LOGGER_H
#define TENSORSLOW_INTERMEDIATE_CODE_LOGGER_H

#include "ConsoleLogger.h"

namespace tensorslow {

class IntermediateCodeLogger : public Logger {
 public:
  static IntermediateCodeLogger& getInstance() {
    static IntermediateCodeLogger instance;
    return instance;
  }

  void log(const std::string& msg) override {
    std::lock_guard<std::mutex> lock(m_mutex);

    // 第一次调用时输出 mermaid 图表开头
    if (!m_initialized) {
      (*m_callback)("```mermaid\n");
      (*m_callback)("graph LR\n");
      m_initialized = true;
    }

    (*m_callback)(msg);
  }

  void terminate() {
    std::lock_guard<std::mutex> lock(m_mutex);
    if (m_initialized) {
      (*m_callback)("```\n");  // 结束 mermaid 图表
      m_initialized = false;  // 标记为未初始化，以便下次重新开始新的图表
    }
  }
  IntermediateCodeLogger(const IntermediateCodeLogger&) = delete;
  IntermediateCodeLogger& operator=(const IntermediateCodeLogger&) = delete;

 private:
  IntermediateCodeLogger() : m_initialized(false) {}

  bool m_initialized;
};

}  // namespace tensorslow

#endif  // TENSORSLOW_INTERMEDIATE_CODE_LOGGER_H