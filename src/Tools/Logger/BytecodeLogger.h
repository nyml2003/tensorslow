#ifndef TENSORSLOW_BYTECODE_LOGGER_H
#define TENSORSLOW_BYTECODE_LOGGER_H

#include "ConsoleLogger.h"

namespace tensorslow {

class BytecodeLogger : public Logger {
 public:
  static BytecodeLogger& getInstance() {
    static BytecodeLogger instance;
    return instance;
  }

  void log(const std::string& msg) override {
    std::lock_guard<std::mutex> lock(m_mutex);
    if (m_callback) {
      (*m_callback)(msg);
    }
  }
  BytecodeLogger(const BytecodeLogger&) = delete;
  BytecodeLogger& operator=(const BytecodeLogger&) = delete;

 private:
  BytecodeLogger() = default;
};

}  // namespace tensorslow

#endif  // TENSORSLOW_BYTECODE_LOGGER_H