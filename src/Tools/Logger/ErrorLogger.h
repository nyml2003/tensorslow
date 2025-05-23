//
// Created by venty on 2025/5/12.
//

#ifndef TENSORSLOW_ERROR_LOGGER_H
#define TENSORSLOW_ERROR_LOGGER_H

#include "ConsoleLogger.h"

namespace tensorslow {

class ErrorLogger : public Logger {
 public:
  static ErrorLogger& getInstance() {
    static ErrorLogger instance;
    return instance;
  }

  void log(const std::string& msg) override {
    if (m_callback) {
      (*m_callback)("[ERROR] ");
      (*m_callback)(msg);
      (*m_callback)("\n");
    }
  }
  ErrorLogger(const ErrorLogger&) = delete;
  ErrorLogger& operator=(const ErrorLogger&) = delete;

 private:
  ErrorLogger() = default;
};

}  // namespace tensorslow

#endif  // TENSORSLOW_ERROR_LOGGER_H