//
// Created by venty on 2025/5/12.
//

#ifndef TENSORSLOW_CONSOLE_LOGGER_H
#define TENSORSLOW_CONSOLE_LOGGER_H

#include "LogStrategy.h"
#include "Logger.h"

namespace tensorslow {

// ConsoleLogger 实现
class ConsoleLogger : public Logger {
 public:
  static ConsoleLogger& getInstance() {
    static ConsoleLogger instance;
    return instance;
  }

  void log(const std::string& msg) override {
    if (m_callback) {
      (*m_callback)(msg);
    }
  }

 private:
  ConsoleLogger() : Logger(std::make_unique<DefaultLogStrategy>()) {}
};

}  // namespace tensorslow

#endif  // TENSORSLOW_CONSOLE_LOGGER_H
