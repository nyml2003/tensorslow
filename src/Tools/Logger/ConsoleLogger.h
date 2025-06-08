//
// Created by venty on 2025/5/12.
//

#ifndef TENSORSLOW_CONSOLE_LOGGER_H
#define TENSORSLOW_CONSOLE_LOGGER_H

#include "LogStrategy.h"
#include "Logger.h"

#include <mutex>

namespace tensorslow {

// ConsoleLogger 实现
class ConsoleLogger : public Logger {
 public:
  static ConsoleLogger& getInstance() {
    static ConsoleLogger instance;
    return instance;
  }

  void log(const std::string& msg) override {
    std::lock_guard<std::mutex> lock(m_mutex);
    if (m_callback) {
      (*m_callback)(msg);
    }
  }
  ConsoleLogger(const ConsoleLogger&) = delete;
  ConsoleLogger& operator=(const ConsoleLogger&) = delete;

 private:
  ConsoleLogger() : Logger(std::make_shared<DefaultLogStrategy>()) {}
};

}  // namespace tensorslow

#endif  // TENSORSLOW_CONSOLE_LOGGER_H
