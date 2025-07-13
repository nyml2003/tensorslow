#ifndef TENSORSLOW_BYTECODE_LOGGER_H
#define TENSORSLOW_BYTECODE_LOGGER_H

#include "Logger.h"

namespace tensorslow {

class BytecodeLogger : public Logger {
 public:
  static BytecodeLogger& getInstance() {
    static BytecodeLogger instance;
    return instance;
  }

  void log(const std::string& msg) override {
    if (m_callback) {
      (*m_callback)(msg);
    }
  }

 private:
  BytecodeLogger() = default;
};

}  // namespace tensorslow

#endif  // TENSORSLOW_BYTECODE_LOGGER_H